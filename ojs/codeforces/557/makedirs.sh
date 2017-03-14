#!/bin/bash
for var in "$@"
do
    mkdir "$var"
    cp temp.cpp "$var"/"$var".cpp
done
