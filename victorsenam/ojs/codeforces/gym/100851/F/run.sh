#!/bin/bash/

cp tests/$1 ./froggy.in
./F
cat froggy.out
echo '---'
cat tests/$1.a
