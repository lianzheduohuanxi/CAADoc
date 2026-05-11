// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAPstINFUpdateProvider.h"

// ProductStructure Framework
#include "CATIProduct.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"
#include "CATIClientContainer.h"
#include "CATIUpdateProvider.h"

// Visualization Framework
#include "CATIModelEvents.h"
#include "CATModify.h"

// ObjectModelerBase Framework
#include "CATDocument.h"
#include "CATAppliContServices.h"
#include "CATILinkableObject.h"

// System Framework
#include "CATBaseUnknown.h"

// Others
#include "iostream.h"

// Tie the implementation to its interface.
#include "TIE_CATIUpdateProvider.h"
TIE_CATIUpdateProvider(CAAPstINFUpdateProvider);

// To declare that the class is an simple implementation
//
CATImplementClass( CAAPstINFUpdateProvider,
                   Implementation, 
                   CATBaseUnknown,
                   CATNull );

// To declare that CAAEPstINFUpdateProvider is an implementation of CATIUpdateProvider, 
// insert the following line in the interface dictionary:
//
//    CAAPstINFUpdateProvider CATIUpdateProvider  libCAAPstINFModeler
//

//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : constructor
//-----------------------------------------------------------------------------
CAAPstINFUpdateProvider::CAAPstINFUpdateProvider():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : destructor
//-----------------------------------------------------------------------------
CAAPstINFUpdateProvider::~CAAPstINFUpdateProvider()
{
}
 
//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : copy constructor
//-----------------------------------------------------------------------------
CAAPstINFUpdateProvider::CAAPstINFUpdateProvider(CAAPstINFUpdateProvider& original): CATBaseUnknown(original)
{
}
 
//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : equal operator
//-----------------------------------------------------------------------------
CAAPstINFUpdateProvider& CAAPstINFUpdateProvider::operator=(CAAPstINFUpdateProvider& original)
{
   CATBaseUnknown::operator=(original);
   return *this;
}

//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : Update
// This provider updates the features of type "CAAPstINFLine" or "CAAPstINFWire" 
// found in the applicative container of type "CAAPstINFCont". 
//-----------------------------------------------------------------------------
int CAAPstINFUpdateProvider::Update(CATBaseUnknown * pObj, CATIDomain_var spDomain) 
{
	cout << "***** CAAPstINFUpdateProvider::Update" << endl << flush;

	int retnum = 1; 

	// Retrieve a pointer to the applicative container.
	CATILinkableObject *piLinkableOnObj = NULL;
	if (NULL == pObj) return retnum;
	HRESULT rc = pObj -> QueryInterface (IID_CATILinkableObject,
		                         (void**) &piLinkableOnObj);
	if (FAILED(rc)) return retnum;

	CATDocument* pDoc = piLinkableOnObj -> GetDocument();
	piLinkableOnObj -> Release();
	piLinkableOnObj = NULL;
		
    CATUnicodeString appliContIdentifier("PstINFContainer");
    CATBaseUnknown *pApplicativeContainer = NULL;
	rc = ::CATGetApplicativeContainer (&pApplicativeContainer,   
                                       pDoc,                     
	   							       IID_CATIContainer,  
                                       appliContIdentifier);     
    if (SUCCEEDED(rc)) cout << "Applicative container retrieved OK" << endl << flush;
    else
	{
       cout << "ERROR in retrieving applicative container" << endl << flush;
       return retnum;
	}

	// Retrieve a pointer to CATIClientContainer in order to list the members
	// of the applicative container.
    CATIClientContainer *piClientOnAppliCont = NULL;
    rc = pApplicativeContainer -> QueryInterface(IID_CATIClientContainer,
                                                 (void**) &piClientOnAppliCont);

    pApplicativeContainer -> Release();
    pApplicativeContainer = NULL;

    if (NULL == piClientOnAppliCont)
	{
       cout << "ERROR in retrieving container pointer" << endl << flush;
       return retnum;
	}
	else cout << "CATIClientContainer pointer retrieved OK" << endl << flush;
	
	// Retrieve the list of features in the applicative container
	CATUnicodeString clientId("CAAPstINFClientId"); 
	CATListPtrCATBaseUnknown *pMemberList = NULL;
    rc = piClientOnAppliCont -> ListMembers(IID_CATISpecObject,
                                            clientId,  
                                            &pMemberList);
    piClientOnAppliCont -> Release();
    piClientOnAppliCont = NULL;

    if (SUCCEEDED(rc)) cout << "Member list retrieved OK" << endl << flush;
    else
	{ 
		cout << "ERROR in retrieving member list" << endl << flush;
		return retnum;
	}

	cout << "Number of members in applicative container: " << pMemberList->Size() << endl << flush;
      
	CATUnicodeString type;
	CATISpecObject *piSpecsMember = NULL;
	for(int i=1;i<=pMemberList->Size();i++)
	{
		piSpecsMember = (CATISpecObject*) (*pMemberList)[i];
		if (NULL == piSpecsMember) return retnum;
		type = piSpecsMember -> GetType();
		cout << "Type of object " << i << " = " << type.ConvertToChar() << endl;
		if ((type == "CAAPstINFLine") || (type == "CAAPstINFWire"))
		{
			cout << "Call update on line or wire." << endl;
			piSpecsMember -> Update();
   	    }
		piSpecsMember -> Release();
		(*pMemberList)[i] = NULL;
		piSpecsMember = NULL;
	}
	delete pMemberList;
	pMemberList = NULL;

	return 0;
}

//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : IsUpToDate - not implemented.
//-----------------------------------------------------------------------------
CATBoolean CAAPstINFUpdateProvider::IsUpToDate(CATBaseUnknown *pObj, CATIDomain_var spDomain)
{
	return FALSE;
}

//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : SetUpToDate - not implemented.
//-----------------------------------------------------------------------------
void CAAPstINFUpdateProvider::SetUpToDate(CATBaseUnknown *pObj, CATBoolean flag)
{
}

//-----------------------------------------------------------------------------
// CAAPstINFUpdateProvider : IsInactive - not implemented.
//-----------------------------------------------------------------------------
int CAAPstINFUpdateProvider::IsInactive(CATBaseUnknown *pObj)
{
	return 0;
}
