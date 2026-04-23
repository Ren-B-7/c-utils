#include "logger.h"

#include <stdarg.h>

static log_level_t _log_level = LOG_INFO;
static FILE* _log_file = NULL;

void log_init(log_level_t level, const char* filepath)
{
	_log_level = level;
	if (filepath) {
		_log_file = fopen(filepath, "a");
	}
}

void log_close(void)
{
	if (_log_file) {
		fclose(_log_file);
		_log_file = NULL;
	}
}

void _log_write(log_level_t level, const char* file, int line, const char* fmt,
 ...)
{
	if (level < _log_level) {
		return;
	}
	FILE* targets[] = {stderr, _log_file};
	for (int i = 0; i < 2; i++) {
		if (targets[i]) {
			fprintf(targets[i], "%s:%d ", file, line);
			va_list ap;
			va_start(ap, fmt);
			vfprintf(targets[i], fmt, ap);
			va_end(ap);
			fputc('\n', targets[i]);
		}
	}
}
