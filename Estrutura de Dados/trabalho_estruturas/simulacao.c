#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

void simular(Ficha *ficha) {
    printf("Simulando...\n");
    reescrever_arquivo();
    printf("Número: %d | Tempo: %d | Paciente: %s | Médico: %s\n", ficha->ficha, ficha->tempo, ficha->nome, ficha->medico);
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
    Ficha *ficha;
    int num = 1;
    int leitura = 1; // 1 para ler a última ficha, 0 para ler a primeira ficha.
    int ponto = 0;

    // Carregar configurações
    configs_ler(tad_configs);
    configs_mostrar(tad_configs);

    while(tad_configs->configs.status != TERMINAR) {
        sleep(tad_configs->configs.intervalo);
        if(tad_configs->configs.status == SIMULAR) {
            // Ler a ficha do arquivo de armazenamento e simular
            Ficha *ficha = ler_arquivo(tad_configs, 0);
            if (ficha != NULL) {
                configs_atualizar(tad_configs, SIMULAR, tad_configs->configs.intervalo);
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

                    /*ficha = ler_arquivo(tad_configs, leitura);
                if(ficha != NULL){
                    num = ficha->ficha + 1;
                }
                ficha = inserir_ficha_lista(fila, num);
                escrever_arquivo(ficha);
                free(ficha);
                if(ponto == 1) {
                    configs_atualizar(tad_configs, SIMULAR, 1, 0);
                    ponto = 0;
                }*/

    return 0;
}