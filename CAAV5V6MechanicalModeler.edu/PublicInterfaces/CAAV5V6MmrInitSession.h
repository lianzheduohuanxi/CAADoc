#ifndef CAAV5V6MmrInitSession_H
#define CAAV5V6MmrInitSession_H

//COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATIAV5Level.h"
#include "CATUnicodeString.h"
#include "CAAV5V6MmrUtilities.h"


class CATIMmiPrtContainer;
class CATOmbLifeCycleRootsBag;
class CATDocument;

#ifdef CATIAR214
HRESULT ExportedByCAAV5V6MmrUtilities  
	 CAAV5V6MmrInitSession(const char *  iRepository, 
    				    const char *  iServer, 
    					const char *  iUser,
    				    const char * iPassword,
    					const char * iRole,
						const char* iStrPLMType,
   		                const CATUnicodeString& iPLM_ExternalIDValue,
   		                const CATUnicodeString& iV_versionValue,
						CATOmbLifeCycleRootsBag &iBag,
                        CATIMmiPrtContainer *&opApplicativeContainer) ;

#else
HRESULT ExportedByCAAV5V6MmrUtilities  
	 CAAV5V6MmrInitSession(char * iSessionName, 
	                       const CATUnicodeString& iStorageName,
						   CATDocument *& oNewDoc,
    				       CATIMmiPrtContainer *&opApplicativeContainer) ;
#endif
         


#endif

