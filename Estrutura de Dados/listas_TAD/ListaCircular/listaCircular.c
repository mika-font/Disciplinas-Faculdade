#include "listaCircular.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int dado;
  No *proximo; // Ponteiro para o próximo nó
} No;

typedef struct ListaCircular {
  No *primeiro; // Ponteiro para o primeiro nó
  No *ultimo;  // Ponteiro para o último nó
  int tamanho; // tamanho atual da lista
} ListaCircular;

ListaCircular *criar_lista() {
  ListaCircular *lista = (ListaCircular *) malloc(sizeof(ListaCircular));
  if (lista == NULL) {
    return NULL; // Falhou alocação de memória
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  lista->tamanho = 0;
  return lista;
}

No *inserir_inicio(ListaCircular *lista, int dado) {
  No *novo = (No *) malloc(sizeof(No));
  if (novo == NULL) {
    return NULL; // Falhou alocação de memória
  }
  novo->dado = dado;

  if (lista->primeiro == NULL) {
    // Lista vazia: novo nó é o primeiro e último nó
    novo->proximo = novo;
    lista->primeiro = novo;
    lista->ultimo = novo;
  } else {
    // Lista não vazia: novo nó se torna o primeiro nó
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    lista->ultimo->proximo = novo; // Atualizar ponteiro do último nó
  }
  lista->tamanho++;
  return novo; // Retornar o ponteiro para o nó inserido
}

No *inserir_fim(ListaCircular *lista, int dado) {
  No *novo = inserir_inicio(lista, dado); // Reutiliza a função inserir_inicio
  if (novo != NULL) {
    lista->ultimo = novo; // Atualizar ponteiro do último nó
    lista->primeiro = lista->ultimo->proximo; // Atualizar o primeiro que foi modificado na inserção
  }
  lista->tamanho++;
  return novo;
}

int remover_inicio(ListaCircular *lista) {
  if (lista->primeiro == NULL) {
    return -1; // Lista vazia
  }

  No *removido = lista->primeiro;
  int valor_removido = removido->dado;

  if (lista->primeiro == lista->ultimo) {
    // Único nó: lista fica vazia
    lista->primeiro = NULL;
    lista->ultimo = NULL;
  } else {
    // Vários nós: atualizar ponteiros
    lista->primeiro = lista->primeiro->proximo;
    lista->ultimo->proximo = lista->primeiro; // Atualizar ponteiro do último nó
  }

  free(removido);
  lista->tamanho--;
  return valor_removido;
}

void imprimir_lista(ListaCircular *lista) {
  if (lista->primeiro == NULL) {
    printf("Lista vazia!\n");
    return;
  }

  No *atual = lista->primeiro;
  do {
    printf("%d ", atual->dado);
    atual = atual->proximo;
  } while (atual != lista->primeiro); // Condição de parada: volta ao primeiro nó
  printf("\n");
}

void destruir_lista(ListaCircular *lista) {
  if (lista->primeiro == NULL) {
    return; // Lista já está vazia
  }

  No *atual = lista->primeiro;
  No *prox;
    
  do {
        prox = atual->proximo; // Salva o próximo nó antes de liberar o atual
        free(atual); // Libera a memória alocada para o nó atual
        atual = prox; // Move para o próximo nó
  } while (atual != lista->primeiro);

  // Atualizar ponteiros da lista vazia
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  lista->tamanho = 0;

  free(lista); // Liberar a memória da lista principal
}
