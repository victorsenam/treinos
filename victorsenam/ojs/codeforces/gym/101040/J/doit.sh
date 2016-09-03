#!/bin/bash
while read -r line
do
    ./gen > inp
    ./brute < inp > sol
    ./J < inp > out
    diff sol out
done
