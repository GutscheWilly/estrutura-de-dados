#ifndef _ARV_BINARIA
#define _ARV_BINARIA

typedef struct ArvBinaria {
    int valor;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

ArvBinaria* inserirValor(ArvBinaria *raiz, int valor);
void imprimirArvorePreOrdem(ArvBinaria *raiz);
void imprimirArvoreEmOrdem(ArvBinaria *raiz);
void imprimirArvorePosOrdem(ArvBinaria *raiz);

#endif