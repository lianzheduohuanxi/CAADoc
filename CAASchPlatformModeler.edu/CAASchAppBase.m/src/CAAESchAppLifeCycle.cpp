//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
#include "CAAESchAppLifeCycle.h"

#include "CATIProduct.h"
#include "CATISchCutAndPaste.h"

// System
#include "CATError.h"
#include "CATErrorMacros.h"

#include "TIE_LifeCycleObject.h"
TIEchain_LifeCycleObject(CAAESchAppLifeCycle);

CATBeginImplementClass (CAAESchAppLifeCycle,DataExtension,CATBaseUnknown,CAASCHEDUPart);
CATAddExtendedImplementation(CAASCHEDUString);
CATEndImplementClass (CAAESchAppLifeCycle);

//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppLifeCycle::CAAESchAppLifeCycle() : CATSpecLifeCycleObjectExt()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppLifeCycle::~CAAESchAppLifeCycle()
{
}

//  ===========================================================================
//  | LifeCycleObject::remove
//  ===========================================================================
void CAAESchAppLifeCycle::remove( int iForCloseContext )
{
  CATIProduct_var spPrd (GetImpl());
  if (!spPrd) return;

  CATTry 
  { 
    if (FAILED(spPrd->IsReference()))
    {
      RemoveComponentExtensionIfNeeded( iForCloseContext );
      CATSpecLifeCycleObjectExt::remove( iForCloseContext );
    }
    else
    {
      if (iForCloseContext)
      {
        RemoveComponentExtensionIfNeeded( iForCloseContext );
        CATSpecLifeCycleObjectExt::remove( iForCloseContext );
      }
    }
  }
  CATCatch (CATError, pError)
  {
	  if (pError) Flush(pError);
  }	
  CATEndTry;
}

//  ===========================================================================
//  | Schematic component needs to be removed by calling the 
//  | CATISchCutAndPastable interface which is implemented by the 
//  | Schematic platform to remove the graphical representation of the
//  | component.
//  ===========================================================================
void CAAESchAppLifeCycle::RemoveComponentExtensionIfNeeded ( int iForCloseContext )
{
  CATISchCutAndPaste *piCCP = NULL;

  CATTry 
  { 
    HRESULT rc1 = E_FAIL;
    if (SUCCEEDED(QueryInterface(IID_CATISchCutAndPaste,(void **)&piCCP)) &&
        piCCP)
    {
       rc1 = piCCP->remove (iForCloseContext);
    }
  }
  CATCatch (CATError, pError)
  {
	  if (pError) Flush(pError);
  }	
  CATEndTry;
  if (piCCP) {piCCP->Release(); piCCP=NULL;}
}
