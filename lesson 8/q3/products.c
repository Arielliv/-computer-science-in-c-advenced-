//
// Created by Ariel Livshits on 03/12/2021.
//

//
// Created by Ariel Livshits on 03/12/2021.
//
#include "products.h";

Product *createProductArr(char *fileName, int *size) {
    Product *products;
    int i, nameLen;

    FILE *filep = fopen(fileName, "rt");
    if (filep == NULL) {
        printf("Error open file");
        exit(1);
    }
    fscanf(filep, "%d\n", size);
    products = (Product *) malloc(sizeof(Product) * (*size));
    // need to check allocation
    for (i = 0; i < *size; i++) {
        fscanf(filep, "%d ", &nameLen);
        products[i].name = (char *) malloc(sizeof(char) * nameLen);
        for (int j = 0; j < nameLen; ++j) {
            products[i].name[j] = fgetc(filep);
        }
        products[i].name[nameLen] = '\0';
        fscanf(filep, "%d", &products[i].price);
        fscanf(filep, "%d\n", &products[i].quantity);
    }
    fclose(filep);
    return products;
}

void sortProducts(Product *products, int size);

void swap(Product *a, Product *b);

void printProductsToFile(Product *products, int size, char *fileName){
    FILE * filep = fopen(fileName,"wt");
    if (filep == NULL) {
        printf("Error open file");
        exit(1);
    }

    fprintf(filep,"%d\n",size);
    for (int i = 0; i < size; ++i) {
        fprintf(filep, "%d", strlen(products[i].name));
        fprintf(filep, "%s", products[i].name);
        fprintf(filep, "%d", products[i].price);
        fprintf(filep, "%d\n", products[i].quantity);
    }
}


