#ifndef CAAV5V6MmrGetGeometry_H
#define CAAV5V6MmrGetGeometry_H

//COPYRIGHT DASSAULT SYSTEMES 2001


#include "CATUnicodeString.h" 
#include "CAAV5V6MmrUtilities.h"

class CATBaseUnknown ;
class CATIPartRequest_var ;


HRESULT ExportedByCAAV5V6MmrUtilities  
          CAAV5V6MmrGetGeometry(CATIPartRequest_var ispModelPart, 
				  const CATUnicodeString iInputName, 
				  CATBaseUnknown ** oInput) ;

#endif

