#! /bin/bash


#arguments pass to this bash script
#Use: on terminal type (for example) >> jcacheGet.sh shms 1791
spec=$1 
runNUM=$2


mss="/mss/hallc/spring17/raw/${spec}_all_0${runNUM}.dat"
#lustre="/lustre/expphy/cache/hallc/spring17/raw"

echo $mss

jcacheCMD="jcache get ${mss} -e cyero002@fiu.edu -x"

echo "Executing command: ${jcacheCMD}" 
eval ${jcacheCMD}    

  
