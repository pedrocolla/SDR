#!/bin/bash
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
/clusterfs/usr/bin/pip install numpy mpi4py
