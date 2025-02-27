#!/bin/sh
#*-------------------------------------------------------------------------
#* setTelemetry
#* Measure and put telemetry
#*-------------------------------------------------------------------------
#*-------------------------------------------------------------------------
#* getCPU
#* Get CPU load 
#*--------------- Requires apt-get install sysstat
#*-------------------------------------------------------------------------
getCPU () {

CPU=$(sar 1 3 | grep "Average:" | while read a ; do
 echo $a | awk '{print $3 + $4 + $5 + $6 + $7}';
done)
echo $CPU

}
#+-----------------------------------------------------------------------------
#* Get telemetry from all major sub-systems
#*-----------------------------------------------------------------------------
getTemp () {

TEMP=$(vcgencmd measure_temp)
echo $TEMP | cut -f2 -d"=" | cut -f1 -d"'"

}
#+-----------------------------------------------------------------------------
#* Get telemetry from all major sub-systems
#*-----------------------------------------------------------------------------
getVolt () {

VOLT=$(vcgencmd measure_volts | cut -f2 -d"=" | cut -f1 -d"V" )
VOLT=$(python -c "print ('%.2f' % ($VOLT*1.0))" )
echo $VOLT 

}
#+-----------------------------------------------------------------------------
#* Get telemetry from all major sub-systems
#*-----------------------------------------------------------------------------
getClock () {

CLOCK=$(vcgencmd measure_clock arm | cut -f2 -d"=")
FX=$(python -c "print(int($CLOCK/1000000))")
echo $FX

}
#+-----------------------------------------------------------------------------
#* Get telemetry from all major sub-systems
#*-----------------------------------------------------------------------------
getStatus () {

STATUS=$(vcgencmd get_throttled)
echo $STATUS | cut -f2 -d"="

}
#+-----------------------------------------------------------------------------
#* Get telemetry from all major sub-systems
#*-----------------------------------------------------------------------------
getDASD () {
FS=$(df | grep "/dev/mm" | grep -v "/boot/firmware" | cut -f1 -d" ")
sudo df -k | grep $FS | awk '{ print $5 ; }' | cut -f1 -d"%"
}
#+-----------------------------------------------------------------------------
#* Get link performance
#*-----------------------------------------------------------------------------
getLink () {

SPEEDTEST="/home/pi/speedtest-cli"
rm -r $SPEEDTEST/speedtest.tmp 2> /dev/null
python $SPEEDTEST/speedtest.py 2>&1  > $SPEEDTEST/speedtest.tmp 

DOWN=$(cat $SPEEDTEST/speedtest.tmp | grep "Download: " | cut -f2- -d" " )
HOST=$(cat $SPEEDTEST/speedtest.tmp | grep "Hosted " | cut -f2- -d":" )
echo "$DOWN-$HOST"
}


#*--------------------------------------------------------------------------
#* putTelemetry 
#* Gather telemetry and assemble an information frame with it, log at Syslog
#*--------------------------------------------------------------------------

echo "CPU($getCPU)"

sar 1 3 | grep "Average:" | while read a ; do
 echo $a | awk '{print $3 + $4 + $5 + $6 + $7}';
done

#STATE="T($(getTemp)°C) V($(getVolt)V) Clk($(getClock)MHz) St($(getStatus)) CPU($(getCPU)%) DASD($(getDASD)%) LINK($(getLink))" 
#echo $STATE | logger -i -t "TLM"
#echo $STATE 


