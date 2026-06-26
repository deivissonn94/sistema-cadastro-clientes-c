#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "config.h"
#include "lista.h"
#include "hash.h"

typedef struct
{
    int id;
    char nome[TAMANHO_STRING];
    char cpf[TAMANHO_CPF];
    char email[TAMANHO_STRING];

} Cliente_arquivo;

void salvar_clientes(Lista *lista);

void carregar_clientes(Lista *lista,Tabela_hash *tabela);

void inserir_dados_no_carregamento(Lista *lista,const Cliente_arquivo *temp,Tabela_hash *tabela);

#endif