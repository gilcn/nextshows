#!/bin/bash

[ ! -d Build ] && mkdir Build
cd Build

cmake .. -DCMAKE_INSTALL_PREFIX=$KDEDIR -DCMAKE_BUILD_TYPE=debugfull
make
make install
