#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tad_configs.h"

#define FILA_FICHAS  "./fila.txt"          //Arquivo de armazenamento de fila

void *selecionar_prioridade(int prioridade) {
  int aux;
  printf("1 - Gestante\n2 - Idoso\n3 - Pessoa com necessidades especiais\n4 - Criança de colo\n5 - Doença crônica\n6 - Demais pacientes\n"); 
  printf("Informe a prioridade do paciente: ");
  scanf("%d", &aux);
  switch(aux) {
    case 1: {
      prioridade = 1; // Gestante
      break;
    }
    case 2: {
      prioridade = 2; // Idoso
      break;
    }
    case 3: {
      prioridade = 3; // Pessoa com necessidades especiais
      break;
    }
    case 4: {
      prioridade = 4; // Criança de colo
      break;
    }
    case 5: {
      prioridade = 5; // Doença crônica
      break;
    }
    default: {
      prioridade = 6; // Demais pacientes
      break;
    }
  }
}

// Gera um tempo de atendimento aleatório.
int intervalo(){
  return rand() % (10 - 5 + 1) + 5;
}

// Preenche o campo nome da ficha.
void *preencher_nome(char nome[], int tamanho){
  int c;
  while ((c = getchar()) != '\n' && c != EOF); // Limpa o buffer de entrada
  printf("Digite o nome do paciente: ");
  fgets(nome, tamanho, stdin);
  nome[strcspn(nome, "\n")] = '\0';
}

// Preenche o campo médico da ficha.
void *preencher_medico(char medico[], int tamanho){
  printf("1 - Cardiologista\n2 - Dermatologista\n3 - Neurologista\n4 - Pediatra\n5 - Ortopedista\n0 - Clínico Geral\n");
  printf("Informe a especialidade que deseja consultar: ");
  int aux;
  scanf("%d", &aux);
  switch(aux) {
    case 1: {
      strncpy(medico, "Cardiologista", tamanho);
      break;
    }
    case 2: {
      strncpy(medico, "Dermatologista", tamanho);
      break;
    }
    case 3: {
      strncpy(medico, "Neurologista", tamanho);
      break;
    }
    case 4: {
      strncpy(medico, "Pediatra", tamanho);
      break;
    }
    case 5: {
      strncpy(medico, "Ortopedista", tamanho);
      break;
    }
    default: {
      strncpy(medico, "Clínico Geral", tamanho);
      break;
    }
  }
}

// Cria uma lista.
Lista *criar_lista() {
  Lista *lista = (Lista *) malloc(sizeof(Lista));
  if (lista == NULL) {
    printf("Erro ao alocar memória.");
    return NULL; // Falha na alocação de memória
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  return lista;
}

// Cria uma ficha e chama as funções de preencher nome e médico e determinar o tempo de atendimento.
Ficha *inserir_ficha_lista(Lista *lista, int num){
  Ficha *ficha = (Ficha *) malloc(sizeof(Ficha));
  if (ficha == NULL) {
    printf("Erro ao alocar memória.");
    return NULL; // Falha na alocação de memória
  }
  ficha->ficha = num;
  ficha->tempo = intervalo();
  preencher_nome(ficha->nome, 50);
  preencher_medico(ficha->medico, 50);

  if(lista->ultimo == NULL){
    lista->primeiro = ficha;
    lista->ultimo = ficha;
  } else {
    lista->ultimo->prox = ficha;
    lista->ultimo = ficha;
  }
  ficha->prox = NULL;
  return ficha;
}

// Imprime a ficha retirada da lista e do arquivo.
void imprimir_ficha(Ficha *ficha){
  printf("Número: %d | Paciente: %s | Médico: %s", ficha->ficha, ficha->nome, ficha->medico);
  printf("\n");
}

// Retira a ficha da lista e libera a memória.
void retirar_ficha_lista(Lista *lista){
  if (lista->primeiro == NULL) {
    return;
  } else {
    Ficha *seguinte = lista->primeiro;
    if (lista->primeiro == lista->ultimo) {
      lista->primeiro = NULL;
      lista->ultimo = NULL;
    } else {
      lista->primeiro = lista->primeiro->prox;
    }
    free(seguinte);
  }
}

// Imprime a lista presente na memória do programa.
void imprimir_lista(Lista *lista) {
  if (lista->primeiro == NULL) {
    printf("Lista vazia!\n");
    return;
  }
  Ficha *atual = lista->primeiro;
  while (atual != NULL) {
    printf("Número: %d | Tempo: %d | Paciente: %s | Especialista: %s", atual->ficha, atual->tempo, atual->nome, atual->medico);
    printf("\n");
    atual = atual->prox;
  }
  printf("\n");
}

// Destrói a lista na memória do programa.
void destruir_lista(Lista *lista) {
  if (lista->primeiro == NULL) {
    return;
  }
  Ficha *atual = lista->primeiro;
  Ficha *anterior;
  while (atual != NULL) {
    anterior = atual;
    atual = atual->prox;
    free(anterior);
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
}

// Abre o arquivo de fichas, criando-o se não existir.
FILE *abrir_arquivo() {
    FILE *arquivo;
    if(access(FILA_FICHAS, F_OK ) != -1 ) {   // Arquivo já existe
      arquivo = fopen(FILA_FICHAS, "r+");     // Apenas abre o arquivo
    } else {                                  // Arquivo não existe
      arquivo = fopen(FILA_FICHAS, "w+");     // Cria arquivo novo
    }
    return arquivo;
}

// Escreve a ficha no arquivo.
void escrever_arquivo(Ficha *ficha) {
    FILE *arquivo = abrir_arquivo();
    if (ficha && arquivo) {
      fseek(arquivo, 0, SEEK_END);
      fprintf(arquivo, "Número: %d | Tempo: %d | Paciente: %s | Médico: %s\n", ficha->ficha, ficha->tempo, ficha->nome, ficha->medico);
      fclose(arquivo);
    }
}

// Lê o arquivo e retira a ficha do arquivo.
Ficha *ler_arquivo(TadConfigs *tad, int leitura) {
    FILE *arquivo = abrir_arquivo();
    if (!arquivo) return NULL;

    char linha[200];
    Ficha *ficha = (Ficha *) malloc(sizeof(Ficha));
    if (!ficha) {
        printf("Erro de alocação de memória.\n");
        fclose(arquivo);
        return NULL;
    }

    if (fgets(linha, sizeof(linha), arquivo)) {
      if(sscanf(linha, "Número: %d | Tempo: %d | Paciente: %[^|]| Médico: %[^\n]", &ficha->ficha, &ficha->tempo, ficha->nome, ficha->medico) == 4){
        ficha->nome[strcspn(ficha->nome, "\n")] = '\0';
        ficha->medico[strcspn(ficha->medico, "\n")] = '\0';
        ficha->prox = NULL;
      } else {
        printf("Erro ao ler os dados da ficha.\n");
        free(ficha);
        ficha = NULL;
      }
    } else {
        free(ficha);
        ficha = NULL;
    }

    fclose(arquivo);
    return ficha;
}

// Reescreve o arquivo sem a ficha retirada.
void reescrever_arquivo() {
    FILE *arquivo = abrir_arquivo();
    if (!arquivo) {
        perror("Erro ao abrir o arquivo de fichas");
        return;
    }

    FILE *temporario = fopen("temp.txt", "w");
    if (!temporario) {
        perror("Erro ao criar arquivo temporário");
        fclose(arquivo);
        return;
    }

    char linha[200];
    int linha_atual = 0;
    while (fgets(linha, sizeof(linha), arquivo)) {
      if (linha_atual > 0) {
        fputs(linha, temporario);
      }
      linha_atual++;
    }
    fclose(arquivo);
    fclose(temporario);

    remove(FILA_FICHAS);
    rename("temp.txt", FILA_FICHAS);
}

// Recupera a lista de fichas do arquivo e a armazena na memória do programa.
// Ocorre todo início de programa.
void recuperar_lista(Lista *lista) {
    FILE *arquivo = abrir_arquivo();
    if(!arquivo) return;

    char linha[200];
    while (fgets(linha, sizeof(linha), arquivo)) {
      Ficha *ficha = (Ficha *) malloc(sizeof(Ficha));
      if (sscanf(linha, "Número: %d | Tempo: %d | Paciente: %[^|]| Médico: %[^\n]", &ficha->ficha, &ficha->tempo, ficha->nome, ficha->medico) == 4) {
        ficha->nome[strcspn(ficha->nome, "\n")] = '\0';
        ficha->medico[strcspn(ficha->medico, "\n")] = '\0';
        ficha->prox = NULL;
        if (lista->primeiro == NULL) {
            lista->primeiro = ficha;
            lista->ultimo = ficha;
        } else {
            lista->ultimo->prox = ficha;
            lista->ultimo = ficha;
        }
      } else {
          free(ficha);  // Se falhar o sscanf, libera a ficha
      }
    }
    fclose(arquivo);
}