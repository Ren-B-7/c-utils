#ifndef BARRUST_MACROS_H__
#define BARRUST_MACROS_H__

#define ARRAYLEN(a) (sizeof(a) / sizeof((a)[0]))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(v, lo, hi) (MIN(MAX((v), (lo)), (hi)))

#define SWAP(T, a, b)                                                          \
  do {                                                                         \
    T _tmp = (a);                                                              \
    (a) = (b);                                                                 \
    (b) = _tmp;                                                                \
  } while (0)

#define UNUSED(x) ((void)(x))

#define IS_POW2(n) (((n) & ((n) - 1)) == 0 && (n) > 0)
#define ALIGN_UP(n, align) (((n) + (align) - 1) & ~((align) - 1))
#define ALIGN_DOWN(n, align) ((n) & ~((align) - 1))

#define BIT_SET(x, bit) ((x) |= (1ULL << (bit)))
#define BIT_CLR(x, bit) ((x) &= ~(1ULL << (bit)))
#define BIT_TOG(x, bit) ((x) ^= (1ULL << (bit)))
#define BIT_TST(x, bit) (((x) >> (bit)) & 1)

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define CONCAT(a, b) a##b
#define ZERO_INIT {0}

#define CAST_SIZE(x) ((size_t)(x))
#define CAST_INT(x) ((int)(x))
#define CAST_PTR(T, x) ((T *)(x))

#if defined(__GNUC__) || defined(__clang__)
#define _DEFER_PASTE(a, b) a##b
#define _DEFER_NAME(line) _DEFER_PASTE(_defer_var_, line)
#define _DEFER_WRAP(fn, ptr)                                                   \
  static inline void _DEFER_PASTE(_defer_fn_, __LINE__)(void *p) {             \
    fn(*(void **)p);                                                           \
  }                                                                            \
  void *_DEFER_NAME(__LINE__)                                                  \
      __attribute__((cleanup(_DEFER_PASTE(_defer_fn_, __LINE__)))) = (ptr)
#define DEFER(fn, ptr) _DEFER_WRAP(fn, ptr)
#else
#define DEFER(fn, ptr)
#endif

#endif
