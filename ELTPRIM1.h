#ifndef ELTPRIM1_H
#define ELTPRIM1_H

#include "ELTSDD1.h"
ELEMENT1 elementCreer1(void) ;
void elementLire1(ELEMENT1 *);
void elementAfficher1(ELEMENT1);
void elementAffecter1(ELEMENT1*, ELEMENT1);
void elementCopier1(ELEMENT1 *, ELEMENT1) ;
int elementComparer1(ELEMENT1, ELEMENT1);
void elementDetruire1 (ELEMENT1);
#endif

