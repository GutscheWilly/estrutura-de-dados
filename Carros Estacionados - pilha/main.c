# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct no{

    char placaCarro[11];
    struct no *proximoCarro;

}No;

typedef struct{

    No *ultimoCarroEmpilhado;
    int quantidadeCarros;

}PilhaCarro;

void InicializarPilhaCarro(PilhaCarro *pilha){

    pilha->ultimoCarroEmpilhado = NULL;
    pilha->quantidadeCarros = 0;

    return;
}

int ReceberOpcaoUsuario(){

    int opcao;

    printf("\n\n(1) -> Adicionar carro  (2) -> Mostrar sequencia de retirada  (3) -> Remover Ultimo veiculo  (0) -> Fechar programa\n\n");
    printf("\n\nDigite uma das opcoes acima: ");
    scanf("%d", &opcao);

    return(opcao);
}

void ReceberPlacaCarroEstacionado(char placa[]){

    printf("\nInforme a placa do carro estacionado: ");
    fflush(stdin);
    fgets(placa, 10, stdin);
    placa[strlen(placa) - 1] = '\0';
    printf("\nPlaca do carro registrada com sucesso!\n");

    return;
}

void AdicionarCarro(PilhaCarro *pilha){

    No *novoCarro = (No *) malloc(sizeof(No));

    if(novoCarro != NULL){
        ReceberPlacaCarroEstacionado(novoCarro->placaCarro);
        novoCarro->proximoCarro = pilha->ultimoCarroEmpilhado;
        pilha->ultimoCarroEmpilhado = novoCarro;
        pilha->quantidadeCarros++;
    } else {
        printf("\nErro ao alocar memoria no programa!\n");
    }

    return;
}

No * RemoverCarro(PilhaCarro *pilha){

    No *carroRemovido = pilha->ultimoCarroEmpilhado;

    if(carroRemovido != NULL){
        pilha->ultimoCarroEmpilhado = carroRemovido->proximoCarro;
        return(carroRemovido);
    } else {
        printf("\nNao ha carros estacionados!\n");
        return(NULL);
    }
}

void MostrarUltimoCarroRetirado(No *ultimoCarro){

    printf("\nUltimo veiculo retirado -> placa: %s\n", ultimoCarro->placaCarro);

    return;
}

void MonstrarSequenciaCarrosRetirados(No *ultimoCarro){

    int sequencia;

    if(ultimoCarro == NULL){
        printf("\nNao ha carros estacionados!\n");
    } else {
        printf("\n\t-------------------------------------------------\n");
        printf("\n\tSequencia da retirada dos veiculos:\n\n");
        for(sequencia = 1 ; ultimoCarro != NULL ; sequencia++){
            printf("\n\t(%d) -> placa: %s\n", sequencia, ultimoCarro->placaCarro);
            ultimoCarro = ultimoCarro->proximoCarro;
        }
        printf("\n\t-------------------------------------------------\n");
    }

    return;
}

int main(){

    PilhaCarro pilhaCarro;
    No *carroRetirado;
    int opcaoUsuario, fimPrograma = 0;

    InicializarPilhaCarro(&pilhaCarro);

    while(fimPrograma == 0){
        opcaoUsuario = ReceberOpcaoUsuario();

        switch(opcaoUsuario){

            case(1):
                AdicionarCarro(&pilhaCarro);
                break;
            case(2):
                MonstrarSequenciaCarrosRetirados(pilhaCarro.ultimoCarroEmpilhado);
                break;
            case(3):
                carroRetirado = RemoverCarro(&pilhaCarro);
                if(carroRetirado != NULL){
                    MostrarUltimoCarroRetirado(carroRetirado);
                }
                free(carroRetirado);
                break;
            case(0):
                printf("\nPrograma finalizado!\n");
                fimPrograma = 1;
                break;
            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    }

    return(0);
}