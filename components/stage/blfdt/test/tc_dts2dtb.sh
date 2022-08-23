#!/bin/sh

curent_dir=$(pwd)
cd $curent_dir
echo $curent_dir

echo "tc_wifi.  dts -> dtb"
dtc -I dts -O dtb -o tc_wifi.dtb tc_wifi.dts

echo "tc_wifi.  dtb -> c"
xxd -i tc_wifi.dtb tc_wifi.c
