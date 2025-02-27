#!/bin/sh
#*------------------------------------------------------------------------------------------------
#  Universidad Aut  noma de Entre Rios
#  Facultad de Ciencia y Tecnolog  a
#  Ingenier  a de Telecomunicaciones
#  Proyecto de investigaci  n
#  Procesamiento de se  ales mediante cluster
#  Microcluster LAN
#  Script para verificar los nodos utilizados por el cluster
#*------------------------------------------------------------------------------------------------

cat $HOSTFILE | grep -v "#" | cut -f 1 -d" " > tmpfile
echo "Nodes:"
cat tmpfile
mpirun --hostfile tmpfile --oversubscribe python /clusterfs/sdr/python/mpi4/mpi4.py
rm -r tmpfile
