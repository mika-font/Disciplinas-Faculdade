#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

int menu() {
    printf("1. Aguardar\n2. Simular\n3. Terminar\n4. Ler\n5. Nova Ficha\n6. Imprimir Fila\n0. Sair\n");
    printf("Informe a opção desejada: ");
    int aux;
    scanf("%d", &aux);
    return aux;
}

int main() {
    // Inicializa o TAD do Configs e o arquivo de comunicação.
    TadConfigs *tad_configs;
    int op;
    int num = 1;
    tad_configs = configs_inicializar();
    if (!tad_configs) {
        printf("Erro ao criar TAD\n");
        return 1;
    }
    do {
        op = menu();
        switch(op) {
            case 1: { // Faz a simulação aguardar.
                configs_atualizar(tad_configs, AGUARDAR, 1);
                break;
            }
            case 2: { // Faz a simulação rodar.
                configs_atualizar(tad_configs, SIMULAR, 1);
                break;
            }
            case 3: { // Faz a simulação terminar.
                configs_atualizar(tad_configs, TERMINAR, 1);
                break;
            }
            case 4: { // Faz a leitura do arquivo de comunicação.
                configs_ler(tad_configs);
                configs_mostrar(tad_configs);
                break;
            }
            case 5: { // Inserer uma nova ficha no arquivo.
                Ficha *ficha = malloc(sizeof(Ficha));
                if (!ficha) {
                    printf("Erro ao alocar memória para ficha!\n");
                    break;
                }
                gerar_ficha_menu(ficha, num);
                printf("Nova ficha gerada!\n");

                if(tad_configs->configs.status == SIMULAR) {
                    configs_atualizar(tad_configs, AGUARDAR, 1); // Simulação aguarda a nova ficha ser gerada.
                    escrever_arquivo(ficha);
                    sleep(1);
                    configs_atualizar(tad_configs, GERAR_FICHA, 1); // Realiza as etapas de alocar a ficha no sistema.
                    printf("Ficha alocada no sistema!\n");
                    sleep(1);
                    configs_atualizar(tad_configs, SIMULAR, 1); // Retorna a simular.
                } else {
                    escrever_arquivo(ficha);
                    sleep(1);
                    configs_atualizar(tad_configs, GERAR_FICHA, 1); // Realiza as etapas de alocar a ficha no sistema.
                    printf("Ficha alocada no sistema!\n");
                    sleep(1);
                    configs_atualizar(tad_configs, AGUARDAR, 1);
                }
                num++;
                free(ficha);
                break;
            }
            case 6: { // Imprimir lista de fichas.
                if(tad_configs->configs.status == SIMULAR) {
                    configs_atualizar(tad_configs, IMPRIMIR, 1); 
                    sleep(1);
                    configs_atualizar(tad_configs, SIMULAR, 1); 
                } else {
                    configs_atualizar(tad_configs, IMPRIMIR, 1);
                    sleep(1);
                    configs_atualizar(tad_configs, AGUARDAR, 1); 
                }
                break;
            }
            case 0: {
                configs_atualizar(tad_configs, AGUARDAR, 1);
                configs_destruir(tad_configs);
                printf("Até a próxima!\n");
                break;
            }
            default: {
                printf("Opção inválida!\n");
                break;
            }
        }
    } while (op != 0);
    return 0;
}
