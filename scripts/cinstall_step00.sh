#!/bin/sh

#*---------------------------------------------------------------------------
#* Ensure the following variables are set on both
#* .bashrc for pi
#* /etc/profile
#*
#* CLUSTERFS="/clusterfs"
#* CLUSTERIP="10.0.0."
#* CLUSTERID="sdr-s0"
#*
#* Ensure the target node has the correct time already
#* 
#* sudo date -s "dd MMM yy HH:MM:SS"
#*
#* Ensure the credentials of the base node has been set
#* already into the target node
#*
#* ssh-copy-id pi@(target_host)
#*----------------------------------------------------------------------------

#* VVVVVVVVVVV---- Configurar aqui el nombre dele nodo 
if [ "$#" -eq 0 ]; then
  echo "No arguments provided. Destination node needed"
else
  echo "The number of arguments is: $# ($1)"
fi

NODE=$1 


#*---- Comienza la ejecuci√≥n

SCRIPT=$CLUSTERFS"/sdr/scripts"
cd $SCRIPT
#*----  Copy latest version of critical files

$SCRIPT/ccp.sh -n $NODE '/home/pi/.bashrc' "/home/pi/.bashrc"

$SCRIPT/ccp.sh -n $NODE '/etc/hosts' "/home/pi/hosts"
$SCRIPT/cexec.sh -n $NODE "sudo mv /home/pi/hosts /etc/hosts && rm -r /home/pi/hosts" 

$SCRIPT/ccp.sh -n $NODE '/etc/profile' "/home/pi/profile"
$SCRIPT/cexec.sh -n $NODE "sudo mv /home/pi/profile /etc/profile  && rm -r /home/pi/profile" 

$SCRIPT/ccp.sh -n $NODE '/etc/resolv.conf' "/home/pi/resolv.conf"
$SCRIPT/cexec.sh -n $NODE "sudo mv /home/pi/resolv.conf /etc/resolv.conf && rm -r /home/pi/resolv.conf" 

$SCRIPT/cexec.sh -n $NODE "ping -c1 www.hotmail.com"

#*---- Install NTP service
$SCRIPT/cexec.sh -n $NODE "sudo apt-get update && sudo apt-get install ntp ntpdate sysstat stress -y"

#*---- Install other packages needed
#$SCRIPT/cexec.sh -n $NODE "sudo apt-get install nfs-common -y"
#$SCRIPT/cexec.sh -n $NODE "sudo mkdir /clusterfs"
#$SCRIPT/cexec.sh -n $NODE "sudo chmod -R 777 /clusterfs"


#*---- Install speedtest
$SCRIPTS/cexec.sh -n $NODE  "cd /home/pi && git clone https://github.com/sivel/speedtest-cli.git && cd speedtest-cli && sudo python setup.py install"
echo "**********************************"
echo "*          ATENCION              *"
echo "**********************************"
echo " "
echo "Realizar manualmente las siguientes sentencias haciendo ssh pi@$NODE"
echo "sudo nano /etc/fstab   (agregar al final la siguiente linea)"
echo "      <master node ip\>:/clusterfs    /clusterfs    nfs    defaults   0 0"
echo "luego "
echo " "
echo "sudo systemctl daemon-reload"
echo "sudo mount -a"
echo " "
echo "Hacer cd /clusterfs y verificar que este© el contenido existente en el"
echo "mismo directorio del nodo base, luego dar"
echo " "
echo "sudo reboot"
