/*------------------------------------------------------------------------------------------------
  Universidad Aut  noma de Entre Rios
  Facultad de Ciencia y Tecnolog  a
  Ingenier  a de Telecomunicaciones

  Proyecto de investigaci  n
  Procesamiento de se  ales mediante cluster
  Microcluster LAN
  Programa de prueba para comparar performance del cluster 
  Evaluaci  n de la conjetura de Collatz en un ambiente OpenMPI

  compile with gcc -o collatz_serial collatz_serial.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define false 0
#define true !false

long collatz(long n, long iterations, int outputFlag){ // Recursive algorithm for collatz problem

        if (outputFlag != false){ // We print out every n (number of the interval) before doing collatz algorithm (this is just to check if everything is okay)
                printf("Collatz %ld\n",n);
        }
        if(n == 1){
                return iterations;
        } else if(n%2 == 0){
                n = n/2;
                iterations++;
                iterations = collatz(n, iterations, outputFlag);
                return iterations;
        } else{
                n =  n*3+1;
                iterations++;
                iterations = collatz(n, iterations, outputFlag);
                return iterations;
        }
}


int main (int argc, char** argv) {

  long q = 0;
  long m = atol(argv[1]);
  long n = atol(argv[2]) + 1;
  long blockSize = atoi(argv[3]);
  int outputFlag = atoi(argv[4]);

  long start_i = m;
  long end_i= n;
  long job, longestJob = 0;
  long longestIt = 0, tempIt;
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  //long n = 10000;
  for (job = start_i; job < end_i; job++) // For every interval of block size we do collatz
  {



      tempIt = collatz(job,0,outputFlag);
      q++;
      if(outputFlag != 0)
         printf("N=%ld iterations=%ld\n",job,tempIt);
      //if (tempIt > longestIt) // We count the longes iteration of interval (this is just to be sure if algorithm is working okay)
      //{
      //   longestIt = tempIt;
      //   longestJob = job;
      //}
  }
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("tasks[%ld] collatz took %f seconds to execute \n", q,cpu_time_used); 

  return 0;
}
