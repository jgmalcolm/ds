#ifndef __JM_H
#define __JM_H

#ifndef __UINT
#define __UINT
typedef unsigned int uint;
#endif

#define MALLOC  malloc
#define REALLOC realloc
#define FREE    free
#define PRINTF  printf

#include <assert.h>
#define ASSERT(exp) do { assert(exp); } while (false)

/* temporary memory, so no need to free */
#define TMP_INIT(ty, var, cnt)                                  \
    ty *(var) = (ty *)MALLOC((cnt) * sizeof(ty)); ASSERT(var);
#define MALLOC_INIT(ty, var, cnt)               \
    TMP_INIT(ty, var, cnt);

#define TMP_SET(ty, dest, cnt)                                          \
    do { dest = (ty *)MALLOC((cnt) * sizeof(ty)); ASSERT(dest); } while (false)
#define MALLOC_SET(ty, dest, cnt)                       \
    do { TMP_SET(ty, dest, cnt); } while (false)

#define REALLOC_SET(ty, dest, cnt)                                      \
    do { dest = (ty *)REALLOC((dest), (cnt) * sizeof(ty));  ASSERT(dest); } while (false)

#define MSG(msg,...) do { char buf[300]; snprintf(buf, sizeof(buf), __FILE__":%d(%s) " msg "\n", __LINE__, __FUNCTION__, ##__VA_ARGS__); PRINTF(buf); } while (false)

#define SHOW(exp) do { char buf[300]; snprintf(buf, sizeof(buf), __FILE__":%d(%s) %s %d\n", __LINE__, __FUNCTION__, #exp, (int)exp); PRINTF(buf); } while (false)
#define SHOW_P(ptr) do { char buf[300]; snprintf(buf, sizeof(buf), __FILE__":%d(%s) %s %p\n", __LINE__, __FUNCTION__, #ptr, ptr); PRINTF(buf); } while (false)
#define SHOW_F(exp) do { char buf[300]; snprintf(buf, sizeof(buf), __FILE__":%d(%s) %s %f\n", __LINE__, __FUNCTION__, #exp, (float)exp); PRINTF(buf); } while (false)

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#endif
