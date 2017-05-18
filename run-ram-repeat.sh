#!/bin/bash

current=`pwd`
cd build
./bench-ram-repeat
cd $current
