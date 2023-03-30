#include <stdio.h>
#include <stdlib.h>

int inputValue() {
    int value;
    scanf("%d", &value);
    return value;
}

int* getArray(int length) {
    int* array = (int*) malloc(length * sizeof(int));

    for (int i = 0 ; i < length ; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

void sortArray(int* array, int length) {
    for (int i = 0 ; i < length - 1 ; i++) {
        int minimunValue = array[i];
        int minimunIndex = i;

        for (int j = i + 1 ; j < length ; j++) {
            int currentValue = array[j];
            int currentIndex = j;

            if (currentValue < minimunValue) {
                minimunValue = currentValue;
                minimunIndex = currentIndex;
            }
        }

        int referenceValue = array[i];
        int referenceIndex = i;

        if (referenceValue > minimunValue) {
            int copyReferenceValue = referenceValue;

            array[referenceIndex] = minimunValue;
            array[minimunIndex] = copyReferenceValue;
        }
    }
}

int areDosesEnought(int* microorganisms, int* doses, int length) {
    for (int i = 0 ; i < length ; i++) {
        if (microorganisms[i] >= doses[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int patientQuantity = inputValue();

    int* microorganismsForEachPatient = getArray(patientQuantity);

    int* dosesForEachPatient = getArray(patientQuantity);

    sortArray(microorganismsForEachPatient, patientQuantity);
    sortArray(dosesForEachPatient, patientQuantity);

    int areEnought = areDosesEnought(microorganismsForEachPatient, dosesForEachPatient, patientQuantity);

    if (areEnought) {
        printf("sim");
    } else {
        printf("nao");
    }

    free(microorganismsForEachPatient);
    free(dosesForEachPatient);
}
