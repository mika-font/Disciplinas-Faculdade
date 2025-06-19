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
        return 1;
    }

    // Inicializa a lista de fichas sem prioridade.
    Lista *fila_sprior = criar_lista();
    if (fila_sprior == NULL) {
        printf("Erro ao criar lista de fichas.\n");
        return 1;
    }
    
    // Carregar configurações da simulação e imprime.
    configs_ler(tad_configs);
    configs_mostrar(tad_configs);

    while(tad_configs->configs.status != TERMINAR) {
        sleep(tad_configs->configs.intervalo); 
        int comando = ler_log(); // comando.log

        if(comando == 1){
            Ficha* ficha_nova;
            ficha_nova = ler_arquivo(tad_configs); //fila.txt

            if (ficha_nova == NULL){
                printf("Nenhuma ficha no arquivo.\n");
            } else {
                reescrever_arquivo(); //fila.txt
                if(ficha_nova->prioridade != 6){
                    fluxo_fila_arvore(arv_prioridades, ficha_nova); 
                } else {
                    inserir_ficha_lista(fila_sprior, ficha_nova); 
                }
                printf("Nova ficha gerada!\n");
            }

        } else if (comando == 2) {
            printf("\nImprimindo Listas de Fichas:");
            printf("\n==============================\n\n");
            for(int i = 1; i <= 5; i++){
                No *priori = buscar(arv_prioridades->raiz, i);
                if (priori != NULL && priori->lista_fichas != NULL && priori->lista_fichas->primeiro != NULL) {
                    printf("Prioridade %d:\n\n", i);
                    imprimir_lista(priori->lista_fichas);
                } else {
                    printf("Prioridade %d: Lista vazia.\n\n", i);
                }
            }
            printf("==============================\n\n");
            printf("Fichas sem prioridade:\n\n");
            imprimir_lista(fila_sprior);
            printf("==============================\n\n");
        } 

        if (tad_configs->configs.status == SIMULAR) {
            int p = 1;
            No *priori = NULL;
            while(p <= 5){
                priori = buscar(arv_prioridades->raiz, p);
                if (priori != NULL && priori->lista_fichas != NULL && priori->lista_fichas->primeiro != NULL){
                    break;
                }
                p++;
            }
            if (priori == NULL || priori->lista_fichas->primeiro == NULL){
                if (fila_sprior->primeiro != NULL){
                    Ficha *ficha = fila_sprior->primeiro;
                    int tempo = ficha->tempo;
                    printf("\n==============================\n\n");
                    imprimir_ficha(ficha);
                    printf("\n");
                    retirar_ficha_lista(fila_sprior);
                    imprimir_proximos(arv_prioridades, fila_sprior);
                    printf("\n");
                    simular_contagem(tempo);
                    printf("\n==============================\n\n");
                } else {
                    printf("Nenhuma ficha para simular.\n");
                }
            } else {
                Ficha *ficha = priori->lista_fichas->primeiro;
                int tempo = ficha->tempo;
                printf("\n==============================\n\n");
                imprimir_ficha(ficha);
                retirar_ficha_lista(priori->lista_fichas);
                if (priori->lista_fichas->primeiro == NULL) {
                    removerNo(arv_prioridades, priori);
                }
                imprimir_proximos(arv_prioridades, fila_sprior);
                simular_contagem(tempo);
                printf("\n==============================\n\n");
            }

        } 

        if (tad_configs->configs.status == AGUARDAR) {
            printf("Aguardando...\n");
        }

        configs_ler(tad_configs); //configuracoes.dat
    }
    
    destruir_arvore(arv_prioridades);
    destruir_lista(fila_sprior);
    return 0;
}