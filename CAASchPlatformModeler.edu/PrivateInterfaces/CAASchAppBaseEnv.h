// COPYRIGHT DASSAULT SYSTEMES  2001 +
//=============================================================================
//

#ifndef CAASchBaseEnv_H
#define CAASchBaseEnv_H

#include "CAASchAppUtilities.h"
#include "CATISpecObject.h"
#include "CATIContainer.h"
#include "CATIProduct.h"
#include "CATBooleanDef.h"
#include "CATErrorDef.h"

class CATDocument;
class CATSession;
class CATISchRoute;
class CATISchInternalFlow;
class CATISchComponent;

//-----------------------------------------------------------------------------

class ExportedByCAASchAppUtilities CAASchAppBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAASchAppBaseEnv ();
    virtual ~CAASchAppBaseEnv();

    //-------------------------------------------------------------------------
    // Get data
    //-------------------------------------------------------------------------
    CATDocument * GetDocument ();
    CATIContainer_var GetRootContainer();
    CATIContainer_var GetSchExtContainer();
    CATIContainer_var GetAppObjContainer();

    //-------------------------------------------------------------------------
    // Save document
    //-------------------------------------------------------------------------
    virtual void SaveDocument (const char *iFileName);

    //-------------------------------------------------------------------------
    // Create environment
    //-------------------------------------------------------------------------

    virtual void CreateCATProductEnv (const char *iFileNameToBeLoaded=NULL,
      boolean iBMode2D=TRUE);


    //-------------------------------------------------------------------------
    // Set current work sheet (to the main non-detail sheet)
    //-------------------------------------------------------------------------
    virtual void SetMainSheet ();

    //-------------------------------------------------------------------------
    // Cleanup
    //-------------------------------------------------------------------------
    virtual void CleanupSession ();

  private:

    void GetSubContainers ();

    CATDocument       *_pSchDoc;
    CATIContainer     *_piSchRootCont;
    CATSession        *_pSession;
    char              *_pSessionIdent;
    CATIContainer_var _spSchExtCont;
    CATIContainer_var _spSchAppObjCont;
};
#endif
