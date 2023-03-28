#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contadorPrefixa;

typedef struct ArvBinaria {
    char letra;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

ArvBinaria* inicializaRaiz(char letra) {
    ArvBinaria *novaRaiz = (ArvBinaria*)malloc(sizeof(ArvBinaria));
    novaRaiz->letra = letra;
    novaRaiz->esquerda = NULL;
    novaRaiz->direita = NULL;
    return novaRaiz;
}

ArvBinaria* montarArvBinaria(ArvBinaria *raiz, char prefixa[], char infixa[], int indexEsquerda, int indexDireita) {
    int i = 0;

    while (infixa[i] != prefixa[contadorPrefixa]) {
        i++;
    }

    contadorPrefixa++;
    
    if (indexEsquerda <= indexDireita && contadorPrefixa <= strlen(infixa)) {
        raiz = inicializaRaiz(infixa[i]);

        if (i > indexEsquerda) {
            raiz->esquerda = montarArvBinaria(raiz->esquerda, prefixa, infixa, indexEsquerda, i - 1);
        }

        if (i < indexDireita) {
            raiz->direita = montarArvBinaria(raiz->direita, prefixa, infixa, i + 1, indexDireita);
        }
    }

    return raiz;
}

void imprimirPosFixa(ArvBinaria *raiz) {
    if (raiz) {
        imprimirPosFixa(raiz->esquerda);
        imprimirPosFixa(raiz->direita);
        printf("%c", raiz->letra);
    }
}

int main() {

    char preFixa[20], inFixa[20], string[40];
    char *tokenString;
    ArvBinaria *raiz;
    int quantTestes, quantNodos;

    scanf("%d", &quantTestes);

    for (int i = 0 ; i < quantTestes ; i++) {
        raiz = NULL;
        fflush(stdin);
        scanf("%d\n", &quantNodos);
        gets(string);
        
        tokenString = strtok(string, " ");

        for (int j = 1 ; j < 3 ; j++) {
            if (j == 1) {
                strcpy(preFixa, tokenString);
            } else {
                strcpy(inFixa, tokenString);
            }
            tokenString = strtok(NULL, " ");
        }

        contadorPrefixa = 0;
        raiz = montarArvBinaria(raiz, preFixa, inFixa, 0, strlen(preFixa) - 1);
        imprimirPosFixa(raiz);
        printf("\n");
    }

    return 0;
}