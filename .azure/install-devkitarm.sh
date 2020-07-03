#!/bin/bash
set -ex

wget https://github.com/devkitPro/pacman/releases/download/v1.0.2/devkitpro-pacman.amd64.deb
sudo dpkg -i devkitpro-pacman.amd64.deb

sudo dkp-pacman -Sy
sudo dkp-pacman -S 3ds-dev --noconfirm
