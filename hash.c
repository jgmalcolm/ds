#include <err.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <alloca.h>

#include "hash.h"





struct hash_t *hash_init(unsigned short bucket_cnt,
                         hash_key_fn key_fn,
                         hash_free_fn free_fn)
{
    if (key_fn == NULL)
        return NULL;

    struct hash_t *h = malloc(sizeof(*h)); assert(h);
    h->buckets = malloc(sizeof(h->buckets[0])*bucket_cnt);
    assert(h->buckets);
    h->load = 0;
    h->bucket_cnt = bucket_cnt;
    h->key_fn = key_fn;
    h->free_fn = free_fn;
    /* clear buckets */
    unsigned short i;
    for (i = 0; i < bucket_cnt; i++)
        h->buckets[i].in_use = 0;
    return h;
}






int hash_rehash(struct hash_t *h, unsigned short new_bucket_cnt)
{
    if (new_bucket_cnt < h->load)
        return HASH_ERROR; /* not enough room to rehash */

    /*-- dimension new buckets --*/
    struct hash_elem_t *new_buckets = malloc(sizeof(new_buckets[0])
                                             *new_bucket_cnt);
    assert(new_buckets);
    unsigned short i;
    for (i = 0; i < new_bucket_cnt; i++)
        new_buckets[i].in_use = 0;
    struct hash_elem_t *old_buckets = h->buckets;
    h->buckets = new_buckets;

    unsigned short old_bucket_cnt = h->bucket_cnt; /* how many to rehash */
    h->bucket_cnt = new_bucket_cnt;

    /*-- rehash old elements --*/
    unsigned short saved_load = h->load;
    h->load = 0;
    for (i = 0; i < old_bucket_cnt; i++) {
        if (old_buckets[i].in_use == 0)
            continue;

        int ret = hash_put_keyed(h, old_buckets[i].key, old_buckets[i].val);
        if (ret != HASH_SUCCESS) {
            /* restore hash upon error */
            warnx("unable to replace");
            h->buckets = old_buckets;
            h->bucket_cnt = old_bucket_cnt;
            h->load = saved_load;
            free(new_buckets);
            return ret;
        }
    }

    h->load = saved_load; /* insert hashed incremented this */

    return HASH_SUCCESS;
}





int hash_put(struct hash_t *h, void *d)
{
    return hash_put_keyed(h, h->key_fn(d), d);
}


int hash_put_keyed(struct hash_t *h, hash_key_t hc, void *d)
{
    if (hash_contains(h, hc) || h->load == h->bucket_cnt) {
        return HASH_ERROR;
    }

    /* insert into proper bucket */
    unsigned short i, start_bucket;
    i = start_bucket = hc % h->bucket_cnt;
    do {
        if (h->buckets[i].in_use == 0) { /* empty? */
            h->buckets[i].in_use = 1;
            h->buckets[i].key = hc;
            h->buckets[i].val = d;
            h->load += 1;
            return HASH_SUCCESS; /* successfully placed */
        }
        i = (i + 1) % h->bucket_cnt; /* next bucket */
    } while (i != start_bucket);

    return HASH_ERROR; /* full */
}

static int hash_index(struct hash_t *h, hash_key_t key)
{
    unsigned short start_bucket = key % h->bucket_cnt;
    unsigned short i = start_bucket;
    do {
        if (h->buckets[i].in_use == 0)
            return HASH_ERROR; /* not found */
        if (h->buckets[i].key == key)
            return i; /* found */
        i = (i + 1) % h->bucket_cnt; /* next bucket */
    } while (i != start_bucket); /* while not wrapped */

    return HASH_ERROR; /* after exhaustive search it was not found */
}




int hash_remove(struct hash_t *h, void *d)
{
    return hash_remove_key(h, h->key_fn(d));
}


int hash_remove_key(struct hash_t *h, hash_key_t key)
{
    /*-- (1) find the element --*/
    unsigned short i = hash_index(h, key);
    if (i == (unsigned short)HASH_ERROR)
        return HASH_ERROR;
    
    /*-- (2) remove this element --*/
    if (h->free_fn) {
        h->free_fn(h->buckets[i].val);
    }
    h->buckets[i].in_use = 0;
    h->load--;

    /*-- (3) find next empty slot --*/
    i = (i + 1) % h->bucket_cnt; /* move just after deleted entry */
    unsigned short start_bucket = i;
    unsigned short move_cnt = 0;
    do {
        if (h->buckets[i].in_use == 0) /* empty? */
            break;
        i = (i + 1) % h->bucket_cnt; /* next bucket */
        move_cnt++; /* keep track of how many we're going to have to copy */
    } while (i != start_bucket);

    /*-- (4) temporarily remove all elements until next empty spot --*/
    struct hash_elem_t *tmp_buckets = alloca(sizeof(tmp_buckets[0])*move_cnt);
    assert(tmp_buckets);
    unsigned short move_to = 0;
    unsigned short move_from = start_bucket;
    unsigned short saved_move_cnt = move_cnt;
    while (move_cnt > 0) {
        tmp_buckets[move_to] = h->buckets[move_from]; /* val and hash code */
        h->buckets[move_from].in_use = 0;

        move_from = (move_from + 1) % h->bucket_cnt;
        move_to++;
        move_cnt--;
    }
    
    /*-- (5) re-insert those elements --*/
    unsigned short saved_load = h->load; /* insert increments load */
    h->load = 0; /* reset for now */
    move_cnt = saved_move_cnt;
    while (move_cnt > 0) {
        assert(hash_put_keyed(h,
                              tmp_buckets[move_cnt-1].key,
                              tmp_buckets[move_cnt-1].val)
               == HASH_SUCCESS); /* no reason to fail if they were present
                                  * before */
        move_cnt--;
    }
    h->load = saved_load;

    return HASH_SUCCESS;
}





void *hash_get(struct hash_t *h, hash_key_t key)
{
    unsigned short ind = hash_index(h, key);

    /* was it found? */
    if (ind == (unsigned short)HASH_ERROR)
        return NULL;

    return h->buckets[ind].val;
}

int hash_contains_val(struct hash_t *h, void *d)
{
    return hash_contains(h, h->key_fn(d));
}

int hash_contains(struct hash_t *h, hash_key_t key)
{
    unsigned short ind = hash_index(h, key);
    return ind != (unsigned short)HASH_ERROR;
}


void *hash_accum(struct hash_t *h,
                 void *(*accum_fn)(hash_key_t key, void *val, void *acc),
                 void *initial_acc)
{
    unsigned short i;

    void *accum = initial_acc;
    for (i = 0; i < h->bucket_cnt; i++) {
        if (h->buckets[i].in_use)
            accum = accum_fn(h->buckets[i].key, h->buckets[i].val, accum);
    }
    return accum;
}

void hash_iter(struct hash_t *h,
               void *(*iter_fn)(hash_key_t, void *, void *),
               void *extra_param)
{
    unsigned short i;

    for (i = 0; i < h->bucket_cnt; i++) {
        if (h->buckets[i].in_use)
            h->buckets[i].val = iter_fn(h->buckets[i].key,
                                        h->buckets[i].val,
                                        extra_param);
    }
}

unsigned short hash_load(struct hash_t *h)
{
    return h->load;
}
