#include <stdio.h>
#include <stdlib.h>
#include "ub.h"
#include "listaprio.h"
#include "grafo.h"

int main (int argc, char** argv) {

  Grafo* arvore;

  if (argc != 2) {
    printf ("uso: %s <nomearquivografo>\n", argv[0]);
    exit(1);
  }

  arvore = arvoreCustoMinimo (argv[1]);
  
  grafoMostra(arvore);
  
  if (grafoConexo(arvore)) printf("Grafo e conexo.\n");
  else printf("Grafo nao e conexo.\n");

  return 0;

} 

