// COPYRIGHT DASSAULT SYSTEMES 2007
//==============================================================================================================================
// Mission: The Use Case copies feature within a Product Model in and without assembly context

//The use case executes on the following input model
//Please note that its mandatory to run this Use Case necessarily on the input model
//The CAAMmrApplMecImport_Root.CATProduct and its included Part documents are located in the CAAMechanicalModeler.edu/InputData directory.

//              The input model. 
/*
 CAAMmrApplMecImport_Root
						|
						|----CAAMmrApplMecImport_Child1 (product)
						|							             | 
						|										 |___CAAMmrApplMecImport_RepFeatOrg 
						|															|
						|   														|__XY Plane
						|															|
						|															|__YZ Plane
						|	    													|
						|															|__ZX Plane
						|															|
						|															|__PartBody	
						|													                |
						|																    |__Point.1
						|																	|
						|																	|__Point.2		
						|																	|
						|																	|__Line.1
						|			
						|----CAAMmrApplMecImport_Child2 (product)
																 | 
																 |__CAAMmrApplMecImport_RepFeatCopied 
        																			|
           													    					|__XY Plane
        																			|
        																			|__YZ Plane
			    																	|
																					|__ZX Plane
																					|
																					|__PartBody	
															              			
*/

//	The use case is based on CAAMmrApplMecImport_Root Product document. This document is composed of four components:
//         - Root Product
//                     . CAAMmrApplMecImport_Child1
//							. Comp1-> CAAMmrApplMecImport_RepFeatOrg.CATPart
//                     . CAAMmrApplMecImport_Child2
//							. Comp2-> CAAMmrApplMecImport_RepFeatCopied.CATPart
//
//			Comp1: The CAAMmrApplMecImport_RepFeatOrg Part document contains the following data
//							- Point.1
//							- Point.2
//							- Line.1

//          Comp2: The CAAMmrApplMecImport_RepFeatCopied Part document is having empty PartBody


//                The resulted output model. 
/*
 CAAMmrApplMecImport_Root
						|
						|----CAAMmrApplMecImport_Child1 (product)
						|							             | 
						|										 |___CAAMmrApplMecImport_RepFeatOrg 
						|															|
						|   														|__XY Plane
						|															|
						|															|__YZ Plane
						|	    													|
						|															|__ZX Plane
						|															|
						|															|__PartBody	
						|													                |
						|																    |__Point.1
						|																	|
						|																	|__Point.2		
						|																	|
						|																	|__Line.1
						|			
						|----CAAMmrApplMecImport_Child2 (product)
																 | 
																 |__CAAMmrApplMecImport_RepFeatCopied 
        																			|
           													    					|__XY Plane
        																			|
        																			|__YZ Plane
			    																	|
																					|__ZX Plane
																					|
																					|__PartBody	
															              					|
																							|__CopyOfLine.1_InAssyCtx
																							|
																							|__CopyOfLine.1_WithoutAssyCtx		
*/

//	This use case does two kinds of copy, with calls to the CATMmrInterPartCopy APIs
//		1.Copies Line.1 feature under CAAMmrApplicativeImport_RepFeatCopied Part in Assy Context
//		  viz. CopyOfLine.1_InAssyCtx

//		2.Copies Line.1 feature under CAAMmrApplicativeImport_RepFeatCopied Part without Assy Context
//		  viz. CopyOfLine.1_WithoutAssyCtx

//	The Use Case further analyses the result, with calls to the CATIMmiApplicativeMechanicalImport APIs. 
//  It retrieves information associated with the copied feature
//  The source feature for copy is output

//  Lastly, and most importantly, the Use Case illustrates the failure to retrieve the relevant information 
//  from the copied feature, if you do not have the proper authorizationfor this retrieval. It further illustrates 
//  to us a mechanism to authorize retrieval of data by associating the copied feature with an Identifier 
//  (using the CATIMmiMechanicalImportApplicative Interface) during the copying process.
//==============================================================================================================================
//   How to execute :
// 
//   CAAMmrApplicativeImport InputPath Feature_name
//
//   with    InputPath    : $WSROOT/CAAMechanicalModeler.edu/InputData
//			 Feature_name : the name of the feature to copy
//           
//
//          
// Return code :
//   0 successful execution
//   1 execution failed
//
//==============================================================================================================================
// Steps        1- Checks the arguments
//				2- Creates the Session
//				3- Opens the CAAMmrApplMecImport_Root document 
//				4- Retrieve the root product from opened document
//				5- Retrieve components of the root product
//  				5.1- Retrieve direct children viz.CAAMmrApplMecImport_Child1 and CAAMmrApplMecImport_Child2
//	    			5.2- Retrieve the component of CAAMmrApplMecImport_Child1
//		    		5.3- Retrieve the component of CAAMmrApplMecImport_Child2
//			    	5.4- Retrieve the Part document from CAAMmrApplMecImport_Child1 viz.CAAMmrApplMecImport_RepFeatOrg
//				    5.5- Retrieve the Part document from CAAMmrApplMecImport_Child2 viz.CAAMmrApplMecImport_RepFeatCopied
//		    		5.6- Retrieve the feature from CAAMmrApplMecImport_RepFeatOrg part document
//				6- Retrieve the CATMmrInterPartCopy pointer for setting data for copying
//					6.1- Seek a CATISpecObject_var type on source and target Part, to set as a parameter for copy later
//					6.2- Retrieve the CATMmrInterPartCopy pointer 
//				7- Copy the feature from CAAMmrApplicativeImport_RepFeatOrg under CAAMmrApplicativeImport_RepFeatCopied
//					7.1- Sets an applicative identifier to be assigned to the Mechanical Import, an output of the copy process
//					7.2- set the source and target for copying, 
//						 These two methods are mandatory to make for contextual link(copy in assembly context)
//					7.3- Set the Link Mode to TRUE
//					     Mandatory since only then the copied feature is an External Reference
//					7.4- Executes the copy
//					7.5- Retrieves the result
//					7.6- Reset the ptCATMmrInterPartCopy for the next Copy
//				8- Analyse the result of copying the feature in Assy Context
//					8.1- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
//					8.2- Confirm FAILURE to retrieve source feature from the copy result (since not yet authorized)
//					8.3- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
//					8.4- Retrieve the Load Status of the Pointed document
//					8.5- Confirm SUCCESS in retrieving Source Feature from Copy Result (since it is currently authorized)
//					8.6- Retrieve the Product Instance aggregating an instance of the representation of the pointed element
//					8.7- Confirm Source Feature used for copying is same as the source feature retrieved from Copy Result
//				9- Confirm Product Instance retrieved above is the same as the source Instance 
//			   10- Second copy : without Assembly context, 
//				   Copy the input feature from CAAMmrApplicativeImport_RepFeatOrg  inside CAAMmrApplicativeImport_RepFeatCopied
//				   10.1- Reinitialize the CATMmrInterPartCopy pointer 
//				   10.2- Set the Link Mode to TRUE
//				    	 Mandatory since only then the copied feature is an External Reference
//						 implementing the CATIMmiMechanicalImportApplicative, an Interface. which provides services 
//						 to retrieve information of the original feature from its copy
//				   10.3- Sets an applicative identifier to be assigned to the Mechanical Import, an output of the copy process
//				    	 This is to authorize seeking relevant information from the copied feature later
//				   10.4- Executes the copy
//				   10.5- Retrieves the result
//				   10.6- Reset ptCATMmrInterPartCopy
//			   11- Analyse the result of copying the feature: without Assembly context
//				   11.1- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
//				   11.2- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
//				   11.3- Retrieve the Load Status of the Pointed document
//				   11.4- Confirm SUCCESS in retrieving Source Feature from Copy Result
//				   11.5- Retrieve the Product Instance it should Fail in Copy without Assembly Context
//				   11.6- Confirm Source Feature used for copying is same as the source feature retrieved from Copy Result
//			   12- Save the modified documents
//				   12.1- Save the CAAMmrApplMecImport_RepFeatCopied
//				   12.2- Save the CAAMmrApplMecImport_Child2
//				   12.3- Save the CAAMmrApplMecImport_Root
//			   13- Close document
//			   14- Close the PLM session
//==============================================================================================================================

// MecModInterfaces
#include "CATMmrInterPartCopy.h"         // To copy mechanical feature
#include "CATIMmiMechanicalImportApplicative.h"
#include "CAAMmrGUIDForApplicativeImport.h"

// ObjectModelerBase Framework
#include "CATSessionServices.h"          // Create_Session and Delete_Session
#include "CATDocumentServices.h"         // Open, Save 
#include "CATDocument.h"
#include "CATIDocRoots.h"
#include "CATIAlias.h"
#include "CATSession.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATBaseUnknown.h"

// Product Structure
#include "CATIProduct.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"              // To get the MechanicalPart
#include "CATILinkableObject.h"  

// System Framework
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATBoolean.h"

// Local Framework
#include "CAAMmrGetGeometry.h"           // To retrieve features
#include "CAAMmrGetPartFromProduct.h"    // To retrieve the Part from a Product 

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
	if (3 != iArgc) 
	{
		cout << endl;
		cout << "CAAMmrApplicativeImport InputPath Feature_name"<< endl;
		cout << "with : InputPath    : $WSROOT/CAAMechanicalModeler.edu/InputData"<< endl;
		cout << "       Feature_name : the name of the feature to copy"<< endl;
		cout << endl;
		return 1;
	}
	cout << "The CAAMmrApplicativeImport main program begins ...."<< endl << endl;
	
	//==========================================================================================================================
	//2- Creates the Session
	//==========================================================================================================================
	char * pSessionName = "CAA_Sample_Session";
	CATSession *pSession = NULL;
	HRESULT rc = ::Create_Session(pSessionName,pSession);
	
	if (FAILED(rc) )
		return 1;

	cout <<"   A session is created" << endl;
	
	//==========================================================================================================================
	//3- Opens the CAAMmrApplMecImport_Root document 
	//==========================================================================================================================
	CATDocument *pProductDocument = NULL;
	CATUnicodeString InputData = iArgv[1] ;
	CATUnicodeString DocumentProductName  = InputData + Slash + "CAAMmrApplMecImport_Root.CATProduct";
	
	rc = CATDocumentServices::OpenDocument(DocumentProductName.ConvertToChar(), pProductDocument);
	if ( FAILED(rc) || ( NULL == pProductDocument) )
	{
		cout << "   The "<< DocumentProductName.ConvertToChar() <<" document is not opened" << endl ;
		return 1;
	}
	
	cout << "   The "<< DocumentProductName.ConvertToChar() <<" document is opened  " << endl ;
	
    //==========================================================================================================================
	//4- Retrieve the root product from opened document
	//==========================================================================================================================

	CATIProduct * piProductOnRoot = NULL;
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
	
	cout <<"   The root product has been found" << endl;
	
	//==========================================================================================================================
	//5- Retrieve components of the root product
	//==========================================================================================================================
	CATListValCATBaseUnknown_var * pListDirectChildren = piProductOnRoot->GetChildren(); 
	if ( (NULL ==pListDirectChildren) || ( pListDirectChildren->Size() !=2) )
        return 1 ;
	
	piProductOnRoot->Release();
	piProductOnRoot = NULL ;
	
	//5.1- Retrieve direct children viz.CAAMmrApplMecImport_Child1 and CAAMmrApplMecImport_Child2
	CATIProduct_var spComp1 = (*pListDirectChildren)[1] ;
	CATIProduct_var spComp2 = (*pListDirectChildren)[2] ;
	
	if ( (NULL_var == spComp1) || (NULL_var == spComp2) )
        return 1 ;

	cout << "   The direct children of the root product has been found" << endl;
	
	delete pListDirectChildren ;
	pListDirectChildren = NULL ;
	
	//5.2- Retrieve the component of CAAMmrApplMecImport_Child1
	pListDirectChildren = spComp1->GetChildren(); 
	if ( (NULL ==pListDirectChildren) || (pListDirectChildren->Size()!=1) )
        return 1 ;
	
	// Retrieve Object of CAAMmrApplMecImport_Child1
	CATIProduct_var spComp3 = (*pListDirectChildren)[1] ;
	
	if ( NULL_var == spComp3 )
        return 1 ;

	cout <<"   Retrieved Objects of CAAMmrApplMecImport_Child1" << endl;
	delete pListDirectChildren ;
	pListDirectChildren = NULL ;

	//5.3- Retrieve the component of CAAMmrApplMecImport_Child2
	pListDirectChildren = spComp2->GetChildren(); 
	if ( (NULL ==pListDirectChildren) || (pListDirectChildren->Size()!=1) )
        return 1 ;
	
	// Retrieve Object of CAAMmrApplMecImport_Child2
	CATIProduct_var spComp4 = (*pListDirectChildren)[1] ;
	
	if ( NULL_var == spComp4 )
        return 1 ;
	
	delete pListDirectChildren ;
	pListDirectChildren = NULL ;
	
	cout <<"   Retrieved Objects of CAAMmrApplMecImport_Child2" << endl;
	
	//5.4- Retrieve the Part document from CAAMmrApplMecImport_Child1 viz.CAAMmrApplMecImport_RepFeatOrg
	CATISpecObject_var spSpecObjectOnMechPartOfRepFeatOrg ;
	rc = ::CAAMmrGetPartFromProduct( spComp3, spSpecObjectOnMechPartOfRepFeatOrg );
	
	if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfRepFeatOrg) )
		return 1 ;
	
	cout << "      The Part feature  of CAAMmrApplMecImport_Child1 has been found" << endl;
	
	//5.5- Retrieve the Part document from CAAMmrApplMecImport_Child2 viz.CAAMmrApplMecImport_RepFeatCopied
	CATISpecObject_var spSpecObjectOnMechPartOfRepFeatCopied ;
	rc = ::CAAMmrGetPartFromProduct( spComp4, spSpecObjectOnMechPartOfRepFeatCopied );
	
	if ( FAILED(rc) || ( NULL_var == spSpecObjectOnMechPartOfRepFeatCopied) )
		return 1 ;
	
	cout << "      The Part feature  of CAAMmrApplMecImport_Child2 has been found" << endl;
	
    //5.6- Retrieve the feature from CAAMmrApplMecImport_RepFeatOrg part document
	CATBaseUnknown * pFeatureToCopy = NULL ;
	CATUnicodeString NameFeatureToCopy = iArgv[2];
	rc = ::CAAMmrGetGeometry(spSpecObjectOnMechPartOfRepFeatOrg,NameFeatureToCopy,&pFeatureToCopy);
	if ( FAILED(rc) || ( NULL == pFeatureToCopy) )
		return 1 ;

    cout<<"      Feature to copy is "<<iArgv[2]<<endl;
	
	//Gets CATBaseUnknown handle on the feature to copy
	CATBaseUnknown_var spFeatureToCopy = pFeatureToCopy;
	
	//Release pFeatureToCopy
	if(NULL != pFeatureToCopy)
	{
		pFeatureToCopy ->Release();
		pFeatureToCopy = NULL ;
	}
	
    //==========================================================================================================================
	//6- Retrieve the CATMmrInterPartCopy pointer for setting data for copying
	//==========================================================================================================================
	//6.1- Seek a CATISpecObject_var type on source and target Part, to set as a parameter for copy later
	CATISpecObject_var SourceToCopy = spFeatureToCopy ;
	CATISpecObject_var Target       = spSpecObjectOnMechPartOfRepFeatCopied ;
    
	//6.2- Retrieve the CATMmrInterPartCopy pointer 
	CATMmrInterPartCopy * ptCATMmrInterPartCopy = new CATMmrInterPartCopy (SourceToCopy,Target) ;
	
	//==========================================================================================================================
	//7- Copy the feature from CAAMmrApplicativeImport_RepFeatOrg under CAAMmrApplicativeImport_RepFeatCopied
	//==========================================================================================================================
	//7.1- Sets an applicative identifier to be assigned to the Mechanical Import, an output of the copy process
	ptCATMmrInterPartCopy ->SetImportApplicativeId(CAAMmrGUIDForApplicativeImport);
	
	//7.2- set the source and target for copying
	//     These two methods are mandatory to make for contextual link(copy in assembly context)
	ptCATMmrInterPartCopy ->SetSourceInstance(spComp1);
	ptCATMmrInterPartCopy ->SetTargetInstance(spComp2);
	
	//7.3- Set the Link Mode to TRUE
    //     Mandatory since only then the copied feature is an External Reference
	CATBoolean CopyWithLink = TRUE;
	ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 
	
	//7.4- Executes the copy
	CATUnicodeString ErrorMsg ;
	rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg);
	if ( FAILED(rc) )
	{
		cout <<" Msg=" << ErrorMsg.ConvertToChar() << endl;
		return 1 ;
	}
	cout <<"      Run is ok" << endl;
	
	//7.5- Retrieves the result
	CATISpecObject_var ResultCopyInAssyContext ;
	rc = ptCATMmrInterPartCopy ->GetResult(ResultCopyInAssyContext);
	if ( SUCCEEDED(rc) && (NULL_var != ResultCopyInAssyContext) )
	{
		CATIAlias_var alias = ResultCopyInAssyContext  ;
		if ( NULL_var != alias )
		{
			cout <<"      The result of the copy in assyContext is" ;
			cout <<" " << alias->GetAlias().ConvertToChar() << endl ;
		}
		else return 1 ;
	}
    //7.6- Reset the ptCATMmrInterPartCopy for the next Copy
	delete ptCATMmrInterPartCopy;
	ptCATMmrInterPartCopy = NULL;
	
    //==========================================================================================================================
	//8- Analyse the result of copying the feature in Assy Context
	//==========================================================================================================================
	cout<<"Analysing the result of copy starts...."<<endl;
	//8.1- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
	CATBoolean LoadedPointedReference ;
	CATBaseUnknown_var spPointedElement1;
	CATBaseUnknown_var spSourceProductInstance1;
	CATIMmiMechanicalImportApplicative *pIMecImportApplicativeOnResultCopy = NULL ;		
	rc = ResultCopyInAssyContext->QueryInterface(IID_CATIMmiMechanicalImportApplicative,
												 (void**)&pIMecImportApplicativeOnResultCopy); 
	if (SUCCEEDED(rc))
	{
		//8.2- Confirm FAILURE to retrieve source feature from the copy result (since not yet authorized)
		rc = pIMecImportApplicativeOnResultCopy->GetPointedElement(spPointedElement1);
		if (SUCCEEDED(rc))
		{
			cout << "Success in retrieving the pointed element which is not expected" << endl;
			return 1;
		}
		cout << "Failure in retrieving the pointed element which is expected" << endl;
		cout << "since it is done prior to setting the applicative ID" << endl;
		
		//8.3- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
		rc = pIMecImportApplicativeOnResultCopy->SetApplicativeId(CAAMmrGUIDForApplicativeImport);
		if (FAILED(rc))
			return 1;
		cout << "Success in setting the identifier of Mechanical Import which authorizes seeking relevant information from it" << endl;
		
		//8.4- Retrieve the Load Status of the Pointed document
		rc = pIMecImportApplicativeOnResultCopy->IsPointedElementLoaded(LoadedPointedReference);
		if (FAILED(rc) || (FALSE == LoadedPointedReference))
			return 1;
		
		cout << "Success in retrieving the loading status of the pointed document" << endl;
		
		//8.5- Confirm SUCCESS in retrieving Source Feature from Copy Result (since it is currently authorized)
		rc = pIMecImportApplicativeOnResultCopy->GetPointedElement(spPointedElement1);
		if (FAILED(rc))
			return 1;
		cout << "Success in retrieving Source Feature from Copy Result (since it is currently authorized)" << endl;
		
		//8.6- Retrieve the Product Instance aggregating an instance of the representation of the pointed element
		rc = pIMecImportApplicativeOnResultCopy->GetSourceProduct(spSourceProductInstance1);
		if (FAILED(rc))
			return 1;
		cout << "Success in retrieving the Product Instance aggregating an instance of the representation of the pointed element" << endl;
		
		pIMecImportApplicativeOnResultCopy->Release();
		pIMecImportApplicativeOnResultCopy = NULL;
		
	} else
		return 1;
	
	//8.7- Confirm Source Feature used for copying is same as the source feature retrieved from Copy Result
	if ( FALSE == spFeatureToCopy->IsEqual(spPointedElement1) ) 
		return 1;
	cout << "Confirmed Source Feature used for copying is same as the source feature retrieved from Copy Result" << endl;		

	//==========================================================================================================================
	//9- Confirm Product Instance retrieved above is the same as the source Instance 
	//==========================================================================================================================
    //Gets CATBaseUnknown_var handle on retrieved instance and source instance 
	CATBaseUnknown_var sp1 = spSourceProductInstance1;
	CATBaseUnknown_var sp2 = spComp1;

	if ( FALSE == sp1->IsEqual(sp2) ) 
			return 1;
		cout << "Confirmed Product Instance retrieved above is the same as the source Instance" << endl;		

	//==========================================================================================================================
	//10- Second copy : without Assembly context
	//    Copy the input feature from CAAMmrApplicativeImport_RepFeatOrg  inside CAAMmrApplicativeImport_RepFeatCopied. 
	//==========================================================================================================================
    cout<<"Copying feature without Assembly context starts...."<<endl;
	
	//10.1- Reinitialize the CATMmrInterPartCopy pointer 
	ptCATMmrInterPartCopy =  new CATMmrInterPartCopy (SourceToCopy,Target) ;	
	
	//10.2-  Set the Link Mode to TRUE
	//		 Mandatory since only then the copied feature is an External Reference
	//		 implementing the CATIMmiMechanicalImportApplicative, an Interface. which provides services 
	//	     to retrieve information of the original feature from its copy
	ptCATMmrInterPartCopy ->SetLinkMode(CopyWithLink) ; 
	
	//10.3- Sets an applicative identifier to be assigned to the Mechanical Import, an output of the copy process
	//		This is to authorize seeking relevant information from the copied feature later
	ptCATMmrInterPartCopy ->SetImportApplicativeId(CAAMmrGUIDForApplicativeImport);
	
	
	//10.4- Executes the copy
	CATUnicodeString ErrorMsg1 ;
	rc = ptCATMmrInterPartCopy ->Run(&ErrorMsg1);
	if ( FAILED(rc) )
	{
		cout <<" Msg=" << ErrorMsg1.ConvertToChar() << endl;
		return 1 ;
	}
	cout <<"      Run is ok" << endl;
	
	//10.5- Retrieves the result
	CATISpecObject_var ResultCopyOutOfAssyContext ;
	rc = ptCATMmrInterPartCopy ->GetResult(ResultCopyOutOfAssyContext);
	if ( SUCCEEDED(rc) && (NULL_var != ResultCopyOutOfAssyContext) )
	{
		CATIAlias_var alias = ResultCopyOutOfAssyContext  ;
		if ( NULL_var != alias )
		{
			cout <<"      The result of the copy out of assyContext is" ;
			cout <<" " << alias->GetAlias().ConvertToChar() << endl ;
		}
		else return 1 ;
	}
	
	//10.6- Reset ptCATMmrInterPartCopy
	delete ptCATMmrInterPartCopy;
	ptCATMmrInterPartCopy = NULL;
	
	//==========================================================================================================================
	//11- Analyse the result of copying the feature: without Assembly context
	//==========================================================================================================================
	cout<<"Analyse the result of Copying feature without Assembly context starts...."<<endl;
	CATBaseUnknown_var spPointedElement2;
	//11.1- Seek the CATIMmiMechanicalImportApplicative* type on the Copied feature
	rc = ResultCopyOutOfAssyContext->QueryInterface(IID_CATIMmiMechanicalImportApplicative,
		                                            (void**)&pIMecImportApplicativeOnResultCopy); 
	if (SUCCEEDED(rc))
	{
		// 11.2- Set the identifier of Mechanical Import which authorizes seeking relevant information from it
		rc = pIMecImportApplicativeOnResultCopy->SetApplicativeId(CAAMmrGUIDForApplicativeImport);
		if (FAILED(rc))
			return 1;
		
		cout << "Success in setting the identifier of Mechanical Import which authorizes seeking relevant information from it" << endl;
		
		// 11.3- Retrieve the Load Status of the Pointed document
		rc = pIMecImportApplicativeOnResultCopy->IsPointedElementLoaded(LoadedPointedReference);
		if (FAILED(rc) || (FALSE == LoadedPointedReference))
			return 1;
		
		cout << "Success in retrieving the loading status of the pointed document" << endl;
		
		// 11.4- Confirm SUCCESS in retrieving Source Feature from Copy Result
		rc = pIMecImportApplicativeOnResultCopy->GetPointedElement(spPointedElement2);
		if (FAILED(rc))
			return 1;
		
		cout << "Success in retrieving Source Feature from Copy Result" << endl;
		
		// 11.5- Retrieve the Product Instance it should Fail in Copy without Assembly Context
		CATBaseUnknown_var spSourceProductInstance2;
		rc = pIMecImportApplicativeOnResultCopy->GetSourceProduct(spSourceProductInstance2);
		if (SUCCEEDED(rc))
			return 1;
		cout << "Failure in retrieving the Product Instance it should Fail in Copy without Assembly Context" << endl;
		
		//release pIMecImportApplicativeOnResultCopy
		pIMecImportApplicativeOnResultCopy->Release();
		pIMecImportApplicativeOnResultCopy = NULL;
		
	} else
		return 1;
	
	// 11.6- Confirm Source Feature used for copying is same as the source feature retrieved from Copy Result
	if ( FALSE == spFeatureToCopy->IsEqual(spPointedElement2)) 
		return 1;
	cout << "Confirmed Source Feature used for copying is same as the source feature retrieved from Copy Result"<<endl;
	
	//==========================================================================================================================
	//12- Save the modified documents
	//==========================================================================================================================
	//12.1- Save the CAAMmrApplMecImport_RepFeatCopied
	CATDocument * pPartDocument = NULL ;
	
	CATIProduct_var  spRef = spComp4->GetReferenceProduct();
	
	if ( NULL_var != spRef )
	{
		CATILinkableObject * piLinkableObject = NULL;
		rc = spRef->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );                            
		
		if ( SUCCEEDED(rc) )
		{
			// Do not release this pointer       
			pPartDocument = piLinkableObject->GetDocument();
			
			piLinkableObject->Release();
			piLinkableObject = NULL ;
		}
	}
	
	if ( NULL == pPartDocument )
		return 1 ;
	
	CATUnicodeString DocumentSaveName = "CAAMmrApplMecImport_RepFeatCopied.CATPart";
	
	DocumentSaveName = InputData + Slash + DocumentSaveName ;
	rc = CATDocumentServices::SaveAs(*pPartDocument,DocumentSaveName.ConvertToChar());
	if (FAILED(rc)) 
		return 1;
	
	cout << "   The "<< DocumentSaveName.ConvertToChar() << " document is saved" << endl ;
	
	//12.2- Save the CAAMmrApplMecImport_Child2
	spRef = spComp2->GetReferenceProduct();
	
	if ( NULL_var != spRef )
	{
		CATILinkableObject * piLinkableObject = NULL;
		rc = spRef->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );                            
		
		if ( SUCCEEDED(rc) )
		{
			// Do not release this pointer       
			pPartDocument = piLinkableObject->GetDocument();
			
			piLinkableObject->Release();
			piLinkableObject = NULL ;
		}
	}
	
	if ( NULL == pPartDocument )
		return 1 ;
	
	DocumentSaveName = InputData + Slash + "CAAMmrApplMecImport_Child2.CATProduct";
	rc = CATDocumentServices::SaveAs (*pPartDocument,DocumentSaveName.ConvertToChar());
	if (FAILED(rc)) 
		return 1;

	cout << "   The "<< DocumentSaveName.ConvertToChar() << " document is saved" << endl ;
	
	//12.3- Save the CAAMmrApplMecImport_Root
	DocumentSaveName = "CAAMmrApplMecImport_Root.CATProduct" ;
	DocumentSaveName = InputData + Slash + DocumentSaveName ;
	
	//
	// Note: SaveAs() method does not save its includes part documents in batch mode.
	// that's why the modified part, document has been saved previoulsy 
	//
	rc = CATDocumentServices::SaveAs(*pProductDocument,DocumentSaveName.ConvertToChar());
	if (FAILED(rc)) 
		return 1;

	cout << "   The "<< DocumentSaveName.ConvertToChar() << " document is saved" << endl ;
	
	//==========================================================================================================================
    //13- Close document
	//==========================================================================================================================
	rc = CATDocumentServices::Remove (*pProductDocument);
	if (FAILED(rc)) 
		return 1;

	cout << "The "<< DocumentProductName.ConvertToChar() ;
	cout <<" document and its included files are closed" << endl ;
	
	pProductDocument = NULL ;
	
    //==========================================================================================================================
	//14- Close the PLM session
	//==========================================================================================================================
	rc = ::Delete_Session(pSessionName);
	if (FAILED(rc)) 
		return 1;

	cout << "Session has been closed" << endl;
	return 0;
	
}
