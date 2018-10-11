#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "set.h"

#define TAM 32

/* cria um conjunto com n elementos */
Set* setCreate(void){
	Set* set = (Set*)malloc(sizeof(Set));
	if (set != NULL) *set = 0;
	return set;
}

/* destroi (desaloca) o conjunto */
Set* setDestroy(Set* set) {
	if (set) free(set);
	return NULL;
}

/* cria uma copia do conjunto */
Set* setCopy(Set* set){
  Set* setcopia = setCreate();
  *setcopia = *set;
  if (setcopia != NULL)
     return setcopia;
  return NULL;
}

/* cria uma complemento do conjunto */
Set* setComplement(Set* set){
  Set* setcomp = setCreate();
  *setcomp = ~*set;
  if (setcomp != NULL)
     return setcomp;
  return NULL;
}

/* insere o elemento i no conjunto */
void setInsert(Set *set, int i) {
   *set = (*set)|(1<<i);
}

/* remove o elemento i do conjunto */
void setRemove(Set *set, int i){
   *set = ~(1<<i) & (*set);
}


/* testa se o elemento i pertence ao conjunto */
int setIsMember(Set *set, int i){
  if ((i<0) || (i>8*sizeof(Set))) return 0;
  return ((1<<i) & (*set));
}


/* cria a uniao de dois conjunto que podem ter tamanhos diferentes */
/* naturalmente o numero de elementos do universo e' o do maior dos dois */
Set* setUnion( Set *set1,  Set *set2){
  *set1 = *set1 | *set2;
    if (set1 != NULL)
      return set1;
  return NULL;
}

/* calcula a intersecao de dois conjuntos */
Set* setIntersection( Set *set1,  Set *set2){
   Set *setInter = setCreate();
  *setInter = (*set1) & (*set2);
    if (setInter != NULL)
      return setInter;
  return NULL;
}

/* calcula a diferenca de set1-set2 */
Set* setDifference(Set *set1, Set *set2){
  Set *setDif = setCreate();
  *setDif = ~*set2 & *set1;
  return setDif;
  return NULL;
}



/* verifica de set2 e' um sub conjunto de set1 */
int setIsSubset( Set *set1,  Set *set2) {
  if ( *set2 == (*set1 & *(set2)))
    return 1;
  return 0;
}


/* verifica se dois conjuntos sao iguais */
int setIsEqual( Set *set1,  Set *set2) {
  if (*set1 == *set2)
    return 1;
  return 0;
}

/* informa a cardinalidade do conjunto */
int setNumberOfElements(Set* set){
  int i, cont=0;
  for (i=0 ; i<TAM ; i++){
    if ( ((1<<i) & (*set)) == (1<<i))
      cont++;
    }
  return cont;
}

/* mostra os elementos do conjunto */
void setShow(char* title, Set* set){
	int i, first=1;
	printf("%s = {", title);
	for (i = 0; i < 8*sizeof(Set); i++) 
		if (setIsMember(set, i)) { 
			if (first) { 
				printf("%d", i); 
				first = 0; 
			}
			else 
				printf(",%d", i);
                 }
	printf("}\n\n");
}

