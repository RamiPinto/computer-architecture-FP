#!/bin/bash
echo "Starting performance evaluation:"
echo "Asteroids=250 - Planets=250 - iterations = 50"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 250 50 250 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=250 - Planets=250 - iterations = 100"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 250 100 250 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=250 - Planets=250 - iterations = 200"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 250 200 250 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=500 - Planets=500 - iterations = 50"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 500 50 500 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=500 - Planets=500 - iterations = 100"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 500 100 500 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=500 - Planets=500 - iterations = 200"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 500 200 500 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=1000 - Planets=1000 - iterations = 50"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 1000 50 1000 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=1000 - Planets=1000 - iterations = 100"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 1000 100 1000 50.5 2000
        let COUNT=COUNT+1
done

echo "Asteroids=1000 - Planets=1000 - iterations = 200"
COUNT=1
until [ $COUNT -gt 10 ]; do
        echo "Iteration" $COUNT
        /usr/bin/time ./nasteroids-seq 1000 200 1000 50.5 2000
        let COUNT=COUNT+1
done
