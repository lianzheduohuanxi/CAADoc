#ifndef CAASysPrintUtilities_H
#define CAASysPrintUtilities_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATSetOfCATString.h"
void  printSet(CATSetOfCATString& iSet) ;

#include "CAASysHashTableOfCAASysPoint2D.h"
void printHashtable(CATHTAB(CAASysPoint2D)& iHashtable) ;

#endif
