
from mpi4py import MPI
import sys
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
cpuname = MPI.Get_processor_name();
msent=0
mrecv=0
if rank == 0:
   msg = "Hello world"
   while True:
       print("cpu(%s) Sending message <%s> order %d" % (cpuname,msg,msent))
       sdata=("Hello world-%d" % msent)
       comm.send(sdata, dest=1) 
       msent=msent+1
       if msent > 10:
          break
   msg="eof"
   comm.send(msg, dest=1) 
   print("eof sent")
   while msent>0: 
       r = comm.recv(source=MPI.ANY_SOURCE, tag=MPI.ANY_TAG)
       msent=msent-1
       print("cpu(%s) Receiving queued message <%s> msent=%d" % (cpuname,r,msent))
   print("Terminating master")
   #sys.exit(0)
elif rank >= 1:
   while True:
       s = comm.recv()
       mback="Ok %d" % (mrecv)
       comm.send(mback,dest=0)
       print ("cpu(%s) rank %d: %s answering %s recv(%d)" % (cpuname,rank, s,mback,mrecv))
       mrecv=mrecv+1

       if s == "eof":
          print("Received eof. Terminating worker")
          break
          #sys.exit(0)
print("Toffoli paso por aqui")
