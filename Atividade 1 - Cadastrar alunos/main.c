# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

typedef struct{

    int dia;
    int mes;
    int ano;

}Data;

typedef struct{

    char nome[20];
    char ra[10];
    Data dataNascimento;
    float notas[3];
    int frequencia;

}Aluno;

int ReceberOpcaoUsuario(){

    int opcao;
    char pegarEnter;
    
    printf("\n\n\n\n\t(1) -> Cadastrar novo aluno   (2) -> Mostrar todos os alunos cadastrados  (3) -> Acessar aluno por RA   (4) -> Excluir aluno   (0) -> Fechar programa\n\n");
    printf("\n\nDigite uma das opções acima: ");
    scanf("%d", &opcao);
    scanf("%c", &pegarEnter);

    return(opcao);
}

Aluno ReceberAluno(){

    Aluno aluno;

    printf("\nInforme o nome do aluno: ");
    fflush(stdin);
    fgets(aluno.nome, 20, stdin);
    aluno.nome[strlen(aluno.nome) - 1] = '\0';
    printf("\nInforme o RA do aluno: ");
    fgets(aluno.ra, 10, stdin);
    aluno.ra[strlen(aluno.ra) - 1] = '\0';
    printf("\nInforme a data de nascimento DD MM AAAA: ");
    scanf("%d%d%d", &aluno.dataNascimento.dia, &aluno.dataNascimento.mes, &aluno.dataNascimento.ano);
    printf("\nInforme as notas das três provas: ");
    for(int i = 0 ; i < 3 ; i++){
        scanf("%f", &aluno.notas[i]);
    }
    printf("\nInforme a frequencia do aluno: ");
    scanf("%d", &aluno.frequencia);
    printf("\n\n<<<< Aluno cadastrado com sucesso! >>>>\n\n");

    return(aluno);
}

void ImprimirAlunosCadastrados(Aluno *alunos, int quantidadeAlunos){

    printf("\n\n---------------------------------------------------------------------------");

    if(quantidadeAlunos != 0){
        for(int i = 0 ; i < quantidadeAlunos ; i++){
            printf("\n\nAluno (%d):\n", i + 1);
            if(strcmp(alunos[i].nome, "excluído") != 0){
                printf("\tNome: %s   ", alunos[i].nome);
                printf("RA: %s   ", alunos[i].ra);
                printf("Data nascimeto: %d/%d/%d", alunos[i].dataNascimento.dia, alunos[i].dataNascimento.mes, alunos[i].dataNascimento.ano);
                printf("\n\n\tFrequência: %d%%  ", alunos[i].frequencia);
                for(int j = 0 ; j < 3 ; j++){
                    printf("Nota P%d: %.2f   ", j + 1, alunos[i].notas[j]);
                }
            } else { 
                printf("\n\tAluno excluído!");
            }
        }
    } else{
        printf("\n\n\tNão há cadastro de alunos!");
    }
    printf("\n\n---------------------------------------------------------------------------\n\n");

    return;
}

bool VerificarExisteAluno(Aluno *alunos, int quantidadeAlunos, int *index){

    bool existe = false;
    char ra[10];

    printf("\n\nInforme o RA do aluno que deseja acessar: ");
    fgets(ra, 10, stdin);
    ra[strlen(ra) - 1] = '\0';

    for(int i = 0 ; i < quantidadeAlunos ; i++){
        if(strcmp(alunos[i].ra, ra) == 0){
            existe = true;
            *index = i;
            break;
        }
    }

    return(existe);
}

void ImprimirAlunoRa(Aluno aluno){

    printf("\n\n---------------------------------------------------------------------------\n");
    printf("\nAluno:\n");
    if(strcmp(aluno.nome, "excluído") != 0){
        printf("\n\tNome: %s   ", aluno.nome);
        printf("RA: %s   ", aluno.ra);
        printf("Data nascimeto: %d/%d/%d", aluno.dataNascimento.dia, aluno.dataNascimento.mes, aluno.dataNascimento.ano);
        printf("\n\n\tFrequência: %d   ", aluno.frequencia);
        for(int i = 0 ; i < 3 ; i++){
            printf("Nota P%d: %.2f   ", i + 1, aluno.notas[i]);
        }
    } else {
        printf("\n\n\tAluno excluído!");
    }
    printf("\n\n---------------------------------------------------------------------------\n\n");

    return;
}

int IndexAlunoExcluido(Aluno *alunos, int quantidadeAlunos){

    int index;

    ImprimirAlunosCadastrados(alunos, quantidadeAlunos);

    if(quantidadeAlunos != 0){
        printf("\n\nInforme o index do aluno que deseja exluir [Aluno (?)]: ");
        scanf("%d", &index);

        if(index <= quantidadeAlunos && index > 0){
            return(index - 1);
        } else {
            printf("\n\n<<<< Index informado inválido! >>>>\n\n");
            return(IndexAlunoExcluido(alunos, quantidadeAlunos));
        }
    }

    return(-1);
}

void ExcluirAluno(Aluno *alunos, int quantidadeAlunos){

    int index = IndexAlunoExcluido(alunos, quantidadeAlunos);

    if(index != -1){
        strcpy(alunos[index].nome, "excluído");
        printf("\n\n<<<< Aluno (%d) excluído com sucesso! >>>>\n\n", index + 1);
    }

    return;
}

int main(){

    Aluno alunos[1000];
    int opcaoUsuario, indexRa, quantidadeAlunosCadastrados = 0;
    bool fimPrograma = false;

    while(fimPrograma == false){

        opcaoUsuario = ReceberOpcaoUsuario();

        switch(opcaoUsuario){

            case(1):
                alunos[quantidadeAlunosCadastrados] = ReceberAluno();
                quantidadeAlunosCadastrados++;
                break;

            case(2):
                ImprimirAlunosCadastrados(alunos, quantidadeAlunosCadastrados);
                break;

            case(3):
                if(VerificarExisteAluno(alunos, quantidadeAlunosCadastrados, &indexRa) == true){
                    ImprimirAlunoRa(alunos[indexRa]);
                } else {
                    printf("\n\n<<<< RA informado não cadastrado! >>>>\n\n");
                }
                break;

            case(4):
                ExcluirAluno(alunos, quantidadeAlunosCadastrados);
                break;

            case(0):
                printf("\n\n\t\t<<<< Programa finalizado! >>>>\n\n");
                fimPrograma = true;
                break;

            default:
                printf("\n\nOpção inválida!\n\n");
        }
    }
    
    return(0);
}