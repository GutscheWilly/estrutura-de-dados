#include <stdio.h>
#include <stdlib.h>
#include "ArvBinaria.h"

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

ArvBinaria* buscarValor(ArvBinaria *raiz, int valor) {
    if (raiz) {
        if (valor == raiz->valor) {
            return raiz;
        } else if (valor < raiz->valor) {
            return buscarValor(raiz->esquerda, valor);
        } else {
            return buscarValor(raiz->direita, valor);
        }
    }
    return NULL;
}

ArvBinaria* removerValor(ArvBinaria *raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }
    if (valor == raiz->valor) {
        if (raiz->esquerda != NULL && raiz->direita != NULL) {
            
        }
        if (raiz->esquerda == NULL && raiz->direita == NULL) {
            free(raiz);
            return NULL;
        } 
        ArvBinaria *auxiliar;
        if (raiz->esquerda == NULL) {
            auxiliar = raiz->direita;
        } else {
            auxiliar = raiz->esquerda;
        }
        free(raiz);
        return auxiliar;
    } else if (valor < raiz->valor) {
        raiz->esquerda = removerValor(raiz->esquerda, valor);
    } else {
        raiz->direita = removerValor(raiz->direita, valor);
    }
    return raiz;
}