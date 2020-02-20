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
	svcCreateMutex(&mutex, false);
}

Log::~Log() {
	svcCloseHandle(mutex);
	fclose(fp);
}

void Log::load(const FS_Archive sdmcArchive) {
	static constexpr auto LOG_PATH = "sdmc:/3ds/3dstris/log.log";
	static const FS_Path logPath =
		fsMakePath(PATH_ASCII, "/3ds/3dstris/log.log");

	if (!fileExists(sdmcArchive, logPath)) {
		LOG_INFO("Creating log file");
		FSUSER_CreateFile(sdmcArchive, logPath, 0, 0);
	}

	setFile(fopen(LOG_PATH, "w"));
	LOG_INFO("3DStris v%s", _3DSTRIS_VERSION);
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
