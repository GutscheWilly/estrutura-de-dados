#include <stdio.h>
#include <stdlib.h>

typedef struct ArvBinaria {
    int valor;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

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

void imprimirCase(ArvBinaria *raiz, int index, int quantArvores) {
    printf("Case %d:\n", index);
    printf("Pre.:");
    imprimirArvorePreOrdem(raiz);
    printf("\nIn..:");
    imprimirArvoreEmOrdem(raiz);
    printf("\nPost:");
    imprimirArvorePosOrdem(raiz);
    printf("\n");
    if (index != quantArvores) {
        printf("\n");
    }
}

int main() {

    ArvBinaria *raiz;
    int quantArvores, quantValores, valor; 

    scanf("%d", &quantArvores);

    for (int i = 1 ; i <= quantArvores ; i++) {
        raiz = NULL;
        scanf("%d", &quantValores);

        for (int j = 1 ; j <= quantValores ; j++) {
            scanf("%d", &valor);
            raiz = inserirValor(raiz, valor);
        }

        imprimirCase(raiz, i, quantArvores);
    }

    return 0;
}