echo "Starting process (30 sec)."
x=1;
while [ $x -le 6000000 ]; do
x=$[x + 1]
done
echo "Finished."
