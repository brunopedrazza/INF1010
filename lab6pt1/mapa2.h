typedef struct smapa Mapa;

Mapa* cria (void);
Mapa* insere (Mapa* m, int chave);
int busca (Mapa *m, int chave);
Mapa* retira (Mapa *m, int chave); /* atenção! nome mudou :-) */
void destroi (Mapa *m);


void debug_mostra_mapa (Mapa *m);
