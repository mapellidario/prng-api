#!/bin/bash

current=`pwd`
cd build
./bench-disk
cd $current
