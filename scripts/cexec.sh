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
#* Script para ejecutar una comando desde el nodo base a todos los nodos trabajadores del cluster
#* Formato:
#*          ./cexec.sh [comando a ejecutar] 
#*
#*          (en caso de mas de un comando separarlo con && )
#*------------------------------------------------------------------------------------------------
echo " "
echo " "

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

ARGS=$#
NODE=$(cat $HOSTS | grep $SELECT | grep $INCLUDE | grep -v $EXCLUDE | awk '{ print $2 ; }' | cut -f1 -d'%')
CMD=$1

case $1 in
    -n|-N)
      NODE="$2"
      CMD="$3"
      ;;
esac

for i in $(cat $HOSTFILE | grep -v "#" | cut -f 1 -d" ")
 do

    IP=$(getent hosts $i | cut -f1 -d " ")
    P=$(ping $i -c 1 | grep 'time=' | grep -v 'No route to host' | wc -l)
    if [ $P -ge 1 ]
    then
       RCALL="ssh pi@$i $CMD"
       RESULT=$($RCALL)
       echo "nodo($i) ip[$IP]: Ok result[$RESULT]]"
    else
       echo "nodo($i) ip[$IP]: no disponible"
    fi
done
