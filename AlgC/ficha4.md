#  Ficha 4 - Algoritmos sobre Grafos

## Representações

```c
#define NV 10

typedef struct aresta {
	int dest; int custo;
	struct aresta *prox;
} *LAdj, *GrafoL [NV];

typedef int GrafoM [NV][NV];
```

##### (1) Constrói o grafo out a partir do grafo in. Considere que in[i][j] == 0 sse não exista a aresta i -> j.

```c
/* Aux */

// Inicializar grafos
void initGrafoL(GrafoL g) {
    for(int i=0; i<NV; i++){
        g[i] = NULL;
    }
}

void initGrafoM(GrafoM g) {
    for(int i=0; i<NV; i++){
        for(int j=0; j<NV; j++){
            g[i][j] = 0;
        }
    }
}

// Inserir nova aresta numa LAdj
LAdj newAresta(int v, int custo, LAdj l) {
  LAdj new = malloc(sizeof(*new));
  new->dest = v;
  new->custo = custo;
  new->prox = l;
  return new;
}

void fromMat (GrafoM in, GrafoL out){
    initGrafoL(in);
    for(int i=0; i<NV; i++){
        for(int j=0; j<NV; j++){
            if(in[i][j]>0){
                out[i] = newAresta(j,in[i,j],out[i]);
            }
}

```

##### (2) Constrói o grafo out como inverso do grafo in.

```c
// TO DO

void inverte (GrafoL in, GrafoL out){
    initGrafoL(out)
}

```

##### (3) Calcula o grau de entrada do grafo (nr maximo de arestas que tem como destino um qualquer vertice).

```c
int inDegree (GrafoL g) {
    int ind[NV];
    int i;
    int grau=0;
    LAdj l; // cria a lista adjacente

    for (i = 0; i < NV; i++)
        ind[i] = 0;

    for (i = 0; i < NV; i++)
        for (l = g[i]; l != NULL; l = l->prox)
            ind[l->dest]++;

    for (i = 0; i < NV; i++)
        if (ind[i] > grau) grau = ind[i];

    return m;
}

// Outra versao
int inDegree (GrafoL g){
    int grau = 0;
    for(int i=0; i<NV; i++){
        int grauAux = 0;
        for(int j=0; j<NV; j++){
            if(g[i]->dest == g[j]->dest) grauAux++;
        }
        if(grauAux > grau) grau = grauAux;
    }
return grau;
}

```

##### (4) Verifica se o array cor corresponde a uma coloração válida do grafo.
Uma coloração de um grafo é uma função (normalmente representada como um array
de inteiros) que atribui a cada vértice do grafo a sua cor, de tal forma que vertices adjacentes (i.e., que estao ligados por uma aresta) têm cores diferentes.

```c
int colorOK (GrafoL g, int cor[]){
    int okay = 1;
    int i;
    LAdj l;
    for(i=0; okay && i<NV; i++){
        for(l=g[i]; l!=NULL; l=l->prox){
            if(cor[i] == cor[l->dest]){
                okay = 0;
                break;
            }
        }
    }
return okay;
}

```

##### (4) Verifica se a função f é um homomorfismo de g para h.
Um homomorfismo de um grafo g para um grafo h é uma função f (representada como
um array de inteiros) que converte os vértices de g nos vértices de h tal que, para cada a aresta a -> b de g existe uma aresta f(a) -> f(b).

```c
/* Aux */
// verifica se a aresta existe
int exist(GrafoL g, int orig, int dest){
    e = 0;
    LAdj l;
    for(l=g[orig]; l!=NULL; l=l->prox){
        if(l->dest == dest){
            e = 1;
            break;
        }
    }
return e;
}

int homomorfOK (GrafoL g, GrafoL h, int f[]){
    int okay = 1;
    int i;
    LAdj l;
    for(i=0; okay && i<NV; i++){
        for(l=g[i]; okay && l!=NULL; l=l->prox){
            if(!exist(g, f[i], f[h[i]->dest])) okay = 0;
        }
    }
return okay;
}

```

## Travessias
Considerar as funções que fazem travessias de grafos.

##### Depth First

```c
int DF (GrafoL g, int or, int v[], int p[], int l[]){
    int i;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    p[or] = -1; l[or] = 0;
    return DFRec (g,or,v,p,l);
}

int DFRec (GrafoL g, int or, int v[], int p[], int l[]){
    int i; LAdj a;
    i=1;
    v[or]=-1;
    for (a=g[or]; a!=NULL;a=a->prox){}
        if (!v[a->dest]){
            p[a->dest] = or;
            l[a->dest] = 1+l[or];
            i+=DFRec(g,a->dest,v,p,l);
        }
    }
    v[or]=1;
    return i;
}
```

##### Breadth First

```c
int BF (GrafoL g, int or, int v[], int p[], int l[]){
    int i, x; LAdj a;
    int q[NV], front, end;
    for (i=0; i<NV; i++) {
        v[i]=0;
        p[i] = -1;
        l[i] = -1;
    }
    front = end = 0;
    q[end++] = or; //enqueue
    v[or] = 1; p[or]=-1;l[or]=0;
    i=1;
    while (front != end){
        x = q[front++]; //dequeue
        for (a=g[x]; a!=NULL; a=a->prox){
            if (!v[a->dest]){
                i++;
                v[a->dest]=1;
                p[a->dest]=x;
                l[a->dest]=1+l[x];
                q[end++]=a->dest; //enqueue
            }
        }
    }
    return i;
}
```


##### (1) Calcula a distância (número de arestas) que separa o vértice v do que lhe está mais distante. A função deverá preencher o array p com os vértices correpondentes a esse caminho.
No grafo apresentado acima, a invocação `maisLonga (g, 0, p)` deve dar como resultado 3 (correspondendo, por exemplo, â distância entre 0 e 7).

```c

int maisLonga (GrafoLg, int or, int p[]){

}

```

##### (2) Recebe como argumento um grafo não orientado g e calcula as componentes ligadas de g, i.e., preenche o array c de tal forma que, para quaisquer par de vértices x e y, c[x] == c[y] sse existe um caminho a ligar x a y.

```c

int componentes (GrafoL g, int c[]){

}

```

##### (3) Preenche o array ord com uma ordenação topológica do grafo.
Num grafo orientado e acíclico, uma ordenação topológica dos seus vértices é uma
sequência dos vértices do grafo em que, se existe uma aresta a -> b então o vértice `a` aparece antes de `b` na sequência. Consequentemente, qualquer vértice aparece na sequÊncia depois de todos os seus alcançãveis.

```c

int ordTop (GrafoL g, int ord[]){

}

```
