//
// 315363366
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

TreeNode *createNewTreeNode(char data, TreeNode *left, TreeNode *right) {
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
        printf("%c ", root->data);
        printInorderHelper(root->right);
    }
}

int buildExpressionTree(char *str, Tree *tr) {
    bool isTreeValid;
    tr->root = NULL;
    isTreeValid = isValid(str);
    if (isTreeValid) {
        *tr = buildExpressionTreeHelper(str);
        //        tr->root = helper(str,0, strlen(str)-1);
    }
    return isTreeValid;
}

bool isValid(char *str) {
    int index = 0;
    char curr = str[index];
    int BracketsCounter = 0;
    while (curr != '\0') {
        if (isBracketsSign(curr)) {
            if (curr == '(') {
                BracketsCounter++;
            } else {
                BracketsCounter--;
            }
        } else if (!isOperatorSign(curr) && !isOneDigitNumber(curr)) {
            return false;
        }
        index++;
        curr = str[index];
    }
    if (BracketsCounter == 0) {
        return true;
    } else {
        return false;
    }
}


int findMiddleOperatorLocation(char *str) {
    int leftBracketsCounter = 0, rightBracketsCounter = 0;
    int index = 0;
    bool found = false;
    char curr = str[index];
    while ((curr != '\0') && (!found)) {
        if (isBracketsSign(curr)) {
            if (curr == '(') {
                leftBracketsCounter++;
            } else {
                rightBracketsCounter++;
            }
        } else if (isOperatorSign(curr) && leftBracketsCounter == rightBracketsCounter + 1) {
            found = true;
        }
        index++;
        curr = str[index];
    }
    return index - 1;
}

Tree buildExpressionTreeHelper(char *str) {
    int location;

    Tree resTree;

    TreeNode *tNode = createNewTreeNode(-1, NULL, NULL);

    if (strlen(str) == 1) {
        tNode->data = str[0];
        tNode->left = tNode->right = NULL;
    } else {
        // find the correct operator sign index
        location = findMiddleOperatorLocation(str);
        tNode->data = str[location];
        char temp = str[location];

        // cut str in operator sign index
        str[location] = '\0';
        tNode->left = buildExpressionTreeHelper(str + 1).root;

        str[location] = temp;
        temp = str[strlen(str) - 1];

        str[strlen(str) - 1] = '\0';
        tNode->right = buildExpressionTreeHelper(str + location + 1).root;
        str[strlen(str) + 1] = '\0';
        str[strlen(str)] = temp;
    }
    resTree.root = tNode;
    return resTree;
}

int calcExpression(Tree tr) {
    return calcExpressionHelper(tr.root);
}

int calcExpressionHelper(TreeNode *tNode) {
    if (tNode == NULL) {
        return 0;
    } else if (tNode->left == NULL && tNode->right == NULL) {
        return charToInt(tNode->data);
    } else {
        return calc(calcExpressionHelper(tNode->left), tNode->data, calcExpressionHelper(tNode->right));
    }
}
