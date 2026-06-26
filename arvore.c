#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "arvore.h"

void exibir_arvore_em_ordem(No_arvore *raiz)
{

    if (raiz != NULL)
    {

        exibir_arvore_em_ordem(raiz->esquerda);
        exibir_cliente(raiz->cliente);
        exibir_arvore_em_ordem(raiz->direita);
    }
}

void preencher_arovre(Lista *lista, Arvore *arvore)
{

    if (lista == NULL || lista->cabeca == NULL)
    {
        return;
    }

    Cliente *atual = lista->cabeca;

    while (atual != NULL)
    {
        inserir_na_arovre(atual, &arvore->raiz);
        atual = atual->proximo;
    }
}

void inserir_na_arovre(Cliente *atual, No_arvore **raiz)
{

    if (*raiz == NULL)
    {

        *raiz = aloca_cliente_arovre(atual);
        return;
    }

    if (strcmp(atual->nome, (*raiz)->cliente->nome) < 0)
    {

        inserir_na_arovre(atual, &(*raiz)->esquerda);
    }
    else
    {

        inserir_na_arovre(atual, &(*raiz)->direita);
    }
}

No_arvore *aloca_cliente_arovre(Cliente *cliente_atual)
{

    No_arvore *novo = malloc(sizeof *novo);

    if (novo == NULL)
    {

        printf("%sErro na alocação no NO da árvore .%s\n\n", VERMELHO, RESET);
        exit(EXIT_FAILURE);
    }

    novo->cliente = cliente_atual;
    novo->direita = novo->esquerda = NULL;

    return novo;
}

void exibir_clientes_ordem_alfabetica(Lista *lista)
{

    printf("\n\n");

    Arvore arvore = {0};

    preencher_arovre(lista, &arvore);

    if (arvore.raiz == NULL)
    {

        printf("%sNenhum cliente está cadastrado.%s\n\n", AMARELO, RESET);
    }
    else
    {

        exibir_arvore_em_ordem(arvore.raiz);

        liberar_memoria_arvore(&arvore);
    }
}

void liberar_memoria_NoAvore(No_arvore *raiz)
{

    if (raiz == NULL)
    {

        return;
    }

    liberar_memoria_NoAvore(raiz->esquerda);
    liberar_memoria_NoAvore(raiz->direita);
    free(raiz);
}

void liberar_memoria_arvore(Arvore *arvore)
{

    liberar_memoria_NoAvore(arvore->raiz);
    arvore->raiz = NULL;
}