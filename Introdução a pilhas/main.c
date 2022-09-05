# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct{

    char nome[20];
    int idade;

}Pessoa;

typedef struct no{

    Pessoa pessoa;
    struct no *proximoNo;

}No;

int ReceberOpcaoUsuario(){

    int opcao;

    printf("\n\n\t\t(1) -> Empilhar     (2) -> Monstrar a pilha     (3) -> Remover topo da pilha     (0) -> Finalizar programa\n\n" );
    printf("\nDigite uma das opcoes acima: ");
    scanf("%d", &opcao);

    return(opcao);
}

Pessoa LerPessoa(){

    Pessoa pessoa;

    printf("\nDigite o nome: ");
    fflush(stdin);
    fgets(pessoa.nome, 20, stdin);
    pessoa.nome[strlen(pessoa.nome) - 1] = '\0'; // Retirando o caracter '\n' da string
    printf("\nDigite a idade: ");
    scanf("%d", &pessoa.idade);
    
    return(pessoa);
}

void Empilhar(No **topo){

    No *novoNo = (No *) malloc(sizeof(No));

    if(novoNo != NULL){
        novoNo->pessoa = LerPessoa();
        novoNo->proximoNo = *topo;
        *topo = novoNo;
        printf("\n\n<<< Dados empilhados com sucesso! >>>\n\n");
    } else {
        printf("\n\n<<< Erro ao alocar memoria para novo no! >>>\n\n");
    }

    return;
}

Pessoa Desempilhar(No **topo){

    No *copiaTopo = *topo;
    Pessoa conteudoTopoPilha;

    if(*topo != NULL){
        *topo = copiaTopo->proximoNo;
        conteudoTopoPilha = copiaTopo->pessoa;
        return(conteudoTopoPilha);
    } else {
        printf("\n\n<<< Pilha esta vazia! >>>\n\n");
        return;
    }
}

void ImprimirPessoaDesempilhada(Pessoa pessoa){

    printf("\n\n\t<<< Nome: %s Idade: %d  ->  Pessoa desempilhada! >>>\n\n", pessoa.nome, pessoa.idade);

    return;
}

void ImprimirPilhaInteira(No *topo){

    if(topo == NULL){
        printf("\n\n<<< Pilha esta vazia! >>>\n\n");
    } else {
        printf("\n\n\n\t--------------- Pilha ----------------\n");
        while(topo != NULL){
            printf("\n\tNome: %s \t Idade: %d\n", topo->pessoa.nome, topo->pessoa.idade);
            topo = topo->proximoNo;
        }
        printf("\n\t------------- Fim Pilha --------------\n\n\n");
    }

    return;
}

int main(){

    No *topo = NULL;
    Pessoa pessoaDesempilhada;
    int opcaoUsuario, tamanhoPilha = 0, fimPrograma = 0;

    while(fimPrograma == 0){

        opcaoUsuario = ReceberOpcaoUsuario();

        switch(opcaoUsuario){

            case(1):
                Empilhar(&topo);
                tamanhoPilha++;
                break;
            case(2):
                ImprimirPilhaInteira(topo);
                break;
            case(3):
                pessoaDesempilhada = Desempilhar(&topo);
                if(tamanhoPilha > 0){
                    ImprimirPessoaDesempilhada(pessoaDesempilhada);
                    tamanhoPilha--;
                }
                break;
            case(0):
                printf("\n\nPrograma finalizado!\n\n");
                fimPrograma = 1;
                break;
            default:
                printf("\n<<< Opcao invalida! >>>\n");
                break;
        }
    }

    return(0);
}