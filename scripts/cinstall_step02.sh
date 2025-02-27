#!/bin/sh

CLUSTERFS="/clusterfs"
SCRIPT=$CLUSTERFS"/sdr/scripts"
PYTHON=$CLUSTERFS"/sdr/python"
if [ "$#" -eq 0 ]; then
  echo "No arguments provided. Destination node needed"
else
  echo "The number of arguments is: $# ($1)"
fi

NODE=$1 

#*---- Continuar con instalación del cluster utilizando recursos en /clusterfs
#*---- Instalar OpenMPI y ambientes relacionados

#*---- Instalar OpenMPI y recursos de desarrollo

cd $SCRIPT
$SCRIPT/cexec.sh -n $NODE "sudo apt-get update && sudo apt-get install gnuradio xterm -y "
$SCRIPT/cexec.sh -n $NODE "sudo apt-get install gnuradio-dev cmake libspdlog-dev clang-format cmake -y "
$SCRIPT/cexec.sh -n $NODE "sudo apt-get install gnuradio-dev cmake libspdlog-dev clang-format -y "
#*---

sudo mkdir /run/user/1000
sudo chmod 0700 /run/user/1000
echo "***************************************"
echo "*            ATENCION                 *"
echo "***************************************"
echo " "
echo "Verificar y configurar bibliotecas custom (OOT) del nodo manualmente"
echo " "
echo " Para construir las bibliotecas custom gr-customModule"
echo " "
echo "  cd %CLUSTERFS/sdr/gnuradio"
echo "  cd gr-customModule"
echo "  sudo rm -r build"
echo "  mkdir build"
echo "  cd build"
echo "  cmake  .."
echo "  make"
echo "  sudo make install"
echo "  sudo ldconfig

