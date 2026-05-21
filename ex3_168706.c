/*
descricao: sistema de fila de chamados implementado com alocacao dinamica
disciplina: algoritmos e estruturas de dados 1 - unifesp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_MENSAGEM 51

typedef struct chamado {
    int id;
    char mensagem[TAM_MENSAGEM];
    struct chamado* proximo;
} Chamado;

typedef struct {
    Chamado* inicio;
    Chamado* fim;
} Fila;

typedef Fila* PFila;

void inicializar(PFila fila) {
    fila->inicio = fila->fim = NULL;
}

void adicionar(PFila fila, int id, char* mensagem) {
    Chamado* novo = (Chamado*)malloc(sizeof(Chamado));
    if (!novo) return;

    novo->id = id;
    strncpy(novo->mensagem, mensagem, TAM_MENSAGEM - 1);
    novo->mensagem[TAM_MENSAGEM - 1] = '\0';
    novo->proximo = NULL;

    if (fila->fim)
        fila->fim->proximo = novo;
    else
        fila->inicio = novo;

    fila->fim = novo;
}

void remover(PFila fila) {
    if (!fila->inicio) {
        printf("Fila vazia!\n");
        exit (0);
    }

    Chamado* temp = fila->inicio;
    fila->inicio = temp->proximo;
    if (!fila->inicio)
        fila->fim = NULL;

    free(temp);
}

void imprimir(PFila fila) {
    if (!fila->inicio) {
        printf("\n");
        return;
    }

    Chamado* atual = fila->inicio;
    while (atual) {
        printf("ID: %d - %s\n", atual->id, atual->mensagem);
        atual = atual->proximo;
    }
}

void limpar(PFila fila) {
    while (fila->inicio) {
        Chamado* temp = fila->inicio;
        fila->inicio = temp->proximo;
        free(temp);
    }
    fila->fim = NULL;
}

int main() {
    int n;

    while (scanf("%d", &n) != 1 || n <= 0 || n > 100) {
        while (getchar() != '\n');
    }

    getchar();

    Fila fila;
    PFila pf = &fila;
    inicializar(pf);

    for (int i = 0; i < n; i++) {
        char linha[100];
        if (!fgets(linha, sizeof(linha), stdin)) break;

        if (strncmp(linha, "ENQUEUE", 7) == 0) {
            int id;
            char mensagem[TAM_MENSAGEM];
            sscanf(linha + 8, "%d %[^\n]", &id, mensagem);
            adicionar(pf, id, mensagem);
        } else if (strncmp(linha, "DEQUEUE", 7) == 0) {
            remover(pf);
        } else if (strncmp(linha, "PRINT", 5) == 0) {
            imprimir(pf);
        } else if (strncmp(linha, "CLEAR", 5) == 0) {
            limpar(pf);
        }
    }

    limpar(pf);
    return 0;
}
