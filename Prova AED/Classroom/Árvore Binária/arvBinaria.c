#include <stdio.h>
#include <stdlib.h>
#include "arvBinaria.h"

ArvBinaria* inserirValor(ArvBinaria *raiz, int valor) {
    if (raiz == NULL) {
        ArvBinaria *novoNo = (ArvBinaria*)malloc(sizeof(ArvBinaria));
        novoNo->valor = valor;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if (valor < raiz->valor) {
        raiz->esquerda = inserirValor(raiz->esquerda, valor);
    } else {
        raiz->direita = inserirValor(raiz->direita, valor);
    }

    return raiz;
}

void imprimirArvorePreOrdem(ArvBinaria *raiz) {
    if (raiz) {
        printf(" %d", raiz->valor);
        imprimirArvorePreOrdem(raiz->esquerda);
        imprimirArvorePreOrdem(raiz->direita);
    }
}

void imprimirArvoreEmOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvoreEmOrdem(raiz->esquerda);
        printf(" %d", raiz->valor);
        imprimirArvoreEmOrdem(raiz->direita);
    }
}

void imprimirArvorePosOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvorePosOrdem(raiz->esquerda);
        imprimirArvorePosOrdem(raiz->direita);
        printf(" %d", raiz->valor);
    }
}