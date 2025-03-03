/* -*- c++ -*- */
/*
 * Copyright 2024 gr-customModule author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "filtro_FIR_cluster_impl.h"
#include <gnuradio/io_signature.h>
#include <mpi.h>

namespace gr {
namespace customModule {


using input_type = float;
using output_type = float;

filtro_FIR_cluster::sptr filtro_FIR_cluster::make(const std::vector<float>& coef, int num_nodo)
{
    return gnuradio::make_block_sptr<filtro_FIR_cluster_impl>(coef, num_nodo);
}


MPI_Comm inter_comm;  // Comunicador para procesos esclavos

filtro_FIR_cluster_impl::filtro_FIR_cluster_impl(const std::vector<float>& coef, int num_nodo)
    : gr::sync_block("filtro_FIR_Cluster",
                     gr::io_signature::make(
                         1 /* min inputs */, 1 /* max inputs */, sizeof(input_type)),
                     gr::io_signature::make(
                         1 /* min outputs */, 1 /*max outputs */, sizeof(output_type)))
{
    _num_nodos = num_nodo;
    
    char cpuname[20];
    int  cpulen;
    MPI_Init(NULL, NULL);

    //MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Get_processor_name( cpuname, &cpulen );
    
    printf("[%s] Filtro maestro iniciado.\n", cpuname);
    
    MPI_Comm_spawn("/clusterfs/sdr/lib/scripts_gnuradio_mpi/filtro_FIR_esclavo", MPI_ARGV_NULL, _num_nodos, MPI_INFO_NULL, 0, MPI_COMM_SELF, &inter_comm, MPI_ERRCODES_IGNORE);
    
    int _num_coefs = coef.size();
    
    if (_num_nodos == 0 || _num_coefs == 0)
    {
        printf("Los coeficientes y el numero de nodos no pueden ser 0.");
    }
    // Envia todos los coeficientes a todos los nodos.
    MPI_Bcast(&_num_coefs, 1, MPI_INT, MPI_ROOT, inter_comm);
    MPI_Bcast(const_cast<float*>(coef.data()), _num_coefs, MPI_FLOAT, MPI_ROOT, inter_comm);
    
    int num_coefs_por_nodo = _num_coefs / _num_nodos;
    //printf("Coeficientes por nodo: (%d).\n", num_coefs_por_nodo);
    int coefs_resto = _num_coefs % _num_nodos;
    
    int indice_primer_coef = 0;
    for(int n = 0; n < _num_nodos; n++)
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
    
}

/*
 * Our virtual destructor.
 */
filtro_FIR_cluster_impl::~filtro_FIR_cluster_impl() 
{
    bool debe_parar = true;

    MPI_Bcast(&debe_parar, 1, MPI_C_BOOL, MPI_ROOT, inter_comm);
    //printf("Enviada correctamente la señal de terminar.\n");
    
    MPI_Finalize();
    printf("MPI finalizado correctamente en el maestro.\n");
}

int filtro_FIR_cluster_impl::work(int noutput_items,
                                  gr_vector_const_void_star& input_items,
                                  gr_vector_void_star& output_items)
{
    auto in = static_cast<const input_type*>(input_items[0]);
    auto out = static_cast<output_type*>(output_items[0]);

    bool debe_parar = false;
    MPI_Bcast(&debe_parar, 1, MPI_C_BOOL, MPI_ROOT, inter_comm);
    //printf("Enviada correctamente la señal de continuar.\n");
    
    // Primero se le indica a los nodos la cantidad de muestras que deben recibir.
    MPI_Bcast(&noutput_items, 1, MPI_INT, MPI_ROOT, inter_comm);
    //printf("Enviado correctamente el número de muestras a recibir (%d).\n", noutput_items);
    
    // Luego se envian las muestras.
    MPI_Bcast((void*)in, noutput_items, MPI_FLOAT, MPI_ROOT, inter_comm);
    //printf("Enviadas correctamente las muestras.\n");
    
    //MPI_Reduce(const void *sendbuf, void *recvbuf, int count,
      //         MPI_Datatype datatype, MPI_Op op, int root,
        //       MPI_Comm comm)
    
    MPI_Reduce(NULL, out, noutput_items, MPI_FLOAT, MPI_SUM, MPI_ROOT, inter_comm);
    /*
    for(int n=0; n< _num_nodos; n++)
    {
        float[]
        MPI_Gather(NULL, 0, MPI_FLOAT, out, noutput_items, MPI_FLOAT, MPI_ROOT, inter_comm);
    }*/
    
    //printf("Recibidas correctamentes las muestras filtradas.\n");
    return noutput_items;
}



} /* namespace customModule */
} /* namespace gr */
