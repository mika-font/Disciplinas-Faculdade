#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"

int menu() {
    printf("1. Aguardar\n2. Simular\n3. Terminar\n4. Ler\n5. Nova Ficha\n6. Imprimir Filas\n7. Imprimir Relatório\n0. Sair\n");
    printf("Informe a opção desejada: ");
    int aux;
    int res = scanf("%d", &aux);
    // Limpa o buffer do teclado e verifica entrada indevida
    if (res != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer até o fim da linha
        aux = -1; 
    }
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

    Relat relatorio[6];
    criar_relatorio(relatorio);

    do {
        op = menu();
        switch(op) {
            case 1: { 
                configs_atualizar(tad_configs, AGUARDAR, 1);
                break;
            }
            case 2: { 
                configs_atualizar(tad_configs, SIMULAR, 1);
                break;
            }
            case 3: { 
                configs_atualizar(tad_configs, TERMINAR, 1);
                break;
            }
            case 4: { // Faz a leitura do arquivo de comunicação.
                configs_ler(tad_configs);
                configs_mostrar(tad_configs);
                break;
            }
            case 5: { // Inserer uma nova ficha no arquivo e atualiza o log de comando
                Ficha *ficha = malloc(sizeof(Ficha));
                if (!ficha) {
                    printf("Erro ao alocar memória para ficha!\n");
                    break;
                }
                gerar_ficha_menu(ficha, num, relatorio);
                printf("Nova ficha gerada!\n");
                escrever_arquivo(ficha); 
                escrever_log(1);

                num++;
                free(ficha);
                break;
            }
            case 6: { // Imprimir lista de fichas.
                escrever_log(2);
                break;
            }
            case 7: { // Imprimir relatorio.
                printf("\nRelatorio:");
                printf("\n=========================\n\n");
                for (int i = 0; i < 6; i++){
                    printf("%s: %d\n", relatorio[i].especialidade, relatorio[i].quantidade);
                }
                printf("\n=========================\n\n");
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
