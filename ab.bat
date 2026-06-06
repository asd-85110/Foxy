@echo off
cmake -B build -S . -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -G Ninja -DCMAKE_BUILD_TYPE=%1 && cd build && ninja -j4 && ninja install && ninja clean