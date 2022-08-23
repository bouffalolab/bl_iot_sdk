#include "../../include/utils_rbtree.h"
#include <stdint.h>
#include <stdio.h>

struct iovec {
    void  *iov_base; // [XSI] Base address of I/O memory region
    size_t iov_len;  // [XSI] Size of region iov_base points to
};

static int my_cmp_cb(struct rb_tree *self, struct rb_node *node_a, struct rb_node *node_b) 
{
    struct iovec *a = (struct iovec *) node_a->value;
    struct iovec *b = (struct iovec *) node_b->value;

    return (a->iov_len > b->iov_len) - (a->iov_len < b->iov_len);
}

int main(int argc, char *argv[])
{
    struct rb_tree *tree = rb_tree_create(my_cmp_cb);
    if (tree) {
        // Use the tree here...
        for (int i = 0; i < 10; i++) {
            struct iovec *v = malloc(sizeof *v);
            v->iov_base = (void *) i;
            v->iov_len = i * i;
            // Default insert, which allocates internal rb_nodes for you.
            printf("[rb_tree_insert] insert %p with base %p len %d\r\n",
                    v,
                    v->iov_base,
                    v->iov_len
            );
            rb_tree_insert(tree, v);
        }

        // To f
        struct iovec *f = rb_tree_find(tree,
                & (struct iovec) { .iov_base = (void *) 7, .iov_len = 0 }
        );
        if (f) {
            printf("[rb_tree_find] found iovec %p(.iov_base = %p, .iov_len = %zu)\n", f, f->iov_base, f->iov_len);
        } else {
            printf("[rb_tree_find] iov_len 9 not found\n");
        }

        printf("[rb_tree_test] testing...\r\n");
        rb_tree_test(tree, f);

        f = rb_tree_find(tree,
                & (struct iovec) { .iov_base = (void *) 7, .iov_len = 10 }
        );
        if (f) {
            printf("[rb_tree_find] found iovec %p(.iov_base = %p, .iov_len = %zu)\n", f, f->iov_base, f->iov_len);
        } else {
            printf("[rb_tree_find] iov_len 10 not found\n");
        }

        printf("[rb_tree_size] is %d\r\n", rb_tree_size(tree));

        // Dealloc call can take optional parameter to notify on each node
        // being deleted so you can free the node and/or your object:
        rb_tree_dealloc(tree, NULL);
    }
}

