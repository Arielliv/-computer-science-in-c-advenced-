#include <stdio.h>
#include <stdlib.h>
#include "../Header Files/trees.h"


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

