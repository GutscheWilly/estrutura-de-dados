#ifndef _ARVORE_BINARIA
#define _ARVORE_BINARIA

typedef struct ArvBinaria {
    int valor;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
} ArvBinaria;

void inserirValor(ArvBinaria **raiz, int valor);
void imprimirArvBinaria(ArvBinaria *raiz);
ArvBinaria* buscarValor(ArvBinaria *raiz, int valor);
ArvBinaria* removerValor(ArvBinaria *raiz, int valor);

#endif