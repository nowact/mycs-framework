#!/usr/bin/bash

echo "install dependent packages into ./OpenSource"
mkdir -p OpenSource

tar -xf Packages/boost_1_72_0.tar.bz2 -C OpenSource
find OpenSource/boost_1_72_0 -type f -print0 | xargs -0 chmod a-w 

#build boost
#cd OpenSource/boost_1_72_0
#./bootstrap.sh ./bootstrap.sh --prefix=/absolute/path/to/mycs-framework/DevLibs/OpenSource/BoostInstall
#./b2 install

