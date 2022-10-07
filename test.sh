#!/bin/bash

if [ -d "./test" ]
then
    cd ./test
    make clean
    make test
fi
