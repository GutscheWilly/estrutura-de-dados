#include <stdio.h>
#include "ArvBinaria.h"

int imprimirOpcao() {
    int opcao;
    printf("\n1 - Inserir valor\n");
    printf("2 - Imprimir arvore\n");
    printf("3 - Buscar elemento\n");
    printf("4 - Remover elemento\n");
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
    
    while (!fimPrograma) {
        switch (imprimirOpcao()) {
            case 1:
                inserirValor(&raiz, receberValor());
                break;
            case 2:
                printf("Arvore: ");
                imprimirArvBinaria(raiz);
                break;
            case 3:
                break;
            case 4:
                break;
            case 0:
                fimPrograma = 1;
                break;
            default:
                printf("Opcao invalida!");
        }
    }

    return 0;
}