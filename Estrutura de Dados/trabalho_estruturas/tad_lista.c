#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tad_configs.h"

Lista *criar_lista() {
  Lista *lista = (Lista *) malloc(sizeof(Lista));
  if (lista == NULL) {
    return NULL; // Falha na alocação de memória
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  return lista;
}

void destruir_lista(Lista *lista) {
  if (lista->primeiro == NULL) {        //Verifica se a lista está vazia.
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


