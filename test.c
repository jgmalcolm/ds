#include <stdio.h>
#include "twul.h"

static bool test(void *a) {
    return (int)a < 30;
}

static void print_leaf(void *_a)
{
    int a = (int)_a;
    printf(" %d", a);
}

static void twul_print_(twul_t *t, uint lvl)
{
    if (t == NULL) return;
    for (uint i = 0; i < lvl; i++) printf(" ");
    printf("%ld:", t->key);
    ll_map(t->leaves, print_leaf);
    printf("\n");
    twul_print_(t->left, lvl + 1);
    twul_print_(t->right, lvl + 1);
}
static void twul_print(twul_t *t) { twul_print_(t, 0); }

int main(void)
{
    twul_t *t = NULL;
    t = twul_add(t, 50, (void *)52);
    t = twul_add(t, 20, (void *)23);
    t = twul_add(t, 40, (void *)48);
    t = twul_add(t, 50, (void *)51);
    t = twul_add(t, 10, (void *)10);
    t = twul_add(t, 40, (void *)42);
    t = twul_add(t, 50, (void *)58);
    t = twul_add(t, 30, (void *)31);

    twul_print(t);

    int a = (int)twul_remove(&t, 20, test);
    printf("%d\n", a);

    twul_print(t);
    twul_free(t, NULL);

    return 0;
}
