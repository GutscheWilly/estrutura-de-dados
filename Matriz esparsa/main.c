# include <stdio.h>
# include <stdlib.h>

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





int main() {









    return 0;
}