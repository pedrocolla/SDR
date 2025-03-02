#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdbool.h>

#include <signal.h>
#include <stdlib.h>
void señal(int señal)
{
    if(señal == SIGSEGV)
    {
        printf("Problema en el stack");
        exit(1);
    }
}

int main(int argc, char** argv){
    signal(SIGSEGV, señal);
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
    
    // Recibe los coeficientes y los guarda. TAG 0
    //float coefs[num_coefs];
    float* coefs = malloc(sizeof(float) * num_coefs);
    if(!coefs)
    {
        printf("Falló la asignación de memoria al array de coeficientes.");
        return 1;
    }
    MPI_Bcast(coefs, num_coefs, MPI_FLOAT, 0, comm_master);
    
    // Recibe la posición del primer coeficiente que le corresponde calcular
    int indice_primer_coef;
    MPI_Recv(&indice_primer_coef, 1, MPI_INT, 0, 0, comm_master, MPI_STATUS_IGNORE);
    
    // Recibe la cantidad de coeficientes que le corresponde calcular
    int num_coefs_locales;
    MPI_Recv(&num_coefs_locales, 1, MPI_INT, 0, 0, comm_master, MPI_STATUS_IGNORE);
    printf("Esclavo %d: Calcula de %d a %d. \n", node, indice_primer_coef, indice_primer_coef+num_coefs_locales-1);
    
    //float historial[num_coefs-1];
    float* historial = malloc(sizeof(float)*(num_coefs-1));
    if(!historial)
    {
        printf("Falló la asignación de memoria al array de historial.");
        free(coefs);
        free(historial);
        return 1;
    }
    memset(historial, 0, sizeof(float)*(num_coefs-1));
    
    float* entrada = NULL;
    float* salida = NULL;
    int tamaño_actual_entrada = 0;
    
    bool debe_parar = false;
    while(debe_parar == false)
    {
        // Recibe la indicación de que el programa continua.
        MPI_Bcast(&debe_parar, 1, MPI_C_BOOL, 0, comm_master);
        //printf("Recibida correctamente la señal de continuación. Esclavo: %d\n", node);
        
        // Primero recibe un broadcast indicando la cantidad de muestras por recibir.
        int num_muestras;
        MPI_Bcast(&num_muestras, 1, MPI_INT, 0, comm_master);
        //printf("Recibida correctamente la cantidad de muestras esperada (%d). Esclavo: %d\n", num_muestras, node);
        
        // Luego se prepara el buffer y recibe las muestras.
        //float entrada[num_muestras];
        
        if(num_muestras > tamaño_actual_entrada)
        {
            free(entrada);
            free(salida);
            entrada = malloc(sizeof(float) * num_muestras);
            salida = malloc(sizeof(float) * num_muestras);
            tamaño_actual_entrada = num_muestras;
            if(!entrada || !salida)
            {
                printf("Falló la asignación de memoria a los array de entrada y salida.");
                free(entrada);
                free(salida);
                free(coefs);
                free(historial);
                return 1;
            }
        }
        
        MPI_Bcast(entrada, num_muestras, MPI_FLOAT, 0, comm_master);
        //printf("Muestras recibidas correctamente. Esclavo: %d\n", node);
        
        //float salida[num_muestras];
        
        for(int i=0; i < num_muestras;i++)
        {
            salida[i] = 0;
            
            for(int c=0; c < num_coefs_locales; c++)
            {
                if(i<indice_primer_coef+c)
                {
                    salida[i] += historial[indice_primer_coef-1-i+c] * coefs[indice_primer_coef+c];
                }else
                {
                    salida[i] += entrada[i-indice_primer_coef-c] * coefs[indice_primer_coef+c];
                }
            }     
        }
        
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
        
        
        MPI_Reduce(salida, NULL, num_muestras, MPI_FLOAT, MPI_SUM, 0, comm_master);
        //MPI_Gather(salida, num_muestras, MPI_FLOAT, NULL, 0, MPI_FLOAT, 0, comm_master);
        //printf("Enviadas correctamente las muestras filtradas. Esclavo: %d\n", node);
    }
    free(coefs);
    free(historial);
    free(entrada);
    free(salida);
    printf("Finalizando... Esclavo: %d\n", node);
    MPI_Finalize();
}
/*
        // Convolución con historial
        int lim_historial = num_coefs-1;
        if(num_muestras<num_coefs)
        {
            lim_historial = num_muestras;
        }
        for(int m=0; m < lim_historial; m++)
        {
            salida[m] = 0;
            for(int c=0; c < num_coefs-1-m; c++)
            {
                salida[m] += historial[c] * coefs[1+c+m];
            }
            
            for(int c=0; c < m+1; c++)
            {
                salida[m] += entrada[c] * coefs[m-c];
            }
       }
    
        
        // Convolución de la entrada
        for (int m=; m < num_muestras; m++)
        {
            salida[m] = 0;
            for(int c=0; c < num_coefs; c++)
            {
                salida[m] += entrada[m-c] * coefs[c];
            }
        }
        
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
        
        */
