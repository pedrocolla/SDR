from mpi4py import MPI

if __name__ == "__main__":

    world_comm = MPI.COMM_WORLD
    world_size = world_comm.Get_size()
    my_rank = world_comm.Get_rank()
    cpuname = MPI.Get_processor_name();

    print("cpu(%s) World Size: %s Rank %s" % (cpuname,str(world_size),str(my_rank)))
