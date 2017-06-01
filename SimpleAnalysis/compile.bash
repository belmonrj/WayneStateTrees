#!/bin/bash



echo "now compiling"
echo "note that warnings are disabled"
#g++ -o analyze tree.cxx analyze.cxx -Wall -lstdc++ `root-config --libs` -I$ROOTSYS/include
g++ -o analyze tree.cxx analyze.cxx -lstdc++ `root-config --libs` -I$ROOTSYS/include




