#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

// Função para embelezar o Simulando...
void simular_contagem(int segundos) {
    for (int i = segundos; i >= 0; i--) {
        printf("\rSimulando... %2d", i); // \r volta ao início da linha
        fflush(stdout);
        sleep(1); 
    }
    printf("\n");
}

// Função para simular a ficha e reescrever o arquivo.
void simular(Ficha *ficha) {
    printf("Simulando...\n");
    reescrever_arquivo();
    simular_contagem(ficha->tempo);
}

int main() {
    // Inicializa o TAD do Configs e o arquivo de comunicação.
    TadConfigs *tad_configs;
    tad_configs = configs_inicializar();
    if (!tad_configs) {
      printf("Erro ao criar TAD\n");
      return 1;
    }
    printf("Arquivo acessado!");

    // Inicializa a árvore de prioridades.
    ABB *arv_prioridades = criar_abb();
    if (arv_prioridades == NULL){
        printf("Erro ao criar árvore de prioridades.\n");
        return 1; // Falha na alocação de memória
    }

    

    // Inicializa a lista de fichas.
    /*Lista *fila = criar_lista();
    recuperar_lista(fila);
    int num;
    if (ler_arquivo(tad_configs) == NULL || fila->ultimo == NULL) {
        num = 0; 
    } else {
        num = fila->ultimo->ficha;
    }*/
    
    // Carregar configurações da simulação e imprime elas.
    configs_ler(tad_configs);
    configs_mostrar(tad_configs);

    while(tad_configs->configs.status != TERMINAR) {
        sleep(tad_configs->configs.intervalo);

        if(tad_configs->configs.status == GERAR_FICHA){
            Ficha* ficha = (Ficha *) malloc(sizeof(Ficha));
            if (ficha == NULL) {
                printf("Erro ao alocar memória para a ficha.\n");
                return 1; // Falha na alocação de memória
            }

            ficha = ler_arquivo_fim();
            
            switch (ficha->prioridade){
                case 1: alocar_no_arvore(1); break;
                case 2: alocar_no_arvore(2); break;
                case 3: alocar_no_arvore(3); break;
                case 4: alocar_no_arvore(4); break;
                case 5: alocar_no_arvore(5); break;
                default: alocar_no_arvore(6); break;
            }

        } else if (tad_configs->configs.status == SIMULAR) {
            // Verifica se há fichas para simular na arvore de prioridade
            // Se houver, simula a ficha, imprime na tela e altera a fila
            // Reescreve o arquivo de fichas sem a ficha retirada
            // Se não houver, vai para a fila de espera padrão e verifica se há fichas para simular
            // Se houver, simula a ficha, imprime na tela e altera a fila
            // Reescreve o arquivo de fichas sem a ficha retirada
            // Se não houver, avisa que não há fichas para simular

            /*if (ler_arquivo(tad_configs) != NULL && fila->primeiro != NULL) {
                Ficha *ficha = fila->primeiro;
                simular(ficha);
                imprimir_ficha(ficha);
                retirar_ficha_lista(fila); 
            } else {
                printf("Nenhuma ficha para simular.\n");
                //configs_atualizar(tad_configs, AGUARDAR, 1); 
            }*/
        } else if (tad_configs->configs.status == IMPRIMIR) {
            //printf("Imprimindo lista de fichas:\n");
            //imprimir_lista(fila);
        } else {
            printf("Aguardando...\n");
        }
        configs_ler(tad_configs);
    }
    return 0;
}