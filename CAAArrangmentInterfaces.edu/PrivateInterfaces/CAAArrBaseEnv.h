// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//

#ifndef CAAArrBaseEnv_H
#define CAAArrBaseEnv_H

#include "CAAArrUtilities.h"
#include "CATIContainer.h"
#include "CATErrorDef.h"
#include "CATUnicodeString.h"

class CATDocument;
class CATSession;
class CATIPspPhysical;
class CATIPspLogicalLine;

//-----------------------------------------------------------------------------

class ExportedByCAAArrUtilities CAAArrBaseEnv
                                    
{
  public:
    //-------------------------------------------------------------------------
    // Constructor/Destructor
    //-------------------------------------------------------------------------
    CAAArrBaseEnv ();
    virtual ~CAAArrBaseEnv();

    //-------------------------------------------------------------------------
    // Get data
    //-------------------------------------------------------------------------
    CATDocument * GetDocument ();
    CATIContainer * GetRootContainer();

    //-------------------------------------------------------------------------
    // Initialize application
    //-------------------------------------------------------------------------
    virtual void ApplicationInit ();

    //-------------------------------------------------------------------------
    // Save document
    //-------------------------------------------------------------------------
    virtual void SaveDocument (const CATUnicodeString &iFileName);

    //-------------------------------------------------------------------------
    // Create environment
    //-------------------------------------------------------------------------
    virtual void CreateCATProductEnv (const CATUnicodeString &iFileNameToBeLoaded);

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
