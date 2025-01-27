#ifndef LSTGRP_H
#define LSTGRP_H
#include "ELTPRIM1.h"

#define MAX_NODES 50
// Structure pour les n�uds du graphe avec poids
typedef struct structNode {
 ELEMENT1 info; // Valeur du n�ud
 int weight; // Poids de l'ar�te
 struct structNode* next; // Pointeur vers le prochain n�ud dans la liste de voisins
} structNode, *Node;
// D�finition de la structure de graphe utilisant la liste d'adjacence
typedef struct {
int V;// Nombre de n�uds dans le graphe
Node adjList[MAX_NODES]; // Tableau de n�uds pour la liste d'adjacence:chaque case hya noeud head
FILE* graphFile;
} strucGraph, *Graph;
#endif
