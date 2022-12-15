#ifndef _ARV_BINARIA
#define _ARV_BINARIA

typedef struct ArvBinaria {
    int letra;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

ArvBinaria* inserirLetra(ArvBinaria *raiz, char letra);
void imprimirArvorePreOrdem(ArvBinaria *raiz);
void imprimirArvoreEmOrdem(ArvBinaria *raiz);
void imprimirArvorePosOrdem(ArvBinaria *raiz);
ArvBinaria* buscarLetra(ArvBinaria *raiz, char letra);

#endif