#include<stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "GRPPRIM.h"
#include "ELTPRIM1.h"

#define INT_MAX 9999
//1
Node createNode(ELEMENT1 e, int weight) {
Node N = (Node) malloc(sizeof(structNode));
    N->info = e;
    N->weight = weight;
    N->next = NULL;
    return N;
}
//2
Graph createGraph(int V){
    Graph G = (Graph) malloc(sizeof(strucGraph));
    G->V = V;
    for (int i = 0; i < V; i++) {
        G->adjList[i]= NULL;//ou G->adjList[i].head = NULL;
    }
    G->graphFile = fopen("graph.out", "w");
    if(G->graphFile == NULL)
	{
		fprintf(stderr, "Erreur : Probleme creation du fichier.\n");
		exit(EXIT_FAILURE);
	}
fprintf(G->graphFile, "graph {\n\
    graph [bgcolor=\"#F8F8F8\"];\n\
    node [style=filled, fontname=\"Arial\", fontsize=12, shape=circle, width=0.8, height=0.8, margin=0.04];\n\
    edge [color=\"#999999\", fontname=\"Arial\", fontsize=10, style=solid];\n\
    rankdir=LR;\n\
    splines=polyline;\n\
    overlap=false;\n\
    sep=0.5;\n\
    ratio=auto;\n\n");
    return G;
}
//3
void addEdge(Graph G,ELEMENT1 src, ELEMENT1 dest, int weight)
{

    int posSrc= nodePos(G, src), posDst= nodePos(G, dest);

    //verification si le src et dest existent ou pas
      if (posSrc== -1) {
          printf("\n la source n'est pas trouvé ");
          return 0;
      }
      if (posDst== -1) {
          printf("\nla destination n'est pas trouvé ");
          return 0;
      }
      Node newNode = createNode(dest, weight);
      // Ajout de dest � la liste de src
        Node q = G->adjList[posSrc];
          while (q->next != NULL) {
              q= q->next;
          }
          q->next = newNode;
      newNode = createNode(dest, weight);
       q = G->adjList[posDst];
      while (q->next != NULL) {
          q= q->next;
      }
      q->next = newNode;


      newNode = createNode(src, weight);
      while (q->next == NULL) {
        q= q->next;
      }
      q->next = newNode;
      fprintf(G->graphFile, "\t%c -- %c[label=%d];\n", src, dest, weight);
}

//4
void printGraph(Graph G){

    for (int i = 0; i < G->V; i++) {
        Node p = G->adjList[i];
        printf("%c -> ", p->info);
        if (p->next!=NULL) p = p->next;
        while (p != NULL) {
            printf("%c (%d) ", p->info, p->weight);
            if (p->info > i) { // avoid printing the same edge twice
            }
            p = p->next;
        }
        printf("\n");
    }
    fprintf(G->graphFile, "}");
    fclose(G->graphFile);
    system("%CD%/graphviz/bin/dotty.exe graph.out");
    system("%CD%/graphviz/bin/dot.exe -Tpng graph.out -o graph.png");
}

/*
void printGraph(Graph G){
    FILE* file = fopen("graph.out", "w");
    if(file == NULL)
	{
		fprintf(stderr, "Erreur : Probleme creation du fichier.\n");
		exit(EXIT_FAILURE);
	}
	fprintf(file, "digraph my_graph\n{\n");





    for (int i = 0; i < G->V; i++) {
        Node p = G->adjList[i];
        printf("%c -> ", p->info);
        while (p != NULL) {
            printf("%c (%d) ", p->info, p->weight);
            p = p->next; // ajout de cette instruction
        }
        printf("\n"); // ajout pour avoir un saut de ligne entre chaque liste de voisins
    }

}

*/
//5
void shortestPath(Graph G, char source, char dest){//affichage de shema et distance
    int src = nodePos(G, source);
    int dst = nodePos(G, dest);
    int distance[G->V];
    int parent[G->V];
    int visited[G->V];
    int i, j, k, w, distmin;
    Node n;

    // Initialisation des tableaux distance,parent et visited
    for (i = 0; i < G->V; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }

    // Initialisation de la distance de la source à 0
    distance[src] = 0;

    // Algorithme de Dijkstra
    for (i = 0; i < G->V; i++) {
        distmin = INT_MAX;
        for (j = 0; j < G->V; j++) {
            if (!visited[j] && (distance[j] < distmin)) {
                distmin = distance[j];
                k = j;
            }
        }
        visited[k] = 1;
        n = G->adjList[k];
        while (n != NULL) {
            w = n->weight;
            j = nodePos(G, n->info);
            if ((!visited[j]) && (distance[k] + w < distance[j])) {
                distance[j] = distance[k] + w;
                parent[j] = k;
            }
            n = n->next;
        }
    }

   // Resultat
    if (distance[dst] == INT_MAX) {
        printf("Il n'existe pas de chemin entre ces deux nouds %c et %c \n", source, dest);
    }
    else {
        printf("Le chemin le plus court entre ces deux nouds %c et %c : ", source, dest);
        printf("%c", source);
        j = parent[dst];
        int points[G->V];
        int inter = 0;
        while (j != -1) {
            points[inter] = j;
            inter++;
            j = parent[j];
        }
        inter-=2;
        while (inter >= 0){
            printf(" -> %c", G->adjList[points[inter--]]->info);

        }
        printf(" -> %c", dest);
        printf("\nLa distance est : %d\n", distance[dst]);
    }
}

int nodePos(Graph G, ELEMENT1 a)
{
    for (int i = 0; i < G->V; i++) {
        if (G->adjList[i]->info == a){
            return i;
        }
    }
    return -1;
}
