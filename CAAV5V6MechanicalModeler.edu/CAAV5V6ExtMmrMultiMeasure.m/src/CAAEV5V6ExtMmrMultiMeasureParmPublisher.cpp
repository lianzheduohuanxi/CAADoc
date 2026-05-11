// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAEV5V6ExtMmrMultiMeasureParmPublisher.cpp
// Provide implementation to interface
//    CATIParmPublisher for CAAV5V6ExtMmrMultiMeasure
//
// Note : CAAEV5V6ExtMmrMultiMeasureParmPublisher is the same use case as CAAEMmrMultiMeasureParmPublisher. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//=================================================================================================

#include "CATIAV5Level.h"

// Local Framework
#include "CAAEV5V6ExtMmrMultiMeasureParmPublisher.h"
#include "CAAIV5V6ExtMmrMultiMeasure.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"
#include "CATIVisitor.h"

// System Framework
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerBase Framework 
#include "CATIContainer.h"

CATBeginImplementClass(CAAEV5V6ExtMmrMultiMeasureParmPublisher, CodeExtension, CATIParmPublisher, CAAV5V6ExtMmrMultiMeasure);
CATEndImplementClass(CAAEV5V6ExtMmrMultiMeasureParmPublisher);

#include "TIE_CATIParmPublisher.h"
TIEchain_CATIParmPublisher(CAAEV5V6ExtMmrMultiMeasureParmPublisher); 

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

#include "TIE_CATIParmDirectAccess.h"
TIEchain_CATIParmDirectAccess(CAAEV5V6ExtMmrMultiMeasureParmPublisher); 
#endif

//==================================================================================================
// Constructeur,Destructeur
//==================================================================================================
CAAEV5V6ExtMmrMultiMeasureParmPublisher::CAAEV5V6ExtMmrMultiMeasureParmPublisher():CATParmPublisherAdapter()
{}

CAAEV5V6ExtMmrMultiMeasureParmPublisher::~CAAEV5V6ExtMmrMultiMeasureParmPublisher()
{}


// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmPublisher::VisitChildren___________________________________________
// -------------------------------------------------------------------------------------------------
void CAAEV5V6ExtMmrMultiMeasureParmPublisher::VisitChildren(CATIVisitor* iVisitor, const int iRecursive)
{ 
  //
	// no recursivity since the only one children is a parameter
	// 
	if (iVisitor)
	{
		CATListValCATBaseUnknown_var listChildren;
		AddChildren("CATBaseUnknown", listChildren);

		int nbChildren = listChildren.Size();
		for (int i = 1; i <= nbChildren; i++)
		{
			CATBaseUnknown_var child = listChildren[i];
			if (child != NULL_var)
			{
				HRESULT rc = iVisitor->Visit(child); 
        if (FAILED(rc))
          return;
			}
		}
	}
}

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================

// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmDirectAccess::RetrieveDirectChildren ___________________________________________
// -------------------------------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrMultiMeasureParmPublisher::RetrieveDirectChildren (CATClassId iIntfName,CATListValCATBaseUnknown_var &iListToFill)   const 
{
	// Method VisitChildren cannot be called directly - ondy DS engine can do it.
	// This interface has been created to have a method (RetrieveDirectChildren ) checking
	// the code retrieving the direct children (VisitChildren and RetrieveDirectChildren use 
  // the same internal method, AddChildren)

	
	((CAAEV5V6ExtMmrMultiMeasureParmPublisher*)this)->AddChildren (iIntfName, iListToFill);
	
	
	return S_OK;
}
#endif

//==================================================================================================
// Local Methods
//==================================================================================================
//___________Implements 1st AddChildren method (CATBaseUnknown_var)_________________________________
// -------------------------------------------------------------------------------------------------

void CAAEV5V6ExtMmrMultiMeasureParmPublisher::AddChildren(CATClassId intfName,CATListValCATBaseUnknown_var &lst)
{
  // Published Parameters:
  // 1st: Gets the Valuated Parm "LengthParm"

  CAAIV5V6ExtMmrMultiMeasure_var spMmrMultiMeasure = this;

  if (spMmrMultiMeasure != NULL_var)
  {
    CATICkeParm_var spLengthParm=NULL_var;
    HRESULT rc = spMmrMultiMeasure->GetLengthParameter(spLengthParm);
		CATICkeParm_var spWetAreaParm=NULL_var;
    rc = spMmrMultiMeasure->GetWetAreaParameter(spWetAreaParm);
		CATICkeParm_var spVolumeParm=NULL_var;
    rc = spMmrMultiMeasure->GetVolumeParameter(spVolumeParm);

    if (spLengthParm!= NULL_var)
    {
      // Determines whether the retrieved Object supports
      // the interface specified in the argument    
      CATBaseUnknown* pAsked=NULL;
      pAsked = spLengthParm->QueryInterface(intfName);
      if (NULL != pAsked)
      {
        // Adds the CATICkeParm which supports the iIntfName interface
        // to the list specified in the second (output) argument
        lst.Append(spLengthParm);
      
        pAsked->Release();
        pAsked = NULL;
      }
    }
		if (spWetAreaParm!= NULL_var)
    {
      // Determines whether the retrieved Object supports
      // the interface specified in the argument    
      CATBaseUnknown* pAsked=NULL;
      pAsked = spWetAreaParm->QueryInterface(intfName);
      if (NULL != pAsked)
      {
        // Adds the CATICkeParm which supports the iIntfName interface
        // to the list specified in the second (output) argument
        lst.Append(spWetAreaParm);
      
        pAsked->Release();
        pAsked = NULL;
      }
    }
		if (spVolumeParm!= NULL_var)
    {
      // Determines whether the retrieved Object supports
      // the interface specified in the argument    
      CATBaseUnknown* pAsked=NULL;
      pAsked = spVolumeParm->QueryInterface(intfName);
      if (NULL != pAsked)
      {
        // Adds the CATICkeParm which supports the iIntfName interface
        // to the list specified in the second (output) argument
        lst.Append(spVolumeParm);
      
        pAsked->Release();
        pAsked = NULL;
      }
    }
  }
}

