#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Tnodo
{
    int vertice; // nº do vértice
    int aresta; // tamanho da aresta
    struct  Tnodo* prox;
};
typedef struct Tnodo nodo;

struct Tgrafo
{
    int numLimitados;       //n limitados do grafo
    int numVertices;        //n vertices do grafo
    int* ListLim;           //ponteiro para a lista de limitados
    nodo** ListAdj;         //lista de adjacencia
};
typedef struct Tgrafo grafo;

//A estrutura que será usada para fazer a fila de prioridade
struct TprioNodo
{
    int vertice;        //Vertice que este nodo representa
    int chave;          //Chave do nodo, a fila será ordenada de acordo
    int pred;           //Predecessor deste nodo no grafo criado por prim
    int retirado;     //1 se o nodo ja foi retirado, 0 se não

};
typedef struct TprioNodo prioNodo;


nodo* cria_nodo(int num_nodo, int aresta);
grafo* cria_grafo(int vertices, grafo* g);
void add_aresta(grafo* grafo, int src, int dest, int aresta);
void inMatriz(grafo* grafo);
grafo* input(grafo* grafo, int numVertices);
void inLimitados(grafo* grafo);
nodo* menorAresta(grafo* grafo, int vertice);
grafo* removeNodo(grafo* grafo,int vertice1,int vertice2);
grafo* removeAresta(grafo* grafo,int vertice1,int vertice2);
int aresta(grafo* grafo,int vertice1,int vertice2);

prioNodo* iniFilaPrio(prioNodo *filaDePrioridade ,int numVertices);
prioNodo* extraiFilaPrio(prioNodo *filaDePrioridade,  int numVertices);
prioNodo* organizaFilaPrio (prioNodo *filaDePrioridade, int numVertices);

grafo* atualizaLimitados(grafo *grafo);

prioNodo* AGM_Prim(grafo* grafo , prioNodo* filaQ, int raiz);

int achaId(int vertViz , prioNodo *filaDePrioridade);
int ehLimitado(int vert, grafo *grafo);
void print_grafo(grafo* grafo);

grafo* liberaVizinhos(grafo* grafo);
nodo* destroiLista(nodo* ptLista);
