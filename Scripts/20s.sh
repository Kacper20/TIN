echo "Starting process (20 sec)."
x=1;
while [ $x -le 4000000 ]; do
x=$[x + 1]
done
echo "Finished."
