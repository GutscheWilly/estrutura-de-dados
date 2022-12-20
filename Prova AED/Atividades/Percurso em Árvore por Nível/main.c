#include<stdio.h>
#include<stdlib.h>

typedef struct no{
    int valor; 
    struct no* esq;
    struct no* dir;
}NO;

typedef struct arvore{
    NO* pont;
}ARVORE;

typedef struct elemento{
    NO* reg;
    struct elemento* prox;
}ELEMENTO;

typedef struct fila{
    ELEMENTO* head;
}FILA;

NO* inserirValor(NO *raiz, int valor) {
    if (raiz == NULL) {
        NO *auxiliar = (NO*)malloc(sizeof(NO));
        auxiliar->valor = valor;
        auxiliar->esq = NULL;
        auxiliar->dir = NULL;
        return auxiliar;
    } else if (valor < raiz->valor) {
        raiz->esq = inserirValor(raiz->esq, valor);
    } else {
        raiz->dir = inserirValor(raiz->dir, valor);
    }
    return raiz;
}

void criaFila(FILA* fila){
    fila->head = NULL;
} 

void insereFila(FILA* fila, NO* p){
    ELEMENTO* novo = (ELEMENTO *) malloc(sizeof(ELEMENTO));
    novo->reg = p;
    novo->prox = NULL;
    if(fila->head==NULL){
        fila->head = novo;
    }else{
        ELEMENTO* pointer = fila->head;
        ELEMENTO* ant = NULL;
        while(pointer!=NULL){
            ant = pointer;
            pointer = pointer->prox;
        }
        ant->prox = novo;
        free(pointer);
    }
}

NO* removeFila(FILA* fila){
    if(fila->head!=NULL){
        ELEMENTO* pointer = fila->head;
        fila->head = pointer->prox;
        return pointer->reg;
    }
}

int tamanhoFila(FILA* fila){
    ELEMENTO* pointer = fila->head;
    int tam;
    tam=0;
    while(pointer!=NULL){
        tam++;
        pointer = pointer->prox;
    }
    return tam;
}
void percursoPorNivel(NO* raiz){
    FILA fila;   
    NO* prox;
    criaFila(&fila);
    insereFila(&fila, raiz);
    while(tamanhoFila(&fila)>0){
        prox = removeFila(&fila);
        printf("%d ", prox->valor);
        if(prox->esq!=NULL){
            insereFila(&fila, prox->esq);
        }
        if(prox->dir!=NULL){
            insereFila(&fila, prox->dir);
        }
    }
}

int main() {

    NO *raiz = NULL;
    int quantTestes, quantValores, valor;

    scanf("%d", &quantTestes);

    for (int i = 1 ; i <= quantTestes ; i++) {
        raiz = NULL;
        scanf("%d", &quantValores);

        for (int j = 1 ; j <= quantValores ; j++) {
            scanf("%d", &valor);
            raiz = inserirValor(raiz, valor);
        }
        printf("Case %d:\n", i);
        percursoPorNivel(raiz);
        printf("\n\n");
    }

    return 0;
}