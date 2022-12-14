#ifndef BST_H
#define BST_H

typedef struct node *link;
struct node {
  unsigned int item;
  link left, right;
};

link search(link t, unsigned int key);
link insert(link t, unsigned int key);
link delete(link t, unsigned int key);
void print_tree(link t);
  

#endif // !BST_H
