#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fila.h"
#define MAX 52


//cria fila
tFila *CriaFila(){
    tFila *f = (tFila*)malloc(sizeof(tFila));
    f->ini = f->fim = NULL;
    return f;
}

//verifica fila vazia
int filaVazia(tFila *fila) {
    return (fila->ini == NULL);
}

//libera fila 
void liberaFila(tFila *fila) {
    NoFila *aux;
    while (fila->ini != NULL) {
        aux = fila->ini;
        fila->ini = fila->ini->prox;
        free(aux);
    }
    free(fila);
}

//cria no na fila
NoFila *criaNoFila(NoFila dadosFila) {
    NoFila *novo = (NoFila*) malloc(sizeof(NoFila));
    if (novo) {
        novo->turno = dadosFila.turno;
        novo->prazo = dadosFila.prazo;
        novo->paus = dadosFila.paus;
        novo->espadas = dadosFila.espadas;
        novo->ouros = dadosFila.ouros;
        novo->copas = dadosFila.copas;
        novo->premio = dadosFila.premio;
        novo->prox = NULL;
    }
    return novo;
}

//insere no na fila
void insereFila(tFila *fila, NoFila dados) {
    NoFila *novo = criaNoFila(dados);
    if (novo == NULL) return; 

    if (filaVazia(fila)) {
        fila->ini = novo;
    } else {
        fila->fim->prox = novo;
    }
    fila->fim = novo;
}

//remove na fila
NoFila *RemoveNoFila(tFila *fila) {
    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return NULL;
    }
    NoFila *aux = fila->ini;
    fila->ini = fila->ini->prox;
    if (fila->ini == NULL) {
        fila->fim = NULL;
    }
    return aux;
}

//tamanho da fila
int tamanhoFila(tFila *fila) {
    int i = 0;
    NoFila *aux = fila->ini;
    while (aux != NULL) {
        aux = aux->prox;
        i++;
    }
    return i;
}

//acessa o inicio da fila
NoFila *AcessaIniFila(tFila *fila) {
    return fila->ini;
}

//imprime a fila
void ImprimeIniFila(tFila *fila) {
    if (!filaVazia(fila)) {
        printf("(P:%d, E:%d, O:%d, C:%d).\n", fila->ini->paus, fila->ini->espadas, fila->ini->ouros, fila->ini->copas);
    } else {
        printf("Fila vazia!\n");
    }
}
