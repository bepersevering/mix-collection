#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


link make_node(unsigned char item) {
    link p = malloc(sizeof *p);
    p->item = item;
    p->left = p->right = NULL;
    return p;
}

void free_node(link t) {
    free(t);
}

link search(link t, unsigned char key) {
    if (!t) {
        return NULL;
    }
    if (t->item == key) {
        return t;
    }
    if (t->item < key) {
        return search(t->left, key);
    }
    if (t->item > key) {
        return search(t->right, key);
    }
    return NULL;
}

link insert(link t, unsigned char key) {
    if (!t) {
        return make_node(key);
    }

    if (t->item > key) {
        t->right = insert(t->right, key);
    } else {
        t->left = insert(t->left, key);
    }
    return t;
}

link delete(link t, unsigned char key) {
    link p;
    if (!t) {
        return NULL;
    }
    if (t->item > key) {
        t->left = delete(t->left, key);
    } else if (t->item < key) {
        t->right = delete(t->right, key);
    } else {
        // t->item == key
        if (t->left == NULL && t->right == NULL) {
            free_node(t);
            t = NULL;
        } else if (t->left) {
            // 从左子树的右子树里面找到最右边（最大的）的
            for (p = t->right; p->right; p = p->right) {
            }
            t->item = p->item;
            t->left = delete(t->left, t->item);
        } else {
            // 从右子树的左子树里面找到最左边（最小的）的
            for (p = t->left; p->left; p = p->left) {
            }
            t->item = p->item;
            t->right = delete(t->right, t->item);
        }
    }

    return t;
}

void print_tree(link t) {
    if (t) {
        printf("(");
        printf("%d", t->item);
        print_tree(t->left);
        print_tree(t->right);
        printf(")");
    } else {
        printf("()");
    }
}
