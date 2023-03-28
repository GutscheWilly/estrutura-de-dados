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
    printf("\n\nDigite um valor para buscar na Arvore: ");
    scanf("%d", &valor);
    return valor;
}

void imprimirBusca(ArvBinaria *busca) {
    if (busca) {
        printf("\nValor encontrado na arvore!\n");
    } else {
        printf("\nValor nao encontrado na arvore!\n");
    }
}

int main() {

    ArvBinaria *raiz = NULL;
    int array[] = {50, 17, 76, 9, 54, 23}, valor;

    for (int i = 0 ; i < 6 ; i++) {
        raiz = inserirValor(raiz, array[i]);
    }

    while (1) {
        imprimirExemplo(raiz);
        valor = receberValor();
        imprimirBusca(buscarValor(raiz, valor));
    }

    return 0;
}