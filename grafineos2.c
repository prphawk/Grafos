/// Aline, Gabriel, Gessica & Mayra

#include <stdio.h>
#include <stdlib.h>

struct Tnodo
{
    int vertice; // nº do vértice
    int aresta; // tamanho da aresta
    struct  Tnodo* prox;
};
typedef struct Tnodo nodo;

struct Tgrafo
{
    int numVertices;
    int numLimitados;
    int* ListLim;
    nodo** ListAdj;
};

typedef struct Tgrafo grafo;

nodo* cria_nodo(int num_nodo, int aresta);
grafo* cria_grafo(int vertices);
void add_aresta(grafo* grafo, int src, int dest, int aresta);
void print_grafo(grafo* grafo);
void inMatriz(grafo* grafo);
grafo* input(grafo* grafo);
void inLimitados(grafo* grafo);
int aresta(grafo* grafo,int vertice1,int vertice2);


int main()
{
    grafo* grafo;

        //printf("\n Numero de campi: ");
        //scanf("%d",&numCampi);

        grafo = input(grafo);

        print_grafo(grafo);

    return 0;
}

int aresta(grafo* grafo,int vertice1,int vertice2){ //devolve o valor da aresta entre dois nodos, entra na sublista do nodo que achar primeiro

    int v;
    nodo* aux;

    for(v = 0; v < grafo->numVertices; v++) //percorre lista principal
    {
        if(v == vertice1)
        {
            aux = grafo->ListAdj[v];
                while (aux) //percorre sublista
                {
                    if(aux->vertice == vertice2)
                        return aux->aresta;
                    aux = aux->prox;
                }
            puts("\n N achamos o vert 2 na sublista de 1, tentando com o vertice 2...");
        }
        if(v == vertice2)
        {
            aux = grafo->ListAdj[v];
                while (aux)
                {
                    if(aux->vertice == vertice1)
                        return aux->aresta;
                    aux = aux->prox;
                }
        }
    }
    puts("\n Estes vert n estao ligados!");
    return 0;
}

grafo* input(grafo* grafo)
{
    int numVertices;

    printf("\n Numero de vertices: ");
    scanf("%d",&numVertices);

    grafo = cria_grafo(numVertices);

    inMatriz(grafo); //pega a matriz de adjacencia

    inLimitados(grafo); //pega a lista de limitados

    return grafo;
}

void inLimitados(grafo* grafo)
{
    int i;

    printf("\n Numero de dispositivos limitados do campus 1: ");
    scanf("%d",&grafo->numLimitados);

    fflush(stdin);

    grafo->ListLim = malloc(grafo->numLimitados * sizeof(int));

    printf("\n Lista de dispositivos limitados do campus 1: ");
    for(i = 0; i < grafo->numLimitados; i++)
        scanf("%d",&grafo->ListLim[i]);
}

void inMatriz(grafo* grafo)
{
    int i,j,aresta;

    for(i = 0; i < grafo->numVertices; i++)
    {
        printf("\n Linha de vertice %d: ",i);

        for(j = 0; j < grafo->numVertices; j++)
        {
            scanf("%d",&aresta);
            if(aresta && j >= i)
                add_aresta(grafo, i, j, aresta);
        }
    }
}

nodo* cria_nodo(int num_nodo, int aresta)
{
    nodo* new_nodo;

    new_nodo = malloc(sizeof(nodo));
    new_nodo->vertice = num_nodo;
    new_nodo->aresta = aresta;
    new_nodo->prox = NULL;

    return new_nodo;
}

grafo* cria_grafo(int numVertices)
{
    int i;
    grafo* grafo;

    grafo = malloc(sizeof(grafo));
    grafo->numVertices = numVertices;
    grafo->numLimitados = 0;

    grafo->ListAdj = malloc(numVertices * sizeof(nodo*));
    grafo->ListLim = NULL;

    for (i = 0; i < numVertices; i++)
        grafo->ListAdj[i] = NULL;

    return grafo;
}

void add_aresta(grafo* grafo, int src, int dest, int aresta)
{
    // adiciona dest à lista de adjacência de src
    nodo* new_nodo;
    new_nodo = cria_nodo(dest, aresta);
    new_nodo->prox = grafo->ListAdj[src];
    grafo->ListAdj[src] = new_nodo;

    // adiciona src à lista de adjacência de dest
    new_nodo = cria_nodo(src, aresta);
    new_nodo->prox = grafo->ListAdj[dest];
    grafo->ListAdj[dest] = new_nodo;
}

void print_grafo(grafo* grafo)
{
    int v;
    for (v = 0; v < grafo->numVertices; v++)
    {
        nodo* aux = grafo->ListAdj[v];
        printf("\n Lista de adjacencia do vertice %d:\n", v);
        while (aux)
        {
            printf("  - Vertice: %d, Aresta: %d \n", aux->vertice, aux->aresta);
            aux = aux->prox;
        }
        printf("\n");
    }
}
