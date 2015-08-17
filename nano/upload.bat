@ECHO OFF
CLS

avrdude.exe -F -v -Cavrdude.conf -patmega328 -PCOM4 -carduino -b57600 -D -Uflash:w:nano.hex:i

PAUSE
