#!/bin/sh
#*------------------------------------------------------------------------------------------------
#* Universidad Autónoma de Entre Rios
#* Facultad de Ciencia y Tecnología
#* Ingeniería de Telecomunicaciones
#*
#* Proyecto de investigación
#* Procesamiento de señales mediante cluster
#* Microcluster LAN
#*------------------------------------------------------------------------------------------------
HOST=$(hostname)
TIME=$(date)
STATUS=$(/clusterfs/sdr/scripts/setTelemetry.sh)
cd /home/pi/Descargas
echo " " >> /home/pi/$HOST.log
echo "$HOST $TIME $STATUS" >> /home/pi/$HOST.log
sudo cat  /home/pi/$HOST.log  >> /var/log/$HOST.log
echo "[$HOST] $STATUS"
rm -r /home/pi/$HOST.log
