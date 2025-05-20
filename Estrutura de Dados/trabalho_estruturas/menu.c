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
    TadConfigs *tad_configs;
    int op;
    // Criar TAD e abrir arquivo
    tad_configs = configs_inicializar();
    if (!tad_configs) {
        printf("Erro ao criar TAD\n");
        return 1;
    }
    Lista *fila = criar_lista();
    Ficha *ficha;
    int num = 1;
    do {
        op = menu();
        switch(op) {
            case 1: { // Faz a fila aguardar.
                configs_atualizar(tad_configs, AGUARDAR, 1);
                break;
            }
            case 2: { // Faz a fila avançar.
                configs_atualizar(tad_configs, SIMULAR, 1);
                break;
            }
            case 3: {
                configs_atualizar(tad_configs, TERMINAR, 1);
                break;
            }
            case 4: {
                // Carregar configurações
                configs_ler(tad_configs);
                // Exibir configurações (carrega do arquivo existente se existir)
                configs_mostrar(tad_configs);
                break;
            }
            case 5: { 
                inserir_ficha_lista(fila, num);
                num++;
                /*ler_arquivo();
                if(arquivo != NULL){
                    num = 12+1;
                } else {}
                ficha = inserir_ficha_lista(fila, num);
                escrever_arquivo(ficha);*/
                break;
            }
            case 6: { 
                imprimir_lista(fila);
                break;
            }
            case 0: {
                configs_destruir(tad_configs);
                destruir_lista(fila);
                printf("Até a próxima!\n");
                break;
            }
            default: {
                printf("Opção inválida!\n");
            }
        }
    } while (op != 0);
    return 0;
}
