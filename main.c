/// Aline, Gabriel, Gessica & Mayra
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
    int numLimitados;
    int numVertices;
    int* ListLim;
    nodo** ListAdj;
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



int main()
{
    grafo** grafos;                                             //Array de endeeços de grafo
    grafo* grafoA;                                              //Recebe o grafo endereçado correto
    int numCampi, numVertices ,i= 0,j = 0, soma = 0;
    prioNodo *filaQ;                                            //Fila de prioridade


    system("clear");                                            //Limpa a tela em Linux

    scanf("%d",&numCampi);                                      //Pega o numero de campi

    grafos = malloc(numCampi * sizeof(grafoA));                //Aloca espaço para os grafos


    while(i<numCampi){

        grafos[i] = malloc(numCampi* sizeof(grafo));

        scanf("%d",&numVertices);                                //Pega o número de vertices

        grafos[i]= input(grafos[i], numVertices);              //Pega as informações do grafo


      i++;
    }

    system("clear");                                           //Limpa a tela em Linux
    while(j < numCampi ){


        grafoA = grafos[j];                                 //Pega o grafo correto coloca em grafoA
        numVertices = grafoA->numVertices;


        filaQ = malloc(numVertices *  sizeof(prioNodo));     //Aloca espaço na fila de prioridade


        grafoA = atualizaLimitados(grafoA);                 //Remove todas as arestas dos limitados, menos a menor aresta que não está conectada a um limitado

        filaQ = AGM_Prim(grafoA,filaQ , 0);                 //Realiza o algoritmo de prim


        for(i=0;i<numVertices;i++){                         //Soma todos os valores da listaDePrioridade
            soma += filaQ[i].chave;

        }


        printf("Campus %d: %d\n",j+1, soma);                //Imprime o resultado da soma
        soma = 0;                                           //Zera a soma
        j++;


        //LIBERACAO DE MEMORIA//////////////////////////////////////////////////
        grafoA = liberaVizinhos(grafoA);
        free(grafoA->ListAdj);
        free(grafoA->ListLim);
        free(grafoA);
        free(filaQ);
        ///////////////////////////////////////

    }



    return 0;
}
