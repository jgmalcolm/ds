#include <stdlib.h>
#include "queue.h"

void q_init(q_t *q)
{
    q->head = q->tail = NULL;
}

void q_enqueue(q_t *q, void *d)
{ /* O(1) */
    q->tail = ll_add_to_back(q->tail, d);
    if (q->head == NULL)
        q->head = q->tail;
    else
        q->tail = ll_next(q->tail);
}

void *q_dequeue(q_t *q)
{ /* O(1) */
    if (q->tail == q->head) /* one element? (or none) */
        q->tail = NULL;
    void *r = ll_remove_first(&q->head);
    if (q->head == NULL) /* last element? */
        q->tail = NULL;
    return r;
}

int q_len(q_t *q)
{
    return ll_len(q->head);
}

int q_empty(q_t *q)
{
    return q->head == NULL;
}

void *q_peek(q_t *q)
{
    return ll_peek(q->head);
}

void q_map(q_t *q, q_map_fn fn) { ll_map(q->head, fn); }


#if 0
void *q_delete(q_t *q, q_test_fn test)
{
    ll_t *remove_first(ll_t **n)
    {
        if (*n == NULL)
            return NULL;
        ll_t *first = *n;
        *n = (*n)->next;
        return first;
    }
    ll_t *prev = NULL; /* to fix tail */
    ll_t *remove(ll_t **lst)
    {
        if (*lst == NULL)
            return NULL;
        /* is this it? */
        if (test((*lst)->data) == 1) {
            return remove_first(lst); /* remove */
        } else {
            prev = *lst;
            ll_t **ptr_to_next = &(*lst)->next;
            return remove(ptr_to_next);
        }
    }

    /*-- try removing --*/
    ll_t *rem = remove(&q->head);
    if (rem == NULL)
        return NULL;

    /*-- fix tail if necessary --*/
    if (rem == q->tail) /* if removing tail */
        q->tail = prev;

    void *r = rem->data;
    FREE(rem);
    return r;
}
#endif
