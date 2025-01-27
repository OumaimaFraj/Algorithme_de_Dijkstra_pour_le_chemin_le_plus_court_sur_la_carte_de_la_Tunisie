#ifndef LSTCARTE_H
#define LSTCARTE_H

#include "ELTPRIM.h"
#define MAX_NODES1 25
// Structure pour les n�uds du carte avec poids=les gouvernorats
typedef struct structNode1 {
 ELEMENT info; // Valeur du n�ud:les donn�es de chaque gouvernorat
 float weight; // Poids de l'ar�te=distance
 struct structNode1* next; // Pointeur vers le prochain n�ud dans la liste de voisins
} structNode1, *Node1;
// D�finition de la structure de carte utilisant la liste d'adjacence
typedef struct {
int V; // Nombre de n�uds dans le graphe
FILE* graphFile;
Node1 adjList[MAX_NODES1]; // Tableau de n�uds pour la liste d'adjacence
} strucCarte, *Carte;
//not sue if je dois d�clarer une structure AdjList:liste chain�
#endif
