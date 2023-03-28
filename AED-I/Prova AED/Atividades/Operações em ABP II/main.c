#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("%d ", raiz->valor);
        imprimirArvorePreOrdem(raiz->esquerda);
        imprimirArvorePreOrdem(raiz->direita);
    }
}

void imprimirArvoreEmOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvoreEmOrdem(raiz->esquerda);
        printf("%d ", raiz->valor);
        imprimirArvoreEmOrdem(raiz->direita);
    }
}

void imprimirArvorePosOrdem(ArvBinaria *raiz) {
    if (raiz) {
        imprimirArvorePosOrdem(raiz->esquerda);
        imprimirArvorePosOrdem(raiz->direita);
        printf("%d ", raiz->valor);
    }
}

ArvBinaria* removerValor(ArvBinaria *raiz, int valor) {
    if (raiz == NULL) {
        return NULL;
    }
    if (valor == raiz->valor) {
        if (raiz->esquerda != NULL && raiz->direita != NULL) {
            ArvBinaria *auxiliar = raiz->esquerda;
            while (auxiliar->direita != NULL) {
                auxiliar = auxiliar->direita;
            }
            raiz->valor = auxiliar->valor;
            auxiliar->valor = valor;
            raiz->esquerda = removerValor(raiz->esquerda, valor);
            return raiz;
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

ArvBinaria* buscarValor(ArvBinaria *raiz, int valor) {
    if (!raiz) {
        return NULL;
    }

    if (raiz->valor == valor) {
        return raiz;
    }

    if (valor < raiz->valor) {
        return buscarValor(raiz->esquerda, valor);
    }

    if (valor > raiz->valor) {
        return buscarValor(raiz->direita, valor);
    }
}

void imprimirBusca(ArvBinaria *raiz, int valor) {
    ArvBinaria *busca = buscarValor(raiz, valor);

    if (busca) {
        printf("%d existe\n", busca->valor);
    } else {
        printf("%d nao existe\n", valor);
    }
}

int main() {

    ArvBinaria *raiz = NULL;
    char string[20];
    int valor;

    while (!feof(stdin)) {
        fflush(stdin);
        scanf("%s", string);

        if (strcmp(string, "INFIXA") == 0) {
            imprimirArvoreEmOrdem(raiz);
            printf("\n");
        } else if (strcmp(string, "PREFIXA") == 0) {
            imprimirArvorePreOrdem(raiz);
            printf("\n");
        } else if (strcmp(string, "POSFIXA") == 0) {
            imprimirArvorePosOrdem(raiz);
            printf("\n");
        } else {
            if (string[0] == 'I') {
                scanf("%d", &valor);
                raiz = inserirValor(raiz, valor);
            }
            if (string[0] == 'P') {
                scanf("%d", &valor);
                imprimirBusca(raiz, valor);
            }
            if (string[0] == 'R') {
                scanf("%d", &valor);
                if (buscarValor(raiz, valor)) {
                    raiz = removerValor(raiz, valor);
                }
            } 
        }
    }

    return 0;
}