#ifndef __BT_H
#define __BT_H

#if !defined(WIN32)
#include <stdbool.h>
#endif
#include "jm.h"

typedef struct bt_t {
    void *data;
    struct bt_t *left, *right;
} bt_t;


#ifdef __cplusplus
extern "C" {
#endif

typedef void (*bt_free_fn) (void *a);
typedef int (*bt_cmp_fn) (void *a, void *b);
typedef bool (*bt_test_fn)(void *a);
typedef void (*bt_map_fn)(void *a);
typedef void *(*bt_fold_fn)(void *a, void *init);

bt_t *bt_add(bt_t *, bt_cmp_fn, void *);
void *bt_remove(bt_t **);
void bt_remove_if(bt_t **, bt_test_fn, bt_free_fn);
void *bt_find(bt_t *, bt_cmp_fn, void *);

/*-- freeing --*/
void bt_free(bt_t *, bt_free_fn);

/*-- length --*/
uint bt_count(bt_t *);
bool bt_is_empty(bt_t *);

/*-- tests --*/
bool bt_all(bt_t *, bt_test_fn); /* 1 iff all pass test_fn==1 */
bool bt_any(bt_t *, bt_test_fn); /* 1 iff any pass test_fn==1 */

/*-- iterating --*/
void bt_map(bt_t *, bt_map_fn);

/* fold functionality */
void *bt_fold(bt_t *, bt_fold_fn, void *init);

/* form new list of abt elements that pass test_fn()==1 */
bt_t *bt_filter(bt_t *, bt_test_fn);
bt_t *bt_filter_set(bt_t **, bt_test_fn); /* destructive */

/*-- peek --*/
void *bt_peek(bt_t *);
bt_t *bt_next(bt_t *);

#ifdef __cplusplus
}
#endif

#endif
