//
// Based on Julienne Walker's <http://eternallyconfuzzled.com/> rb_tree
// implementation.
//
// Modified by Mirek Rusin <http://github.com/mirek/rb_tree>.
//
// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>
//

#ifndef __UTILS_RBTREE_H__
#define __UTILS_RBTREE_H__

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

#ifndef RB_ITER_MAX_HEIGHT
#define RB_ITER_MAX_HEIGHT 64 // Tallest allowable tree to iterate
#endif

struct rb_node;
struct rb_tree;

typedef int  (*rb_tree_node_cmp_f) (struct rb_tree *self, struct rb_node *a, struct rb_node *b);
typedef void (*rb_tree_node_f)     (struct rb_tree *self, struct rb_node *node);

struct rb_node {
    int             red;     // Color red (1), black (0)
    struct rb_node *link[2]; // Link left [0] and right [1]
    void           *value;   // User provided, used indirectly via rb_tree_node_cmp_f.
};

struct rb_tree {
    struct rb_node    *root;
    rb_tree_node_cmp_f cmp;
    size_t             size;
    void              *info; // User provided, not used by rb_tree.
};

struct rb_iter {
    struct rb_tree *tree;
    struct rb_node *node;                     // Current node
    struct rb_node *path[RB_ITER_MAX_HEIGHT]; // Traversal path
    size_t          top;                      // Top of stack
    void           *info;                     // User provided, not used by rb_iter.
};

int             rb_tree_node_cmp_ptr_cb (struct rb_tree *self, struct rb_node *a, struct rb_node *b);
void            rb_tree_node_dealloc_cb (struct rb_tree *self, struct rb_node *node);

struct rb_node *rb_node_alloc           ();
struct rb_node *rb_node_create          (void *value);
struct rb_node *rb_node_init            (struct rb_node *self, void *value);
void            rb_node_dealloc         (struct rb_node *self);

struct rb_tree *rb_tree_alloc           ();
struct rb_tree *rb_tree_create          (rb_tree_node_cmp_f cmp);
struct rb_tree *rb_tree_init            (struct rb_tree *self, rb_tree_node_cmp_f cmp);
void            rb_tree_dealloc         (struct rb_tree *self, rb_tree_node_f node_cb);
void           *rb_tree_find            (struct rb_tree *self, void *value);
int             rb_tree_insert          (struct rb_tree *self, void *value);
int             rb_tree_remove          (struct rb_tree *self, void *value);
size_t          rb_tree_size            (struct rb_tree *self);

int             rb_tree_insert_node     (struct rb_tree *self, struct rb_node *node);
int             rb_tree_remove_with_cb  (struct rb_tree *self, void *value, rb_tree_node_f node_cb);

int             rb_tree_test            (struct rb_tree *self, struct rb_node *root);

struct rb_iter *rb_iter_alloc           ();
struct rb_iter *rb_iter_init            ();
struct rb_iter *rb_iter_create          ();
void            rb_iter_dealloc         (struct rb_iter *self);
void           *rb_iter_first           (struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_last            (struct rb_iter *self, struct rb_tree *tree);
void           *rb_iter_next            (struct rb_iter *self);
void           *rb_iter_prev            (struct rb_iter *self);

#endif
