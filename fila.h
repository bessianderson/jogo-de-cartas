typedef struct nofila{
  int turno;
  int prazo;
  int paus;
  int espadas;
  int ouros;
  int copas;
  int premio;
  struct nofila *prox;
}NoFila;

typedef struct {
  NoFila *ini;
  NoFila *fim;
}tFila;


//funções fila
tFila *CriaFila(void);
int filaVazia(tFila *fila);
void liberaFila(tFila *fila);
NoFila *criaNoFila(NoFila dadosFila);
void insereFila(tFila *fila, NoFila dados);
NoFila *RemoveNoFila(tFila *fila);
NoFila *AcessaIniFila(tFila *fila);
int tamanhoFila(tFila *fila);
void ImprimeIniFila(tFila *fila);