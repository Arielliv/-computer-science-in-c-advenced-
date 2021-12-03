//
// Created by Ariel Livshits on 03/12/2021.
//

#ifndef Q3_PRODUCTS_H
#define Q3_PRODUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct product {
    char *name;
    int price;
    int quantity;
} Product;

Product *createProductArr(char *fileName, int *size);

void sortProducts(Product *products, int size);

void swap(Product *a, Product *b);

void printProductsToFile(Product *products, int size, char *fileName);

#endif //Q3_PRODUCTS_H
