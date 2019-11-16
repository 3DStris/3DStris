# 3DStris [![Build Status][travis-badge]][travis-link]
Basic Tetris clone for the 3DS.

<p float="left">
	<img src="screenshot.png" width="400px"/>
	<img src="banner.png" width="400px"/>
</p>

# Building
## Setup
For building [you'll need to set up devkitPro][devkitpro-setup], CMake >= 3.12 and the following tools in your `PATH`:
- [bannertool][bannertool-url]
- [makerom][makerom-url]

Make sure to clone recursively (required for `lib/3ds-cmake`):
```bash
git clone --recursive https://github.com/matcool/3DStris
# Or if you've already cloned
git submodule update --init
```
## Commands
*On Windows, the following commands should be run in devkitPro's shell `devkitPro/msys2/usr/bin/bash.exe`.*
```bash
mkdir build && cd build
cmake -G "Unix Makefiles" .. # Use "Unix Makefiles" as to avoid using MSVC on Windows
make
```
Binaries can be found in `build/apps/`.

[devkitpro-setup]: https://www.3dbrew.org/wiki/Setting_up_Development_Environment
[makerom-url]: https://github.com/jakcron/Project_CTR
[bannertool-url]: https://github.com/Steveice10/bannertool
[travis-badge]: https://travis-ci.org/3DStris/3DStris.svg?branch=master
[travis-link]: https://travis-ci.org/3DStris/3DStris
