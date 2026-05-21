#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct No {
    int codigo;
    char descricao[51];
    struct No* prox;
    struct No* ant;
} No;
 
No* inicio = NULL;
 
No* cria_no(int codigo, const char* descricao) {
    No* novo_no;
    novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) {
        return (0);
    }
    novo_no->codigo = codigo;
    strncpy(novo_no->descricao, descricao, 50);
    novo_no->descricao[50] = '\0';
    novo_no->prox = novo_no->ant = NULL;
    return novo_no;
}
 
int existe(int codigo) {
    No* atual;
    if (inicio == NULL) {
        return 0;
    }
    atual = inicio;
    do {
        if (atual->codigo == codigo) {
            return 1;
        }
        atual = atual->prox;
    } while (atual != inicio);
    return 0;
}
 
void ADD (int codigo, const char* descricao) {
    No* novo_no;
    No* ultimo;
    if (existe(codigo)) {
        printf("Codigo ja existente!\n");
        return;
    }
    novo_no = cria_no(codigo, descricao);
    if (inicio == NULL) {
        inicio = novo_no;
        inicio->prox = inicio->ant = inicio;
    } else {
        ultimo = inicio->ant;
        ultimo->prox = novo_no;
        novo_no->ant = ultimo;
        novo_no->prox = inicio;
        inicio->ant = novo_no;
    }
}
 
void REMOVE (int codigo) {
    No* atual;
    No* a_remover;
    if (inicio == NULL) {
        printf("Codigo nao encontrado!\n");
        return;
    }
    atual = inicio;
    do {
        if (atual->codigo == codigo) {
            a_remover = atual;
            if (a_remover->prox == a_remover) {
                inicio = NULL;
            } else {
                a_remover->ant->prox = a_remover->prox;
                a_remover->prox->ant = a_remover->ant;
                if (a_remover == inicio) {
                    inicio = a_remover->prox;
                }
            }
            free(a_remover);
            return;
        }
        atual = atual->prox;
    } while (atual != inicio);
    printf("Codigo nao encontrado!\n");
}
 
void PRINT_FORWARD() {
    No* atual;
    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    atual = inicio;
    do {
        printf("Codigo: %d - %s\n", atual->codigo, atual->descricao);
        atual = atual->prox;
    } while (atual != inicio);
}
 
void PRINT_REVERSE() {
    No* atual;
    if (inicio == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    atual = inicio->ant;
    do {
        printf("Codigo: %d - %s\n", atual->codigo, atual->descricao);
        atual = atual->ant;
    } while (atual != inicio->ant);
}
 
void SEARCH (int codigo) {
    No* atual;
    if (inicio == NULL) {
        printf("Codigo nao encontrado!\n");
        return;
    }
    atual = inicio;
    do {
        if (atual->codigo == codigo) {
            printf("Codigo: %d - %s\n", atual->codigo, atual->descricao);
            return;
        }
        atual = atual->prox;
    } while (atual != inicio);
    printf("Codigo nao encontrado!\n");
}
 
void limpa_lista() {
    No* atual;
    No* temp;
    if (inicio == NULL) {
        return;
    }
    atual = inicio->prox;
    while (atual != inicio) {
        temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(inicio);
    inicio = NULL;
}
 
int main() {
    int N, cont=0, code;
    char linha[200], cmd[20], desc[100];
 
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 0;
    }
    if (sscanf(linha, "%d", &N) != 1) {
        return 0;
    }
    if (N < 1 || N > 100) {
        printf("N nao e valido!\n");
        return 0;
    }
    
    while (fgets(linha, sizeof(linha), stdin) != NULL) {
        cont++;
        if (sscanf(linha, "%s", cmd) != 1) {
            continue;
        }
        if (strcmp(cmd, "ADD") == 0) {
            if (sscanf(linha, "%*s %d %[^\n]", &code, desc) >= 2) {
                ADD(code, desc);
            }
        } else if (strcmp(cmd, "REMOVE") == 0) {
            if (sscanf(linha, "%*s %d", &code) == 1) {
                REMOVE (code);
            }
        } else if (strcmp(cmd, "PRINT_FORWARD") == 0) {
            PRINT_FORWARD();
        } else if (strcmp(cmd, "PRINT_REVERSE") == 0) {
            PRINT_REVERSE();
        } else if (strcmp(cmd, "SEARCH") == 0) {
            if (sscanf(linha, "%*s %d", &code) == 1) {
                SEARCH (code);
            }
        }
    }
 
    if (cont < N) {
        printf("N superior ao numero de comandos!\n");
    }
    if (cont > N){
        printf("Numero de comandos superior a N!\n");
    }
 
    limpa_lista();
    return 0;
}