#!/bin/sh
#*------------------------------------------------------------------------------------------------
#  Universidad Aut  noma de Entre Rios
#  Facultad de Ciencia y Tecnolog  a
#  Ingenier  a de Telecomunicaciones
#  Proyecto de investigaci  n
#  Procesamiento de se  ales mediante cluster
#  Microcluster LAN
#  Script para correr benchmark de calculo de numeros primos
#*------------------------------------------------------------------------------------------------

LOWER=1
UPPER=1000
SLICE=15
cat $HOSTFILE | grep -v "#" | cut -f 1 -d" ">tmpfile
echo "Nodes:"
cat tmpfile
mpirun --oversubscribe --hostfile tmpfile python primes.py -l $LOWER -u $UPPER -s $SLICE 
rm -r tmpfile
