
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DFUNCHOOK_DISASM=capstone -DFUNCHOOK_INSTALL=OFF ../.
make
cd ..
gcc -g -O0 -o funchooktest funchooktest.c -L./build -lfunchook
