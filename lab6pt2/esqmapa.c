
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "mapa.h"

typedef enum {ESQ, MEIO, DIR} tipofilho;


typedef enum {OK, RETIRA_MENOR, RETIRA_MAIOR} tiporesultado;

struct smapa {
	int  kp, kg;   /* chaves: kp<kg, se kg existir. Se kg=-1, significa que ele não existe. */
	Mapa  *pai;
	Mapa  *esq;
	Mapa  *meio;
	Mapa  *dir;
};

Mapa* cria (void) {
	return NULL;
}

Mapa* novoNo (int chave) {
	Mapa *m = (Mapa*) malloc(sizeof(struct smapa));
	if (m == NULL) {
		printf ("erro no malloc! \n");
		exit(1);
	}
	m->pai = NULL;
	m->kp = chave; 
	m->kg = -1;
	m->esq = m->meio = m->dir = NULL;
	return m;
}

Mapa* overflowQuebra (Mapa *m, int *valorainserir, Mapa* novofilho) {
/* quebra o nó m em dois, cada um com uma chave                    */
/* entrada:                                                        */
/* m é nó com 2 chaves                                             */
/* *valorainserir é a nova chave                                   */
/* novofilho é subárvore que deve entrar à esquerda da nova chave  */
/* saída:                                                          */
/* retorno é o novo nó criado                                      */
/* *valorainserir é a mediana que tem que "subir"                  */

  Mapa* novo;

  novo = (Mapa*) malloc(sizeof(struct smapa));
  if (novo==NULL) { printf ("erro no malloc! \n"); exit(1);}

  if (*valorainserir < m->kp) {
    novo->esq = novofilho;
    if (novo->esq) novo->esq->pai = novo;
    novo->kp = *valorainserir;
    novo->meio = m->esq;
    if (novo->meio) novo->meio->pai = novo;
    novo->kg = -1;
    novo->dir = NULL;
    *valorainserir = m->kp;
    m->esq = m->meio;
    m->kp = m->kg;
  }
  else if (*valorainserir < m->kg) {
	novo->meio = novofilho;
	if (novo->meio) novo->meio->pai = novo;
	novo->kp = m->kp;
	m->kp = m->kg;
	novo->kg = -1;
	novo->dir = NULL;
	novo->esq = m->esq;
	if (novo->esq) novo->esq->pai = novo;
   m->esq = m->meio;
		
   } 
   
 else {
   novo->esq = m->esq;
   if (novo->esq) novo->esq->pai = novo;
   m->esq = novofilho;
	if (novo->esq) novo->esq->pai = novo;
	novo->kp = m->kp;
	m->kp = *valorainserir;
	novo->meio = m->meio;
	if (novo->meio) novo->meio->pai = novo;
	*valorainserir = m->kg;
	novo->dir = NULL;
	novo->kg = -1;
  }
  /* parte que "sobrou" sempre fica assim: */
  m->meio = m->dir;
  m->kg = -1;
  m->dir = NULL;
  return novo;
}

int insere2 (Mapa* m, int chave, int* valorainserir, Mapa** novofilho) {

  int inseriraqui = 0; /* indica se deve inserir neste nó */

  if (m==NULL) {
    printf("erro! subárvore nula! \n"); exit (1);
  }

  if (m->esq != NULL) { /* não é folha, só insere neste nó se chamada recursiva retornar mediana  */
    if (chave < m->kp) {
      inseriraqui = insere2(m->esq, chave, valorainserir, novofilho); 
    }
    else if (((m->kg != -1) && (chave < m->kg)) || (m->kg == -1)) {
      /* ou está entre as duas chaves ou só tem uma chave no nó */
      inseriraqui = insere2(m->meio, chave, valorainserir, novofilho);
    }
    else { /* chave > m->kg */
      inseriraqui = insere2(m->dir, chave, valorainserir, novofilho);
    }
  }
  else { /* este nó é folha, tem que inserir nele de qq jeito */
    *valorainserir = chave;
    inseriraqui = 1;
    *novofilho = NULL; /* neste caso novo item não tem uma subarvore associada */
  } 

  if (!inseriraqui) return 0; /* inserção já está completa */

  if (m->kg==-1) /* tem  espaço no nó */{
    if(m->kp < *valorainserir){
			m->kg = *valorainserir;
			m->dir = m->meio;
			m->meio = *novofilho;
		}
	
  	else {
  		   m->kg = m->kp; 
  		   m->kp = *valorainserir;
			m->dir = m->meio;
			m->meio = m->esq;
			m->esq = *novofilho;
  	}
    return 0; /* como havia espaço, não sobem valores a serem inseridos */
  }

  *novofilho = overflowQuebra (m, valorainserir, *novofilho); 

  return 1; /* quando há quebra sempre sobe a mediana para nova inserção */ 
}

Mapa* insere (Mapa* m, int chave) {
  int valorquesubiu;
  Mapa* novofilho;
  Mapa* novaraiz;
  if (m==NULL) {
    m = novoNo (chave);
  }
  else {
    if (insere2 (m, chave, &valorquesubiu, &novofilho)) {
      /* cria nova raiz */
      novaraiz = novoNo (valorquesubiu);
      novaraiz->esq = novofilho;
      novaraiz->meio = m;
      m = novaraiz;
    } 
  }

  return m;
}


int busca (Mapa *m, int chave) {
	return 0;
}

void preenche (Mapa *m, Mapa *esquerda, int kp, Mapa *meio, int kg, Mapa *direita) {
	m->kp = kp;
	m->kg = kg;
	m->esq = esquerda;
	m->meio = meio;
	m->dir = direita;
}

tiporesultado retirarec (Mapa *m, int chave) {

	Mapa *filhoqueficou, *irmao;
	tiporesultado res;
	tipofilho minhapos;

	if (m == NULL) {
		printf("erro! subárvore nula! \n"); exit (1);
	}

 	if (m->esq != NULL) { /* não é folha */
		if (chave < m->kp) {
			res = retirarec(m->esq, chave);
		}
	    else if (m->kp == chave) { /* achou - troca por succ */
			m->kp = maisaesquerda(m->meio);
			res = retirarec(m->meio, m->kp);
		}
		else if (((m->kg != -1) && (chave < m->kg)) || (m->kg == -1)) {
      		/* ou está entre as duas chaves ou só tem uma chave no nó */
			res = retirarec(m->meio, chave);
		}
    	else if (m->kg == chave) { /* achou - troca por succ */
			m->kg = maisaesquerda(m->dir);
			res = retirarec(m->dir, m->kg);
		}
    	else { /* chave > m->kg */
			res = retirarec(m->dir, chave);
		}
		if (res == OK) {
			return OK;
		}
	}
  	else { /* este nó é folha, chave tem que estar nele de qq jeito */
		if (chave == m->kp)
			res = RETIRA_MENOR;
		else if (chave == m->kg)
			res = RETIRA_MAIOR;
    else return OK;	/* chave não está na árvore!!! */
	}
  	/* retirada */
  	/* pode ser porque estamos em uma folha ou porque "caiu" uma das chaves */

  	if (res == RETIRA_MAIOR) { /* caso mais simples */
		preenche(m, m->esq, m->kp, m->meio?m->meio:m->dir, -1, NULL);
		return OK;
	}

  	/* RETIRAMENOR */ 
	if (m->kg != -1) {	/* ainda vai ficar um no nó, tb simples */
		preenche(m, m->esq?m->esq:m->meio, m->kg, m->dir, -1, NULL);
		return OK;
	}

  	/* RETIRAMENOR: essa é a única chave! combinar ou distribuir */

	minhapos = minhaposnopai(m->pai, m);

  	/* se ainda tiver algum filho pegá-lo para passar para outro */
	filhoqueficou = m->esq?m->esq:m->meio;

	if (minhapos == ESQ) { 
		irmao = m->pai->meio;
    if (irmao->kg == -1) { /* combinar */
			res = RETIRA_MENOR;
			preenche(irmao, filhoqueficou, m->pai->kp, irmao->esq, irmao->kp, irmao->meio);
			if (irmao->esq)
				irmao->esq->pai = irmao;
			m->pai->esq = NULL;
			free(m);
		}
    	else { /* irmão tem duas chaves, redistribuir  */
			res = OK;
			preenche(m, filhoqueficou, m->pai->kp, irmao->esq, -1, NULL);   
			if (m->meio != NULL)
				m->meio->pai = m;   
			if (m->esq != NULL)
				m->esq->pai = m;
			preenche(m->pai, m->pai->esq, irmao->kp, m->pai->meio, m->pai->kg, m->pai->dir);
			preenche(irmao, irmao->meio, irmao->kg, irmao->dir, -1, NULL);
		}  
	}
	else if (minhapos == MEIO) {
        irmao = m->pai->esq;
        if (irmao->kg == -1) {
						res = RETIRA_MENOR;
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, m->pai->kp, filhoqueficou);
            if (irmao->dir != NULL)
            	irmao->dir->pai = irmao;
            m->pai->meio = NULL;
            free(m);
        }
        else {
						res = OK;
            preenche(m, irmao->dir, m->pai->kp, filhoqueficou, -1, NULL);
						if (m->meio)
            	m->meio->pai = m;
            if (m->esq != NULL)
            	m->esq->pai = m;
            preenche(m->pai, m->pai->esq, irmao->kg, m->pai->meio, m->pai->kg, m->pai->dir);
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, -1, NULL);
        }
    }
    else if (minhapos == DIR) {
        irmao = m->pai->meio;
        if (irmao->kg == -1) {
						res = RETIRA_MAIOR;
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, m->pai->kp, filhoqueficou);
            if (irmao->dir != NULL)
            	irmao->dir->pai = irmao;
            m->pai->meio = NULL;
            free(m);
        }
        else {
						res = OK;
            preenche(m, irmao->dir, m->pai->kp, filhoqueficou, -1, NULL);
            if (m->esq != NULL)
            	m->esq->pai = m;
            if (m->meio != NULL)
            	m->meio->pai = m;
            preenche(m->pai, m->pai->esq, irmao->kg, m->pai->meio, m->pai->kg, m->pai->dir);
            preenche(irmao, irmao->esq, irmao->kp, irmao->meio, -1, NULL);
        }
    }
	return res;
}


Mapa* retira (Mapa *m, int chave) {
	Mapa* novaraiz;
	tiporesultado res;

	res = retirarec(m, chave);

 	if (res == RETIRA_MAIOR)
		preenche(m, m->esq, m->kp, m->meio?m->meio:m->dir, -1, NULL);

	else if (res == RETIRA_MENOR) {
		if (m->kg != -1)
			preenche(m, m->esq?m->esq:m->meio, m->kg, m->dir, -1, NULL);
		else {
			novaraiz = (m->esq)?m->esq:m->meio;
			novaraiz->pai = m->pai;
			free(m);
			m = novaraiz;
		}
	}
	return m;
}

tipofilho minhaposnopai (Mapa* pai, Mapa* m) {
	if (m == pai->esq) return ESQ;
	else if (m == pai->meio) return MEIO;
	else if (m == pai->dir) return DIR;
}


int maisaesquerda (Mapa *m) {
	while (m->esq)
		m = m->esq;
	return m->kp;
}

void destroi (Mapa *m) {
	if (m!= NULL) {
		destroi (m->esq);
		destroi (m->meio);
		destroi (m->dir);
		free (m);
	}
}

void debug_mostra_mapa_int (Mapa *m) {
  printf ("[");
  if (m != NULL) {
  	if (m->pai != NULL)
  	{
  		printf ("%d:%d/%d", m->kp, m->kg, m->pai->kp);
  	}
  	else {
  		printf ("%d:%d", m->kp, m->kg);
  	}
    
    debug_mostra_mapa_int (m->esq);
    debug_mostra_mapa_int (m->meio);
    if (m->kg != -1) {
    	debug_mostra_mapa_int(m->dir);
    }
  }
  printf ("]");
}

void debug_mostra_mapa (Mapa *m) {
	debug_mostra_mapa_int (m);
	printf("\n");
}
