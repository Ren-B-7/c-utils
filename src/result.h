#ifndef BARRUST_RESULT_H__
#define BARRUST_RESULT_H__

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define RESULT_MSG_LEN 256

typedef struct {
	bool ok;
	char msg[RESULT_MSG_LEN];
} result_t;

static inline result_t result_ok(void)
{
	result_t r;
	r.ok = true;
	r.msg[0] = '\0';
	return r;
}

static inline result_t result_err(const char* fmt, ...)
{
	result_t r;
	r.ok = false;
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(r.msg, RESULT_MSG_LEN, fmt, ap);
	va_end(ap);
	return r;
}

#define TRY(expr) \
	do { \
		result_t _r = (expr); \
		if (!_r.ok) \
			return _r; \
	} while (0)

static inline void result_unwrap(result_t r, const char* ctx)
{
	if (!r.ok) {
		fprintf(stderr, "[result] FATAL in %s: %s\n", ctx, r.msg);
		abort();
	}
}

#define RESULT_UNWRAP(r) result_unwrap((r), __func__)

static inline bool result_check(result_t r, const char* ctx)
{
	if (!r.ok) {
		fprintf(stderr, "[result] ERROR in %s: %s\n", ctx, r.msg);
	}
	return r.ok;
}

typedef struct {
	bool ok;
	void* value;
	char msg[RESULT_MSG_LEN];
} result_ptr_t;

static inline result_ptr_t result_ptr_ok(void* value)
{
	result_ptr_t r;
	r.ok = true;
	r.value = value;
	r.msg[0] = '\0';
	return r;
}

static inline result_ptr_t result_ptr_err(const char* fmt, ...)
{
	result_ptr_t r;
	r.ok = false;
	r.value = NULL;
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(r.msg, RESULT_MSG_LEN, fmt, ap);
	va_end(ap);
	return r;
}

#endif
