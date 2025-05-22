#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tad_configs.h"

#define FILA_FICHAS  "./fila.txt"          //Arquivo de armazenamento de fila

// Gera um tempo de atendimento aleatório.
int intervalo(){
  return rand() % (10 - 5 + 1) + 5;
}

// Preenche o campo nome da ficha.
void *preencher_nome(char nome[], int tamanho){
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
  printf("Digite seu nome: ");
  fgets(nome, tamanho, stdin);
  nome[strcspn(nome, "\n")] = '\0';
}

// Preenche o campo médico da ficha.
void *preencher_medico(char medico[], int tamanho){
  //int c;
  //while ((c = getchar()) != '\n' && c != EOF);
  printf("Digite o médico: ");
  fgets(medico, tamanho, stdin);
  medico[strcspn(medico, "\n")] = '\0';
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
  printf("Número: %d | Paciente: %s\n Médico: %s\n", ficha->ficha, ficha->nome, ficha->medico);
}

// Retira a ficha da lista, chama a função de imprimir ficha e libera a memória.
void retirar_ficha_lista(Lista *lista){
  if (lista->primeiro == NULL) {
    return;
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

FILE *abrir_arquivo() {
    FILE *arquivo;
    if(access(FILA_FICHAS, F_OK ) != -1 ) {  // Arquivo já existe
      arquivo = fopen(FILA_FICHAS, "r+");   // Apenas abre o arquivo
    } else {                                 // Arquivo não existe
      arquivo = fopen(FILA_FICHAS, "w+");   // Cria arquivo novo
    }
    return arquivo;
}

// Escreve a ficha no arquivo
void escrever_arquivo(Ficha *ficha) {
    FILE *arquivo = abrir_arquivo();
    if (ficha && arquivo) {
      fseek(arquivo, 0, SEEK_END);
      fprintf(arquivo, "Número: %d | Tempo: %d | Paciente: %s | Médico: %s\n", ficha->ficha, ficha->tempo, ficha->nome, ficha->medico);
      fclose(arquivo);
    }
}

// Lê o arquivo e retira a ficha do arquivo.
Ficha *ler_arquivo(TadConfigs *tad, int leitura) {
    FILE *arquivo = abrir_arquivo();
    Ficha *ficha = (Ficha *) malloc(sizeof(Ficha));
    if (arquivo && ficha) {
      if(leitura == 0){
        rewind(arquivo);
      } else {
        fseek(arquivo, 0, SEEK_END);
      }
      fscanf(arquivo, "Número: %d | Tempo: %d", &ficha->ficha, &ficha->tempo);
      fgets(ficha->nome, sizeof(ficha->nome), arquivo);
      ficha->nome[strcspn(ficha->nome, "\n")] = '\0';
      fgets(ficha->medico, sizeof(ficha->medico), arquivo);
      ficha->medico[strcspn(ficha->medico, "\n")] = '\0';
      fclose(arquivo);
    }
    return ficha;
}

// Reescreve o arquivo sem a ficha.
void reescrever_arquivo() {
    FILE *arquivo = abrir_arquivo();
    FILE *temporario = fopen("temp.txt", "w");
    if (!temporario) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo);
        return;
    }
    if (arquivo) {
      char linha[200];
      int linha_atual = 0;
      while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha_atual > 0) {
          fputs(linha, temporario);
        }
        linha_atual++;
      }
      fclose(arquivo);
      fclose(temporario);

      remove(FILA_FICHAS);
      rename("temp.txt", FILA_FICHAS);
    }
}
