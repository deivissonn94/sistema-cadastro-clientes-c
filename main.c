// Alguns compiladores (GCC/MinGW) ignoram esta pragma.
// Se estiver usando MSVC e houver problemas de acentuação,
// experimente habilitá-la novamente.

// #pragma execution_character_set("utf-8")

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "hash.h"
#include "persistencia.h"
#include "trie.h"
#include <conio.h>

int main(void)
{

    // Configurando UTF-8 para a saída no terminal
    configurar_utf8();

    // Iniciando dados na memória stack
    Lista lista;
    Tabela_hash tabela;
    Trie trie;
    Resultado_busca resultado_tempo_real;

    iniciar_lista(&lista);
    iniciar_tabela_hash(&tabela);
    trie.raiz = criar_trie();
    iniciando_resultado_busca(&resultado_tempo_real);

    // carregando dados dos clientes
    carregar_clientes(&lista, &tabela);
    carregar_trie(&lista, trie.raiz);

    // Laço do programa principal
    int opcao_menu_pricipal;
    bool loop = true;

    while (loop)
    {

        exibir_menu_pricipal();
        opcao_menu_pricipal = entrada_opcao();

        switch (opcao_menu_pricipal)
        {
        case 1:
        {

            char buffer_nome[TAMANHO_STRING];
            entrada_nome(buffer_nome, exibir_descricao_cadastro_nome);

            char buffer_cpf[TAMANHO_CPF];
            entrada_cpf(buffer_cpf);

            if (busca_por_cpf_cliente(&tabela, buffer_cpf) != NULL)
            {

                printf("%sCPF já cadastrado!%s\n\n", AMARELO, RESET);

                aguardar_enter();
                system("cls");
                break;
            }

            char buffer_email[TAMANHO_STRING];
            entrada_email(buffer_email);

            inserir_na_lista(&lista, buffer_nome, buffer_cpf, buffer_email);

            inserir_cliente_tabela_hash(lista.cauda, &tabela);

            inserir_nome_trie(trie.raiz, lista.cauda);

            printf("%sCliente cadastrado com sucesso!%s\n\n", VERDE, RESET);

            aguardar_enter();
            system("cls");

            break;
        }
        case 2:
        {
            int id_buscado = entrada_id();

            Cliente *cliente = busca_cliente_por_id(&lista, id_buscado);

            exibir_retorno_de_cliente_buscado(cliente);

            aguardar_enter();
            system("cls");

            break;
        }
        case 3:

        {
            char cpf_buscado[TAMANHO_STRING];

            entrada_cpf(cpf_buscado);

            Cliente *cliente = busca_por_cpf_cliente(&tabela, cpf_buscado);

            exibir_retorno_de_cliente_buscado(cliente);

            aguardar_enter();
            system("cls");

            break;
        }
        case 4:

        {

            Cliente *cliente_buscado = realiza_busca_em_tempo_real_trie(trie.raiz, &resultado_tempo_real);

            system("cls");

            if (cliente_buscado)
            {

                exibir_cliente(cliente_buscado);
            }
            else
            {

                printf("%sNenhum cliente encontrado ou selecionado.%s\n\n", AMARELO, RESET);
            }

            aguardar_enter();
            system("cls");

            break;
        }
        case 5:
        {
            if (lista.cabeca == NULL)
            {

                printf("%sNão é possível fazer nenhuma remoção, pois a lista está vazia!%s\n\n", AMARELO, RESET);
                aguardar_enter();
                system("cls");
                break;
            }

            int id_buscado = entrada_id();

            Cliente *buscado = busca_cliente_por_id(&lista, id_buscado);

            if (buscado == NULL)
            {

                printf("%sID do cliente não foi encontrado.%s\n\n", AMARELO, RESET);
            }
            else
            {

                remover_cliente_tabela_hash(&tabela, buscado->cpf);
                remover_da_lista_por_id(&lista, buscado->id);
                atualizar_trie(&lista, &trie.raiz);

                printf("%sCliente removido com sucesso!%s\n\n", VERDE, RESET);
            }

            aguardar_enter();
            system("cls");

            break;
        }
        case 6:
        {
            remover_da_lista_por_nome(&lista, &tabela, trie.raiz, &resultado_tempo_real);
            atualizar_trie(&lista, &trie.raiz);

            aguardar_enter();
            system("cls");
            break;
        }
        case 7:
        {
            printf("\n\n");
            exibir_clientes_ordem_cadastro(&lista);
            aguardar_enter();
            system("cls");
            break;
        }
        case 8:
        {

            exibir_clientes_ordem_alfabetica(&lista);
            aguardar_enter();
            system("cls");
            break;
        }
        case 0:
        {
            printf("%sEncerrando programa.....%s\n\n", AMARELO, RESET);

            salvar_clientes(&lista);

            liberar_memoria_da_lista(&lista);
            liberar_memoria_hash(&tabela);
            liberar_trie(trie.raiz);

            loop = false;

            break;
        }

        default:
            printf("%sDigite uma opção valida.%s\n\n", AMARELO, RESET);
            break;
        }
    }

    return 0;
}