#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

// Função para criar um novo nó da árvore
NoArvore *criarArvore() {
    NoArvore *Arvore = (NoArvore *)malloc(sizeof(NoArvore));
    Arvore->esquerda = NULL;
    Arvore->direita = NULL;
    return Arvore;
}

// Função para inserir um nó na árvore
NoArvore *inserirNaArvore(NoArvore *raiz, tcarta carta) {
    if (raiz == NULL) {
        return criarArvore(carta);
    }

    // Inserção ordenada por valor da carta
    if (carta.valor < raiz->carta.valor) {
        raiz->esquerda = inserirNaArvore(raiz->esquerda, carta);
    } else {
        raiz->direita = inserirNaArvore(raiz->direita, carta);
    }

    return raiz;
}

// Função para calcular a pontuação total da árvore


// Função para liberar a memória da árvore
void liberarArvore(NoArvore *raiz) {
    if (raiz == NULL) {
        return;
    }
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

int profundidadeMinima(NoArvore* raiz) {
    // Se a árvore está vazia, a profundidade é 0
    if (raiz == NULL) return 0;

    // Se não tem filho esquerdo, retorna a profundidade do lado direito
    if (raiz->esquerda == NULL) return 1 + profundidadeMinima(raiz->direita);

    // Se não tem filho direito, retorna a profundidade do lado esquerdo
    if (raiz->direita == NULL) return 1 + profundidadeMinima(raiz->esquerda);

    // Se tem ambos os filhos, pega o mínimo entre os dois caminhos
    return 1 + (profundidadeMinima(raiz->esquerda) < profundidadeMinima(raiz->direita) 
                ? profundidadeMinima(raiz->esquerda) 
                : profundidadeMinima(raiz->direita));
}

 NoArvore *moverPilhaParaArvore(tPilha *pilha, NoArvore *arvore){

    while(!PilhaVazia(pilha)){
        arvore = inserirNaArvore(arvore, pilha->topo->carta);
        RemoveNoPilha(pilha);
    }
    return arvore;
}
