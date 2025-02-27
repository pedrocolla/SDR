"""
/*------------------------------------------------------------------------------------------------
  Universidad Autónoma de Entre Rios
  Facultad de Ciencia y Tecnología
  Ingeniería de Telecomunicaciones

  Proyecto de investigación
  Procesamiento de señales mediante cluster
  Microcluster LAN
  Programa de prueba para comparar performance del cluster
  Evaluación de la conjetura de Collatz en un ambiente OpenMPI

  This code computes primes between a lower and upper marks

  To execute this code:

  mpirun -np NUMBER_OF_PROCESSES --hostfile HOSTFILE python primes.py [-l LOWER] [-u UPPER] [-s SLICE] [-v] 

where....

  NUMBER_OF_PROCESSES is the number of desired processes.
  HOSTFILE is a file which records the location of your nodes.

""" 
from mpi4py import MPI
import argparse
import math
import sys
import socket
import time

def erathostenes(lower,upper):
 dataset=""
 return dataset


cpu=socket.gethostname()

#*--- Initial connection with the MPI environment

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
cpu = MPI.Get_processor_name()
verbose=False
dataQueue=""
#*--- Segment the workload

lower = 1
upper = 500
total_slices=2


#--- Arguments passed
if rank == 0:
   n = len(sys.argv) 
   i=0
   while i<n and n>1:
       arg=sys.argv[i]
       arg=arg.upper()
       if arg == "-L":
          lower=int(sys.argv[i+1])
          print("[%s] Lower is %d" % (cpu,lower)) 
          i=i+1
       if arg == "-U":
          upper=int(sys.argv[i+1])
          print("[%s] Upper is %d" % (cpu,upper)) 
          i=i+1
       if arg == "-S":
          total_slices=int(sys.argv[i+1])
          print("[%s] Total slices is %d" % (cpu,total_slices)) 
          i=i+1
       if arg == "-V":
          verbose=True
          print("[%s] Verbose is True" % (cpu)) 
       if arg == "-H":
          print("[%s] mpirun -np NUMBER_OF_PROCESSES --hostfile HOSTFILE python primes.py [-u UPPER] [-l LOWER] [-s TOTAL SLICES][-v]") 
          MPI.Finalize()
          sys.exit(0)
          break;
       i=i+1


#*--- Finalize initialization

start = time.process_time()
blocksize=(upper-lower+1)/total_slices

#--- Rank==0  This is the master node.

if rank == 0:

    slice = 0
    process = 1

    print ("[%s] Processing primer interval Lower(%d) Upper(%d) Slices(%d) Blocksize(%d)" % (cpu,lower,upper,total_slices,blocksize))

    #-- Send the first batch of processes to the nodes.
    while process < size and slice < total_slices:
        l=slice*blocksize
        u=(slice*blocksize)+blocksize
        comm.send(l,dest=process,tag=1)
        comm.send(u,dest=process,tag=2)
        print("[%s] Rank(%d) send lower(%d) upper(%d) to process(%d)" % (cpu,rank,l,u,process))
        slice += 1
        process += 1

    #-- Wait for the data to come back
    process=1
    received_processes = 0
    while received_processes < total_slices:
        data = comm.recv(source=MPI.ANY_SOURCE, tag=1)
        dataQueue =dataQueue + data
        if verbose == True:
           print ("[%s] Rank(%d) Received  data" % (cpu,rank))
           print ("[%s] Rank(%d) Data [%s]" % (cpu,rank,data))

        received_processes += 1

        if slice < total_slices:
            l=slice*blocksize
            u=(slice*blocksize)+blocksize
            comm.send(l,dest=process,tag=1)
            comm.send(u,dest=process,tag=2)
            print("[%s] Rank(%d) send lower(%d) upper(%d) to process(%d)" % (cpu,rank,l,u,process))
            slice += 1
            process+=1
            if process > size:
               process=1

    # Send the shutdown signal

    for process in range(1,size):
        comm.send(-1, dest=process, tag=1)

    print ("[%s] Finalizó busqueda primos lower(%d) upper(%s) tiempo=%.3f secs" % (cpu,lower,upper,time.process_time()-start))
    if verbose == True:
       print ("[%s] Data\n%s\n" % (cpu,dataQueue))


#--- These are the slave nodes, where rank > 0. They do the real work
else:
    while True:
        lower = comm.recv(source=0, tag=1)
        if lower == -1: break
        upper = comm.recv(source=0, tag=2)
        dataQueue=""
        if verbose==True:
           print("[%s] Rank(%d) Received unit Lower(%d) Upper(%d) " % (cpu,rank,lower,upper))

        for num in range(int(lower), int(upper)):
          if num > 1:

   # all prime numbers are greater than 1

             for i in range(2, num):
                 if (num % i) == 0:
                    break
             else:
                 dataQueue=dataQueue+"%d "%(num)
        comm.send(dataQueue, dest=0, tag=1)
        if verbose==True:
           print("[%s] Rank(%d) Returning lower(%d) upper(%d)" % (cpu,rank,lower,upper))
