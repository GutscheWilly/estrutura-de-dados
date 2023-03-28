#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int valor; 
    struct No* esquerda;
    struct No* direita;
}No;

typedef struct ArvBinaria{
    No* raiz;
}ArvBinaria;

typedef struct Elemento{
    No* raiz;
    struct Elemento* proximo;
}Elemento;

typedef struct Fila{
    Elemento* inicio;
}Fila;

No* inserirValor(No *raiz, int valor) {
    if (raiz == NULL) {
        No *auxiliar = (No*)malloc(sizeof(No));
        auxiliar->valor = valor;
        auxiliar->esquerda = NULL;
        auxiliar->direita = NULL;
        return auxiliar;
    } else if (valor < raiz->valor) {
        raiz->esquerda = inserirValor(raiz->esquerda, valor);
    } else {
        raiz->direita = inserirValor(raiz->direita, valor);
    }
    return raiz;
}

void criaFila(Fila* fila){
    fila->inicio = NULL;
} 

void insereFila(Fila *fila, No *raiz){
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    novo->raiz = raiz;
    novo->proximo = NULL;
    if (fila->inicio == NULL) {
        fila->inicio = novo;
    } else {
        Elemento *anterior = NULL;
        Elemento *auxiliar = fila->inicio;
        while (auxiliar != NULL) {
            anterior = auxiliar;
            auxiliar = auxiliar->proximo;
        }
        anterior->proximo = novo;
        free(auxiliar);
    }
}

No* removeFila(Fila* fila){
    if (fila->inicio != NULL) {
        Elemento *auxiliar = fila->inicio;
        fila->inicio = auxiliar->proximo;
        return auxiliar->raiz;
    }
    return NULL;
}

int tamanhoFila(Fila *fila){
    Elemento *auxiliar = fila->inicio;
    int tamanho = 0;

    while (auxiliar != NULL) {
        tamanho++;
        auxiliar = auxiliar->proximo;
    }
    return tamanho;
}

void percursoPorNivel(No *raiz){
    Fila fila;   
    No *proximo;

    criaFila(&fila);
    insereFila(&fila, raiz);

    while (tamanhoFila(&fila) > 0) {
        proximo = removeFila(&fila);
        printf("%d ", proximo->valor);

        if (proximo->esquerda != NULL) {
            insereFila(&fila, proximo->esquerda);
        }
        if (proximo->direita != NULL) {
            insereFila(&fila, proximo->direita);
        }
    }
}

int main() {

    No *raiz = NULL;
    int quantTestes, quantValores, valor;

    scanf("%d", &quantTestes);

    for (int i = 1 ; i <= quantTestes ; i++) {
        raiz = NULL;
        scanf("%d", &quantValores);

        for (int j = 1 ; j <= quantValores ; j++) {
            scanf("%d", &valor);
            raiz = inserirValor(raiz, valor);
        }

        printf("Case %d:\n", i);
        percursoPorNivel(raiz);
        printf("\n\n");
    }

    return 0;
}