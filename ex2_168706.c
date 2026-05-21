/*
descricao: simulador de calculadora utilizando pilha baseada em lista encadeada
disciplina: algoritmos e estruturas de dados 1 - unifesp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct No {
    int valor;
    struct No* proximo;
} No;
 
typedef struct Pilha {
    No* topo;
} Pilha;
 
void push(Pilha* pilha, int valor) {
    No* novo = malloc(sizeof(No));
    novo->valor = valor;
    novo->proximo = pilha->topo;
    pilha->topo = novo;
}
 
int esta_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}
 
int pop(Pilha* pilha, int* resultado) {
    if (esta_vazia(pilha)) return 0;
    No* temporario = pilha->topo;
    *resultado = temporario->valor;
    pilha->topo = temporario->proximo;
    free(temporario);
    return 1;
}
 
int topo(Pilha* pilha, int* resultado) {
    if (esta_vazia(pilha)) return 0;
    *resultado = pilha->topo->valor;
    return 1;
}
 
void imprimir_pilha(Pilha* pilha) {
    No* atual = pilha->topo;
    if (!atual) {
        printf("\n");
        return;
    }
 
    while (atual) {
        printf("%d", atual->valor);
        if (atual->proximo) printf(" ");
        atual = atual->proximo;
    }
    printf("\n");
}
 
void limpar_pilha(Pilha* pilha) {
    int descartado;
    while (pop(pilha, &descartado));
}
 
int tamanho(Pilha* pilha) {
    int contador = 0;
    No* atual = pilha->topo;
    while (atual) {
        contador++;
        atual = atual->proximo;
    }
    return contador;
}
 
int roll(Pilha* pilha, int n) {
    if (n == 1) return 1;
    if (n <= 0 || n > tamanho(pilha)) return 0;
 
    No* anterior = NULL;
    No* atual = pilha->topo;
 
    for (int i = 1; i < n; i++) {
        anterior = atual;
        atual = atual->proximo;
    }
 
    if (anterior) anterior->proximo = atual->proximo;
    atual->proximo = pilha->topo;
    pilha->topo = atual;
 
    return 1;
}
 
int main() {
    Pilha pilha = {NULL};
    int N;
    if (scanf("%d\n", &N) != 1 || N < 1 || N > 100) {
        printf("Erro: Quantidade invalida de comandos!\n");
        return 0;
    }
 
    char linha[100];
    char comando[20];
    int valor;
    int houve_print = 0;
 
    for (int i = 0; i < N; i++) {
        if (!fgets(linha, sizeof(linha), stdin)) break;
        int lidos = sscanf(linha, "%s %d", comando, &valor);
 
        if (strcmp(comando, "PUSH") == 0) {
            if (lidos != 2) {
                printf("Erro: PUSH sem valor!\n");
                return 0;
            }
            push(&pilha, valor);
 
        } else if (strcmp(comando, "POP") == 0) {
            if (!pop(&pilha, &valor)) {
                printf("Erro: Pilha vazia!\n");
                return 0;
            }
 
        } else if (strcmp(comando, "ADD") == 0 || strcmp(comando, "SUB") == 0 ||
                   strcmp(comando, "MUL") == 0 || strcmp(comando, "DIV") == 0) {
            int a, b;
            if (!pop(&pilha, &b) || !pop(&pilha, &a)) {
                printf("Erro: Elementos insuficiente para operacao!\n");
                return 0;
            }
 
            if (strcmp(comando, "ADD") == 0) push(&pilha, a + b);
            else if (strcmp(comando, "SUB") == 0) push(&pilha, a - b);
            else if (strcmp(comando, "MUL") == 0) push(&pilha, a * b);
            else {
                if (b == 0) {
                    printf("Erro: Divisao por zero!\n");
                    return 0;
                }
                push(&pilha, a / b);
            }
 
        } else if (strcmp(comando, "DUP") == 0) {
            if (!topo(&pilha, &valor)) {
                printf("Erro: Pilha vazia para DUP!\n");
                return 0;
            }
            push(&pilha, valor);
 
        } else if (strcmp(comando, "SWAP") == 0) {
            int a, b;
            if (!pop(&pilha, &a) || !pop(&pilha, &b)) {
                printf("Erro: Pilha insuficiente para SWAP!\n");
                return 0;
            }
            push(&pilha, a);
            push(&pilha, b);
 
        } else if (strcmp(comando, "ROLL") == 0) {
            if (lidos != 2) {
                printf("Erro: n fora dos limites!\n");
 
                return 0;
            }
            if (!roll(&pilha, valor)) {
                printf("Erro: Posicao invalida!\n");
                return 0;
            }
 
        } else if (strcmp(comando, "CLEAR") == 0) {
            limpar_pilha(&pilha);
 
        } else if (strcmp(comando, "PRINT") == 0) {
            imprimir_pilha(&pilha);
            houve_print = 1;
 
        } else {
            printf("Erro: Comando invalido!\n");
            return 0;
        }
    }
 
    if (!houve_print) {
        imprimir_pilha(&pilha);
    }
 
    return 0;
}
