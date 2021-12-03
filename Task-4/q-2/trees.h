//
// Created by Ariel Livshits on 01/12/2021.
//

#ifndef Q_2_TREES_H
#define Q_2_TREES_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct treeNode {
    unsigned char data;
    struct treeNode *left;
    struct treeNode *right;

} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;

TreeNode *createNewTreeNode(char data, TreeNode *left, TreeNode *right);

void printTreeInorder(Tree tr);

void printInorderHelper(TreeNode *root);

void freeTree(Tree tr);

void freeTreeHelper(TreeNode *root);

int buildExpressionTree(char *str, Tree *tr);

Tree buildExpressionTreeHelper(char *str);

bool isValid(char *str);

int findMiddleOperatorLocation(char *str);

int calcExpression(Tree tr);

int find(char *str, int startIndex, int endIndex);

TreeNode *helper(char *str, int startIndex, int endIndex);

int calcExpressionHelper(TreeNode* tNode);

#endif //Q_2_TREES_H
