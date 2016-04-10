rd /s/q bin
mkdir bin
rd /s/q build
mkdir build
cd build
: cmake -G "MinGW Makefiles" ..\future_net
cmake -G "MinGW Makefiles" ..\future_net
mingw32-make
cd ..
del temp\result0.csv
bin\future_net.exe ..\test-case\case0\topo.csv ..\test-case\case0\demand.csv temp\result0.csv
echo off
echo The result0 is:
type temp\result0.csv
