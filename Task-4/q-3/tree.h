//
// 315363366
//

#ifndef Q_3_TREE_H
#define Q_3_TREE_H

#include <stdio.h>
#include <stdlib.h>


typedef struct treeNode {
    int data;
    struct treeNode *parent;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

typedef struct tree {
    TreeNode *root;
    List leafList;
} Tree;

#define LEFT  0
#define RIGHT 1

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right);

void printTreeInorder(Tree tr);

void printInorderHelper(TreeNode *root);

void freeTree(Tree tr);

void freeTreeHelper(TreeNode *root);

Tree BuildTreeFromArrayWithLeafList(int *arr, int size);

Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data);

void printLeafList(Tree tr);

TreeNode *findParent(Tree tr, int parentData, int branchSelect);

Tree BuildTreeFromArray(int *arr, int size);

List creatListFromTreeLeaves(Tree tr);

TreeNode *findParentHelper(TreeNode *tNode, int parentData, int branchSelect);

void creatListFromTreeLeavesHelper(TreeNode *tNode, List *list);

#endif //Q_3_TREE_H
