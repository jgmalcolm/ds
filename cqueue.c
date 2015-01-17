#include <stdlib.h>
#include <assert.h>
#include "cqueue.h"

/*-- initialize cqueue --*/
void cqueue_init(cq_t *cq)
{
    assert(cq->q = (void *)malloc(sizeof(*(cq->q))));
    queue_init(cq->q);
}
/*-- enqueue --*/
void cqueue_enqueue(cq_t *cq, void *d)
{
    queue_enqueue(cq->q, d);
}

/*-- next --*/
void *cqueue_next(cq_t *cq)
{
    void *current;

    current = queue_dequeue(cq->q);
    queue_enqueue(cq->q, current); /* put back on end */

    return cqueue_peek(cq);
}

/*-- peek --*/
void *cqueue_peek(cq_t *cq)
{
    return queue_peek(cq->q);
}
