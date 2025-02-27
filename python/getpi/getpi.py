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

  This code computes pi. It's not the first python
  pi computation tool that I've written.  This program
  is a good test of the mpi4py library, which is
  essentially a python wrapper to the C MPI library.

  To execute this code:

  mpirun -np NUMBER_OF_PROCESSES --hostfile HOSTFILE python getpi.py [-s SLICE_SIZE] [-t TOTAL_SLICE] [-v] 

where....

  NUMBER_OF_PROCESSES is the number of desired processes.
  HOSTFILE is a file which records the location of your nodes.

""" 
from mpi4py import MPI
import time
import argparse
import sys
import math

#*--- Initial connection with the MPI environment

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
cpu = MPI.Get_processor_name()
verbose=False
abort=False
#*--- Segment the workload

slice_size = 1000000
total_slices = 10

#--- Arguments passed
if rank == 0:
   print("Name of Python script: %s" % (sys.argv[0]))
   n = len(sys.argv) 
   print("Arguments passed:", end = " ")
   i=0
   while i<n and n>1:
       arg=sys.argv[i]
       arg=arg.upper()
       if arg == "-S":
          slice_size=int(sys.argv[i+1])
          print("[%s] Slice is %d" % (cpu,slice_size)) 
          i=i+1
       if arg == "-T":
          total_slices=int(sys.argv[i+1])
          print("[%s] Total slices %d" % (cpu,total_slices)) 
          i=i+1
       if arg == "-V":
          verbose=True
          print("[%s] Verbose is True" % (cpu)) 
       if arg == "-H":
          print("[%s] mpirun -np NUMBER_OF_PROCESSES --hostfile HOSTFILE python getpi.py [-s SLICE_SIZE] [-t TOTAL_SLICE] [-v]") 
          MPI.Finalize()
          sys.exit(0)
          break;
       i=i+1

#*--- Finalize initialization

start = time.process_time()


#--- Rank==0  This is the master node.

if rank == 0:
    pi = 0
    slice = 0
    process = 1

    print ("[%s] Size of the work unit is %d slice size (%d) total slices (%d)  work unit size (%d)" % (cpu,slice_size*total_slices,slice_size,total_slices,size))

    #-- Send the first batch of processes to the nodes.
    while process < size and slice < total_slices:
        comm.send(slice, dest=process, tag=1)
        if verbose == True:
           print ("[%s] Sending slice (%d) to process(%d)" % (cpu,slice,process))
        slice += 1
        process += 1

    #-- Wait for the data to come back
    received_processes = 0
    while received_processes < total_slices:
        pi += comm.recv(source=MPI.ANY_SOURCE, tag=1)
        process = comm.recv(source=MPI.ANY_SOURCE, tag=2)
        if verbose==True:
           print ("[%s] Received  data from process (%d)" % (cpu,process))
        received_processes += 1

        if slice < total_slices:
            comm.send(slice, dest=process, tag=1)
            if verbose == True:
               print ("[%s] Sending slice (%d) to process (%d)" % (cpu,slice,process))
            slice += 1

    # Send the shutdown signal
    for process in range(1,size):
        comm.send(-1, dest=process, tag=1)
    pi=4.0*pi
    error = abs(pi - math.pi)
    print ("[%s] El resultado de Pi=%.16f  error=%.16f t=%.3f secs" % (cpu,pi,error,time.process_time()-start))

#--- These are the slave nodes, where rank > 0. They do the real work
else:
    while True:
        start = comm.recv(source=0, tag=1)
        if start == -1: break
        print("[%s] Rank(%d) Received work unit start(%d)" % (cpu,rank,start))
        i = 0
        slice_value = 0
        while i < slice_size:
            if i%2 == 0:
                slice_value += 1.0 / (2*(start*slice_size+i)+1)
            else:
                slice_value -= 1.0 / (2*(start*slice_size+i)+1)
            i += 1

        comm.send(slice_value, dest=0, tag=1)
        comm.send(rank, dest=0, tag=2)
