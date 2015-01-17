#ifndef __TWUL_H
#define __TWUL_H

#if !defined(WIN32)
#include <stdbool.h>
#endif
#include "jm.h"
#include "ll.h"

typedef struct twul_t {
    long key;
    ll_t *leaves;
    struct twul_t *left, *right;
} twul_t;

#ifndef _FN_
#define _FN_
typedef void (*free_fn) (void *a);
typedef int (*cmp_fn) (void *a, void *b);
typedef bool (*test_fn)(void *a);
typedef void (*map_fn)(void *a);
typedef void *(*map_ret_fn)(void *a);
typedef void *(*fold_fn)(void *a, void *init);
#endif

#ifdef __cplusplus
extern "C" {
#endif

twul_t *twul_add(twul_t *, long key, void *);
void *twul_remove(twul_t **, long key, test_fn);

void twul_free(twul_t *, free_fn);
uint twul_count(twul_t *);

#ifdef __cplusplus
}
#endif

#endif
