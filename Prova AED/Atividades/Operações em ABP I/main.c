#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArvBinaria {
    char letra;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

ArvBinaria* inserirLetra(ArvBinaria *raiz, int letra) {
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
        printf("%c ", raiz->letra);
        imprimirArvorePreOrdem(raiz->esquerda);
        imprimirArvorePreOrdem(raiz->direita);
    }
}

void imprimirArvoreEmOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvoreEmOrdem(raiz->esquerda);
        printf("%c ", raiz->letra);
        imprimirArvoreEmOrdem(raiz->direita);
    }
}

void imprimirArvorePosOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvorePosOrdem(raiz->esquerda);
        imprimirArvorePosOrdem(raiz->direita);
        printf("%c ", raiz->letra);
    }
}

ArvBinaria* buscarLetra(ArvBinaria *raiz, char letra) {
    if (!raiz) {
        return NULL;
    }

    if (raiz->letra == letra) {
        return raiz;
    }

    if (letra < raiz->letra) {
        return buscarLetra(raiz->esquerda, letra);
    }

    if (letra > raiz->letra) {
        return buscarLetra(raiz->direita, letra);
    }
}

void imprimirBusca(ArvBinaria *raiz, char letra) {
    ArvBinaria *busca = buscarLetra(raiz, letra);

    if (busca) {
        printf("%c existe\n", busca->letra);
    } else {
        printf("%c nao existe\n", letra);
    }
}

int main() {

    ArvBinaria *raiz = NULL;
    char string[20];

    while (!feof(stdin)) {
        fflush(stdin);
        fgets(string, 20, stdin);
        string[strlen(string) - 1] = '\0';

        if (string[0] == 'I' && string[1] == ' ') {
            raiz = inserirLetra(raiz, string[2]);
        }

        if (string[0] == 'P' && string[1] == ' ') {
            imprimirBusca(raiz, string[2]);
        } else {
            if (strcmp(string, "INFIXA") == 0) {
                imprimirArvoreEmOrdem(raiz);
                printf("\n");
            }

            if (strcmp(string, "PREFIXA") == 0) {
                imprimirArvorePreOrdem(raiz);
                printf("\n");
            }    

            if (strcmp(string, "POSFIXA") == 0) {
                imprimirArvorePosOrdem(raiz);
                printf("\n");
            }  
        }
    }

    return 0;
}