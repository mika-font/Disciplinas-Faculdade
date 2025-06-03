#include <stdio.h>
#include <stdlib.h>

// Definição do nó da árvore
typedef struct No {
    int chave;
    struct No* esquerdo;
    struct No* direito;
    struct No* pai;
} No;

// Definição da árvore
typedef struct {
    No* raiz;
} ABB;

// Função para criar um novo nó
No* criarNo(int chave) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->chave = chave;
    novoNo->esquerdo = novoNo->direito = novoNo->pai = NULL;
    return novoNo;
}

// Função para inicializar uma árvore ABB
ABB* criarABB() {
    ABB* abb = (ABB*)malloc(sizeof(ABB));
    abb->raiz = NULL;
    return abb;
}

// Função para inserir um nó na árvore
void inserir(ABB* abb, int chave) {
    if(abb->raiz == NULL){
        abb->raiz = criarNo(chave);
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

    No* novoNo = criarNo(chave);
    novoNo->pai = pai; // Definir o pai do novo nó
    if(chave < pai->chave) {
        pai->esquerdo = novoNo; // Inserir como filho esquerdo
    } else {
        pai->direito = novoNo; // Inserir como filho direito
    }
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

// Função para encontrar o nó mínimo (mais à esquerda) na BST
No* minimo(No* node) {
    No* atual = node;
    while (atual && atual->esquerdo != NULL) {
        atual = atual->esquerdo; // Descer para o filho esquerdo
    }
    return atual; // Retorna o nó mínimo encontrado
}

// Função para encontrar o nó máximo (mais à direita) na BST
No* maximo(No* node) {
    No* atual = node;
    while (atual && atual->direito != NULL) {
        atual = atual->direito; // Descer para o filho direito
    }
    return atual; // Retorna o nó máximo encontrado
}

// Função para encontrar o sucessor de um nó na BST
No* sucessor(No* atual) {
    // Caso 1: Se o nó tem um filho à direita,
    // o sucessor é o menor nó na subárvore direita
    if (atual->direito != NULL)
        return minimo(atual->direito);

    // Caso 2: Se o nó não tem filho à direita, subir na árvore usando o pai
    struct No* ancestral = atual->pai;
    // Enquanto o atual for igual ao filho da direita do pai,
    // significa que ele é o filho da direita
    while (ancestral != NULL && atual == ancestral->direito) {
        atual = ancestral; // subindo na árvore
        ancestral = ancestral->pai; // subindo na árvore
    }

    return ancestral;
}

// Função para encontrar o predecessor de um nó
No* predecessor(No* atual) {
    // Caso 1: Se o nó tem um filho à esquerda,
    // o predecessor é o maior nó na subárvore esquerda
    if (atual->esquerdo != NULL)
        return maximo(atual->esquerdo);

    // Caso 2: Se o nó não tem filho à esquerda, subir na árvore usando o pai
    struct No* ancestral = atual->pai;
    // Enquanto o atual for igual ao filho da esquerda do pai,
    // significa que ele é o filho da esquerda
    while (ancestral != NULL && atual == ancestral->esquerdo) {
        atual = ancestral; // subindo na árvore
        ancestral = ancestral->pai; // subindo na árvore
    }

    return ancestral;
}

// Função para remover um nó da árvore binária de busca (ABB)
void removerNo(ABB* abb, No* no) {
    No* noParaRemover;  // Variável para o nó que será removido
    No* filhoDoNoParaRemover;  // Variável para o filho do nó que será removido

    // Se o nó a ser removido tem no máximo um filho
    if (no->esquerdo == NULL || no->direito == NULL)
        noParaRemover = no;
    else
        noParaRemover = sucessor(no);  // Caso contrário, encontre o sucessor do nó

    // Atribua o filho do nó que será removido (pode ser NULL)
    if (noParaRemover->esquerdo != NULL)
        filhoDoNoParaRemover = noParaRemover->esquerdo;
    else
        filhoDoNoParaRemover = noParaRemover->direito;

    // Se o filho do nó a ser removido não for nulo, atualize seu pai
    if (filhoDoNoParaRemover != NULL)
        filhoDoNoParaRemover->pai = noParaRemover->pai;

    // Atualize o ponteiro do pai do nó a ser removido
    if (noParaRemover->pai == NULL)
        abb->raiz = filhoDoNoParaRemover;  // Caso o nó a ser removido seja a raiz
    else if (noParaRemover == noParaRemover->pai->esquerdo)
        noParaRemover->pai->esquerdo = filhoDoNoParaRemover;
    else
        noParaRemover->pai->direito = filhoDoNoParaRemover;

    // Se o nó a ser removido não for o mesmo nó passado como parâmetro, copie a chave
    // Só ocorre quando a remoção é um filho com 2 nós e, nesse código, pegamos o sucessor.
    // Nesse caso é feita a cópia do valor para o nó "removido", o nó removido de fato (free) é o sucessor,
    // visto que copiamos seu valor para simplificar as operações.
    if (noParaRemover != no)
        no->chave = noParaRemover->chave;

    // Libere a memória do nó que foi removido
    free(noParaRemover);
}

// Função para percorrer a árvore em-ordem
void emOrdem(No* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esquerdo);
        printf("%d ", raiz->chave);
        emOrdem(raiz->direito);
    }
}

// Função para percorrer a árvore pré-ordem
void preOrdem(No* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->chave);
        preOrdem(raiz->esquerdo);
        preOrdem(raiz->direito);
    }
}

// Função para percorrer a árvore pós-ordem
void posOrdem(No* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerdo);
        posOrdem(raiz->direito);
        printf("%d ", raiz->chave);
    }
}

// Função principal para teste
int main() {
    ABB* abb = criarABB();

    inserir(abb, 50);
    inserir(abb, 30);
    inserir(abb, 20);
    inserir(abb, 40);
    inserir(abb, 70);
    inserir(abb, 60);
    inserir(abb, 80);

    printf("Percurso em ordem: ");
    emOrdem(abb->raiz);
    printf("\n");

    printf("Percurso pre-ordem: ");
    preOrdem(abb->raiz);
    printf("\n");

    printf("Percurso pos-ordem: ");
    posOrdem(abb->raiz);
    printf("\n");

    No* no = buscar(abb->raiz, 40);
    if (no != NULL)
        printf("Nó encontrado com chave %d\n", no->chave);
    else
        printf("Nó não encontrado\n");

    No* noMinimo = minimo(abb->raiz);
    if (noMinimo != NULL)
        printf("Chave do nó mínimo: %d\n", noMinimo->chave);

    No* noMaximo = maximo(abb->raiz);
    if (noMaximo != NULL)
        printf("Chave do nó máximo: %d\n", noMaximo->chave);

    No* noSucessor = sucessor(no);
    if (noSucessor != NULL)
        printf("Sucessor do nó com chave %d é %d\n", no->chave, noSucessor->chave);

    No* noPredecessor = predecessor(no);
    if (noPredecessor != NULL)
        printf("Predecessor do nó com chave %d é %d\n", no->chave, noPredecessor->chave);

    removerNo(abb, no);
    printf("Percurso em ordem após remoção: ");
    emOrdem(abb->raiz);
    printf("\n");

    return 0;
}
