#include <stdio.h>

//define number of cols and rows
#define NUMBER_OF_COLS 10
#define NUMBER_OF_ROWS 10

int countIndentionAmount(int num);

void printMulBoard();

// main - prints multiply board of 10
int main() {
    printMulBoard();
    return 0;
}

//count how much indention needed and return it
int countIndentionAmount(int num) {
    int count = 0;
    do {
        num /= 10;
        ++count;
    } while (num != 0);
    return count;
}

//print multiply board
void printMulBoard() {
    //loop from 1 to 10 for rows multiply, add a brake line in each iteration
    for (int i = 1; i <= NUMBER_OF_COLS; i++) {
        //loop from 1 to 10 for cols multiply, multiply col vs row value and prints it
        for (int j = 1; j <= NUMBER_OF_ROWS; j++) {
            //indention to right
            int indentionAmount = countIndentionAmount(j * 10);
            if (indentionAmount == 2) {
                printf("%*d ", indentionAmount, j * i);
//            } else {
                printf("%*d", indentionAmount, j * i);
            }

        }
        printf("\n");
    }
}
