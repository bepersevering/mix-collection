#include <stdlib.h>
#include "binarytree.h"

link make_node(unsigned char item) {
  link p = malloc(sizeof *p);
  p->item = item;
  p->left = p->right = NULL;
  return p;
}

void free_node(link t) {
  free(t);
}

link init(unsigned char VLR[], unsigned char LVR[], int n) {
  link t;
  int k;
  if (n <= 0) {
    return NULL;
  }

  // find root in LVR
  for (k = 0; VLR[0] != LVR[k]; k++) {
    
  }

  t = make_node(VLR[0]);
  t->left = init(VLR + 1, LVR, n - k -1);
  t->right = init(VLR + k + 1, LVR + k + 1, n - k - 1);
  return t;
}

void pre_order(link t, void (*visit)(link)) {
  if (t == NULL) {
    return;
  }
  visit(t);
  pre_order(t->left, visit);
  pre_order(t->right, visit);
}

void in_order(link t, void (*visit)(link)) {
  if (t == NULL) {
    return;
  }
  
  in_order(t->left, visit);
  visit(t);
  in_order(t->right, visit);
}

void post_order(link t, void (*visit)(link)){
  if (t == NULL) {
    return;
  }
  post_order(t->left, visit);
  post_order(t->right, visit);
  visit(t);
}

int count(link t) {
  if (!t) {
    return 0;
  }
  return 1 + count(t->left) + count(t->right);
}

int depth(link t) {
  if (!t) {
    return 0;
  }
  int leftDepth = 1 + depth(t->left);
  int rightDepth = 1 + depth(t->right);

  return leftDepth > rightDepth ? leftDepth : rightDepth;
}

void destroy(link t) {
  post_order(t, free_node);
}