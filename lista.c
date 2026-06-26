#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "menu.h"
#include "lista.h"
#include "hash.h"

void remover_da_lista_por_nome(Lista *lista, Tabela_hash *tabela, No_trie *raiz, Resultado_busca *resultado)
{

    if (lista->cabeca == NULL || tabela == NULL)
    {

        printf("%sNão é possivel fazer nenhuma remoção pois a lista está vazia !%s\n\n", AMARELO, RESET);
        return;
    }

    Cliente *buscado = realiza_busca_em_tempo_real_trie(raiz, resultado);

    if (buscado == NULL)
    {

        printf("%sNenhum cliente encontrado ou selecionado.%s\n\n", AMARELO, RESET);
        return;
    }

    int opcao_retornada = confirmar_remocao(buscado);

    if (opcao_retornada == 1)
    {

        remover_cliente_tabela_hash(tabela, buscado->cpf);
        remover_da_lista_por_id(lista, buscado->id);
        printf("%sCliente removido com sucesso!%s\n\n", VERDE, RESET);
    }
    else
    {

        printf("%sOperação cancelada. Retornando ao menu principal.%s\n\n", AMARELO, RESET);
    }
}

Cliente *busca_cliente_por_id(Lista *lista, int id_buscado)
{

    if (lista == NULL)
    {

        return NULL;
    }

    Cliente *atual = lista->cabeca;

    while (atual != NULL)
    {
        if (atual->id == id_buscado)
        {

            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

void remover_da_lista_por_id(Lista *lista, int id_alvo)
{

    if (lista->cabeca == NULL)
    {

        printf("%sNão é possível fazer nenhuma remoção, pois a lista está vazia!%s\n\n", AMARELO, RESET);
        return;
    }

    Cliente *atual = busca_cliente_por_id(lista, id_alvo);

    if (atual == NULL)
    {

        printf("%sID do cliente não foi encontrado !%s\n\n", AMARELO, RESET);
        return;
    }

    if (atual == lista->cabeca && lista->cabeca == lista->cauda)
    {

        free(atual);
        lista->cabeca = lista->cauda = NULL;
    }
    else if (atual == lista->cabeca)
    {

        lista->cabeca = lista->cabeca->proximo;
        lista->cabeca->anterior = NULL;
        free(atual);
    }
    else if (atual == lista->cauda)
    {

        lista->cauda = lista->cauda->anterior;
        lista->cauda->proximo = NULL;
        free(atual);
    }
    else
    {

        atual->anterior->proximo = atual->proximo;
        atual->proximo->anterior = atual->anterior;
        free(atual);
    }
}

void iniciar_lista(Lista *lista)
{

    *lista = (Lista){0};
    lista->id_proximo = 1;
}

void inserir_na_lista(Lista *lista, const char *nome, const char *cpf, const char *email)
{

    Cliente *novo = criar_cliente(lista, nome, cpf, email);

    if (lista->cabeca == NULL)
    {

        lista->cabeca = lista->cauda = novo;
    }
    else
    {

        lista->cauda->proximo = novo;
        novo->anterior = lista->cauda;
        lista->cauda = novo;
    }
}

Cliente *criar_cliente(Lista *lista, const char *nome, const char *cpf, const char *email)
{

    Cliente *novo = malloc(sizeof *novo);
    if (novo == NULL)
    {

        printf("%sErro na alocação do cliente .%s\n\n", VERMELHO, RESET);
        exit(EXIT_FAILURE);
    }

    novo->id = lista->id_proximo++;

    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';

    strncpy(novo->cpf, cpf, sizeof(novo->cpf) - 1);
    novo->cpf[sizeof(novo->cpf) - 1] = '\0';

    strncpy(novo->email, email, sizeof(novo->email) - 1);
    novo->email[sizeof(novo->email) - 1] = '\0';

    novo->proximo = novo->anterior = NULL;

    return novo;
}

void exibir_clientes_ordem_cadastro(Lista *lista)
{

    if (lista->cabeca == NULL)
    {

        printf("%sNenhum cliente está cadastrado.%s\n\n", AMARELO, RESET);
        return;
    }

    Cliente *atual = lista->cabeca;

    while (atual != NULL)
    {
        exibir_cliente(atual);

        atual = atual->proximo;
    }
}

void liberar_memoria_da_lista(Lista *lista)
{

    Cliente *atual = lista->cabeca;

    while (atual != NULL)
    {
        Cliente *temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    lista->cabeca = lista->cauda = NULL;
}
