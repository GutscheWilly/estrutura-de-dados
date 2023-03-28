#include <stdio.h>
#include "arvBinaria.h"

void imprimirExemplo(ArvBinaria *raiz) {
    printf("\nPre-Ordem: ");
    imprimirArvorePreOrdem(raiz);
    printf("\nEm-Ordem: ");
    imprimirArvoreEmOrdem(raiz);
    printf("\nPos-Ordem: ");
    imprimirArvorePosOrdem(raiz);
}

int receberValor() {
    int valor;
    printf("\n\nDigite um valor para inserir na Arvore: ");
    scanf("%d", &valor);
    return valor;
}

int main() {

    ArvBinaria *raiz = NULL;
    int array[] = {4, 1, 6, 3, 5, 7, 2}, valor;

    for (int i = 0 ; i < 7 ; i++) {
        raiz = inserirValor(raiz, array[i]);
    }

    while (1) {
        imprimirExemplo(raiz);
        valor = receberValor();
        raiz = inserirValor(raiz, valor);
    }
}