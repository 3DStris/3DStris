#!/bin/bash
set -ex

wget https://github.com/devkitPro/pacman/releases/download/devkitpro-pacman-1.0.1/devkitpro-pacman.deb
sudo dpkg -i devkitpro-pacman.deb

sudo dkp-pacman -Sy
sudo dkp-pacman -S 3ds-dev --noconfirm
