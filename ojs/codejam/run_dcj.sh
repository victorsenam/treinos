#!/bin/bash

DIRECTORY=$( cd "$( dirname $0 )" && pwd )
PYTHON="/usr/bin/python2.7"

NODES=${2:-'100'}

$PYTHON $DIRECTORY/dcj/dcj.py test --source=$1 --nodes=$NODES --output=all
