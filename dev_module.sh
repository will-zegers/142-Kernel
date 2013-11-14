#!/bin/bash

modName="hermes"

echo "[+] Making the \"$modName\" module"
make > /dev/null
wait
rmmod $modName 2> /dev/null
wait
insmod $modName.ko 
echo "[+] Module $modName.ko inserted to the kernel"
cat /proc/modules|grep hermes
mknod $modName c 100 0 2>/dev/null
echo "[+] Device $modName created"
