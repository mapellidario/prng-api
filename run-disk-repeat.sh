#!/bin/bash

current=`pwd`
cd build
./bench-disk-repeat
cd $current
