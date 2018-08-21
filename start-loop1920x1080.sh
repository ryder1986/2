#FRI="-r 15"
FRI=-re
FRO=""
#FRO="-r 15"
SZ=1920x1080
while  [ 1 ] 
do 
   sleep 1
   ffmpeg      $FRI      -i  09_30_26.264   $FRO    -s   $SZ     -c:v  libx264   -f  flv  rtmp://localhost/live/$SZ
done 
