#ifndef __CACHE_H
#define __CACHE_H

#include "hash.h"   /* for fast lookup into contents */

typedef hash_key_t cache_key_t;

typedef hash_key_fn cache_key_fn;

/* initialize each book keeping entry */
typedef void *(*cache_init_fn)(unsigned short capacity);

/* accumulator function to determine who to kick out (Note bene, assumes
 * return is a pointer to a cache_key_t; first passed NULL; assume must call
 * free(3) on returned key.) */
typedef void *(*cache_findvictim_fn)(cache_key_t k, void *bk, void *acc);

/* hook when removing an item, e.g. to free memory, bookkeeping */
typedef void (*cache_free_fn)(void *data, void *bk);

/* hook when accessing an item (called after item brought into cache) */
typedef void (*cache_access_fn)(void *ref, void *bk);

/* hook to fetch data from external source to store in cache (return bk) */
typedef void (*cache_fetch_fn)(void *ref, void **data, void **bk);




struct cache_method_t {
    cache_init_fn init_fn;
    cache_access_fn access_fn;
    cache_findvictim_fn findvictim_fn;
    cache_free_fn free_fn;
    cache_fetch_fn fetch_fn;
    cache_key_fn key_fn;
};

/* each entry in internal hash holds its reference, book keeping, data */
struct cache_entry_t {
    void *bk;   /* book keeping */
    void *data; /* actual cached */
/*     unsigned int size;  /\* data size *\/ */
};

struct cache_t {
    struct hash_t *h;  /* for "O(1)" lookup */
    struct cache_method_t meth; /* replacement algorithm hooks */
    unsigned int hit_cnt;
    unsigned int access_cnt;
    unsigned short max_cnt;
    unsigned long long int max_size;
};

struct cache_t *cache_init(unsigned short bucket_cnt,
                           unsigned short max_cnt,
                           unsigned long long int max_size,
                           struct cache_method_t meth);

/* input reference, return data */
void *cache_access(struct cache_t *c, void *ref);
unsigned long long int cache_get_maxsize(struct cache_t *c);
void cache_iter(struct cache_t *c,
                void *(*iter_fn)(cache_key_t key, void *entry, void *extra),
                void *initial_iter);
unsigned int cache_get_access_cnt(struct cache_t *c);
unsigned int cache_get_hit_cnt(struct cache_t *c);
void cache_reset_stats(struct cache_t *c);
#endif



/* TODO: constrain cache to a size, not just the number of entries. Since it's
 * currently constrained to the number of entries, that negates the O(1)
 * effect of hashing. */
