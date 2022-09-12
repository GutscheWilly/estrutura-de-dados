# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <conio.h>

# define quantidadePilhas 4
# define maximoContainerPilha 3

typedef struct container{

    int codigoContainer;
    char corContainer[20];
    struct container *proximoContainer;

}Container;

typedef struct{

    Container *topoPilha;
    int tamanhoPilha;

}Pilha;

void InicializarPilhas(Pilha *pilha){

    for(int i = 0 ; i < quantidadePilhas ; i++){
        pilha[i].topoPilha = NULL;
        pilha[i].tamanhoPilha = 0;
    }

    return;
}

int ReceberOpcaoUsuario(){

    int opcao;
    
    printf("\n\n\n\t\t(1) -> Empilhar container   (2) -> Monstrar todos as pilhas   (3) -> Desempilhar container   (0) -> Fechar Programa\n\n");
    printf("\nInforme uma das opcoes acima: ");
    scanf("%d", &opcao);

    return(opcao);
}

int indexMenorPilha(Pilha *pilha){

    int index = 0;

    for(int i = 1 ; i < quantidadePilhas ; i++){
        if(pilha[index].tamanhoPilha > pilha[i].tamanhoPilha){
            index = i;
        }
    }

    return(index);
}

int ReceberCodigoContainer(){

    int codigo;

    printf("\nInforme o codigo do container: ");
    scanf("%d", &codigo);

    return(codigo);
}

void ReceberCorContainer(char string[]){

    printf("\nInformer a cor do container: ");
    fflush(stdin);
    fgets(string, 20, stdin);
    string[strlen(string) - 1] = '\0';

    return;
}

void EmpilharContainer(Pilha *pilha){

    int index = indexMenorPilha(pilha);
    Container *novoContainer;

    if(pilha[index].tamanhoPilha < maximoContainerPilha){

            novoContainer = (Container *) malloc(sizeof(Container));

            if(novoContainer != NULL){
                novoContainer->codigoContainer = ReceberCodigoContainer();
                ReceberCorContainer(novoContainer->corContainer);
                novoContainer->proximoContainer = pilha[index].topoPilha;
                pilha[index].topoPilha = novoContainer;
                pilha[index].tamanhoPilha++;
                printf("\nEmpilhamento realizado com sucesso!\n");
            } else {
                printf("\nErro ao alocar memoria para empilhar container!\n");
            }

    } else {
        printf("\nNao e possivel empilhar mais containers!\n");
    }

    return;
}

void ImprimirTodasPilhas(Pilha *pilha){

    Container *copiaTopoPilha;
    int contadorContainer;

    for(int i = 0 ; i < quantidadePilhas ; i++){

        copiaTopoPilha = pilha[i].topoPilha;
        contadorContainer = 1;

        printf("\n\nPilha (%d):\n", i + 1);
        printf("\n\tQuantidade de containers: %d\n", pilha[i].tamanhoPilha);

        while(copiaTopoPilha != NULL){
            printf("\n\tContainer %d -> Codigo: %d  Cor: %s\n", contadorContainer, copiaTopoPilha->codigoContainer, copiaTopoPilha->corContainer);
            copiaTopoPilha = copiaTopoPilha->proximoContainer;
            contadorContainer++;
        }
    }

    return;
}

int IndexPilhaRemoverContainer(Pilha *pilha){

    int index;
    bool existeContainerDesempilhar = false;

    ImprimirTodasPilhas(pilha);

    for(int i = 0 ; i < quantidadePilhas ; i++){

        if(pilha[i].tamanhoPilha > 0){
            existeContainerDesempilhar = true;
            break;
        }
    }

    if(existeContainerDesempilhar == true){
        printf("\n\nInforme o numero da pilha que deseja desempilhar: ");
        scanf("%d", &index);
        return(index - 1);
    } else {
        return(-1);
    }
}

Container* DesempilharContainer(Pilha *pilha){

    Container *containerRemovido;
    int indexDesempilhar = IndexPilhaRemoverContainer(pilha);

    if(indexDesempilhar >= 0 && indexDesempilhar < quantidadePilhas){

        if(pilha[indexDesempilhar].tamanhoPilha > 0){
            containerRemovido = pilha[indexDesempilhar].topoPilha;
            pilha[indexDesempilhar].topoPilha = containerRemovido->proximoContainer;
            pilha[indexDesempilhar].tamanhoPilha--;
            return(containerRemovido);
        } else {
            printf("\n\n<<<< Pilha nao possui containers! >>>>\n\n");
        }

    } else {

        if(indexDesempilhar == -1){
            printf("\n\n<<<< Nenhuma pilha possui container empilhados! >>>>\n\n");
        } else {
            printf("\n\n<<<< Numero da pilha informado nao existe! >>>>\n\n");
        }
    }

    return(NULL);
}

void ImprimirContainerDesempilhado(Container *containerDesempilhado){

    if(containerDesempilhado != NULL){
        printf("\n\nCodigo do container desempilhado: %d   Cor: %s\n\n", containerDesempilhado->codigoContainer, containerDesempilhado->corContainer);
        printf("\tContainer desempilhado com sucesso!\n\n");
    }

    return;
}


int main(){

    Pilha *pilha = (Pilha *) malloc(quantidadePilhas * sizeof(Pilha));
    Container *ultimoContainerDesempilhado = NULL;
    int opcaoUsuario;
    bool fimPrograma = false;

    InicializarPilhas(pilha);

    while(fimPrograma == false){

        opcaoUsuario = ReceberOpcaoUsuario();

        _sleep(1000);
        system("cls");

        switch(opcaoUsuario){

            case(1):
                EmpilharContainer(pilha);
                break;
            
            case(2):
                ImprimirTodasPilhas(pilha);
                break;

            case(3):
                ultimoContainerDesempilhado = DesempilharContainer(pilha);
                ImprimirContainerDesempilhado(ultimoContainerDesempilhado);
                free(ultimoContainerDesempilhado);
                break;

            case(0):
                printf("\n\n<<<< Programa finalizado! >>>>\n\n");
                fimPrograma = true;
                break;

            default:
                printf("\n\n\t<<<< Opcao invalida! >>>>\n\n");
        }
    }

    return(0);
}