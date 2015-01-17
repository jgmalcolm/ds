#ifndef MALLOC
#define MALLOC(a,sz) { (a) = malloc((sz)*sizeof(*(a))); assert(a); }
#endif

#include <assert.h>
#include <stdlib.h>
#include "coll.h"

struct coll_t *coll_new(void)
{
    struct coll_t *c; MALLOC(c, 1);
    MALLOC(c->elements, COLL_SIZE);
    c->count = 0;
    c->max_count = COLL_SIZE;

    return c;
}

static void coll_enlarge(struct coll_t *c)
{
    c->max_count = c->max_count * COLL_RESIZE_FACTOR;
    c->elements = realloc(c->elements, c->max_count * sizeof(c->elements[0]));
    assert(c->elements);
}

void coll_add(struct coll_t *c, void *a)
{
    /*-- (1) resize if necessary (update cursor) --*/
    if (c->count == c->max_count)
        coll_enlarge(c);

    /*-- (2) book keeping --*/
    c->count += 1;

    /*-- (3) add to end --*/
    c->elements[c->count - 1] = a;
}

void coll_append(struct coll_t *to_c, struct coll_t *from_c)
{
    /*-- (1) resize to_c if necessary --*/
    while (to_c->max_count < to_c->count + from_c->count)
        coll_enlarge(to_c);

    /*-- (2) copy over elements en mass --*/
    int i;
    for (i = 0; i < from_c->count; i++)
        to_c->elements[to_c->count + i] = from_c->elements[i];

    /*-- (3) book keeping --*/
    to_c->count += from_c->count;
}

void coll_empty(struct coll_t *c, coll_free_fn free)
{
    /*-- (1) free all elements --*/
    if (free != NULL) {
        int i;
        for (i = 0; i < c->count; i++)
            free(c->elements[i]);
    }

    /*-- (2) update book keeping --*/
    c->count = 0;
}

void coll_free(struct coll_t *c, coll_free_fn free_fn)
{
    coll_empty(c, free_fn);
    free(c);
}

size_t coll_count(struct coll_t *c)
{
    return c->count;
}

size_t coll_count_if(struct coll_t *c, coll_test_fn test)
{
    size_t cnt = 0;
    int i;
    for (i = 0; i < c->count; i++)
        if (test(c->elements[i]) == 1)
            cnt += 1;
    return cnt;
}


int coll_all(struct coll_t *c, coll_test_fn test)
{
    int i;
    for (i = 0; i < c->count; i++) {
        if (test(c->elements[i]) == 0)
            return 0; /* fail */
    }
    return 1; /* all passed */
}

void coll_map(struct coll_t *c, coll_map_fn map)
{
    int i;
    for (i = 0; i < c->count; i++)
        c->elements[i] = map(c->elements[i]);
}

struct coll_t *coll_filter(struct coll_t *c, coll_test_fn test)
{
    struct coll_t *new_c = coll_new();

    int i;
    for (i = 0; i < c->count; i++) {
        if (test(c->elements[i]) == 1)
            coll_add(new_c, c->elements[i]);
    }

    return new_c;
}
struct coll_t *coll_remove(struct coll_t *c, coll_test_fn test)
{
    struct coll_t *new_c = coll_new();

    int i;
    for (i = 0; i < c->count; i++) {
        if (test(c->elements[i]) == 1) {
            /*-- (1) remove --*/
            void *removed = c->elements[i];
            if (i < c->count - 1) { /* if not last, move last item here */
                c->elements[i] = c->elements[c->count - 1];
            }
            c->count += -1;

            /*-- (2) add --*/
            coll_add(new_c, removed);

            /*-- (3) repeat on this one that has been moved here --*/
            i += -1;
        }
    }

    return new_c;
}

void *coll_fold(struct coll_t *c, coll_fold_fn fn, void *init)
{
    int i;
    for (i = 0; i < c->count; i++) {
        init = fn(c->elements[i], init);
    }
    return init;
}

/* Implementation note, it is assumed that there is little need to resize
 * down */

/* Assumption.  Iterate from start of array to end.  Modifications,
 * e.g. additions and removals, are seen later in the traversal.
 */


void coll_delete(struct coll_t *c, coll_test_fn test)
{
    for (int i = 0; i < c->count; i++) {
        if (test(c->elements[i]) == 1) {
            /*-- (1) remove --*/
            if (i < c->count - 1) { /* if not last, move last item here */
                c->elements[i] = c->elements[c->count - 1];
            }
            c->count += -1;

            /*-- (2) repeat on this one that has been moved here --*/
            i += -1;
        }
    }
}
void coll_delete_pt(struct coll_t *c, void *v)
{
    int is_pointer(void *v2) { return v == v2; }
    coll_delete(c, is_pointer);
}
