// COPYRIGHT DASSAULT SYSTEMES 2007
//=======================================================================
//
// Class  CAAEMmrMultiMeasureReplace:
// Implements CATIReplace for MmrMultiMeasure
//
//========================================================================
// CATIBuild Implementation 
//========================================================================

// Local Framework
#include "CAAEMmrMultiMeasureReplace.h"
#include "CAAIMmrMultiMeasure.h"

// ObjectModelerBase Framework
#include "CATIRedrawEvent.h"              // To handle the Redraw in the Tree Representation
#include "CATLISTV_CATBaseUnknown.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"               // To handle feature, update it
#include "CATBaseUnknown.h"

// MechanicalModeler Framework
#include "CATIFeaturize.h"                // On the fly featurization of Selection Objects 
#include "CATIBRepAccess.h"
#include "CATIMfBRep.h"  
#include "CATIMfPoint.h"
#include "CATIGeometricalElement.h"

// Include System
#include "CATUnicodeString.h"

// Implementation BOA
CATImplementBOA( CATIReplace, CAAEMmrMultiMeasureReplace);

// Implementation Class
CATBeginImplementClass (CAAEMmrMultiMeasureReplace, DataExtension, CATIReplace, CAAMmrMultiMeasure);
CATEndImplementClass(CAAEMmrMultiMeasureReplace);

//-----------------------------------------------------------------------------
// To declare that CAAMmrMultiMeasure implement CATIReplace ,  
// insert the following line in the interface dictionary:
// CAAMmrMultiMeasure  CATIReplace  libCAAMmrMultiMeasureAndMeasureSet
//-----------------------------------------------------------------------------

CAAEMmrMultiMeasureReplace::CAAEMmrMultiMeasureReplace()
{
}
//-----------------------------------------------------------------------------
CAAEMmrMultiMeasureReplace::~CAAEMmrMultiMeasureReplace ()
{
}
//-----------------------------------------------------------------------------
HRESULT CAAEMmrMultiMeasureReplace::IsElementValidForReplace(const CATUnicodeString& iNameOfRole,
                                                            const CATBaseUnknown_var& iElement,
                                                            CATUnicodeString& oMessage, 
                                                            int& oElementValidity, 
                                                            const CATBaseUnknown_var& iOldValue)
{
  HRESULT exit = E_FAIL;

  CATUnicodeString NameAttribute = "FeatureToMeasure";
  CATUnicodeString NameAttributeKBRep = "BRepFeatureToMeasure";

  if (iNameOfRole != NameAttribute && 
    iNameOfRole != NameAttributeKBRep )
  {
    oMessage = "This is not Good Attribute Name";
    oElementValidity = 0;
    return exit;
  }

  if (iNameOfRole == NameAttribute || iNameOfRole == NameAttributeKBRep )
  {
    CATIGeometricalElement_var hCandidate = iElement;
    CATIBRepAccess_var hCandidateBRepAccess = iElement;

    if (!hCandidate && !hCandidateBRepAccess )
    {
      oMessage = "This is not a good candidate";
      oElementValidity = 0;
      return exit;
    }
    else
    {
      //If BRepAccess
      if (!!hCandidateBRepAccess)
      {
        //BRepAccess Case
        int dimension = hCandidateBRepAccess -> GetDimension();
        if ( dimension != 0)
        {
          oMessage = "Ftr BRep Valid To Replace";
          oElementValidity = 1;
          exit = S_OK;
          return exit;
        }
        else    
        {
          oMessage = "InValid To Replace : Is Not a Valid BRepAccess";
          oElementValidity = 0;
          return exit;
        }
      }
      //GeometricalFtr
      else
      {
        oMessage = "Valid To Replace";
        oElementValidity = 1;
        exit = S_OK;
        return exit;
      }
    }
  }
  return exit;
}

//------------------------------------------------------------------------
HRESULT
CAAEMmrMultiMeasureReplace::Replace(const CATUnicodeString& iNameOfRole,
                                   CATBaseUnknown_var& ispNewElement,
                                   const CATBaseUnknown_var& ispOldValue)
{
  HRESULT rc = E_FAIL;

  CATISpecObject_var spCurrent = this;
  CAAIMmrMultiMeasure* pMmrMultiMeasure = NULL;

  rc = QueryInterface(IID_CAAIMmrMultiMeasure,(void **)&pMmrMultiMeasure );
  if(SUCCEEDED(rc) && pMmrMultiMeasure != NULL)
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
      rc = pMmrMultiMeasure -> SetInputGeomFeature(spForReplace);
    }
    
    //Update Spec Tree
    //----------------------
    CATIRedrawEvent_var spEvent(spCurrent);
    if (NULL_var != spEvent)
    {
      spEvent->Redraw();
    }
    pMmrMultiMeasure -> Release();
    pMmrMultiMeasure = NULL;
  }
  return rc;
}

