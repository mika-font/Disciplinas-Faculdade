#include "vetordinamico.h" //Inclui o arquivo dos protótipos de funções
#include <stdio.h>
#include <stdlib.h>

struct VetorDinamico {
    int tamanho;        // tamanho atual do vetor
    int capacidade;     // capacidade máxima do vetor
    int *elementos;     // array para armazenar os elementos
};

VetorDinamico* criar_vetor(int capacidade_inicial) {
    VetorDinamico *vetor = (VetorDinamico*)malloc(sizeof(VetorDinamico));
    if (vetor == NULL) {
        printf("Erro ao alocar memória para o vetor.\n");
        return NULL;
    }
    vetor->tamanho = 0;
    vetor->capacidade = capacidade_inicial;
    vetor->elementos = (int*)malloc(capacidade_inicial * sizeof(int));
    if (vetor->elementos == NULL) { //Caso não seja possível alocar memória
        printf("Erro ao alocar memória para os elementos do vetor.\n");
        free(vetor); // Libera a memória.
        return NULL;
    }
    return vetor;
}

void liberar_vetor(VetorDinamico *vetor) {
    if (vetor != NULL) {
        free(vetor->elementos);
        free(vetor);
    }
}

void adicionar_elemento(VetorDinamico *vetor, int elemento) {
    if (vetor->tamanho == vetor->capacidade) { // Se já tiver atingido o limite de memória.
        int nova_capacidade = vetor->capacidade * 2;
        int *novo_array = (int*)realloc(vetor->elementos, nova_capacidade * sizeof(int));
        if (novo_array == NULL) {
            printf("Erro ao realocar memória para os elementos do vetor.\n");
            return;
        }
        vetor->elementos = novo_array;
        vetor->capacidade = nova_capacidade;
    }
    vetor->elementos[vetor->tamanho] = elemento;
    vetor->tamanho++;
}

void imprimir_vetor(VetorDinamico *vetor) {
    if(vetor->tamanho == 0){
        printf("Vetor está vazio.\n");
    }
    printf("Elementos do vetor: ");
    for (int i = 0; i < vetor->tamanho; i++) {
        printf("%d ", vetor->elementos[i]);
    }
    printf("\n");
}

void remover_elemento(VetorDinamico *vetor, int posicao) {
    if (posicao < 0 || posicao >= vetor->tamanho){
        printf("Posição inválida.");
    } else {
        //free(vetor->elementos[posicao]);
        for (int i = posicao; i < vetor->tamanho - 1; i++) {
            vetor->elementos[i] = vetor->elementos[i + 1];
        }    
	    vetor->tamanho--;
    }
}

int buscar_elemento(VetorDinamico *vetor, int valor) {
    int i;
    for(i = 0; i < vetor->tamanho; i++){
        if(vetor->elementos[i] == valor){
            printf("O elemento %d está na posição: %d\n", vetor->elementos[i], i+1);
            return 1;
        }
    }
    if(i == vetor->tamanho){
        printf("Não encontrado.");
        return -1;
    }
}