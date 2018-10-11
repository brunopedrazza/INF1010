/*Bruno Pedrazza
  Leon França*/


#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

int main(void) {

    int ci;

    Mapa *mapa1 = cria();

    while (1) {
      printf ("chave a inserir: ");
      scanf ("%d", &ci);
      if (ci==-1) break;
      mapa1 = insere (mapa1, ci);
      debug_mostra_mapa (mapa1);
    }

		while (1) {
      printf ("chave a retirar: ");
      scanf ("%d", &ci);
      if (ci==-1) break;
      mapa1 = retira (mapa1, ci);
      debug_mostra_mapa (mapa1);
    }

    destroi (mapa1);

    return 0;
}

