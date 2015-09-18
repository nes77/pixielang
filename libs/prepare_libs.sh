#!/usr/bin/env bash

echo "Building Boost..."

CURDIR = $(readlink -f ./)

cd ./boost/
./bootstrap.sh --prefix=$CURDIR
./b2 install
