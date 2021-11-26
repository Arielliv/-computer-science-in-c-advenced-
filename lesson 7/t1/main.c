#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode* right;
    struct TreeNode* left;
}TreeNode;

typedef struct Tree
{
    TreeNode* root;
}Tree;

bool hasPathSum(Tree tr, int sum);

int treeDiameter(Tree tr);

TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right);
Tree BuildTree1();
Tree BuildTree2();

void FreeTree(Tree tr);
void FreeTreeRec(TreeNode *root);

void main()
{
    Tree tr1 = BuildTree1();
    Tree tr2 = BuildTree2();

    hasPathSum(tr1, 22) ? printf("True\n") : printf("False\n");
    hasPathSum(tr1, 30) ? printf("True\n") : printf("False\n");
    printf("Tree diameter is: %d\n", treeDiameter(tr2));

    FreeTree(tr1);
    FreeTree(tr2);
}

bool hasPathSum(Tree tr, int sum)
{

}

int treeDiameter(Tree tr)
{

}

TreeNode* createNewTreeNode(int data, TreeNode* left, TreeNode* right)
{
    TreeNode* res = (TreeNode*)malloc(sizeof(TreeNode));

    res->data = data;
    res->left = left;
    res->right = right;

    return res;
}

Tree BuildTree1()
{
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

Tree BuildTree2()
{
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

void FreeTree(Tree tr)
{
    FreeTreeRec(tr.root);
}

void FreeTreeRec(TreeNode *root)
{
    if (root != NULL)
    {
        FreeTreeRec(root->left);
        FreeTreeRec(root->right);
        free(root);
    }
}