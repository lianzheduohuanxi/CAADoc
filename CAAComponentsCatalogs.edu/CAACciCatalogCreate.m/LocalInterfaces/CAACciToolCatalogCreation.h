// COPYRIGHT DASSAULT SYSTEMES  2002
#ifndef CAACciToolCatalogCreation_H
#define CAACciToolCatalogCreation_H

// System Framework
#include "CATErrorDef.h" 
#include "CATUnicodeString.h"

// This method creates the CAATool.catalog document in the iOutputPath directory
// in using data (Part document) stored in the iInputPath directory and also 
// stored in the iOutputPath directory. In this last case, it is the previous 
// catalog document created by the CAAScrewCatalogCreation and the
// CAANuts6SidesCatalogCreation functions
//
HRESULT CAAToolCatalogCreation(CATUnicodeString & iInputPath, CATUnicodeString & iOutputPath) ;

#endif

