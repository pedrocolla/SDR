##*------------------------------------------------------------------------------------------------
##  Universidad Autónoma de Entre Rios
##  Facultad de Ciencia y Tecnología
##  Ingeniería de Telecomunicaciones
##
##  Proyecto de investigación
##  Procesamiento de señales mediante cluster
##  Microcluster LAN
##  Programa de prueba para comparar performance del cluster
##    Evaluación de Pi con distintas precisiones ambiente OpenMPI
##
##*--------------------------------------------------------------------------------------------------
import time
from mpi4py import MPI
from math   import pi as PI
from numpy  import array
import sys

def comp_pi(n, myrank=0, nprocs=1):
    h = 1.0 / n
    s = 0.0
    for i in range(myrank + 1, n + 1, nprocs):
        x = h * (i - 0.5)
        s += 4.0 / (1.0 + x**2)
    return s * h

def prn_pi(pi, PI, t):

    message = "pi is approximately %.16f, error is %.16f time(%.6f)"
    print  (message % (pi, abs(pi - PI), t))

numint=20
if len(sys.argv) > 0:
	numint= int(sys.argv[1])
comm = MPI.COMM_WORLD
nprocs = comm.Get_size()
myrank = comm.Get_rank()

n    = array(0, dtype=int)
pi   = array(0, dtype=float)
mypi = array(0, dtype=float)

if myrank == 0:
    _n = numint # Here is the number of intervals
    n.fill(_n)
    start = time.time()

comm.Bcast([n, MPI.INT], root=0)
_mypi = comp_pi(n, myrank, nprocs)
mypi.fill(_mypi)
comm.Reduce([mypi, MPI.DOUBLE], [pi, MPI.DOUBLE],op=MPI.SUM, root=0)
if myrank == 0:
    prn_pi(pi, PI,(time.time()-start))

