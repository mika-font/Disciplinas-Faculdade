#include "listaDupla.h" // Assuming you renamed the header to "listaDupla.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int dado;
  No *anterior;
  No *proximo;
} No;

typedef struct ListaDupla {
  No *primeiro;
  No *ultimo;
} ListaDupla;

ListaDupla *criar_lista() {
  ListaDupla *lista = (ListaDupla *) malloc(sizeof(ListaDupla));
  if (lista == NULL) {
    return NULL; // Memory allocation failure
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  return lista;
}

No *inserir_inicio(ListaDupla *lista, int dado) {
  No *novo = (No *) malloc(sizeof(No));
  if (novo == NULL) {
    return NULL; // Memory allocation failure
  }
  novo->dado = dado;
  novo->anterior = NULL;
  novo->proximo = lista->primeiro;

  if (lista->primeiro == NULL) {
    lista->ultimo = novo;
  } else {
    lista->primeiro->anterior = novo;
  }

  lista->primeiro = novo;
  return novo;
}

No *inserir_fim(ListaDupla *lista, int dado){
  No *novo = (No *) malloc(sizeof(No));
  if (novo == NULL) {
    return NULL; // Memory allocation failure
  }
  novo->dado = dado;
  novo->anterior = lista->ultimo;
  novo->proximo = lista->primeiro;

  if (lista->primeiro == NULL) {
    lista->ultimo = novo;
  } else {
    lista->primeiro->anterior = novo;
  }

  lista->primeiro = novo;
  return novo;
}

No *inserir_posicao(ListaDupla *lista, int dado, int posicao){

}

int remover_inicio(ListaDupla *lista) {
  if (lista->primeiro == NULL) {
    return -1; // Empty list
  }

  No *removido = lista->primeiro;
  int valor_removido = removido->dado;

  if (lista->primeiro == lista->ultimo) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
  } else {
    lista->primeiro = lista->primeiro->proximo;
    lista->primeiro->anterior = NULL;
  }

  free(removido);
  return valor_removido;
}

int remover_fim(ListaDupla *lista, int dado){

}

int remover_posicao(ListaDupla *lista, int posicao){

}

void imprimir_lista(ListaDupla *lista, Direcao dir) {
    if (lista->primeiro == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    if(dir == INICIO) {
        No *atual = lista->primeiro;
        while (atual != NULL) {
          printf("%d ", atual->dado);
          atual = atual->proximo;
        }
    } else {
        // Implementar impressão iniciando do FIM (impressão em ordem inversa)
    }
    printf("\n");
}

void destruir_lista(ListaDupla *lista) {
  if (lista->primeiro == NULL) {
    return;
  }

  No *atual = lista->primeiro;
  No *anterior;
  while (atual != NULL) {
    anterior = atual;
    atual = atual->proximo;
    free(anterior);
  }

  lista->primeiro = NULL;
  lista->ultimo = NULL;
  free(lista);
}
