#ifndef CARTEPRIM_h
#define CARTEPRIM_h
#include "ELTPRIM.h"
#include "LSTSDD1.h"

Node1 createNode1(ELEMENT e, float weight);
Carte createCarte();
void addEdge1(Carte C, ELEMENT src, ELEMENT dest, float weight);//bsh tarbet deux noeuds b baabdhhom
void printCarte(Carte G);
void shortestPath1(Carte G, char source[30], char dest[30]);//ou void shortestPath(Graph G, char* source, char* dest);
//Les fonctions auxiliaires getNodePosition et minDistance
int getNodePosition(Carte C, char nom[30]);
int minDistance(int dist[], int visited[], int n);

#endif
