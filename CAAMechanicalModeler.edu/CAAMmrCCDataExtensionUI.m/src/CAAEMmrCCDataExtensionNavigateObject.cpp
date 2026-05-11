//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2006
//=======================================================================
//
// Class  CAAEMmrCCDataExtensionNavigateObject:
// Implementation CATINavigateObject for MmrCCDataExtension
//
// NB: Standard behavior in the Spec Tree
// (CATINavigModify / CATINavigElement not impemented)

#include "CAAEMmrCCDataExtensionNavigateObject.h"
#include "CAAIMmrCCDataExtension.h"

#include "CATIDescendants.h"

//include System
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATISpecObject.h"
#include "CATLISTV_CATBaseUnknown.h"


//include ObjectSpecsModeler
#include "CATIAlias.h"
#include "CATISpecObject.h"

//include des Cke
#include "CATICkeParm.h"


CATBeginImplementClass(CAAEMmrCCDataExtensionNavigateObject, DataExtension, CATINavigateObject, CAAMmrCCDataExtension);
CATEndImplementClass(CAAEMmrCCDataExtensionNavigateObject);

CATImplementBOA(CATINavigateObject,CAAEMmrCCDataExtensionNavigateObject); 

//-------------------------------------------------
//____________Constructor/Destructor_______________
//-------------------------------------------------

CAAEMmrCCDataExtensionNavigateObject::CAAEMmrCCDataExtensionNavigateObject()
{
}
CAAEMmrCCDataExtensionNavigateObject::~CAAEMmrCCDataExtensionNavigateObject()
{
}
//-------------------------------------------------
//_________Interfaces CATINavigateObject___________
//-------------------------------------------------
//___________ Implements GetIdentificators ________
//-------------------------------------------------
CATListOfCATUnicodeString* CAAEMmrCCDataExtensionNavigateObject::GetIdentificators()
{	
  CATListOfCATUnicodeString* IdCard = new CATListOfCATUnicodeString;
  CATIAlias *piAlias = NULL;

  HRESULT rc = QueryInterface( IID_CATIAlias, ( void**) &piAlias);
  if(SUCCEEDED(rc) && piAlias!= NULL)
  {
    IdCard->Append(piAlias->GetAlias());
   
    piAlias -> Release();
    piAlias = NULL;
  }
  else
    IdCard->Append("no name");
  return IdCard;
}
//-------------------------------------------------
//_____________ Implements GetChildren ____________
//-------------------------------------------------
CATLISTV(CATBaseUnknown_var)* CAAEMmrCCDataExtensionNavigateObject::GetChildren()
{
  CATLISTV(CATBaseUnknown_var)* Children = NULL;
  //Show components
  Children = new CATListValCATBaseUnknown_var();

  CAAIMmrCCDataExtension *piMmrCCDataExt = NULL;
  HRESULT rc = QueryInterface( IID_CAAIMmrCCDataExtension, ( void**) &piMmrCCDataExt);
  if(SUCCEEDED(rc) && piMmrCCDataExt != NULL)
  {
    CATICkeParm_var spValuatedParm;
    rc = piMmrCCDataExt -> GetValuatedParam(spValuatedParm);
    if(SUCCEEDED(rc) && !!spValuatedParm)
      Children -> Append(spValuatedParm);

    piMmrCCDataExt -> Release();
    piMmrCCDataExt = NULL;
  }
  return Children;
}
