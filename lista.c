#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lista.h"
#include "pilha.h"
#define MAX 52

//Função que cria lista.
Nodo *CriaLista(){
    Nodo *lista=NULL;
    return lista;
    };

//Função do tipo void que imprime o resultado do sorteio e o número de cartas restantes.
void Sorteio(tPilha *monte, Nodo **mao, int *tamanhoMao) {
    if (!PilhaVazia(monte)) {
        tNoPilha *cartaNo = RemoveNoPilha(monte);
        tcarta carta = cartaNo->carta;
        free(cartaNo);

        printf("\nCarta sorteada:\n");
        exibirCarta(carta);

        // Adiciona a carta sorteada à mão
        inserirNaMao(mao, carta);
        (*tamanhoMao)++;
        printf("Cartas na mão: %d\n", *tamanhoMao);
    } else {
        printf("\n\nAs cartas acabaram!\n");
    }
}

//Função do tipo void que embaralha as cartas.
void Embaralhar(tcarta baralho[], int cartas){
  srand(time(NULL));

  for (int i = cartas - 1; i > 0; i--) {       
      int j = rand() % (i + 1);
      tcarta temp = baralho[i];
      baralho[i] = baralho[j];
      baralho[j] = temp;
  }
}

void EmbaralharPilha(tPilha *pilha) {
    // Converte a pilha em um array de cartas, embaralha e reconstrói a pilha
    int tamanho = TamanhoPilha(pilha);
    tcarta *cartas = (tcarta *)malloc(tamanho * sizeof(tcarta));
    
    // Remove as cartas da pilha e coloca no array
    for (int i = 0; i < tamanho; i++) {
        tNoPilha *no = RemoveNoPilha(pilha);
        cartas[i] = no->carta;
        free(no);
    }
    
    // Embaralha o array de cartas
    Embaralhar(cartas, tamanho);
    
    // Reconstrói a pilha com as cartas embaralhadas
    for (int i = 0; i < tamanho; i++) {
        tNoPilha *novoNo = (tNoPilha *)malloc(sizeof(tNoPilha));
        novoNo->carta = cartas[i];
        novoNo->prox = NULL;
        InsereNoPilha(pilha, novoNo);
    }
    
    free(cartas);
}

void moverDescarteParaMonte(tPilha *descarte, tPilha *monte) {
    while (!PilhaVazia(descarte)){
        // Remove a carta do topo do descarte
        tNoPilha *cartaNo = RemoveNoPilha(descarte);
        
        // Insere a carta no topo do monte
        InsereNoPilha(monte, cartaNo);
    }
}

void moverMonteParaDescarte(tPilha *monte, tPilha *descarte){
 while(!PilhaVazia(monte)){
        tNoPilha *cartaNo = RemoveNoPilha(monte);
        
        InsereNoPilha(descarte, cartaNo);
 }   
}

void reembaralharDescarte(tPilha *monte, tPilha *descarte) {
    // Move todas as cartas do descarte para o monte
    moverDescarteParaMonte(descarte, monte);

    // Embaralha as cartas no monte
    EmbaralharPilha(monte);
}

//Função do tipo void que exibe a carta.
void exibirCarta(tcarta carta) {
    printf("\n");
    printf("  +--------------------------+\n");
    printf("  | Face: %-17s  |\n", carta.face);  
    printf("  | Naipe: %-16s  |\n", carta.naipe); 
    printf("  | Valor: %-16d  |\n", carta.valor); 
    printf("  | Nome: %-17s  |\n", carta.nome); 
    printf("  +--------------------------+\n");
}

//---------------------funções de lista---------------------
//Função tipo Nodo que cria um novo nó da lista.
Nodo *criarNodo(tcarta carta) {
    Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
    if(novo == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }
    novo->carta = carta;
    novo->prox = NULL;
    return novo;
}

//Função tipo void que insere a carta na mão.
void inserirNaMao(Nodo **mao, tcarta carta) {
    Nodo *novo = criarNodo(carta);
    if(*mao == NULL) {
        *mao = novo;  
    }else{
        Nodo *temp = *mao;
        while (temp->prox != NULL) {
            temp = temp->prox; 
        }
        temp->prox = novo; 
    }
}

//Função tipo void que exibe a mão do jogador.
void exibirMao(Nodo *mao) {
    Nodo *temp = mao;
    while (temp != NULL) {
        printf("Carta: %d de %s\n", temp->carta.valor, temp->carta.naipe);
        temp = temp->prox;  
    }
}

//Função tipo void que libera a memória da mão.
void liberarMao(Nodo **mao) {
    Nodo *temp;
    while (*mao != NULL) {
        temp = *mao;
        *mao = (*mao)->prox;  
        free(temp);           
    }
}

//Função de tipo void que reposiciona a carta na mão.
void reposicionarCarta(Nodo **mao, int tamanhoMao) {
    int origem, destino;

   
    printf("\nDigite a posição da carta a ser movida (1 a %d): ", tamanhoMao);
    scanf("%d", &origem);
    printf("Digite a posição para onde deseja mover a carta (1 a %d): ", tamanhoMao);
    scanf("%d", &destino);

    // Valida as posições
    if(origem < 1 || origem > tamanhoMao || destino < 1 || destino > tamanhoMao || origem == destino) {
        printf("\nPosições inválidas ou iguais. Escolha entre 1 e %d.\n", tamanhoMao);
        return;
    }

    // Remove a carta da posição de origem
    Nodo *anterior = NULL;
    Nodo *atual = *mao;

    for(int i = 1; i < origem; i++) {
        anterior = atual;
        atual = atual->prox;
    }

    // Desconecta o nó da posição de origem
    if(anterior == NULL) {
        *mao = atual->prox; 
    }else{
        anterior->prox = atual->prox;
    }

    // Recoloca a carta na posição de destino
    if(destino == 1) {
        atual->prox = *mao;
        *mao = atual;
    }else{
        Nodo *temp = *mao;
        for (int i = 1; i < destino - 1; i++) {
            temp = temp->prox;
        }
        atual->prox = temp->prox;
        temp->prox = atual;
    }

    printf("\nCarta reposicionada com sucesso!\n");
}


//Função do tipo void que descarta as cartas da mão.
void descartarCartas(Nodo **mao, int *tamanhoMao, int *recursosPaus, int *recursosEspadas, int *recursosOuros, int *recursosCopas, tPilha *descarte) {
    int N;

    printf("Quantas cartas deseja remover (1-5)? ");
    scanf("%d", &N);

    if (N < 1 || N > 5 || N > *tamanhoMao) {
        printf("Quantidade inválida. Tente novamente.\n");
        return;
    }

    for (int i = 0; i < N; i++) {
        int posicao;
        printf("\nMão Atual:\n");
        exibirMao(*mao);
        printf("Digite a posição da carta a descartar (1 a %d): ", *tamanhoMao);
        scanf("%d", &posicao);

        if (posicao < 1 || posicao > *tamanhoMao) {
            printf("\nPosição inválida. Tente novamente.\n");
            i--;
        } else {
            // Remove a carta e obtém seus dados
            tcarta cartaRemovida = removerCarta(mao, posicao);
            (*tamanhoMao)--;
            printf("\nCarta descartada com sucesso!\n");

            // Adiciona a carta descartada à pilha de descarte
            tNoPilha *novoNo = (tNoPilha*)malloc(sizeof(tNoPilha));
            novoNo->carta = cartaRemovida;
            novoNo->prox = NULL;
            InsereNoPilha(descarte, novoNo);

            // Converte a carta descartada em recursos
            char naipe = cartaRemovida.naipe[0]; // Pega o primeiro caractere do naipe
            int valor = cartaRemovida.valor;

            switch (naipe) {
                case 'P': // Paus
                    *recursosPaus += valor;
                    break;
                case 'E': // Espadas
                    *recursosEspadas += valor;
                    break;
                case 'O': // Ouros
                    *recursosOuros += valor;
                    break;
                case 'C': // Copas
                    *recursosCopas += valor;
                    break;
                default:
                    printf("Naipe inválido.\n");
                    break;
            }

            printf("Recursos atualizados: Paus=%d, Espadas=%d, Ouros=%d, Copas=%d\n",
                   *recursosPaus, *recursosEspadas, *recursosOuros, *recursosCopas);
        }
    }

    // Calcula o bônus com a mão restante
    int bonus = calcularBonus(*mao);
    printf("\nBônus alcançado com a mão restante: %d pontos\n", bonus);
}

void descartarCartasSerio(Nodo **mao, int *tamanhoMao, int *recursosPaus, int *recursosEspadas, int *recursosOuros, int *recursosCopas, tPilha *descarte){

            tcarta cartaRemovida = removerCartaSerio(mao);
            (*tamanhoMao)--;

            // Adiciona a carta descartada à pilha de descarte
            tNoPilha *novoNo = (tNoPilha*)malloc(sizeof(tNoPilha));
            novoNo->carta = cartaRemovida;
            novoNo->prox = NULL;
            InsereNoPilha(descarte, novoNo);
        }
      

//Função do tipo void que remove a carta da mão.
tcarta removerCarta(Nodo **mao, int posicao) {
    Nodo *temp = *mao;
    Nodo *anterior = NULL;
    tcarta cartaRemovida;

    // Encontra a carta na posição especificada
    for (int i = 1; i < posicao; i++) {
        anterior = temp;
        temp = temp->prox;
    }

    // Remove a carta da lista
    if (anterior == NULL) {
        *mao = temp->prox; // Remove a primeira carta
    } else {
        anterior->prox = temp->prox; // Remove uma carta no meio ou no fim
    }

    // Copia os dados da carta antes de liberar a memória
    cartaRemovida = temp->carta;
    free(temp); // Libera a memória do nó removido

    return cartaRemovida;
}

tcarta removerCartaSerio(Nodo **mao) {
    Nodo *temp = *mao;
    Nodo *anterior = NULL;
    tcarta cartaRemovida;

    // Remove a carta da lista
    if (anterior == NULL) {
        *mao = temp->prox; // Remove a primeira carta
    } else {
        anterior->prox = temp->prox; // Remove uma carta no meio ou no fim
    }

    // Copia os dados da carta antes de liberar a memória
    cartaRemovida = temp->carta;
    free(temp); // Libera a memória do nó removido

    return cartaRemovida;
}

//Função do tipo inteiro que calcula o bônus com a mão restante.
int calcularBonus(Nodo *mao) {
    int valores[14] = {0};
    int naipes[4] = {0};
    int tamanho = 0;

    // Conta valores e naipes
    Nodo *atual = mao;
    while (atual != NULL) {
        valores[atual->carta.valor]++;
        if (strcmp(atual->carta.naipe, "P") == 0) naipes[0]++;
        else if (strcmp(atual->carta.naipe, "C") == 0) naipes[1]++;
        else if (strcmp(atual->carta.naipe, "E") == 0) naipes[2]++;
        else if (strcmp(atual->carta.naipe, "O") == 0) naipes[3]++;
        tamanho++;
        atual = atual->prox;
    }

    int bonus = 0;
    
    // Verificar os bônus
    for(int i = 1; i <= 13; i++) {
        if (valores[i] == 2) bonus += 2;         
        else if (valores[i] == 3) bonus += 5;    
        else if (valores[i] == 4) bonus += 20;   
    }

    // Verificar sequência
    int sequencia = 0;
    for(int i = 1; i <= 13; i++) {
        if(valores[i] > 0) {
            sequencia++;
        }else{
            if (sequencia > 1) bonus += 2 * sequencia;
            sequencia = 0;
        }
    }
    if(sequencia > 1) bonus += 2 * sequencia; 

    // Verificar mesmo naipe
    for(int i = 0; i < 4; i++) {
        if(naipes[i] == tamanho) { 
            bonus += 3 * tamanho;
        }
    }

    return bonus;
}