#include <stdlib.h>
#include <malloc.h>
#include "ELTPRIM.h"
#include "CARTEPRIM.h"


#define INT_MAX 9999
//1
Node1 createNode1(ELEMENT e, float weight){
    Node1 N = (Node1) malloc(sizeof(structNode1));
    N->info = e;
    N->weight = weight;
    N->next = NULL;
    return N;
}
//2
Carte createCarte(){
    Carte C = (Carte) malloc(sizeof(strucCarte));
    if (C == NULL) {
        printf("erreur d'allocation du memoire\n");
        return ;
    }
    C->graphFile = fopen("graph.out", "w");
    if(C->graphFile == NULL)
	{
		fprintf(stderr, "Erreur : Probleme creation du fichier.\n");
		exit(EXIT_FAILURE);
	}
    fprintf(C->graphFile, "graph {\n\
        graph [bgcolor=\"#F8F8F8\"];\n\
        node [style=filled, fontname=\"Arial\", fontsize=12, shape=circle, width=0.8, height=0.8, margin=0.04];\n\
        edge [color=\"#999999\", fontname=\"Arial\", fontsize=10, style=solid];\n\
        rankdir=LR;\n\
        splines=polyline;\n\
        overlap=false;\n\
        sep=0.5;\n\
        ratio=auto;\n\n");

    // decouvrir le nombre des noeuds (C->V)
    char line[100];
    int nbrLignes = 0;
    FILE* countF = fopen("nodes.txt", "r");
    if (countF == NULL) {
        printf("Erreur d'ouverture du fichier nodes.txt\n");
        free(C);
        return ;
    }

    while (fgets(line, sizeof(line), countF) != NULL) nbrLignes++;
    fclose(countF);

    nbrLignes--; // on ne compte pas la premiere ligne
    C->V = nbrLignes;

    // initialiser adjList
    for(int i = 0; i < C->V; i++) {
        C->adjList[i] = NULL;
    }

    // ouvrir nodes.txt
    FILE* fichier = fopen("nodes.txt", "r");
    if (fichier == NULL) {
        printf("Erreur d'ouvrerture du fichier nodes.txt\n");
        free(C);
        return ;
    }

    // ne pas lire la premiere ligne
    fgets(line, sizeof(line), fichier);

    int ouv = 0;
    while (fgets(line, sizeof(line), fichier) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        ELEMENT e = elementCreer();
        if (e == NULL) {
            printf("Erreur d'allocation memoire\n");
            fclose(fichier);
            return NULL;
        }

        strcpy(e->Nom, strtok(line, ":"));
        strcpy(e->dateCreation , strtok(NULL, ":"));
        strcpy(e->population , strtok(NULL, ":"));
        strcpy(e->superficie , strtok(NULL, ":"));
        strcpy(e->nbMunicipalites , strtok(NULL, ":"));
        C->adjList[ouv] = createNode(e, 0);
        if (C->adjList[ouv] == NULL) {
            printf("Erreur : allocation memoire echouee\n");
            fclose(fichier);
            return NULL;
        }
        ouv++;
    }
    fclose(fichier);

    // ouvrir vertices.txt
    FILE* fichier1 = fopen("vertices.txt", "r");
    if (fichier1 == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier vertices.txt\n");
        return NULL;
    }

    while (fgets(line, sizeof(line), fichier1) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        char *srcNom = strtok(line, "*");
        char *dstNom = strtok(NULL, "*");
        char *weightValue = strtok(NULL, "*");

        int srcPos = getNodePosition(C, srcNom);
        if (srcPos == -1){
            printf("%s n'est pas trouve\n", srcNom);
            fclose(fichier1);
            return NULL;
        }

        int dstPos = getNodePosition(C, dstNom);
        if (dstPos == -1){
            printf("%s n'est pas trouve\n", dstNom);
            fclose(fichier1);
            return NULL;
        }


        addEdge1(C, C->adjList[srcPos]->info, C->adjList[dstPos]->info, atof(weightValue));
    }
    fclose(fichier1);

    return C;
}
//3
void addEdge1(Carte C, ELEMENT src, ELEMENT dest, float weight){
    //Recherche de la position de src et dest dans adjList
    int possrc= getNodePosition(C, src->Nom), posdest= getNodePosition(C, dest->Nom);
    //code
    int i;
    //verification si le src et dest existent ou pas
    if (possrc== -1) {
        printf("\n l'element src n'existe pas dans la carte ");
        return 0;
    }
    if (posdest== -1) {
        printf("\n l'element dest n'existe pas dans la carte ");
        return 0;
    }
  // Cr�ation du nouveau noeud
    Node1 newNode1 = createNode1(dest, weight);
    // Ajout de dest de la liste de src
    if (C->adjList[possrc]== NULL){
        C->adjList[possrc]= newNode1;
    }
    else {
        Node1 q = C->adjList[possrc];
        while (q->next!= NULL) {
            q= q->next;
        }
        q->next = newNode1;
    }
    // Cr�ation du nouveau noeud
    newNode1 = createNode1(src, weight);
        Node1 q = C->adjList[posdest];
        while (q->next!= NULL) {
            q= q->next;
        }
        q->next = newNode1;
    fprintf(C->graphFile, "\t%s -- %s[label=%.1f];\n", src->Nom, dest->Nom, weight);
}

//4

//en utilisant les couleurs
/*void printCarte(Carte C){
    // Codes de couleur pour les sommets
    char* colors[] = {"\x1b[31m", "\x1b[32m", "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[37m"};
    int colorIndex = 0;

    for (int i = 0; i < C->V; i++) {
        Node1 p = C->adjList[i];
        printf("%s%s (%.1f) -> ", colors[colorIndex], p->info->Nom, p->weight);
        p = p->next;
        while (p != NULL) {
            printf("-- %s%s (%.1f) ", colors[(colorIndex+1)%7], p->info->Nom, p->weight);
            p = p->next;
        }
        printf("\x1b[0m\n\n"); // Réinitialisation de la couleur à la valeur par défaut
        colorIndex = (colorIndex + 1) % 7; // Passage à la couleur suivante
    }
}*/



void printCarte(Carte C) {
    printf("\n");
    printf("+------------------------------------------------------------+\n");
    printf("|                        Carte des villes                    |\n");
    printf("+------------------------+------------------------+----------+\n");
    printf("| Ville                  | Voisins                | Distance |\n");
    printf("+------------------------+------------------------+----------+\n");

    for (int i = 0; i < C->V; i++) {
        Node1 p = C->adjList[i];

        if (p == NULL) {
            printf("| %-22s | %-22s | %-8s |\n", C->adjList[i]->info->Nom, "-", "-");
            printf("+------------------------+------------------------+----------+\n");
            continue;
        }

        printf("| %-22s | %-22s | %-8.1f |\n", C->adjList[i]->info->Nom, p->info->Nom, p->weight);
        p = p->next;

        while (p != NULL) {
            printf("| %-22s | %-22s | %-8.1f |\n", " ", p->info->Nom, p->weight);
            p = p->next;
        }

        printf("+------------------------+------------------------+----------+\n");
    }
    fprintf(C->graphFile, "}");
    fclose(C->graphFile);
    system("%CD%/graphviz/bin/dotty.exe graph.out");
    system("%CD%/graphviz/bin/dot.exe -Tpng graph.out -o graph.png");
}


//Les fonctions auxiliaires getNodePosition et minDistance
int getNodePosition(Carte C, char nom[]) {
    for (int i = 0; i < C->V; i++) {
        if (strcmp(C->adjList[i]->info->Nom, nom) == 0) {
            return i;
        }
    }
    return -1; // Le noeud n'existe pas dans la carte
}
int minDistance(int dist[], int visited[], int T) {
    int min = INT_MAX, min_index = -1;
    for (int i = 0; i < T; i++) {
        if (visited[i] == 0 && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

//5
void shortestPath1(Carte C, char source[], char dest[]){
    int src = getNodePosition(C, source);
    int dst = getNodePosition(C, dest);
    float distance[C->V];
    int parent[C->V];
    int visited[C->V];
    int i, j, k, w, distmin;
    Node1 n;

    // Initialisation des tableaux distance, parent et visited
    for (i = 0; i < C->V; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }

    // Initialisation de la distance de la source à 0
    distance[src] = 0;

    // Algorithme de Dijkstra
    for (i = 0; i < C->V; i++) {
        distmin = INT_MAX;
        for (j = 0; j < C->V; j++) {
            if (!visited[j] && (distance[j] < distmin)) {
                distmin = distance[j];
                k = j;
            }
        }
        visited[k] = 1;
        n = C->adjList[k];
        while (n != NULL) {
            w = n->weight;
            j = getNodePosition(C,n->info->Nom);
            if ((!visited[j]) && (distance[k] + w < distance[j])) {
                distance[j] = distance[k] + w;
                parent[j] = k;
            }
            n = n->next;
        }
       }

    // Résultat
    if (distance[dst] == INT_MAX) {
        printf("Il n'existe pas de chemin entre ces deux noeuds %s et %s \n", source, dest);
    }
    else {
        printf("Le chemin le plus court entre ces deux noeuds %s et %s : ", source, dest);
        printf("%s", source);
        j = parent[dst];
        int points[C->V];
        int inter = 0;
        while (j != -1) {
            points[inter++] = j;
            j = parent[j];
        }
        inter-=2;
        while (inter >= 0){
            printf(" -> %s", C->adjList[points[inter--]]->info->Nom);
        }
        printf(" -> %s", dest);
        printf("\n La distance est : %.1f Km\n", distance[dst]);
    }
}
