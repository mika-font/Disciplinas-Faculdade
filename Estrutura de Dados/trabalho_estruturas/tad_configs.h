#ifndef TAD_CONFIGS_H
#define TAD_CONFIGS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int ficha;
    int tempo;
    char nome[50];
    char medico[50];
    struct no *prox; 
} Ficha;

typedef struct lista {
    Ficha *primeiro;
    Ficha *ultimo;
} Lista;

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

typedef enum {
    NENHUMA,
    BAIXA,
    MEDIA,
    ALTA
} PrioridadeItem;

typedef struct item {
    int id;
    int tempo_processamento;
    PrioridadeItem prioridade;
    int finalizado;
} Item;

FILE *configs_abrir();
TadConfigs *configs_inicializar();
void configs_fechar(FILE *arquivo);
void configs_destruir(TadConfigs *tad);
void configs_salvar(TadConfigs *tad);
void configs_ler(TadConfigs *tad);
void configs_mostrar(TadConfigs *tad);
void configs_atualizar(TadConfigs *tad, statusProcessamento status, int intervalo);

Lista *criar_lista();
Ficha *inserir_ficha_lista(Lista *lista, int num);
void retirar_ficha_lista(Lista *lista);
void destruir_lista(Lista *lista);
void imprimir_lista(Lista *lista);
void imprimir_ficha(Ficha *ficha);
int intervalo();
void *preencher_nome(char nome[], int tamanho);
void *preencher_medico(char medico[], int tamanho);

void escrever_arquivo(Ficha *ficha);
void ler_arquivo();

#endif
