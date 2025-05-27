#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

void simular(Ficha *ficha) {
    printf("Simulando...\n");
    reescrever_arquivo();
    //printf("Número: %d | Tempo: %d | Paciente: %s | Médico: %s\n", ficha->ficha, ficha->tempo, ficha->nome, ficha->medico);
    sleep(ficha->tempo);
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

    // Inicializa a lista de fichas.
    Lista *fila = criar_lista();
    recuperar_lista(fila);
    int num;
    if (ler_arquivo(tad_configs, 0) == NULL || fila->ultimo == NULL) {
        num = 0; 
    } else {
        num = fila->ultimo->ficha;
    }
    
    // Carregar configurações
    configs_ler(tad_configs);
    configs_mostrar(tad_configs);

    while(tad_configs->configs.status != TERMINAR) {
        sleep(tad_configs->configs.intervalo);
        if(tad_configs->configs.status == GERAR_FICHA){
            num++;
            Ficha *ficha = inserir_ficha_lista(fila, num);
            escrever_arquivo(ficha);
        } else if (tad_configs->configs.status == SIMULAR) {
            if (ler_arquivo(tad_configs, 0) != NULL && fila->primeiro != NULL) {
                Ficha *ficha = fila->primeiro;
                simular(ficha);
                imprimir_ficha(ficha);
                retirar_ficha_lista(fila); 
            } else {
                printf("Nenhuma ficha para simular.\n");
                //configs_atualizar(tad_configs, AGUARDAR, 1); 
            }
        } else if (tad_configs->configs.status == IMPRIMIR) {
            printf("Imprimindo lista de fichas:\n");
            imprimir_lista(fila);
        } else {
            printf("Aguardando...\n");
        }
        configs_ler(tad_configs);
    }
    return 0;
}