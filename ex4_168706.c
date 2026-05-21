#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int val;
    struct No* prox;
} No;

typedef struct Pilha {
    char* nome;
    No* topo;
    struct Pilha* prox;
} Pilha;

Pilha* cabeca = NULL;

Pilha* busca_pilha(const char* nome) {
    for (Pilha* p = cabeca; p; p = p->prox)
        if (strcmp(p->nome, nome) == 0)
            return p;
    return NULL;
}

void remove_pilha(Pilha* p) {
    Pilha* ant = NULL;
    Pilha* atual = cabeca;
    while (atual) {
        if (atual == p) {
            if (ant) ant->prox = atual->prox;
            else cabeca = atual->prox;
            free(atual->nome);
            free(atual);
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
}

void cria_pilha(const char* nome) {
    if (busca_pilha(nome)) return;
    Pilha* p = malloc(sizeof(Pilha));
    p->nome = strdup(nome);
    p->topo = NULL;
    p->prox = cabeca;
    cabeca = p;
}

void força_cria_pilha(const char* nome, No* topo) {
    Pilha* p = busca_pilha(nome);
    if (p) remove_pilha(p);
    Pilha* nova = malloc(sizeof(Pilha));
    nova->nome = strdup(nome);
    nova->topo = topo;
    nova->prox = cabeca;
    cabeca = nova;
}

void empilha(Pilha* p, int x) {
    No* n = malloc(sizeof(No));
    n->val = x;
    n->prox = p->topo;
    p->topo = n;
}

int desempilha(Pilha* p, const char* nome) {
    if (!p->topo) {
        printf("Pilha %s vazia!\n", nome);
        return 1;
    }
    No* t = p->topo;
    p->topo = t->prox;
    free(t);
    if (!p->topo) remove_pilha(p);
    return 0;
}

void imprime_valores(No* topo) {
    printf("[");
    for (No* n = topo; n; n = n->prox) {
        printf("%d", n->val);
        if (n->prox) printf(", ");
    }
    printf("]");
}

int cmd_imprime(Pilha* p, const char* nome) {
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        return 1;
    }
    imprime_valores(p->topo);
    printf("\n");
    return 0;
}

void cmd_mostra() {
    if (!cabeca) {
        printf("\n");
        return;
    }
    for (Pilha* p = cabeca; p; p = p->prox) {
        printf("%s:\t", p->nome);
        imprime_valores(p->topo);
        printf("\n");
    }
}

int cmd_topo(Pilha* p, const char* nome) {
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        return 1;
    }
    if (!p->topo) {
        printf("Pilha %s vazia!\n", nome);
        return 1;
    }
    printf("%d\n", p->topo->val);
    return 0;
}

int cmd_funde(const char* n1, const char* n2) {
    Pilha* p1 = busca_pilha(n1);
    Pilha* p2 = busca_pilha(n2);
    if (!p1 || !p2) {
        printf("Erro: pilhas nao encontradas!\n");
        return 1;
    }
    if (p2->topo) {
        No* aux = p2->topo;
        while (aux->prox) aux = aux->prox;
        aux->prox = p1->topo;
        p1->topo = p2->topo;
    }
    remove_pilha(p2);
    return 0;
}

int cmd_separa(const char* origem, const char* destino, int k) {
    Pilha* p1 = busca_pilha(origem);
    if (!p1) {
        printf("Pilha %s nao encontrada!\n", origem);
        return 1;
    }

    int tamanho = 0;
    No* temp = p1->topo;
    while (temp) {
        tamanho++;
        temp = temp->prox;
    }

    if (k > tamanho) {
        k = tamanho;
    }

    if (k == 0) {
        força_cria_pilha(destino, NULL);
        return 0;
    }

    No* p = p1->topo;
    int count = 0;
    No* novo_topo = p;
    No* anterior = NULL;

    while (p && count < k) {
        anterior = p;
        p = p->prox;
        count++;
    }

    p1->topo = p;
    anterior->prox = NULL;

    if (!p1->topo) remove_pilha(p1);

    força_cria_pilha(destino, novo_topo);
    return 0;
}

void libera_tudo() {
    while (cabeca) {
        Pilha* p = cabeca;
        cabeca = cabeca->prox;
        No* n = p->topo;
        while (n) {
            No* t = n;
            n = n->prox;
            free(t);
        }
        free(p->nome);
        free(p);
    }
}

int main() {
    char linha[256];
    int N = 0;

    while (N < 1 || N > 100) {
        if (!fgets(linha, sizeof(linha), stdin)) return 1;
        sscanf(linha, "%d", &N);
    }

    for (int i = 0; i < N; i++) {
        if (!fgets(linha, sizeof(linha), stdin)) break;
        linha[strcspn(linha, "\r\n")] = 0;

        if (strncmp(linha, "SHOW", 4) == 0) {
            cmd_mostra();
        } else if (strncmp(linha, "SPLIT", 5) == 0) {
            char o[64], d[64];
            int x;
            if (sscanf(linha + 5, "%63s %63s %d", o, d, &x) == 3) {
                if (cmd_separa(o, d, x)) {
                    libera_tudo();
                    return 1;
                }
            }
        } else if (strncmp(linha, "MERGE", 5) == 0) {
            char n1[64], n2[64];
            if (sscanf(linha + 5, "%63s %63s", n1, n2) == 2) {
                if (cmd_funde(n1, n2)) {
                    libera_tudo();
                    return 1;
                }
            }
        } else {
            char nome[64], raw[64];
            if (sscanf(linha, "%63[^:]:%63[^\n]", nome, raw) == 2) {
                char *cmd = raw;
                while (*cmd == ' ' || *cmd == '\t') cmd++;

                if (strcmp(cmd, "INIT") == 0) {
                    cria_pilha(nome);
                } else if (strncmp(cmd, "PUSH", 4) == 0) {
                    char *arg = cmd + 4;
                    while (*arg == ' ' || *arg == '\t') arg++;
                    int v;
                    if (sscanf(arg, "%d", &v) == 1) {
                        Pilha* p = busca_pilha(nome);
                        if (!p) {
                            printf("Pilha %s nao encontrada!\n", nome);
                            libera_tudo();
                            return 1;
                        }
                        empilha(p, v);
                    }
                } else if (strcmp(cmd, "POP") == 0) {
                    Pilha* p = busca_pilha(nome);
                    if (!p) {
                        printf("Pilha %s nao encontrada!\n", nome);
                        libera_tudo();
                        return 1;
                    }
                    if (desempilha(p, nome)) {
                        libera_tudo();
                        return 1;
                    }
                } else if (strcmp(cmd, "TOP") == 0) {
                    Pilha* p = busca_pilha(nome);
                    if (cmd_topo(p, nome)) {
                        libera_tudo();
                        return 1;
                    }
                } else if (strcmp(cmd, "PRINT") == 0) {
                    Pilha* p = busca_pilha(nome);
                    if (cmd_imprime(p, nome)) {
                        libera_tudo();
                        return 1;
                    }
                }
            }
        }
    }

    libera_tudo();
    return 0;
}
