// COPYRIGHT DASSAULT SYSTEMES 2007
//=================================================================================================
//
// CAAEMmrCCDataExtensionParmPublisher .cpp
// Provide implementation to interface
//    CATIParmPublisher for MmrCCDataExtension
//
//=================================================================================================

// Local Framework
#include "CAAEMmrCCDataExtensionParmPublisher.h"
#include "CAAIMmrCCDataExtension.h"

// ObjectSpecsModeler Framework
#include "CATLISTV_CATISpecObject.h"
#include "CATISpecObject.h"

// KnowledgeInterfaces Framework
#include "CATICkeParm.h"

CATBeginImplementClass(CAAEMmrCCDataExtensionParmPublisher, CodeExtension, CATBaseUnknown, CAAMmrCCDataExtension);
CATEndImplementClass(CAAEMmrCCDataExtensionParmPublisher);

#include "TIE_CATIParmPublisher.h"
TIEchain_CATIParmPublisher(CAAEMmrCCDataExtensionParmPublisher); 

//==================================================================================================
// Constructeur,Destructeur
//==================================================================================================
CAAEMmrCCDataExtensionParmPublisher::CAAEMmrCCDataExtensionParmPublisher():CATParmPublisherAdapter()
{
}

CAAEMmrCCDataExtensionParmPublisher::~CAAEMmrCCDataExtensionParmPublisher()
{
}

//==================================================================================================
// Private Methods
//==================================================================================================
//___________Implements 1st AddChildren method (CATBaseUnknown_var)_________________________________
// -------------------------------------------------------------------------------------------------

void CAAEMmrCCDataExtensionParmPublisher::AddChildren(CATClassId intfName,CATListValCATISpecObject_var &lst)
{
  // Published Parameters:
  // 1st: Gets the Valuated Parm "LengthParm"

  CAAIMmrCCDataExtension *piMmrCCDataExtension = NULL;

  HRESULT rc = QueryInterface(IID_CAAIMmrCCDataExtension, ( void**) &piMmrCCDataExtension );

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

// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmPublisher::GetDirectChildren_______________________________________
// -------------------------------------------------------------------------------------------------
void CAAEMmrCCDataExtensionParmPublisher::GetDirectChildren (CATClassId intfName,CATListValCATISpecObject_var &lst)
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
void CAAEMmrCCDataExtensionParmPublisher::GetAllChildren (CATClassId intfName,CATListValCATISpecObject_var &lst)  
{
	// Adds Params managed directly by Knowledge
	CATParmPublisherAdapter::GetAllChildren(intfName,lst);
	// Adds "personnal" Params
	AddChildren (intfName, lst);
}
// -------------------------------------------------------------------------------------------------
//____________Implements CATIParmPublisher::VisitChildren___________________________________________
// -------------------------------------------------------------------------------------------------
void CAAEMmrCCDataExtensionParmPublisher::VisitChildren(CATIVisitor* iVisitor, const int iRecursive)
{ 
	if (iVisitor)
	{
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
	}
}
