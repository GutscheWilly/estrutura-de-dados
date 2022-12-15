#include <stdio.h>
#include <string.h>
#include "arvBinaria.h"

void receberString(char string[]) {
    fflush(stdin);
    printf("Digite um expressao: ");
    fgets(string, 100, stdin);
    string[strlen(string) - 1] = '\0';
}

void imprimirExemplo(ArvBinaria *raiz) {
    printf("\nPre-Ordem: ");
    imprimirArvorePreOrdem(raiz);
    printf("\nEm-Ordem: ");
    imprimirArvoreEmOrdem(raiz);
    printf("\nPos-Ordem: ");
    imprimirArvorePosOrdem(raiz);
}

int main() {

    ArvBinaria *raiz = NULL;
    char string[100];

    receberString(string);

    for (int i = 0 ; string[i] != '\0' ; i++) {
        if (string[i] != ' ') {
            raiz = inserirLetra(raiz, string[i]);
        }
    }

    imprimirExemplo(raiz);

    return 0;
}