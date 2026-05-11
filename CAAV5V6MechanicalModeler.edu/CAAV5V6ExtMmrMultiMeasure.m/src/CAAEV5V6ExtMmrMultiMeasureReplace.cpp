// COPYRIGHT DASSAULT SYSTEMES 2012
//=======================================================================
//
// Class  CAAEV5V6ExtMmrMultiMeasureReplace:
// Implements CATIReplace for CAAV5V6ExtMmrMultiMeasure
//
// Note :  CAAEV5V6ExtMmrMultiMeasureReplace is the same use case as  CAAEMmrMultiMeasureReplace. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//========================================================================
// CATIBuild Implementation 
//========================================================================

#include "CATIAV5Level.h"

// Local Framework
#include "CAAEV5V6ExtMmrMultiMeasureReplace.h"
#include "CAAIV5V6ExtMmrMultiMeasure.h"

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"              // To handle the Redraw in the Tree Representation

// CATMecModUseItf Framework
#include "CATIMmiUseGeometricalElement.h"
#include "CATIMmiUseTopoAccess.h"

// CATMecModLiveUseItf
#include "CATMmiContractDefs.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"


// Implementation BOA
CATImplementBOA( CATIReplace, CAAEV5V6ExtMmrMultiMeasureReplace);

// Implementation Class
CATBeginImplementClass (CAAEV5V6ExtMmrMultiMeasureReplace, DataExtension, CATIReplace, CAAV5V6ExtMmrMultiMeasure);
CATEndImplementClass(CAAEV5V6ExtMmrMultiMeasureReplace);

//-----------------------------------------------------------------------------
// To declare that CAAMmrMultiMeasure implement CATIReplace ,  
// insert the following line in the interface dictionary:
// CAAV5V6ExtMmrMultiMeasure  CATIReplace  libCAAV5V6ExtMmrMultiMeasure
//-----------------------------------------------------------------------------

CAAEV5V6ExtMmrMultiMeasureReplace::CAAEV5V6ExtMmrMultiMeasureReplace()
{
}
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasureReplace::~CAAEV5V6ExtMmrMultiMeasureReplace ()
{
}
//-----------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrMultiMeasureReplace::IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
                                                            const CATBaseUnknown_var& iElement,
                                                            CATUnicodeString& oMessage, 
                                                            int& oElementValidity, 
                                                            const CATBaseUnknown_var& iOldValue)
{
  HRESULT rc = E_FAIL;

  CATUnicodeString NameAttribute = "V5V6FeatureToMeasure";
  CATUnicodeString NameAttributeKBRep = "V5V6BRepFeatureToMeasure";

	// Check input
  if (iNameOfRole != NameAttribute && iNameOfRole != NameAttributeKBRep)
  {
    oMessage = "This is not Good Attribute Name";
    oElementValidity = 0;
    return rc;
  }

  CATIMmiUseGeometricalElement_var spCandidate = iElement;
  CATIMmiUseTopoAccess_var spCandidateBRepAccess = iElement;

  if (spCandidate == NULL_var && spCandidateBRepAccess == NULL_var)
  {
    oMessage = "This is not a good candidate";
    oElementValidity = 0;
    return rc;
  }
  else
  {
    //If BRepAccess
    if (spCandidateBRepAccess != NULL_var)
    {
      //BRepAccess Case
			CATMmiDimension Dimension;
			CATMmiDimensionType DimensionType;
      rc = spCandidateBRepAccess->GetBrepFtrGeometryType(Dimension, DimensionType);
      if (Dimension != CATMmiDimUnknown || Dimension != CATMmiVertex)
      {
        oMessage = "Ftr BRep Valid To Replace";
        oElementValidity = 1;
        rc = S_OK;
        return rc;
      }
      else    
      {
        oMessage = "InValid To Replace : Is Not a Valid BRepAccess";
        oElementValidity = 0;
        return rc;
      }
    }
    //GeometricalFtr
    else
    {
      oMessage = "Valid To Replace";
      oElementValidity = 1;
      rc = S_OK;
      return rc;
    }
  }

  return rc;
}

//------------------------------------------------------------------------
HRESULT
CAAEV5V6ExtMmrMultiMeasureReplace::Replace(const CATUnicodeString& iNameOfRole,
                                   CATBaseUnknown_var& ispNewElement,
                                   const CATBaseUnknown_var& ispOldValue)
{
  HRESULT rc = E_FAIL;

  CAAIV5V6ExtMmrMultiMeasure_var spMmrMultiMeasure = this;

  if (spMmrMultiMeasure != NULL_var)
  {
    CATBaseUnknown_var spForReplace = ispNewElement;
    CATUnicodeString Message;
    int ElementValidity;

    rc = IsElementValidForReplace(iNameOfRole,
                                  spForReplace, 
                                  Message, 
                                  ElementValidity, 
                                  ispOldValue);

    if (SUCCEEDED(rc) && ElementValidity == 1)
    {
      rc = spMmrMultiMeasure->SetInputGeomFeature(spForReplace);
    }
    
    //Update Spec Tree
    //----------------------
	
    CATIRedrawEvent_var spEvent(spMmrMultiMeasure);
    if (NULL_var != spEvent)
    {
      spEvent->Redraw();
    }
    
  }
  return rc;
}

