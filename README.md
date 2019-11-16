# 3DStris (WIP)

Basic tetris clone for the 3DS

![3dstris screenshot](https://raw.githubusercontent.com/matcool/3DStris/master/screenshot.png)

# Building
## Setup
For building you'll need devkitPro ([how to install and setup for 3ds dev](https://www.3dbrew.org/wiki/Setting_up_Development_Environment)), CMake and these on your path: [bannertool](https://github.com/Steveice10/bannertool) and [makerom](https://github.com/jakcron/Project_CTR)

Also make sure to recursive clone (needed for `lib/3ds-cmake`) :
```bash
git clone https://github.com/matcool/3DStris --recursive
# Or if you've already cloned
git submodule update --init
```
## Commands
*On Windows you should run these in the devkitPro's shell `devkitPro/msys2/usr/bin/bash.exe`*
```bash
mkdir build && cd build
cmake -G "Unix Makefiles" .. # Use "Unix Makefiles" as to avoid using MSVC on Windows
make
```
Binaries can be found on `build/apps/`