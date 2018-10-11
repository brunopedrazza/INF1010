#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
 
int main()
{
  int * caminhos;
  int i, no;

  Grafo * g=grafoLe("grafo.dat");
  grafoMostra("Grafo dado: ",g);
  
  while (1) {
    printf ("no origem? (-1 para fim) ");
    scanf("%d", &no);
    if (no==-1) break;
    caminhos = menoresCaminhos(g, no);
    if (caminhos == NULL) printf ("no invalido!\n");
    else {
      for (i=0; caminhos[i]!= -1; i++)
        printf ("menor caminho de %d ate %d: %d\n", no, i, caminhos[i]);
      free (caminhos);
   }
  }

  free(g);

  return 0 ;
}

