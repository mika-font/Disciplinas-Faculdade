#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tad_configs.h"

#define CONFIGS_FILE "./configuracoes.dat" //Arquivo de comunicação entre os prompts

TadConfigs *configs_inicializar() {//const char *nome_arquivo
    TadConfigs *tad = malloc(sizeof(TadConfigs));
    if (!tad) {
      return NULL;
    }
    FILE *arquivo = configs_abrir();
    if(arquivo) {
        // lê os dados
        configs_ler(tad);
        configs_fechar(arquivo);
    } else {
        return NULL;
    }
    return tad;
}
FILE *configs_abrir() {
    FILE *arquivo;
    if(access(CONFIGS_FILE, F_OK ) != -1 ) {  // Arquivo já existe
        arquivo = fopen(CONFIGS_FILE, "rb+"); // Apenas abre o arquivo
    } else {                                  // Arquivo não existe
        arquivo = fopen(CONFIGS_FILE, "wb+"); // Cria arquivo novo
        TadConfigs *tad = malloc(sizeof(TadConfigs));
        tad->configs.status = AGUARDAR;       // Inicializa o TAD com dados padrão
        tad->configs.intervalo = 1;           // Atualização de tela
        if(tad && arquivo) {                  // Se existe ambos, ele irá escrever o tad no arquivo
          fwrite(&tad->configs, sizeof(Configs), 1, arquivo);
        }
    }
    return arquivo;
}
void configs_fechar(FILE *arquivo) { // Fecha o arquivo
    fclose(arquivo);
}
void configs_destruir(TadConfigs *tad) {
  if (tad) {
    if (tad->arquivo) {
      fclose(tad->arquivo);
    }
    free(tad);
  }
}
void configs_salvar(TadConfigs *tad) { // Salva os dados no arquivo no HD.
    FILE *arquivo = configs_abrir();
    if (tad && arquivo) {
      fwrite(&tad->configs, sizeof(Configs), 1, arquivo);
    }
    configs_fechar(arquivo);
}
void configs_ler(TadConfigs *tad) { //
  FILE *arquivo = configs_abrir();
  if (tad && arquivo) {
    fread(&tad->configs, sizeof(Configs), 1, arquivo);
  }
  configs_fechar(arquivo);
}
void configs_mostrar(TadConfigs *tad) {
  if (tad) {
      // Exibir configurações (carrega do arquivo existente se existir)
      printf("\nConfigurações:\n");
      printf(" - Status: %s\n", tad->configs.status == 0 ? "Aguardar" : tad->configs.status == 1 ? "Simular" : "Terminar");
      printf(" - Intervalo: %d segundo\n\n", tad->configs.intervalo);
  }
}
void configs_atualizar(TadConfigs *tad, statusProcessamento status, int intervalo) {
  if(tad) { //Atualiza o arquivo de comunicação
    tad->configs.status = status;
    tad->configs.intervalo = intervalo;
    configs_salvar(tad);
  }
}