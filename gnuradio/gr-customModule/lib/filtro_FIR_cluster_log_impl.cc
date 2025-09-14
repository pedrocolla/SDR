/* -*- c++ -*- */
/*
 * Copyright 2025 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "filtro_FIR_cluster_log_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace customModule {

using input_type = float;
using output_type = float;
filtro_FIR_cluster_log::sptr filtro_FIR_cluster_log::make(const std::vector<float>& coef,
                                                          int num_nodos,
                                                          int num_muestras_log)
{
    return gnuradio::make_block_sptr<filtro_FIR_cluster_log_impl>(
        coef, num_nodos, num_muestras_log);
}


filtro_FIR_cluster_log_impl::filtro_FIR_cluster_log_impl(const std::vector<float>& coef,
                                                         int num_nodos,
                                                         int num_muestras_log)
    : gr::sync_block("filtro_FIR_cluster_log",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    _num_muestras_log = num_muestras_log;
    
    char cpuname[MPI_MAX_PROCESSOR_NAME];
    int cpulen;
    MPI_Init(NULL, NULL);

    //MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Get_processor_name(cpuname, &cpulen);
    
    MPI_Info info;
    MPI_Info_create(&info);
    MPI_Info_set(info, "bind_to", "none");
    MPI_Info_set(info, "map_by", "slot");
    MPI_Info_set(info, "hostfile", "/srv/clusterfs/sdr/etc/hostfile.s");
    
    printf("[%s] Filtro maestro iniciado.\n", cpuname);
    
    const char* ruta_esclavo;
    if(_num_muestras_log != 0)
    {   
        ruta_esclavo = "/srv/clusterfs/sdr/lib/scripts_gnuradio_mpi/filtro_FIR_esclavo_log";
    }else
    {
        ruta_esclavo = "/srv/clusterfs/sdr/lib/scripts_gnuradio_mpi/filtro_FIR_esclavo";
    }
 
    MPI_Comm_spawn(ruta_esclavo, MPI_ARGV_NULL, num_nodos, info, 0, MPI_COMM_SELF, &inter_comm, MPI_ERRCODES_IGNORE);

 
    int _num_coefs = coef.size();
    
    if (num_nodos == 0 || _num_coefs == 0)
    {
        printf("Los coeficientes y el numero de nodos no pueden ser 0.");
    }
    // Envia todos los coeficientes a todos los nodos.
    MPI_Bcast(&_num_coefs, 1, MPI_INT, MPI_ROOT, inter_comm);
    MPI_Bcast(const_cast<float*>(coef.data()), _num_coefs, MPI_FLOAT, MPI_ROOT, inter_comm);

    int num_coefs_por_nodo = _num_coefs / num_nodos;
    //printf("Coeficientes por nodo: (%d).\n", num_coefs_por_nodo);
    int coefs_resto = _num_coefs % num_nodos;
   
    int indice_primer_coef = 0;
    for(int n = 0; n < num_nodos; n++)
    {
        int num_coefs_enviar = num_coefs_por_nodo;
        // Si quedarán coeficientes sin asignar, los primeros [coefs_resto] trabajadores se asignan uno extra.
        if(n < coefs_resto)
        {
            num_coefs_enviar++;
        }
        // Indica al nodo cual es el primer coeficiente que le corresponde.
        MPI_Send(&indice_primer_coef, 1, MPI_INT, n, 0, inter_comm);
        // Indica al nodo cuantos coeficientes debe calcular a partir del primero.
        MPI_Send(&num_coefs_enviar, 1, MPI_INT, n, 0, inter_comm);
        printf("Coeficientes enviados al esclavo %d.\n", n);
        indice_primer_coef += num_coefs_enviar;
    }
    
    // Inicialización de log
    if(_num_muestras_log != 0)
    {
        char nombre[64];
        time_t t = time(NULL);
        struct tm* fecha = localtime(&t);
        strftime(nombre, sizeof(nombre), "/srv/clusterfs/sdr/logs_filtro/log_%y-%m-%d_%H-%M-%S.csv", fecha);
        
        log = fopen(nombre, "w");
        if(log == NULL)
        {
            perror("Error al generar el archivo log.\n");
        }else
        {
            printf("Generado el archivo: %s\n", nombre);
        }
        
        fprintf(log, "Inicio, Arrays, Continuar, Muestras, Transmision, Devolucion, Num_muestras \n");
    }
  
}

/*
 * Our virtual destructor.
 */
filtro_FIR_cluster_log_impl::~filtro_FIR_cluster_log_impl() 
{
    bool debe_parar = true;

    MPI_Bcast(&debe_parar, 1, MPI_C_BOOL, MPI_ROOT, inter_comm);
    //printf("Enviada correctamente la señal de terminar.\n");
    
    MPI_Finalize();
    printf("MPI finalizado correctamente en el maestro.\n");
}

int filtro_FIR_cluster_log_impl::work(int noutput_items,
                                      gr_vector_const_void_star& input_items,
                                      gr_vector_void_star& output_items)
{
    struct timespec tiempo;
    long long t0, t1, t2, t3, t4, t5 = 0;   
    // Inicio
    clock_gettime(CLOCK_MONOTONIC, &tiempo);
    t0 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
    
    // Inicio del ciclo de trabajo distribuido actual.
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);
    clock_gettime(CLOCK_MONOTONIC, &tiempo);
    t1 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;

    bool debe_parar = false;
    MPI_Bcast(&debe_parar, 1, MPI_C_BOOL, MPI_ROOT, inter_comm);
    //printf("Enviada correctamente la señal de continuar.\n");
    clock_gettime(CLOCK_MONOTONIC, &tiempo);
    t2 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
    
    // Primero se le indica a los nodos la cantidad de muestras que deben recibir.
    MPI_Bcast(&noutput_items, 1, MPI_INT, MPI_ROOT, inter_comm);
    //printf("Enviado correctamente el número de muestras a recibir (%d).\n", noutput_items);
    clock_gettime(CLOCK_MONOTONIC, &tiempo);
    t3 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
    
    // Luego se envian las muestras.
    MPI_Bcast((void*)in, noutput_items, MPI_FLOAT, MPI_ROOT, inter_comm);
    //printf("Enviadas correctamente las muestras.\n");
    clock_gettime(CLOCK_MONOTONIC, &tiempo);
    t4 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
    
    //MPI_Reduce(const void *sendbuf, void *recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm);
    MPI_Reduce(NULL, out, noutput_items, MPI_FLOAT, MPI_SUM, MPI_ROOT, inter_comm);
    //printf("Recibidas correctamentes las muestras filtradas.\n");
    clock_gettime(CLOCK_MONOTONIC, &tiempo);
    t5 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
    
    bool log_activo = false;
    if(_num_muestras_log != 0)
    {
        if(contador < _num_muestras_log || _num_muestras_log == -1)
        {
            fprintf(log, "%lld, %lld, %lld, %lld, %lld, %lld, %d\n",t0, t1, t2, t3, t4, t5, noutput_items);
            contador += noutput_items;
            log_activo = true;
        }else if(log != NULL)
        {
            fclose(log);
            log = NULL;
            printf("Se guardó el archivo log.\n");
        }   
    }
    MPI_Bcast(&log_activo, 1, MPI_C_BOOL, MPI_ROOT, inter_comm);
    
    return noutput_items;
}

} /* namespace customModule */
} /* namespace gr */
