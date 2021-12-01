//
// Created by Ariel Livshits on 30/11/2021.
//

#include "trees.h"
#include "utils.h"

void freeTree(Tree tr) {
    freeTreeHelper(tr.root);
}


void freeTreeHelper(TreeNode *root) {
    if (root != NULL) {
        freeTreeHelper(root->left);
        freeTreeHelper(root->right);
        free(root);
    }
}

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right) {
    TreeNode *res = (TreeNode *) malloc(sizeof(TreeNode));
    checkMemoryAllocation(res);

    res->data = data;
    res->left = left;
    res->right = right;

    return res;
}

void printTreeInorder(Tree tr) {
    printInorderHelper(tr.root);
    printf("\n");
}

void printInorderHelper(TreeNode *root) {
    if (root == NULL)
        return;
    else {
        printInorderHelper(root->left);
        printf("%d ", root->data);
        printInorderHelper(root->right);
    }
}

Tree BuildTreeFromArray(int *arr, int size) {
    Tree tr;
    Tree leftTr;
    Tree rightTr;
    int index;
    index = size / 2;
    tr.root = createNewTreeNode(arr[index], NULL, NULL);
    if (size == 1) {
        tr.root->data = arr[0];
        tr.root->left = NULL;
        tr.root->right = NULL;
    } else {
        tr.root->data = arr[index];
        if (arr[index / 2] != -1) {
            leftTr = BuildTreeFromArray(arr, index);
            tr.root->left = leftTr.root;
        } else {
            tr.root->left = NULL;
        }
        if (arr[index + (index / 2) + 1] != -1) {
            rightTr = BuildTreeFromArray(arr + index + 1, index);
            tr.root->right = rightTr.root;
        } else {
            tr.root->right = NULL;
        }
    }
    return tr;
}