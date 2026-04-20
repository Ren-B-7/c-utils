#ifndef BARRUST_LOGGER_H__
#define BARRUST_LOGGER_H__

#include <stdio.h>

typedef enum {
  LOG_DEBUG = 0,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_NONE,
} log_level_t;

void log_init(log_level_t level, const char *filepath);
void log_close(void);
void _log_write(log_level_t level, const char *file, int line, const char *fmt,
                ...);

#define LOG_DEBUG(...) _log_write(LOG_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) _log_write(LOG_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) _log_write(LOG_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) _log_write(LOG_ERROR, __FILE__, __LINE__, __VA_ARGS__)

#endif
