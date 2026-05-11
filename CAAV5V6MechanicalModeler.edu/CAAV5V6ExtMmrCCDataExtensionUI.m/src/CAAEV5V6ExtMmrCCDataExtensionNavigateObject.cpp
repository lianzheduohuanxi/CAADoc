//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2012
//=======================================================================
//
// Class  CAAEV5V6ExtMmrCCDataExtensionNavigateObject:
// Implementation of CATINavigateObject for CAAV5V6ExtMmrCCDataExtension
//
// NB: Standard behavior in the Spec Tree
// (CATINavigModify / CATINavigElement not impemented)

// Local CAAV5V6MechanicalModeler.edu framework
#include "CAAEV5V6ExtMmrCCDataExtensionNavigateObject.h"
#include "CAAIV5V6ExtMmrCCDataExtension.h"

// System framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerBase framework in V5 
// ObjectModelerSystem framework in V6 
#include "CATIAlias.h"
  
// KnowledgeInterfaces framework  
#include "CATICkeParm.h"


CATBeginImplementClass( CAAEV5V6ExtMmrCCDataExtensionNavigateObject, DataExtension, CATINavigateObject, CAAV5V6ExtMmrCCDataExtension);
CATEndImplementClass( CAAEV5V6ExtMmrCCDataExtensionNavigateObject);

CATImplementBOA(CATINavigateObject, CAAEV5V6ExtMmrCCDataExtensionNavigateObject); 

//-------------------------------------------------
//____________Constructor/Destructor_______________
//-------------------------------------------------

 CAAEV5V6ExtMmrCCDataExtensionNavigateObject:: CAAEV5V6ExtMmrCCDataExtensionNavigateObject()
{
}
 CAAEV5V6ExtMmrCCDataExtensionNavigateObject::~ CAAEV5V6ExtMmrCCDataExtensionNavigateObject()
{
}
//-------------------------------------------------
//_________Interfaces CATINavigateObject___________
//-------------------------------------------------
//___________ Implements GetIdentificators ________
//-------------------------------------------------
CATListOfCATUnicodeString* CAAEV5V6ExtMmrCCDataExtensionNavigateObject::GetIdentificators()
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
CATLISTV(CATBaseUnknown_var)* CAAEV5V6ExtMmrCCDataExtensionNavigateObject::GetChildren()
{
  CATLISTV(CATBaseUnknown_var)* Children = NULL;
  //Show components
  Children = new CATListValCATBaseUnknown_var();

  CAAIV5V6ExtMmrCCDataExtension *piMmrCCDataExt = NULL;
  HRESULT rc = QueryInterface( IID_CAAIV5V6ExtMmrCCDataExtension, ( void**) &piMmrCCDataExt);
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
