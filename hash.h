#ifndef __HASH_H
#define __HASH_H

enum {
    HASH_LINEAR_PROBING
/*     HASH_QUADRATIC_PROBING */
/*     HASH_SEPARATE_CHAINING */
};

/* error codes */
enum {
    HASH_TRUE = 1,
    HASH_FALSE = 0,

    HASH_SUCCESS = 1,
    HASH_ERROR = -1
};

typedef unsigned long long int hash_key_t;

/* computes the has code */
typedef hash_key_t (*hash_key_fn)(void *d);
/* frees an element */
typedef void (*hash_free_fn)(void *d);

struct hash_elem_t {
    unsigned in_use : 1;
    hash_key_t key;
    void *val; /* NULL indicates empty bucket */
};
struct hash_t {
    hash_key_fn key_fn;
    hash_free_fn free_fn;
    unsigned short load; /* number of buckets taken */
    unsigned short bucket_cnt;
    struct hash_elem_t *buckets; /* bucket[i].val==NULL => empty bucket i */
    unsigned int overwrite : 1; /* 1 iff overwrite if element exists */
};


struct hash_t *hash_init(unsigned short bucket_cnt,
                         hash_key_fn key_fn, /* required */
                         hash_free_fn free_fn); /* optional (none: NULL) */
int hash_rehash(struct hash_t *h, unsigned short new_bucket_cnt);

/* insert/remove */
int hash_put(struct hash_t *h, void *d);
int hash_put_keyed(struct hash_t *h, hash_key_t key, void *d);
int hash_remove_key(struct hash_t *h, hash_key_t key);
int hash_remove(struct hash_t *h, void *d);

/* access */
void *hash_get(struct hash_t *h, hash_key_t key);
unsigned short hash_load(struct hash_t *h);
void *hash_(struct hash_t *h, unsigned short index);
void hash_iter(struct hash_t *h,
               void *(*iter_fn)(hash_key_t key, void *val, void *extra_param),
               void *extra_param);
void *hash_accum(struct hash_t *h,
                 void *(*accum_fn)(hash_key_t key, void *val, void *acc),
                 void *initial_acc);



/* tests */
int hash_contains(struct hash_t *h, hash_key_t key);
int hash_contains_val(struct hash_t *h, void *d);


#endif

/* Note, relies upon hash function to provide uniqueness so that actual values
 * are never compared.
 */
