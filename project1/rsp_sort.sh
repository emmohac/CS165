#!/bin/bash

echo "size,time" > rsp_$1.csv

for ((i=10;i<=18;i++))
do
    echo $((2**i))
    ./phase2 "$1" $((2**i)) rsp >> rsp_$1.csv
done