#include <stdio.h>
#include <stdlib.h>
#include "arvBinaria.h"

ArvBinaria* inserirLetra(ArvBinaria *raiz, char letra) {
    if (raiz == NULL) {
        ArvBinaria *novoNo = (ArvBinaria*)malloc(sizeof(ArvBinaria));
        novoNo->letra = letra;
        novoNo->esquerda = NULL;
        novoNo->direita = NULL;
        return novoNo;
    }

    if (letra < raiz->letra) {
        raiz->esquerda = inserirLetra(raiz->esquerda, letra);
    } else {
        raiz->direita = inserirLetra(raiz->direita, letra);
    }

    return raiz;
}

void imprimirArvorePreOrdem(ArvBinaria *raiz) {
    if (raiz) {
        printf(" %c", raiz->letra);
        imprimirArvorePreOrdem(raiz->esquerda);
        imprimirArvorePreOrdem(raiz->direita);
    }
}

void imprimirArvoreEmOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvoreEmOrdem(raiz->esquerda);
        printf(" %c", raiz->letra);
        imprimirArvoreEmOrdem(raiz->direita);
    }
}

void imprimirArvorePosOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvorePosOrdem(raiz->esquerda);
        imprimirArvorePosOrdem(raiz->direita);
        printf(" %c", raiz->letra);
    }
}

ArvBinaria* buscarletra(ArvBinaria *raiz, char letra) {
    if (!raiz) {
        return NULL;
    }

    if (raiz->letra == letra) {
        return raiz;
    }

    if (letra < raiz->letra) {
        return buscarletra(raiz->esquerda, letra);
    }

    if (letra > raiz->letra) {
        return buscarletra(raiz->direita, letra);
    }
}