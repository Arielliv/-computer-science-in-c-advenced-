#include "array.h"

void printInt(const void *obj) {
    printf("%d ", *(int *) obj);
}

void saveInt(FILE *f, const void *obj) {
    fwrite(obj, sizeof(int), 1, f);
}

void *loadInt(FILE *f) {
    int *newValue = (int *) malloc(sizeof(int));
    fread(newValue, sizeof(int), 1, f);
    return newValue;
}

void main() {
    Array intArr;
    Array intArrFromFile;
    int n1 = 3, n2 = 8, n3 = 5;

    initArray(&intArr, sizeof(int), 2, printInt, saveInt, loadInt);
    addToEnd(&intArr, &n1);
    addToEnd(&intArr, &n2);
    addToEnd(&intArr, &n3);

    printArr(&intArr);
    saveArrToFile("intsArr.bin", &intArr);
    freeArray(&intArr);

    initArray(&intArrFromFile, sizeof(int), 2, printInt, saveInt, loadInt);
    printf("\nInt arr from file, before read:\n");
    printArr(&intArrFromFile);
    loadArrFromFile("intsArr.bin", &intArrFromFile);
    printf("\nInt arr from file, after read:\n");
    printArr(&intArrFromFile);
    freeArray(&intArrFromFile);
}



