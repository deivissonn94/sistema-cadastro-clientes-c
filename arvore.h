#ifndef ARVORE_H
#define ARVORE_H

#include "menu.h"
#include "lista.h"


typedef struct No_arvore
{
    Cliente *cliente;
    struct No_arvore *esquerda;
    struct No_arvore *direita;
}No_arvore;

typedef struct
{
    No_arvore *raiz;
}Arvore;

No_arvore *aloca_cliente_arovre(Cliente *cliente_atual);

void inserir_na_arovre(Cliente *atual,No_arvore **raiz);

void exibir_arvore_em_ordem(No_arvore *raiz);

void preencher_arovre(Lista *lista,Arvore *arvore);

void exibir_clientes_ordem_alfabetica(Lista *lista);

void liberar_memoria_NoAvore(No_arvore *raiz);

void liberar_memoria_arvore(Arvore *arvore);

#endif