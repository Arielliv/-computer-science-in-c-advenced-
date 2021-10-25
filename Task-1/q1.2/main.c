#include <stdio.h>

// return amount of indention according to num
int countIndentionAmount(int num);

//print mul table
void printMultTable();


// main - prints multiply board of 10
int main() {
    int maxMult;

    printf("Please enter number:\n");

    scanf("%d", &maxMult);

    printMultTable(maxMult);

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
void printMultTable(int maxMultiply) {
    //loop from 1 to maxMultiply for rows multiply, add a brake line in each iteration
    for (int i = 1; i <= maxMultiply; i++) {
        //loop from 1 to maxMultiply for cols multiply, multiply col vs row value and prints it
        for (int j = 1; j <= maxMultiply; j++) {
            //amount of indention to right
            int indentionAmount = countIndentionAmount(j * maxMultiply);

            //if last col, not space printed
            if (j == maxMultiply) {
                printf("%*d", indentionAmount, j * i);
            } else {
                printf("%*d ", indentionAmount, j * i);
            }
        }
        printf("\n");
    }
}
