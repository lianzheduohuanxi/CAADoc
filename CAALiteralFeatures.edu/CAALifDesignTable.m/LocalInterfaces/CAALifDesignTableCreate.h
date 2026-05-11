#ifndef CAALifDesignTableCreate_H
#define CAALifDesignTableCreate_H

// COPYRIGHT DASSAULT SYSTEMES  2000

class CATIContainer_var;

#include "CATCke.h"
#include "CATListOfCATUnicodeString.h"
#include "CATICkeParmFactory.h"

// ==============================================================
//     ABSTRACT 
//     --------
//     
//     Creates a design table from an external file in txt format. 
//     Adds automatically associations. 
//     Adds one-by-one associations.
//     Retrieves the list of associations.
//     Displays the current configuration.
//     Sets the current configuration.
// ==============================================================

CATCke::Boolean CAALifDesignTableCreate(CATIContainer_var, char*);               
#endif








































































