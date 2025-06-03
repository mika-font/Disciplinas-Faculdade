#ifndef TAD_CONFIGS_H
#define TAD_CONFIGS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int ficha;
    int tempo;
    char nome[50];
    char medico[50];
    int prioridade;
    struct no *prox; 
} Ficha;

typedef struct lista {
    Ficha *primeiro;
    Ficha *ultimo;
} Lista;

// Lista de fichas é separada do arquivo de fichas para facilitar a manipulação

typedef enum {
    AGUARDAR,       //Aguarda comandos do menu
    SIMULAR,        //Funciona o atendimento
    TERMINAR,       //Finaliza a simulação
    GERAR_FICHA,    //Gera uma nova ficha
    LER,            //Lê o arquivo e executa as fichas
    IMPRIMIR,       //Imprime as fichas e suas informações
} statusProcessamento;

typedef struct conf {
    statusProcessamento status;
    int intervalo;
} Configs;

typedef struct tad_configs {
  FILE *arquivo;
  Configs configs;
} TadConfigs;

typedef struct No {
    int chave;
    struct No* esquerdo;
    struct No* direito;
    struct No* pai;
} No;

typedef struct {
    No* raiz;
} ABB;


FILE *configs_abrir();
TadConfigs *configs_inicializar();
void configs_fechar(FILE *arquivo);
void configs_destruir(TadConfigs *tad);
void configs_salvar(TadConfigs *tad);
void configs_ler(TadConfigs *tad);
void configs_mostrar(TadConfigs *tad);
void configs_atualizar(TadConfigs *tad, statusProcessamento status, int intervalo);

// Parte 1 - Lista de Fichas
Lista *criar_lista();
Ficha *inserir_ficha_lista(Lista *lista, int num);
void retirar_ficha_lista(Lista *lista);
void destruir_lista(Lista *lista);
void imprimir_lista(Lista *lista);
void recuperar_lista(Lista *lista);
void imprimir_ficha(Ficha *ficha);
void *preencher_nome(char nome[], int tamanho);
void *preencher_medico(char medico[], int tamanho);
int intervalo();

// Parte 1 - Arquivo de Fichas
FILE *abrir_arquivo();
Ficha *ler_arquivo(TadConfigs *tad, int leitura);
void escrever_arquivo(Ficha *ficha);
void reescrever_arquivo();

// Parte 2 - Arvore de Prioridade
ABB *criar_abb();
No *criar_no(int chave);
No *buscar(No *raiz, int chave);
No *sucessor(No *atual);
No *minimo(No *atual);
No *maximo(No *atual);
void *selecionar_prioridade(int prioridade);
void inserirNo(ABB *abb, int chave);
void removerNo(ABB *abb, int chave);



#endif
