#include <stdio.h>
#include <stdlib.h>

int inputNumber() {
    int number;
    scanf("%d", &number);
    return number;
}

int* getNumberArray(int numberQuantity) {
    int* numberArray = (int*) malloc(numberQuantity * sizeof(int));

    for (int i = 0 ; i < numberQuantity ; i++) {
        scanf("%d", &numberArray[i]);
    }
    return numberArray;
}

int searchNumber(int number, int* array, int beginIndex, int endIndex, int* recursiveCalls) {
    int middleIndex = (endIndex + beginIndex) / 2;

    int middleNumber = array[middleIndex];

    if (middleNumber == number) {
        return 1;
    }

    if (beginIndex >= endIndex) {
        return 0;
    }

    *recursiveCalls += 1;

    if (middleNumber > number) {
        return searchNumber(number, array, beginIndex, middleIndex - 1, recursiveCalls);
    }

    if (middleNumber < number) {
        return searchNumber(number, array, middleIndex + 1, endIndex, recursiveCalls);
    }

    return 0;
}

int main() {
    int numberQuantity = inputNumber();

    int* numberArray = getNumberArray(numberQuantity);

    int numberToBeSearch = inputNumber();

    int recursiveCalls = 0;

    int isNumberFound = searchNumber(numberToBeSearch, numberArray, 0, numberQuantity - 1, &recursiveCalls);

    if (isNumberFound) {
        printf("%d", recursiveCalls);
    } else {
        printf("%d nao foi encontrado", numberToBeSearch);
    }

    free(numberArray);

    return 0;
}
