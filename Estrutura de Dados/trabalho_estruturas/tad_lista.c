#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tad_configs.h"

// Gera um tempo de atendimento aleatório.
int intervalo(){
  return rand() % (10 - 5 + 1) + 5;
}

// Preenche o campo nome da ficha.
char preencher_nome(char nome[], int tamanho){
  printf("Digite seu nome: ");
  fgets(nome, tamanho, stdin);
  nome[strcspn(nome, "\n")] = '\0';
  return nome;
}

// Preenche o campo médico da ficha.
char preencher_medico(char medico[], int tamanho){
  printf("Digite o médico: ");
  fgets(medico, tamanho, stdin);
  medico[strcspn(medico, "\n")] = '\0';
  return medico;
}

// Cria uma lista.
Lista *criar_lista() {
  Lista *lista = (Lista *) malloc(sizeof(Lista));
  if (lista == NULL) {
    printf("Erro ao alocar memória.");
    return NULL; // Falha na alocação de memória
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  return lista;
}

// Cria uma ficha e chama as funções de preencher strings e determinar o tempo de atendimento.
Ficha *inserir_ficha_lista(Lista *lista, int num){
  Ficha *ficha = (Ficha *) malloc(sizeof(Ficha));
  if (ficha == NULL) {
    printf("Erro ao alocar memória.");
    return NULL; // Falha na alocação de memória
  }
  ficha->ficha = num;
  ficha->tempo = intervalo();
  preencher_nome(ficha->nome, 50);
  preencher_medico(ficha->medico, 50);

  if(lista->ultimo == NULL){
    lista->primeiro = ficha;
    lista->ultimo = ficha;
  } else {
    lista->ultimo->prox = ficha;
    lista->ultimo = ficha;
  }
  ficha->prox = NULL;
  return ficha;
}

// Imprime a ficha.
void imprimir_ficha(Ficha *ficha){
  printf("Número: %d\n Paciente: %s\n Médico: %s\n", ficha->ficha, ficha->nome, ficha->medico);
}

// Retira a ficha da lista, chama a função de imprimir ficha e libera a memória.
void retirar_ficha_lista(Lista *lista){
  if (lista->primeiro == NULL) {
    return -1;
  } else {
    Ficha *seguinte = lista->primeiro;
    if (lista->primeiro == lista->ultimo) {
      lista->primeiro = NULL;
      lista->ultimo = NULL;
    } else {
      lista->primeiro = lista->primeiro->prox;
    }
    imprimir_ficha(seguinte);
    free(seguinte);
  }
}

// Imprime a lista.
void imprimir_lista(Lista *lista) {
  if (lista->primeiro == NULL) {
    printf("Lista vazia!\n");
    return;
  }
  Ficha *atual = lista->primeiro;
  while (atual != NULL) {
    printf("n°: %d - %d s\n", atual->ficha, atual->tempo);
    atual = atual->prox;
  }
  printf("\n");
}

// Destrói a lista.
void destruir_lista(Lista *lista) {
  if (lista->primeiro == NULL) {
    return;
  }
  Ficha *atual = lista->primeiro;
  Ficha *anterior;
  while (atual != NULL) {
    anterior = atual;
    atual = atual->prox;
    free(anterior);
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
}

//Finalizar depois
/*void escrever_arquivo(Ficha *ficha){
  FILE * arquivo;
  arquivo = fopen("./fichas.txt", "a");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo.");
    return -1;
  }
  fprintf(arquivo, "Ficha: %d | Nome: %s | Médico: %s | Tempo: %d\n", ficha->ficha, ficha->nome, ficha->medico, ficha->tempo);

  fclose(arquivo);
}

void ler_arquivo(){
  
}

void fechar_arquivo(){
  
}*/