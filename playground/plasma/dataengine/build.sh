#!/bin/bash
cmake . -DCMAKE_INSTALL_PREFIX=$KDEDIR -DCMAKE_BUILD_TYPE=debugfull
make
make install
