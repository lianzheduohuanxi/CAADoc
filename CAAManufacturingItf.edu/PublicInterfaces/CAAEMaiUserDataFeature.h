// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAEMaiUserDataFeature:
//
// Sample code for : Providing an editor to a User Data Feature
// Mission         : Sample of implementation of the CATIMfgUserDataFeature interface
//
// ===================================================================

#ifndef CAAEMaiUserDataFeature_h
#define CAAEMaiUserDataFeature_h

// System
#include "CATBaseUnknown.h"

// Dialog
#include "CATDlgInclude.h"

class CAAEMaiUserDataFeature : public CATBaseUnknown
{
  public: 
      
    CATDeclareClass;

// Constructor and Destructor

    CAAEMaiUserDataFeature();
    virtual ~CAAEMaiUserDataFeature();

// Implementation of the CATIMfgUserDataFeature interface methods
 
    HRESULT GetEditor (CATDialog *iFather,CATDlgFrame* &oEditor);

    HRESULT GetNLSDescription (CATUnicodeString &oNLSDescription);

  private:

// Copy Constructor and operator =

    CAAEMaiUserDataFeature(const CAAEMaiUserDataFeature &iObjectToCopy);
    CAAEMaiUserDataFeature& operator = (const CAAEMaiUserDataFeature &iObjectToCopy);
};

#endif

