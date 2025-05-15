#ifndef LISTADUPLA_H
#define LISTADUPLA_H

// Definição incompleta do registro para evitar que o usuário modifique valores diretamente
typedef struct ListaDupla ListaDupla;
typedef struct No No;
typedef enum {
    INICIO, FIM
} Direcao;


// Função para criar uma nova Lista Duplamente encadeada
ListaDupla* criar_lista();

// Outras operações disponibilizadas pelo nosso TAD
void destruir_lista(ListaDupla *lista);

// Acesso
No *buscar(ListaDupla *lista, int dado);
// Implementar quando dir for FIM, impressão na ordem inversa
void imprimir_lista(ListaDupla *lista, Direcao dir);

// Inserção
No *inserir_inicio(ListaDupla *lista, int dado);
No *inserir_fim(ListaDupla *lista, int dado);
No *inserir_posicao(ListaDupla *lista, int dado, int posicao);

// Remoção
int remover_inicio(ListaDupla *lista);
int remover_fim(ListaDupla *lista);
int remover_posicao(ListaDupla *lista, int posicao);

#endif /* LISTADUPLA_H */
