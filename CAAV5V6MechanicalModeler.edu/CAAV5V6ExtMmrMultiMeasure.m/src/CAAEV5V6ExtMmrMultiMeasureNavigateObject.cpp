//========================================================================
// COPYRIGHT DASSAULT SYSTEMES  2012
//=======================================================================
//
// Class  CAAEV5V6ExtMmrMultiMeasureNavigateObject:
// Implement CATINavigateObject for CAAV5V6ExtMmrMultiMeasure
//
// NB: Standard behavior in the Spec Tree
// (CATINavigModify / CATINavigElement not impemented)
//
// Note : CAAEV5V6ExtMmrMultiMeasureNavigateObject is the same use case as CAAEMmrMultiMeasureNavigateObject. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

// local CAAMechanicalModelerExtend.edu framework
#include "CAAEV5V6ExtMmrMultiMeasureNavigateObject.h"
#include "CAAIV5V6ExtMmrMultiMeasure.h"

// System framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerSystem framework 
#include "CATIAlias.h"
  
// KnowledgeInterfaces framework  
#include "CATICkeParm.h"


CATBeginImplementClass(CAAEV5V6ExtMmrMultiMeasureNavigateObject, DataExtension, CATINavigateObject, CAAV5V6ExtMmrMultiMeasure);
CATEndImplementClass(CAAEV5V6ExtMmrMultiMeasureNavigateObject);

CATImplementBOA(CATINavigateObject,CAAEV5V6ExtMmrMultiMeasureNavigateObject); 

//-------------------------------------------------
//____________Constructor/Destructor_______________
//-------------------------------------------------

CAAEV5V6ExtMmrMultiMeasureNavigateObject::CAAEV5V6ExtMmrMultiMeasureNavigateObject()
{
}
CAAEV5V6ExtMmrMultiMeasureNavigateObject::~CAAEV5V6ExtMmrMultiMeasureNavigateObject()
{
}
//-------------------------------------------------
//_________Interfaces CATINavigateObject___________
//-------------------------------------------------
//___________ Implements GetIdentificators ________
//-------------------------------------------------
CATListOfCATUnicodeString* CAAEV5V6ExtMmrMultiMeasureNavigateObject::GetIdentificators()
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
CATLISTV(CATBaseUnknown_var)* CAAEV5V6ExtMmrMultiMeasureNavigateObject::GetChildren()
{
  CATLISTV(CATBaseUnknown_var)* Children = NULL;
  //Show components
  Children = new CATListValCATBaseUnknown_var();

  CAAIV5V6ExtMmrMultiMeasure *piMmrMultiMeasure = NULL;
  HRESULT rc = QueryInterface( IID_CAAIV5V6ExtMmrMultiMeasure, ( void**) &piMmrMultiMeasure);
  if (SUCCEEDED(rc) && piMmrMultiMeasure != NULL)
  {
    CATICkeParm_var spLengthParm;
    rc = piMmrMultiMeasure->GetLengthParameter(spLengthParm);
	if (SUCCEEDED(rc) && !!spLengthParm)
	{
	  if ((spLengthParm->Value())->AsReal() != NULL)
      Children -> Append(spLengthParm);
	}

	CATICkeParm_var spWetAreaParm;
    rc = piMmrMultiMeasure->GetWetAreaParameter(spWetAreaParm);
	if (SUCCEEDED(rc) && !!spWetAreaParm)
	{
	  if ((spWetAreaParm->Value())->AsReal() != NULL)
      Children -> Append(spWetAreaParm);
	}

	CATICkeParm_var spVolumeParm;
    rc = piMmrMultiMeasure -> GetVolumeParameter(spVolumeParm);
	if(SUCCEEDED(rc) && !!spVolumeParm)
	{
	  if ((spVolumeParm->Value())->AsReal() != NULL)
      Children -> Append(spVolumeParm);
	}
    
	piMmrMultiMeasure -> Release();
    piMmrMultiMeasure = NULL;
  }

  return Children;
}
