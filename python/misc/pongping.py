
from mpi4py import MPI
import sys

comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
cpuname = MPI.Get_processor_name();
msent=0
mrecv=0
i=1
if rank == 0:
   msg = "Hello, world"
   while True:
      if msent<size-1:
          msent=msent+1
          comm.send(msg, dest=msent) 
          print("cpu(%s) Sending message <%s> to rank %d" % (cpuname,msg,msent))
      if comm.Iprobe():
          rdata = comm.recv()
          print("cpu(%s) Receiving non blocking message <%s> mrecv(%d)" % (cpuname,rdata,mrecv))
          mrecv=mrecv+1
      if mrecv == msent:
          print("cpu(%s) Terminating" % (cpuname))
          sys.exit(0)
elif rank >= 1:
   s = comm.recv()
   mback="Ok %d" % (rank)
   comm.send(mback,dest=0)
   print ("cpu(%s) rank %d: %s answering %s" % (cpuname,rank, s,mback))
