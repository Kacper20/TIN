#!/bin/bash
echo "Starting process (10 sec)."
x=1;
while [ $x -le 2000000 ]; do
x=$[x + 1]
done
echo "Finished."
