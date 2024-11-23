#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ELTPRIM.h"
#include "GRPPRIM.h"
#include "ELTPRIM1.h"
#include "CARTEPRIM.h"

// Function and procedure declarations

Graph creerGraphPersonalise()
{
    char option = '\0';
    int v;
    do
    {
        printf("donner le nombre des noeuds a ajouter\nV = ");
        scanf("%d", &v);
    } while(v < 2);
    Graph G = createGraph(v);
    for(int i = 0; i < G->V; i++)
    {
        printf("Noeud n%i = ", i+1);
        char e;
        scanf(" %c", &e);
        G->adjList[i] = createNode(e, 0);
    }

    //ajouter les arretes
    char src, dst;
    int w;
    do
    {
        system("cls");
        printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~AJOUTER UNE ARRETE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        //lire les informations
        do
        {
            printf("\nDonner une source deja existante dans le Graph\nSource = ");
            scanf(" %c", &src);
        }while(nodePos(G, src) == -1);
        do
        {
            printf("\nDonner une destination deja existante dans le Graph\nDestination = ");
            scanf(" %c", &dst);
        }while(nodePos(G, dst) == -1);
        printf("\nDonner la distance entre les deux noeuds\nPoids = ");
        scanf("%d", &w);
        //addEdge
        addEdge(G, G->adjList[nodePos(G, src)]->info, G->adjList[nodePos(G, dst)]->info, w);
        //donner le choix a creer une autre arrete
        option = '\0';
        printf("Ajouter une autre arrete O/n ");
        scanf(" %c", &option);
    } while(option == 'O' || option == 'o');

    return G;
}

Graph creerGraphDefault()
{
    Graph G = createGraph(6);
    printf("The graph is successfully located.\n");

    // Create 6 nodes
    Node n1 = createNode('A', 0);
    Node n2 = createNode('B', 0);
    Node n3 = createNode('C', 0);
    Node n4 = createNode('D', 0);
    Node n5 = createNode('E', 0);
    Node n6 = createNode('F', 0);
    // Initialize the contiguous array
    G->adjList[0] = n1;
    G->adjList[1] = n2;
    G->adjList[2] = n3;
    G->adjList[3] = n4;
    G->adjList[4] = n5;
    G->adjList[5] = n6;
    // Add edges to the graph
printf("done 510");
    addEdge(G, 'A', 'B', 5);
    addEdge(G, 'A', 'D', 4);
    addEdge(G, 'B', 'E', 4);
    addEdge(G, 'B', 'C', 1);
    addEdge(G, 'C', 'F', 6);
    addEdge(G, 'D', 'E', 2);
    addEdge(G, 'D', 'F', 7);
    addEdge(G, 'E', 'F', 3);

    printf("The graph is successfully created.\n");

    return G;
}


void afficherShortestPath(Graph G)
{
    char source = '\0', destination = '\0';
    int posSrc, posDst;

    do {
        posSrc = nodePos(G, source);
        posDst = nodePos(G, destination);

        if (posSrc == -1) {
            printf("Donner une source du Graph\nsource = ");
            scanf(" %c", &source);
        } else if (posDst == -1) {
            printf("Donner une destination a rechercher du Graph\ndestination = ");
            scanf(" %c", &destination);
        }
    } while (posSrc == -1 || posDst == -1);

    shortestPath(G, G->adjList[posSrc]->info, G->adjList[posDst]->info);
}

void afficherShortestPathC(Carte G)
{
    char source[100], destination[100];
    int posSrc, posDst;
    do {
        posSrc = getNodePosition(G, source);
        posDst = getNodePosition(G, destination);

        if (posSrc == -1) {
            printf("Donner une source de la carte\nsource = ");
            scanf(" %s", &source);
        } else if (posDst == -1) {
            printf("Donner une destination a rechercher dans la carte\ndestination = ");
            scanf(" %s", &destination);
        }
    } while (posSrc == -1 || posDst == -1);

    shortestPath1(G, G->adjList[posSrc]->info->Nom, G->adjList[posDst]->info->Nom );
}



void clearScreen() {
    system("cls");
}

void printMenu() {
    printf("\n====== MENU ======\n");
    printf("1) Utiliser le Graph\n");
    printf("2) Utiliser la carte\n");
    printf("3) Quitter\n");
    printf("===================\n");
}

void printGraphMenu() {
    printf("\n====== GRAPH MENU ======\n");
    printf("1) Utiliser un Graph existant\n");
    printf("2) Creer un nouveau Graph\n");
    printf("3) Quitter\n");
    printf("========================\n");
}

void printGraphOperations() {
    printf("\n====== GRAPH OPERATIONS ======\n");
    printf("1) Afficher le graphe\n");
    printf("2) Chercher un chemin\n");
    printf("3) Retour\n");
    printf("==============================\n");
}

void printCarteOperations() {
    printf("\n====== CARTE OPERATIONS ======\n");
    printf("1) Afficher la carte\n");
    printf("2) Chercher un chemin\n");
    printf("3) Retour\n");
    printf("==============================\n");
}

char enterOption() {
    char option;
    printf("\nEntrez votre choix: ");
    scanf(" %c", &option);
    return option;
}

int main() {
    char option = '\0';
    while (option != '3') {
        clearScreen();
        printMenu();
        option = enterOption();
        switch (option) {
            case '1': {
                Graph G;
                clearScreen();
                printGraphMenu();
                option = enterOption();
                switch (option) {
                    case '1': {
                        G = creerGraphDefault();
                        break;
                    }
                    case '2': {
                        clearScreen();
                        G = creerGraphPersonalise();
                        break;
                    }
                    case '3': {
                        printf("exit...\n");
                        break;
                    }
                    default: {
                        printf("Option invalide.\n");
                        break;
                    }
                }
                option = '\0';
                while (option != '3') {
                    clearScreen();
                    printGraphOperations();
                    option = enterOption();
                    switch (option) {
                        case '1': {
                            clearScreen();
                            printf("Graph:\n");
                            printGraph(G);
                            printf("\n");
                            printGraphOperations();
                            option = enterOption();
                            break;
                        }
                        case '2': {
                            clearScreen();
                            printf("Chemin le plus court:\n");
                            afficherShortestPath(G);
                            printf("\n");
                            printGraphOperations();
                            option = enterOption();
                            break;
                        }
                        case '3': {
                            break;
                        }
                        default: {
                            printf("Option invalide.\n");
                            break;
                        }
                    }
                }
                option = '\0';
                break;
            }
            case '2': {
                Carte G = createCarte();
                option = '\0';
                while (option != '3') {
                    clearScreen();
                    printCarteOperations();
                    option = enterOption();
                    switch (option) {
                        case '1': {
                            clearScreen();
                            printf("Carte:\n");
                            printCarte(G);
                            printf("\n");
                            printCarteOperations();
                            option = enterOption();
                            break;
                        }
                        case '2': {
                            clearScreen();
                            printf("Chemin le plus court:\n");
                            afficherShortestPathC(G);
                            printf("\n");
                            printCarteOperations();
                            option = enterOption();
                            break;
                        }
                        case '3': {
                            break;
                        }
                        default: {
                            printf("Option invalide.\n");
                            break;
                        }
                    }
                }
                option = '\0';
                break;
            }
            case '3': {
                printf("Au revoir!\n");
                break;
            }
            default: {
                printf("Option invalide.\n");
                break;
            }
        }
    }
    return 0;
}


