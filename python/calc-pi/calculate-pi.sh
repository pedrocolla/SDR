#!/bin/sh
#*------------------------------------------------------------------------------------------------
#  Universidad Aut  noma de Entre Rios
#  Facultad de Ciencia y Tecnolog  a
#  Ingenier  a de Telecomunicaciones
#  Proyecto de investigaci  n
#  Procesamiento de se  ales mediante cluster
#  Microcluster LAN
#  Script para correr benchmark de calculo de pi
#*------------------------------------------------------------------------------------------------
SIZE=1000000
TOTAL=14

cat $HOSTFILE | grep -v "#" | cut -f 1 -d" " > tmpfile
echo "Nodes:"
cat tmpfile
echo " "
mpirun --oversubscribe --hostfile tmpfile python calculate-pi.py $SIZE 
rm -r tmpfile

