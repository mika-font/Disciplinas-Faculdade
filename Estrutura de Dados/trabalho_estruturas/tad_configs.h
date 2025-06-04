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

typedef struct No_ar {
    int chave;
    struct No_ar* esquerdo;
    struct No_ar* direito;
    struct No_ar* pai;
    Lista *lista_fichas;
} No;

typedef struct {
    No* raiz;
} ABB;

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

void gerar_ficha_menu(Ficha *ficha);
void *preencher_nome(char nome[], int tamanho);
void *preencher_medico(char medico[], int tamanho);
void *selecionar_prioridade(int prioridade);
int intervalo();

// Parte 1 - Arquivo de Fichas
FILE *abrir_arquivo();
Ficha *ler_arquivo(TadConfigs *tad);
void escrever_arquivo(Ficha *ficha);
void reescrever_arquivo();

// Parte 2 - Arvore de Prioridade
ABB *criar_abb();
No *criar_no(int chave);
No *buscar(No *raiz, int chave);
No *sucessor(No *atual);
No *minimo(No *atual);
No *maximo(No *atual);
void inserir_no_na_arvore(ABB *abb, int chave);
void remover_no_na_arvore(ABB *abb, int chave);
void alocar_no_na_arvore(ABB *abb, Ficha *ficha);

#endif
