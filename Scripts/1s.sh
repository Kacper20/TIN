#!/bin/bash
echo "Starting process (1 sec)."
x=1;
while [ $x -le 200000 ]; do
x=$[x + 1]
done
echo "Finished after 1 sec."
