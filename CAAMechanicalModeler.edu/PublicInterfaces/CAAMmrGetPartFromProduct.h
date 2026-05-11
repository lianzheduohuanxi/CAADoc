#ifndef CAAMmrGetPartFromProduct_H
#define CAAMmrGetPartFromProduct_H

//COPYRIGHT DASSAULT SYSTEMES 2001


#include "CATISpecObject.h" 
#include <CATIProduct.h> 
#include <CATBaseUnknown.h> 
#include <CAAMmrUtilities.h>

HRESULT ExportedByCAAMmrUtilities 
          CAAMmrGetPartFromProduct(CATIProduct_var        ispProduct , 				  
				                   CATISpecObject_var  & ospPartFromProduct) ;

#endif

