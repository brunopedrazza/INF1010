/*Bruno Pedrazza
  Leon França*/


#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

int main(void) {

    int ci, menor;

    Mapa *mapa1 = cria();

    while (1) {
      printf ("chave a inserir: ");
      scanf ("%d", &ci);
      if (ci==-1) break;
      mapa1 = insere (mapa1, ci);
      
      debug_mostra_mapa (mapa1);
    }
    
    scanf("%d",&menor);
    menoresque(mapa1,menor);
    
    destroi (mapa1);

    return 0;
}

void menoresque (Mapa *m, int c){
	if (m==NULL) return;
	menoresque(m->esq,c);
	if (m->kp >= c) return;
	printf("%d\n",m->kp);
	menoresque(m->meio,c);
	if (m->kg >= c) return;
	if (m->kg != -1) printf("%d\n",m->kg);
	menoresque(m->dir,c);
}
