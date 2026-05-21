/*
descricao: operacoes matematicas com matrizes esparsas otimizadas atraves de listas encadeadas
disciplina: algoritmos e estruturas de dados 1 - unifesp
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int col;
    int val;
    struct Node* prox;
} Node;

typedef struct {
    Node** linhas;
    int n;
} MatrizEsparsa;

Node* criar_no(int col, int val) {
    Node* novo = (Node*)malloc(sizeof(Node));
    if (novo) {
        novo->col = col;
        novo->val = val;
        novo->prox = NULL;
    }
    return novo;
}

MatrizEsparsa* criar_matriz(int n) {
    int i;
    MatrizEsparsa* mat = (MatrizEsparsa*)malloc(sizeof(MatrizEsparsa));
    mat->n = n;
    mat->linhas = (Node**)malloc(n * sizeof(Node*));
    for (i = 0; i < n; i++) mat->linhas[i] = NULL;
    return mat;
}

void inserir(MatrizEsparsa* mat, int lin, int col, int val) {
    if (val == 0) return;
    Node* novo = criar_no(col, val);
    novo->prox = mat->linhas[lin];
    mat->linhas[lin] = novo;
}

MatrizEsparsa* ler_matriz(int n) {
    int i, j, val;
    MatrizEsparsa* mat = criar_matriz(n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            scanf("%d", &val);
            inserir(mat, i, j, val);
        }
    return mat;
}

int buscar(MatrizEsparsa* mat, int lin, int col) {
    Node* atual = mat->linhas[lin];
    while (atual) {
        if (atual->col == col) return atual->val;
        atual = atual->prox;
    }
    return 0;
}

MatrizEsparsa* soma(MatrizEsparsa* a, MatrizEsparsa* b) {
    int i, j, val;
    MatrizEsparsa* res = criar_matriz(a->n);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->n; j++) {
            val = buscar(a, i, j) + buscar(b, i, j);
            inserir(res, i, j, val);
        }
    }
    return res;
}

MatrizEsparsa* subtrai(MatrizEsparsa* a, MatrizEsparsa* b) {
    int i, j, val;
    MatrizEsparsa* res = criar_matriz(a->n);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->n; j++) {
            val = buscar(a, i, j) - buscar(b, i, j);
            inserir(res, i, j, val);
        }
    }
    return res;
}

MatrizEsparsa* multiplica(MatrizEsparsa* a, MatrizEsparsa* b) {
    int i, j, k, soma_val;
    MatrizEsparsa* res = criar_matriz(a->n);
    for (i = 0; i < a->n; i++) {
        for (j = 0; j < a->n; j++) {
            soma_val = 0;
            for (k = 0; k < a->n; k++) {
                soma_val += buscar(a, i, k) * buscar(b, k, j);
            }
            inserir(res, i, j, soma_val);
        }
    }
    return res;
}

void imprimir(MatrizEsparsa* mat) {
    int i, j;
    for (i = 0; i < mat->n; i++) {
        for (j = 0; j < mat->n; j++) {
            printf("%d", buscar(mat, i, j));
            if (j < mat->n - 1) printf(" ");
        }
        printf("\n");
    }
}

void liberar(MatrizEsparsa* mat) {
    int i;
    Node* atual;
    while (mat->linhas && (i = mat->n--)) {
        atual = mat->linhas[i - 1];
        while (atual) {
            Node* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(mat->linhas);
    free(mat);
}

int main() {
    int opcao, n;
    MatrizEsparsa *a, *b, *res;

    scanf("%d", &opcao);
    scanf("%d", &n);
    a = ler_matriz(n);
    b = ler_matriz(n);

    if (opcao == 1)
        res = soma(a, b);
    else if (opcao == 2)
        res = subtrai(a, b);
    else if (opcao == 3)
        res = multiplica(a, b);
    else
        return 0;

    imprimir(res);

    liberar(a);
    liberar(b);
    liberar(res);
    return 0;
}
