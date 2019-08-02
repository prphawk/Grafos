#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"


//ALGORITMO DE PRIM

prioNodo* AGM_Prim(grafo* grafo , prioNodo* filaQ, int raiz){
//Executa o algoritomo de prim

    int numVertices = grafo->numVertices;

    prioNodo *u;         //nodo que retiramos da fila
    int verticeU;        //Valor do vertice de U
    nodo *vizinho;       //Lista de vizinhos
    int vertViz;         //Vertice do Vizinho
    int vizId;


    filaQ = iniFilaPrio(filaQ, numVertices);                                       //Inicializa a fila de prioridade

    filaQ[raiz].chave = 0;

    filaQ = organizaFilaPrio(filaQ,numVertices);                                   //r.chave = 0



    while( u = extraiFilaPrio(filaQ,numVertices)){                                  //Pega o primeiro da fila, se for NULL acabo o while
        verticeU = u->vertice;
        vizinho = grafo->ListAdj[u->vertice];                                       //Coloca os vizinhos de u em vizinho

        while(vizinho != NULL){
            vertViz = vizinho->vertice;              //Vertice do vizinho na lista de adjacencia
            vizId = achaId(vertViz,filaQ);           //Encontra o ID do vertice na lista de prioridade


            if( filaQ[vizId].retirado == 0 &&  aresta(grafo,vertViz, verticeU) < filaQ [vizId].chave) {
                //Se o vizinho está na lista && a distancia entre ele e u for menor que sua chave


                filaQ[vizId].pred = verticeU;                              //Coloca u como predecessor
                filaQ[vizId].chave = aresta(grafo,vertViz,verticeU);       //Coloca a distancia entre u e o vertice como chave
                filaQ = organizaFilaPrio(filaQ,numVertices);


            }

            vizinho = vizinho->prox;

        }

    }

    return filaQ;
}


grafo* liberaVizinhos(grafo* grafoA){

    int i;

    for(i=0;i<grafoA->numVertices;i++){
        grafoA->ListAdj[i] = destroiLista(grafoA->ListAdj[i]);
    }

    return grafoA;
}

nodo* destroiLista(nodo* ptLista){
    //LIBERA A LISTA DE VIZINHO
    nodo *ptaux; //ponteiro auxiliar para percorrer a lista

    while (ptLista != NULL)
    {
        ptaux = ptLista;
        ptLista = ptLista->prox;

        if(!ptaux)
            free(ptaux);
    }
    free(ptLista);

    return NULL;
}



//FUNÇÕES PARA LIMITADOS
grafo* atualizaLimitados(grafo *grafo){
 //Remove todas as aresta que conectam 2 limitados e remove todas menos a menor de todos os limitados,
    int numLimitados = grafo->numLimitados;
    int vertMenorAresta;
    int limitado;
    int i;
    nodo* nodoMenorAresta;
    nodo* aux;


   // printf("Num Limitados: %d \n", numLimitados);

    for(i=0;i< numLimitados;i++){

        limitado = grafo->ListLim[i];                   //Pega o vertice do limitado
        aux = grafo->ListAdj[limitado];                 //Pega a lista de vizinhos do limitado
        nodoMenorAresta = menorAresta(grafo,limitado);
        vertMenorAresta = nodoMenorAresta->vertice;      //Pega o vertice de menor aresta do limitado


        while(aux){

            if(aux->vertice != vertMenorAresta ){
                grafo = removeAresta(grafo,aux->vertice,limitado);   //Remove todas as arestas menos a menor do limitado
           }

            aux = aux->prox;

        }


        //printf("Limitado Feito: %d ",i);

    }

    return grafo;


}

int ehLimitado(int vert, grafo *grafo){
//Retorna 1 se um vertice for limitado, 0 se não
    int i;

    for(i=0;i<grafo->numLimitados;i++){//Se achar o limitado retorna 1
        if(grafo->ListLim[i] == vert){
            return 1;
        }

    }
    return 0;                           //Se não retorna 0
}



nodo* menorAresta(grafo* grafo, int vertice) //retorna o NODO que está ligado pela menor aresta, NÃO RETORNA LIMITADOS
{
    int menor = INT_MAX;
    nodo* resposta = NULL;
    nodo* aux = grafo->ListAdj[vertice];


    while(aux) //percorre sublista
    {
        if(aux->aresta < menor && !ehLimitado(aux->vertice, grafo))    //Se for menor e não for limitado
        {
            menor = aux->aresta;                                   //Atualiza resposta e menor
            resposta = aux;
        }

        aux = aux->prox;
    }


    return resposta;
}


grafo* removeAresta(grafo* grafo,int vertice1,int vertice2)
{
    if(vertice1 == vertice2){
        printf("Nenhum laço eh permitido.\n");
        grafo = removeNodo(grafo,vertice1,vertice2);            //Para remover a aresta, remove o nodo da lista de vizinho dos dois vertices
        return grafo;
    }

    grafo = removeNodo(grafo,vertice1,vertice2);            //Para remover a aresta, remove o nodo da lista de vizinho dos dois vertices
    grafo = removeNodo(grafo,vertice2,vertice1);

    return grafo;
}

grafo* removeNodo(grafo* grafo,int vertice1,int vertice2){

    nodo* aux = grafo->ListAdj[vertice1];;
    nodo* ant = NULL;

    while (aux !=NULL && aux->vertice != vertice2)  //Procura o vertice2
	{
		ant = aux;
        aux = aux->prox;
	}

    if(aux == NULL){                               //Nada acontece
       return grafo;

    }
    if(ant == NULL){                                //Se ant null,remove o primeiro elemento
        grafo->ListAdj[vertice1] = aux->prox;

    }
    else{                                           //Vai remover no meio
        ant->prox = aux->prox;
    }



    return grafo;
}

//FUNÇÕES PARA A FILA DE PRIORIDADE

int achaId(int vertViz , prioNodo *filaDePrioridade){
//FUNÇÃO RETORA O ID DE UM VERTICE NA FILA DE PRIORIDADE

    int i = 0;


    while(1){                                       //Procura pelo vertice, se encontrar, retorna seu ID
        if(vertViz == filaDePrioridade[i].vertice){
            return i;
        }

        i++;
    }

    return -1;
}



prioNodo* organizaFilaPrio (prioNodo *filaDePrioridade, int numVertices){
//Organiza a fila utilizando um algoritmo de insertion sort
    int i,j;
    prioNodo nodoAux;

   for (i = 1; i < numVertices; i++)
   {
       nodoAux = filaDePrioridade[i];
       j = i-1;

       while (j >= 0 && filaDePrioridade[j].chave > nodoAux.chave)
       {
           filaDePrioridade[j+1] = filaDePrioridade[j];
           j = j-1;
       }
       filaDePrioridade[j+1] = nodoAux;
   }

    return filaDePrioridade;
}

prioNodo* extraiFilaPrio(prioNodo *filaDePrioridade, int numVertices){    //Retorna o primeiro da fila de prioridade
//Retorna o primeiro nodo da fila, marca esse nodo como retirado
    int i;

    for(i=0; i<numVertices;i++){

        if(filaDePrioridade[i].retirado == 0){  //Se não foi retirado
            filaDePrioridade[i].retirado = 1;
            return &filaDePrioridade[i];
        }
    }

    return NULL;

}

prioNodo* iniFilaPrio(prioNodo *filaDePrioridade , int numVertices){ //Inicializa a fila de prioridade
//Inicia a fila de prioridade

    int i;
    int infinito = INT_MAX;



    for(i=0;i<numVertices;i++){
        filaDePrioridade[i].vertice = i;              //Cada vertice deve ser contado
        filaDePrioridade[i].chave = infinito;           //Inicia com infinito
        filaDePrioridade[i].pred = -1;                //Ainda não definido
        filaDePrioridade[i].retirado = 0;
    }


    return filaDePrioridade;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//FUNÇÕES GERAIS DO GRAFO

int aresta(grafo* grafo,int vertice1,int vertice2){ //devolve o valor da aresta entre dois nodos, entra na sublista do nodo que achar primeiro


    nodo* aux;
    int infinito = INT_MAX;

    aux =  grafo->ListAdj[vertice1];                //Aux é a lista de vizinhos de vertice1

    while(aux != NULL){                             //Procura vertice2 na lista de vizinhos, se encontrar, retorna a aresta
        if(aux->vertice == vertice2){
            return aux->aresta;
        }

        aux = aux->prox;
    }
    //Vamos testar ao contrario

    aux =  grafo->ListAdj[vertice2];                //Aux é a lista de vizinhos de vertice 2

     while(aux != NULL){                            //Procura vertice1 na lista de vizinhos, se encontrar retorna aresta
        if(aux->vertice == vertice1){
            return aux->aresta;
        }

        aux = aux->prox;
    }



    printf("\nEstes vertices nao estao ligados: %d %d\n", vertice1+1, vertice2+1);    //Se eles não estão ligados, retorna infinito
    return infinito;
}

grafo* input(grafo* grafo, int numVertices)
{
    grafo = cria_grafo(numVertices,grafo);

    inMatriz(grafo); //pega a matriz de adjacencia

    inLimitados(grafo); //pega a lista de limitados

    return grafo;
}


void inLimitados(grafo* grafo)
{
    int i, limitado;
    int numLimit;

    scanf("%d",&numLimit);


    grafo->ListLim = malloc(numLimit * sizeof(int)); //Libera espaço para a lista de limitados
    grafo->numLimitados = numLimit;




    if(grafo->numLimitados)
    {


        for(i = 0; i < grafo->numLimitados; i++){

            scanf("%d",&limitado);
            limitado--;                         //VERTICE 1 TERÁ INDICE 0 etc..
            grafo->ListLim[i] = limitado;



        }
    }



}

void inMatriz(grafo* grafo)
{
    int i,j,aresta;

    for(i = 0; i < grafo->numVertices; i++)
    {

        for(j = 0; j < grafo->numVertices; j++)
        {

            scanf("%d",&aresta);
            if(aresta && j >= i )                   //ADICIONA AO GRAFO AS ARESTAS LIDAS
                add_aresta(grafo, i, j, aresta);



        }

    }

}

nodo* cria_nodo(int num_nodo, int aresta)
{
    //Aloca um nodo na memoria, inicializa ele
    nodo* new_nodo;

    new_nodo = malloc(sizeof(nodo));
    new_nodo->vertice = num_nodo;
    new_nodo->aresta = aresta;
    new_nodo->prox = NULL;

    return new_nodo;
}

grafo* cria_grafo(int numVertices, grafo *g)
{
    int i;

    g = malloc(sizeof(grafo));                          //Aloca o grafo

    g->ListAdj = malloc(numVertices * sizeof(nodo*));   //Aloca a lista de adjacencia


    g->numVertices = numVertices;                       //Atualizaumero de vertices
    g->numLimitados = 0;
    g->ListLim = NULL;



    for (i = 0; i < numVertices; i++)                   //Inicializa com NULL
        g->ListAdj[i] = NULL;

    return g;
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


