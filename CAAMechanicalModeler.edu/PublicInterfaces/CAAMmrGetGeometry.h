#ifndef CAAMmrGetGeometry_H
#define CAAMmrGetGeometry_H

//COPYRIGHT DASSAULT SYSTEMES 2001


#include "CATISpecObject.h" 
#include <CATUnicodeString.h> 
#include <CATBaseUnknown.h> 
#include <CAAMmrUtilities.h>

HRESULT ExportedByCAAMmrUtilities 
          CAAMmrGetGeometry(CATISpecObject_var ispModelPart, 
				  const CATUnicodeString iInputName, 
				  CATBaseUnknown ** oInput) ;

#endif

