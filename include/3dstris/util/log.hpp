/*
 * Copyright (c) 2020 rxi, 3DStris
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `log.c` for details.
 */

#pragma once

extern "C" {
#include <3ds/synchronization.h>
}
#include <stdio.h>
#include <time.h>

#include <limits>

#define LOG_TRACE(...) \
	Log::get().log(Log::Level::TRACE, __FILE__, __LINE__, __VA_ARGS__)

#ifndef NDEBUG
	#define LOG_DEBUG(...) \
		Log::get().log(Log::Level::DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#else
	#define LOG_DEBUG(...)
#endif

#define LOG_INFO(...) \
	Log::get().log(Log::Level::INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) \
	Log::get().log(Log::Level::WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) \
	Log::get().log(Log::Level::ERROR, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FATAL(...) \
	Log::get().log(Log::Level::FATAL, __FILE__, __LINE__, __VA_ARGS__)

class Log final {
   public:
	enum class Level { TRACE, DEBUG, INFO, WARN, ERROR, FATAL };

	static Log& get() noexcept {
		static Log log;
		return log;
	}

	void log(Level level, const char* __restrict file, int line,
			 const char* __restrict string) noexcept;

	template <typename... Args>
	void log(const Level level, const char* __restrict file, int line,
			 const char* __restrict fmt, Args&&... args) noexcept {
		static const char* LEVELS[]{"TRACE", "DEBUG", "INFO",
									"WARN",	 "ERROR", "FATAL"};

		if (level < this->level || (quiet && !fp)) {
			return;
		}

		// Get current time
		const time_t t = time(nullptr);
		tm lt;
		localtime_r(&t, &lt);

		svcWaitSynchronization(mutex, std::numeric_limits<s64>::max());

		const auto printTo = [&](FILE* fp, const char* __restrict format) {
			char buf[32];
			buf[strftime(buf, sizeof buf, format, &lt)] = '\0';
			fprintf(fp, "%s %-5s %s:%d: ", buf,
					LEVELS[static_cast<size_t>(level)], file, line);
			fprintf(fp, fmt, args...);
			fputs("\n", fp);
			fflush(fp);
		};

		// Log to stderr
		if (!quiet) {
			printTo(stderr, "%T");
		}
		// Log to file
		if (fp) {
			printTo(fp, "%F %T");
		}

		svcReleaseMutex(mutex);
	}

	void setFile(FILE* fp) noexcept;
	void setLevel(Level level) noexcept;
	void setQuiet(bool enable) noexcept;

   private:
	Log() noexcept;
	~Log() noexcept;

	Handle mutex;

	FILE* fp = nullptr;
	Level level = Level::INFO;
	bool quiet = true;
};
