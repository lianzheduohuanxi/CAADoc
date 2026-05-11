// COPYRIGHT DASSAULT SYSTEMES 2004

//=============================================================================
//  Abstract of Use Case "CAAEwrListWiresInBundleSegment":
//  --------------------------------------------------
//
//  This Use Case illustrates how to list wires in a bundle segment
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
//  2. Initializing Electrical Environment 
//  3. Retrieving all Geometrical Bundle under the Root Product and Selecting one to analyze 
//  4. Retrieving all Bundle Segments under the Geometrical Bundle and Selecting one to analyze 
//  5. List the Wires going through the bundle segment
//  6. Epilogue.
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document
//  3 - ERROR in getting root product
//  4 - ERROR in initializing electrical environment 
//  5 - ERROR in searching geometrical bundle
//  6 - ERROR in retrieving geometrical bundle
//  7 - ERROR in binding to CATIParmPublisher interface
//  8 - ERROR in searching instances under geometrical bundle
//  9 - ERROR in retrieving bundle segment 
// 10 - ERROR in binding to CATIInstance interface
// 11 - ERROR in searching bundle segment
// 12 - ERROR in binding to CATIEwrRouteSegment interface
// 13 - ERROR in no conductors found in bundle segment
// 14 - ERROR in removing document
// 15 - ERROR in deleting session
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEwrListWiresInBundleSegment input.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the of the document itself (Electrical-External-data-start.CATProduct).
//
//
//  You may reference the supplied CATProduct document called "Session.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic directory. 
//
//
//=============================================================================
// C++ include ( result display )
// LRO 08:01:15
#include "CATBoolean.h"
#include "CATIType.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>

// System
#include "CATBaseUnknown.h"           // Generic Object
#include "CATLISTV_CATBaseUnknown.h"  // list of generic objects

// ObjectModelerBase interfaces
#include "CATSessionServices.h"       // managing session
#include "CATDocumentServices.h"      // managing documents in session
#include "CATDocument.h"              // manipulating documents
#include "CATIDocRoots.h"             // browsing root objects in documents

// ProductStructure interfaces 
#include "CATIProduct.h"              // managing products    

// ObjectSpecModeler
#include "CATLISTV_CATISpecObject.h"  // managing SpecObjects
 
// Electrical interfaces
#include "CATIEleDocServices.h"       // initializing electrical environement 

// ElecRoutingItf
#include "CATIEwrRouteSegment.h"      // interface to list the wires in a bundle segment

// ElecAttrAccess
#include "CATIElecAttrAccess.h"				// interface to get electrical attributes
#include "CATICkeInst.h"

// ParmPublisher
#include "CATIParmPublisher.h"				// interface to get all instances under a product
#include "CATIInstance.h"							// interface to manage instance

// TypeDictionary
#include "CATITypeDictionary.h"				// interface to get type
#include "CATGlobalFunctions.h"				// class to get dictionary


int main (int argc, char * argv[] )
{ 
  //--------------------------------------------------------------------
  // 1. Prologue 
  //--------------------------------------------------------------------
  cout << endl << flush;
  cout << endl << flush;
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  
  // --- Creating the Session:  A session must always be created in a batch
  
  CATSession *pSession = NULL;
  
  char *sessionName = "CAAEwrListWiresInBundleSegment_Session";
  HRESULT rc = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(rc)) && (NULL != pSession))
  {
    cout << "> session created : " << sessionName <<endl << flush;
  }
  else
  {
    cout << "ERROR in creating session" << sessionName << endl << flush;
    return 1;
  }
  
  // --- Opening an existing document 
  //     The input parameter to this sample program must contain 
  //     the entire path and name of the document that is to be opened.  
  
  CATDocument *pDoc = NULL; // pDoc is a pointer to the document 
  
  cout << "> open document :"<< argv[1] << endl << flush;
  rc = CATDocumentServices::Open(argv[1], pDoc);
  if (SUCCEEDED(rc) && (NULL != pDoc))
  {
    cout << "> document opened " << endl << flush;
  }
  else
  {
    cout << "ERROR in opening document" << endl << flush;
    return 2;
  }
  
  // --- Retrieving root product of the opened document 
  
  CATIProduct* piRootProduct = NULL;// piRootProduct is a handle to document root product
  
  CATIDocRoots * pDocRoots = NULL;
  rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &pDocRoots);
  if ( FAILED(rc) || (NULL==pDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = pDocRoots->GiveDocRoots();
  pDocRoots->Release();
  pDocRoots=NULL;
  
  if ( (NULL!=pListRootProduct) && pListRootProduct->Size() )
  {
    CATBaseUnknown_var spUnkRootPrd = (*pListRootProduct)[1];
    if(NULL_var == spUnkRootPrd) return 4;
    
    rc = spUnkRootPrd->QueryInterface(IID_CATIProduct,(void **)&piRootProduct );
    
    delete pListRootProduct;
    pListRootProduct = NULL;
    //
    if  (SUCCEEDED(rc) && (NULL != piRootProduct))
      cout << "> root product found in document " << endl << flush;
    else
    {
      cout << "ERROR : Root product not found in document " << endl << flush;
      return 2;
    }
  }
  
  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  CATIEleDocServices * piElecDocServices = NULL;
 
  rc = pDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
 
  if (FAILED(rc) || (NULL == piElecDocServices)) return 4;

  rc = piElecDocServices->Initialize(); 
  
  if (SUCCEEDED(rc) )
  {
    cout << "> electrical environment initialized " << endl << flush;
  }
  else
  {
    cout << "ERROR : electrical environment initialization failed " << endl << flush;
  }
 
  piElecDocServices->Release();
  piElecDocServices=NULL;

  
  //--------------------------------------------------------------------
  // 3. Retrieving all geometrical bundles under the root product 
  //    and Selecting one geometrical bundle  
  //--------------------------------------------------------------------

  // --- Retrieving all geometrical bundles under root product 
	CATListValCATBaseUnknown_var *pListGeoBundle = piRootProduct->GetAllChildren();
  piRootProduct->Release();
  piRootProduct = NULL;
  
  int NumberOfGeoBundle = 0;
  if ( (NULL!=pListGeoBundle) && pListGeoBundle->Size() ) 
  {
    NumberOfGeoBundle = pListGeoBundle->Size();
		cout << "> number of geometrical bundle found in assembly : "<< NumberOfGeoBundle << endl << flush;
  }
  else
  {
    cout << "ERROR : no geometrical bundle found in assembly " << endl << flush;
    return 5;
  }

  // --- Selecting first geometrical bundle
	CATIElecAttrAccess * piElecObjectAttribute = NULL;
	CATBaseUnknown_var spUnkGBN = NULL_var;
	CATBoolean GBNFound = FALSE;
	for (int i = 1; (i <= NumberOfGeoBundle) && (!GBNFound); i++)
	{
		spUnkGBN = (*pListGeoBundle)[i];
		if(NULL_var == spUnkGBN) return 6;

		rc = spUnkGBN->QueryInterface(IID_CATIElecAttrAccess, (void **)&piElecObjectAttribute);
		if (SUCCEEDED(rc) && (NULL != piElecObjectAttribute))
		{
			CATUnicodeString objectElecType = "";
			CATUnicodeString GBNType = "ElecGeoBundle";
			piElecObjectAttribute->GetElecType(objectElecType);
			if (objectElecType == GBNType)
				GBNFound = TRUE;

			piElecObjectAttribute->Release();
			piElecObjectAttribute = NULL;
		}
	}
	delete pListGeoBundle;
	pListGeoBundle = NULL;


	//--------------------------------------------------------------------
  // 4. Retrieving all instances under the geometrical bundle 
  //    and Selecting one bundle segment 
  //--------------------------------------------------------------------

	// --- Retrieving all instances under geometrical bundle
	CATIParmPublisher * piGeoBundle = NULL;
	rc = spUnkGBN->QueryInterface(IID_CATIParmPublisher, (void **)&piGeoBundle);
	if (SUCCEEDED(rc) && (NULL != piGeoBundle))
	{
		cout << "> binding to CATIParmPublisher interface OK" <<endl << flush;
	}
	else
  {
    cout << "ERROR : binding to CATIParmPublisher interface failed " << endl << flush;
    return 7;
  }

	CATListValCATISpecObject_var spListInstance;
	piGeoBundle->GetAllChildren(CATIInstance::ClassName(), spListInstance);
	int NumberOfInstances = 0;
	if (spListInstance.Size())
	{
		NumberOfInstances = spListInstance.Size();
		cout << "> number of instances found in geometrical bundle : "<< NumberOfInstances << endl << flush;
  }
  else
  {
    cout << "ERROR : no instances found in geometrical bundle " << endl << flush;
    return 8;
  }
	piGeoBundle->Release();
	piGeoBundle = NULL;
	
	// --- Retrieving bundle segment type
	CATITypeDictionary_var spTypeDictionnary = CATGlobalFunctions::GetTypeDictionary();
	CATIType_var spBundleSegmentType = NULL_var;
	const CATUnicodeString BNSType = "BundleSegment";
	const CATUnicodeString ElecPackage = "Electrical";
	rc = spTypeDictionnary->FindTypeSafe(BNSType, ElecPackage, spBundleSegmentType);
	if (SUCCEEDED(rc) && (NULL_var != spBundleSegmentType))
	{
		cout << "> bundle segment type retrieved "<< endl << flush;
  }
  else
  {
    cout << "ERROR : retrieving of bundle segment type failed " << endl << flush;
    return 9;
  }

	// --- Selecting Bundle Segment.2 bundle segment
	CATIInstance_var spBNSInstance = NULL_var;
	CATIInstance * piBNSInstance = NULL;
	CATBoolean BNSFound = FALSE;
	for (int j = 1; (j <= NumberOfInstances) && (!BNSFound); j++)
	{
		spBNSInstance = spListInstance[j];
		if (NULL_var == spBNSInstance)
		{
			cout << "ERROR : binding to CATIInstance interface failed " << endl << flush;
			return 10;
		}
		piBNSInstance = spBNSInstance->IsSupporting(spBundleSegmentType);
		if (NULL != piBNSInstance)
		{
			rc = piBNSInstance->QueryInterface(IID_CATIElecAttrAccess, (void **)&piElecObjectAttribute);
			if (SUCCEEDED(rc) && (NULL != piElecObjectAttribute))
			{
				CATICkeInst_var spRefDes = NULL_var;
				rc = piElecObjectAttribute->Get("Elec_Ref_Des", spRefDes);
				piElecObjectAttribute->Release();
				piElecObjectAttribute = NULL;
				if (SUCCEEDED(rc) && (NULL_var != spRefDes))
				{
					CATUnicodeString BNSRefDes = "Bundle Segment.2";
					if (spRefDes->AsString() == BNSRefDes)
					{
						BNSFound = TRUE;
						break;
					}
				}
				else
				{
					cout << "ERROR : no Ref_Des found " << endl << flush;
				}
			}
			piBNSInstance->Release();
			piBNSInstance = NULL;
		}
	}


	if (BNSFound && (NULL != piBNSInstance))
	{
		cout << "> Bundle Segment.2 bundle segment selected "<< endl << flush;
	}
	else
	{
		cout << "ERROR : no bundle segment found " << endl << flush;
		return 11;
	}



  //--------------------------------------------------------------------
  // 5. List the Wires going through the bundle segment
  //-------------------------------------------------------------------- 

  CATIEwrRouteSegment *piEwrRouteSegment = NULL;
  rc = piBNSInstance->QueryInterface(IID_CATIEwrRouteSegment, (void **)&piEwrRouteSegment);
  piBNSInstance->Release();
  piBNSInstance = NULL;

  if ( SUCCEEDED(rc) && (NULL!=piEwrRouteSegment) )
  {
    cout << "> binding to CATIEwrRouteSegment interface OK" <<endl << flush;
  }
  else
  {
    cout << "ERROR : binding to CATIEwrRouteSegment interface failed " << endl << flush;
    return 12;
  }

  CATListValCATBaseUnknown_var* pListConductors = NULL;
  rc = piEwrRouteSegment->ListConductors(pListConductors);
  piEwrRouteSegment->Release();
  piEwrRouteSegment = NULL;

  if ( SUCCEEDED(rc) && (NULL!=pListConductors) )
  {
    int nbConductors = pListConductors->Size();
    cout << "> select bundle segment to analyse " <<endl << flush;
    cout << "> Number of conductors found in Bundle Segment :  "<< nbConductors << endl << flush;
    delete pListConductors;
    pListConductors = NULL;
  }
  else
  {
    cout << "ERROR : no conductors found in bundle segment " << endl << flush;
    return 13;
  }

  //--------------------------------------------------------------------
  // 11. Epilogue  
  //--------------------------------------------------------------------
  
  // --- removing document from session 
  rc = CATDocumentServices::Remove(*pDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 14;
  }
  // --- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 15;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}
