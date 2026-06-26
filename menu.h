#ifndef MENU_H
#define MENU_H

#include <stdbool.h>
#include <stddef.h>
#include "config.h"
#include "lista.h"
#include "trie.h"

void captura_do_buffer(char *buffer,size_t tamanho_buffer);

void configurar_utf8(void);

bool valida_nome(const char *nome_digitado);

void exibir_descricao_cadastro_nome(void);

void entrada_nome(char *nome_digitado,void (*descricao)(void));

void exibir_descricao_nome_buscado(void);

int entrada_id(void);

void exibir_clientes_compactados(Cliente *atual);

void exibir_cliente(Cliente *atual);

bool valida_cpf(const char *cpf_informado);

void entrada_cpf(char *cpf_informado);

bool valida_email(const char *email);

void entrada_email(char *email_digitado);

void exibir_menu_pricipal(void);

bool valida_opcao(const char *opcao_digitada);

int entrada_opcao(void);

bool valida_numeros(const char *entrada);

void aguardar_enter(void);

void exibir_retorno_de_cliente_buscado(Cliente *cliente);

int confirmar_remocao(Cliente *buscado);



#endif