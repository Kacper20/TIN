echo "Starting process (60 sec)."
x=1;
while [ $x -le 10000000 ]; do
x=$[x + 1]
done
echo "Finished after 60 sec."
