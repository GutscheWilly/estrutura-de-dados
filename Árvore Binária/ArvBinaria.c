#include "ArvBinaria.h"
#include <stdio.h>
#include <stdlib.h>

void inserirValor(ArvBinaria **raiz, int valor) {
    if (*raiz == NULL) {
        *raiz = (ArvBinaria*)malloc(sizeof(ArvBinaria));
        (*raiz)->valor = valor;
        (*raiz)->esquerda = NULL;
        (*raiz)->direita = NULL;
    } else if (valor < (*raiz)->valor) {
        inserirValor(&((*raiz)->esquerda), valor);
    } else {
        inserirValor(&((*raiz)->direita), valor);
    }
}

void imprimirArvBinaria(ArvBinaria *raiz) {
    if (raiz) {
        printf("%d ", raiz->valor);
        imprimirArvBinaria(raiz->esquerda);
        imprimirArvBinaria(raiz->direita);
    }
}

