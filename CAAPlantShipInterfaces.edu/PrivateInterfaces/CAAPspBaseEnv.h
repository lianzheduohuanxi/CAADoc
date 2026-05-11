// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//

#ifndef CAAPspBaseEnv_H
#define CAAPspBaseEnv_H

#include "CAAPspUtilities.h"
#include "CATIContainer.h"
#include "CATUnicodeString.h"
#include "IUnknown.h"
#include "CATBaseUnknown.h"

class CATDocument;
class CATIProduct;
class CATSession;
class CATIPspPhysical;
class CATIPspLightPart;
class CATIPspLogicalLine;

class ExportedByCAAPspUtilities CAAPspBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAPspBaseEnv ();
    virtual ~CAAPspBaseEnv();

    //-------------------------------------------------------------------------
    // Get data
    //-------------------------------------------------------------------------
    CATDocument * GetDocument ();
    CATIContainer * GetRootContainer();

    //-------------------------------------------------------------------------
    // Save document
    //-------------------------------------------------------------------------
    //virtual void SaveDocument (const CATUnicodeString &iFileName);

    //-------------------------------------------------------------------------
    // Create environment
    //-------------------------------------------------------------------------
    virtual void CreateCATProductEnv (const CATUnicodeString &iFileNameToBeLoaded);

    //-------------------------------------------------------------------------
    // Initialize application
    //-------------------------------------------------------------------------
    virtual void ApplicationInit (const CATUnicodeString &iuApplicationContext = "CATPiping");

    //-------------------------------------------------------------------------
    //  Get root product in the document
    //-------------------------------------------------------------------------
    virtual CATIProduct * GetRootProduct ();

    //-------------------------------------------------------------------------
    // Get a child object of a product
    // iObjectTestMethod tests if child object meets criteria.
    // ipiParentProduct is the product whose children will be searched.
    //                  if NULL, the root product will be searched.
    //-------------------------------------------------------------------------
    virtual IUnknown * GetChildObject (IUnknown * iObjectTestMethod(const CATBaseUnknown_var &spObject), 
                                       const CATIProduct *ipiParentProduct = NULL);

    //-------------------------------------------------------------------------
    // Get a child object of a product that adheres to an interface and matches a name.
    // iIID is the object interface type.
    // iuObjectName is the name of the object. If null, it is not used.
    // ipiParentProduct is the product whose children will be searched.
    //                  if NULL, the root product will be searched.
    //-------------------------------------------------------------------------
    virtual IUnknown * GetChildObject (const IID &iIID, 
                                       const CATUnicodeString &iuObjectName = "", 
                                       const CATIProduct *ipiParentProduct = NULL);

    //-------------------------------------------------------------------------
    // Get the first physical object found under a parent product. NULL uses root product.
    //-------------------------------------------------------------------------
    virtual CATIPspPhysical * GetAPhysicalObject (const CATIProduct *ipiParentProduct = NULL);

    //-------------------------------------------------------------------------
    // Get the first physical light object found under a parent product. NULL uses root product.
    //-------------------------------------------------------------------------
    virtual CATIPspLightPart * GetALightObject (const CATIProduct *ipiParentProduct = NULL);

    //-------------------------------------------------------------------------
    // Get the first bendable pipe found under a parent product. NULL uses root product.
    //-------------------------------------------------------------------------
    virtual CATIPspPhysical * GetABendablePipeObject (const CATIProduct *ipiParentProduct = NULL);

    //-------------------------------------------------------------------------
    // Get the first logical line found under a parent product. NULL uses root product.
    //-------------------------------------------------------------------------
    virtual CATIPspLogicalLine * GetALogicalLine (const CATIProduct *ipiParentProduct = NULL);

    //-------------------------------------------------------------------------
    // Cleanup
    //-------------------------------------------------------------------------
    virtual void CleanupSession ();

  private:

    CATDocument       *_pDocument;
    CATIContainer     *_piRootCont;
    CATSession        *_pSession;
    char              *_pSessionIdent;

};
#endif
