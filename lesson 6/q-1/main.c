#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    int data;
    struct treeNode *right;
    struct treeNode *left;
} TreeNode;

typedef struct tree {
    TreeNode *root;
} Tree;

void PrintInorder(Tree tr);

void PrintInorderRec(TreeNode *root);

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right);

Tree BuildTree();

void FreeTree(Tree tr);

void FreeTreeRec(TreeNode *root);

void printLeavesHelper(TreeNode *root);

void printLeaves(Tree tr);

void RearrangeHelper(TreeNode *root);

void swapTNodes(TreeNode *tNode1, TreeNode *tNode2);

void Rearrange(Tree *tr);

void main() {
    Tree tr = BuildTree();

    printf("The leaves are:\n");
    printLeaves(tr);

    printf("\n");

    ////////////////////////////////////////////////////

    PrintInorder(tr);
    Rearrange(&tr);
    PrintInorder(tr);

    FreeTree(tr);
}

void printLeavesHelper(TreeNode *root) {
    if (root == NULL)
        return;
    if (root->left != NULL)
        printLeavesHelper(root->left);
    if (root->right != NULL)
        printLeavesHelper(root->right);
    else
        printf("%d ", root->data);
}

void printLeaves(Tree tr) {
    printLeavesHelper(tr.root);
}

void swapTNodes(TreeNode *tNode1, TreeNode *tNode2) {
    int tempTNodeData;

    tempTNodeData = tNode1->data;
    tNode1->data = tNode2->data;
    tNode2->data = tempTNodeData;
}

void RearrangeHelper(TreeNode *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return;

    if (root->left != NULL && root->right == NULL) {
        RearrangeHelper(root->left);
        if (root->left->data > root->data) {
            swapTNodes(root->left, root);
        }
    }

    if (root->left == NULL && root->right != NULL) {
        RearrangeHelper(root->right);
        if (root->right->data > root->data) {
            swapTNodes(root->right, root);
        }
    } else {
        RearrangeHelper(root->left);
        RearrangeHelper(root->right);
        if (root->left->data > root->right->data && root->left->data > root->data) {
            swapTNodes(root->left, root);
        } else if (root->right->data > root->left->data && root->right->data > root->data) {
            swapTNodes(root->right, root);
        }
    }
}

void Rearrange(Tree *tr) {
    RearrangeHelper(tr->root);
}

void PrintInorder(Tree tr) {
    PrintInorderRec(tr.root);
    printf("\n");
}

void PrintInorderRec(TreeNode *root) {
    if (root == NULL)
        return;
    else {
        PrintInorderRec(root->left);
        printf("%d ", root->data);
        PrintInorderRec(root->right);
    }
}

TreeNode *createNewTreeNode(int data, TreeNode *left, TreeNode *right) {
    TreeNode *res = (TreeNode *) malloc(sizeof(TreeNode));

    res->data = data;
    res->left = left;
    res->right = right;

    return res;
}

Tree BuildTree() {
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



//void printLeaves(Tree tr) {
//    printLeavesHelper(tr.root);
//}
//
//void printLeavesHelper(TreeNode *tNode) {
//    if (tNode == NULL) {
//        return;
//    }
//    if (tNode->left != NULL) {
//        printLeavesHelper(tNode->left);
//    }
//    if (tNode->right != NULL) {
//        printLeavesHelper(tNode->right);
//    }
//    if (tNode->left == NULL && tNode->right == NULL) {
//        printf("%d ", tNode->data);
//    }
//}