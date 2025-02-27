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
#* Script para ejecutar una copia desde el nodo base a todos los nodos trabajadores del cluster
#* Formato:
#*          ./ccp.sh [nombre_archivo_en_base] [path/nombre_archivo_en_nodo]
#*
#*          (la copia debe realizarse en un path para el cual el usuario pi tenga permiso)
#*------------------------------------------------------------------------------------------------
clear
RR=$(pwd)
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

ARGS=$#

NODE=$(cat $HOSTS | grep "$SELECT" | grep "$INCLUDE" | grep -v "$EXCLUDE" | awk '{ print $2 ; }' | cut -f1 -d'%')

FROMF=$1
TOF=$2

case $1 in
    -n|-N)
      NODE="$2"
      FROMF="$3"
      TOF="$4"
      ;;
esac

for i in $(echo $NODE)
 do

    echo "Processing node($i)"
    IP=$(getent hosts $i | cut -f1 -d " ")
    P=$(ping $i -c 1 | grep 'time=' | grep -v 'No route to host' | wc -l)
    if [ $P -ge 1 ]
    then
       CMD="scp $FROMF pi@$i:$TOF"
       RESULT="$($CMD)"
       echo "nodo($i) ip[$IP]: Ok result($RESULT)" 
    else
       echo "nodo($i) ip[$IP]: no disponible"
    fi
done
