#!/bin/sh
set -ex

wget -O bannertool https://geni.site/stuff/bannertool
chmod +x bannertool
sudo mv bannertool /usr/bin/
