#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os produtos
typedef struct {
    char nome[50];
    float precoPorKg;
    float quantidadeEmKg;
} Produto;

Produto estoque[100];  // Array de produtos
int quantidadeDeProdutos = 0;  // Contador de produtos no estoque

// Funções do admin
void menuAdmin();
void gerenciarEstoque();
void gerenciarVendas();  // Declaração da função para gerenciamento de vendas

// Funções de vendas
void menuVendas();
void realizarVenda();
void emitirRecibo(float total);

// Funções para estoque
void menuEstoque();
void adicionarProduto();
void removerProduto();
void consultarEstoque();

// Função de pesagem
float pesarProduto(float quantidade);

// Função de login
int login(char userType[]);

int main() {
    char userType[20];

    while (1) {
        printf("===== Sistema Hortifrúti =====\n");
        printf("Login como (admin/vendas/estoque): ");
        scanf("%s", userType);

        // Verifica o tipo de usuário e realiza o login
        if (!login(userType)) {
            printf("Acesso negado!\n");
            continue;  // Retorna para a tela de login
        }

        if (strcmp(userType, "admin") == 0) {
            menuAdmin();
        } else if (strcmp(userType, "vendas") == 0) {
            menuVendas();
        } else if (strcmp(userType, "estoque") == 0) {
            menuEstoque();
        }

        // Após sair do menu, volta para a tela de login
    }

    return 0;
}

// Função de login
int login(char userType[]) {
    char senha[20];

    printf("Digite a senha: ");
    scanf("%s", senha);

    // Verifica a senha de acordo com o tipo de usuário
    if (strcmp(userType, "admin") == 0 && strcmp(senha, "admin123") == 0) {
        return 1;
    } else if (strcmp(userType, "vendas") == 0 && strcmp(senha, "vendas123") == 0) {
        return 1;
    } else if (strcmp(userType, "estoque") == 0 && strcmp(senha, "estoque123") == 0) {
        return 1;
    }
    return 0;
}

// Funções do Admin
void menuAdmin() {
    int opcao;
    do {
        printf("\n===== Menu Admin =====\n");
        printf("1. Gerenciar Estoque\n");
        printf("2. Gerenciar Vendas\n");  // Adicionado gerenciamento de vendas
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                gerenciarEstoque();
                break;
            case 2:
                gerenciarVendas();  // Chama a função de gerenciamento de vendas
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

// Funções de Vendas
void gerenciarVendas() {
    menuVendas();  // Chama o menu de vendas para o admin
}

void menuVendas() {
    int opcao;
    do {
        printf("\n===== Menu Vendas =====\n");
        printf("1. Realizar Venda\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                realizarVenda();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void realizarVenda() {
    char nomeProduto[50];
    float quantidade, preco, total = 0.0;

    printf("\n===== Venda =====\n");

    // Solicita o nome do produto
    printf("Digite o nome do produto: ");
    fflush(stdin);
    scanf(" %[^\n]s", nomeProduto);  // Lê até a nova linha

    // Solicita a quantidade
    printf("Digite a quantidade (em Kg): ");
    scanf("%f", &quantidade);

    // Verifica o produto no estoque e realiza a venda
    for (int i = 0; i < quantidadeDeProdutos; i++) {
        if (strcmp(estoque[i].nome, nomeProduto) == 0) {
            preco = estoque[i].precoPorKg;
            if (estoque[i].quantidadeEmKg >= quantidade) {
                estoque[i].quantidadeEmKg -= quantidade;
                total = preco * pesarProduto(quantidade);
                printf("Produto: %s | Preco: R$%.2f/Kg | Quantidade: %.2f Kg | Total: R$%.2f\n",
                    estoque[i].nome, estoque[i].precoPorKg, quantidade, total);
            } else {
                printf("Quantidade indisponível no estoque!\n");
                return;
            }
        }
    }

    // Emite recibo da venda
    emitirRecibo(total);
}

void emitirRecibo(float total) {
    printf("\n===== Recibo =====\n");
    printf("Total da venda: R$%.2f\n", total);
    printf("Obrigado pela compra!\n");
}

// Funções para Estoque
void gerenciarEstoque() {
    // Chama o menu do estoque
    menuEstoque();
}

void menuEstoque() {
    int opcao;
    do {
        printf("\n===== Menu Estoque =====\n");
        printf("1. Adicionar Produto\n");
        printf("2. Remover Produto\n");
        printf("3. Consultar Estoque\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto();
                break;
            case 2:
                removerProduto();
                break;
            case 3:
                consultarEstoque();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}

void adicionarProduto() {
    printf("\n===== Adicionar Produto =====\n");

    // Solicita o nome do produto
    printf("Nome do produto: ");
    fflush(stdin);  // Limpa o buffer de entrada
    scanf(" %[^\n]s", estoque[quantidadeDeProdutos].nome);  // Lê até a nova linha

    // Solicita o preço por kg
    printf("Preco por Kg: ");
    scanf("%f", &estoque[quantidadeDeProdutos].precoPorKg);

    // Solicita a quantidade em kg
    printf("Quantidade em Kg: ");
    scanf("%f", &estoque[quantidadeDeProdutos].quantidadeEmKg);

    quantidadeDeProdutos++;
    printf("Produto adicionado com sucesso!\n");
}

void removerProduto() {
    char nomeProduto[50];
    printf("\n===== Remover Produto =====\n");
    printf("Nome do produto a ser removido: ");
    fflush(stdin);  // Limpa o buffer de entrada
    scanf(" %[^\n]s", nomeProduto);

    for (int i = 0; i < quantidadeDeProdutos; i++) {
        if (strcmp(estoque[i].nome, nomeProduto) == 0) {
            for (int j = i; j < quantidadeDeProdutos - 1; j++) {
                estoque[j] = estoque[j + 1];
            }
            quantidadeDeProdutos--;
            printf("Produto removido com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}

void consultarEstoque() {
    printf("\n===== Estoque Atual =====\n");
    for (int i = 0; i < quantidadeDeProdutos; i++) {
        printf("Produto: %s | Preco: R$%.2f/Kg | Quantidade: %.2f Kg\n",
               estoque[i].nome, estoque[i].precoPorKg, estoque[i].quantidadeEmKg);
    }
}

// Função de pesagem
float pesarProduto(float quantidade) {
    return quantidade;  // Aqui você pode adicionar lógica para "simular" o peso
}
//PIM204
