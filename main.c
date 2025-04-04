#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pilha.h"
#include "lista.h"
#include "fila.h"
#include "arvore.h"
#define MAX 52


int main() {
    int escolha;
    int cartas = 0;
    int opcao;
    int atual = 0;
    int tamanhoMao = 0;
    int turnoAtual = 1; 
    int recursosPaus = 0; 
    int recursosEspadas = 0;
    int recursosOuros = 0;
    int recursosCopas = 0;
    int reembaralhamentos = 0; 
    int ProfMinima=1;
    int PontFinal=0;
    int antecedencia=0;
    int prazoRestante=0;
    int somaRecursosTarefa=0;
    int somaRecursosTarefaIncompleta=0;
    tcarta baralho[MAX];
    FILE *arquivo = fopen("baralho1.dat", "r");
    Nodo *lista = CriaLista();
    Nodo *mao = CriaLista();
    Nodo *descartetemp = CriaLista();
    tFila *ftarefas = CriaFila();
    tPilha *monte = CriaPilha(), *descarte = CriaPilha();
    NoArvore *DescArvore;
    DescArvore=criarArvore();
    //sorteio
    
    //Lê o baralho
    if(arquivo == NULL){
        printf("Erro ao ler o arquivo do baralho.\n");
        return 0;
    }
    for(int j=0; j<52; j++){
      fscanf(arquivo, "%s %s %d %[^\n]",
                  baralho[cartas].face,
                  baralho[cartas].naipe,
                  &baralho[cartas].valor,
                  baralho[cartas].nome);  
                  cartas++;
    }

    fclose(arquivo);

    // Lê as tarefas do arquivo e insere na fila
    FILE *arquivoTarefas = fopen("tarefas.dat", "r");
    if(arquivoTarefas == NULL) {
        printf("Erro ao abrir o arquivo de tarefas.\n");
        return 0;
    }

    NoFila no_solto;
    while(fscanf(arquivoTarefas, "%d %d %d %d %d %d %d",
                  &no_solto.turno, &no_solto.prazo, &no_solto.paus, &no_solto.espadas,
                  &no_solto.ouros, &no_solto.copas, &no_solto.premio) == 7) {
        no_solto.prox = NULL;
        insereFila(ftarefas, no_solto); // Insere a tarefa na fila
    }
    fclose(arquivoTarefas);

    // Embaralha o baralho
    Embaralhar(baralho, cartas);
    
    for (int i = 0; i < cartas; i++) {
    tNoPilha *novoNo = (tNoPilha*)malloc(sizeof(tNoPilha));
    novoNo->carta = baralho[i];
    novoNo->prox = NULL;
    InsereNoPilha(monte, novoNo);
}
    // Início do programa
    printf("Criando mão automaticamente...\n");

    // Inicializa a mão do jogador
        for (int i = 0; i < 5; i++) {
            Sorteio(monte, &mao, &tamanhoMao);
     }
    

    // Menu
    while (1){
        //Exibe o cabeçalho do jogo
        printf("\nP: %d - E: %d - O: %d - C: %d - *: %d\n", recursosPaus, recursosEspadas, recursosOuros, recursosCopas, reembaralhamentos);

        //Exibe as tarefas pendentes
        printf("Tarefas: ");
        NoFila *atualFila = ftarefas->ini;
        while(atualFila != NULL) {
            int prazoRestante = atualFila->prazo - (turnoAtual - atualFila->turno);
            if(prazoRestante > 0 && turnoAtual >= atualFila->turno) {
                printf("%d (P:%d, E:%d, O:%d, C:%d); ", prazoRestante,
                       atualFila->paus, atualFila->espadas, atualFila->ouros, atualFila->copas);
            }
            atualFila = atualFila->prox;
        }
        printf("\n");

 // Exibe a mão do jogador
printf("\nMão do Jogador:\n");
printf("+-----+-----+-----+-----+-----+\n");
printf("|   1 |   2 |   3 |   4 |   5 |\n");
printf("+-----+-----+-----+-----+-----+\n");
printf("| ");

Nodo *temp = mao;
while (temp != NULL) {
    // Exibe a carta formatada
    printf("%s-%c | ", temp->carta.face, temp->carta.naipe[0]);
    temp = temp->prox;
}

// Preenche com espaços se houver menos de 5 cartas na mão
for (int i = tamanhoMao; i < 5; i++) {
    printf("| ");
}

printf("\n+-----+-----+-----+-----+-----+\n");

// Exibe o tamanho do monte e do descarte
printf("\nInformações do Jogo:\n");
printf("+-------------------+-------------------+\n");
printf("| Monte: %-9d | Descarte:%-9d |\n", TamanhoPilha(monte), TamanhoPilha(descarte));
printf("+-------------------+-------------------+\n");


        // Exibe o menu
        printf("\nMenu:\n");
        printf("1 - Reposicionar carta\n");
        printf("2 - Descartar cartas\n");
        printf("3 - Cumprir tarefa\n");
        printf("4 - Reembaralhar tudo (*:%d)\n", reembaralhamentos);
        printf("5 - Finalizar turno\n");
        printf("6 - Encerrar jogo\n");
        printf("Digite opcao desejada: ");
        scanf("%d", &opcao);

        if(opcao == 1){
            if (tamanhoMao > 1) {
                reposicionarCarta(&mao, tamanhoMao);
            } else {
                printf("\nVocê precisa de pelo menos 2 cartas para reposicionar.\n");
            }
        }else if (opcao == 2) {
    if (tamanhoMao > 0) {
        descartarCartas(&mao, &tamanhoMao, &recursosPaus, &recursosEspadas, &recursosOuros, &recursosCopas, descarte);
    } else {
        printf("\nVocê não tem cartas para descartar.\n");
    }

        }else if(opcao == 3) {
            // Cumprir tarefa
            if(ftarefas == NULL || ftarefas->ini == NULL) {
                printf("Nenhuma tarefa disponível.\n");
            }else{
                // Encontrar a primeira tarefa pendente (prazo válido e turno correto)
                NoFila *atualFila = ftarefas->ini;
                NoFila *tarefa = NULL;

                while (atualFila != NULL) {
                    prazoRestante = atualFila->prazo - (turnoAtual - atualFila->turno);
                    if (prazoRestante > 0 && turnoAtual >= atualFila->turno) {
                        tarefa = atualFila;
                        break;
                    }
                    atualFila = atualFila->prox;
                }

                if(tarefa == NULL){
                    printf("Nenhuma tarefa disponível para cumprir.\n");
                }else{
                    // Verificar se o jogador possui os recursos necessários
                    if(recursosPaus >= tarefa->paus && recursosEspadas >= tarefa->espadas &&
                        recursosOuros >= tarefa->ouros && recursosCopas >= tarefa->copas){
                        // Deduzir os recursos
                        somaRecursosTarefa+=tarefa->paus+tarefa->ouros+tarefa->espadas+tarefa->copas;
                        recursosPaus -= tarefa->paus;
                        recursosEspadas -= tarefa->espadas;
                        recursosOuros -= tarefa->ouros;
                        recursosCopas -= tarefa->copas;

                        printf("Tarefa cumprida com sucesso! Premio: %d\n", tarefa->premio);
                        reembaralhamentos+=tarefa->premio;
                        antecedencia+=prazoRestante;

                        // Remove a tarefa da fila
                        if(ftarefas->ini == tarefa) {
                            ftarefas->ini = tarefa->prox; // Remove a primeira tarefa
                        }else{
                            NoFila *anterior = ftarefas->ini;
                            while (anterior->prox != tarefa) {
                                anterior = anterior->prox;
                            }
                            anterior->prox = tarefa->prox; // Remove uma tarefa no meio ou no fim
                        }
                        free(tarefa); // Libera a memória da tarefa concluída
                    }else{
                        printf("Recursos insuficientes para cumprir a tarefa.\n");
                    }
                }
            }
        }else if(opcao == 4) {
            // Reembaralhar tudo
            if(reembaralhamentos > 0) {
                reembaralhamentos--;
                moverMonteParaDescarte(monte, descarte);
                while(tamanhoMao>0){
                descartarCartasSerio(&mao, &tamanhoMao, &recursosPaus, &recursosEspadas, &recursosOuros, &recursosCopas, descarte);
                }
                reembaralharDescarte(monte, descarte);
                for (int i = 0; i < 5; i++) {
            Sorteio(monte, &mao, &tamanhoMao);
            }
            }else{
                printf("Você não tem reembaralhamentos disponíveis.\n");
            }
        }else if(opcao == 5) {
            // Finalizar turno
            turnoAtual++; 
            // Incrementa o turno atual
            printf("Turno %d iniciado.\n", turnoAtual);
            

            // Comprar cartas até completar 5 na mão
            while(tamanhoMao < 5 && (!PilhaVazia(monte))) {
                Sorteio(monte, &mao, &tamanhoMao);
            }
            if(PilhaVazia(monte)){
                moverDescarteParaMonte(descarte,monte);
            }

            // Verificar se alguma tarefa expirou
            if(ftarefas != NULL && ftarefas->ini != NULL) {
                NoFila *atualFila = ftarefas->ini;
                NoFila *anterior = NULL;

                while(atualFila != NULL){
                    int prazoRestante = atualFila->prazo - (turnoAtual - atualFila->turno);

                    // Tarefa expirada
                    if (prazoRestante <= 0) {
                        printf("Tarefa expirou! Paus=%d, Espadas=%d, Ouros=%d, Copas=%d\n",
                            atualFila->paus, atualFila->espadas, atualFila->ouros, atualFila->copas);
                            somaRecursosTarefaIncompleta=atualFila->paus+atualFila->espadas+atualFila->ouros+atualFila->copas;

                        // Remove a tarefa da fila
                        if(anterior == NULL) {
                            ftarefas->ini = atualFila->prox; // Remove a primeira tarefa
                        }else{
                            anterior->prox = atualFila->prox; // Remove uma tarefa no meio ou no fim
                        }

                        NoFila *temp = atualFila;
                        atualFila = atualFila->prox;
                        free(temp); // Libera a memória da tarefa removida
                    }else{
                        anterior = atualFila;
                        atualFila = atualFila->prox;
                    }
                }
            }
        }
            
            else if(opcao == 6){
                DescArvore = moverPilhaParaArvore(descarte, DescArvore);
                
                ProfMinima = profundidadeMinima(DescArvore);
                
                int somaRecursos=0;
                
                somaRecursos=recursosPaus+recursosEspadas+recursosOuros+recursosCopas;
            
                
                PontFinal = ProfMinima * ((antecedencia) * (somaRecursosTarefa) + (somaRecursos/2) ) - (somaRecursosTarefaIncompleta);  
                printf("\n\nJogo encerrado! A Pontuacao final é: %d\n", PontFinal);
            }

          
        else if(opcao == 0) {
            printf("\nSaindo do programa...\n");
            break; // Sai do loop e encerra o programa
        }else{
            printf("\nOpção inválida. Tente novamente...\n");
        }
    }

    // Exibe a mão final do jogador
    printf("\nMão final do jogador:\n");
    exibirMao(mao);

    // Libera a memória da mão
    liberarMao(&mao);

    // Libera a memória da fila de tarefas
    liberaFila(ftarefas);

    return 0;
}

