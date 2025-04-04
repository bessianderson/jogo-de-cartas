#ifndef ARVORE_H
#define ARVORE_H

#include "carta.h"
#include "lista.h"
#include "pilha.h"

typedef struct noArvore {
    tcarta carta;
    struct noArvore *esquerda;
    struct noArvore *direita;
} NoArvore;

// Função para criar um novo nó da árvore
NoArvore *criarArvore();

// Função para inserir um nó na árvore
NoArvore *inserirNaArvore(NoArvore *raiz, tcarta carta);
NoArvore *inserirNaArvore2(NoArvore *raiz, tNoPilha carta);

// Função para liberar a memória da árvore
void liberarArvore(NoArvore *raiz);

NoArvore *moverPilhaParaArvore(tPilha *descarte, NoArvore *arvore);

int profundidadeMinima(NoArvore* raiz);
#endif