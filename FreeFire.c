#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10 // Capacidade máxima da mochila

/*
 * Programa: Sistema de Inventário - Mochila de Loot
 * Objetivo: Simular uma mochila virtual que armazena itens coletados pelo jogador.
 *
 * Funcionalidades:
 *  - Cadastrar até 10 itens
 *  - Remover item pelo nome
 *  - Listar todos os itens
 *  - Buscar item pelo nome (busca sequencial)
 *
 * Estrutura usada:
 *  struct Item -> nome, tipo e quantidade
 *  Vetor de structs -> representa a mochila (lista sequencial)
 */

// Definição da estrutura que representa um item
struct Item {
    char nome[30];
    char tipo[20];
    int quantidade;
};

// Funções do sistema
void inserirItem(struct Item mochila[], int *contador);
void removerItem(struct Item mochila[], int *contador);
void listarItens(struct Item mochila[], int contador);
void buscarItem(struct Item mochila[], int contador);

int main() {
    struct Item mochila[MAX_ITENS];
    int contador = 0; // Número de itens na mochila
    int opcao;

    printf("=== SISTEMA DE INVENTÁRIO - MOCHILA DE LOOT ===\n");

    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &contador);
                break;
            case 2:
                removerItem(mochila, &contador);
                break;
            case 3:
                listarItens(mochila, contador);
                break;
            case 4:
                buscarItem(mochila, contador);
                break;
            case 0:
                printf("Encerrando o sistema... Até mais, sobrevivente!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

/*
 * Função: inserirItem
 * Objetivo: cadastrar um novo item na mochila, se houver espaço.
 */
void inserirItem(struct Item mochila[], int *contador) {
    if (*contador >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    struct Item novo;

    printf("\n--- Cadastro de Novo Item ---\n");
    printf("Digite o nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o \n do final

    printf("Digite o tipo do item (arma, municao, cura, ferramenta...): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*contador] = novo;
    (*contador)++;

    printf("Item '%s' adicionado com sucesso à mochila!\n", novo.nome);
}

/*
 * Função: removerItem
 * Objetivo: remover um item da mochila pelo nome (busca sequencial).
 */
void removerItem(struct Item mochila[], int *contador) {
    if (*contador == 0) {
        printf("A mochila está vazia. Nenhum item para remover.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = -1;
    for (int i = 0; i < *contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }

    if (encontrado != -1) {
        // Desloca os elementos à esquerda
        for (int i = encontrado; i < *contador - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*contador)--;
        printf("Item '%s' removido da mochila.\n", nomeBusca);
    } else {
        printf("Item '%s' não encontrado.\n", nomeBusca);
    }
}

/*
 * Função: listarItens
 * Objetivo: exibir todos os itens da mochila.
 */
void listarItens(struct Item mochila[], int contador) {
    if (contador == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n--- Itens na Mochila ---\n");
    for (int i = 0; i < contador; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
        printf("-----------------------------\n");
    }
}

/*
 * Função: buscarItem
 * Objetivo: localizar um item na mochila com base no nome (busca sequencial).
 */
void buscarItem(struct Item mochila[], int contador) {
    if (contador == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < contador; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("  Nome: %s\n", mochila[i].nome);
            printf("  Tipo: %s\n", mochila[i].tipo);
            printf("  Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

