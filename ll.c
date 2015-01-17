#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jm.h"
#include "ll.h"

ll_t *ll_add_to_back(ll_t *pn, void *d)
{
    if (pn == NULL) {
        MALLOC_INIT(ll_t, pnew, 1);
        pnew->data = d;
        pnew->next = NULL;
        return pnew;
    } else {
        pn->next = ll_add_to_back(pn->next, d);
        return pn;
    }
}





ll_t *ll_add_to_front(ll_t *pn, void *d)
{
    MALLOC_INIT(ll_t, pnew, 1);
    pnew->data = d;
    pnew->next = pn;
    return pnew;
}





ll_t *ll_add(ll_t *pn, void *d)
{
    return ll_add_to_front(pn, d);
}





ll_t *ll_add_sort(ll_t *n, ll_cmp_fn cmp_fn, void *d)
{

    if (n == NULL) {
        MALLOC_INIT(ll_t, pnew, 1);
        pnew->data = d;
        pnew->next = NULL;
        return pnew;
    }

    if (cmp_fn(d, n->data) <= 0) {
        /* belongs here or before */
        MALLOC_INIT(ll_t, pnew, 1);
        pnew->data = d;
        pnew->next = n;
        return pnew;
    } else {
        /* belongs later */
        n->next = ll_add_sort(n->next, cmp_fn, d);
        return n;
    }
}






void *ll_remove_first(ll_t **ppn)
{
    ll_t *first;
    void *ret;

    if (*ppn == NULL)
        return NULL;

    first = *ppn;           /* Get first node */
    *ppn = (*ppn)->next;    /* Move the head of the list */
    ret = first->data;      /* save pointer to its data */
    FREE(first);         /* free node */
    return ret;             /* return data */
}






static int find_index(ll_t *lst, ll_test_fn test, int ind)
{
    if (lst == NULL) return -1; /* not found */
    return test(lst->data) ? ind : find_index(lst->next, test, ind + 1);
}


int ll_find_index(ll_t *lst, ll_test_fn test)
{
    return find_index(lst, test, 0);
}


void *ll_find_sorted(ll_t *lst, ll_cmp_fn cmp_fn, void *d)
{
    if (lst == NULL)
        return NULL;

    int cmp = cmp_fn(d, lst->data);
    if (cmp < 0)
        return NULL; /* should have hit it already */
    else if (cmp == 0)
        return lst->data;
    else
        return ll_find_sorted(lst->next, cmp_fn, d);
}









void *ll_find(ll_t *lst, ll_test_fn test_fn)
{
    if (lst == NULL)
        return NULL;
    
    return test_fn(lst->data) ? lst->data : ll_find(lst->next, test_fn);
}







/* visit in same order as ll_map */
void ll_free(ll_t *lst, ll_free_fn free_fn)
{
    if (lst == NULL) return;
    if (free_fn) free_fn(lst->data); /* free data? */
    ll_free(lst->next, free_fn);
    FREE(lst);
}








bool ll_is_empty(ll_t *n)
{
    return (n == NULL);
}





uint ll_len(ll_t *pn)
{
    if (pn == NULL) return 0;
    return 1 + ll_len(pn->next);
}





void *ll_peek(ll_t *n)
{
    return n->data;
}




ll_t *ll_next(ll_t *n)
{
    return n->next;
}





void *ll_peek_nth(ll_t *p, unsigned int n)
{
    if (n == 0)
        return p->data;
    else if (p->next != NULL)
        return ll_peek_nth(p->next, n-1);
    else
        return NULL; /* not found */
}







void *ll_remove(ll_t **lst, ll_test_fn test)
{
    /* done? */
    if (*lst == NULL)
        return NULL;

    /* is this it? */
    if (test((*lst)->data)) {
        /* remove it */
        return ll_remove_first(lst);
    } else {
        /* keep looking */
        ll_t **ptr_to_next = &(*lst)->next;
        return ll_remove(ptr_to_next, test);
    }
}

void ll_remove_if(ll_t **lst, ll_test_fn test, ll_free_fn free)
{
    /* done? */
    if (*lst == NULL) return;

    /* is this one? */
    if (test((*lst)->data)) {
        free(ll_remove_first(lst));
        ll_remove_if(lst, test, free);
    } else {
        ll_remove_if(&(*lst)->next, test, free);
    }
}
  




bool ll_any(ll_t *lst, ll_test_fn test_fn)
{
    if (lst == NULL)
        return false;

    return test_fn(lst->data) || ll_any(lst->next, test_fn);
}

bool ll_all(ll_t *lst, ll_test_fn test_fn)
{
    if (lst == NULL)
        return true;

    return test_fn(lst->data) && ll_all(lst->next, test_fn);
}







static void ll_gen_(ll_t *lst, ll_mapi_fn fn, int i)
{
    if (lst == NULL) return;
    fn(lst->data, i);
    ll_gen_(lst->next, fn, i + 1); /* next */
}
void ll_gen(ll_t *lst, ll_mapi_fn fn) { ll_gen_(lst, fn, 0); }


void ll_map(ll_t *lst, ll_map_fn map_fn)
{
    if (lst == NULL)
        return;

    map_fn(lst->data);
    ll_map(lst->next, map_fn);
}







ll_t *ll_concat(ll_t *first, ll_t *last)
{
    if (first == NULL)
        return last; /* put here */

    first->next = ll_concat(first->next, last);
    return first;
}








ll_t *ll_filter(ll_t *lst, ll_test_fn test)
{
    if (lst == NULL)
        return NULL;

    if (test(lst->data)) {
        /* keep this node */
        MALLOC_INIT(ll_t, new_, 1);
        new_->next = ll_filter(lst->next, test);
        new_->data = lst->data;
        return new_;
    } else {
        return ll_filter(lst->next, test);
    }
}







ll_t *ll_filter_set(ll_t **lst, ll_test_fn test)
{
    if (*lst == NULL)
        return NULL;

    if (test((*lst)->data)) {
        /* keep this node */
        void *data = ll_remove_first(lst);
        MALLOC_INIT(ll_t, new_, 1);
        new_->data = data;
        new_->next = ll_filter_set(lst, test);
        return new_;
    } else {
        ll_t **next = &(*lst)->next;
        return ll_filter_set(next, test);
    }
}









void *ll_foldl(ll_fold_fn fn, void *init, ll_t *lst)
{
    if (lst == NULL) {
        return init;
    } else {
        return ll_foldl(fn, fn(lst->data, init), lst->next);
    }
}



void *ll_foldr(ll_fold_fn fn, void *init, ll_t *lst)
{
    if (lst == NULL) {
        return init;
    } else {
        return fn(lst->data, ll_foldr(fn, init, lst->next));
    }
}







void ll_move(ll_t **from, ll_t **to)
{
    void *p = ll_remove_first(from);
    *to = ll_add_to_front(*to, p);
}




ll_t *ll_update(ll_t *cur, ll_update_fn fn)
{
    if (!cur) return NULL;

    ll_t *cur_ = fn(cur->data);
    FREE(cur);
    return ll_concat(cur_, ll_update(cur->next, fn));
}



static void **g_arr = NULL;
inline static void write_arr(void *d, int i)
{
    g_arr[i] = d;
}
void *ll2array(ll_t *lst)
{
    MALLOC_INIT(void *, arr, ll_len(lst));
    g_arr = arr;
    ll_gen(lst, write_arr);
    return arr;
}
