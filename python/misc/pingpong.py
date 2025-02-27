
from mpi4py import MPI
comm = MPI.COMM_WORLD
size = comm.Get_size()
rank = comm.Get_rank()
cpuname = MPI.Get_processor_name();
msent=0
if rank == 0:
   msg = "Hello, world"
   for i in range(1, size, 1):
       print("cpu(%s) Sending message <%s> to rank %d" % (cpuname,msg,i))
       comm.send(msg, dest=i) 
       msent=msent+1
       if comm.Iprobe():
          rdata = comm.recv()
          print("cpu(%s) Receiving non blocking message <%s>" % (cpuname,rdata))
          msent=msent-1
   while msent>0: 
       #r = comm.recv()
       r = comm.recv(source=MPI.ANY_SOURCE, tag=MPI.ANY_TAG)
       print("cpu(%s) Receiving queued message <%s>" % (cpuname,r))
       msent=msent-1
elif rank >= 1:
   s = comm.recv()
   mback="Ok %d" % (rank)
   comm.send(mback,dest=0)
   print ("cpu(%s) rank %d: %s answering %s" % (cpuname,rank, s,mback))
