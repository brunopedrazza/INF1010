#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "mapa.h"

struct smapa {
  int chave;
  int dado;
  char vermelho;
  struct smapa* esq;
  struct smapa *dir;
};

typedef enum result {OK, RED, LEFTRED, RIGHTRED} Result;

static Mapa *cria_no (int c, int novodado) {
  Mapa *nn = (Mapa *)malloc(sizeof(Mapa));
  if (nn!=NULL) {
    nn->esq = nn->dir = NULL;
    nn->chave =c;
    nn->vermelho = 1;
    nn->dado = novodado;
  }
  return nn;
}

Mapa* cria (void) {
  return NULL;
}

static Mapa* rotaciona_dir(Mapa *m) {
  Mapa* esq = m->esq;
  m->esq = esq->dir;
  esq->dir = m;
  return esq;
}

static Mapa* rotaciona_esq(Mapa *m) {
  Mapa* dir = m->dir;
  m->dir = dir->esq;
  dir->esq = m;
  return dir;
}

Mapa* trocaCores (Mapa *m) {
  char corpai = m->vermelho; 
  m->vermelho = !corpai;
  m->esq->vermelho = corpai;
  m->dir->vermelho = corpai;
  return m;
}

static int e_preto (Mapa *m) {
  return (m==NULL) || (!m->vermelho);
}

Mapa* corrigeDir (Mapa *m, Result* status) {
  switch (*status) {
    case OK:
      break;
    case RED:
      if (m->vermelho) *status = RIGHTRED;
      else *status = OK;
      break;
    case RIGHTRED:
      if (e_preto(m->esq)) {  /* tio preto ou vazio - podemos tratar como preto */
				printf ("RRb\n");
        m = rotaciona_esq (m);
        m = trocaCores(m);
        *status = OK;
      }
      else {  /* tio vermelho */
				printf ("RRr\n");
        m = trocaCores (m);
        *status = RED;
      }
      break;
    case LEFTRED:
      if (e_preto(m->esq)) {
				printf ("RLb\n"); /* tio preto ou vazio */
				m->dir = rotaciona_dir(m->dir);
				m = rotaciona_esq (m);
				m = trocaCores(m);
				*status = OK;
      }
      else { /* tio vermelho */
				printf ("RLr\n");
        m = trocaCores(m);
				m = rotaciona_dir(m);
				*status = RED;
      }
      break;
  }
  return m;
}

Mapa* corrigeEsq (Mapa *m, Result* status) {

  switch (*status) {
    case OK:
      break;
    case RED:
      if (m->vermelho) *status = LEFTRED;
      else *status = OK;
      break;
    case LEFTRED:
      if (e_preto(m->dir)) {  /* tio preto ou vazio - podemos tratar como preto */
				printf ("LLb\n");
        m = rotaciona_dir (m);
        m = trocaCores(m);
        *status = OK;
      }
      else { /* tio é vermelho */
				printf ("LLr\n");
        m = trocaCores (m);
        *status = RED;
      }
      break;
    case RIGHTRED:
      if (e_preto(m->dir)) {  /* tio preto ou vazio - podemos tratar como preto */
				printf ("LRb\n");
        m->esq = rotaciona_esq(m->esq);
				m = rotaciona_dir(m);
				m = trocaCores(m);
				*status = OK;
      }
      else { /* tio é vermelho */
				printf ("LRr\n");
        m = trocaCores(m);
				m = rotaciona_esq(m);
				*status = RED;
				
      }
      break;
  }
  return m;
}
          

Mapa* insereRec (Mapa* m, int chave, int novodado, Result* status){
  if (m==NULL) {
    m = cria_no (chave, novodado);
    *status = RED;
  }
  else if (chave < m->chave) {
    m->esq = insereRec (m->esq, chave, novodado, status);
    m = corrigeEsq (m, status);
  }
  else if (chave > m->chave) {
    m->dir = insereRec (m->dir, chave, novodado, status);
    m = corrigeDir (m, status);
  }
  return m;
}


Mapa* insere (Mapa* m, int chave, int novodado) {
  Result status;
  m = insereRec (m, chave, novodado, &status);
  if (status == RED) m->vermelho = 0;
  else if (status != OK) {
    printf ("erro ao voltar para a raiz: status invalido %d !\n", status);
    exit(1);
  }
  return m;
}

int busca (Mapa *m, int chave) {
  return INT_MAX;
}

Mapa* retira (Mapa *m, int chave){
  return m;
}

void destroi (Mapa *m){
}

void debug_mostra_int (Mapa* m) {

    printf("(");
    if (m != NULL) {
      printf("%d-%d", m->chave,m->vermelho);
      debug_mostra_int(m->esq);
      debug_mostra_int(m->dir);
    }
    printf(")");
}

void debug_mostra_mapa (Mapa *m){
    debug_mostra_int (m); printf ("\n");
}
