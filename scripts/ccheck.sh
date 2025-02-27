#!/bin/sh
#*------------------------------------------------------------------------------------------------
#* Universidad Autónoma de Entre Rios
#* Facultad de Ciencia y Tecnología
#* Ingeniería de Telecomunicaciones
#*
#* Proyecto de investigación
#* Procesamiento de señales mediante cluster
#* Microcluster LAN
#*
#* Script para ejecutar una comando ping desde el nodo base a todos los nodos trabajadores del cluster
#* Formato:
#*          ./cping.sh  [-n nodo]
#*
#
#*------------------------------------------------------------------------------------------------
clear

CURR=$(pwd)
PWD=$(dirname $0)

export DISPLAY=:0.0

SELECT=$CLUSTERID
INCLUDE=$CLUSTERIP
EXCLUDE=$CLUSTERID"0"

#*--- Execution environment

SCRIPT_PATH=$(dirname "$0")
if [ "$SCRIPT_PATH" = "." ]; then
   SCRIPT_PATH=$(pwd)
fi

SCRIPT_NAME="$(basename "$(test -L "$0" && readlink "$0" || echo "$0")")"
ME=$(echo $SCRIPT_NAME | cut -f 1 -d ".")
HOSTS="/etc/hosts"
HOSTFILE="$SCRIPTS/../etc/hostfile.s"

case $1 in
    -n|-N)
      NODE="$2"
      CMD="$3"
      ;;
esac

echo "Cluster health checking script"

for i in $(cat ../etc/hostfile.s | awk '{print $1 }' | grep -v "#")
 do
    IP=$(getent hosts $i | cut -f1 -d " ")
    P=$(ping $i -c 1 | grep 'time=' | grep -v 'No route to host' | wc -l)
    if [ $P -ge 1 ]
    then
      echo "nodo($i) ip[$IP]: ttl=$(ping -c 1 sdr-s01 | grep "time=" | cut -f 4 -d"=")"
    else
      echo "nodo($i) ip[$IP]: no disponible"
    fi
done
