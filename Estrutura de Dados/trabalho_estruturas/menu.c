#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

int menu() {
    printf("1. Aguardar\n2. Simular\n3. Terminar\n4. Ler\n5. Nova Ficha\n0. Sair\n");
    printf("Informe a opção desejada: ");
    int aux;
    scanf("%d", &aux);
    return aux;
}

int main() {
    // Inicializa o TAD do Configs e o arquivo de comunicação.
    TadConfigs *tad_configs;
    int op;
    tad_configs = configs_inicializar();
    if (!tad_configs) {
        printf("Erro ao criar TAD\n");
        return 1;
    }
    // Incializa a lista de fichas.
    Lista *fila = criar_lista();
    Ficha *ficha;
    int num = 1;
    int leitura = 1; // 1 para ler a última ficha, 0 para ler a primeira ficha.
    int ponto = 0;
    do {
        configs_ler(tad_configs);
        if(tad_configs->configs.apagar == 1) {
            retirar_ficha_lista(fila);
            configs_atualizar(tad_configs, tad_configs->configs.status, tad_configs->configs.intervalo, 0);
        }
        op = menu();
        switch(op) {
            case 1: { // Faz a simulação aguardar.
                configs_atualizar(tad_configs, AGUARDAR, 1, 0);
                break;
            }
            case 2: { // Faz a simulação rodar.
                configs_atualizar(tad_configs, SIMULAR, 1, 0);
                break;
            }
            case 3: { // Faz a simulação terminar.
                configs_atualizar(tad_configs, TERMINAR, 1, 0);
                break;
            }
            case 4: { // Faz a leitura do arquivo de comunicação.
                configs_ler(tad_configs);
                configs_mostrar(tad_configs);
                break;
            }
            case 5: { // Inserer uma nova ficha na lista.
                if(tad_configs->configs.status == SIMULAR) {
                    configs_atualizar(tad_configs, AGUARDAR, 1, 0);
                    ponto = 1;
                } else {
                    ponto = 0;
                }
                ficha = ler_arquivo(tad_configs, leitura);
                if(ficha != NULL){
                    num = ficha->ficha + 1;
                }
                ficha = inserir_ficha_lista(fila, num);
                escrever_arquivo(ficha);
                free(ficha);
                if(ponto == 1) {
                    configs_atualizar(tad_configs, SIMULAR, 1, 0);
                    ponto = 0;
                }
                break;
            }
            case 6: { 
                imprimir_lista(fila);
                break;
            }
            case 0: {
                configs_atualizar(tad_configs, AGUARDAR, 1, 0);
                configs_destruir(tad_configs);
                destruir_lista(fila);
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
