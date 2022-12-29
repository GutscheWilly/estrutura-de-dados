#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ArvBinaria {
    char letra;
    struct ArvBinaria *esquerda;
    struct ArvBinaria *direita;
}ArvBinaria;

void retirarEspacosDaString(char string[]) {
    int i = 0;
    
    while (string[i] != '\0') {
        if (string[i] == ' ') {
            for (int j = i ; j < strlen(string) ; j++) {
                string[j] = string[j + 1];
            }
        }
        i++;
    }
}

void adicionarCaracterNaString(char string[], int index, char caracter) {
    for (int i = strlen(string) + 1 ; i > index ; i--) {
        string[i] = string[i - 1];
    }
    string[index] = caracter;
}

void adicionarParentesesNaString(char string[]) {
    int i = 0;

    while (i < strlen(string)) {

        if (string[i] == '*' || string[i] == '/') {

            if (string[i - 1] != ')') {
                adicionarCaracterNaString(string, i - 1, '(');
            } else {
                int j = i - 2;
                // ideia estranha de igualar a quantidade de parenteses a serem fechados (    )))
                while (string[j] != '(') {
                    j--;
                }
                adicionarCaracterNaString(string, j, '(');
            }

            i++;

            if (string[i + 2] != '(') {
                adicionarCaracterNaString(string, i + 2, ')');
            } else {
                int j = i + 1;
                while (string[j] != ')') {
                    j++;
                }
                adicionarCaracterNaString(string, j, ')');
            }

            i++;
        }

        i++;
    }
}

int main() {

    char string[202];

    gets(string);

    retirarEspacosDaString(string);

    printf("Original:  %s\n\n", string);

    adicionarParentesesNaString(string);

    printf("Modificada:  %s\n\n", string);



    return 0;
}