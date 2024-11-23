#ifndef GRPPRIM_H
#define GRPPRIM_H
#include "LSTSDD.h"
#include "ELTPRIM1.h"


Node createNode(ELEMENT1 c , int weight);
Graph createGraph(int V);
void addEdge(Graph G, ELEMENT1 src, ELEMENT1 dest, int weight);//bsh tarbet deux noeuds b baabdhhom
void printGraph(Graph G);
void shortestPath(Graph G, char source, char dest);
int nodePos(Graph G, ELEMENT1 a);

#endif
