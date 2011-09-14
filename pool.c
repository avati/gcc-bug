#include <stdlib.h>
#include <assert.h>
#include <stdio.h>


struct list_head {
        struct list_head *next;
        struct list_head *prev;
};


struct pool {
        struct list_head  list;
        int               count;
        unsigned long     size;
        void             *slab;
};


char global_init;


/* Uncommenting the prototype with attribute masks the bug */
//void *__calloc (size_t nmemb, size_t size) __attribute_malloc__;

void *
__calloc (size_t nmemb, size_t size)
{
        return calloc (nmemb, size);
}


void
pool_validate (struct pool *pool)
{
        struct list_head *list = NULL;
        struct list_head *head = NULL;
        int               count = 0;

        head = &pool->list;

        for (list = head->next; list != head; list = list->next) {
                count++;
        }

        if (pool->count == count) {
                printf ("GOOD :)\n");
        } else {
                printf ("BAD :(\n");
        }
}


struct pool *
pool_new (int size, int count)
{
        struct pool      *pool = NULL;
        void             *slab = NULL;
        int               i = 0;
        struct list_head *list = NULL;
        struct list_head *head = NULL;


        /* commenting the below line hides the bug */
        do { if (!global_init) break; } while (0);

        pool = __calloc (sizeof (*pool), 1);
        if (!pool)
                return NULL;

        head = &pool->list;
        head->next = head->prev = head;

        pool->size = size;
        pool->count = count;

        slab = __calloc (count, size);
        if (!slab) {
                free (pool);
                return NULL;
        }

        for (i = 0; i < count; i++) {
                list = slab + (i * (size));

                list->next = list->prev = list;

                list->next = head;
                list->prev = head->prev;
                list->next->prev = list;
                list->prev->next = list;
        }

        pool->slab = slab;

        return pool;
}


int main (int argc, char *argv[])
{
        struct pool *pool = NULL;

        pool = pool_new (1024, 1024);

        pool_validate (pool);

        return 0;
}
