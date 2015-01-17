#include <stdlib.h>
#include "bt.h"

bt_t *bt_add(bt_t *t, bt_cmp_fn cmp, void *d)
{
    if (t == NULL) {
        MALLOC_INIT(bt_t, n, 1);
        n->data = d;
        n->left = n->right = NULL;
        return n;
    }

    if (cmp(d, t->data) < 0)
        t->left = bt_add(t->left, cmp, d);
    else
        t->right = bt_add(t->right, cmp, d);
    return t;
}


static void *go_left(bt_t **t_)
{
    bt_t *t = *t_;
    return t->left ? go_left(&t->left) : bt_remove(t_);
}
static void *go_right(bt_t **t_)
{
    bt_t *t = *t_;
    return t->right ? go_right(&t->right) : bt_remove(t_);
}

void *bt_remove(bt_t **t_)
{
    ASSERT(*t_);
    bt_t *t = *t_;
    void *d = t->data;
    if (t->right && t->right->left == NULL) {
        /* pull up right directly */
        bt_t *right = t->right;
        t->data = right->data;
        t->right = t->right->right;
        FREE(right);
    } else if (t->left && t->left->right == NULL) {
        /* pull up left directly */
        bt_t *left = t->left;
        t->data = left->data;
        t->left = t->left->left;
        FREE(left);
    } else if (t->right) {
        /* go right and then all the way left */
        t->data = go_left(&t->right);
    } else if (t->left) {
        /* go left and then all the way right */
        t->data = go_right(&t->left);
    } else {
        /* no children */
        FREE(*t_);
        *t_ = NULL;
    }
    return d;
}

void bt_remove_if(bt_t **t_, bt_test_fn test, bt_free_fn fn)
{
    bt_t *t = *t_;
    if (t == NULL) return;

    if (test(t->data)) {
        void *data = bt_remove(t_);
        if (fn) fn(data);
        bt_remove_if(t_, test, fn);
    } else {
        bt_remove_if(&(*t_)->left, test, fn);
        bt_remove_if(&(*t_)->right, test, fn);
    }
}
void *bt_find(bt_t *t, bt_cmp_fn cmp, void *d);

void bt_free(bt_t *t, bt_free_fn fn)
{
    if (t == NULL) return;
    bt_free(t->left, fn);
    bt_free(t->right, fn);
    if (fn) fn(t->data);
    FREE(t);
}

uint bt_len(bt_t *);

void bt_map(bt_t *, bt_map_fn);

void *bt_fold(bt_t *t, bt_fold_fn fn, void *init)
{
    if (t == NULL) return init;
    init = fn(t->data, init);
    init = bt_fold(t->left, fn, init);
    init = bt_fold(t->right, fn, init);
    return init;
}
