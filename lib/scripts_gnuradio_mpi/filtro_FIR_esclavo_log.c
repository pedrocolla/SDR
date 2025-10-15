/*
 * Universidad Autónoma de Entre Ríos
 * Facultad de Ciencia y Tecnología
 * Ingeniería en Telecomunicaciones
 * 
 * Proyecto I+D Procesamiento SDR en cluster distribuido
 * 
 * Descripción:
 * Implementación del bloque FIR para procesamiento distribuido.
 * Este componente aplica un filtro de respuesta finita (FIR) sobre los
 * datos de entrada, con soporte para ejecución paralela mediante MPI.
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <mpi.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv){
    int node;
    char cpuname[20];
    int  cpulen;
    
    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &node);
    MPI_Get_processor_name( cpuname, &cpulen );
 
    printf("[%s] Iniciado el esclavo (%d)!\n", cpuname,node);
    
    MPI_Comm comm_master;
    MPI_Comm_get_parent(&comm_master);
    
    // Recibe la cantidad de coeficientes que debe recibir para alojar memoria.
    int num_coefs;
    MPI_Bcast(&num_coefs, 1, MPI_INT, 0, comm_master);
    
    // Recibe todos los coeficientes y los guarda.
    float* coefs = malloc(sizeof(float) * num_coefs);
    if(!coefs)
    {
        printf("Falló la asignación de memoria al array de coeficientes. Esclavo: %d\n", node);
        return 1;
    }
    MPI_Bcast(coefs, num_coefs, MPI_FLOAT, 0, comm_master);
    
    // Recibe la posición del primer coeficiente que le corresponde calcular
    int indice_primer_coef;
    MPI_Recv(&indice_primer_coef, 1, MPI_INT, 0, 0, comm_master, MPI_STATUS_IGNORE);
    
    // Recibe la cantidad de coeficientes que le corresponde calcular
    int num_coefs_locales;
    MPI_Recv(&num_coefs_locales, 1, MPI_INT, 0, 0, comm_master, MPI_STATUS_IGNORE);

    if(num_coefs_locales == 0)
    {
        printf("El número de coeficientes asignados es 0. Esclavo: %d\n", node);
    }else
    {
        printf("Esclavo %d: Calcula de %d a %d. \n", node, indice_primer_coef, indice_primer_coef+num_coefs_locales-1);    
    }
    
    // Crea el espacio para almacenar las muestras del filtro completo
    float* historial = malloc(sizeof(float)*(num_coefs-1));
    if(!historial)
    {
        printf("Falló la asignación de memoria al array de historial. Esclavo: %d\n", node);
        free(coefs);
        free(historial);
        return 1;
    }
    memset(historial, 0, sizeof(float)*(num_coefs-1));
    
    float* entrada = NULL;
    float* salida = NULL;
    int tamaño_actual_entrada = 0;
    
    // Creación de archivo log.
    char nombre[128];
    char strfecha[64];
    time_t t = time(NULL);
    struct tm* fecha = localtime(&t);
    strftime(strfecha, sizeof(strfecha), "%y-%m-%d_%H-%M-%S.csv", fecha);
    snprintf(nombre, sizeof(nombre), "/srv/clusterfs/sdr/logs_filtro/log_esclavo_%s-%d_%s", cpuname, node, strfecha);
 
    struct timespec tiempo;
    long long t0, t1, t2, t3, t4, t5, t6, t7 = 0;   
    FILE* log = fopen(nombre, "w");
    
    fprintf(log, "Inicio, Continuar, Recep_Num_Muestras, Ampliacion_Array, Recepcion, Convolucion, Historial, Devolucion, Num_Muestras\n");
    
    bool debe_parar = false;
    while(debe_parar == false)
    {
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t0 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;

        // Recibe la indicación de que el programa continua.
        MPI_Bcast(&debe_parar, 1, MPI_C_BOOL, 0, comm_master);
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t1= tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
        
        // Recibe la indicación de la cantidad de muestras por recibir.
        int num_muestras;
        MPI_Bcast(&num_muestras, 1, MPI_INT, 0, comm_master);
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t2 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
        
        // Cada vez que reciba un volumen de muestras mayor que cualquiera recibido anteriormente, aumenta de forma permanente el tamaño de los buffers. 
        if(num_muestras > tamaño_actual_entrada)
        {
            free(entrada);
            free(salida);
            entrada = malloc(sizeof(float) * num_muestras);
            salida = malloc(sizeof(float) * num_muestras);
            tamaño_actual_entrada = num_muestras;
            if(!entrada || !salida)
            {
                printf("Falló la asignación de memoria a los array de entrada y salida. Esclavo: %d\n", node);
                free(entrada);
                free(salida);
                free(coefs);
                free(historial);
                return 1;
            }
        }
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t3 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
        
        // Recibe las muestras.
        MPI_Bcast(entrada, num_muestras, MPI_FLOAT, 0, comm_master);
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t4 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;

        // Calculo de convolución.
        for(int i=0; i < num_muestras;i++)
        {
            salida[i] = 0;
            
            for(int c=0; c < num_coefs_locales; c++)
            {
                // Se separa el aporte de las muestras nuevas y las de ciclos anteriores.
                if(i<indice_primer_coef+c)
                {
                    salida[i] += historial[indice_primer_coef-1-i+c] * coefs[indice_primer_coef+c];
                }else
                {
                    salida[i] += entrada[i-indice_primer_coef-c] * coefs[indice_primer_coef+c];
                }
            }     
        }
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t5 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
        
        // Actualización del historial de muestras.
        if(num_muestras < num_coefs-1)
        {
            for(int h=0; h < num_coefs-1-num_muestras; h++)
            {
                historial[num_coefs-2-h] = historial[num_coefs-2-h-num_muestras];
            }
            for(int h=0; h < num_muestras; h++)
            {
                historial[h] = entrada[num_muestras-1-h];
            }
        }else
        {
            for(int h=0; h < num_coefs-1; h++)
            {
                historial[h] = entrada[num_muestras-1-h];
            }      
        }
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t6 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
        
        // Devolución del resultado.
        MPI_Reduce(salida, NULL, num_muestras, MPI_FLOAT, MPI_SUM, 0, comm_master);
        clock_gettime(CLOCK_MONOTONIC, &tiempo);
        t7 = tiempo.tv_sec * 1000000000LL + tiempo.tv_nsec;
        
        // Recibe la indicación de que el archivo log continúa.
        bool log_activo = false;
        MPI_Bcast(&log_activo, 1, MPI_C_BOOL, 0, comm_master);
        
        if(log_activo == true)
        {
            fprintf(log, "%lld, %lld, %lld, %lld, %lld, %lld, %lld, %lld, %d\n",t0, t1, t2, t3, t4, t5, t6, t7, num_muestras);  
            fflush(log);
        }
                    
    }
    free(coefs);
    free(historial);
    free(entrada);
    free(salida);
    fsync(fileno(log)); 
    fclose(log);
    printf("Finalizando... Esclavo: %d\n", node);
    MPI_Finalize();
}
