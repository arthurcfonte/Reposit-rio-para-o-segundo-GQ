#include <stdio.h>
#include <string.h>

#define TAM_CADASTRO 100

struct Conta {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[20];
    double saldo;
};

/* (a) Funcao de busca.
   Retorna a posicao da conta no cadastro; -1 se o cadastro estiver vazio;
   -2 se a conta nao for encontrada. */
int buscaConta(struct Conta cad[], int tam, int numero) {
    if (tam == 0) return -1;
    for (int i = 0; i < tam; i++) {
        if (cad[i].numero == numero) return i;
    }
    return -2;
}

/* (b) Procedimento para cadastrar uma nova conta */
void cadastrarConta(struct Conta cad[], int *tam, int numero) {
    if (*tam >= TAM_CADASTRO) {
        printf("Erro: cadastro cheio (maximo de %d contas).\n", TAM_CADASTRO);
        return;
    }
    if (buscaConta(cad, *tam, numero) >= 0) {
        printf("Nao e possivel cadastrar: numero de conta repetido.\n");
        return;
    }

    struct Conta nova;
    nova.numero = numero;
    printf("Nome do cliente: ");
    scanf(" %49[^\n]", nova.nome);
    printf("CPF: ");
    scanf(" %14[^\n]", nova.cpf);
    printf("Telefone: ");
    scanf(" %19[^\n]", nova.telefone);
    printf("Saldo inicial: ");
    scanf("%lf", &nova.saldo);
    if (nova.saldo < 0) {
        printf("Erro: o saldo inicial nao pode ser negativo.\n");
        return;
    }

    cad[*tam] = nova;   // insere no final do cadastro
    (*tam)++;
    printf("Conta cadastrada com sucesso.\n");
}

/* (c) Procedimento para consultar o saldo de uma conta */
void consultarSaldo(struct Conta cad[], int tam, int numero) {
    int pos = buscaConta(cad, tam, numero);
    if (pos < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }
    printf("Saldo da conta %d: R$ %.2f\n", numero, cad[pos].saldo);
}

/* (d) Procedimento para fazer um deposito */
void depositar(struct Conta cad[], int tam, int numero) {
    int pos = buscaConta(cad, tam, numero);
    if (pos < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    double valor;
    printf("Valor do deposito: ");
    scanf("%lf", &valor);
    if (valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }
    cad[pos].saldo += valor;
    printf("Deposito realizado. Novo saldo: R$ %.2f\n", cad[pos].saldo);
}

/* (e) Procedimento para fazer um saque */
void sacar(struct Conta cad[], int tam, int numero) {
    int pos = buscaConta(cad, tam, numero);
    if (pos < 0) {
        printf("Conta nao cadastrada.\n");
        return;
    }

    double valor;
    printf("Valor do saque: ");
    scanf("%lf", &valor);
    if (valor <= 0) {
        printf("Valor invalido.\n");
        return;
    }
    if (cad[pos].saldo >= valor) {
        cad[pos].saldo -= valor;
        printf("Saque realizado. Novo saldo: R$ %.2f\n", cad[pos].saldo);
    } else {
        printf("Nao existe saldo suficiente.\n");
    }
}

/* (f) Procedimento que exibe numero, nome e telefone de todas as contas */
void exibirContas(struct Conta cad[], int tam) {
    if (tam == 0) {
        printf("Cadastro vazio.\n");
        return;
    }
    for (int i = 0; i < tam; i++) {
        printf("Conta: %d | Titular: %s | Telefone: %s\n",
               cad[i].numero, cad[i].nome, cad[i].telefone);
    }
}

/* Auxiliar: pergunta qual cadastro usar (1 = corrente, 2 = poupanca) */
int escolherCadastro() {
    int tipo;
    do {
        printf("Cadastro (1 - Conta Corrente, 2 - Conta Poupanca): ");
        if (scanf("%d", &tipo) != 1) return 0;
    } while (tipo != 1 && tipo != 2);
    return tipo;
}

int main() {
    struct Conta corrente[TAM_CADASTRO], poupanca[TAM_CADASTRO];
    int tamCorrente = 0, tamPoupanca = 0;
    int opcao;

    do {
        printf("\n===== BANCO DINHEIRO CERTO =====\n");
        printf("1 - Cadastrar conta\n");
        printf("2 - Consultar saldo\n");
        printf("3 - Depositar\n");
        printf("4 - Sacar\n");
        printf("5 - Exibir contas\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        if (scanf("%d", &opcao) != 1) break;

        if (opcao < 0 || opcao > 5) {
            printf("Opcao invalida.\n");
            continue;
        }
        if (opcao == 0) {
            printf("Encerrando...\n");
            break;
        }

        int tipo = escolherCadastro();
        if (tipo == 0) break;
        struct Conta *cad = (tipo == 1) ? corrente : poupanca;
        int *tam = (tipo == 1) ? &tamCorrente : &tamPoupanca;

        if (opcao == 5) {
            exibirContas(cad, *tam);
        } else {
            int numero;
            printf("Numero da conta: ");
            scanf("%d", &numero);
            if (opcao == 1) cadastrarConta(cad, tam, numero);
            else if (opcao == 2) consultarSaldo(cad, *tam, numero);
            else if (opcao == 3) depositar(cad, *tam, numero);
            else if (opcao == 4) sacar(cad, *tam, numero);
        }
    } while (opcao != 0);

    return 0;
}
