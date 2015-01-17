#include <stdlib.h>
#include "twul.h"

twul_t *twul_add(twul_t *t, long key, void *d)
{
    if (t == NULL) {
        MALLOC_SET(twul_t, t, 1);
        t->key = key;
        t->leaves = ll_add(NULL, d);
        t->left = t->right = NULL;
    } else if (key == t->key) {
        t->leaves = ll_add(t->leaves, d);
    } else if (key < t->key) {
        t->left = twul_add(t->left, key, d);
    } else {
        t->right = twul_add(t->right, key, d);
    }
    return t;
}

void *twul_remove(twul_t **t_, long key, test_fn test)
{
    twul_t *t = *t_;
    if (t == NULL) return NULL;
    if (key == t->key)      return ll_remove(&t->leaves, test);
    else if (key < t->key)  return twul_remove(&t->left, key, test);
    else                    return twul_remove(&t->right, key, test);
}

void twul_free(twul_t *t, free_fn fn)
{
    if (t == NULL) return;
    ll_free(t->leaves, fn);
    twul_free(t->left, fn);
    twul_free(t->right, fn);
    FREE(t);
}

uint twul_count(twul_t *t)
{
    if (t == NULL) return 0;
    return ll_len(t->leaves) + twul_count(t->left) + twul_count(t->right);
}
