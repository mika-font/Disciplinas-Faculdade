#ifndef TAD_CONFIGS_H
#define TAD_CONFIGS_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura do Relatório
typedef struct relatorio{
    char especialidade[50];
    int quantidade;
}Relat;

// Estrutura da Ficha
typedef struct no {
    int ficha;
    int tempo;
    char nome[50];
    char medico[50];
    int prioridade;
    struct no *prox; 
} Ficha;

// Estrutura da Fila
typedef struct lista {
    Ficha *primeiro;
    Ficha *ultimo;
} Lista;

// Estrutra do Nó da Árvore
typedef struct No {
    int chave;
    struct No* esquerdo;
    struct No* direito;
    struct No* pai;
    Lista *lista_fichas;
} No;

// Estrutura da Árvore
typedef struct {
    No* raiz;
} ABB;

// Funções do Simulação
typedef enum {
    AGUARDAR,       //Aguarda comandos do menu
    SIMULAR,        //Funciona o atendimento
    TERMINAR,       //Finaliza a simulação
    LER,            //Lê o arquivo de configs
} statusProcessamento;

// Estrutura do Intervalo de Processamento
typedef struct conf {
    statusProcessamento status;
    int intervalo;
} Configs;

// Estrutura do Arquivo de Configurações
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

FILE *abrir_arquivo();
FILE *abrir_log();
Lista *criar_lista();
Ficha *inserir_ficha_lista(Lista *lista, Ficha *ficha);
Ficha *ler_arquivo(TadConfigs *tad);
ABB *criar_abb();
No *criar_no(int chave);
No *buscar(No *raiz, int chave);
No *sucessor(No *atual);
No *minimo(No *atual);
No *maximo(No *atual);
void criar_relatorio(Relat *relatorio);
void retirar_ficha_lista(Lista *lista);
void destruir_lista(Lista *lista);
void imprimir_lista(Lista *lista);
void imprimir_ficha(Ficha *ficha);
void imprimir_proximos(ABB *arvore, Lista *lista);
void gerar_ficha_menu(Ficha *ficha, int num, Relat *relatorio);
void *preencher_nome(char nome[], int tamanho);
void *preencher_medico(char medico[], int tamanho);
void selecionar_prioridade(int *prioridade);
void escrever_arquivo(Ficha *ficha);
void reescrever_arquivo();
void inserir_no_na_arvore(ABB *abb, int chave);
void removerNo(ABB *abb, No *no);
void removerNoFolha(ABB *abb, No *no);
void removerNoComUmFilho(ABB *abb, No *no);
void removerNoComDoisFilhos(ABB *abb, No *no);
void fluxo_fila_arvore(ABB *abb, Ficha *ficha);
void destruir_no(No *no);
void destruir_arvore(ABB *abb);
void escrever_log(int comando);
void reescrever_log(); 
int intervalo();
int ler_log();

#endif
