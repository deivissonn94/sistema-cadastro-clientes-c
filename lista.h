#ifndef LISTA_H
#define LISTA_H

#include "config.h"
#include <stdbool.h>
#include <stddef.h>


typedef struct Tabela_hash Tabela_hash;
typedef struct No_trie No_trie;
typedef struct Resultado_busca Resultado_busca;


typedef struct Cliente
{
    int id;
    char nome[TAMANHO_STRING];
    char cpf[TAMANHO_CPF];
    char email[TAMANHO_STRING];
    

    struct Cliente *proximo;
    struct Cliente *anterior;

} Cliente;

typedef struct Lista
{
    int id_proximo;

    Cliente *cabeca;
    Cliente *cauda;

} Lista;

void iniciar_lista(Lista *lista);

Cliente *criar_cliente(Lista *lista, const char *nome, const char *cpf, const char *email);

void inserir_na_lista(Lista *lista, const char *nome, const char *cpf, const char *email);

void remover_da_lista_por_id(Lista *lista, int id_alvo);

void remover_da_lista_por_nome(Lista *lista, Tabela_hash *tabela, No_trie *raiz, Resultado_busca *resultado);

void exibir_clientes_ordem_cadastro(Lista *lista);

void liberar_memoria_da_lista(Lista *lista);

Cliente *busca_cliente_por_id(Lista *lista,int id_buscado);



#endif