#include <stdio.h>
#include <stdlib.h>

int inputValue() {
    int value;
    scanf("%d", &value);
    return value;
}

int* inputArray(int size) {
    int* array = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

int* splitArray(int* array, int size, int begin) {
    int* splitArray = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        splitArray[i] = array[begin + i];
    }
    return splitArray;
}

void merge(int* array, int begin, int middle, int end) {
    int leftSize = middle - begin + 1;
    int rightSize = end - middle;

    int* leftArray = splitArray(array, leftSize, begin);
    int* rightArray = splitArray(array, rightSize, middle + 1);

    int leftIndex = 0;
    int rightIndex = 0;

    for (int i = begin; i <= end; i++) {
        if (leftIndex >= leftSize) {
            array[i] = rightArray[rightIndex];
            rightIndex++;
            continue;
        }

        if (rightIndex >= rightSize) {
            array[i] = leftArray[leftIndex];
            leftIndex++;
            continue;
        }

        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[i] = leftArray[leftIndex];
            leftIndex++;
        } else {
            array[i] = rightArray[rightIndex];
            rightIndex++;
        }
    }
}

void mergeSort(int* array, int begin, int end) {
    if (begin < end) {
        int middle = (begin + end) / 2;

        mergeSort(array, begin, middle);
        mergeSort(array, middle + 1, end);

        merge(array, begin, middle, end);
    }
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
}

int main() {
    int quantityValue = inputValue();
    
    int* values = inputArray(quantityValue); 

    mergeSort(values, 0, quantityValue - 1);

    printArray(values, quantityValue);

    return 0;
}
