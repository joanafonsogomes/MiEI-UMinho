/* Ficha 4 - Algoritmos sobre Grafos */
#include <stdio.h>
#include <stdlib.h>

/* Representacoes */

# define NV 11

// grafos ladj
typedef struct aresta {
    int dest; int custo;
    struct aresta *prox;   
} *LAdj, *GrafoL [NV];

// grafos matrizes
typedef int GrafoM[NV][NV];

/* 1 */

// Auxs
void initGrafoL(GrafoL g){
    int i;
    for(i=0; i<NV; i++){
        g[i] = NULL;
    }
}

void initGrafoM(GrafoM g){
    int i, j;
    for(i=0; i<NV; i++){
        for(j=0; j<NV; j++){
            g[i][j] = 0;
        }   
    }
}

// Insere uma nova aresta numa LAdj
LAdj newAresta(int v, int custo, LAdj l){
    LAdj new = malloc(sizeof(new));
    new->dest = v;
    new->custo = custo;
    new->prox = l;

    return new;
}


void fromMat(GrafoM in, GrafoL out){
    int i, j;
    initGrafoL(out);
    for(i=0; i<NV; i++){
        for(j=0; j<NV; j++){
            if(in[i][j]>0){
                // newAresta(vertice dest, custo, vertice origem)
                out[i] = newAresta(j,in[i][j],out[i]);
            }
        }
    }
}

/* 2 */

void inverte(GrafoL in, GrafoL out){
    int i;
    LAdj l;
    initGrafoL(out);
    for(i=0; i<NV; i++){
        for(l=in[i]; l!=NULL; l=l->prox){
                // newAresta(vert dest, custo, vert origem)
               out[l->dest] = newAresta(i,l->custo,out[l->dest]);
        }
    }
}

/* 3 */

int inDegree(GrafoL g){
    int max, i;
    int deg[NV];
    LAdj l;
    for(i=0; i<NV; i++) deg[i];
    for(i=0; i<NV; i++){
        for(l=g[i]; l!=NULL; l=l->prox){
            deg[l->dest]++;
        }
    }
    max = deg[0];
    for(i=1; i<NV; i++){
        if(deg[i]>max) max = deg[i];
    }
    return max;
}

/* 4 */

int colorOK(GrafoL g, int cor[]){
    int i;
    LAdj l;
    for(i=0; i<NV; i++){
        for(l=g[i]; l!=NULL; l=l->prox){
            if(cor[i] != cor[l->dest]){
                return 0;
            }
        }
    }
    return 1;
}

/* Travessias */

/* 1 */

// Auxiliares

int maisLonga(GrafoL g, int or, int p[]){
   /* Calcula a distancia, por isso tem de ser BFS */
    int i, d, v, visit[NV], parent[NV]; l[NV];
    BF(g,or,visit,parent,l);
    // encontrar o vértice mais distante
    d=0, v=or;
    for(i=0; i<NV; i++){
        if(l[i]>d){
            d=l[i];
            v=i;
        }
    }
    // preencher o array p com os vertices desse caminho
    i=d;
    p[i--]=v;
    while(parent[v]>=0){
        v=parent[v];
        p[i--]=v;
    }
    return d;
}

/* 2 */

int componentes(GrafoL g, int c[]){
    int i, component, orig;
    int visit[NV], parent[NV], l[NV];
    // usa o array de input como array de visitados (serve de inicialização)
    DF(g,0,c,parent,l);
    component = 1; //componentes ja processados
    do{
        for(orig=0; orig<NV && c[orig]; orig++);
        if(orig<NV){
            DF(g,orig,visit,parent,l); //agora o array de visitados ja e diferente do c
            component++; //aumenta o nr de componentes processadas
            //copia info dos visitados para o array c
            for(i=0; i<NV;i++){
                if(visit[i]) c[i] = component;
            }
        }
    } while (orig<NV);
    return component;
}

/* 3 
int ordTop(GrafoL g, int ord[]){
    int i;
    int visit[], parent[], l;

}*/

/* Q4 2 teste 19/20 */

//calcula o custo do caminho do grafo g constituido por k vertices armazenados no array v 
int pesoC(GrafoM g, int v[], int k){
    int i, a, b, custo = 0;
    for(i=0; i<k-1; i++){
        a = v[i]; b = v[i+1];
        if(g[a][b] != NE){ //NE esta no teste como utilizado para representar arestas inexistentes
            custo += g[a][b];
        }
        else return -1;
    }
    return custo;
}

/* Q5 2 teste 19/20 */
/* (i) */

void componentes(GrafoL g, int n, int comp[]){
    int i, component = 0, parent[n];
    for(i=0; i<n; i++) comp[i] = -1; //array para controlar a travessia
    for(i=0; i<n; i++){
        if(comp[i] == -1){
            DF(g,i,comp,parent,component);
            component++;
        }
    }
}

/* Exame 2019/2020 */
/* Q3 */

typedef enum balancefactor { LH, EH, TH } BalanceFactor;

typedef struct treenode {
    BalanceFactor bf; // indice de equilibrio AVL
    int entry; // inteiro guardado no no
    int n_elems; // nr de elementos desta arvore
    struct treeNode *left, *right;
} *Tree;

// (i) funcao de rotacao a esquerda
Tree rotateLeft(Tree t){
    Tree aux = t->right;
    t->n_elems = (t->left != NULL ? (t->left)->n_elem : 0) + ((t->right!= NULL ? (t->right)->n_elem : 0)) + 1;
    aux->left = t;
    aux->n_elems = (t->left != NULL ? (t->left)->n_elem : 0) + ((t->right!= NULL ? (t->right)->n_elem : 0)) + 1;
    t=aux;
    return aux;
}

// (ii) dado um inteiro x, contar o nr de elementos igual ao inferior a ele na tree
int rank(Tree t, int x){
    int count = 0;
    while(t){
        if(t->entry <= x) count++;
        rank(t->left,x);
        rank(t->right,x);
    }
    return count;
}

/* Q4 */

int count_reachable(GrafoM g, int s, int n){
    int i, j;
    for(i=0; i<MAX; i++){
        for(j=0; j<MAX; j++){
            
        }
    }
}