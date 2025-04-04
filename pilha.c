#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

tPilha *CriaPilha(){
  tPilha *aux = malloc(sizeof(tPilha));
  aux->topo = NULL;
  aux->base = NULL;
  return aux;
}

int PilhaVazia(tPilha *pilha){
  if (pilha->topo == NULL && pilha->base == NULL){
    return 1;
  }else{
    return 0;
  }  
}

void LiberaPilha(tPilha *pilha){
  tNoPilha *aux;
  pilha->base = NULL;
  while (!PilhaVazia(pilha)) {
    aux = pilha->topo->prox;
    free(pilha->topo);
    pilha->topo = aux;
  }
  free(pilha);
}

void InsereNoPilha(tPilha *pilha, tNoPilha *novoNo){
  tNoPilha *aux = novoNo;
  if(PilhaVazia(pilha)){
    pilha->topo = aux;
    pilha->base = aux;
  }else{
    aux->prox = pilha->topo;
    pilha->topo = aux;
  }
}

tNoPilha *RemoveNoPilha(tPilha *pilha){
  tNoPilha *aux = pilha->topo;
  if (!PilhaVazia(pilha)){
    if(TamanhoPilha(pilha)==1){
      pilha->topo = pilha->topo->prox;
      pilha->base = NULL;
      aux->prox = NULL;
      return aux;
    }else{
      pilha->topo = pilha->topo->prox;
      aux->prox = NULL;
      return aux;
    }
  }
  return NULL;
}

tNoPilha *AcessaTopoPilha(tPilha *pilha){
  tNoPilha *aux = pilha->topo;
  return aux;
}

int TamanhoPilha(tPilha *pilha){
  int i=1;
  tNoPilha *auxtopo = pilha->topo, *auxbase = pilha->base;
  if(PilhaVazia(pilha)){
    return 0;
  }else{
    if(auxtopo == auxbase){
      return 1;
    }else{
      while(auxtopo != auxbase){
        auxtopo = auxtopo->prox;
        i++;
      }
      return i;
    }
  }
}