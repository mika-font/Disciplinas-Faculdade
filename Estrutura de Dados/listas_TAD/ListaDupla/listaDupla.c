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
  if(novo == NULL){
    return NULL;
  }
  novo->dado = dado;
  novo->proximo = NULL;
  novo->anterior = lista->ultimo;
    
  if (lista->primeiro == NULL) {
      lista->primeiro = novo;
      lista->ultimo = novo;
  } else {
      lista->ultimo->proximo = novo;
      lista->ultimo = novo;
  }
  return novo;
}

No *inserir_posicao(ListaDupla *lista, int dado, int posicao){
  if(posicao < 0){
    return NULL;
  } 
  if(posicao == 1){
    return inserir_inicio(lista, dado);
  } else {
    No *novo = (No *) malloc(sizeof(No));
    if(novo == NULL){
      return NULL;
    }
    novo->dado = dado;
    
    No *aux = lista->primeiro;
    int count = 0;

    while(aux != NULL){
      count++;
      if(count == posicao){
        novo->proximo = aux;
        novo->anterior = aux->anterior;

        if(aux->anterior != NULL){
          aux->anterior->proximo = novo;
        }
        aux->anterior = novo;
        return novo;
      }
      aux = aux->proximo;
    }
    if(count+1 == posicao) {
      return inserir_fim(lista, dado);
    }
  }
  return NULL;
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

int remover_fim(ListaDupla *lista){
 if (lista->primeiro == NULL) {
    return -1; // Empty list
  }

  No *removido = lista->ultimo;
  int valor_removido = removido->dado;

  if (lista->primeiro == lista->ultimo) {
    lista->primeiro = NULL;
    lista->ultimo = NULL;
  } else {
    lista->ultimo = lista->ultimo->anterior;
    lista->ultimo->proximo = NULL;
  }

  free(removido);
  return valor_removido;
}

int remover_posicao(ListaDupla *lista, int posicao){
  if (lista->primeiro == NULL || posicao <= 0) {
    return -1; // Empty list
  }

  if(posicao == 1){
    return remover_inicio(lista);
  } else {
    No *atual = lista->primeiro;
    int count = 0;
    while (atual != NULL) {
      count++;
      if(count == posicao){
        int valor_removido = atual->dado;
        if (atual->anterior != NULL) {
          atual->anterior->proximo = atual->proximo;
        }      
        if (atual->proximo != NULL) {
          atual->proximo->anterior = atual->anterior;
        } else {
          lista->ultimo = atual->anterior;
        }
        free(atual);
        return valor_removido;
      }
      atual = atual->proximo;
    }
  }
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
        No *atual = lista->ultimo;
        while (atual != NULL) {
          printf("%d ", atual->dado);
          atual = atual->anterior;
        }
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
