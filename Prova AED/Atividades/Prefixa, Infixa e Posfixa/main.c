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








int main() {

    ArvBinaria *raiz = NULL;
    char formaPrefixa[53], formaInfixa[53];
    int quantTestes, quantNodos;
    char teste[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    scanf("%d", &quantTestes);

    /*
    for (int i = 1 ; i <= quantTestes ; i++) {
        scanf("%d", &quantNodos);
        scanf("%s", formaPrefixa);
        scanf("%s", formaInfixa);
    }
    */

    for(int i = 0 ; i < 6 ; i++) {
        raiz = inserirLetra(raiz, teste[i]);
    }

    imprimirArvorePreOrdem(raiz);
    printf("\n");
    imprimirArvoreEmOrdem(raiz);
    printf("\n");
    imprimirArvorePosOrdem(raiz);

    return 0;
}