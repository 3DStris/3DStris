/*
 * Copyright (c) 2020 rxi, 3DStris
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef NDEBUG
extern "C" {
	#include <3ds/console.h>
}
#endif

#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>
#include <3dstris/version.hpp>

Log::Log() noexcept {
	static const FS_Path HOMEBREW_PATH = fsMakePath(PATH_ASCII, "/3ds/");
	static const FS_Path GAME_PATH = fsMakePath(PATH_ASCII, "/3ds/3dstris/");
	static constexpr auto LOG_PATH = "sdmc:/3ds/3dstris/log.log";

#ifndef NDEBUG
	consoleDebugInit(debugDevice_3DMOO);
	setLevel(Log::Level::DEBUG);
	setQuiet(false);
#endif

	// Please don't use any of the LOG macros here

	svcCreateMutex(&mutex, false);

	FS_Archive sdmcArchive;
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));

	if (!directoryExists(sdmcArchive, HOMEBREW_PATH)) {
		log(Level::INFO, __FILE__, __LINE__, "Creating /3ds/");
		FSUSER_CreateDirectory(sdmcArchive, HOMEBREW_PATH, 0);
	}
	if (!directoryExists(sdmcArchive, GAME_PATH)) {
		log(Level::INFO, __FILE__, __LINE__, "Creating 3DStris dir");
		FSUSER_CreateDirectory(sdmcArchive, GAME_PATH, 0);
	}

	FSUSER_CloseArchive(sdmcArchive);

	fp = fopen(LOG_PATH, "w");
	log(Level::INFO, __FILE__, __LINE__, "3DStris v%s-%s", _3DSTRIS_VERSION,
		_3DSTRIS_GIT_HASH);
}

Log::~Log() noexcept {
	svcCloseHandle(mutex);
	fclose(fp);
}

void Log::log(const Level level, const char* __restrict file, const int line,
			  const char* __restrict string) noexcept {
	log(level, file, line, "%s", string);
}

void Log::setFile(FILE* fp) noexcept {
	this->fp = fp;
}

void Log::setLevel(const Level level) noexcept {
	this->level = level;
}

void Log::setQuiet(const bool enable) noexcept {
	this->quiet = enable;
}
