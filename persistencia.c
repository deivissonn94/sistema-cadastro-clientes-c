#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "persistencia.h"

void inserir_dados_no_carregamento(Lista *lista,const Cliente_arquivo *temp,Tabela_hash *tabela){

    inserir_na_lista(lista,temp->nome,temp->cpf,temp->email);
    if(lista->cauda != NULL){

        lista->cauda->id = temp->id;
    }

    if(temp->id >= lista->id_proximo){

        lista->id_proximo = temp->id +1;
    }

    inserir_cliente_tabela_hash(lista->cauda,tabela);


}

void carregar_clientes(Lista *lista,Tabela_hash *tabela){

    FILE *arquivo = fopen("clientes.dat","rb");

    if (arquivo == NULL)
    {
        printf("Arquivo não encontrado.\n");
        return;
    }

    Cliente_arquivo temp;

    while (fread(&temp,sizeof(temp),1,arquivo) == 1)
    {
        inserir_dados_no_carregamento(lista,&temp,tabela);

        
    }
    
    fclose(arquivo);

}

void salvar_clientes(Lista *lista)
{

    FILE *arquivo = fopen("clientes.dat", "wb");

    if (arquivo == NULL)
    {

        printf("%sErro ao abrir arquivo.%s\n", VERMELHO, RESET);
        return;
    }

    Cliente *atual = lista->cabeca;

  

    while (atual != NULL)
    {
        Cliente_arquivo temp;

        temp.id = atual->id;

        strcpy(temp.nome, atual->nome);
        strcpy(temp.cpf, atual->cpf);
        strcpy(temp.email, atual->email);

        fwrite(&temp, sizeof(Cliente_arquivo), 1, arquivo);

        atual = atual->proximo;
    }

    fclose(arquivo);
}