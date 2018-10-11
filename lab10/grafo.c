#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "grafo.h"
#include "listaprio2.h"

typedef struct _viz Viz;

struct _viz {
  int noj;
  float peso;
  Viz*  prox;
};

struct _grafo {
  int nv;           /* numero de nos ou vertices */
  int na;           /* numero de arestas */
  Viz** viz;         /* viz[i] aponta para a lista de arestas vizinhas do no i */
};

/* aux para fila */
typedef struct _sq SQ;
struct _sq {
  int info;
  SQ* prox;
};


static SQ* enqueue(SQ* queue, int info){
  SQ* novo = (SQ*)malloc(sizeof(SQ));
  SQ* aux = queue;
  assert(novo);
  novo->info = info;
  novo->prox = NULL;
  if (!queue){
    return novo;
  }
  while (aux->prox){
    aux = aux->prox;
  }
  aux->prox = novo;
  return queue;
}

static SQ* dequeue(SQ* queue,int* info){
  SQ* libera;
  if (!queue){
    *info = -1;
    return NULL;
  }
  *info = queue->info;
  libera = queue;
  queue = queue->prox;
  free(libera);
  return queue;
}



static Viz* criaViz(Viz* head, int noj, float peso) {

  Viz* no = (Viz*) malloc(sizeof(Viz));
  assert(no);
  no->noj = noj;
  no->peso = peso;
  no->prox = head;
  return no;
}

static Grafo* grafoCria(int nv, int na) {

  int i;
  Grafo* g = (Grafo *) malloc(sizeof(Grafo));
  g->nv = nv;
  g->na = na;
  g->viz = (Viz **) malloc(sizeof(Viz *) * nv);
  for (i = 0; i < nv; i++)
    g->viz[i] = NULL;
  return g;
}


Grafo* grafoLe( char* filename ) {


  FILE *arq = fopen(filename,"rt");
  int nv, na, no1, no2 = 0;
  float peso;
  Grafo* novo;
	
  fscanf(arq, "%d %d", &nv, &na);
  novo = grafoCria(nv, na);
  assert(novo);
  while (fscanf(arq, "%d %d %f", &no1, &no2, &peso) == 3) {
    novo->viz[no1] = criaViz(novo->viz[no1], no2, peso);
    novo->viz[no2] = criaViz(novo->viz[no2], no1, peso);
  }
  return novo;
}

Grafo*   grafoLibera(Grafo* grafo) {
  if (grafo) {
    int i = 0;
    Viz* no,*aux;
    for (i = 0; i < grafo->nv; i++){
      no = grafo->viz[i];
      while (no){
        aux = no->prox;
        free(no);
        no = aux;
      }
    }
    free(grafo->viz);
    free(grafo);
  }
  return NULL;
}

void grafoMostra (char* title, Grafo * grafo) {
  int i;
  if (title)
    printf("%s", title);
  if (grafo) {
    printf("NV: %d, NA: %d\n", grafo->nv, grafo->na);
    for (i = 0; i < grafo->nv; i++){
    Viz* viz = grafo->viz[i];
    printf("[%d]->", i);
    while (viz) {
      printf("{%d, %g}->", viz->noj, viz->peso);
      viz = viz->prox;
    }
    printf("NULL\n");
    }
  }
}

static void visita(Viz** vizinhos, int noinicial, char* visitados){
	printf("%d\n",noinicial);
	visitados[noinicial] = 1;
	Viz *aux = vizinhos[noinicial];
	while (aux != NULL){
		if (!visitados[aux->noj]) visita(vizinhos,aux->noj,visitados);
		aux = aux->prox;
	}
}

void grafoPercorreProfundidade (Grafo *grafo, int no_inicial) {
	int i;
	char* visitados = (char*) malloc(sizeof(char)*grafo->nv);
	for(i=0; i < grafo->nv; i++) visitados[i] = 0;
	visita(grafo->viz, no_inicial, visitados);

} 

Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial) {
  return grafo;
}

void grafoPercorreLargura (Grafo *grafo, int no_inicial) {

   int i, no;
   SQ *minhafila = NULL;
   Viz* aux;
   char* enfileirados = (char*) malloc (sizeof(char)*grafo->nv);
   for(i = 0 ; i < grafo->nv ; i++) enfileirados[i] = 0;
   enfileirados[no_inicial] = 1;
   minhafila = enqueue(minhafila, no_inicial);
   
   while (minhafila){
      minhafila = dequeue (minhafila, &no);
      printf("%d\n",no);
      
      aux = grafo->viz[no];
      while (aux){
         if (!enfileirados[aux->noj]){
            minhafila = enqueue(minhafila, aux->noj);
            enfileirados[aux->noj] = 1;
         }
         aux = aux->prox;
      }
   }
   
   free(enfileirados);
} 

int* menoresCaminhos (Grafo *grafo, int no_inicial){

	if (no_inicial >= grafo->nv || no_inicial < 0) return NULL;
	
	int i, peso, no = no_inicial;
	
	Viz *aux = grafo->viz[no_inicial];
	ListaP *prio = listap_cria(grafo->nv);
	
	char* marcados = (char*)malloc(sizeof(char)*grafo->nv);
	int* menores = (int*)malloc(sizeof(int)*grafo->nv);
	int* ultimomenor = (int*)malloc(sizeof(int)*(grafo->nv + 1));
	
	for (i=0 ; i<grafo->nv ; i++) { 
		marcados[i] = 0; 
		menores[i] = INT_MAX;  /*infinito*/
		listap_insere (prio, INT_MAX, i);
		ultimomenor[i] = -2; /* em caso de erro */
	}
	
	marcados[no_inicial] = 1;
	menores[no_inicial] = 0;
	ultimomenor[grafo->nv] = -1;
	ultimomenor[no_inicial] = no_inicial;
	
	for (i=0 ; i < grafo->nv  ; i++) {
		while (aux != NULL){
			if (!marcados[aux->noj]){
				peso = menores[no] + aux->peso;
				if (peso < menores[aux->noj]){
					menores[aux->noj] = peso;
					listap_corrige	(prio, peso, aux->noj);
					ultimomenor[aux->noj] = no; 
				}
			}
			aux = aux->prox;
		}
		
		marcados[no] = 1;
		no = listap_remove(prio);
		aux = grafo->viz[no];
	}
	
	free(menores);
	free(marcados);
	listap_libera(prio);
	
	return ultimomenor;
}

Grafo* arvoreCustoMinimo (Grafo *grafo){
	return grafo;
}








