#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ELTPRIM.h"
#define ELEMENT_VIDE NULL

ELEMENT elementCreer (void) {
ELEMENT e;
e = (ELEMENT) malloc(sizeof(strucGouvernorat));
return e;
}
void elementDetruire (ELEMENT e) {
free (e);
}

void elementLire(ELEMENT* e) {
char x;
printf(" \n Donner le nom:");
fgets((*e)->Nom,sizeof((*e)->Nom), stdin);//ou  scanf("%99s",(*e)->Nom);
printf(" \n Donner la date de cr�ation:");
scanf("%s",&((*e)->dateCreation));
printf(" \n Donner la population:") ;
scanf("%s",&((*e)->population));
printf(" \n Donner la superficie:");
scanf("%s",&((*e)->superficie));
printf(" \n Donner le nombre de municipalit�s:");
scanf("%s",&((*e)->nbMunicipalites));
x=getchar();
}

void elementAfficher(ELEMENT e) {
 printf("nom=%s,la date de cr�ation=%d,la population=%d,la superficie=%d,le nombre de municipalit�s=%d",e->Nom,e->dateCreation,e->population,e->superficie,e->nbMunicipalites);
}
void elementAffecter(ELEMENT* e1, ELEMENT e2) {
*e1 = e2 ;
}
void elementCopier(ELEMENT *e1, ELEMENT e2) {
strcpy((*e1)->Nom,e2->Nom);
strcpy((*e1)->population,e2->population);
strcpy((*e1)->superficie,e2->superficie);
strcpy((*e1)->nbMunicipalites,e2->nbMunicipalites);
}
int elementComparer(ELEMENT e1, ELEMENT e2) {
return ((e1->population)-(e2->population)) ;
}
