
"""
  Universidad Autónoma de Entre Rios
  Facultad de Ciencia y Tecnología
  Ingeniería de Telecomunicaciones

  Proyecto de investigación
  Procesamiento de señales mediante cluster
  Microcluster LAN
  Programa de prueba para comparar performance del cluster

  This code computes pi. It's not the first python
  pi computation tool that I've written.  This program
  is a good test of the mpi4py library, which is
  essentially a python wrapper to the C MPI library.

  To execute this code: 

      python getpi_classic.py
""" 

import math
import socket
import time

cpu=socket.gethostname()

#*--- Recursive algorithm to compute pi

def compute_pi(n):
 start=time.process_time()
 s1=start
 h = 1.0 / n
 s = 0.0
 for i in range(n):
   x = h * (i + 0.5)
   s += 4.0 / (1.0 + x**2)
   if (i%500000 == 0):
      e1=time.process_time()
      print("[%s] Processing %d iterations lap %.2f secs total %.2f" % (socket.gethostname(),i,(e1-s1),(e1-start)))
      s1=e1
 return s * h


#*---- Run parameters

n = 10000000
start = time.process_time()

#*---- Compute value

pi = compute_pi(n)

#*---- Present results
error = abs(pi - math.pi)
print ("[%s] El resultado de Pi=%.16f  error=%.16f t=%.3f secs" % (cpu,pi, error,time.process_time()-start))
