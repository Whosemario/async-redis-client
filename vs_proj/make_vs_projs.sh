#!/bin/sh

#mkdir vs2015/x64 -p

#rm vs2015/x64/* -rf
cd vs2015/x64
cmake ../../.. -G"Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug -DPYTHON_ROOT="C:\\Python27"
cd ../..

