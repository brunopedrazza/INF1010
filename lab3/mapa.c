#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include "mapa.h"

struct smapa {
  int chave;
  int conteudo;
  short int bf;
  struct smapa* esq;
  struct smapa* dir;
};

static Mapa* cria_no(int c, int novodado);
static Mapa* insere2(Mapa *m, int chave, int novodado, int *cresceu);
static Mapa* corrige_dir(Mapa *m);
static Mapa* corrige_esq(Mapa *m);
static Mapa* rotaciona_dir(Mapa *m);
static Mapa* rotaciona_esq(Mapa *m);

static Mapa* cria_no(int c, int novodado) {
  Mapa *m = (Mapa*)malloc(sizeof(Mapa));
  if (m != NULL) {
    m->esq = m->dir = NULL;
    m->chave = c;
    m->conteudo = novodado;
    m->bf = 0;
  }
  return m;
}

Mapa* cria() {
  return NULL;
}

Mapa* insere (Mapa* m, int chave, int novodado) {
  int cresceu = 0;
  return insere2(m, chave, novodado, &cresceu);
}

static Mapa* insere2(Mapa *m, int chave, int novodado, int *cresceu) {
  if (m == NULL) {
    m = cria_no(chave, novodado);
    *cresceu = 1;
  }
  else if (chave < m->chave) {
		m->esq = insere2 (m->esq, chave, novodado, cresceu);
		if(*cresceu){
			switch(m->bf){
			case 1:
				m->bf = 0;
        *cresceu = 0;
        break;
			case 0:
				m->bf = -1;
        break;
			case -1:
				m = corrige_esq(m);
				*cresceu = 0;
        break;
			}	
		}
  }
  else if (chave > m->chave) {
    m->dir = insere2(m->dir, chave, novodado, cresceu);
    if(*cresceu) {
      switch (m->bf) {
      case 1: /* já era 1, não pode crescer a direita */
        m = corrige_dir(m);
        *cresceu = 0;
        break;
      case 0: /* estava equilibrada, pode aumentar de um lado  avisando para cima que cresceu*/
        m->bf = 1;
        break;
      case -1: /* ficou equilibrada, então não cresceu em altura */
        m->bf = 0;
        *cresceu = 0;
        break;
      }
    }
  }
  return m;
}

static Mapa* corrige_esq(Mapa *m) {
	if (m->esq->bf == -1) {
		m->bf = m->esq->bf = 0;
		return rotaciona_dir(m);
	}
	else{
		m->bf = m->dir->bf = 0;
		return rotaciona_esq(m);
	}
}

static Mapa* corrige_dir(Mapa *m) {
  if (m->dir->bf == 1) {
    m->bf = m->dir->bf = 0;
    return rotaciona_esq(m);
  }
  else{
		m->bf = m->esq->bf = 0;
		return rotaciona_dir(m);
  }
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

int busca (Mapa *m, int chave) {
  if (m == NULL) {
    return -1;
  }
  else if (m->chave == chave) {
    return m->conteudo;
  }
  else if (chave < m->chave) {
  return busca(m->esq, chave);
  }
  else if (chave > m->chave) {
    return busca(m->dir, chave);
  }
  else {
    return -1;
  }
}


void destroi (Mapa *m) {
  if (m != NULL) {
    destroi(m->esq);
    destroi(m->dir);
    free(m);
  }
}


void debug_mostra_mapa_int (Mapa* m) {

  printf("(");
  if (m != NULL) {
    printf("%d-%d", m->chave,m->bf);
    debug_mostra_mapa_int(m->esq);
    debug_mostra_mapa_int(m->dir);
  }
  printf(")");
}

void debug_mostra_mapa (Mapa* m) {
  debug_mostra_mapa_int (m); printf ("\n");
}

int debug_altura (Mapa *m) /*Questao 3*/ {
	int hEsq, hDir;
	if (m == NULL)
		return -1;
	else {
		hEsq = debug_altura (m->esq);
  	hDir = debug_altura (m->dir);
  	if (hEsq > hDir) 
			return hEsq + 1;
  	else 
	  	return hDir + 1;
	}
}

