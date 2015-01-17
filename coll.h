/* Collection interface */

#ifndef __COLL_H
#define __COLL_H

#include <stdlib.h>  /* size_t */

#define COLL_SIZE  (256)
#define COLL_RESIZE_FACTOR (2)

struct coll_t {
    void **elements;
    size_t count;     /* current load */
    size_t max_count; /* max capacity for current sizing */
};

typedef void (*coll_free_fn)(void *a);
typedef int (*coll_cmp_fn)(void *a, void *b);
typedef int (*coll_test_fn)(void *a);
typedef void *(*coll_map_fn)(void *a);
typedef void *(*coll_fold_fn)(void *a, void *init);

#ifdef __cplusplus
extern "C" {
#endif

/*-- create/destroy --*/
struct coll_t *coll_new(void);
void coll_compact(struct coll_t *);
void coll_empty(struct coll_t *, coll_free_fn); /* fn == NULL if no free */
void coll_free(struct coll_t *, coll_free_fn); /* fn == NULL if no free */

/*-- add --*/
void coll_add(struct coll_t *, void *);
void coll_append(struct coll_t *, struct coll_t *);

/*-- count --*/
size_t coll_count(struct coll_t *);
size_t coll_count_if(struct coll_t *, coll_test_fn);

/*-- testing --*/
int coll_all(struct coll_t *, coll_test_fn);

/*-- traversing --*/
void coll_map(struct coll_t *, coll_map_fn);

/*-- form new list of all elements that pass test_fn() == 1 */
struct coll_t *coll_filter(struct coll_t *, coll_test_fn);
/*-- filter yet remove those items from original coll --*/
struct coll_t *coll_remove(struct coll_t *, coll_test_fn);

/* selectively delete */
void coll_delete(struct coll_t *, coll_test_fn);
void coll_delete_pt(struct coll_t *, void *);

/*-- fold functionality --*/
void *coll_fold(struct coll_t *, coll_fold_fn, void *init);

#ifdef __cplusplus
}
#endif

#endif /* __COLL_H */
