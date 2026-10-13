#!/bin/bash

echo "[*] Init build directory"
mkdir -p ./build

echo "[*] Compiling with clang++"
clang++ -o ./build/SysRT main.cpp -I . -std=c++20 -luv -lv8

echo "[*] Creating Test Script"
printf "terminal.log('Hi');\nvar name = terminal.getinput('Whats your name');\nfile.write('name.txt', name);\nterminal.log(file.read('name.txt'));\n" > test.js

echo "[*] Running test"
./build/SysRT test.js

echo "[*] Done: Executable in ./build"
