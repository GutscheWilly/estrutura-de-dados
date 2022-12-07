#include <stdio.h>
#include <stdlib.h>
#include "ArvBinaria.h"

int imprimirOpcao() {
    int opcao;
    printf("\n1 - Inserir valor\n");
    printf("2 - Imprimir arvore\n");
    printf("3 - Buscar valor\n");
    printf("4 - Remover valor\n");
    printf("0 - Fechar programa\n");
    scanf("%d", &opcao);
    system("cls");
    return opcao;
}

int receberValor() {
    int valor;
    printf("Digite um valor: ");
    scanf("%d", &valor);
    return valor;
}

int main() {

    ArvBinaria *raiz = NULL;
    int fimPrograma = 0;
    int array[] = {583, 245, 731, 123, 389, 278, 684, 893};
    int valor;

    for (int i = 0 ; i < 8 ; i++) {
        inserirValor(&raiz, array[i]);
    }
    
    while (!fimPrograma) {
        switch (imprimirOpcao()) {
            case 1:
                inserirValor(&raiz, receberValor());
                break;
            case 2:
                printf("Arvore: ");
                imprimirArvBinaria(raiz);
                printf("\n");
                break;
            case 3:
                if (buscarValor(raiz, receberValor())) {
                    printf("Valor encontrado!\n");
                } else {
                    printf("Valor nao encontrado!\n");
                }
                break;
            case 4:
                valor = receberValor();
                if (buscarValor(raiz, valor)) {
                    raiz = removerValor(raiz, valor);
                    printf("Valor %d removido com sucesso!\n", valor);
                } else {
                    printf("Valor %d nao pertence a arvore!\n", valor);
                }
                break;
            case 0:
                fimPrograma = 1;
                break;
            default:
                printf("Opcao invalida!\n");
        }
    }

    return 0;
}