#!/bin/sh
set -ex

wget -O makerom.zip https://github.com/jakcron/Project_CTR/releases/download/v0.16/makerom_016_ctrtool.zip
unzip makerom.zip

cd Ubuntu
chmod +x makerom
sudo mv makerom /usr/bin/
