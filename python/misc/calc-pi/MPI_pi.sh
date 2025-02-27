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
#*      MPI_pi [-m MPI|SERIAL] [-n processes] [-f hostfile]  [-p particiones]
#*
#*------------------------------------------------------------------------------------------------

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


PI="/clusterfs/calc-pi"
cd $PI

#*---------------------------------------------------------------------------------
#* Script is now standing on execution environment
#*---------------------------------------------------------------------------------
NP=2
MODE="MPI"
HOSTFILE=$PI/"hostfile"
PARTITION=10

while getopts 'n:f:m:p:' opt; do
  case "$opt" in
    m)
      MODE="$OPTARG"
      ;;

    p)
      PARTITION="$OPTARG"
      ;;

    n)
      NP="$OPTARG"
      ;;   
    f)
      HOSTFILE="$OPTARG"
      ;;   
  :)
      echo -e "option requires an argument, see -h for help"
      exit 1
      ;;

    ?|h)
      echo "Usage: $($ME) [-m MPI|SERIAL] [-n nodes] [-f hostfile] [-p Partitions]"
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
echo "[$ME] Executing pi computation test using $MODE mode with parameters [$PARTITION]"

if [ "$MODE" = "SERIAL" ]; then
    python $PI/calculate-pi-serial.py $PARTITION
else
    if [ "$MODE" = "MPI" ]; then 
       mpirun  --hostfile $HOSTFILE -np $NP python $PI/calculate-pi.py $PARTITION
    else
       echo "[$ME] Wrong execution mode, terminating!"
       exit 1
    fi
fi







