#include <stdlib.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define TAM 1000

int M;
int MM;

typedef int Dado;

typedef struct {
	Dado chave;
} Registro;

typedef struct Pagina* ApontadorPagina;

typedef struct Pagina {
	int n;
	Registro r[TAM];
	ApontadorPagina p[TAM];
} Pagina;

void inicializar(ApontadorPagina *apontadorPagina) {
	*apontadorPagina = NULL;
}

void insereNaPagina(ApontadorPagina apontadorPagina, Registro registro, ApontadorPagina apontadorDireita) {
	int k = apontadorPagina->n;
	int naoAchouPosicao = (k > 0);

	while (naoAchouPosicao) {
		if (registro.chave >= apontadorPagina->r[k - 1].chave) {
			naoAchouPosicao = FALSE;
			break;
		}

		apontadorPagina->r[k] = apontadorPagina->r[k - 1];
		apontadorPagina->p[k + 1] = apontadorPagina->p[k];
		k--;

		if (k < 1)
			naoAchouPosicao = FALSE;
	}

	apontadorPagina->r[k] = registro;
	apontadorPagina->p[k + 1] = apontadorDireita;
	apontadorPagina->n++;
}

void Ins(Registro registro, ApontadorPagina apontadorPagina, int* aumentou, Registro* RegRetorno, ApontadorPagina* apontadorRetorno) {
	int i = 1; // Posição provavel do vetor em que novo indice sera inserido
	int j;
	ApontadorPagina apontadorAux;

	if (apontadorPagina == NULL) { // Critério de parada da recursão. Pode ser usado para arvore vazia, arvore com espaço em folhas ou arvore que explode
		*aumentou = TRUE;
		(*RegRetorno) = registro;
		(*apontadorRetorno) = NULL;
		return;
	}

	while (i < apontadorPagina->n && registro.chave > apontadorPagina->r[i - 1].chave)
		i++; // Percorrendo vetores dos nós para encontrar valor maior (ou igual) que o novo indice

	if (registro.chave == apontadorPagina->r[i - 1].chave) {
		*aumentou = FALSE;
		return;
	}

	if (registro.chave < apontadorPagina->r[i - 1].chave)
		i--; // Como o valor nao é igual, só pode ser maior, entao volta-se uma posição

	Ins(registro, apontadorPagina->p[i], aumentou, RegRetorno, apontadorRetorno); // Chama-se recursivo para descer na arvore

	if (!*aumentou)
		return;

	if (apontadorPagina->n < MM) { /* Pagina tem espaco */
		insereNaPagina(apontadorPagina, *RegRetorno, *apontadorRetorno); // Chama insere na página pq tem esoaço
		*aumentou = FALSE;
		return;
	}

	/* Overflow: Pagina tem que ser dividida */			// Página nao tem espaço suficiente
	apontadorAux = (ApontadorPagina)malloc(sizeof(Pagina)); // Cria nova pagina pra ser raiz da subarvore que vem do split
	apontadorAux->n = 0;
	apontadorAux->p[0] = NULL; // Ela começa com zero indices e primeiro filho pra NULL

	if (i < M + 1) {
		insereNaPagina(apontadorAux, apontadorPagina->r[MM - 1], apontadorPagina->p[MM]);
		apontadorPagina->n--;
		insereNaPagina(apontadorPagina, *RegRetorno, *apontadorRetorno);
	} else
		insereNaPagina(apontadorAux, *RegRetorno, *apontadorRetorno);

	for (j = M + 2; j <= MM; j++)
		insereNaPagina(apontadorAux, apontadorPagina->r[j - 1], apontadorPagina->p[j]);

	apontadorPagina->n = M;
	apontadorAux->p[0] = apontadorPagina->p[M + 1];
	*RegRetorno = apontadorPagina->r[M];
	*apontadorRetorno = apontadorAux;
}

void Insere(Registro registro, ApontadorPagina *apontadorPagina) {
	int aumentou;
	Registro RegRetorno;
	Pagina *apontadorRetorno, *apontadorAux;
	Ins(registro, *apontadorPagina, &aumentou, &RegRetorno, &apontadorRetorno); // Chamando funcao insere auxiliar

	if (aumentou) { /* Arvore cresce na altura pela raiz */
		apontadorAux = (Pagina *)malloc(sizeof(Pagina)); // Criando nova raiz
		apontadorAux->n = 1;									   // Definindo que a nova raiz só terá um índice
		apontadorAux->r[0] = RegRetorno;						   // Definindo valor do unico indice da raiz
		apontadorAux->p[1] = apontadorRetorno;						   // Definindo filho da direita da raiz, resultado do split que causou explosao no tamanho
		apontadorAux->p[0] = *apontadorPagina;								   // Definindo filho da esquerda da raiz, resultado do split que causou explosao no tamanho
		*apontadorPagina = apontadorAux;									   // Enderençando nova raiz
	}
}

void pegarInputs(Pagina **pagina) {
	Registro registro;
	int input;
	scanf("%d", &input);
	registro.chave = input;

	while (input >= 0) {
		Insere(registro, pagina);
		scanf("%d", &input);
		registro.chave = input;
	}
}

ApontadorPagina buscar(ApontadorPagina pagina, int dado) {
	if (pagina != NULL) {
		int i = 0;
		while (i < pagina->n && dado > pagina->r[i].chave) {
			i++;
		}
		if (i < pagina->n && dado == pagina->r[i].chave) {
			return pagina; 
		}
		else if (pagina->p[i] != NULL) {
			return buscar(pagina->p[i], dado);
		}
		else
			return NULL; 
	}
	else
		return NULL; 
}

void imprimirPagina(ApontadorPagina pagina) {
	for (int i = 0; i < pagina->n; i++) {
		printf("%d ", pagina->r[i].chave);
	}
}

int main() {
	scanf("%d", &M);
	MM = M * 2;

	Pagina *pagina = NULL;
	inicializar(&pagina);
	pegarInputs(&pagina);

	int chaveBusca;
	scanf("%d", &chaveBusca);

	ApontadorPagina paginaBuscada = buscar(pagina, chaveBusca);

	printf("%d\n", pagina->n);

	if (paginaBuscada == NULL) {
		printf("Valor nao encontrado");
	} else {
		printf("%d\n", paginaBuscada->n);
		imprimirPagina(paginaBuscada);
	}

	return 0;
}
