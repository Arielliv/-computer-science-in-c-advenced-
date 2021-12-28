#include <stdio.h>
#include <stdlib.h>
typedef unsigned char BYTE;

BYTE * createBitsArray(int arr[], int size, int * bitArrSize);
int countSetBits(BYTE * bitsArr, int size);
int getMax(int arr[], int size);
BYTE setBit(BYTE ch, int i);

int main()
{
    int arr[] = { 7, 2, 9, 4, 13 };
    BYTE* bitsArr;
    int count;
    int size;
    bitsArr = createBitsArray(arr,
                              sizeof(arr) / sizeof(arr[0]), &size);
    count = countSetBits(bitsArr, size);
    printf("Counter: %d\n", count);

    free(bitsArr);
}
BYTE * createBitsArray(int arr[], int size,
                       int * bitArrSize)
{
    BYTE* bitsArr;
    int i;
    int max = getMax(arr, size);
    int bitsSize = max / 8 + 1;

    bitsArr = (BYTE*)calloc(bitsSize, sizeof(BYTE));

    //bitsArr = (BYTE*)malloc(bitsSize * sizeof(BYTE));
    /*for (i = 0; i < bitsSize; i++)
        bitsArr[i] = 0;*/

    for (i = 0; i < size; i++)
    {
        bitsArr[arr[i] / 8] = setBit(bitsArr[arr[i] / 8],
                                     7 - arr[i] % 8);
    }

    *bitArrSize = bitsSize;
    return bitsArr;
}
int countSetBits(BYTE * bitsArr, int size)
{
    /*int i,j, counter = 0;
    BYTE num;
    for (i = 0; i < size; i++)
    {
        num = bitsArr[i];
        for (j = 7; j >= 0 && num!=0; j--)
        {
            if ((num - pow(2, j)) >= 0)
            {
                counter++;
                num -= pow(2, j);
            }
        }
    }
    return counter;*/

    //////
    int i;
    BYTE currByte;
    BYTE mask = 0x01;
    int counter = 0;
    for (i = 0; i < size; i++)
    {
        currByte = bitsArr[i];
        while (currByte != 0)
        {
            if ((mask & currByte) == 0x01)
                counter++;
            currByte = currByte >> 0x01;
        }
    }
    return counter;
}
int getMax(int arr[], int size)
{
    int i,max=arr[0];
    for (i = 1; i < size; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }
    return max;
}
BYTE setBit(BYTE ch, int i)
{
    BYTE mask = 1 << i;
    return ch | mask;
}