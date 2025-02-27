#!/bin/sh

if [ "$#" -eq 0 ]; then
  echo "No arguments provided. Destination node needed"
else
  echo "The number of arguments is: $# ($1)"
fi

NODE=$1

SCRIPT=$CLUSTERFS/"sdr/scripts"
PYTHON=$CLUSTERFS/"sdr/python"
#*---- Continuar con instalación del cluster utilizando recursos en /clusterfs
#*---- Instalar OpenMPI y ambientes relacionados

#*---- Instalar OpenMPI y recursos de desarrollo

cd $SCRIPT
$SCRIPT/cexec.sh -n $NODE "sudo apt-get install gcc make git gdb  -y "
$SCRIPT/cexec.sh -n $NODE "sudo apt-get update && sudo apt-get install openmpi-bin openmpi-common libopenmpi3 -y"
$SCRIPT/cexec.sh -n $NODE "sudo apt-get install mpi-default-dev   -y "

#*--- Instalar ambiente mpi4py
$SCRIPT/cexec.sh -n $NODE "sudo apt-get install python3-mpi4py -y"

#*--- Copiar recursos de soporte mpi4py
cd $PYTHON
git clone https://github.com/akkornel/mpi4py.git

#*---
echo "***************************************"
echo "*            ATENCION                 *"
echo "***************************************"
echo " "
echo "Verificar y configurar el nodo"

