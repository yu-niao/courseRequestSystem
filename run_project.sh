#!/bin/bash

# 如果build文件夹存在，则删除
if [ -d "build" ]; then
    rm -rf build
fi

if [ -d "bin" ]; then
    rm -rf bin
fi

mkdir build

cd build

cmake ..

make 