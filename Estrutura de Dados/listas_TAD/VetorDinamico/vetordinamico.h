#ifndef VETORDINAMICO_H
#define VETORDINAMICO_H

// Definição incompleta do registro para evitar que o usuário modifique valores diretamente
typedef struct VetorDinamico VetorDinamico;

// Função para criar um novo VetorDinamico
VetorDinamico* criar_vetor(int capacidade_inicial);

// Função para liberar a memória alocada para o VetorDinamico
void liberar_vetor(VetorDinamico *vetor);

// Função para adicionar um elemento ao final do VetorDinamico
void adicionar_elemento(VetorDinamico *vetor, int elemento);

// Função para remover um elemento de uma posição específica do VetorDinamico
void remover_elemento(VetorDinamico *vetor, int posicao);

// Função para imprimir os elementos do VetorDinamico
void imprimir_vetor(VetorDinamico *vetor);

// Função para buscar a posição do primeiro elemento encontrado no VetorDinamico com valor igual ao parâmetro
int buscar_elemento(VetorDinamico *vetor, int valor);


#endif /* VETORDINAMICO_H */
