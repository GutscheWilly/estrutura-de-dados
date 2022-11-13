# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct no {
    int valor;
    int coluna;
    struct no *proximo;
}No;

typedef struct {
    No **matriz;
    int linhas;
    int colunas;
}Matriz;

Matriz* inicializarMatriz(int linhas, int colunas) {
    Matriz *mat = (Matriz*) malloc(sizeof(Matriz));

    mat->matriz = (No**) malloc(linhas * sizeof(No*));
    for (int i = 0 ; i < linhas ; i++) {
        mat->matriz[i] = NULL;
    }
    mat->linhas = linhas;
    mat->colunas = colunas;

    return mat;
}

bool inserirMatriz(Matriz *mat, int linha, int coluna, int valor) {
    // verificando se a linha e a coluna são válidas  
    if (linha < 0 || linha >= mat->linhas || coluna < 0 || coluna >= mat->colunas) {
        return false;
    }

    // busca pela posição da linha e da coluna
    No *anterior = NULL;
    No *atual = mat->matriz[linha];
    while (atual != NULL && atual->coluna < coluna) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual != NULL && atual->coluna == coluna) {
        // modificando o valor da posição se o Nó dela já existir
        if (valor == 0) {
            if (anterior == NULL) {
                mat->matriz[linha] = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
        } else {
            atual->valor = valor;
        }
    } else if (valor != 0) {
        // criando Nó e inserindo na matriz
        No *novo = (No*) malloc(sizeof(No));

        novo->valor = valor;
        novo->coluna = coluna;
        novo->proximo = atual;
        if (anterior == NULL) {
            mat->matriz[linha] = novo;
        } else {
            anterior->proximo = novo;
        }
    }

    return true;
}

int acessarValor(Matriz *mat, int linha, int coluna) {
    // verificando se a linha e a coluna são válidas  
    if (linha < 0 || linha >= mat->linhas || coluna < 0 || coluna >= mat->colunas) {
        return 0;
    }

    No *atual = mat->matriz[linha];
    while (atual != NULL && atual->coluna < coluna) {
        atual = atual->proximo;
    }
    if (atual != NULL && atual->coluna == coluna) {
        return atual->valor;
    }

    return 0;
}

void imprimirMatriz(Matriz *mat) {
    No *atual;

    for (int i = 0 ; i < mat->linhas ; i++) {
        printf("Linha (%d) -> ", i);
        atual = mat->matriz[i];
        while (atual != NULL) {
            printf("%d ", atual->valor);
            atual = atual->proximo;
        }
        printf("\n");
    }
}


int main() {









    return 0;
}