#ifndef HASH_H
#define HASH_H


#include "lista.h"
#include "arvore.h"


typedef struct No_hash
{

    Cliente *cliente;
    struct No_hash *proximo;
} No_hash;

typedef struct Tabela_hash
{
    No_hash *baldes[TAMANHO_TABELA_HASH];
} Tabela_hash;

int cria_chave_hash(const char *cpf_cliente);

void iniciar_tabela_hash(Tabela_hash *tabela);

No_hash *aloca_NoHash(Cliente *cliente);

void inserir_cliente_tabela_hash(Cliente *cliente, Tabela_hash *tabela);

Cliente *busca_por_cpf_cliente(Tabela_hash *tabela, const char *cpf_informado);

void exibir_cliente_buscado_por_cpf(Cliente *cliente);

void executando_busca_por_cpf(Tabela_hash *tabela, const char *cpf_informado);

void preencher_tabela_hash(Lista *lista, Tabela_hash *tabela);

void exibir_clientes_tabela_hash(Tabela_hash *tabela);

void liberar_memoria_hash(Tabela_hash *tabela);

void remover_cliente_tabela_hash(Tabela_hash *tabela, const char *cpf_informado);

#endif
