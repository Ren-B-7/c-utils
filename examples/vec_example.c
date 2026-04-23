#include <stdio.h>
#include "../src/vec.h"

/* Create a vector type for ints */
VEC_DECL(int_vec_t, int);

static int cmp_ints(const void *a, const void *b) {
    const int *x = a;
    const int *y = b;
    return (*x > *y) - (*x < *y);
}

int main(void) {
    int_vec_t vec = {0};

    /* Push values */
    VEC_PUSH(vec, 10);
    VEC_PUSH(vec, 20);
    VEC_PUSH(vec, 30);
    VEC_PUSH(vec, 40);

    printf("Initial vector:\n");
    VEC_FOREACH(int, item, vec) {
        printf("%d ", *item);
    }
    printf("\n");

    /* Insert into middle */
    VEC_INSERT(vec, 1, 15);

    printf("After insert at index 1:\n");
    VEC_FOREACH(int, item, vec) {
        printf("%d ", *item);
    }
    printf("\n");

    /* Remove element */
    VEC_REMOVE(vec, 2);

    printf("After remove index 2:\n");
    VEC_FOREACH(int, item, vec) {
        printf("%d ", *item);
    }
    printf("\n");

    /* Accessors */
    printf("First: %d\n", VEC_FIRST(vec));
    printf("Last: %d\n", VEC_LAST(vec));
    printf("Index 1: %d\n", VEC_GET(vec, 1));

    /* Set */
    VEC_SET(vec, 1, 99);

    printf("After set index 1 = 99:\n");
    VEC_FOREACH(int, item, vec) {
        printf("%d ", *item);
    }
    printf("\n");

    /* Sort */
    VEC_SORT(vec, cmp_ints);

    printf("After sort:\n");
    VEC_FOREACH(int, item, vec) {
        printf("%d ", *item);
    }
    printf("\n");

    /* Pop */
    int popped = VEC_POP(vec);
    printf("Popped: %d\n", popped);

    printf("Final vector:\n");
    VEC_FOREACH(int, item, vec) {
        printf("%d ", *item);
    }
    printf("\n");

    /* Free memory */
    VEC_FREE(vec);

    return 0;
}
