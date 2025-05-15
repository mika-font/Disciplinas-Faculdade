#include <stdio.h>
#include <stdlib.h>
#include "listaDupla.h" // Assuming you have updated the header to "listaDupla.h"

int main() {
  // Criar uma lista vazia
  ListaDupla *minhaLista = criar_lista();

  // Inserir alguns elementos na lista
  inserir_inicio(minhaLista, 10);
  inserir_inicio(minhaLista, 20);
  inserir_inicio(minhaLista, 30);

  // Imprimir a lista (para frente)
  printf("Lista: ");
  imprimir_lista(minhaLista, INICIO);

  // Remover o primeiro elemento
  int valorRemovido = remover_inicio(minhaLista);
  printf("Elemento removido: %d\n", valorRemovido);

  // Imprimir a lista novamente (para frente)
  printf("Lista após remoção: ");
  imprimir_lista(minhaLista, FIM);

  // Destruir a lista para liberar memória
  destruir_lista(minhaLista);

  printf("Lista destruída.\n");

  return 0;
}
