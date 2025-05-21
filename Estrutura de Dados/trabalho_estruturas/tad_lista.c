#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tad_configs.h"

#define FILA_FICHAS  "./fila.dat"          //Arquivo de armazenamento de fila

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
  printf("Número: %d\n Paciente: %s\n Médico: %s\n", ficha->ficha, ficha->nome, ficha->medico);
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
      arquivo = fopen(FILA_FICHAS, "rb+"); // Apenas abre o arquivo
    } else {                                 // Arquivo não existe
      arquivo = fopen(FILA_FICHAS, "wb+"); // Cria arquivo novo
    }
    return arquivo;
}

// Escreve a ficha no arquivo
void escrever_arquivo(Ficha *ficha) {
    FILE *arquivo = abrir_arquivo();
    if (ficha && arquivo) {
      fseek(arquivo, 0, SEEK_END);  // Garante que a escrita comece no final do arquivo
      fwrite(ficha, sizeof(Ficha), 1, arquivo);
      fclose(arquivo);
    }
}

// Lê o arquivo e retira a ficha do arquivo.
Ficha *ler_arquivo(TadConfigs *tad, int posicao) {
    FILE *arquivo = abrir_arquivo();
    Ficha *ficha = (Ficha *) malloc(sizeof(Ficha));
    if (arquivo && ficha) {
      // O é inicio e 1 é o fim do arquivo.
        if(posicao == 1) {
          fseek(arquivo, 0, SEEK_END);
          long tamanho = ftell(arquivo);

          if (tamanho < sizeof(Ficha)) {
              printf("Arquivo vazio ou corrompido.\n");
              fclose(arquivo);
              return NULL;
          }
          fseek(arquivo, -sizeof(Ficha), SEEK_END);
          fread(ficha, sizeof(Ficha), 1, arquivo);
        } else {
          rewind(arquivo);  // Garante que a leitura comece do início do arquivo
          fread(ficha, sizeof(Ficha), 1, arquivo);
          fclose(arquivo);
        }
    }
    return ficha;
}

// Reescreve o arquivo sem a ficha retirada.
void reescrever_arquivo() {
    FILE *arquivo = abrir_arquivo();
    if (arquivo) {
      fseek(arquivo, 0, SEEK_END);
      long tamanho = ftell(arquivo);
      int total = tamanho / sizeof(Ficha);
      rewind(arquivo);

      Ficha *fichas = malloc(tamanho);
      fread(fichas, sizeof(Ficha), total, arquivo);
      fclose(arquivo);

      arquivo = fopen(FILA_FICHAS, "wb");
      fwrite(fichas + 1, sizeof(Ficha), total - 1, arquivo);
      fclose(arquivo);
      free(fichas);
    }
}
