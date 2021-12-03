#include <stdio.h>
#define SWAP(type, a, b) {type temp;temp =a; a=b; b=temp;}

// \ drop a line
// #define SWAP(type, a, b) {type temp;\temp =1; a=b;\ b=temp;}

int main(){
    int x = 5;
    int y = 6;
    SWAP(int, x, y);
    printf("x = %d, y = %d", x, y);
}