#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 82

typedef struct no {
    char valor;
    struct no *esquerda;
    struct no *direita;
} No;

No* criar_no(char valor) {
    No* novo_no = (No*) malloc(sizeof(No));
    if (novo_no != NULL) {
        novo_no->valor = valor;
        novo_no->esquerda = NULL;
        novo_no->direita = NULL;
    }
    return novo_no;
}

int encontrar_indice(char vetor[], int inicio, int fim, char alvo) {
    int i;
    for (i = inicio; i <= fim; i++) {
        if (vetor[i] == alvo)
            return i;
    }
    return -1;
}

No* construir_arvore(char prefixo[], char infixo[], int inicio, int fim, int *indice_atual) {
    No *raiz;
    int indice_raiz;

    if (inicio > fim)
        return NULL;

    raiz = criar_no(prefixo[*indice_atual]);
    (*indice_atual)++;

    if (inicio == fim)
        return raiz;

    indice_raiz = encontrar_indice(infixo, inicio, fim, raiz->valor);

    raiz->esquerda = construir_arvore(prefixo, infixo, inicio, indice_raiz - 1, indice_atual);
    raiz->direita = construir_arvore(prefixo, infixo, indice_raiz + 1, fim, indice_atual);

    return raiz;
}

void percorrer_pos_ordem(No *raiz) {
    if (raiz == NULL)
        return;
    percorrer_pos_ordem(raiz->esquerda);
    percorrer_pos_ordem(raiz->direita);
    printf("%c", raiz->valor);
}

void liberar_arvore(No *raiz) {
    if (raiz == NULL)
        return;
    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);
    free(raiz);
}

int main() {
    int n;
    char prefixo[MAX], infixo[MAX];

    while (scanf("%d %s %s", &n, prefixo, infixo) == 3) {
        int indice_inicial;
        No *raiz;

        indice_inicial = 0;
        raiz = construir_arvore(prefixo, infixo, 0, n - 1, &indice_inicial);
        percorrer_pos_ordem(raiz);
        printf("\n");
        liberar_arvore(raiz);
    }

    return 0;
}
