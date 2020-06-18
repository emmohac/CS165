#!/bin/bash

echo "size,time" > asp_$1.csv

for ((i=10;i<=20;i++))
do
    echo $((2**i))
    ./phase2 "$1" $((2**i)) asp >> asp_$1.csv
done