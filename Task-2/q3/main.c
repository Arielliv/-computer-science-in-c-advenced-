//315363366
//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char **setPtrToCharsArray(char **str_array);

int main() {

    char **str_array;

    unsigned int str_array_size;

    char **ptr_to_chars_array;

    unsigned int res;


    str_array = getStrArrayInput(
            &str_array_size); // Get the size and strings from user (can't assume max size for each string)

    ptr_to_chars_array = setPtrToCharsArray(str_array);

    res = RemoveFromStrArray(&str_array, str_array_size, ptr_to_chars_array);

    printArray(str_array, str_array_size - res);

    // Free memory

    freeArray(str_array, str_array_size - res);

    free(ptr_to_chars_array);

}

char **setPtrToCharsArray(char **str_array) {

    char **res;

    int size, i;

    int str_array_row, str_array_col;


    scanf("%d", &size); // Get number of ptrs

    res = (char **) malloc(sizeof(char *) * (size + 1)); // Add 1 for NULL at the end



    for (i = 0; i < size; i++) {

        scanf("%d", &str_array_row);

        scanf("%d", &str_array_col);

        res[i] = str_array[str_array_row] + str_array_col;

    }


    res[size] = NULL; // Set the last one to NULL



    return res;

}