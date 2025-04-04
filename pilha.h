#ifndef PILHA_H
#define PILHA_H

#include "carta.h"


typedef struct noPilha {
    tcarta carta;
    struct noPilha *prox;
} tNoPilha;

typedef struct {
    tNoPilha *topo;
    tNoPilha *base;
} tPilha;

// Declarações de funções
tPilha *CriaPilha();
int PilhaVazia(tPilha *pilha);
void LiberaPilha(tPilha *pilha);
void InsereNoPilha(tPilha *pilha, tNoPilha *novoNo);
tNoPilha *RemoveNoPilha(tPilha *pilha);
tNoPilha *AcessaTopoPilha(tPilha *pilha);
int TamanhoPilha(tPilha *pilha);

#endif