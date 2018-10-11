#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <inttypes.h>
#include <time.h>

#define REPETE 1000
#define MAX 100000

typedef struct smapa {
  int chave;
  int dados;
  Mapa* esq;
  Mapa* dir;
}Mapa; 

Mapa* preenche (Mapa* m, int dados[], int inicio, int fim) {
  int meio;
  if (inicio>fim) return m;
  meio = (fim+inicio)/2;
  m = insere (m, dados[meio], dados[meio]);
  m = preenche (m, dados, inicio, meio-1);
  m = preenche (m, dados, meio+1, fim);
  return m;
} 
Mapa* cria (void) {
  return NULL;
}

Mapa *insere (Mapa *m, int chave, int d) {
  if (m == NULL){
    m = (Mapa*)malloc(sizeof(Mapa));
    m -> chave = chave;
    m -> dados = d;
    m -> esq = NULL;
    m -> dir = NULL;
  }
  else if (chave < (m->chave))
    m->esq = insere(m->esq, chave, d);
  else if (chave > (m->chave))
    m->dir = insere(m->dir, chave, d);
  return m;
}

int busca (Mapa *m, int chave) {
  if (m == NULL)
    return (-1);
  else if (chave == m->chave)
    return m->dados;
  else if (chave < (m->chave))
    return busca(m->esq, chave);
  else
    return busca(m->dir, chave);
}  

void debug_mostra_mapa_int (Mapa* m) {

  printf("[");
  if (m != NULL) {
    printf("%d ", m->chave);
    debug_mostra_mapa_int(m->esq);
    debug_mostra_mapa_int(m->dir);
  }
  printf("]");
}

void debug_mostra_mapa (Mapa* m) {
  debug_mostra_mapa_int (m); printf ("\n");
}

void destroi (Mapa *m) {
  if (m==NULL) return;
  destroi (m->esq);
  destroi (m->dir);
  free(m);
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

  debug_mostra_mapa (ummapa);

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

  debug_mostra_mapa (outromapa);

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
