//
// Created by Ariel Livshits on 30/11/2021.
//

#ifndef T_1_TREES_H
#define T_1_TREES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    unsigned int data;
    struct treeNode *left;
    struct treeNode *right;

} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right);

void printTreeInorder(Tree tr);

void printInorderHelper(TreeNode *root);

void freeTree(Tree tr);

void freeTreeHelper(TreeNode *root);

Tree BuildTreeFromArray(int *arr, int size);

#endif //T_1_TREES_H
