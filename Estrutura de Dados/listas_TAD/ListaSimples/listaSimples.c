#include "listaSimples.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct No { // Estrutura para o elemento
  int dado;
  No *proximo;
} No;

typedef struct ListaSimples { // Estrutura para a lista
  No *primeiro;   // Ponteiro para o primeiro nó (excluindo o cabeçalho)
  No *ultimo;     // Ponteiro para o último nó
} ListaSimples;

ListaSimples *criar_lista() {
  ListaSimples *lista = (ListaSimples *) malloc(sizeof(ListaSimples));
  if (lista == NULL) {
    return NULL; // Falha na alocação de memória
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  return lista;
}

No *inserir_inicio(ListaSimples *lista, int dado) {
  // Alocar memória para o novo nó
  No *novo = (No *) malloc(sizeof(No));
  if (novo == NULL) {
    return NULL; // Falha na alocação de memória
  }
  // Atribuir valor e inicializar ponteiro 'proximo'
  novo->dado = dado;
  novo->proximo = NULL;
  // Inserir o novo nó no início da lista
  if (lista->primeiro == NULL) {
    // Lista vazia: novo nó é o primeiro e último nó
    lista->primeiro = novo;
    lista->ultimo = novo;
  } else {
    // Lista não vazia: novo nó se torna o primeiro nó
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
  }
  return novo; // Retornar o ponteiro para o nó inserido
}

No *inserir_fim(ListaSimples *lista, int dado) {
	// Alocar memC3ria para o novo nC3
	No *novo = (No *) malloc(sizeof(No));
	if (novo == NULL) {
		return NULL; // Falha na alocaC'C#o de memC3ri
	}
	// Atribuir valor e inicializar ponteiro 'proximo'
	novo->dado = dado;
	novo->proximo = NULL;
	// Inserir o novo nó no fim da lista
	if(lista->primeiro == NULL){
	  lista->primeiro = novo;
		lista->ultimo = novo;
	} else {
	  lista->ultimo->proximo = novo;
		lista->ultimo = novo;
	}
	return novo; // Retornar o ponteiro para o nC3 inserido
}

//Insere um valor em alguma posição da lista
No *inserir_posicao(ListaSimples *lista, int dado, int posicao){
  // Alocar memC3ria para o novo nC3
	No *novo = (No *) malloc(sizeof(No));
	if (novo == NULL) {
		return NULL; // Falha na alocaC'C#o de memC3ri
	}
	// Atribuir valor e inicializar ponteiro 'proximo'
	novo->dado = dado;
	novo->proximo = NULL;

  int count = 0;
  if(posicao == 0) {
    return inserir_inicio(lista, dado);
  } else {
    No *aux = lista->primeiro;
    while(aux->proximo != NULL){
      if(count+1 == posicao) {
        novo->proximo = aux->proximo;
        aux->proximo = novo;
        return novo;
      }
      aux = aux->proximo;
      count++;
    }
    if(count+1 == posicao) {
      return inserir_fim(lista, dado);
    }
  }
	return NULL;
}

int remover_inicio(ListaSimples *lista) {
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
  }
  free(removido);
  return valor_removido;
}

int remover_fim(ListaSimples *lista){
  if (lista->primeiro == NULL) {
		return -1; // Lista vazia
	}
	No *removido = lista->ultimo;
	int valor_removido = removido->dado;
  if (lista->primeiro == lista->ultimo) {
		// Cnico nó: lista fica vazia
		lista->primeiro = NULL;
		lista->ultimo = NULL;
	} else {
	  No *aux = lista->primeiro;
		// VC!rios nC3s: atualizar ponteiros
		while(aux->proximo != lista->ultimo){
      aux = aux->proximo;
		}
		lista->ultimo = aux;
		aux->proximo = NULL;
	}
	free(removido);
	return valor_removido;
}

int remover_posicao(ListaSimples *lista, int posicao){
  if (lista == NULL || lista->primeiro == NULL || posicao < 0) {
		return -1; // Lista vazia
	}
  int count = 0;
  if(posicao == 0){
    remover_inicio(lista);
  } else {
    No *aux = lista->primeiro;
    No *anterior = NULL;
    while(aux->proximo != lista->ultimo && count < posicao){
      anterior = aux;
      aux = aux->proximo;
      count++;
      if(count+1 == posicao){
        int valor = aux->dado;
        anterior->proximo = aux->proximo;
        free(aux);
        return valor;
      }
    }
    if(count+1 == posicao){
      remover_fim(lista);
    }
  }
  
}

void imprimir_lista(ListaSimples *lista) {
  if (lista->primeiro == NULL) {
    printf("Lista vazia!\n");
    return;
  }
  No *atual = lista->primeiro;
  while (atual != NULL) {
    printf("%d ", atual->dado);
    atual = atual->proximo;
  }
  printf("\n");
}

void destruir_lista(ListaSimples *lista) {
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
}
