/*
descricao: controle de compras de clientes usando structs e alocacao dinamica de vetores
disciplina: algoritmos e estruturas de dados 1 - unifesp
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_LIVROS 100

typedef struct {
    float dinheiro;
    int qtd_livros;
    float *precos;
} Cliente;


Cliente* lerDadosClientes(int N) {
    Cliente *clientes = malloc(N * sizeof(Cliente));
    if (clientes == NULL) {
        return NULL;
    }

    for (int i = 0; i < N; i++) {
        do {
            scanf("%f", &clientes[i].dinheiro);
        } while (clientes[i].dinheiro < 0);

        do {
            scanf("%d", &clientes[i].qtd_livros);
        } while (clientes[i].qtd_livros < 0 || clientes[i].qtd_livros > MAX_LIVROS);

        if (clientes[i].qtd_livros > 0) {
            clientes[i].precos = malloc(clientes[i].qtd_livros * sizeof(float));
            if (clientes[i].precos == NULL) {
                return NULL;
            }

            for (int j = 0; j < clientes[i].qtd_livros; j++) {
                do {
                    scanf("%f", &clientes[i].precos[j]);
                } while (clientes[i].precos[j] < 0);
            }
        }
    }
    return clientes;
}

void calcularCompras(Cliente *clientes, int N) {
    for (int i = 0; i < N; i++) {
        float dinheiro = clientes[i].dinheiro;
        int comprados = 0;

        for (int j = 0; j < clientes[i].qtd_livros; j++) {
            if (dinheiro >= clientes[i].precos[j]) {
                dinheiro -= clientes[i].precos[j];
                comprados++;
            }
        }

        printf("%d %.2f\n", comprados, dinheiro);
    }
}

int main() {
    int N;
    do {
        scanf("%d", &N);
    } while (N < 1 || N > 100);

    Cliente *clientes = lerDadosClientes(N);
    calcularCompras(clientes, N);

    for (int i = 0; i < N; i++) {
        if (clientes[i].precos != NULL) {
            free(clientes[i].precos);
        }
    }
    free(clientes);

    return 0;
}
