#ifndef LISTACIRCULAR_H
#define LISTACIRCULAR_H

// Definição incompleta do registro para evitar que o usuário modifique valores diretamente
typedef struct ListaCircular ListaCircular;
typedef struct No No;

// Função para criar uma nova Lista Circular
ListaCircular* criar_lista();

// Outras operações disponibilizadas pelo nosso TAD
void destruir_lista(ListaCircular *lista);

// Acesso
No *buscar(ListaCircular *lista, int dado);
void imprimir_lista(ListaCircular *lista);

// Inserção
No *inserir_inicio(ListaCircular *lista, int dado);
No *inserir_fim(ListaCircular *lista, int dado);
// Agora temos o tamanho, que pode ser usado para verificar se a posição é válida
No *inserir_posicao(ListaCircular *lista, int dado, int posicao);
// Teste com N inserções através dessa função
// A posição depende do valor e os elementos inseridos até o momento da nova inserção
No *inserir_ordem_crescente(ListaCircular *lista, int dado);

// Remoção
int remover_inicio(ListaCircular *lista);
int remover_fim(ListaCircular *lista);
int remover_posicao(ListaCircular *lista, int dado, int posicao);

#endif /* LISTACIRCULAR_H */
