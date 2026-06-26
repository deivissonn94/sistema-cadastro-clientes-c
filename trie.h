#ifndef TRIE_H
#define TRIE_H

#include "lista.h"
#include <conio.h>
#include <stddef.h>


typedef struct No_cliente
{
    Cliente *cliente;
    struct No_cliente *proximo_cliente;
} No_cliente;

typedef struct No_trie
{

    struct No_trie *filhos[TAMANHO_TRIE];

    No_cliente *cliente;

    bool fim_palavra;

} No_trie;

typedef struct 
{
    No_trie *raiz;
} Trie;

typedef struct Resultado_busca
{
    Cliente **clientes;
    size_t total;
    size_t capacidade;
} Resultado_busca;

No_trie *criar_trie(void);

void normalizar_nome(const char *entrada, char *saida);

int indice_trie(char c);

void inserir_nome_trie(No_trie *raiz, Cliente *cliente);

No_trie *busca_nome_trie(No_trie *raiz, const char *nome_buscado);

void listar_nomes_trie(No_trie *atual);

No_trie *busca_prefixo(No_trie *raiz, const char *entrada);

void realiza_busca_auto_complete(No_trie *raiz, const char *entrada,Resultado_busca *resultado);

No_cliente *criar_no_cliente(Cliente *cliente);

void exibir_nomes_trie_no_cliente(No_trie *atual);

char normalizar_acento(unsigned char codigo);

void liberar_no_cliente(No_cliente *atual);

void liberar_trie(No_trie *atual);

void carregar_trie(Lista *lista,No_trie *raiz);

void atualizar_trie(Lista *lista,No_trie **raiz);

Cliente *realiza_busca_em_tempo_real_trie(No_trie *raiz,Resultado_busca *resultado);

void iniciando_resultado_busca(Resultado_busca *resultado);

void conta_clientes_na_trie(No_trie *atual, size_t *contador);

Cliente **aloca_capacidade_cliente_resultado(size_t capacidade);

void alocar_resultado_busca(Resultado_busca *resultado,size_t contador);

void preencher_resultado(Resultado_busca *resultado,No_trie *atual);

#endif