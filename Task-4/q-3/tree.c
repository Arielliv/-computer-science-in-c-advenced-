//
// 315363366
//
#include "list.h"
#include "tree.h"
#include "util.h"

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

Tree BuildTreeFromArrayWithLeafList(int *arr, int size) {
    Tree tr = BuildTreeFromArray(arr, size);
    makeEmptyList(&tr.leafList);
    tr.leafList = creatListFromTreeLeaves(tr);
    return tr;
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

List creatListFromTreeLeaves(Tree tr) {
    List newList;
    makeEmptyList(&newList);
    creatListFromTreeLeavesHelper(tr.root, &newList);
    return newList;
}

void creatListFromTreeLeavesHelper(TreeNode *tNode, List *list) {
    if (tNode == NULL) {
        return;
    } else if (tNode->left == NULL && tNode->right == NULL)
        insertDataToEndList(list, tNode->data);
    else {
        creatListFromTreeLeavesHelper(tNode->left, list);
        creatListFromTreeLeavesHelper(tNode->right, list);
    }
}

Tree AddLeaf(Tree tr, TreeNode *p, int branchSelect, int data) {
    if (branchSelect == RIGHT) {
        p->right = createNewTreeNode(data, NULL, NULL);
    } else {
        p->left = createNewTreeNode(data, NULL, NULL);
    }
    int index = findListNode(&tr.leafList, p->data);
    if (index == -1) {
        if (branchSelect == RIGHT) {
            insertDataToEndList(&tr.leafList, data);
        } else {
            insertDataToStartList(&tr.leafList, data);
        }
    } else {
        updateDataToPlaceInList(&tr.leafList, data, index);
    }

    return tr;
}

void printLeafList(Tree tr) {
    printList(tr.leafList);
}

TreeNode *findParent(Tree tr, int parentData, int branchSelect) {
    return findParentHelper(tr.root, parentData, branchSelect);
}

TreeNode *findParentHelper(TreeNode *tNode, int parentData, int branchSelect) {
    if (tNode == NULL) {
        return NULL;
    } else {
        if (tNode->data == parentData) {
            if (branchSelect == RIGHT && tNode->right == NULL) {
                return tNode;
            } else if (tNode->left == NULL) {
                return tNode;
            }
//            if (tNode->left == NULL && tNode->right == NULL) {
//                return tNode;
//            }
        } else {
            TreeNode *left = findParentHelper(tNode->left, parentData, branchSelect);
            TreeNode *right = findParentHelper(tNode->right, parentData, branchSelect);
            if (left != NULL) {
                return left;
            } else {
                return right;
            }
        }
    }

}