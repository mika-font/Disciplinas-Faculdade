#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "tad_configs.h"

// Função para criar um novo nó.
No* criar_no(int chave) {
    No* novoNo = (No*) malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->esquerdo = novoNo->direito = novoNo->pai = NULL;
    return novoNo;
}

// Função para inicializar a árvore ABB.
ABB* criar_abb() {
    ABB* abb = (ABB*) malloc(sizeof(ABB));
    abb->raiz = NULL;
    return abb;
}

// Função para inserir um nó na árvore.
void inserir_no_na_arvore(ABB* abb, int chave) {
    if(abb->raiz == NULL){
        abb->raiz = criar_no(chave);
        if (abb->raiz == NULL) {
            printf("Erro ao alocar nó raiz.\n");
            return;
        }

        abb->raiz->lista_fichas = criar_lista();
        if (abb->raiz->lista_fichas == NULL) {
            printf("Erro ao criar lista de fichas para o nó raiz.\n");
            free(abb->raiz);
            abb->raiz = NULL;
        }

        return;
    } 
    
    No* atual = abb->raiz;
    No* pai = NULL;
    
    while (atual != NULL) {
        pai = atual;
        if (chave < atual->chave) {
            atual = atual->esquerdo;
        } else if (chave > atual->chave) {
            atual = atual->direito; 
        } else { // Não insere duplicado
            return; 
        }
    }

    No* novoNo = criar_no(chave);
    if (novoNo == NULL) {
        printf("Erro ao alocar novo nó.\n");
        return;
    }

    novoNo->pai = pai; 
    if(chave < pai->chave) {
        pai->esquerdo = novoNo; 
    } else {
        pai->direito = novoNo;
    }

    novoNo->lista_fichas = criar_lista();
    if(novoNo->lista_fichas == NULL) {
        printf("Erro ao criar lista de fichas para o nó.\n");
        if(chave < pai->chave){
            pai->esquerdo = NULL;
        } else {
            pai->direito = NULL;
        } 
        free(novoNo);
        return; // Falha na alocação de memória
    }
}

// Função para encontrar o menor nó da árvore
No* minimo(No* node) {
    No* atual = node;
    while (atual && atual->esquerdo != NULL) {
        atual = atual->esquerdo;
    }
    return atual;
}

// Função para encontrar o maior nó da árvore
No* maximo(No* node) {
    No* atual = node;
    while (atual && atual->direito != NULL) {
        atual = atual->direito;
    }
    return atual;
}

// Função para encontrar o sucessor de um nó na árvore
No* sucessor(No* atual) {
    // Caso 1: Se o nó tem filho à direita, o sucessor é o mínimo da subárvore direita
    if (atual->direito != NULL){
        return minimo(atual->direito);
    }
    // Caso 2: Se o nó não tem filho à direita, subir na árvore usando o pai
    struct No* ancestral = atual->pai;
    while (ancestral != NULL && atual == ancestral->direito) {
        atual = ancestral; 
        ancestral = ancestral->pai; 
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
            atual = atual->esquerdo; 
        } else {
            atual = atual->direito; 
        }
    }
    return NULL; // Nó não encontrado
}

// Função que remove um nó sem filhos
void removerNoFolha(ABB* abb, No* no) {
    if (no == NULL) return;
    
    if (no->pai == NULL) { // Se for a raiz
        abb->raiz = NULL;
    } else if (no->pai->esquerdo == no) { // Se for filho à esquerda do pai
        no->pai->esquerdo = NULL;
    } else if (no->pai->direito == no) { // Se for filho à direita do pai
        no->pai->direito = NULL;
    }

    destruir_lista(no->lista_fichas);
    free(no);
}

// Função que remove um nó com um filho
void removerNoComUmFilho(ABB* abb, No* no) {
    if (no == NULL) return;

    No* filho = (no->esquerdo != NULL) ? no->esquerdo : no->direito;

    if (no->pai == NULL) {
        abb->raiz = filho;
    } else if (no->pai->esquerdo == no) {
        no->pai->esquerdo = filho;
    } else if (no->pai->direito == no) {
        no->pai->direito = filho;
    }
    if(filho != NULL){
        filho->pai = no->pai;
    }
    destruir_lista(no->lista_fichas);
    free(no);
}

// Função que remove nó com dois filhos
void removerNoComDoisFilhos(ABB* abb, No* no) {
    if (no == NULL) return;

    No* suc = sucessor(no);
    no->chave = suc->chave;

    if (suc->esquerdo == NULL && suc->direito == NULL){
        removerNoFolha(abb, suc);
    } else {
        removerNoComUmFilho(abb, suc);
    }
}

// Função que verifica qual o caso de remoção
void removerNo(ABB* abb, No* no) {
    if (no == NULL) return;

    if (no->esquerdo == NULL && no->direito == NULL) {
        removerNoFolha(abb, no);
    } else if (no->esquerdo == NULL || no->direito == NULL) {
        removerNoComUmFilho(abb, no);
    } else {
        removerNoComDoisFilhos(abb, no);
    }
}

// Função que realiza a busca na árvore e organiza as fichas do respectivo nó
void fluxo_fila_arvore(ABB *abb, Ficha *ficha) {
    if (abb == NULL || ficha == NULL) return;
    
    No *priori = buscar(abb->raiz, ficha->prioridade);

    if(priori == NULL){
        inserir_no_na_arvore(abb, ficha->prioridade); 
        priori = buscar(abb->raiz, ficha->prioridade);
        if (priori == NULL) {
            printf("Erro ao criar ou buscar nó de prioridade %d.\n", ficha->prioridade);
            return;
        }
    }

    if (priori->lista_fichas == NULL) {
        printf("Erro: lista de fichas não alocada para a prioridade %d.\n", ficha->prioridade);
        return;
    }

    if (inserir_ficha_lista(priori->lista_fichas, ficha) == NULL) {
        printf("Erro ao inserir ficha na lista da prioridade %d.\n", ficha->prioridade);
        return;
    }
}

// Função que destrói o nó da árvore de forma recursiva
void destruir_no(No *no) {
    if (no == NULL) return;
    destruir_no(no->esquerdo);
    destruir_no(no->direito);
    destruir_lista(no->lista_fichas);
    free(no);
}

// Função que destrói a árvore
void destruir_arvore(ABB *abb) {
    if (abb == NULL) return;
    destruir_no(abb->raiz);
    abb->raiz = NULL;
}