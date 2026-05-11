// COPYRIGHT Dassault Systemes 2002

// Local Framework
#include "CAAEPstINFCSORoot.h"

// ApplicationFrame Framework
#include "CATICSOFilter.h"

// Others
#include "iostream.h"
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATICSOFilter.h"
TIE_CATICSOFilter( CAAEPstINFCSORoot);

// To declare that the class is a data extension of CAAPstINFRoot
//
CATImplementClass( CAAEPstINFCSORoot,
                   DataExtension,
                   CATBaseUnknown,
                   CAAPstINFRoot );
 
// To declare that CAAEPstINFCSORoot implements CATICSOFilter for the
// CAAPstINFRoot component, insert the following line in the interface dictionary:
//
//    CAAPstINFRoot CATICSOFilter libCAAINFCommands
//
//-----------------------------------------------------------------------------
// CAAEPstINFCSORoot : constructor
//-----------------------------------------------------------------------------
CAAEPstINFCSORoot::CAAEPstINFCSORoot():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAEPstINFCSORoot : destructor
//-----------------------------------------------------------------------------
CAAEPstINFCSORoot::~CAAEPstINFCSORoot()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATICSOFilter::CommandIsAvailable
// Only the command "Paste" is to be made available for the root object.
//-----------------------------------------------------------------------------
HRESULT CAAEPstINFCSORoot::CommandIsAvailable (const char *pHeaderID, const CATCSO *pCSO)
{
	cout << "******CAAEPstINFCSORoot::CommandIsAvailable" << endl;
    HRESULT result;
    result = E_FAIL;
  
    if (!strcmp(pHeaderID, "Paste")) 
       result = S_OK;

    return result;	
}

//-----------------------------------------------------------------------------
// Implements CATICSOFilter::AvailableElements
//-----------------------------------------------------------------------------
HRESULT CAAEPstINFCSORoot::AvailableElements (const char *pHeaderID, const CATCSO *pCSO, CATListValCATBaseUnknown_var **spAvailableElements)
{
	cout << "******CAAEPstINFCSORoot::AvailableElements" << endl;
    return S_OK;
}

