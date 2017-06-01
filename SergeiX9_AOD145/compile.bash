#!/bin/bash

if [ -e "TaskDataDictionary.cxx" ]
then
echo "TaskDataDictionary.cxx exists, skipping"
else
echo "TaskDataDictionary.cxx does not exist, making"
rootcint TaskDataDictionary.cxx -c TaskData.h TaskDataLinkDef.h
fi


echo "now compiling"

g++ -o sergei tree.cxx TaskData.cxx TaskDataDictionary.cxx sergei.cxx -Wall -lstdc++ `root-config --libs` -I$ROOTSYS/include




