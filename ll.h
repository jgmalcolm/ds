#ifndef __LL_H
#define __LL_H

#if !defined(WIN32)
#include <stdbool.h>
#endif
#include "jm.h"

typedef struct ll_t {
    void *data;
    struct ll_t *next;
} ll_t;


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*ll_free_fn) (void *a);
typedef int (*ll_cmp_fn) (void *a, void *b);
typedef bool (*ll_test_fn)(void *a);
typedef void (*ll_map_fn)(void *a);
typedef void (*ll_mapi_fn)(void *a, int);
typedef ll_t *(*ll_update_fn)(void *cur);
typedef void *(*ll_fold_fn)(void *a, void *init);

/*-- adding --*/
ll_t *ll_add(ll_t *, void *);
ll_t *ll_add_to_back(ll_t *, void *);
ll_t *ll_add_to_front(ll_t *, void *);
ll_t *ll_add_sorted(ll_t *, ll_cmp_fn, void *);
ll_t *ll_concat(ll_t *, ll_t *);

/*-- removing --*/
void *ll_remove_first(ll_t **);
void *ll_remove(ll_t **, ll_test_fn);
void ll_remove_if(ll_t **, ll_test_fn, ll_free_fn);
void ll_move(ll_t **from, ll_t **to);

/*-- finding --*/
void *ll_find(ll_t *, ll_test_fn);
void *ll_find_sorted(ll_t *, ll_cmp_fn, void *);
int ll_find_index(ll_t *, ll_test_fn);

/*-- freeing --*/
void ll_free(ll_t *, ll_free_fn); /* free_fn == NULL iff only free
                                          * linked list data structure, not
                                          * actual data */

/*-- length --*/
uint ll_len(ll_t *);
bool ll_is_empty(ll_t *);

/*-- tests --*/
bool ll_all(ll_t *, ll_test_fn); /* 1 iff all pass test_fn==1 */
bool ll_any(ll_t *, ll_test_fn); /* 1 iff any pass test_fn==1 */

/*-- iterating --*/
void ll_map(ll_t *, ll_map_fn);
void ll_gen(ll_t *, ll_mapi_fn);

/* fold functionality */
void *ll_foldl(ll_fold_fn fn, void *init, ll_t *lst);
void *ll_foldr(ll_fold_fn fn, void *init, ll_t *lst);

/* form new list of all elements that pass test_fn()==1 */
ll_t *ll_filter(ll_t *, ll_test_fn);
ll_t *ll_filter_set(ll_t **, ll_test_fn); /* destructive */
ll_t *ll_update(ll_t *, ll_update_fn);

/*-- peek --*/
void *ll_peek(ll_t *);
void *ll_peek_nth(ll_t *, unsigned int); /* zero-indexed */
ll_t *ll_next(ll_t *);

void *ll2array(ll_t *);

#ifdef __cplusplus
}
#endif

#endif
