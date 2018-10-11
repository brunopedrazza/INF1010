typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave, int novodado);
/* considera chaves nÃ£o negativas e nÃ£o repetidas */

int busca (Mapa *m, int chave);
void destroi (Mapa *m);

int iguais (Mapa *m1, Mapa *m2);
int e_abb (Mapa *m);
int e_avl (Mapa*m);
int chavek (Mapa* m, int k);
int verificaordenacao (Mapa *m);
void succ (Mapa *m, int c);
int debug_altura (Mapa *m);

Mapa* debug_troca_chave (Mapa *m, int original, int novachave);
void debug_mostra_mapa (Mapa *m);

