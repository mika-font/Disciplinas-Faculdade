#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tad_configs.h"

// Necessário arquivo da lista de fichas ou da árvore?

// Função para criar um novo nó
No* criar_no(int chave) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->esquerdo = novoNo->direito = novoNo->pai = NULL;
    return novoNo;
}

// Função para inicializar uma árvore ABB
ABB* criar_abb() {
    ABB* abb = (ABB*) malloc(sizeof(ABB));
    abb->raiz = NULL;
    return abb;
}

// Função para inserir um nó na árvore
void inserir_no_na_arvore(ABB* abb, int chave) {
    if(abb->raiz == NULL){
        abb->raiz = criar_no(chave);
        return;
    } 
    No* atual = abb->raiz;
    No* pai = NULL;
    
    while (atual != NULL) {
        pai = atual;
        if (chave < atual->chave) {
            atual = atual->esquerdo; // Ir para a subárvore esquerda
        } else if (chave > atual->chave) {
            atual = atual->direito; // Ir para a subárvore direita
        } else {
            return; // Chave já existe, não inserir duplicado
        }
    }

    No* novoNo = criar_no(chave);
    novoNo->pai = pai; // Definir o pai do novo nó
    if(chave < pai->chave) {
        pai->esquerdo = novoNo; // Inserir como filho esquerdo
    } else {
        pai->direito = novoNo; // Inserir como filho direito
    }

    novoNo->lista_fichas = criar_lista();
}

No* minimo(No* node) {
    No* atual = node;
    while (atual && atual->esquerdo != NULL) {
        atual = atual->esquerdo; // Descer para o filho esquerdo
    }
    return atual; // Retorna o nó mínimo encontrado
}

No* maximo(No* node) {
    No* atual = node;
    while (atual && atual->direito != NULL) {
        atual = atual->direito; // Descer para o filho direito
    }
    return atual; // Retorna o nó máximo encontrado
}

No* sucessor(No* atual) {
    // Caso 1: Se o nó tem um filho à direita,
    // o sucessor é o menor nó na subárvore direita
    if (atual->direito != NULL){
        return minimo(atual->direito);
    }

    // Caso 2: Se o nó não tem filho à direita, subir na árvore usando o pai
    struct No_ar* ancestral = atual->pai;
    // Enquanto o atual for igual ao filho da direita do pai,
    // significa que ele é o filho da direita
    while (ancestral != NULL && atual == ancestral->direito) {
        atual = ancestral; // subindo na árvore
        ancestral = ancestral->pai; // subindo na árvore
    }
    return ancestral;
}

// Função para buscar um nó na árvore
No* buscar(No* raiz, int chave) {
    No* atual = raiz;
    while (atual != NULL) {
        if (chave == atual->chave) {
            return atual; // Nó encontrado
        } else if (chave < atual->chave) {
            atual = atual->esquerdo; // Buscar na subárvore esquerda
        } else {
            atual = atual->direito; // Buscar na subárvore direita
        }
    }
    return NULL; // Nó não encontrado
}

// Função para remover um nó da árvore.
void remover_no_na_arvore(ABB* abb, No* no) {
    No* no_remover;  
    No* filho_no_remover;

    // Se o nó a ser removido tem no máximo um filho
    if (no->esquerdo == NULL || no->direito == NULL){
        no_remover = no;
    } else {
        no_remover = sucessor(no);
    }

    // Atribua o filho do nó que será removido (pode ser NULL)
    if (no_remover->esquerdo != NULL){
        filho_no_remover = no_remover->esquerdo;
    } else {
        filho_no_remover = no_remover->direito;
    }

    // Se o filho do nó a ser removido não for nulo, atualize seu pai
    if (filho_no_remover != NULL){
        filho_no_remover->pai = no_remover->pai;
    }

    // Atualize o ponteiro do pai do nó a ser removido
    if (no_remover->pai == NULL) {
        abb->raiz = filho_no_remover;  // Caso o nó a ser removido seja a raiz
    } else if (no_remover == no_remover->pai->esquerdo) {
        no_remover->pai->esquerdo = filho_no_remover;
    } else {
        no_remover->pai->direito = filho_no_remover;
    }

    if (no_remover != no){
        no->chave = no_remover->chave;
    }

    // Libere a memória do nó que foi removido
    free(no_remover);
}

void alocar_no_na_arvore(ABB *abb, Ficha *ficha) {
    No *priori = buscar(abb->raiz, ficha->prioridade);
    if(priori == NULL){
        inserir_no_na_arvore(abb, ficha->prioridade); // cria um nó na arvore
        priori = buscar(abb->raiz, ficha->prioridade); // Busca novamente para obter o nó recém-criado
    }
    inserir_ficha_lista(priori->lista_fichas, ficha);

    // Se não encontrar, cria um novo nó de prioridade e cria a lista daquela prioridade
    // Se encontrar, insere a ficha na lista daquela prioridade
}