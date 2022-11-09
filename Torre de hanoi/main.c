# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct disco {
    int diametro;
    struct disco *proximo;
}Disco;

typedef struct {
    Disco *topo;
    int quantidadeDiscos;
}Pino;

Pino inicializarPino() {
    Pino pino;

    pino.topo = NULL;
    pino.quantidadeDiscos = 0;

    return pino;
}

void imprimirPino(Pino pino) {
    printf("Topo <-------------------> Base\n\t");
    while (pino.topo != NULL) {
        printf("%d ", pino.topo->diametro);
        pino.topo = pino.topo->proximo;
    }
    printf("\n");
}

void adicionarDisco(Pino *pino, Disco *discoAdicionado) {
    discoAdicionado->proximo = pino->topo;
    pino->topo = discoAdicionado;
    pino->quantidadeDiscos++;
}

Disco* removerDisco(Pino *pino) {
    Disco *discoRemovido = pino->topo;

    if (discoRemovido != NULL) {
        pino->topo = pino->topo->proximo;
        pino->quantidadeDiscos--;
    }

    return discoRemovido;
}

bool verificarValidadePino(Pino pino) {
    bool valido = true;

    for (int i = 1 ; i < pino.quantidadeDiscos ; i++) {
        if (pino.topo->diametro > pino.topo->proximo->diametro) {
            valido = false;
            break;
        } else {
            pino.topo = pino.topo->proximo;
        }
    }

    return valido;
}

int main() {

    Pino pino1 = inicializarPino(), pino2 = inicializarPino(), pino3 = inicializarPino();
    int quantidadeDiscos, quantidadeJogadas;
    bool jogoValido = true;

    printf("Informe a quantidade de discos: ");
    scanf("%d", &quantidadeDiscos);
    printf("Informe a quantidade de jogadas: ");
    scanf("%d", &quantidadeJogadas);

    for (int i = quantidadeDiscos ; i > 0 ; i--) {
        Disco *disco = (Disco*) malloc(sizeof(Disco));
        disco->diametro = i;
        adicionarDisco(&pino1, disco);
    }

    for (int i = 0 ; i < quantidadeJogadas ; i++) {
        printf("\nPino (1):\n");
        imprimirPino(pino1);
        printf("\nPino (2):\n");
        imprimirPino(pino2);
        printf("\nPino (3):\n");
        imprimirPino(pino3);

        int origem, destino;
        printf("\nRetirar do pino: ");
        scanf("%d", &origem);
        printf("Colocar no pino: ");
        scanf("%d", &destino);

        Disco *discoRemovido;
        switch (origem) {
            case 1:
                discoRemovido = removerDisco(&pino1);
                break;
            case 2:
                discoRemovido = removerDisco(&pino2);
                break;
            case 3:
                discoRemovido = removerDisco(&pino3);
                break;
        }

        switch (destino) {
            case 1:
                adicionarDisco(&pino1, discoRemovido);
                break;
            case 2:
                adicionarDisco(&pino2, discoRemovido);
                break;
            case 3:
                adicionarDisco(&pino3, discoRemovido);
                break;
        }

        if (!verificarValidadePino(pino1) || !verificarValidadePino(pino2) || !verificarValidadePino(pino3)) {
            printf("\n<<< Movimento errado! >>>");
            i = quantidadeJogadas;
            jogoValido = false;
        }
    }

    if (jogoValido == true) {
        if (verificarValidadePino(pino3) && pino3.quantidadeDiscos == quantidadeDiscos) {
            printf("\n<<< Resolvido! >>>");
        } else {
            printf("\n<<< Incompleto! >>>");
        }
    }

    return 0;
}