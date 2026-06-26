# Sistema de Cadastro de Clientes em C

Sistema de cadastro de clientes desenvolvido em **linguagem C** para terminal Windows, com **CRUD completo**, utilizando diferentes estruturas de dados para otimizar as operações de cadastro, busca e remoção.

O projeto foi desenvolvido com o objetivo de praticar conceitos fundamentais da linguagem C, como alocação dinâmica de memória, modularização, persistência em arquivos e integração entre estruturas de dados.

---

# Funcionalidades

- Cadastro de clientes
- Busca por ID
- Busca por CPF utilizando Tabela Hash
- Busca por nome com autocomplete utilizando Trie
- Listagem de clientes em ordem de cadastro
- Listagem de clientes em ordem alfabética
- Remoção de clientes por ID
- Remoção de clientes por nome
- Persistência dos dados em arquivo

---

# Estruturas de Dados Utilizadas

- Lista Duplamente Encadeada
- Tabela Hash
- Trie
- Arquivos Binários para persistência

---

# Tecnologias

- Linguagem C
- GCC / MinGW
- Git
- GitHub
- Terminal Windows

---

# Estrutura do Projeto

```
.
├── arvore.c
├── arvore.h
├── config.h
├── hash.c
├── hash.h
├── lista.c
├── lista.h
├── main.c
├── menu.c
├── menu.h
├── persistencia.c
├── persistencia.h
├── trie.c
├── trie.h
├── README.md
└── .gitignore
```

---

# Como Compilar

```bash
gcc *.c -o programa
```

---

# Como Executar

```bash
programa.exe
```

---

# Objetivo do Projeto

Este projeto foi desenvolvido para consolidar conhecimentos em programação na linguagem C através da implementação de um sistema completo de cadastro de clientes.

Além do CRUD tradicional, o sistema utiliza diferentes estruturas de dados para demonstrar aplicações práticas de algoritmos estudados durante o aprendizado.

---

# Conceitos Praticados

Durante o desenvolvimento deste projeto foram praticados:

- Manipulação de ponteiros
- Alocação dinâmica de memória
- Modularização de projetos em C
- Lista Duplamente Encadeada
- Tabela Hash
- Trie
- Persistência em Arquivos
- Organização de código
- Versionamento utilizando Git
- Publicação de projetos no GitHub

---

# Melhorias Futuras

- Interface gráfica
- Ordenação utilizando Árvore Binária de Busca
- Exportação de dados
- Testes automatizados
- Compatibilidade com Linux

---

# Autor

**Deivisson Pereira**

Desenvolvido como projeto de estudo e portfólio para praticar estruturas de dados, organização de código e desenvolvimento em linguagem C.