#include <stdio.h>
#include <stdlib.h>

int* newIntArray(int size) {
    int* array = (int*) malloc(size * sizeof(int));
    return array;
}

int* splitArray(int* arrayToBeCopied, int size, int begin, int end) {
    int* newArray = newIntArray(size);

    for (int i = begin; i < end; i++) {
        newArray[i] = arrayToBeCopied[i];
    }
    return newArray;
}

void merge(int* array, int begin, int middle, int end) {
    int leftSize = middle - begin + 1;
    int rightSize = end - middle;

    int* leftArray = splitArray(array, leftSize, begin, middle);
    int* rightArray = splitArray(array, rightSize, middle + 1, end);


}

void mergeSort(int *array, int begin, int end) {
    if (begin < end) {
        int middle = (begin + end) / 2;

        mergeSort(array, begin, middle);
        mergeSort(array, middle + 1, end);
        merge()
    }
}

int main() {

}