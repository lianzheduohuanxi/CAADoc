// COPYRIGHT DASSAULT SYSTEMES 2012
//=================================================================================================
//
// CAAEV5V6ExtMmrCCDataExtensionParmPublisher 
// Provide implementation to interface
//    CATIParmPublisher for CAAV5V6ExtMmrCCDataExtension
//
// Note : CAAEV5V6ExtMmrCCDataExtensionParmPublisher is the same use case as CAAEMmrCCDataExtensionParmPublisher. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//
//=================================================================================================

#include "CATIAV5Level.h"

// Local CAAV5V6MechanicalModeler.edu Framework
#include "CAAEV5V6ExtMmrCCDataExtensionParmPublisher.h"
#include "CAAIV5V6ExtMmrCCDataExtension.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"
#include "CATIVisitor.h"

// System Framework
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerBase Framework 
#include "CATIContainer.h"

#ifdef CATIAV5R23
//============================================== 
// V5 only
//==============================================
// ObjectSpecsModeler Framework
#include "CATLISTV_CATISpecObject.h"
#include "CATISpecObject.h"
#endif

CATBeginImplementClass(CAAEV5V6ExtMmrCCDataExtensionParmPublisher, CodeExtension, CATIParmPublisher, CAAV5V6ExtMmrCCDataExtension);
CATEndImplementClass(CAAEV5V6ExtMmrCCDataExtensionParmPublisher);

#include "TIE_CATIParmPublisher.h"
TIEchain_CATIParmPublisher(CAAEV5V6ExtMmrCCDataExtensionParmPublisher); 

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
#include "TIE_CATIParmDirectAccess.h"
TIEchain_CATIParmDirectAccess(CAAEV5V6ExtMmrCCDataExtensionParmPublisher); 
#endif

//==================================================================================================
// Constructeur,Destructeur
//==================================================================================================
CAAEV5V6ExtMmrCCDataExtensionParmPublisher::CAAEV5V6ExtMmrCCDataExtensionParmPublisher():CATParmPublisherAdapter()
{}

CAAEV5V6ExtMmrCCDataExtensionParmPublisher::~CAAEV5V6ExtMmrCCDataExtensionParmPublisher()
{}


// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmPublisher::VisitChildren___________________________________________
// -------------------------------------------------------------------------------------------------
void CAAEV5V6ExtMmrCCDataExtensionParmPublisher::VisitChildren(CATIVisitor* iVisitor, const int iRecursive)
{ 
  //
	// no recursivity since the only one children is a parameter
	// 
	if (iVisitor)
	{
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
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
#else
//============================================== 
// V5 only
//==============================================
	    CATLISTV(CATISpecObject_var) liste;
		CATLISTV(CATISpecObject_var) tmp;
		
        CATParmPublisherAdapter::GetDirectChildren("CATISpecObject",tmp);
		
        int sizei = tmp.Size();
        int i = 1;
        for (i = 1; i<=sizei; i++)
		{
			liste.Append(tmp[i]);
		}

		AddChildren("CATBaseUnknown", liste);

		sizei = liste.Size();
		for (i = 1; i <= sizei; i++)
		{
			CATBaseUnknown_var elem = liste[i];
			if (!!elem)
			{
				HRESULT hr = iVisitor->Visit(elem);
				if (!SUCCEEDED(hr))
				{
					return;
				}
			}
		}
#endif
	}
}

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmDirectAccess::RetrieveDirectChildren ___________________________________________
// -------------------------------------------------------------------------------------------------
HRESULT CAAEV5V6ExtMmrCCDataExtensionParmPublisher::RetrieveDirectChildren (CATClassId iIntfName,CATListValCATBaseUnknown_var &iListToFill)   const 
{
	// Method VisitChildren cannot be called directly - ondy DS engine can do it.
	// This interface has been created to have a method (RetrieveDirectChildren ) checking
	// the code retrieving the direct children (VisitChildren and RetrieveDirectChildren use 
  // the same internal method, AddChildren)

	
	((CAAEV5V6ExtMmrCCDataExtensionParmPublisher*)this)->AddChildren (iIntfName, iListToFill);
	
	
	return S_OK;
}
#else
//============================================== 
// V5 only
//==============================================
// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmPublisher::GetDirectChildren_______________________________________
// -------------------------------------------------------------------------------------------------
void CAAEV5V6ExtMmrCCDataExtensionParmPublisher::GetDirectChildren (CATClassId intfName,CATListValCATISpecObject_var &lst)
{
	// Adds Params managed directly by Knowledge
	CATParmPublisherAdapter::GetDirectChildren (intfName,lst);
	// Adds "personnal" Params
	AddChildren (intfName, lst);
	return;
}
// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmPublisher::GetAllChildren__________________________________________
// -------------------------------------------------------------------------------------------------
void CAAEV5V6ExtMmrCCDataExtensionParmPublisher::GetAllChildren (CATClassId intfName,CATListValCATISpecObject_var &lst)  
{
	// Adds Params managed directly by Knowledge
	CATParmPublisherAdapter::GetAllChildren(intfName,lst);
	// Adds "personnal" Params
	AddChildren (intfName, lst);
}
#endif


//==================================================================================================
// Local Methods
//==================================================================================================
//___________Implements 1st AddChildren method (CATBaseUnknown_var)_________________________________
// -------------------------------------------------------------------------------------------------

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
void CAAEV5V6ExtMmrCCDataExtensionParmPublisher::AddChildren(CATClassId intfName,CATListValCATBaseUnknown_var &lst)
{
  // Published Parameters:
  // 1st: Gets the Valuated Parm "LengthParm"

  CAAIV5V6ExtMmrCCDataExtension_var spMmrCCDataExtension = this;

  if (spMmrCCDataExtension != NULL_var)
  {
    CATICkeParm_var spValuatedParm=NULL_var;
    HRESULT rc = spMmrCCDataExtension->GetValuatedParam(spValuatedParm);

    if (SUCCEEDED(rc) && spValuatedParm!= NULL_var)
    {
      // Determines whether the retrieved Object supports
      // the interface specified in the argument    
      CATBaseUnknown* pAsked=NULL;
      pAsked = spValuatedParm->QueryInterface(intfName);
      if (NULL != pAsked)
      {
        // Adds the CATICkeParm which supports the iIntfName interface
        // to the list specified in the second (output) argument
        lst.Append(spValuatedParm);
      
        pAsked->Release();
        pAsked = NULL;
      }
    }
  }
}

#else
//============================================== 
// V5 only
//==============================================

void CAAEV5V6ExtMmrCCDataExtensionParmPublisher::AddChildren(CATClassId intfName,CATListValCATISpecObject_var &lst)
{
  // Published Parameters:
  // 1st: Gets the Valuated Parm "LengthParm"

  CAAIV5V6ExtMmrCCDataExtension *piMmrCCDataExtension = NULL;

  HRESULT rc = QueryInterface(IID_CAAIV5V6ExtMmrCCDataExtension, ( void**) &piMmrCCDataExtension );

  if(SUCCEEDED(rc) && piMmrCCDataExtension != NULL)
  {
    CATICkeParm_var spValuatedParm;
    piMmrCCDataExtension -> GetValuatedParam(spValuatedParm);

    // Determines whether the retrieved CATISpecObject supports
    // the interface specified in the argument
    
    CATBaseUnknown* pAsked=NULL;
    pAsked = spValuatedParm -> QueryInterface(intfName);
    if ( NULL != pAsked )
    {
      // Adds the CATICkeParm which supports the iIntfName interface
      // to the list specified in the second (output) argument
      lst.Append(spValuatedParm);
      
      pAsked -> Release();
      pAsked = NULL;
    }
    piMmrCCDataExtension -> Release();
    piMmrCCDataExtension = NULL;
  }
}

#endif
