# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct no{

    int valor;
    struct no *proximoNo;

}No;

int ReceberValor(){

    int valor;

    printf("\nDigite um valor: ");
    scanf("%d", &valor);

    return(valor);
}

void InserirFila(No **fila){

    No *novoNo = (No *) malloc(sizeof(No));
    No *encontrarFim;

    if(novoNo){
        novoNo->valor = ReceberValor();
        novoNo->proximoNo = NULL;
        if(*fila == NULL){
            *fila = novoNo;
        } else {
            encontrarFim = *fila;
            while(encontrarFim->proximoNo){
                encontrarFim = encontrarFim->proximoNo;
            }
            encontrarFim->proximoNo = novoNo;
            printf("\nInserido na fila com sucesso!\n");
        }
    } else {
        printf("\nErro ao alocar memoria!\n");
    }

    return;
}

No * RemoverFila(No **fila){

    No *noRemovido = NULL;

    if(*fila){
        noRemovido = *fila;
        *fila = noRemovido->proximoNo;
        printf("\nRemovido da fila com sucesso!\n");
    } else {
        printf("\nFila vazia!\n");
    }

    return(noRemovido);
}

void ImprimirFila(No *fila){

    int contador = 1;

    printf("\nFila:\n");
    while(fila){
        printf("\n\t(%d) -> %d\n", contador, fila->valor);
        fila = fila->proximoNo;
        contador++;
    }

    return;
}

int Menu(){

    int opcao;

    printf("\n\n\t(1) -> Inserir na fila  (2) -> Remover da fila  (3) -> Imprimir fila\n\n");
    printf("\nDigite uma das opcoes: ");
    scanf("%d", &opcao);

    return(opcao);
}

int main(){

    No *fila = NULL, *removido;
    int opcao;
    bool fimPrograma = false;

    while(fimPrograma == false){
        opcao = Menu();
        system("cls");
        switch(opcao){
            case 1:
                InserirFila(&fila);
                break;
            case 2:
                removido = RemoverFila(&fila);
                free(removido);
                break;
            case 3:
                ImprimirFila(fila);
                break;
            default:
                printf("\nOpcao invalida!\n");
        }
    }

    return(0);
}