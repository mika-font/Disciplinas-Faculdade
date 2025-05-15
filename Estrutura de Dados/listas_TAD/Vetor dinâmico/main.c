#include <stdio.h>
#include "vetordinamico.h"

int main() {
    // Criar um vetor dinâmico com capacidade inicial de 5 elementos
    VetorDinamico *vetor = criar_vetor(5);

    // Adicionar elementos ao vetor
    adicionar_elemento(vetor, 10);
    adicionar_elemento(vetor, 20);
    adicionar_elemento(vetor, 30);
    adicionar_elemento(vetor, 40);
    adicionar_elemento(vetor, 50);

    // Imprimir o vetor
    printf("Vetor após adicionar elementos:\n");
    imprimir_vetor(vetor);

    // Remover o elemento na posição 2
    remover_elemento(vetor, 2);

    // Imprimir o vetor após a remoção
    printf("Vetor após remover o elemento na posição 2:\n");
    imprimir_vetor(vetor);

    // Liberar a memória alocada para o vetor
    liberar_vetor(vetor);

    return 0;
}
