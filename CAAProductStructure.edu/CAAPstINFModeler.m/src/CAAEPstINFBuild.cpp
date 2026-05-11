// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFBuild.h"

// System Framework
#include "CATErrorDef.h"

//----ObjectSpecsModeler Framework 
#include "CATISpecObject.h"
#include "CATIBuild.h"

// Visualization Framework
#include "CATIModelEvents.h"
#include "CATModify.h"

// Others
#include "iostream.h"

// Tie the implementation to its interface
#include "TIE_CATIBuild.h"
TIE_CATIBuild( CAAEPstINFBuild );

// To declare that the class is a data extension of CAAPstINFLine and CAAPstINFWire
//
CATBeginImplementClass( CAAEPstINFBuild,   // Implementation class
                        DataExtension,         
                        CATBaseUnknown,        
                        CAAPstINFLine );   // Component extended by this class
CATAddClassExtension(CAAPstINFWire);
CATEndImplementClass(CAAEPstINFBuild);

// To declare that CAAEPstINFBuild implements CATIBuild for the CAAPstINFLine and
// CAAPstINFWire components, insert the following lines in the interface dictionary:
//
//    CAAPstINFLine CATIBuild  libCAAINFModeler
//    CAAPstINFWire CATIBuild  libCAAINFModeler
//
//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEPstINFBuild::CAAEPstINFBuild()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEPstINFBuild::~CAAEPstINFBuild()
{
}

//-----------------------------------------------------------------------------
// Redefinition of the CATIBuild::Build() service 
// Refresh the Line's or Wire's Representation
//-----------------------------------------------------------------------------
HRESULT CAAEPstINFBuild::Build()
{
    cout << "******* Start of: CAAEPstINFBuild::Build()" << endl;
     
    // Retrieve a CATIModelEvents interface pointer on the current line or wire feature
	// in order to send a modification notification to force its re-visualization.
    
    CATIModelEvents * pModelEvents = NULL;                
    HRESULT rc = QueryInterface(IID_CATIModelEvents, 
		                 (void**)&pModelEvents);
    if (SUCCEEDED(rc))
    {
       CATModify Notif (pModelEvents); 
       pModelEvents->Dispatch(Notif);

       pModelEvents-> Release();
       pModelEvents = NULL;
    }
	else cout << "CATIModelEvents QI on Line or Wire failed." << endl;

    return S_OK;
}
