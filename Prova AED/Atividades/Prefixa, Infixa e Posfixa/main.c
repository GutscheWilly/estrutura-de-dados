#include <stdio.h>
#include <stdlib.h>

typedef struct ArvBinaria {
    char letra;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

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
        printf(" %d", raiz->letra);
        imprimirArvorePreOrdem(raiz->esquerda);
        imprimirArvorePreOrdem(raiz->direita);
    }
}

void imprimirArvoreEmOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvoreEmOrdem(raiz->esquerda);
        printf(" %d", raiz->letra);
        imprimirArvoreEmOrdem(raiz->direita);
    }
}

void imprimirArvorePosOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvorePosOrdem(raiz->esquerda);
        imprimirArvorePosOrdem(raiz->direita);
        printf(" %d", raiz->letra);
    }
}








int main() {

    ArvBinaria *raiz;
    char string1[53], string2[53];
    int quantTestes, quantNodos;

    scanf("%d", &quantTestes);

    for (int i = 1 ; i < quantTestes ; i++) {
        scanf("%d", &quantNodos);

        
    }



    return 0;
}