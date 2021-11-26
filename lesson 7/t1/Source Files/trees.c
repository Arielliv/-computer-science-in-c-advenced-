//
// Created by Ariel Livshits on 26/11/2021.
//

#include <stdbool.h>
#include "../Header Files/trees.h"

int max(int a, int b) {
    return a > b ? a : b;
}

bool hasPathSum(Tree tr, int sum) {
    return hasPathSumHelper(tr.root, sum);
}

bool hasPathSumHelper(TreeNode *tNode, int sum) {
    if (tNode == NULL) {
        if (sum == 0) {
            return true;
        } else {
            return false;
        }
    }
//    if (tNode->left == NULL && tNode->right == NULL) {
//        if (tNode->data == sum && sum > 0) {
//            return true;
//        } else {
//            return false;
//        }
//    } else {
    sum -= tNode->data;
    bool leftResult = hasPathSumHelper(tNode->left, sum);
    bool rightResult = hasPathSumHelper(tNode->right, sum);
    return (leftResult || rightResult);
//    }

}

int treeDiameter(Tree tr) {
    int height = 0;
    return treeDiameterHelper(tr.root, &height);
}

int treeDiameterHelper(TreeNode *tNode, int *height) {
    int heightLeft = 0, heightRight = 0;
    int diameterLeft = 0, diameterRight = 0;

    if (tNode == NULL) {
        *height = 0;
        return 0;
    } else {
        diameterLeft = treeDiameterHelper(tNode->left, &heightLeft);
        diameterRight = treeDiameterHelper(tNode->right, &heightRight);
        *height = max(heightLeft, heightRight) + 1;

        return max(heightLeft + heightRight, max(diameterLeft, diameterRight));
    }
}

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right) {
    TreeNode *res = (TreeNode *) malloc(sizeof(TreeNode));

    res->data = data;
    res->left = left;
    res->right = right;

    return res;
}

Tree BuildTree1() {
    Tree T;
    TreeNode *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8;

    n1 = createNewTreeNode(3, NULL, NULL);
    n2 = createNewTreeNode(11, NULL, NULL);
    n3 = createNewTreeNode(2, n1, n2);
    n4 = createNewTreeNode(15, NULL, NULL);
    n5 = createNewTreeNode(4, n3, n4);
    n6 = createNewTreeNode(55, NULL, NULL);
    n7 = createNewTreeNode(3, NULL, n6);
    n8 = createNewTreeNode(5, n5, n7);

    T.root = n8;

    return T;
}

Tree BuildTree2() {
    Tree T;
    TreeNode *n1, *n2, *n3, *n4, *n5, *n6, *n7, *n8, *n9;

    n1 = createNewTreeNode(3, NULL, NULL);
    n2 = createNewTreeNode(12, n1, NULL);
    n3 = createNewTreeNode(2, NULL, n2);
    n4 = createNewTreeNode(1, NULL, NULL);
    n5 = createNewTreeNode(8, NULL, n4);
    n6 = createNewTreeNode(15, NULL, n5);
    n7 = createNewTreeNode(4, n3, n6);
    n8 = createNewTreeNode(6, NULL, NULL);
    n9 = createNewTreeNode(10, n7, n8);

    T.root = n9;

    return T;
}

void FreeTree(Tree tr) {
    FreeTreeRec(tr.root);
}

void FreeTreeRec(TreeNode *root) {
    if (root != NULL) {
        FreeTreeRec(root->left);
        FreeTreeRec(root->right);
        free(root);
    }
}