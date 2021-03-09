#define BinarySearchTree_h

#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode {
    void *element;
    int freq;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef int (*TreeComparator)(void *element1, void *element2);

typedef void (*printNode)(void*);

int add(TreeNode **root, void *element, TreeComparator f);
int find(TreeNode *root, void *key, TreeComparator f, void **element);
void in_order(TreeNode *root, printNode print);
void pre_order(TreeNode *root, printNode print);
void post_order(TreeNode *root, printNode print);
int removeTreeNode(TreeNode **root, void *key, TreeComparator f);
int height (TreeNode *root);
void destroy (TreeNode **root);

//#endif