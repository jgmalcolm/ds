#ifndef __CQUEUE_H
#define __CQUEUE_H

#include "queue.h"

typedef struct {
    q_t *q;
} cq_t;

/*-- initialize cqueue --*/
void cqueue_init(cq_t *cq);

/*-- enqueue --*/
void cqueue_enqueue(cq_t *cq, void *d);

/*-- returns next --*/
void *cqueue_next(cq_t *cq);

/*-- peek at current (do not dequeue) --*/
void *cqueue_peek(cq_t *cq);

#endif
