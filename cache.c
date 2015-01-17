#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <assert.h>

#include "cache.h"

struct cache_t *cache_init(unsigned short bucket_cnt,
                           unsigned short max_cnt,
                           unsigned long long int max_size,
                           struct cache_method_t meth)
{
    struct cache_t *c = malloc(sizeof(*c)); assert(c);
    c->h = hash_init(bucket_cnt, meth.key_fn, NULL); assert(c->h);
    c->meth = meth;
    c->max_cnt = max_cnt;
    c->max_size = max_size;
    assert(max_cnt <= bucket_cnt);
    cache_reset_stats(c);
    return c;
}
unsigned int cache_get_hit_cnt(struct cache_t *c)
{
    return c->hit_cnt;
}
unsigned int cache_get_access_cnt(struct cache_t *c)
{
    return c->access_cnt;
}

void cache_reset_stats(struct cache_t *c)
{
    c->hit_cnt = c->access_cnt = 0;
}

unsigned long long int cache_get_maxsize(struct cache_t *c)
{
    return c->max_size;
}

void *cache_access(struct cache_t *c, void *ref)
{
    cache_key_t key = c->h->key_fn(ref);
    struct cache_entry_t *entry;

    c->access_cnt++;
    /*-- present in cache? --*/
    if (hash_contains(c->h, key)) {
        c->hit_cnt++;
        entry = hash_get(c->h, key);
    } else {
        /* at capacity? */
        if (c->h->load == c->max_cnt) {
            /*-- replace someone --*/
            /* (1) find victim */
            cache_key_t *victim_key;
            victim_key = hash_accum(c->h, c->meth.findvictim_fn, NULL);
/*             warnx("replacing %018lld", *victim_key); */

            /* (2) free/save victim out of cache*/
            struct cache_entry_t *victim = hash_get(c->h, *victim_key);
            c->meth.free_fn(victim->data, victim->bk);
            assert(hash_remove_key(c->h, *victim_key) == HASH_SUCCESS);
            entry = victim;
        } else {
            entry = malloc(sizeof(*entry)); assert(entry);
            entry->bk = c->meth.init_fn(c->max_cnt);
        }

        /* (3) load data into cache */
        c->meth.fetch_fn(ref, &entry->data, &entry->bk);
        assert(hash_put_keyed(c->h, key, entry) == HASH_SUCCESS);
    }

    c->meth.access_fn(ref, entry->bk); /* access book keeping */
    return entry->data;
}


void cache_iter(struct cache_t *c,
                void *(*iter_fn)(cache_key_t key, void *entry, void *extra),
                void *initial_iter)
{
    hash_iter(c->h, iter_fn, initial_iter);
}


/* TODO constrain cache capacity (major rework because have to repeatedly kick
 * out entries until enough space for new.
 */
