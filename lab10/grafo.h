typedef struct _grafo Grafo;

Grafo* grafoLe( char* filename );
Grafo* grafoLibera(Grafo* grafo);
void grafoMostra(char* title, Grafo* grafo);
void grafoPercorreProfundidade(Grafo * grafo, int no_inicial);
Grafo* criaArvoreGeradora (Grafo *grafo, int no_inicial);
void grafoPercorreLargura(Grafo * grafo, int no_inicial);
int* menoresCaminhos (Grafo *grafo, int no_inicial);
Grafo* arvoreCustoMinimo (Grafo *grafo);
