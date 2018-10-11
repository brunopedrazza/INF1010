typedef struct smapa Mapa;

void menoresque (Mapa *m, int c);
Mapa* cria (void);
Mapa* insere (Mapa* m, int chave);
int busca (Mapa *m, int chave);
Mapa* retira (Mapa *m, int chave); /* atenção! nome mudou :-) */
void destroi (Mapa *m);


void debug_mostra_mapa (Mapa *m);

struct smapa
{
        int  kp, kg;   /* chaves: kp<kg, se kg existir. Se kg=-1, significa que ele não existe. */
        Mapa  *pai;
        Mapa  *esq;
        Mapa  *meio;
        Mapa  *dir;
};
