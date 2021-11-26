//
// Created by Ariel Livshits on 26/11/2021.
//
// #pragma once - will do the same
#ifndef T1_TREES_H
#define T1_TREES_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *right;
    struct TreeNode *left;
} TreeNode;

typedef struct Tree {
    TreeNode *root;
} Tree;


bool hasPathSum(Tree tr, int sum);

bool hasPathSumHelper(TreeNode *tNode, int sum);

int treeDiameter(Tree tr);

int treeDiameterHelper(TreeNode *tNode, int *height);

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right);

Tree BuildTree1();

Tree BuildTree2();

void FreeTree(Tree tr);

void FreeTreeRec(TreeNode *root);

int max(int a, int b);

#endif //T1_TREES_H

