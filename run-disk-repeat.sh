#!/bin/bash

current=`pwd`
cd install/bin
./bench-disk-repeat
cd $current
