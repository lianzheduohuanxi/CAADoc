#ifndef CAAEMmrCatalogSynchronizeForCombCrv_H
#define CAAEMmrCatalogSynchronizeForCombCrv_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// System Framework
#include "CATBaseUnknown.h"  // To derive from 

class CATPixelImage;
class CATUnicodeString;

#include "CATICkeType.h"

/**
* Class extending the object "CombinedCurve".
* It implements the interface :
*      ComponentsCatalogsInterfaces.CATICatalogSynchronize
*/

class CAAEMmrCatalogSynchronizeForCombCrv: public CATBaseUnknown
{
    CATDeclareClass;
    
public:
    
    // Standard constructors and destructors for an implementation class
    // -----------------------------------------------------------------
   CAAEMmrCatalogSynchronizeForCombCrv ();
   virtual ~CAAEMmrCatalogSynchronizeForCombCrv ();
 
   virtual HRESULT GetAlias(CATUnicodeString& oAlias) ;

   virtual HRESULT GetEmbeddedPreview(CATPixelImage** oImage) ;

   virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   int& oKeyWordValue) ;
 
   virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   const CATICkeType* iKeywordType,
                                   double& oKeyWordValue) ;

   virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   CATCke::Boolean & oKeyWordValue) ;
 

   virtual HRESULT GetKeywordValue(const CATUnicodeString& iKeywordName,
                                   CATUnicodeString& oKeyWordValue) ;
    
private:
    // The copy constructor and the equal operator must not be implemented
    // -------------------------------------------------------------------
    CAAEMmrCatalogSynchronizeForCombCrv (CAAEMmrCatalogSynchronizeForCombCrv & iObjectToCopy);
    CAAEMmrCatalogSynchronizeForCombCrv& operator=(CAAEMmrCatalogSynchronizeForCombCrv & iObjectToCopy);
    
};


#endif
