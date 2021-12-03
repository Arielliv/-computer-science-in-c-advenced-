#define _CRT_SECURE_NO_WARNINGS
#include "products.h"

int main(int argc, char *argv[]) {
    Product *products;
    int size;
    products = createProductArr(argv[1], &size);
//    sortProducts(products, size);
    printProductsToFile(products, size, argv[2]);
    return 0;
}
