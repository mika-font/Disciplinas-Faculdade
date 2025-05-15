#include <stdio.h>
#include <stdlib.h>
#include "listaSimples.h"

int main() {
  // Criar uma lista vazia
  ListaSimples *minhaLista = criar_lista();

  // Inserir alguns elementos na lista
  inserir_inicio(minhaLista, 10);
  inserir_inicio(minhaLista, 20);
  inserir_inicio(minhaLista, 30);

  // Imprimir a lista
  printf("Lista: ");
  imprimir_lista(minhaLista);

  // Remover o primeiro elemento
  int valorRemovido = remover_inicio(minhaLista);
  printf("Elemento removido: %d\n", valorRemovido);

  // Imprimir a lista novamente
  printf("Lista após remoção: ");
  imprimir_lista(minhaLista);

  // Destruir a lista para liberar memória
  destruir_lista(minhaLista);

  printf("Lista destruída.\n");

  return 0;
}
