#include <stdio.h>
#include <stdlib.h>
#include "listaprio2.h"

struct _listaprio {
  int max; /* tamanho maximo do heap */
  int pos; /* proxima posicao disponivel no vetor */ 
  int* prioridade; /* vetor das prioridades */
  int* identificador; /* identificador do no */
}; 

static void corrige_abaixo(int* prios, int* id, int atual, int tam);
static void corrige_acima(ListaP* heap, int pos);
static void troca(int a, int b, int* v);

ListaP* listap_cria(int max){
  ListaP* heap=(ListaP*)malloc(sizeof(struct _listaprio)); 
  heap->max=max;
  heap->pos=0;
  heap->prioridade=(int *)malloc(max*sizeof(int)); 
  heap->identificador=(int*)malloc(max*sizeof(int));
  return heap;
}

static void troca(int a, int b, int* v) {
  int f = v[a];
  v[a] = v[b];
  v[b] = f;
}

static void corrige_acima(ListaP* heap, int pos) {
  int pai;
  while (pos > 0){
    pai = (pos-1)/2;
    if (heap->prioridade[pai] > heap->prioridade[pos]){
      troca(pos,pai,heap->prioridade);
      troca(pos,pai,heap->identificador);
     }
    else 
      break;
    pos=pai;
  }
}

void listap_insere(ListaP* heap, int prioridade, int dado) {
  if ( heap->pos < heap->max ) {
    heap->prioridade[heap->pos]=prioridade;
    heap->identificador[heap->pos]=dado; 
    corrige_acima(heap,heap->pos); 
    heap->pos++;
    } 
    else {
      printf("Heap CHEIO!\n"); 
      exit(1);
    }
}

static void corrige_abaixo(int* prios, int* id, int atual, int tam){
  int pai=atual;
  int filho_esq, filho_dir, filho;
  while (2*pai+1 < tam){
    filho_esq=2*pai+1;
    filho_dir=2*pai+2;
    if (filho_dir >= tam) filho_dir=filho_esq;
    if (prios[filho_esq]<prios[filho_dir])
        filho=filho_esq;
    else
        filho=filho_dir;
    if (prios[pai]>prios[filho]){
            troca(pai,filho,prios);
            troca(pai,filho,id);
         }
    else
            break;
    pai=filho;
  }
}

int listap_remove(ListaP* heap) {
  if (heap->pos>0) {
    int topo = heap->identificador[0];
    heap->prioridade[0] = heap->prioridade[heap->pos-1];
    heap->identificador[0] = heap->identificador[heap->pos-1];
    heap->pos--;
    corrige_abaixo(heap->prioridade, heap->identificador, 0, heap->pos);
    return topo;
  }
  else {
     return -1;
  }
}

void listap_corrige (ListaP* heap, int novaprio, int dado) {

	for (int i = 0; i < heap->pos; i++) {
		if (heap->identificador[i] == dado) {
			heap->prioridade[i] = novaprio;
	      corrige_acima(heap, i);
			break;
		}
	}
}

void listap_libera (ListaP * h) {
  free(h->prioridade);
  free(h->identificador);
  free(h);
}

void debug_listap_show (ListaP *h, char* title){
	int i;
	printf("%s={",title);
	for (i=0; i<(h->pos); i++)
		printf("%d(%d),",h->prioridade[i],h->identificador[i]);
	printf("}\n");

}

