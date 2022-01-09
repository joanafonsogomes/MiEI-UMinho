#  Ficha 3 - ESTRUTURAS DE DADOS

## MIN-HEAPS
Uma min-heap é uma árvore binária em cada nodo é menor ou igual a todos os seus sucessores.

##### (1) Expressoes que permitam calcular...

##### (a) O indice onde se encontra a sub-arvore ESQ do nodo da posicao i
2i + 1

##### (b) O indice onde se encontra a sub-arvore DIR do nodo da posicao i
2i + 2

##### (c) O indice onde se encontra o PAI do nodo da posicao i */
(i-1) / 2

##### (d) O indice onde se encontra a primeira folha */
N / 2

##### (2) **BUBBLE-UP** (por sucessivas trocas com o pai, puxa o elemento que esta na posicao i da min-heap h ate que satisfaca a propriedade das min-heaps.

```c
/* Auxs */
int getParent (int i){
    parent = (i-1) / 2;
    return parent;
} 

int left (int i){
    leftChild = 2i + 1;
    return leftChild;
} 

int right (int i){
    rightChild = 2i + 2;
    return rightChild;
} 

void swap (int h[], int a, int b){
    int temp = h[a];
    h[a] = h[b];
    h[b] = temp;
}

void bubbleUp (int i, int h[]){
    int parent = getParent(i);
    while (i >= 0 && h[parent] > h[i]){
        parent = getParent(i);
        swap(h,i,parent);
        i = parent;
    }
}
```

##### Identifique o pior caso desta funcao e calcule o numero de comparacoes/trocas efectuadas nesse caso.
O pior caso é quando o elemento na posicao i é maior do que o elemento que estava na raiz (h[0]). \
O numero de comparações nesse caso é height - 1.

##### (3) **BUBBLE-DOWN** (por sucessivas trocas com um dos filhos, empura o elemento que esta na posicao i da min-heap h ate que satisfaca a propriedade das min-heaps)

```c
void bubbleDown (int i, int h[], int N){
    while(i < N-1){
        childLeft = h[left(i)];
        childRight = h[right(i)];
        int m;
        m = ( childLeft > childRight ) ? childRight : childLeft ; 
        swap(h,i,m);
        i = m;
    }
}
```
##### (4)

```c
#define Max 100
typedef struct pQueue {
int valores [Max];
int tamanho;
} PriorityQueue;
```

* Inicializa q com a fila vazia.

```c
void empty (PriorityQueue *q){
    q->tamanho = 0;
}
```

* Testa se está vazia.

```c
int isEmpty (PriorityQueue *q){
    if(q->tamanho == 0) return 1;
    else return 0;
}
```

* Adiciona um elemento à fila (retornando 0 se a operação or possível).

```c
int add (int x, PriorityQueue *q){
    if (q->tamanho == Max) return 1;
    q->valores[q->tamanho] = x;
    bubbleUp(q->tamanho,q->valores);
    q->tamanho++;
    return 0;
}
```

* Remove o proximo elemento (devolvendo-o em *rem) e retornando 0 se a operacao for possivel.

```c
int rem (PriorityQueue *q, int *rem){
    if(isEmpty(q)) return 1;
    *rem = q->valores[0];
    q->valores[0] = q->valores[q->tamanho - 1];
    q->tamanho--;
    bubbleDown(0,q->valores,q->tamanho);
    return 0;
}
```

<img src="https://github.com/joanafonsogomes/miei/blob/master/AlgC/images/ex4.jpeg" alt="ex4" width="400"/>
