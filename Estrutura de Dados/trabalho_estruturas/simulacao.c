#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

void simular(Ficha *ficha) {
    printf("Simulando...\n");
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

    // Carregar configurações
    configs_ler(tad_configs);
    configs_mostrar(tad_configs);

    while(tad_configs->configs.status != TERMINAR) {
        sleep(tad_configs->configs.intervalo);
        if(tad_configs->configs.status == SIMULAR) {
            // Ler a ficha do arquivo de armazenamento e simular
            Ficha *ficha = ler_arquivo(tad_configs, 0);
            if (ficha != NULL) {
                configs_atualizar(tad_configs, SIMULAR, tad_configs->configs.intervalo, 1);
                simular(ficha);
                free(ficha);
            } else {
                printf("Nenhuma ficha para simular.\n");
            }
        } else {
            printf("Aguardando...\n");
        }
        configs_ler(tad_configs);
    }

    return 0;
}