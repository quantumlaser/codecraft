#!/bin/bash
#cd /home/wuzhaohui/Workspace/code2016/codecraft/SDK-gcc-1.0
rm -fr bin
mkdir bin
rm -fr build
mkdir build
cd build
cmake ../future_net
make
cd ..
rm -fr temp
mkdir temp
./bin/future_net ../test-case/case0/topo.csv ../test-case/case0/demand.csv temp/result0.csv
echo
echo "The result0 is： "
cat temp/result0.csv
