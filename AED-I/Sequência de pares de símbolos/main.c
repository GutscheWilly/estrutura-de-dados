# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct no {
    char caracter;
    struct no *proximo;
}No;

typedef struct {
    No *topo;
    int tamanho;
}Pilha;

Pilha iniciliarzarPilha() {
    Pilha pilha;
    pilha.topo = NULL;
    pilha.tamanho = 0;
    return pilha;
}

void empilhar(Pilha *pilha, char caracter) {
    No *novoNo = (No*) malloc(sizeof(No));
    novoNo->caracter = caracter;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
    pilha->tamanho++;
}

No* desempilhar(Pilha *pilha) {
    No *removido = pilha->topo;
    if(removido) {
        pilha->topo = pilha->topo->proximo;
        pilha->tamanho--;
    }
    return removido;
}

int main() {

    Pilha pilha = iniciliarzarPilha();
    int quantidadePares, quantidadeCaracteres;
    int erroDireita = 0, erroEsquerda = 0;

    printf("Informe a quantidade de pares de símbolos: ");
    scanf("%d", &quantidadePares);
    char paresSimbolos[quantidadePares][10];
    printf("Informe a quantidade de caracteres da sequecia: ");
    scanf("%d", &quantidadeCaracteres);

    printf("Digite os pares: \n");
    for (int i = 0 ; i < quantidadePares ; i++) {
        fflush(stdin);
        char string[10];
        fgets(paresSimbolos[i], 10, stdin);
    }

    printf("Digite a sequencia de caracteres:\n");
    for (int i = 0 ; i < quantidadeCaracteres ; i++) {
        char caracter;
        fflush(stdin);
        scanf("%c", &caracter);

        for (int j = 0 ; j < quantidadePares ; j++) {
            if (caracter == paresSimbolos[j][0]) {
                empilhar(&pilha, caracter);
                break;
            }
        }

        for (int j = 0 ; j <quantidadePares ; j++) {
            if (caracter == paresSimbolos[j][2] ) {
                free(desempilhar(&pilha));
                break;
            }
        }
    }

    if (pilha.topo == NULL) {
        printf("\n<<< Correto! >>>");
    } else {
        int valido = 0;
        for (int i = 0 ; i < quantidadePares ; i++) {
            if (pilha.topo->caracter == paresSimbolos[i][0]) {
                printf("\n<<< Simbolo esquerdo nao fechado >>>");
                valido = 1;
                break;
            }
        }
        if (valido == 0) {
            printf("Simbolo direito nao esperado");
        }
    }
}