#ifndef CAAMcaGetGeometry_H
#define CAAMcaGetGeometry_H

//COPYRIGHT DASSAULT SYSTEMES 2001


#include "CATISpecObject.h" 
#include <CATUnicodeString.h> 
#include <CATBaseUnknown.h> 
#include <CAAMcaUtilities.h>

HRESULT ExportedByCAAMcaUtilities 
          CAAMcaGetGeometry(CATISpecObject_var ispModelPart, 
				  const CATUnicodeString iInputName, 
				  CATBaseUnknown ** oInput) ;

#endif

