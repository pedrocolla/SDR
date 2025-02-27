#!/bin/sh

DIR1=/clusterfs/sdr/lib/scripts_gnuradio_mpi
DIR2=/clusterfs/sdr/Coeficientes_Filtros
DIR3=/clusterfs/sdr/gnuradio

cd /clusterfs/sdr

tar -cvf GNURadio_bup.tar $DIR1 $DIR2 $DIR3 . 
