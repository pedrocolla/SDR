#!/bin/bash

NODES=("sdr-s00" "sdr-s01" "sdr-s02" "sdr-s03" "sdr-s04")

for NODE in "${NODES[@]}"; do
  echo "========== Nodo: $NODE =========="

  if [ "$NODE" == "sdr-s00" ]; then
    bash /srv/clusterfs/sdr/scripts/nodeTelemetry.sh
  else
    REMOTE_PATH="/clusterfs/sdr/scripts/nodeTelemetry.sh"
    ssh pi@$NODE "bash $REMOTE_PATH"
  fi

  echo ""
done

