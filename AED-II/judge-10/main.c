#include <stdlib.h>
#include <stdio.h>

#define FALSE 0
#define TRUE 1
#define TAM 1000

int M;
int MM;

typedef int TipoChave;

typedef struct TipoRegistro
{
	TipoChave Chave;
} TipoRegistro;

typedef struct TipoPagina *TipoApontador;

typedef struct TipoPagina
{
	int n;
	TipoRegistro r[TAM];
	TipoApontador p[TAM];
} TipoPagina;

void Inicializa(TipoApontador *Dicionario)
{
	*Dicionario = NULL;
}

void InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir)
{
	short NaoAchouPosicao;
	int k;
	k = Ap->n;
	NaoAchouPosicao = (k > 0);
	while (NaoAchouPosicao)
	{
		if (Reg.Chave >= Ap->r[k - 1].Chave)
		{
			NaoAchouPosicao = FALSE;
			break;
		}
		Ap->r[k] = Ap->r[k - 1];
		Ap->p[k + 1] = Ap->p[k];
		k--;
		if (k < 1)
			NaoAchouPosicao = FALSE;
	}
	Ap->r[k] = Reg;
	Ap->p[k + 1] = ApDir;
	Ap->n++;
}

void Ins(TipoRegistro Reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno)
{
	long i = 1; // Posição provavel do vetor em que novo indice sera inserido
	long j;
	TipoApontador ApTemp;

	if (Ap == NULL) // Critério de parada da recursão. Pode ser usado para arvore vazia, arvore com espaço em folhas ou arvore que explode
	{
		*Cresceu = TRUE;
		(*RegRetorno) = Reg;
		(*ApRetorno) = NULL;
		return;
	}

	while (i < Ap->n && Reg.Chave > Ap->r[i - 1].Chave)
		i++; // Percorrendo vetores dos nós para encontrar valor maior (ou igual) que o novo indice

	if (Reg.Chave == Ap->r[i - 1].Chave)
	{
		printf(" Erro: Registro ja esta presente\n");
		*Cresceu = FALSE;
		return;
	}

	if (Reg.Chave < Ap->r[i - 1].Chave)
		i--; // Como o valor nao é igual, só pode ser maior, entao volta-se uma posição

	Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno); // Chama-se recursivo para descer na arvore

	if (!*Cresceu)
		return;

	if (Ap->n < MM) /* Pagina tem espaco */
	{
		InsereNaPagina(Ap, *RegRetorno, *ApRetorno); // Chama insere na página pq tem esoaço
		*Cresceu = FALSE;
		return;
	}

	/* Overflow: Pagina tem que ser dividida */			// Página nao tem espaço suficiente
	ApTemp = (TipoApontador)malloc(sizeof(TipoPagina)); // Cria nova pagina pra ser raiz da subarvore que vem do split
	ApTemp->n = 0;
	ApTemp->p[0] = NULL; // Ela começa com zero indices e primeiro filho pra NULL
	if (i < M + 1)
	{
		InsereNaPagina(ApTemp, Ap->r[MM - 1], Ap->p[MM]);
		Ap->n--;
		InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
	}
	else
		InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
	for (j = M + 2; j <= MM; j++)
		InsereNaPagina(ApTemp, Ap->r[j - 1], Ap->p[j]);
	Ap->n = M;
	ApTemp->p[0] = Ap->p[M + 1];
	*RegRetorno = Ap->r[M];
	*ApRetorno = ApTemp;
}

void Insere(TipoRegistro Reg, TipoApontador *Ap)
{
	short Cresceu;
	TipoRegistro RegRetorno;
	TipoPagina *ApRetorno, *ApTemp;
	Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno); // Chamando funcao insere auxiliar
	if (Cresceu)									  /* Arvore cresce na altura pela raiz */
	{
		ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina)); // Criando nova raiz
		ApTemp->n = 1;									   // Definindo que a nova raiz só terá um índice
		ApTemp->r[0] = RegRetorno;						   // Definindo valor do unico indice da raiz
		ApTemp->p[1] = ApRetorno;						   // Definindo filho da direita da raiz, resultado do split que causou explosao no tamanho
		ApTemp->p[0] = *Ap;								   // Definindo filho da esquerda da raiz, resultado do split que causou explosao no tamanho
		*Ap = ApTemp;									   // Enderençando nova raiz
	}
}

void pegarInputs(TipoPagina **pagina)
{
	TipoRegistro registro;
	int input;
	scanf("%d", &input);
	registro.Chave = input;

	while (input >= 0)
	{
		Insere(registro, pagina);
		scanf("%d", &input);
		registro.Chave = input;
	}
}

TipoApontador buscar(TipoApontador pagina, int dado)
{
	if (pagina != NULL)
	{
		int i = 0;
		while (i < pagina->n && dado > pagina->r[i].Chave)
		{
			i++;
		}
		if (i < pagina->n && dado == pagina->r[i].Chave)
		{
			return pagina; 
		}
		else if (pagina->p[i] != NULL)
		{
			return buscar(pagina->p[i], dado);
		}
		else
			return NULL; 
	}
	else
		return NULL; 
}

void imprimirPagina(TipoApontador pagina) 
{
	for (int i = 0; i < pagina->n; i++) {
		printf("%d ", pagina->r[i].Chave);
	}
}

int main()
{
	scanf("%d", &M);
	MM = M * 2;

	TipoPagina *pagina = NULL;
	Inicializa(&pagina);
	pegarInputs(&pagina);

	int chaveBusca;
	scanf("%d", &chaveBusca);

	TipoApontador paginaBuscada = buscar(pagina, chaveBusca);

	printf("%d\n", pagina->n);

	if (paginaBuscada == NULL) {
		printf("Valor nao encontrado");
	} else {
		printf("%d\n", paginaBuscada->n);
		imprimirPagina(paginaBuscada);
	}

	return 0;
}
