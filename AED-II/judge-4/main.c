#include <stdio.h>
#include <stdlib.h>

int inputValue() {
    int value;
    scanf("%d", &value);
    return value;
}

int* inputValuesArray(int size) {
    int* array = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        array[i] = inputValue();
    }
    return array;
}

int* copyArray(int* array, int size) {
    int* copiedArray = (int*) malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        int copiedValue = array[i];
        copiedArray[i] = copiedValue;
    }
    return copiedArray;
}

void swap(int* array, int firstIndex, int secondIndex) {
    int firstValue = array[firstIndex];
    int secondValue = array[secondIndex];
    
    array[firstIndex] = secondValue;
    array[secondIndex] = firstValue;
}

int partition(int* array, int startIndex, int endIndex) {
    int pivotValue = array[endIndex];

    int referenceIndex = startIndex;

    for (int currentIndex = startIndex; currentIndex < endIndex; currentIndex++) {
        int currentValue = array[currentIndex];

        if (currentValue < pivotValue) {
            swap(array, referenceIndex, currentIndex);
            referenceIndex++;
        }
    }

    swap(array, referenceIndex, endIndex);

    return referenceIndex;
}

void setMinAndMaxDepths(int currentDepth, int* minDepth, int* maxDepth) {
    if (currentDepth < *minDepth) {
        *minDepth = currentDepth;
    }

    if (currentDepth > *maxDepth) {
        *maxDepth = currentDepth;
    }
}

void quickSort(int* array, int startIndex, int endIndex, int currentDepth, int* minDepth, int* maxDepth) {
    if (startIndex < endIndex) {
        int pivotIndex = partition(array, startIndex, endIndex);

        quickSort(array, startIndex, pivotIndex - 1, currentDepth + 1, minDepth, maxDepth);
        quickSort(array, pivotIndex + 1, endIndex, currentDepth + 1, minDepth, maxDepth);

        return;
    }

    setMinAndMaxDepths(currentDepth, minDepth, maxDepth);
}

int gapDepth(int minDepth, int maxDepth) {
    return maxDepth - minDepth;
}

int medianOfThreeIndex(int* array, int startIndex, int endIndex) {
    int middleIndex = (startIndex + endIndex) / 2;

    if (array[middleIndex] > array[endIndex]) {
        swap(array, middleIndex, endIndex);
    }

    if (array[startIndex] > array[endIndex]) {
        swap(array, startIndex, endIndex);
    }

    if (array[startIndex] > array[middleIndex]) {
        swap(array, startIndex, middleIndex);
    }

    return middleIndex;
}

int medianOfThreePartition(int* array, int startIndex, int endIndex) {
    int pivotIndex = medianOfThreeIndex(array, startIndex, endIndex);
    
    swap(array, pivotIndex, endIndex);

    return partition(array, startIndex, endIndex);
}

void quickSortMedianOfThree(int* array, int startIndex, int endIndex, int currentDepth, int* minDepth, int* maxDepth) {
    if (startIndex < endIndex) {
        int pivotIndex = medianOfThreePartition(array, startIndex, endIndex);

        quickSortMedianOfThree(array, startIndex, pivotIndex - 1, currentDepth + 1, minDepth, maxDepth);
        quickSortMedianOfThree(array, pivotIndex + 1, endIndex, currentDepth + 1, minDepth, maxDepth);

        return;
    }

    setMinAndMaxDepths(currentDepth, minDepth, maxDepth);
}

int main() {
    int size = inputValue();
    int* array = inputValuesArray(size);
    int* copiedArray = copyArray(array, size);

    // Quick Sort 
    int minDepth = size;
    int maxDepth = 0;

    quickSort(array, 0, size - 1, 0, &minDepth, &maxDepth);
    int gap = gapDepth(minDepth, maxDepth);

    printf("%d", gap);

    // Quick Sort - Median of Three
    minDepth = size;
    maxDepth = 0;

    quickSortMedianOfThree(copiedArray, 0, size - 1, 0, &minDepth, &maxDepth);
    gap = gapDepth(minDepth, maxDepth);

    printf("\n%d", gap);

    // Free Memory
    free(array);
    free(copiedArray);

    return 0;
}
