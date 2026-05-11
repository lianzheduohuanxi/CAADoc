#ifndef CAAMmrRetrieveCornerAndVectorsFromPad_H
#define CAAMmrRetrieveCornerAndVectorsFromPad_H

//COPYRIGHT DASSAULT SYSTEMES 2001


#include "CATISpecObject.h" 
#include <CATUnicodeString.h> 
#include <CATBaseUnknown.h> 

HRESULT CAAMmrRetrieveCornerAndVectorsFromPad(CATBaseUnknown *  iInputPad, 
                                              CATBaseUnknown ** oVectorX,
				              CATBaseUnknown ** oVectorY);

#endif

