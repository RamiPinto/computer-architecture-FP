#!/bin/bash
echo "Starting performance evaluation:"
echo $'\nAsteroids=250 - Planets=250 - threads=1'
COUNT=1
export OMP_NUM_THREADS=1
printenv | grep OMP_NUM_THREADS
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-par 250 100 250 50.5 2000
        let COUNT=COUNT+1
done

echo $'\nAsteroids=250 - Planets=250 - threads=2'
COUNT=1
export OMP_NUM_THREADS=2
printenv | grep OMP_NUM_THREADS
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-par 250 100 250 50.5 2000
        let COUNT=COUNT+1
done

echo $'\nAsteroids=250 - Planets=250 - threads=4'
COUNT=1
export OMP_NUM_THREADS=4
printenv | grep OMP_NUM_THREADS
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-par 250 100 250 50.5 2000
        let COUNT=COUNT+1
done

echo $'\nAsteroids=250 - Planets=250 - threads=8'
COUNT=1
export OMP_NUM_THREADS=8
printenv | grep OMP_NUM_THREADS
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-par 250 100 250 50.5 2000
        let COUNT=COUNT+1
done

echo $'\nAsteroids=250 - Planets=250 - threads=16'
COUNT=1
export OMP_NUM_THREADS=16
printenv | grep OMP_NUM_THREADS
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-par 250 100 250 50.5 2000
        let COUNT=COUNT+1
done
