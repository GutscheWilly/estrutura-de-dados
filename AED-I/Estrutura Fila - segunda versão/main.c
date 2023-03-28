# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <stdbool.h>

typedef struct no{

    int valor;
    struct no *proximoNo;

}No;

typedef struct{

    No *inicioFila;
    int tamanhoFila;

}Fila;

void InicializarFila(Fila **fila){

    *fila = (Fila *)malloc(sizeof(Fila));

    (*fila)->inicioFila = NULL;
    (*fila)->tamanhoFila = 0;

    return; 
}

void InserirFila(Fila *fila){

    No *novoNo = (No *)malloc(sizeof(No));
    No *fimFila;

    if(novoNo){
        novoNo->valor = rand() % 1000;
        novoNo->proximoNo = NULL;
        if(fila->inicioFila == NULL){
            fila->inicioFila = novoNo;
        } else {
            fimFila = fila->inicioFila;
            while(fimFila->proximoNo){
                fimFila = fimFila->proximoNo;
            }
            fimFila->proximoNo = novoNo;
        }
        (fila->tamanhoFila)++;
        printf("\nInserido na fila com sucesso!\n");
    } else {
        printf("\nProblema ao alocar memoria!\n");
    }

    return;
}

No * RemoverFila(Fila *fila){

    No *removido = NULL;

    if(fila->inicioFila){
        removido = fila->inicioFila;
        fila->inicioFila = removido->proximoNo;
        (fila->tamanhoFila)--;
        printf("\nRemovido da fila com sucesso!\n");
    } else {
        printf("\nFila vazia!\n");
    }

    return(removido);
}

void ImprimirFila(Fila *fila){

    No *copiaFila = fila->inicioFila;
    int contador = 1;

    printf("\n------------------------------------------------------------\n");
    printf("\n\tTamanho da fila: %d\n", fila->tamanhoFila);

    if(copiaFila){
        while(copiaFila){
            printf("\n\t\t(%d) -> %d\n", contador, copiaFila->valor);
            copiaFila = copiaFila->proximoNo;
            contador++;
        }
    } else {
        printf("\nFila vazia!\n");
    }

    printf("\n------------------------------------------------------------\n");

    return;
}

int ReceberOpcao(){

    int opcao;

    printf("\n(1) -> Inserir fila\n(2) -> Remover fila\n(3) -> Imprimir fila\n(0) -> Fechar programa\n");
    printf("\nDigite uma das opcoes acima: ");
    scanf("%d", &opcao);

    return(opcao);
}

void ImprimirElementoRemovido(No *removido){

    printf("\nValor do usuario removido: %d\n", removido->valor);

    return;
}

int main(){

    Fila *fila;
    No *removido;
    bool fimPrograma = false;

    srand(time(NULL));
    InicializarFila(&fila);

    while(fimPrograma == false){
        switch(ReceberOpcao()){
            case 1:
                InserirFila(fila);
                break;
            case 2:
                removido = RemoverFila(fila);
                ImprimirElementoRemovido(removido);
                free(removido);
                break;
            case 3:
                ImprimirFila(fila);
                break;
            case 0:
                printf("\nPrograma finalizado!\n");
                fimPrograma = true;
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    }

    return(0);
}