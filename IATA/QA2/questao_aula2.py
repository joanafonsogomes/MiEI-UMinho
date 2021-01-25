import csv
import networkx as net
import collections
import matplotlib.pyplot as plt
from termcolor import colored
import time

########## ABRIR E PROCESSAR O FICHEIRO (codigo fornecido) ##########

in_file=csv.reader(open('lista_arestas.txt','r'))

g=net.Graph()
for line in in_file:
    g.add_edge(line[0],line[1],weight=line[2],conf=line[3])

# NODOS DO GRAFO
all_nodos = list(g.nodes) 

########## CRIAR GRAFO COM AS INFORMAÇÕES DO FICHEIRO .TXT ########## 

# Posicoes para todos os nodos
pos = net.circular_layout(g)

# Ajustar tamanho da figura
plt.figure(figsize=(50,50))

# Nodos
net.draw_networkx_nodes(g, pos, node_size=50)

# Arestas
net.draw_networkx_edges(g, pos, width=0.5, alpha=0.5, edge_color='b')

# Labels
net.draw_networkx_labels(g, pos, font_size=7.5, font_family='FreeMono', font_weight='bold')

plt.axis('off')
plt.show();

## Distribuicao de Graus ##

grau_seq = sorted([gr for n, gr in g.degree()], reverse=True)

grau_count = collections.Counter(grau_seq)
grau, count = zip(*grau_count.items())

fig, ax = plt.subplots()
plt.bar(grau, count, width=0.80, color="b")

# Labels
plt.title("Distribuição de grau")
plt.ylabel("Contador")
plt.xlabel("Grau")
ax.set_xticks([gr + 0.4 for gr in grau])
ax.set_xticklabels(grau)

plt.show()


########## DIAMETRO ##########
print(colored('\n ########## CÁLCULO DO DIÂMETRO ########## \n', 'red'))
time.sleep(3)

S = [g.subgraph(c).copy() for c in net.connected_components(g)]

for s in S:
    print(net.diameter(s))

sub = 0
for s in S:
    if (net.diameter(s)) > sub:
        sub = net.diameter(s)

print("\n",colored('> O diâmetro do grafo g é', 'blue'),colored(sub, 'blue'),"\n")

time.sleep(10)

########## DISTANCIA ##########
print(colored('\n ########## DISTANCIA ########## \n', 'red'))
time.sleep(1)

## Grau de um nodo ##

print(colored('\n GRAUS DE TODOS OS NODOS\n', 'red'))
time.sleep(3)
for n in all_nodos:
    degree = net.degree(g,n)
    print(n,":",degree)
    time.sleep(0.05)

time.sleep(10)

## Shortest Path 2 nodos ##

print(colored('\n \n SHORTEST PATH ENTRE DOIS NODOS \n', 'red'))
time.sleep(3)

#Listagem dos nodos para escolha do user
ind = 0
for n in all_nodos:
    print(ind,":",n)
    time.sleep(0.05)
    ind += 1
print("\n")

val1 = input("Escolha o primeiro nodo usando a numeração acima: ")
val2 = input("Escolha o segundo nodo: ")

if (int(val1) < len(all_nodos)) and (int(val2) < len(all_nodos)):
    nodo1 = all_nodos[int(val1)]
    nodo2 = all_nodos[int(val2)]
    try:
        net.shortest_path(g, nodo1, nodo2)
        sp = net.shortest_path(g, nodo1, nodo2)
        spl = net.shortest_path_length(g, nodo1, nodo2)
        print("\n")
        print(colored('> Caminho mais pequeno entre os nodos escolhidos:', 'blue'),sp)
        print(colored('> Comprimento:', 'blue'),spl)
    except:
        print(colored('\n > Não existe path entre os dois nodos escolhidos!', 'blue'))
else :
    print("\n > Os nodos inseridos são inválidos.")

time.sleep(10)

## DISTANCIA DE UM NODO PARA TODOS OS OUTROS ##

print(colored('\n \n DISTÂNCIA DE UM NODO PARA TODOS OS OUTROS \n', 'red'))
time.sleep(3)

# BFS #

print(colored('\n \n 1. BREADTH FIRST SEARCH \n', 'red'))
time.sleep(3)

#Listagem dos nodos para escolha do user

ind = 0
for n in all_nodos:
    print(ind,":",n)
    time.sleep(0.05)
    ind += 1
print("\n")
val = input("Insira o nodo usando a numeração acima: ")

plt.figure(figsize=(100,50))

if int(val) < len(list(g.nodes)):
    try:
        nodo = all_nodos[int(val)] 
        S = net.bfs_tree(g,nodo)
        net.draw_networkx(S)
        print(colored('\n A apresentar a árvore BFS para o nodo', 'blue'),colored(nodo, 'blue'),colored("...", 'blue'))
        time.sleep(4)
        plt.title("BFS")
        plt.axis('on')
        plt.show()
    except:
        print("ERRO")
else :
    print("\n > Nodo inválido.")


# DFS #

print(colored('\n \n 2. DEPTH FIRST SEARCH \n', 'red'))
time.sleep(3)

#Listagem dos nodos para escolha do user
ind = 0
for n in all_nodos:
    print(ind,":",n)
    time.sleep(0.05)
    ind += 1
print("\n")
val = input("Insira o nodo usando a numeração acima: ")

plt.figure(figsize=(100,50))

if int(val) < len(list(g.nodes)):
    try:
        nodo = all_nodos[int(val)] 
        S = net.dfs_tree(g,nodo)
        net.draw_networkx(S)
        print(colored('\n A apresentar a árvore DFS para o nodo', 'blue'),colored(nodo, 'blue'),colored("...", 'blue'))
        time.sleep(4)
        plt.title("DFS")
        plt.axis('on')
        plt.show()
    except:
        print("ERRO")
else :
    print("\n > Nodo inválido.")

## Maior distância entre um nodo e todos os outros (eccentricy) ##

print(colored('\n \n ECCENTRICY \n', 'red'))
time.sleep(3)

S = [g.subgraph(c).copy() for c in net.connected_components(g)]

#Listagem dos nodos para escolha do user
ind = 0
for n in all_nodos:
    print(ind,":",n)
    time.sleep(0.05)
    ind += 1
print("\n")
val = input("Insira o nodo usando a numeração acima: ")

if int(val) < len(list(g.nodes)):
    nodo = all_nodos[int(val)] 
    for s in S:
        try:
            dist = net.eccentricity(s,nodo)
            if(dist) :
                print(colored('\n > A maior distância entre o nodo','blue'), colored(nodo,'blue'), colored('e todos os outros é','blue'), colored(dist,'blue'))
        except:
            print("erro")
else :
    print("\n > Nodo inválido.")

time.sleep(10)

########## MEDIDAS DE CENTRALIDADE ##########

print(colored('\n \n ##########  MEDIDAS DE CENTRALIDADE ##########', 'red'))

time.sleep(3)

# Degree centrality (o número de conecções de um nodo para todos os outros)
print(colored('\n \n CENTRALIDADE DO GRAU \n', 'red'))
time.sleep(3)
print(net.degree_centrality(g))
time.sleep(0.5)

# Eigenvector centrality (o quão importante é um nodo em função de quão bem conectado está)
print(colored('\n \n EIGENVECTOR CENTRALITY \n', 'red'))
time.sleep(3)
print(net.eigenvector_centrality(g))
time.sleep(0.5)

# Closeness centrality (importância de um nodo em função da sua proximidade com os outros da rede)
print(colored('\n \n CLOSENESS CENTRALITY \n', 'red'))
time.sleep(3)
print(net.closeness_centrality(g))
time.sleep(0.5)

# Betweeness centrality (quantifica quantas vezes um nodo aparece nos caminhos mais curtos entre dois nodos)
print(colored('\n \n BETWEENESS CENTRALITY \n', 'red'))
time.sleep(3)
print(net.betweenness_centrality(g))