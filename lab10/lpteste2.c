#include <stdio.h>
#include <limits.h>
#include "listaprio2.h"

int main(void) {
  int i,n=8;
  int info, v[]={25, 48, 37, 12, 57, 86, 33, 92};
  ListaP* lp = listap_cria(30);
  for (i=0;i<n;i++) {
    listap_insere(lp,v[i],i);
    printf("insere %d(%d), ", v[i], i);
    debug_listap_show(lp, "lp=");
  }
  /* reposicionando... */
  for (i=0;i<n;i++) {
    printf("corrige prio de %d, ", i);
    corrige_pos (lp, -v[i], i);
    debug_listap_show(lp, "lp=");
  }
  do{
    info = listap_remove(lp);
    printf("remove %d ", info);
    debug_listap_show(lp, "lp=");
  } while(info != -1);

  listap_libera(lp);
  return 0;
}

