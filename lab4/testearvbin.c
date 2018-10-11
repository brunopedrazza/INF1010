#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include "mapa.h"

#define REPETE 1000
#define MAX 100000
#define ANTIGA 7
#define NOVA 99

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

  int muitos[MAX];
  int i, c;
  long int tamanho;
  int chavedada;

  if (argc!=2) {
    printf("uso: <%s> <tamanhoMapa>\n", argv[0]);
    exit(1);
  }
  tamanho = strtol (argv[1], NULL, 10);
  if (tamanho == 0) {
    printf("tamanho invÃ¡lido!\n");
    exit(1);
  }

  Mapa *mapa1 = cria();
  Mapa *mapa2 = cria();
  Mapa *mapa3 = cria();
  Mapa *mapa4 = cria();

  for (i=0;i<tamanho;i++) muitos[i]=i;

	printf("\n");

  printf("constroi mapa1  -------------- \n");
  for (i=0;i<tamanho;i++) {
    mapa1 = insere(mapa1, i, muitos[i]);
  }
  debug_mostra_mapa (mapa1);

	printf("mapa1 Ã© avl? %s\n", e_avl(mapa1)?"sim":"nÃ£o");
  printf("mapa1 Ã© abb? %s\n", e_abb(mapa1)?"sim":"nÃ£o");
	printf("altura mapa1 ---- %d\n",debug_altura(mapa1));
	for (i=0;i<tamanho;i++) {
    mapa4 = insere(mapa4, i, muitos[i]);
  }
	
  mapa4 = debug_troca_chave (mapa4, ANTIGA, NOVA);
  
	printf("\n");

  printf("Troca %d por %d no mapa1 (novo mapa4) ------ \n",ANTIGA,NOVA);
  
  debug_mostra_mapa (mapa4);

  printf("mapa4 Ã© avl? %s\n", e_avl(mapa4)?"sim":"nÃ£o");
  printf("mapa4 Ã© abb? %s\n", e_abb(mapa4)?"sim":"nÃ£o");
	printf("altura mapa4 ---- %d\n",debug_altura(mapa4));

	printf("\n");

  printf("constroi mapa2 -------------- \n");
  mapa2 = preenche (mapa2, muitos, 0, tamanho-1);

  debug_mostra_mapa (mapa2);

	printf("mapa2 Ã© avl? %s\n", e_avl(mapa2)?"sim":"nÃ£o");
  printf("mapa2 Ã© abb? %s\n", e_abb(mapa2)?"sim":"nÃ£o");
	printf("\n");

  printf("mapa1 e mapa2 sao iguais? %s\n", iguais(mapa1,mapa2)?"sim":"nao");
  printf("mapa1 e mapa1 sao iguais? %s\n", iguais(mapa1,mapa1)?"sim":"nao");
  printf("mapa2 e mapa2 sao iguais? %s\n", iguais(mapa2,mapa2)?"sim":"nao");
	printf("mapa1 e mapa4 sao iguais? %s\n", iguais(mapa1,mapa4)?"sim":"nao");
  
	printf("\n");

  printf("constroi mapa3 -------------- \n");
  while (1) {
    printf ("inserir em mapa3 (digite -1 para terminar): ");
    scanf ("%d", &chavedada);
    if (chavedada==-1) break;
    mapa3 = insere(mapa3, chavedada, chavedada);
  }
  debug_mostra_mapa (mapa3);

  printf("mapa3 Ã© avl? %s\n", e_avl(mapa3)?"sim":"nÃ£o");
  printf("mapa3 Ã© abb? %s\n", e_abb(mapa3)?"sim":"nÃ£o");
	printf("altura mapa3 ---- %d\n",debug_altura(mapa3));
	printf("chaves do mapa 3 menores que:");
	scanf("%d",&c);
	succ(mapa3,c);

  while (1) {
    printf ("posiÃ§Ã£o (digite -1 para terminar): ");
    scanf ("%d", &chavedada);
    if (chavedada==-1) break;

    printf("em mapa3 chave %d Ã© %d\n", chavedada, chavek(mapa3, chavedada));
  }

  destroi(mapa1); 
  destroi(mapa2);
  destroi(mapa3);
	destroi(mapa4);

  return 0;
}
