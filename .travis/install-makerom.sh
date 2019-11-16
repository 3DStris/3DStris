#!/bin/sh
set -ex

git clone https://github.com/jakcron/Project_CTR.git
cd Project_CTR/makerom
make

chmod +x makerom
sudo mv makerom /usr/bin
