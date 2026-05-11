// COPYRIGHT DASSAULT SYSTEMES 2007
//==============================================================================================================================
//  Mission: The Use Case retrieves information of a Mech Import, copied from a CombinedCurve feature whose startUp definition exists in a CATALOG.
//           The authentication to seek this information is done by specifying the ClientID of the CombinedCurve StartUp Catalog.


//	The use case executes on the following input model
//  Please note that its mandatory to run this Use Case necessarily on the input model 
//  The CAAMmrImportWithClientId_Root.CATProduct and its included Part documents are located in the CAAMechanicalModeler.edu/InputData directory.
//  Moreover the UC does not modify or save the input model, but only seeks information from it

/*
 CAAMmrImportWithClientId_Root
						|
						|----CAAMmrImportWithClientId_Child1 (product)
						|							             | 
						|										 |CAAMmrImportWithClientId_Org 
						|															|
						|															|__Geometrical Set.1	
						|													                |
						|																    |__CombinedCurve.1
						|																	|
						|																	|__Point.1		
						|																	
						|			
						|----CAAMmrImportWithClientId_Child2 (product)
																 | 
																 |CAAMmrImportWithClientId_Copies 
        																			|
																					|__PartBody
																					|
																					|__External References
																							|
																							|__Copy_CombinedCurve.1
																							|
																							|__Copy_CombinedCurve.2
																							|																																																|
																							|__Copy_Point.1
*/
//	The use case is based on CAAMmrImportWithClientId_Root Product document. This document is composed of four components:
//         - Root Product
//                     . CAAMmrImportWithClientId_Child1
//							. Comp1-> CAAMmrImportWithClientId_Org.CATPart
//                     . CAAMmrImportWithClientId_Child2
//							. Comp2-> CAAMmrImportWithClientId_Copies.CATPart
//
//			Comp1: The CAAMmrImportWithClientId_Org Part document contains the following data
//							- Point.1
//							- CombinedCurve.1

//          Comp2: The CAAMmrImportWithClientId_Copies Part document has three copied features under External References
//							- Copy_CombinedCurve.1   copied out of assy context
//							- Copy_CombinedCurve.2   copied in assy context
//							- Copy_Point.1           copied in assy context


//  The Use Case begins with setting the authentication with ClientID, an essential pre-requisite 
//  for seeking information from a Mechanical Import
//  In the process it illustrates the failure to do so, since the pointed element is not loaded
//  Next it attempts to load the pointed element with a call to LoadPointedElement and illustrates its
//  failure to do so.
//  In the process, it demonstrates to the user the irrelevance of the call to LoadPointedElement in the
//  ClientID context
//  Reason being, that the process of authentication with the ClientID, pre-requisites loading the pointed
//  element. Hence the calls to LoadPointedElement as well as IsPointedElementLoaded are insignificant
//  since they always return E_FAIL, as illustrated by this UC

//  Subsequently it loads the pointed element and goes on to illustrate 
//  the success in setting the authentication with ClientID
//  It then demonstrates the SUCCESS in seeking all relevant information from various Mechanical Imports
//  viz. Copy_CombinedCurve.1  and Copy_CombinedCurve.2, thanks to the services exposed by 
//  CATIMmiMechanicalImportApplicative Interface, implemented by all Mechanical Imports

//  Finally it demonstrates the failure to set the authentication to Copy_Point.1, it being a copy of a
//  standard DS feature, a Point
//  User thus realizes the the ClientID authentication works only for those features which are copies
//  of features whose startups are defined in user catalogs.
//  While it fails for the feature copied from standard DS features

//==============================================================================================================================
//   How to execute :
// 
//   CAAMmrImportWithClientId InputPath
//
//   with    InputPath    : $WSROOT/CAAMechanicalModeler.edu/InputData
//           
//          
// Return code :
//   0 successful execution
//   1 execution failed
//
//==============================================================================================================================
// Steps         1- Checks the arguments
//				 2- Creates the Session
//				 3- Opens the CAAMmrImportWithClientId_Copies document 
//				 4- Retrieves elements from opened document
//						4-1 The MechanicalPart feature
//						4-2 Retrieve Copy_CombinedCurve.1 feature
//				 5- Failure to do a StartUp Catalog authentication when pointed element is not loaded
//						5.1- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
//						5.2- Illustrate failure to do a StartUp Catalog authentication on Copy_CombinedCurve.1
//							5.2.1 Setting the Catalog ID to a string for authentication
//							5.2.2 Actually doing an authentication
//				 6- Illustrate irrelevance of IsPointedElementLoaded and LoadPointedElement calls
//						6.1- Failure to retrieve the Load Status of the Pointed document
//						6.2- Failure to Load the pointed document
//				 7- Opens the CAAMmrApplMecImport_Root document
//				 8- Retrieve the root product from opened document
//				 9- Retrieve the Copy_CombinedCurve.1 feature from CAAMmrImportClientId_Child2.1, 
//					CombinedCurve.1 is copied without assembly context
//						9.1- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
//						9.2- Retrieve Source Feature 
//						9.3- Retrieve the Product Instance aggregating an instance of the representation of the pointed element, 
//						      It should fail here as feature is copied outof assembly context
//						9.4- Retrieve the loading status of the pointed document, It should fail here as this method is 
//						      IsPointedElementLoaded always returns failure in clientId context 
//				10- Retrieve the Copy_CombinedCurve.2 feature from CAAMmrImportClientId_Child2.1, CombinedCurve.2 is copied 
//					in assembly context
//				11- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
//						11.1- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
//						11.2- Retrieve Source Feature 
//						11.3- Retrieve the Product Instance aggregating the Representation of the Source Feature
//				12- Retrieve the Copy_Point.1 feature from CAAMmrImportClientId_Child2.1, Point.1 is copied without assembly context, 
//					 it is not instantiated from CombinedCurve Startup Catalog 
//				13- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
//						13.1- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
//						      It should fail here as Point.1 is DS feature, it is not instantiated from CombinedCurve Startup Catalog
//				14- Unload the component from the current session
//				15- Close the PLM session
//==============================================================================================================================
// MecModInterfaces
#include "CATMmrInterPartCopy.h"         // To copy mechanical feature
#include "CATIMmiMechanicalImportApplicative.h"

// ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATSession.h"  
#include "CATDocumentServices.h"         // Open, Save 
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATIAlias.h"
#include "CATInit.h"                     // To retrieve the root container

// Product Structure
#include "CATIProduct.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // To get the MechanicalPart

// System Framework
#include "CATString.h"

// Local Framework
#include "CAAMmrGetGeometry.h"           // To retrieve features
#include "CAAMmrGetPartFromProduct.h"

// MecModInterfaces
#include "CATIMmiMechanicalImportApplicative.h"
#include "CATIPrtContainer.h"

// System Framework
#include "CATString.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"

// Local Framework
#include "CAAMmrGetGeometry.h"         // To retrieve features
#include "CAAMmrGetPartFromProduct.h"  // To retrieve the Part from a Product 

// C++ Standard Library
#include <iostream.h>  

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif
int main(int iArgc, char *iArgv[])        		    
{  	
	
	//==========================================================================================================================
	// 1- Checks the arguments
	//==========================================================================================================================
	if ((2 != iArgc) ) 
	{
		cout << endl;
		cout << "CAAMmrImportWithClientId InputPath"<< endl;
		cout << "with : InputPath : $WSROOT/CAAMechanicalModeler.edu/InputData"<< endl;
		cout << endl;
		return 1;
	}
	cout << "The CAAMmrImportWithClientId main program begins ...."<< endl << endl;
	//==========================================================================================================================
	//2 - Creates Session
	//==========================================================================================================================
	char * pSessionName = "CAA_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(pSessionName,pSession);
	
	if (FAILED(rc) )
	{
		return 1;
	}
	cout <<"		A session is created" << endl;
	//==========================================================================================================================
	//3- Opens the CAAMmrImportWithClientId_Copies document 
	//==========================================================================================================================
	CATDocument *pDocument = NULL;
	CATDocument *pProductDocument = NULL;
	
	CATString InputData = iArgv[1] ;
	CATString DocumentName  = InputData + Slash + "CAAMmrImportWithClientId_Copies.CATPart";
	
	rc = CATDocumentServices::OpenDocument(DocumentName.ConvertToChar(), pDocument);
	if ( FAILED(rc) || ( NULL == pDocument) )
	{
		return 1;
	}
	
	cout << "The "<< DocumentName.ConvertToChar() <<" document is opened" << endl ;
	//==========================================================================================================================
	// 4- Retrieves elements from opened document
	//==========================================================================================================================
	// 4-1 The MechanicalPart feature
	CATInit * pInitOnDoc = NULL ;
	rc = pDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
	if ( FAILED(rc) )
	{
		cout << "Error in the CATInit interface"<< endl;
		return 1 ;
	}
	
	CATIPrtContainer * pIPrtContOnDocument = NULL ;
	pIPrtContOnDocument = (CATIPrtContainer*)pInitOnDoc->GetRootContainer("CATIPrtContainer");
	
	if ( NULL == pIPrtContOnDocument )
	{
		return 1 ;
	}
	
	// No more need of this interface
	pInitOnDoc->Release();
	pInitOnDoc = NULL ;
	
	CATISpecObject_var spSpecObjectOnMechPart = pIPrtContOnDocument->GetPart();
	if ( NULL_var == spSpecObjectOnMechPart )
	{
		return 1 ;
	}
	cout << "		The MechanicalPart feature has been found" << endl;
	
	pIPrtContOnDocument->Release();
	pIPrtContOnDocument = NULL ;
	
	// 4-2 Retrieve Copy_CombinedCurve.1 feature
	CATBaseUnknown * pSet = NULL ;
	rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPart,"Copy_CombinedCurve.1",&pSet);
	if ( FAILED(rc) || ( NULL == pSet) )
	{
		return 1 ;
	}
	cout << "Success in retrieving the Copy_CombinedCurve.1 feature from CAAMmrImportWithClientId_Copies"<<endl;
	
	//==========================================================================================================================
	// 5- Failure to do a StartUp Catalog authentication when pointed element is not loaded
	//==========================================================================================================================
    //5.1- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
	cout << endl << "Retrieving info from Copy_CombinedCurve.1"<<endl;
	CATBoolean LoadedPointedReference ;
	CATIProduct * piProductOnRoot = NULL;
	CATUnicodeString DocumentProductName;
	CATIMmiMechanicalImportApplicative *pIMecImportApplicativeOnResultCopy = NULL ;		
	rc = pSet->QueryInterface(IID_CATIMmiMechanicalImportApplicative,
							  (void**)&pIMecImportApplicativeOnResultCopy); 
	pSet->Release();
	pSet = NULL ;

	//5.2- Illustrate failure to do a StartUp Catalog authentication on Copy_CombinedCurve.1
	// 5.2.1 Setting the Catalog ID to a string for authentication
	CATUnicodeString ClientId = "SAMPLES";
	if (SUCCEEDED(rc))
	{
		// 5.2.2 Actually doing an authentication
		rc = pIMecImportApplicativeOnResultCopy->SetPointedElementClientId(ClientId);
		if (SUCCEEDED(rc))
		{
			cout << "		Success in setting the client ID for Copy_CombinedCurve.1. Expected since pointed element not loaded" << endl;
			return 1;
		}
		cout << "		Failure in setting the client ID for Copy_CombinedCurve.1. Expected since pointed element not loaded" << endl;
		
	//==========================================================================================================================
	// 6- Illustrate relevance of IsPointedElementLoaded and LoadPointedElement calls
	//==========================================================================================================================
		// 6.1- Failure to retrieve the Load Status of the Pointed Document
		rc = pIMecImportApplicativeOnResultCopy->IsPointedElementLoaded(LoadedPointedReference);
		if (FAILED(rc))
			return 1;
		
		cout << "		Success in retrieving the loading status of the pointed Document" << endl;
		cout << "		Success expected " << endl;
		
		// 6.2- Failure to Load the pointed Document
		rc = pIMecImportApplicativeOnResultCopy->LoadPointedElement();
		if (FAILED(rc))
			return 1;
		
		cout << "		Success in loading the pointed representation containing pointed element" << endl;
		cout << "		Success expected " << endl;
		
		//==========================================================================================================================
		//7- Opens the CAAMmrApplMecImport_Root document 
		//==========================================================================================================================
		DocumentProductName  = InputData + Slash + "CAAMmrImportWithClientId_Root.CATProduct";
		
		rc = CATDocumentServices::OpenDocument(DocumentProductName.ConvertToChar(), pProductDocument);
		if ( FAILED(rc) || ( NULL == pProductDocument) )
		{
			cout << endl <<"The "<< DocumentProductName.ConvertToChar() <<" document is not opened" << endl ;
			return 1;
		}
		
		cout << "The "<< DocumentProductName.ConvertToChar() <<" document is opened  " << endl ;
		
		//==========================================================================================================================
		//8- Retrieve the root product from opened document
		//==========================================================================================================================
		CATIDocRoots * piDocRootsOnDoc = NULL;
		rc = pProductDocument->QueryInterface(IID_CATIDocRoots,(void**) &piDocRootsOnDoc);
		
		if ( SUCCEEDED(rc) ) 
		{
			// Gets the root product which is the first element of root elements
			CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc->GiveDocRoots();
			
			if ( NULL == pRootProducts )
				return 1 ;
			
			if (pRootProducts->Size() > 0 )
			{  
				CATBaseUnknown_var spRootProduct = (*pRootProducts)[1];
				
				// Gets CATIProduct handle on the root product.
				if ( NULL_var != spRootProduct )
					rc = spRootProduct->QueryInterface(IID_CATIProduct,(void**) &piProductOnRoot);     
				
				delete pRootProducts;
				pRootProducts = NULL;
			}
			piDocRootsOnDoc->Release();
			piDocRootsOnDoc = NULL ;
		}
		
		if ( NULL == piProductOnRoot )
			return 1 ;
		
		cout <<"The root product has been found" << endl;
		piProductOnRoot->Release();
		piProductOnRoot = NULL ;
		
		//==========================================================================================================================
		//9- Retrieve the CombinedCurve.1 feature from CAAMmrImportClientId_Child2.1
		//   CombinedCurve.1 is copied without assembly context
		//==========================================================================================================================
		CATBaseUnknown_var spPointedElement1;
		CATBaseUnknown_var spSourceProductInstance1;
		//9.1- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
		rc = pIMecImportApplicativeOnResultCopy->SetPointedElementClientId(ClientId);
		if (FAILED(rc))
			return 1;
		
		cout << "		Success in setting the client ID for Copy_CombinedCurve.1, now that pointed element is loaded" << endl;
		//9.2- Retrieve Source Feature 
		rc = pIMecImportApplicativeOnResultCopy->GetPointedElement(spPointedElement1);
		if (FAILED(rc))
			return 1;
		
		cout << "		Success in retrieving Source Feature from Copy_CombinedCurve.1" << endl;
		
		CATIAlias_var aliasOfSourceFeature1 = spPointedElement1 ;
		cout <<"		The source feature is " << aliasOfSourceFeature1->GetAlias().ConvertToChar() << endl;
		
		//9.3- Retrieve the Product Instance aggregating an instance of the representation of the pointed element
		//      It should fail here as feature is copied outof assembly context
		rc = pIMecImportApplicativeOnResultCopy->GetSourceProduct(spSourceProductInstance1);
		if (SUCCEEDED(rc))
			return 1;   
		
		cout << "		Failure in GetSourceProduct since Copy_CombinedCurve.1 is an out of assy context copy" << endl;
		
		//9.4- Retrieve the loading status of the pointed document,
		//      IsPointedElementLoaded always returns success in clientId context  
		rc = pIMecImportApplicativeOnResultCopy->IsPointedElementLoaded(LoadedPointedReference);
		if (FAILED(rc))
			return 1; 
		
		pIMecImportApplicativeOnResultCopy->Release();
		pIMecImportApplicativeOnResultCopy = NULL;
		
	} else
		return 1;
	
	//==========================================================================================================================
	//10- Retrieve the CombinedCurve.2 feature from CAAMmrImportClientId_Child2.1
	//    CombinedCurve.2 is copied in assembly context
	//==========================================================================================================================
	cout << endl << "Retrieving information from Copy_CombinedCurve.2" << endl; 
	CATUnicodeString NameFeatureToCopy = "Copy_CombinedCurve.2";
	CATBaseUnknown * pCopiedFeatureInAssyContext = NULL ;
	rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPart ,NameFeatureToCopy ,&pCopiedFeatureInAssyContext );
	if (FAILED(rc))
		return 1;
	
	cout << "		Success in retrieving Copy_CombinedCurve.2 under CAAMmrClienId_Copies" << endl;
	
	//==========================================================================================================================
	//11- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
	//==========================================================================================================================
	CATBaseUnknown_var spPointedElement2;
	CATBaseUnknown_var spSourceProductInstance2;
	if (NULL != pCopiedFeatureInAssyContext)
		rc = pCopiedFeatureInAssyContext->QueryInterface(IID_CATIMmiMechanicalImportApplicative,
		(void**)&pIMecImportApplicativeOnResultCopy); 
	else
		return 1;
	
	if (SUCCEEDED(rc))
	{  
		//11.1- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
		rc = pIMecImportApplicativeOnResultCopy->SetPointedElementClientId(ClientId);
		if (FAILED(rc))
			return 1;
		
		cout << "		Success in setting the client ID for Copy_CombinedCurve.2" << endl;
		//11.2- Retrieve Source Feature 
		rc = pIMecImportApplicativeOnResultCopy->GetPointedElement(spPointedElement2);
		if (FAILED(rc))
			return 1;
		
		cout << "		Success in retrieving source feature of Copy_CombinedCurve.2" << endl;
		
		CATIAlias_var aliasOfSourceFeature2 = spPointedElement2 ;
		cout <<"		The source feature is " << aliasOfSourceFeature2->GetAlias().ConvertToChar() << endl ;
		
		//11.3- Retrieve the Product Instance aggregating the Representation of the Source Feature
		rc = pIMecImportApplicativeOnResultCopy->GetSourceProduct(spSourceProductInstance2);
		if (FAILED(rc))
			return 1;
		
		cout << "		Success in GetSourceProduct on Copy_CombinedCurve.2" << endl;
		
		CATIAlias_var aliasOfSourceProductInstance = spSourceProductInstance2 ;
		cout <<"The source product instance is " << aliasOfSourceProductInstance->GetAlias().ConvertToChar() << endl << endl;
		
		pIMecImportApplicativeOnResultCopy->Release();
		pIMecImportApplicativeOnResultCopy = NULL;
		
		pCopiedFeatureInAssyContext->Release();
		pCopiedFeatureInAssyContext = NULL;
		
	} else
		return 1;
	
	//==========================================================================================================================
	//12- Retrieve the Copy_Point.1 feature from CAAMmrClienId_Copies
	//    Copy_Point.1 is copied without assembly context, it is not instantiated from CombinedCurve Startup Catalog  
	//==========================================================================================================================
	cout << "Retrieving information from Copy_Point.1" << endl; 
    NameFeatureToCopy = "Copy_Point.1";
	CATBaseUnknown *pCopiedFeature_Point = NULL;
	rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPart,NameFeatureToCopy ,&pCopiedFeature_Point);
	if (FAILED(rc))
	{
		cout << "		Failure in retrieving the copied point from CAAMmrClienId_Copies" <<endl;
		return 1;
	}
	cout << "		Success in retrieving the copied point from CAAMmrClienId_Copies" << endl;
	
	//==========================================================================================================================
	//13- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
	//==========================================================================================================================
	if (NULL != pCopiedFeature_Point)
		rc = pCopiedFeature_Point->QueryInterface(IID_CATIMmiMechanicalImportApplicative,
		(void**)&pIMecImportApplicativeOnResultCopy); 
	if (SUCCEEDED(rc))
	{   
		//13.1- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
		//      It should fail here as Point.1 is DS feature, it is not instantiated from CombinedCurve Startup Catalog
		rc = pIMecImportApplicativeOnResultCopy->SetPointedElementClientId(ClientId);
		if (SUCCEEDED(rc))
			return 1;
		
		cout << "		Failure in setting the client ID" << endl;
		cout << "		Expected since Copy_Point.1 is a copy of a standard DS feature" << endl;
		cout << "		ClientID authentication is valid only for copies of features instantiated from catalogs" << endl;
		
		pIMecImportApplicativeOnResultCopy->Release();
		pIMecImportApplicativeOnResultCopy = NULL;
		
		pCopiedFeature_Point->Release();
		pCopiedFeature_Point = NULL;
	} 
	else
		return 1;
	//==========================================================================================================================
	//14- Unload the component from the current session
	//==========================================================================================================================
	rc = CATDocumentServices::Remove (*pProductDocument);
	if (FAILED(rc)) 
		return 1;
	
	cout << "The "<< DocumentProductName.ConvertToChar() <<endl;
	cout <<" documents and its included files are closed" << endl ;
	
    pDocument = NULL ;
	pProductDocument = NULL ;
	
    //==========================================================================================================================
	//15- Close the PLM session
	//==========================================================================================================================
	rc = ::Delete_Session(pSessionName);
	if (FAILED(rc)) 
		return 1;
	
	cout << "		Session has been closed" << endl<<endl<<endl;
	return 0;
	
}
