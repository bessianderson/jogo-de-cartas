#ifndef BARALHO
#define BARALHO

#include "carta.h"  
#include "pilha.h"  

typedef struct nodo {
    tcarta carta;
    struct nodo *prox;
} Nodo;

// Declarações de funções
void Sorteio(tPilha *monte, Nodo **mao, int *tamanhoMao);
void Embaralhar(tcarta baralho[], int cartas);
void exibirCarta(tcarta carta);
Nodo *CriaLista();
Nodo *criarNodo(tcarta carta);
void inserirNaMao(Nodo **mao, tcarta carta);
void exibirMao(Nodo *mao);
void liberarMao(Nodo **mao);
void reposicionarCarta(Nodo **mao, int tamanhoMao);
void descartarCartas(Nodo **mao, int *tamanhoMao, int *recursosPaus, int *recursosEspadas, int *recursosOuros, int *recursosCopas, tPilha *descarte);
void descartarCartasSerio(Nodo **mao, int *tamanhoMao, int *recursosPaus, int *recursosEspadas, int *recursosOuros, int *recursosCopas, tPilha *descarte);
tcarta removerCarta(Nodo **mao, int posicao);
tcarta removerCartaSerio(Nodo **mao);
int calcularBonus(Nodo *mao);
void reembaralharDescarte(tPilha *monte, tPilha *descarte);
void moverDescarteParaMonte(tPilha *descarte, tPilha *monte);
void moverMonteParaDescarte(tPilha *monte, tPilha *descarte);

#endif