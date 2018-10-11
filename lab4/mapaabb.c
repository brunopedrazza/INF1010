#include <stdlib.h>
#include <stdio.h>

#include "mapa.h"

struct smapa {
  int chave;
  int dados;
  Mapa* esq;
  Mapa* dir;
};

static int auxe_abb (Mapa *m,int *maiorvisto);
static int altura (Mapa *m);
static int auxchavek (Mapa *m, int k, int *qnts);

Mapa* cria (void) {
  return NULL;
}

static Mapa *cria_no (int c, int d) {
  Mapa *nn = (Mapa *)malloc(sizeof(Mapa));
  if (nn!=NULL) {
    nn->esq = nn->dir = NULL;
    nn->chave =c;
    nn->dados = d;
  }
  return nn;
}

Mapa *insere (Mapa *m, int chave, int d) {
  if (m==NULL) 
    return cria_no(chave, d);
  else if (chave < m->chave) 
    m->esq = insere(m->esq,chave,d);
  else  /* if (chave > m->chave) */ {
    m->dir = insere(m->dir,chave,d);
  }
  return m;
}

int busca (Mapa *m, int chave) {
  while (m!=NULL) {
    if (chave < m->chave)
      m = m->esq;
    else if (chave > m->chave)
      m = m->dir;
    else
      return m->dados;
  }
  return -1;
}  


void debug_mostra_mapa_int (Mapa* m) {

  printf("[");
  if (m != NULL) {
    printf("%d ", m->chave);
    debug_mostra_mapa_int(m->esq);
    debug_mostra_mapa_int(m->dir);
  }
  printf("]");
}

void debug_mostra_mapa (Mapa* m) {
  debug_mostra_mapa_int (m); printf ("\n");
}

void destroi (Mapa *m) {
  if (m==NULL) return;
  destroi (m->esq);
  destroi (m->dir);
  free(m);
}

int iguais (Mapa *m1, Mapa *m2){
  if (m1 == NULL && m2 == NULL)
    return 1;
	if (m1 == NULL || m2 == NULL)
		return 0;
  return ((m1->chave == m2->chave) && (iguais(m1->esq,m2->esq)) && (iguais(m1->dir,m2->dir)));
}

int e_abb (Mapa *m) {
	int maiorvisto = -1;
	return (auxe_abb(m,&maiorvisto));
}

static int auxe_abb (Mapa *m,int *maiorvisto) {
	if (m == NULL)
		return 1;
	if (!auxe_abb(m->esq,maiorvisto)) return 0;
	if (m->chave > (*maiorvisto)){
		(*maiorvisto) = m->chave;
		return auxe_abb(m->dir,maiorvisto);
	}
	else return 0;
}

Mapa* debug_troca_chave (Mapa *m, int original, int novachave){
  if (m == NULL)
    return m;
  if (original < m->chave)
    m->esq = debug_troca_chave(m->esq,original,novachave);
  else if (original > m->chave)
    m->dir = debug_troca_chave(m->dir,original,novachave);
  else
    m->chave = novachave;
  return m;
}

int e_avl (Mapa *m) {
	if (!e_abb(m)) return 0;
	if (m == NULL) return 1;
	if ((altura(m->esq) - altura(m->dir) > 1 ) || (altura(m->esq) - altura(m->dir) < -1 ))
		return 0;
	return (e_avl(m->esq));
	return (e_avl(m->dir));
	return 1;
}

static int altura (Mapa *m) {
	int he, hd;
	if (m == NULL) return 0;
	he = altura (m->esq);
	hd = altura (m->dir);
	return (he>hd?he:hd) + 1;
} 

int chavek (Mapa* m, int k) {
	int qnts = 0;
	return (auxchavek(m,k,&qnts));
}

static int auxchavek (Mapa *m, int k, int *qnts){
	int num;
	if (m == NULL) return -1;
	num = auxchavek(m->esq,k,qnts);
	if (*qnts >= k) return num;
	(*qnts)++;
	if ((*qnts) == k) return m->chave;
	return auxchavek(m->dir,k,qnts);
}

void succ (Mapa *m, int c){
	if (m == NULL) return ;
	succ(m->esq,c);
	if (m->chave < c) printf("%d\n",m->chave);
	succ(m->dir,c);
}

int debug_altura (Mapa *m) /*versao se tivesse bf*/{
	int i = 1;
	int h = 0;
	while (i){
		if (m == NULL) i = 0;
		h++;
		else if (m->bf > 0)
			m = m->dir;
		else m = m->esq
	}
	return h;
}

int debug_altura (Mapa *m){
	int he, hd;
	he = hd = 0;
	Mapa *esquerdo = cria();
	Mapa *direito = cria();
	esquerdo = m;
	direito = m;
	while (esquerdo != NULL || direito != NULL){
		esquerdo = esquerdo->esq;
		he++;
		direito = direito->dir;
		hd++;
	}
	return (hd>he?hd:he);
}


