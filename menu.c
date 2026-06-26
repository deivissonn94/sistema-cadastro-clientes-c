#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "menu.h"
#include <windows.h>


int confirmar_remocao(Cliente *buscado)
{

    char buffer[TAMANHO_STRING];

    while (true)
    {   

        exibir_cliente(buscado);

        printf("Deseja remover este cliente?\n");
        printf("1- Sim \n");
        printf("2 - Não\n\n");

        captura_do_buffer(buffer, TAMANHO_STRING);

        bool valida = valida_opcao(buffer);

        if (valida)
        {

            int opcao = atoi(buffer);

            if(opcao == 1 || opcao == 2){

                return opcao;

            }else{

                printf("%sEscolha entre 1 ou 2.%s\n\n",AMARELO,RESET);
                
                aguardar_enter();
                system("cls");

                continue;

            }

            
        }
        else
        {

            continue;
        }
    }

    
}

void exibir_retorno_de_cliente_buscado(Cliente *cliente)
{

    if (cliente)
    {

        exibir_cliente(cliente);
    }
    else
    {

        printf("%sCliente não encontrado.%s\n\n", AMARELO, RESET);
    }
}

void aguardar_enter(void)
{
    printf("\nPressione ENTER para continuar...");
    getchar();
}

bool valida_numeros(const char *entrada)
{

    for (size_t i = 0; entrada[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)entrada[i]))
        {

            printf("%sVocê deve digitar apenas números.%s\n\n", AMARELO, RESET);
            return false;
        }
    }

    return true;
}

int entrada_opcao(void)
{

    char buffer[TAMANHO_STRING];

    while (true)
    {
        captura_do_buffer(buffer, TAMANHO_STRING);

        bool valida = valida_opcao(buffer);

        if (!valida)
        {
            printf("Escolha uma opção:");
            continue;
        }
        else
        {

            return atoi(buffer);
        }
    }
}

bool valida_opcao(const char *opcao_digitada)
{

    if (opcao_digitada[0] == '\0')
    {

        printf("%sA entrada está vazia.%s\n\n", AMARELO, RESET);
        return false;
    }

    return valida_numeros(opcao_digitada);
}

void exibir_menu_pricipal(void)
{
    printf("\n");
    printf(AZUL "========================================\n" RESET);
    printf(AZUL "      SISTEMA DE CADASTRO DE CLIENTES\n" RESET);
    printf(AZUL "========================================\n" RESET);

    printf("1 - Cadastrar cliente\n");
    printf("2 - Buscar por ID\n");
    printf("3 - Buscar por CPF\n");
    printf("4 - Buscar por nome\n");
    printf("5 - Remover por ID\n");
    printf("6 - Remover por nome\n");
    printf("7 - Exibir todos os clientes\n");
    printf("8 - Exibir clientes em ordem alfabética\n");
    printf("0 - Sair\n");

    printf(AZUL "========================================\n" RESET);
    printf("Escolha uma opção: ");
}

void entrada_email(char *email_digitado)
{

    while (true)
    {

        printf("Digite o e-mail : ");

        captura_do_buffer(email_digitado, TAMANHO_STRING);

        bool valida = valida_email(email_digitado);

        if (!valida)
        {

            continue;
        }
        else
        {

            break;
        }
    }
}

bool valida_email(const char *email)
{

    if (email[0] == '\0')
    {

        printf("%sA entrada está vazia.%s\n\n", AMARELO, RESET);
        return false;
    }

    if (email[0] == '@')
    {
        printf("%sEmail não pode começar com '@'.%s\n\n", AMARELO, RESET);
        return false;
    }

    const char *arroba = strchr(email, '@');

    if (arroba == NULL)
    {

        printf("%sEmail deve conter '@'.%s\n\n", AMARELO, RESET);
        return false;
    }

    if (strchr(arroba + 1, '@') != NULL)
    {

        printf("%sEmail deve possuir apenas um '@'.%s\n\n", AMARELO, RESET);
        return false;
    }
    if (strchr(arroba + 1, '.') == NULL)
    {

        printf("%sEmail deve conter '.' após o '@'.%s\n\n", AMARELO, RESET);
        return false;
    }

    size_t tamanho_email = strlen(email);

    if (email[tamanho_email - 1] == '.')
    {

        printf("%sEmail não pode terminar com '.'.%s\n\n", AMARELO, RESET);
        return false;
    }

    return true;
}

void entrada_cpf(char *cpf_informado)
{

    while (true)
    {
        printf("Digite apenas números para o cpf :");

        captura_do_buffer(cpf_informado, TAMANHO_CPF);

        bool valida = valida_cpf(cpf_informado);

        if (!valida)
        {

            continue;
        }
        else
        {

            break;
        }
    }
}

bool valida_cpf(const char *cpf_informado)
{

    if (strlen(cpf_informado) != 11)
    {

        printf("%sQuantidades de números digitados e imcopatível com CPF.%s\n\n", AMARELO, RESET);
        return false;
    }

    return valida_numeros(cpf_informado);
}

int entrada_id(void)
{

    char buffer[TAMANHO_STRING];

    while (true)
    {
        printf("Digite o ID desejado : ");

        captura_do_buffer(buffer, TAMANHO_STRING);

        if (buffer[0] == '\0')
        {
            printf("%sDigite um ID válido!%s\n\n", AMARELO, RESET);
            continue;
        }

        bool valida = valida_numeros(buffer);

        if (!valida)
        {

            continue;
        }
        else
        {

            int id = atoi(buffer);

            if (id <= 0)
            {

                printf("%sDigite um ID válido!%s\n\n", AMARELO, RESET);
                continue;
            }
            else
            {

                return id;
            }
        }
    }
}

void entrada_nome(char *nome_digitado, void (*descricao)(void))
{

    while (true)
    {

        descricao();

        captura_do_buffer(nome_digitado, TAMANHO_STRING);

        bool valida = valida_nome(nome_digitado);

        if (!valida)
        {

            printf("%sNome digitado não pode conter números e caracteres especiais,ou entrada estar vazia.%s\n\n", AMARELO, RESET);
            continue;
        }

        break;
    }
}

bool valida_nome(const char *nome_digitado)
{

    if (nome_digitado[0] == '\0')
    {

        return false;
    }

    bool contem_letra = false;

    for (int i = 0; nome_digitado[i] != '\0'; i++)
    {

        unsigned char c = nome_digitado[i];

        if (c < 128)
        {

            if (isalpha(c))
            {

                contem_letra = true;
            }

            if (!isalpha(c) && c != ' ')
            {

                return false;
            }
        }
    }

    return contem_letra;
}

void captura_do_buffer(char *buffer, size_t tamanho_buffer)
{
    if (fgets(buffer, tamanho_buffer, stdin) == NULL)
    {
        buffer[0] = '\0';
        return;
    }

    size_t tamanho = strlen(buffer);

    if (tamanho > 0 && buffer[tamanho - 1] == '\n')
    {
        buffer[tamanho - 1] = '\0';
    }
    else
    {
        int c;

        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
    }
}

void configurar_utf8(void)
{

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

void exibir_descricao_cadastro_nome(void)
{

    printf("Digite o nome que deseja cadastrar : ");
}

void exibir_descricao_nome_buscado(void)
{

    printf("Digite o nome que deseja buscar : ");
}

void exibir_clientes_compactados(Cliente *atual)
{

    printf(
        "[ID: %d] %s | CPF: %.3s.%.3s.%.3s-%.2s | %s\n",
        atual->id,
        atual->nome,
        atual->cpf,
        atual->cpf + 3,
        atual->cpf + 6,
        atual->cpf + 9,
        atual->email);
}

void exibir_cliente(Cliente *atual)
{

    printf(
        AZUL "ID: %d\n" RESET
             "Nome: %s\n"
             "CPF: %s\n"
             "Email: %s\n"
             "--------------------------------\n",
        atual->id,
        atual->nome,
        atual->cpf,
        atual->email);
}