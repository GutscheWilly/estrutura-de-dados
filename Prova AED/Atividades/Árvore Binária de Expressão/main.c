#include <stdio.h>
#include <stdlib.h>

typedef struct ArvBinaria {
    char letra;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

ArvBinaria* insereArvBinaria(ArvBinaria *raiz, char letra) {
    if (raiz == NULL) {
        ArvBinaria *auxiliar = (ArvBinaria*)malloc(sizeof(ArvBinaria));
        auxiliar->letra = letra;
        auxiliar->esquerda = NULL;
        auxiliar->direita = NULL;
        return auxiliar;
    }

    if (letra < raiz->letra)
}





int main() {








    return 0;
}