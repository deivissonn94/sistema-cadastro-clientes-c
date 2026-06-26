#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include  "hash.h"



void liberar_memoria_hash(Tabela_hash *tabela)
{

    if (tabela == NULL)
    {

        printf("%sTabela não foi iniciada.%s\n\n", AMARELO, RESET);
        return;
    }

    for (size_t i = 0; i < TAMANHO_TABELA_HASH; i++)
    {
        No_hash *atual = tabela->baldes[i];

        while (atual != NULL)
        {
            No_hash *temp = atual;
            atual = atual->proximo;
            free(temp);
        }

        tabela->baldes[i] = NULL;
    }
}

void exibir_clientes_tabela_hash(Tabela_hash *tabela)
{

    if (tabela == NULL)
    {

        printf("%sTabela não foi iniciada.%s\n\n", AMARELO, RESET);
        return;
    }

    for (size_t i = 0; i < TAMANHO_TABELA_HASH; i++)
    {
        No_hash *atual = tabela->baldes[i];

        while (atual != NULL)
        {
            exibir_cliente(atual->cliente);
            atual = atual->proximo;
        }
    }
}

void remover_cliente_tabela_hash(Tabela_hash *tabela, const char *cpf_informado)
{

    if (tabela == NULL)
    {

        return;
    }

    int chave = cria_chave_hash(cpf_informado);

    No_hash *atual = tabela->baldes[chave];

    if (atual == NULL)
    {

        return;
    }

    if (strcmp(atual->cliente->cpf, cpf_informado) == 0)
    {

        tabela->baldes[chave] = tabela->baldes[chave]->proximo;
        free(atual);
        return;
    }

    bool encontrou = false;

    while (atual->proximo != NULL)
    {
        if (strcmp(atual->proximo->cliente->cpf, cpf_informado) == 0)
        {
            encontrou = true;
            break;
        }
        atual = atual->proximo;
    }

    if (encontrou)
    {

        No_hash *removido = atual->proximo;

        atual->proximo = atual->proximo->proximo;
        free(removido);
    }
}

void preencher_tabela_hash(Lista *lista, Tabela_hash *tabela)
{

    if (tabela == NULL)
    {

        printf("%sTabela não foi iniciada.%s\n\n", AMARELO, RESET);
        return;
    }

    if (lista == NULL || lista->cabeca == NULL)
    {
        return;
    }

    Cliente *atual = lista->cabeca;

    while (atual != NULL)
    {
        inserir_cliente_tabela_hash(atual, tabela);
        atual = atual->proximo;
    }
}

void executando_busca_por_cpf(Tabela_hash *tabela, const char *cpf_informado)
{

    Cliente *buscado = busca_por_cpf_cliente(tabela, cpf_informado);

    exibir_cliente_buscado_por_cpf(buscado);
}

void exibir_cliente_buscado_por_cpf(Cliente *cliente)
{

    if (cliente)
    {

        exibir_cliente(cliente);
    }
    else
    {

        printf("%sCPF informado não foi encontrado no sistema.%s\n\n", AMARELO, RESET);
    }
}

Cliente *busca_por_cpf_cliente(Tabela_hash *tabela, const char *cpf_informado)
{

    if (tabela == NULL)
    {

        printf("%sTabela não foi iniciada.%s\n\n", AMARELO, RESET);
        return NULL;
    }

    int chave = cria_chave_hash(cpf_informado);

    No_hash *buscado = tabela->baldes[chave];

    while (buscado != NULL)
    {
        if (strcmp(buscado->cliente->cpf, cpf_informado) == 0)
        {

            return buscado->cliente;
        }
        buscado = buscado->proximo;
    }

    return NULL;
}

No_hash *aloca_NoHash(Cliente *cliente)
{

    No_hash *novo = malloc(sizeof(No_hash));

    if (novo == NULL)
    {

        printf("%sErro na alocação do cliente hash .%s\n\n", VERMELHO, RESET);
        exit(EXIT_FAILURE);
    }

    novo->cliente = cliente;
    novo->proximo = NULL;

    return novo;
}

void inserir_cliente_tabela_hash(Cliente *cliente, Tabela_hash *tabela)
{
    if (tabela == NULL)
    {

        printf("%sTabela não foi iniciada.%s\n\n", AMARELO, RESET);
        return;
    }

    if (cliente == NULL)
    {

        printf("%sCliente não está cadastrado.%s\n\n", AMARELO, RESET);
        return;
    }

    int chave = cria_chave_hash(cliente->cpf);

    No_hash *novo = aloca_NoHash(cliente);

    novo->proximo = tabela->baldes[chave];
    tabela->baldes[chave] = novo;
}

int cria_chave_hash(const char *cpf_cliente)
{

    unsigned int hash = 0;

    for (int i = 0; cpf_cliente[i] != '\0'; i++)
    {

        hash = hash * 31 + cpf_cliente[i];
    }

    return hash % TAMANHO_TABELA_HASH;
}

void iniciar_tabela_hash(Tabela_hash *tabela)
{
    if(tabela == NULL)
    {
        return;
    }

    *tabela = (Tabela_hash){0};
}