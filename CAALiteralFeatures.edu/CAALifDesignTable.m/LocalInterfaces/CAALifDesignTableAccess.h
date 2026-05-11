#ifndef CAALifDesignTableAccess_H
#define CAALifDesignTableAccess_H

// COPYRIGHT DASSAULT SYSTEMES  2000

class CATIContainer_var;

#include "CATCke.h"
#include "CATListOfCATUnicodeString.h"
#include "CATICkeParmFactory.h"

// ===============================================================
//   ABSTRACT
//   --------
//     Creates a design table from an external file in txt format 
//     Adds associations 
//     Displays the names of the columns
//     Gets the column where a parameter is
//     Retrieves the parameter in a given column
//     Retrieves the value in a given cell
// ===============================================================

CATCke::Boolean CAALifDesignTableAccess(CATIContainer_var, char*);               
#endif








































































