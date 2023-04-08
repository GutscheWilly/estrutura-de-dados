#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node* start;
    Node* end;
    int size;
} List;

List* newList() {
    List* list = (List*) malloc(sizeof(List));
    list->start = NULL;
    list->end = NULL;
    list->size = 0;
    return list;
}

Node* newNode(int value) {
    Node* node = (Node*) malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

void addNode(List* list, int value) {
    list->size++;

    if (list->start == NULL) {
        list->start = newNode(value);
        list->end = list->start;
        return;
    }

    list->end->next = newNode(value);
    list->end = list->end->next;
}

int inputValue() {
    int value;
    scanf("%d", &value);
    return value;
}

List* inputValuesList(int size) {
    List* list = newList();

    for (int i = 0; i < size; i++) {
        int value = inputValue();
        addNode(list, value);
    }
    return list;
}

void printList(List list) {
    Node* currentNode = list.start;

    for (int i = 0; i < list.size; i++) {
        int value = currentNode->value;
        printf("%d ", value);
        currentNode = currentNode->next;
    }
}

Node* getNodeByIndex(List* list, int index) {
    if (index < 0 || index > list->size - 1) {
        return NULL;
    }

    Node* node = list->start;

    for (int i = 0; i < index; i++) {
        node = node->next;
    }   
    return node;
}

List* splitList(List* list, int startIndex, int endIndex) {
    List* splitList = newList();

    Node* auxiliaryNode = getNodeByIndex(list, startIndex);

    for (int i = startIndex; i <= endIndex; i++) {
        int value = auxiliaryNode->value;
        addNode(splitList, value);
        auxiliaryNode = auxiliaryNode->next;
    }
    return splitList;
}

void removeStartOfList(List* list) {
    Node* start = list->start;
    list->start = start->next;
    list->size--;
    free(start);

    if (list->size == 0) {
        list->end = NULL;
    }
}

void merge(List* list, int beginIndex, int middleIndex, int endIndex) {
    List* leftList = splitList(list, beginIndex, middleIndex);
    List* rightList = splitList(list, middleIndex + 1, endIndex);

    Node* currentNode = getNodeByIndex(list, beginIndex);

    for (int i = beginIndex; i <= endIndex; i++) {
        if (leftList->size == 0) {
            currentNode->value = rightList->start->value;
            currentNode = currentNode->next;
            removeStartOfList(rightList);
            continue;
        }

        if (rightList->size == 0) {
            currentNode->value = leftList->start->value;
            currentNode = currentNode->next;
            removeStartOfList(leftList);
            continue;
        }

        int leftValue = leftList->start->value;
        int rightValue = rightList->start->value;

        if (leftValue <= rightValue) {
            currentNode->value = leftValue;
            removeStartOfList(leftList);
        }

        if (rightValue < leftValue) {
            currentNode->value = rightValue;
            removeStartOfList(rightList);
        }

        currentNode = currentNode->next;
    }

    free(leftList);
    free(rightList);
}

void mergeSort(List* list, int beginIndex, int endIndex, int* leftDepth, int* rightDepth) {
    if (beginIndex < endIndex) {
        int middleIndex = (beginIndex + endIndex) / 2;

        if (leftDepth) {
            *leftDepth += 1;
        }

        if (rightDepth) {
            *rightDepth += 1;
        }

        mergeSort(list, beginIndex, middleIndex, leftDepth, NULL);
        mergeSort(list, middleIndex + 1, endIndex, NULL, rightDepth);

        merge(list, beginIndex, middleIndex, endIndex);
    }
}

int maxDepth(int leftDepth, int rightDepth) {
    if (leftDepth >= rightDepth) {
        return leftDepth;
    }
    return rightDepth;
}

void freeList(List* list) {
    while (list->size > 0) {
        removeStartOfList(list);
    }
    free(list);
}

int main() {
    int size = inputValue();
    List* list = inputValuesList(size);

    int leftDepth = 0;
    int rightDepth = 0;

    mergeSort(list, 0, list->size - 1, &leftDepth, &rightDepth);

    int depth = maxDepth(leftDepth, rightDepth);

    printList(*list);
    printf("\n%d", depth);

    freeList(list);

    return 0;
}
