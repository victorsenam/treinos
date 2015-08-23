#!/bin/bash
for i in $(seq 157)
do
    echo $i;
    ./C < inout/C_"$i".in > outs/C_"$i".out;
    diff outs/C_"$i".out inout/C_"$i".sol;
done
