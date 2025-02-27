#!/bin/sh
#*------------------------------------------------------------------------------------------------
#* Universidad Autónoma de Entre Rios
#* Facultad de Ciencia y Tecnología
#* Ingeniería de Telecomunicaciones
#*
#* Proyecto de investigación
#* Procesamiento de señales mediante cluster
#*         Ejecuta una sesión de stress de 900 segundos para verificar la estabilidad del nodo
#*------------------------------------------------------------------------------------------------

TIMEOUT="900s"
SLEEP="10"
CLUSTER=$CLUSTERFS"/sdr/scripts"

clear
while true; 
do 
$CLUSTER/setTelemetry.sh
sleep $SLEEP;
done &

stress -c 4 -t $TIMEOUT
