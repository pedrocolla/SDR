"""
/*------------------------------------------------------------------------------------------------
  Universidad Autónoma de Entre Rios
  Facultad de Ciencia y Tecnología
  Ingeniería de Telecomunicaciones

  Proyecto de investigación
  Procesamiento de señales mediante cluster
  Microcluster LAN
  Programa de prueba para comparar performance del cluster
  Python program to display all the prime numbers within an interval


""" 

import sys
import socket
import time

lower = 1
upper = 100000
cpu=socket.gethostname()
verbose = False

n = len(sys.argv) 
print("Arguments passed:", end = " ")
i=0
while i<n and n>1:
  arg=sys.argv[i]
  arg=arg.upper()
  if arg == "-L":
     lower=int(sys.argv[i+1])
     print("[%s] lower %d" % (cpu,lower)) 
     i=i+1
  if arg == "-U":
     upper=int(sys.argv[i+1])
     print("[%s] upper %d" % (cpu,upper)) 
     i=i+1
  if arg == "-V":
     verbose=True
     print("[%s] Verbose set" % (cpu)) 
     i=i+1
  i=i+1

print("[%s] Computing Prime numbers between lower(%d) and upper(%d)\n" % (cpu,lower,upper))
start=time.process_time()
slices=10
blocksize=(upper-lower+1)/slices
m=0
s1=time.process_time()
dataQueue=""
for num in range(lower, upper + 1):
   if num%blocksize == 0:
      e1=time.process_time()
      print("Processing %d thru %d range....lap %.3f secs total %.3f secs" % (num,num+blocksize,(e1-s1),(e1-start))) 
      s1=e1
   # all prime numbers are greater than 1
   if num > 1:
       for i in range(2, num):
           if (num % i) == 0:
               break
       else:
           dataQueue=dataQueue+("%d " % (num))
           if verbose == True:
              print("%d" % (num), end =" ")
           m=m+1


print("\n[%s] Finalizó búsqueda primos lower(%d) upper(%d) time=%.3f secs detectados(%d)" % (cpu,lower,upper,time.process_time()-start,m))
if verbose==True:
   print("\n[%s] Dataset \n%s\n" % (cpu,dataQueue))
