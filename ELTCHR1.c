#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ELTPRIM1.h"
#define ELEMENT_VIDE NULL

ELEMENT1 elementCreer1 (void) {
ELEMENT1 e;
e = (ELEMENT1) malloc(sizeof('z'));
return e;
}
void elementDetruire1 (ELEMENT1 e) {
free (e);
}

void elementLire1(ELEMENT1* e) {
char x;
//printf(" \nDonnez un caractere :") ;
scanf("%c",&(*(*e)));
}

void elementAfficher1(ELEMENT1 e) {
 printf("%c",*e);
}
void elementAffecter1(ELEMENT1* e1, ELEMENT1 e2) {
*e1 = e2 ;
}
void elementCopier1(ELEMENT1 *e1, ELEMENT1 e2) {
*(*e1)=*e2;
}
int elementComparer1(ELEMENT1 e1, ELEMENT1 e2) {
return e1 - e2 ;
}

