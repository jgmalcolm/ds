#ifndef __QUEUE_H
#define __QUEUE_H

#include "ll.h"

typedef struct {
    ll_t *head; /* list representing queue */
    ll_t *tail; /* last element for quick enqueue */
} q_t;
typedef bool (*q_test_fn)(void *);
typedef void (*q_map_fn)(void *);

void q_init(q_t *);
void q_enqueue(q_t *, void *);
void *q_dequeue(q_t *);
int q_len(q_t *);
void *q_peek(q_t *);
int q_empty(q_t *);
void q_map(q_t *, q_map_fn);
void *q_delete(q_t *, q_test_fn); /* remove yet keep order */

#endif
