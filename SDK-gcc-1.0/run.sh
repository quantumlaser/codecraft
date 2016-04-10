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
rm temp/result0.csv
./bin/future_net test-case/case0/topo.csv test-case/case0/demand.csv temp/result0.csv
echo
echo "The result0 is： "
cat temp/result0.csv

rm temp/result1.csv
./bin/future_net test-case/case1/topo.csv test-case/case1/demand.csv temp/result1.csv
echo
echo "The result1 is： "
cat temp/result1.csv

rm temp/result2.csv
./bin/future_net test-case/case2/topo.csv test-case/case2/demand.csv temp/result2.csv
echo
echo "The result2 is： "
cat temp/result2.csv
