#!/bin/sh
#*------------------------------------------------------------------------------------------------
#* Universidad Aut  noma de Entre Rios
#* Facultad de Ciencia y Tecnolog  a
#* Ingenier  a de Telecomunicaciones
#*
#* Proyecto de investigaci  n
#* Procesamiento de se  ales mediante cluster
#* Microcluster LAN
#*
#* Script para ejecutar una comando desde el nodo base a todos los nodos trabajadores del cluster
#* Formato:
#*      MPI_collatz [-m MPI|SERIAL] [-n processes] [-f hostfile]  [-s Start] [-e End] [-b Blocksize] [-v]
#*
#*------------------------------------------------------------------------------------------------
#To run use: 
# mpirun (-np x) collatz n m z y 
#   (np flag is to use certain amout of process) 
#   ( [n;m] - interval int type, z - block size to which the interval will be divided
#   y is outputFlad if y = 0 no output only the time that the algorithm used, anything else will give every output)


#*---- Retrieve execution environment

CURR=$(pwd)
PWD=$(dirname $0)
export DISPLAY=:0.0

#*--- Execution environment

SCRIPT_PATH=$(dirname "$0")
if [ "$SCRIPT_PATH" = "." ]; then
   SCRIPT_PATH=$(pwd)
fi

SCRIPT_NAME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"
ME=$(echo $SCRIPT_NAME | cut -f 1 -d ".")


COLLATZ=$CLUSTERFS/"sdr/lib/collatz"
cd $COLLATZ

#*---------------------------------------------------------------------------------
#* Script is now standing on execution environment
#*---------------------------------------------------------------------------------
VERBOSE=0
START=1
END=100000
BLOCKSIZE=1000
NP=4
MODE="MPI"

while getopts 'n:f:m:s:e:b:vh' opt; do
  case "$opt" in
    m)
      MODE="$OPTARG"
      ;;

    s)
      START="$OPTARG"
      ;;

    e)
      END="$OPTARG"
      ;;
    n)
      NP="$OPTARG"
      ;;
    f)
      HOSTFILE="$OPTARG"
      ;;
    b)
      BLOCKSIZE="$OPTARG"
      ;;
  :)
      echo -e "option requires an argument, see -h for help"
      exit 1
      ;;
    v)
      VERBOSE=1
      ;;

    ?|h)
      echo "Usage: $($ME) [-m MPI|SERIAL] [-n nodes] [-f hostfile] [-s Start] [-e End] [-b Blocksize] [-v]"
      exit 1
      ;;
  esac
done

#*--------- Make the mode argument uppercase

shift "$(($OPTIND -1))"
MODE=$(echo "$MODE" | tr '[:lower:]' '[:upper:]')


#*-------- Identify the selected mode of running

if [ "$MODE" = "SERIAL" ]; then
    echo "[$ME] Selected mode is Serial at node $(hostname)"
else
    if [ "$MODE" = "MPI" ];  then
       echo "[$ME] Selected mode is MPI cluster"
    else
       echo "[$ME] Wrong execution mode, terminating!"
       exit 1
    fi
fi

#*------ Starting execution
clear
echo "[$ME] Executing collatz conjecture test using $MODE mode with parameters [$START,$END,$BLOCKSIZE]"

if [ "$MODE" = "SERIAL" ]; then
    $COLLATZ/collatz_serial $START $END $BLOCKSIZE $VERBOSE
else
    if [ "$MODE" = "MPI" ]; then 
       mpicc -o $COLLATZ/collatz $COLLATZ/collatz.c
       cat $HOSTFILE | grep -v "#" | cut -f 1 -d" " >tmpfile
       echo "Nodes:"
       cat tmpfile
       echo " "
       mpirun  --hostfile tmpfile -np $NP $COLLATZ/collatz $START $END $BLOCKSIZE $VERBOSE
       rm -r tmpfile
    else
       echo "[$ME] Wrong execution mode, terminating!"
       exit 1
    fi
fi







