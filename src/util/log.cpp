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

#include <3dstris/util/fs.hpp>
#include <3dstris/util/log.hpp>
#include <3dstris/version.hpp>

Log::Log() {
	const static FS_Path HOMEBREW_PATH = fsMakePath(PATH_ASCII, "/3ds/");
	const static FS_Path GAME_PATH = fsMakePath(PATH_ASCII, "/3ds/3dstris/");
	static constexpr auto LOG_PATH = "sdmc:/3ds/3dstris/log.log";

	svcCreateMutex(&mutex, false);

	FS_Archive sdmcArchive;
	FSUSER_OpenArchive(&sdmcArchive, ARCHIVE_SDMC, fsMakePath(PATH_EMPTY, ""));

	if (!directoryExists(sdmcArchive, HOMEBREW_PATH)) {
		log(INFO, __FILE__, __LINE__, "Creating /3ds/");
		FSUSER_CreateDirectory(sdmcArchive, HOMEBREW_PATH, 0);
	}
	if (!directoryExists(sdmcArchive, GAME_PATH)) {
		log(INFO, __FILE__, __LINE__, "Creating 3DStris dir");
		FSUSER_CreateDirectory(sdmcArchive, GAME_PATH, 0);
	}

	FSUSER_CloseArchive(sdmcArchive);

	setFile(fopen(LOG_PATH, "w"));
	log(INFO, __FILE__, __LINE__, "3DStris v%s", _3DSTRIS_VERSION);
}

Log::~Log() {
	svcCloseHandle(mutex);
	fclose(fp);
}

void Log::setFile(FILE* fp) {
	this->fp = fp;
}

void Log::setLevel(const Level level) {
	this->level = level;
}

void Log::setQuiet(const bool enable) {
	this->quiet = enable;
}
