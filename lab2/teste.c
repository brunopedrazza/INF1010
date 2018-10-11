#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "mapa.h"

#define REPETE 1000
#define MAX 100000

Mapa* preenche (Mapa* m, int dados[], int inicio, int fim) {
  int meio;
  if (inicio>fim) return m;
  meio = (fim+inicio)/2;
  m = insere (m, dados[meio], dados[meio]);
  m = preenche (m, dados, inicio, meio-1);
  m = preenche (m, dados, meio+1, fim);
  return m;
}

int main (int argc, char** argv) {

  clock_t clantes, cldepois;
    
  int muitos[MAX];
  int i, dado;
  long int tamanho;

  if (argc!=2) {
    printf("uso: <%s> <tamanhoMapa>\n", argv[0]);
    exit(1);
  }
  tamanho = strtol (argv[1], NULL, 10);
  if (tamanho == 0 || tamanho>MAX) {
    printf("tamanho invÃ¡lido! Usar tamanhos entre 1 e %d\n", MAX);
    exit(1);
  }

  Mapa *ummapa = cria();
  Mapa *outromapa = cria();

  for (i=0;i<tamanho;i++) muitos[i]=i;
  
  printf("\nconstroi um mapa -------------- \n");

  clantes = clock();
  for (i=0;i<tamanho;i++) ummapa = insere(ummapa, i, muitos[i]);
  cldepois = clock();
  printf("\nTempo de insercao foi de %f segundos\n\n", (double)(cldepois - clantes) / CLOCKS_PER_SEC);

  //debug_mostra_mapa (ummapa);

  printf("\nbusca %ld\n", tamanho+1);
  clantes = clock();
  dado = busca(ummapa, tamanho+1);
  printf ("achou? %s\n", (dado!=-1)?"sim":"nÃ£o");
  
  printf("busca %ld\n", tamanho-1);
  dado = busca(ummapa, tamanho-1);
  printf ("achou? %s\n", (dado!=-1)?"sim":"nÃ£o");
  cldepois = clock();

  printf("\nTempo de busca foi de %f segundos\n\n", (double)(cldepois - clantes) / CLOCKS_PER_SEC);

  printf("\nconstroi outro mapa -------------- \n");
  clantes = clock();
  outromapa = preenche (outromapa, muitos, 0, tamanho-1);
  cldepois = clock();
  printf("\nTempo de insercao foi de %f segundos\n\n", (double)(cldepois - clantes) / CLOCKS_PER_SEC);

  //debug_mostra_mapa (outromapa);

  printf("\nbusca %ld\n", tamanho+1);
  clantes = clock();
  dado = busca(outromapa, tamanho+1);
  printf ("achou? %s\n", (dado!=-1)?"sim":"nÃ£o");

  printf("busca %ld\n", tamanho-1);
  dado = busca(outromapa, tamanho-1);
  printf ("achou? %s\n", (dado!=-1)?"sim":"nÃ£o");
  clantes = clock();

  printf("\nTempo de busca foi de %f segundos\n\n", (double)(cldepois - clantes) / CLOCKS_PER_SEC);

  destroi(ummapa); destroi(outromapa);

  return 0;}
