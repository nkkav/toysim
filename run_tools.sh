#!/bin/bash

# This should be adapted according to your system's settings!
ARCHC_BIN_PATH=/cygdrive/e/opt/archc/bin

make -f Makefile.archc distclean
${ARCHC_BIN_PATH}/acsim toy.ac -abi -g -s
make -f Makefile.archc
rm -rf acbingenbuilddir
${ARCHC_BIN_PATH}/acbingen.sh -atoy -i`pwd`/../toysim-tools/ toy.ac
#cd build
#/usr/local/bin/binutils-2.16.1/configure --target=toy-elf --prefix=/cygdrive/g/devel/toy-install
#make all-gas
#make install-gas
#cd ../build
