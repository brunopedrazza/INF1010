#include <stdio.h>
#include <stdlib.h>
#include "listaprio.h"

#define TAM 8
int main(void) {
  int i;
  int info, v[]={25, 48, 37, 12, 57, 86, 33, 92};
  int *ordenado;
  ListaP *lp1, *lp2;

  lp1 = listap_cria(10, TAM, v);
  debug_listap_show(lp1, "lp1 ");
  lp2 = listap_cria(30, 0, NULL);
  for (i=0;i<TAM;i++) {
    listap_insere(lp2,v[i]);
    printf("insere %d, ", v[i]);
    debug_listap_show(lp2, "lp2 ");
  }
  do{
    info = listap_remove(lp2);
    printf("remove %d ", info);
    debug_listap_show(lp2, "lp2 ");
  } while(info>0);
  
  ordenado = cria_listaordenada (v, TAM);
  
  for (i=0 ; i<TAM ; i++)
    printf("%d\n",ordenado[i]);
    
  listap_libera(lp1);
  listap_libera(lp2);
  return 0;
}

