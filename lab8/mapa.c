#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mapa.h"

#define TAMINICIAL 256

typedef struct {
  int chave;
  int dados;
  int prox;
} ttabpos;

struct smapa {
  int tam;
  ttabpos *tabpos;
};

unsigned int hash1 (int a) {
  return a;
}
  
unsigned int hash2(int a) {
  a = (a ^ 61) ^ (a >> 16);
  a = a + (a << 3);
  a = a ^ (a >> 4);
  a = a * 0x27d4eb2d;
  a = a ^ (a >> 15);
  return a;
}

unsigned int hash (int chave) {
  return hash1(chave);
}

Mapa* cria () {
  int i;
  Mapa* m = (Mapa*) malloc (sizeof(Mapa));
  if (m==NULL) {printf("erro de memoria! \n"); exit(1);}
  m->tabpos = (ttabpos*) malloc (TAMINICIAL*sizeof(ttabpos)); 
  if (m->tabpos==NULL) {printf("erro de memoria! \n"); exit(1);}
  m->tam = TAMINICIAL;
  for (i=0;i<TAMINICIAL;i++) {
    m->tabpos[i].chave = -1;
    m->tabpos[i].prox = -1;
  }
  return m;
}

Mapa* insere (Mapa* m, int chave, int dados) {
  int pos = hash(chave)%(m->tam);
  int i = 0, hash0;

  if (m->tabpos[pos].chave == -1) { /* está vazia - caso fácil */
    m->tabpos[pos].chave = chave;
    m->tabpos[pos].dados = dados;
    m->tabpos[pos].prox = -1;
  }
  else { /* tem que encontrar outra posicao livre */
    /* ... procura valor correto para poslivre */
    /* achou posicao livre  - verificar quem vai para ela */
    /* hash de item em pos é igual ao da nova chave? */
    /* sim -  conflito primario: encadeia na lista do item em pos */
      /* ... */
    /* nao - conflito secundario: expulsa o item atual de pos */
      /* encontrar a posicao do item atualmente em pos na sua lista */
      /* ... */
      /* acertar encadeamento */
      /* ... */
      hash0 = hash(m->tabpos[pos].chave)%(m->tam);
      while (m->tabpos[i].chave != -1){
         if (i > m->tam){
            printf("Tabela cheia.\n");
            return m;
           }
         i++;
       }
      if (hash0 != pos){
         m->tabpos[i].chave = m->tabpos[pos].chave;
         m->tabpos[i].dados = m->tabpos[pos].dados;
         m->tabpos[i].prox = m->tabpos[pos].prox;
         
         while (m->tabpos[hash0].prox != pos)
            hash0 = m->tabpos[hash0].prox;
            
         m->tabpos[hash0].prox = i;
         
         m->tabpos[pos].chave = chave;
         m->tabpos[pos].dados = dados;
         m->tabpos[pos].prox = -1;
       }
      else {
         m->tabpos[i].chave = chave;
         m->tabpos[i].dados = dados;
         m->tabpos[i].prox = m->tabpos[pos].prox;
         
         m->tabpos[pos].prox = i;
       }
     }
  return m;
}

int busca (Mapa *m, int chave) {
	int pos = hash(chave)%(m->tam);
	while (m->tabpos[pos].chave != -1){
		if (m->tabpos[pos].chave == chave) return pos;
		if (m->tabpos[pos].prox == -1) break;
		pos = m->tabpos[pos].prox;
	}
  return -1;
}

void destroi (Mapa *m) {
  free (m->tabpos);
  free (m);
}

void debug_mostra_mapa (Mapa* m) {
  int i;
  for (i=0;i<m->tam;i++) 
    if (m->tabpos[i].chave!=-1) 
      printf ("posicao %d, chave %d, proximo %d\n", i, m->tabpos[i].chave, m->tabpos[i].prox);
}

