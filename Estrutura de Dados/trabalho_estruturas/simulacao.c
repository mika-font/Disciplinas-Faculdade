#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

void simular(int tempo) {
    printf("Simulando...\n");
    sleep(tempo);
}

int main() {
    TadConfigs *tad_configs;
    // Criar TAD e abrir arquivo
    tad_configs = configs_inicializar();
    if (!tad_configs) {
      printf("Erro ao criar TAD\n");
      return 1;
    }
    printf("Arquivo acessado!");
    // Carregar configurações
    configs_ler(tad_configs);
    configs_mostrar(tad_configs);
    while(tad_configs->configs.status != TERMINAR) {
        sleep(1);
        if(tad_configs->configs.status == SIMULAR) {
            simular(2);
        } else {
            printf("Aguardando...\n");
        }
        configs_ler(tad_configs);
    }

    return 0;
}
/*Deve-se implementar uma fila utilizando lista encadeada.
No menu, o usuário cria uma nova ficha, um tempo (de preferência
aleatório) é associado a esta ficha. Depois, adicionar a mesma na fila.
Na TV, conforme o tempo passa, os itens são removidos da fila e
apresentados na tela. Quando terminar o tempo, chama o próximo.

typedef struct Node {
    int ficha;           // Número da ficha
    int tempo;           // Tempo de atendimento
    struct Node* prox;   // Ponteiro para o próximo nó
} Node;

// Estrutura da fila
typedef struct {
    Node* ini;  // Início da fila
    Node* fim;  // Fim da fila
} Fila;*/