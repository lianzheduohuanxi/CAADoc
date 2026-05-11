// COPYRIGHT DASSAULT SYSTEMES 1994-2000

//===============================================================================================
//
//  What does the factory do ?
//
//     o -1- Getting a pointer on the features container
//     o -2- Opening the CAAOmmCatalog catalog
//     o -3- Retrieving CAAOmmVerticalLine startup
//     o -4- Creating a vertical line instance
//     o -5- Setting default values for the attributes of the instance
//
//===============================================================================================

// Local framework  
#include "CAAEOmmFactory.h"       // needed as class header file
#include "CATOsmSUHandler.h"

// System resources
#include "iostream.h"             // needed for trace management

// System framework
#include "CATUnicodeString.h"     // needed to handle strings
#include "CATBaseDispatch.h"      // needed as operating system independant IDispatch interface

// ObjectModelerBase framework
#include "CATIContainer.h"        // needed as a pointer to navigate into document structure

// ObjectSpecsModeler
#include "CATISpecObject.h"            // needed to reach the vertical line as a specification

// MechModInterfaces
#include "CATIPartRequest.h"          // needed to reach the par document root node
#include "CATIAPart.h"            // needed to set the vertical line within the exposed model


// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CAAIAOmmFactory.h"
TIE_CAAIAOmmFactory(CAAEOmmFactory);

CATImplementClass( CAAEOmmFactory,
                   DataExtension,
                   CATBaseUnknown,
                   MechanicalPart );

// Dictionary entry to be added :
// MechanicalPart CAAIAOmmFactory libCAAOmmImpl
 
//-----------------------------------------------------------------------------
// CAAEOmmFactory : constructor
//-----------------------------------------------------------------------------
CAAEOmmFactory::CAAEOmmFactory(): CATBaseUnknown()
{
 cout << "CAAEOmmFactory : CTOR" << endl ;
}

//-----------------------------------------------------------------------------
// CAAEOmmFactory : destructor
//-----------------------------------------------------------------------------
CAAEOmmFactory::~CAAEOmmFactory()
{
 cout << "CAAEOmmFactory : DTOR" << endl ;
}

//-----------------------------------------------------------------------------
// CAAEOmmFactory : get_Application
//-----------------------------------------------------------------------------
HRESULT  CAAEOmmFactory::get_Application(CATIAApplication *& opiApplicationOnCATIA)
{
 HRESULT rc=E_FAIL;
 opiApplicationOnCATIA=NULL;

 // Retrieves OLE exposed parent class
 CATBaseDispatch* piBaseOnParent=NULL;
 rc=get_Parent(piBaseOnParent);

 // Then delegates the job to the parent (gets up until CATIA is found out)
 if (SUCCEEDED(rc)) {
    // NB : get_Parent methos returns a CATIABase based interface casted 
    // into a CATBaseDispatch one
    rc = ( (CATIABase*) piBaseOnParent)->get_Application(opiApplicationOnCATIA);
    piBaseOnParent->Release();
    piBaseOnParent = NULL ;
    }
 return rc;
}


//-----------------------------------------------------------------------------
// CAAEOmmFactory : get_Name
//-----------------------------------------------------------------------------
HRESULT  CAAEOmmFactory::get_Name(CATBSTR & oName)
{
   // Instance is a singleton : name is the meta-class alias name
   CATUnicodeString str ("OmmFactory");
   str.ConvertToBSTR(&oName);
   return S_OK;
}

//-----------------------------------------------------------------------------
// CAAEOmmFactory : put_Name
//-----------------------------------------------------------------------------
HRESULT  CAAEOmmFactory::put_Name(const CATBSTR & iName)
{
   cout  << "CAAEOmmFactory::put_Name" << endl;
   // Method cannot be implemented in this case
   HRESULT rc = E_NOTIMPL;

   return rc;
}

//-----------------------------------------------------------------------------
// CAAEOmmFactory : GetItem
//-----------------------------------------------------------------------------
HRESULT CAAEOmmFactory::GetItem(const CATBSTR & iName, CATBaseDispatch *& opiBaseOnChildObject)
{
   cout  << "CAAEOmmFactory::GetItem" << endl;
   // Method cannot be implemented in this case : unresolved symbols management should be done
   // thru CATIGenTrac interface
   HRESULT rc = E_NOTIMPL;

   return rc;
}

//-----------------------------------------------------------------------------
// CAAEOmmFactory : get_Parent
//-----------------------------------------------------------------------------
HRESULT __stdcall CAAEOmmFactory::get_Parent(CATBaseDispatch *& opiBaseOnOLEParent)
{
   // Gets the parent object as regards the OLE exposed model
   // i.e. the Part feature, object which to get this factory from
   HRESULT rc=QueryInterface(IID_CATIAPart, (void**) &opiBaseOnOLEParent);
   return rc;
}

//-----------------------------------------------------------------------------
// Implements CATIABibFactory::AddNewVerticalLine
//-----------------------------------------------------------------------------
HRESULT __stdcall CAAEOmmFactory::AddNewVerticalLine(
				CATIAReference        * ipiReferenceOnPoint1,
				CATIAReference        * ipiReferenceOnPoint2,
				CAAIAOmmVerticalLine *& opiVerticalLineOnLine)
{
   cout << "CAAEOmmFactory::AddNewVerticalLine" << endl;
   HRESULT rc = E_FAIL;
   opiVerticalLineOnLine=NULL;

    //-------------------------------------------------------------------------------
    // -1- Getting a pointer on the features container
    //-------------------------------------------------------------------------------
    CATIPartRequest *piPartOnThis = NULL;
    rc = QueryInterface( IID_CATIPartRequest, ( void**) &piPartOnThis );
    if (FAILED(rc) ) {
        return E_FAIL;
	}
    CATBaseUnknown_var spBUOnMainTool ;
    rc = piPartOnThis->GetMainBody("",spBUOnMainTool);
    if (FAILED(rc) || (NULL_var==spBUOnMainTool)) {
        return E_FAIL;
	}
    piPartOnThis->Release();
    piPartOnThis = NULL ;
    CATISpecObject_var spSpecOnMainTool = spBUOnMainTool ;
    
    CATIContainer_var spiContainer = spSpecOnMainTool->GetFeatContainer();
    if (NULL_var==spiContainer) {
       return E_FAIL;
       }

 
    //-------------------------------------------------------------------------------
    // -2- Opening the OLE4MecMod features catalog
    //-------------------------------------------------------------------------------
    
    const CATUnicodeString catalogName("CAAOmmCatalog.CATfct");
    const CATUnicodeString clientID("CAA_OLE4MecMod");
    CATUnicodeString StartupType = "CAAOmmVerticalLine";
    
	CATOsmSUHandler startupHandler(StartupType, clientID, catalogName);
    //-------------------------------------------------------------------------------
    // -4- Creating a vertical line instance
    //-------------------------------------------------------------------------------
	CATISpecObject_var specOnInstance;
	startupHandler.Instanciate(specOnInstance,  spiContainer, NULL);

	if (!specOnInstance)
		return E_FAIL;
    
    //-------------------------------------------------------------------------------
    // -5- Setting default values for the attributes of the instance
    //-------------------------------------------------------------------------------
    rc = specOnInstance->QueryInterface( IID_CAAIAOmmVerticalLine, (void**) &opiVerticalLineOnLine );
    
	if( FAILED(rc) ) {
        return E_FAIL;
        }
    
    rc = opiVerticalLineOnLine->put_Point1( ipiReferenceOnPoint1 );
    rc = opiVerticalLineOnLine->put_Point2( ipiReferenceOnPoint2 );
    
   return rc;
}
