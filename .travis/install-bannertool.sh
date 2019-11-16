#!/bin/sh
set -ex

git clone --recursive https://github.com/Steveice10/bannertool.git
cd bannertool
sudo make install
