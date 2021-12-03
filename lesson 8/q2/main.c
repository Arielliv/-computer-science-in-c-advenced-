#include <stdio.h>

int main(int argc, char *argv[]) {
    int var1;
    float var2;
    char op;
    sscanf(argv[1], "%d", &var1);
    // also can be done - var1 = atoi(argv[1]);
    sscanf(argv[2], "%c", &op);
    // also can be done - op = argv[2][0];
    sscanf(argv[3], "%f", &var2);
    printf("%d + %f = %.3f\n", var1, var2, var1 + var2);
    return 0;
}
