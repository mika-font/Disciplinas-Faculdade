#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tad_configs.h"

#define FILA_FICHAS  "./fila.txt"          //Arquivo de armazenamento de fila

// Função para selecionar a prioridade do paciente.
void selecionar_prioridade(int *prioridade) {
  int aux;
  printf("1 - Gestante\n2 - Idoso\n3 - Pessoa com necessidades especiais\n4 - Criança de colo\n5 - Doença crônica\n6 - Demais pacientes\n"); 
  printf("Informe a prioridade do paciente: ");
  scanf("%d", &aux);
  switch(aux) {
    case 1: *prioridade = 1; break;   // Gestante
    case 2: *prioridade = 2; break;   // Idoso 
    case 3: *prioridade = 3; break;   // Pessoa com necessidades especiais
    case 4: *prioridade = 4; break;   // Criança de colo
    case 5: *prioridade = 5; break;   // Doença crônica
    default: *prioridade = 6; break;  // Demais pacientes
  }
}

// Função para gerar um tempo de atendimento aleatório.
int intervalo(){
  return (rand() % 6) + 5;
}

// Função para preencher o campo nome da ficha.
void *preencher_nome(char nome[], int tamanho){
  int c;
  while ((c = getchar()) != '\n' && c != EOF); // Lê tudo o que foi digitado anteriormente até apertar enter
  printf("Digite o nome do paciente: ");
  fgets(nome, tamanho, stdin);
  nome[strcspn(nome, "\n")] = '\0';
}

// Função para preencher o campo médico da ficha.
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

// Função para criar o relatório
void criar_relatorio(Relat relatorio[]){
  const char *especialidades[6] = {
      "Cardiologista",
      "Dermatologista",
      "Neurologista",
      "Pediatra",
      "Ortopedista",
      "Clínico Geral"
  };

  for (int i = 0; i < 6; i++) {
    strcpy(relatorio[i].especialidade, especialidades[i]);
    relatorio[i].quantidade = 0;
  }
}

// Função para criar uma lista.
Lista *criar_lista() {
  Lista *lista = (Lista *) malloc(sizeof(Lista));
  if (lista == NULL) {
    printf("Erro ao alocar memória.");
    return NULL;
  }
  lista->primeiro = NULL;
  lista->ultimo = NULL;
  return lista;
}

// Função para inserir a ficha na respectiva fila.
Ficha *inserir_ficha_lista(Lista *lista, Ficha *ficha){
  if (lista == NULL || ficha == NULL) return NULL; 

  ficha->prox = NULL;

  if (lista->primeiro == NULL) {
    lista->primeiro = ficha;
    lista->ultimo = ficha;
  } else {
    lista->ultimo->prox = ficha;
    lista->ultimo = ficha;
  }
  return ficha;
}

// Função para registrar a quantidade de seleções de um determinado médico.
void registrar_relatorio(char medico[], Relat relatorio[]){
  for(int i = 0; i < 6; i++){
    if(strcmp(medico, relatorio[i].especialidade) == 0){ 
      relatorio[i].quantidade++;
    }
  }
}

// Função para preencher os campos necessários da ficha.
void gerar_ficha_menu(Ficha *ficha, int num, Relat *relatorio) {
  ficha->ficha = num;
  ficha->tempo = intervalo();
  preencher_nome(ficha->nome, 50);
  preencher_medico(ficha->medico, 50);
  registrar_relatorio(ficha->medico, relatorio);
  selecionar_prioridade(&ficha->prioridade);
}

// Função para imprimir a ficha retirada da lista.
void imprimir_ficha(Ficha *ficha){
  printf("Número:       F%d\nPaciente:     %s\nEspecialista: %s\nPrioridade:   %d\n", ficha->ficha, ficha->nome, ficha->medico, ficha->prioridade);
}

// Função para imprimir os próximos das filas
void imprimir_proximos(ABB *arvore, Lista *lista){
    // Próximo com prioridade
    No *prox_prior = NULL;
    Ficha *prox_ficha_prior = NULL;
    for (int i = 1; i <= 5; i++) {
        prox_prior = buscar(arvore->raiz, i);
        if (prox_prior && prox_prior->lista_fichas && prox_prior->lista_fichas->primeiro) {
            prox_ficha_prior = prox_prior->lista_fichas->primeiro;
            break;
        }
    }
    if (prox_ficha_prior) {
        printf("-> Próximo com prioridade: F%d.\n", prox_ficha_prior->ficha);
    } else {
        printf("-> Próximo com prioridade: Fila vazia.\n");
    }

    // Próximo sem prioridade
    if (lista && lista->primeiro) {
        printf("-> Próximo sem prioridade: F%d.\n", lista->primeiro->ficha);
    } else {
        printf("-> Próximo sem prioridade: Fila vazia.\n");
    }
}

// Função para retirar a ficha da respectiva fila.
void retirar_ficha_lista(Lista *lista){
  if (lista == NULL || lista->primeiro == NULL) {
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

// Função para imprimir todas as fichas de uma fila.
void imprimir_lista(Lista *lista) {
  if (lista->primeiro == NULL) {
    printf("Lista vazia!\n\n");
    return;
  }
  Ficha *atual = lista->primeiro;
  while (atual != NULL) {
    printf("Número:       F%d\nTempo:        %d\nPaciente:     %s\nEspecialista: %s\nPrioridade:   %d\n\n", atual->ficha, atual->tempo, atual->nome, atual->medico, atual->prioridade);
    atual = atual->prox;
  }
}

// Função para destruir a fila.
void destruir_lista(Lista *lista) {
  if (lista == NULL || lista->primeiro == NULL) {
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

// Função para criar e/ou abrir o arquivo de ficha.
FILE *abrir_arquivo() {
    FILE *arquivo;
    if(access(FILA_FICHAS, F_OK ) != -1 ) {   // Arquivo já existe
      arquivo = fopen(FILA_FICHAS, "r+");     
    } else {                                  // Arquivo não existe
      arquivo = fopen(FILA_FICHAS, "w+");     
    }
    return arquivo;
}

// Função para escrever no arquivo fila.txt.
void escrever_arquivo(Ficha *ficha) {
    FILE *arquivo = abrir_arquivo();
    if (ficha && arquivo) {
      fseek(arquivo, 0, SEEK_END);
      fprintf(arquivo, "Número: %d | Tempo: %d | Paciente: %s | Especialista: %s | Prioridade: %d\n", ficha->ficha, ficha->tempo, ficha->nome, ficha->medico, ficha->prioridade);
      fclose(arquivo);
    }
}

// Função para ler e retirar a ficha do arquivo fila.txt.
Ficha *ler_arquivo(TadConfigs *tad) {
    FILE *arquivo = abrir_arquivo();
    if (!arquivo) return NULL;

    char linha[200];
    Ficha *ficha = (Ficha *) malloc(sizeof(Ficha));
    if (ficha == NULL) {
        printf("Erro de alocação de memória.\n");
        fclose(arquivo);
        return NULL;
    }

    if (fgets(linha, sizeof(linha), arquivo)) {
      if(sscanf(linha, "Número: %d | Tempo: %d | Paciente: %[^|] | Especialista: %[^|] | Prioridade: %d\n", &ficha->ficha, &ficha->tempo, ficha->nome, ficha->medico, &ficha->prioridade) == 5){
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

// Função para reescrever o arquivo fila.txt sem a primeira linha.
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
