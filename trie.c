#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <windows.h>
#include "trie.h"
#include "menu.h"

//-------------------------funções de liberacao------------------

void liberar_no_cliente(No_cliente *atual)
{

    while (atual != NULL)
    {

        No_cliente *temp = atual;
        atual = atual->proximo_cliente;
        free(temp);
    }
}

void liberar_trie(No_trie *atual)
{

    if (atual == NULL)
    {

        return;
    }

    for (size_t i = 0; i < TAMANHO_TRIE; i++)
    {
        liberar_trie(atual->filhos[i]);
    }

    liberar_no_cliente(atual->cliente);

    free(atual);
}

//-----------------------------------------------------------------------

void alocar_resultado_busca(Resultado_busca *resultado, size_t contador)
{

    // limpeza da strutc resultado
    free(resultado->clientes);
    *resultado = (Resultado_busca){0};

    if (contador == 0)
    {

        return;
    }

    resultado->capacidade = contador;

    resultado->clientes = aloca_capacidade_cliente_resultado(resultado->capacidade);
}

Cliente **aloca_capacidade_cliente_resultado(size_t capacidade)
{

    Cliente **novo = calloc(capacidade, sizeof(Cliente *));

    if (novo == NULL)
    {

        printf("%sErro na realocação do resultado .%s\n\n", VERMELHO, RESET);
        exit(EXIT_FAILURE);
    }

    return novo;
}

void iniciando_resultado_busca(Resultado_busca *resultado)
{

    *resultado = (Resultado_busca){0};
}

void conta_clientes_na_trie(No_trie *atual, size_t *contador)
{

    if (atual == NULL)
    {

        return;
    }

    if (atual->fim_palavra && atual->cliente)
    {

        No_cliente *aux = atual->cliente;

        while (aux != NULL)
        {
            (*contador)++;
            aux = aux->proximo_cliente;
        }
    }

    for (int i = 0; i < TAMANHO_TRIE; i++)
    {

        if (atual->filhos[i] != NULL)
        {

            conta_clientes_na_trie(atual->filhos[i], contador);
        }
    }
}

Cliente *realiza_busca_em_tempo_real_trie(No_trie *raiz, Resultado_busca *resultado)
{
    char buffer[TAMANHO_STRING] = {'\0'};
    int pos = 0;
    int selecionado = 0;

    printf("Busca: %s\n\n", buffer);

    while (true)
    {
        int tecla = getch();

        if (tecla == 0 || tecla == 224)
        {
            tecla = getch();

            switch (tecla)
            {
            case 72:
            {
                if (selecionado > 0)
                {
                    selecionado--;
                }
                break;
            }

            case 80:
            {
                if (selecionado < resultado->total - 1)
                {
                    selecionado++;
                }
                break;
            }
            }
        }
        else
        {

            if (tecla == 13) // Enter

            {

                if (resultado->total > 0)
                {

                    return resultado->clientes[selecionado];
                }
                return NULL;
            }

            if (tecla == 8)
            {
                if (pos > 0)
                {
                    pos--;
                    buffer[pos] = '\0';
                }
            }
            else
            {
                if (pos < TAMANHO_STRING - 1)
                {
                    buffer[pos++] = tecla;
                    buffer[pos] = '\0';
                }
            }
        }

        system("cls");

        printf("Busca: %s\n\n", buffer);

        if (buffer[0] != '\0')
        {
            realiza_busca_auto_complete(raiz, buffer, resultado);
            if (selecionado >= resultado->total)
                selecionado = 0;
        }

        for (size_t i = 0; i < resultado->total; i++)
        {
            if (i == selecionado)
                printf("> %s\n", resultado->clientes[i]->nome);
            else
                printf("  %s\n", resultado->clientes[i]->nome);
        }
    }
}

void atualizar_trie(Lista *lista, No_trie **raiz)
{

    liberar_trie(*raiz);

    *raiz = criar_trie();

    carregar_trie(lista, *raiz);
}

void carregar_trie(Lista *lista, No_trie *raiz)
{

    if (lista == NULL)
    {

        return;
    }

    Cliente *atual = lista->cabeca;

    while (atual != NULL)
    {
        inserir_nome_trie(raiz, atual);
        atual = atual->proximo;
    }
}

void realiza_busca_auto_complete(No_trie *raiz, const char *entrada, Resultado_busca *resultado)
{

    No_trie *retornado = busca_prefixo(raiz, entrada);

    if (retornado == NULL)
    {

        return;
    }

    size_t contador = 0;

    conta_clientes_na_trie(retornado, &contador);

    alocar_resultado_busca(resultado, contador);

    preencher_resultado(resultado, retornado);
}

void preencher_resultado(Resultado_busca *resultado, No_trie *atual)
{

    if (atual == NULL)
    {

        return;
    }

    if (atual->fim_palavra)
    {

        No_cliente *aux = atual->cliente;

        while (aux != NULL)
        {
            resultado->clientes[resultado->total++] = aux->cliente;
            aux = aux->proximo_cliente;
        }
    }

    for (int i = 0; i < TAMANHO_TRIE; i++)
    {

        if (atual->filhos[i] != NULL)
        {

            preencher_resultado(resultado, atual->filhos[i]);
        }
    }
}

No_trie *busca_prefixo(No_trie *raiz, const char *entrada)
{

    if (raiz == NULL)
    {

        return NULL;
    }

    char entrada_normalizada[TAMANHO_STRING];

    normalizar_nome(entrada, entrada_normalizada);

    No_trie *atual = raiz;

    for (int i = 0; entrada_normalizada[i] != '\0'; i++)
    {

        int indice = indice_trie(entrada_normalizada[i]);

        if (atual->filhos[indice] == NULL)
        {

            return NULL;
        }

        atual = atual->filhos[indice];
    }

    return atual;
}

void exibir_nomes_trie_no_cliente(No_trie *atual)
{

    if (atual == NULL)
    {

        return;
    }

    No_cliente *aux = atual->cliente;

    while (aux != NULL)
    {
        printf("%s\n", aux->cliente->nome);
        aux = aux->proximo_cliente;
    }
}

void listar_nomes_trie(No_trie *atual)
{

    if (atual == NULL)
    {
        return;
    }

    if (atual->fim_palavra)
    {

        exibir_nomes_trie_no_cliente(atual);
    }

    for (int i = 0; i < TAMANHO_TRIE; i++)
    {

        if (atual->filhos[i] != NULL)
        {

            listar_nomes_trie(atual->filhos[i]);
        }
    }
}

No_trie *busca_nome_trie(No_trie *raiz, const char *nome_buscado)
{

    No_trie *atual = raiz;

    char nome_normalizado[TAMANHO_STRING];

    normalizar_nome(nome_buscado, nome_normalizado);

    for (int i = 0; nome_normalizado[i] != '\0'; i++)
    {

        int indice = indice_trie(nome_normalizado[i]);

        if (atual->filhos[indice] == NULL)
            return NULL;

        atual = atual->filhos[indice];
    }

    if (atual != NULL && atual->fim_palavra)
        return atual;

    return NULL;
}

int indice_trie(char c)
{

    if (c == ' ')
    {

        return 26;
    }

    return c - 'a';
}

void inserir_nome_trie(No_trie *raiz, Cliente *cliente)
{

    No_trie *atual = raiz;

    char nome_normalizado[TAMANHO_STRING];

    normalizar_nome(cliente->nome, nome_normalizado);

    for (int i = 0; nome_normalizado[i] != '\0'; i++)
    {

        int indice = indice_trie(nome_normalizado[i]);

        if (atual->filhos[indice] == NULL)
        {

            atual->filhos[indice] = criar_trie();
        }

        atual = atual->filhos[indice];
    }

    No_cliente *novo = criar_no_cliente(cliente);

    atual->fim_palavra = true;
    novo->proximo_cliente = atual->cliente;
    atual->cliente = novo;
}

No_cliente *criar_no_cliente(Cliente *cliente)
{

    No_cliente *novo = malloc(sizeof *novo);

    if (novo == NULL)
    {

        printf("%sErro na alocação do No_cliente .%s\n\n", VERMELHO, RESET);
        exit(EXIT_FAILURE);
    }

    novo->cliente = cliente;
    novo->proximo_cliente = NULL;

    return novo;
}

No_trie *criar_trie(void)
{

    No_trie *novo = calloc(1, sizeof *novo);

    if (novo == NULL)
    {

        printf("%sErro na alocação da trie .%s\n\n", VERMELHO, RESET);
        exit(EXIT_FAILURE);
    }

    return novo;
}

void normalizar_nome(const char *entrada, char *saida)
{

    int j = 0;

    for (int i = 0; entrada[i] != '\0'; i++)
    {

        unsigned char c = entrada[i];

        if (c == 195)
        {

            char convertido = normalizar_acento((unsigned char)entrada[++i]);

            if (convertido != '\0')
            {

                saida[j++] = convertido;
            }

            continue;
        }

        if (c >= 'A' && c <= 'Z')
            c += 32;
        if ((c >= 'a' && c <= 'z') || c == ' ')
            saida[j++] = c;
    }

    saida[j] = '\0';
}

char normalizar_acento(unsigned char codigo)
{
    switch (codigo)
    {
    // a
    case 128: // À
    case 129: // Á
    case 130: // Â
    case 131: // Ã
    case 160: // à
    case 161: // á
    case 162: // â
    case 163: // ã
        return 'a';

    // c
    case 135: // Ç
    case 167: // ç
        return 'c';

    // e
    case 137: // É
    case 138: // Ê
    case 169: // é
    case 170: // ê
        return 'e';

    // i
    case 141: // Í
    case 173: // í
        return 'i';

    // o
    case 147: // Ó
    case 148: // Ô
    case 149: // Õ
    case 179: // ó
    case 180: // ô
    case 181: // õ
        return 'o';

    // u
    case 154: // Ú
    case 186: // ú
        return 'u';
    }

    return '\0';
}