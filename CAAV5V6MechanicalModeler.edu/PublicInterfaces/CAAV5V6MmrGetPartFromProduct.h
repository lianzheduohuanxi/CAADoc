#ifndef CAAV5V6MmrGetPartFromProduct_H
#define CAAV5V6MmrGetPartFromProduct_H

//COPYRIGHT DASSAULT SYSTEMES 2012


#include "CATIAV5Level.h"
#include "CAAV5V6MmrUtilities.h"

// System Framework
#include "CATBaseUnknown.h"

class CATIPartRequest_var ;
class CATIPLMNavInstance_var ;
class CATIProduct_var;
class CATISpecObject_var; 

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
HRESULT ExportedByCAAV5V6MmrUtilities 
          CAAV5V6MmrGetPartFromProduct(CATIPLMNavInstance_var   ispNavInstance , 				  
				                       CATIPartRequest_var  & ospPartFromProduct) ;


#else
//============================================== 
// V5 only
//==============================================
HRESULT ExportedByCAAV5V6MmrUtilities
	      CAAV5V6MmrGetPartFromProduct(CATIProduct_var ispProduct, 
		                                CATISpecObject_var  & ospPartFromProduct);
#endif


#endif

