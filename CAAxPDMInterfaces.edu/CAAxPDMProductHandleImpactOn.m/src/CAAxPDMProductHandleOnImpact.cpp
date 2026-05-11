// COPYRIGHT DASSAULT SYSTEMES 2008
//==============================================================================================================
// Mission         : Renaming an Instance and Publication
//
//					 This Use Case illustrates the CATIPrdHandleImpactsOnInstance and 
//					 CATIPrdHandleImpactsOnReference APIs  (ProductStructureInterfaces fw)
//
//					 On renaming a Product Instance, the CATIPrdHandleImpactsOnInstance APIs manage the impacts.
//					 The impacted elements are those which point to this instance are reconnected
//					 On renaming a Publication, the CATIPrdHandleImpactsOnReference APIs manage the impacts.
//				     The impacted elements are those which point to this publication are reconnected
//                   
//                   This use case requires PX1 ( for PS and CATxPDMInterfaces API ) licence
//
//============================================================================================
// Run command     : 
//          mkrun -c "CAAxPDMProductHandleImpactOn InputProductPath OutputFilePath " 
//
//					where InputProductPath is the path where the File for processing is found
//						  Typically found in the CAAxPDMInterfaces.edu/InputData
//						     CAAxPDMProductHandleImpactOn_Root.CATProduct, 
//                           CAAxPDMProductHandleImpactOn_Part1.CATPart,
//                           CAAxPDMProductHandleImpactOn_Part2.CATPart 
//						  are the input documents
//						  OutputFilePath   is the location where the Files will be saved
//						  The files saved are : CAAxPDMPart1HandleOnImpactNew.CATPart,
//												CAAxPDMPart2HandleOnImpactNew.CATPart,
//												CAAxPDMProductHandleOnImpactNew.CATProduct
//
//============================================================================================         
// Steps           
//					1- Control of arguments number        
//					2- Create Session
//					3- Opening an existing document 
//					4- Search for the document's root product
//					5- Retrieve the root product's children
//					6- Rename a Publication which occurs under a Child Reference
//					7- Rename a Child Instance
//					8- Check Publication name is indeed renamed
//					9- Check child Instance is indeed renamed
//				   10- Save Session and Rename Input V5 Documents
//				   11- Remove opened document from session
//                 12- Delete the session 

//============================================================================================
//Return code      :
//				     0 successful execution
//				     1 execution failed
//============================================================================================

#include <iostream.h>

// CATObjectModelerBase Framework
#include "CATSession.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"

// ProductStructure Framework
#include "CATIProduct.h"
#include "CATIPrdObjectPublisher.h"

// System Framework
#include "CATLib.h"
#include "CATIAlias.h"
#include "CATIDescendants.h"
#include "CATIPrdHandleImpactsOnInstance.h"
#include "CATIPrdHandleImpactsOnReference.h"
#include "CATDocument.h"

#include "CATILinkableObject.h"
#include "CATUnicodeString.h"

// CATxPDMInterfaces Framework
#include "CATxPDMSessionServices.h"

#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

int main(int argc, char **iArgv)
{
	HRESULT rc = 0;

	//----------------------------------------------------------------------
	// 1- Control of arguments number        
	//----------------------------------------------------------------------
	if (3 != argc) {
		cout << "ERROR : bad number of arguments " << argc << endl;
		return 1;  
	}

	//----------------------------------------------------------------------
	// 2-  Create Session
	//----------------------------------------------------------------------
	CATSession *pSession = NULL;
	rc = ::Create_Session("CAAxPDMProductHandleImpactOn_Session", pSession);
	if (FAILED(rc)) 
		return 2;

	cout << "Success in creating session" << endl;

	//----------------------------------------------------------------------
	// 3-  Opening an existing document 
	//----------------------------------------------------------------------
	CATDocument *pDoc = NULL;
	CATUnicodeString InputPath(iArgv[1]);
	InputPath += Slash;
	InputPath += CATUnicodeString("CAAxPDMProductHandleImpactOn_Root.CATProduct");

	rc = CATDocumentServices::OpenDocument(InputPath, pDoc);
	if (FAILED(rc) || NULL == pDoc)
		return 3;
	
	cout << "Success in opening an input document" << endl;

	//----------------------------------------------------------------------
	// 4- Search for the document's root product
	//----------------------------------------------------------------------
	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
		(void**) &piDocRootsOnDoc);
	if (FAILED(rc) || NULL == piDocRootsOnDoc)
		return 4;

	cout << "Success in query of CATIDocRoots from Document opened" <<endl;

	CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;

	if (NULL != pRootProducts && pRootProducts->Size() > 0) {  
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	} else 
		return 5;

	cout << "Success in retrieving the Root Product" << endl;

	if (NULL != piDocRootsOnDoc) {
		piDocRootsOnDoc->Release();
		piDocRootsOnDoc=NULL;
	}

	//----------------------------------------------------------------------
	// Get CATIProduct handle on the root product.
	//----------------------------------------------------------------------
	CATIProduct *piProductOnRoot = NULL;
	if (NULL_var != spRootProduct)
		rc = spRootProduct->QueryInterface(IID_CATIProduct,(void**) &piProductOnRoot);

	if (FAILED(rc) || NULL == piProductOnRoot)
		return 6;

	cout << "Success in Querying CATIProduct from the Root Product" << endl;

	//----------------------------------------------------------------------
	// 5- Retrieve the root product's children
	//----------------------------------------------------------------------
	CATListValCATBaseUnknown_var *pChildren = NULL;
	pChildren = piProductOnRoot->GetChildren();
	int childCount = 0 ;
	if (( NULL == pChildren) || ( 2 != pChildren->Size()))
		return 1;

	CATIProduct_var spChild1 = (CATIProduct_var) (*pChildren)[1];
	CATIProduct_var spChild2 = (CATIProduct_var) (*pChildren)[2];

	if ((NULL_var == spChild1 ) || ( NULL_var==spChild2 ))
		return 1 ;

	cout << "Success in retrieving the 2 Children under Root" << endl;

	//----------------------------------------------------------------------
	// 6- Rename a Publication which occurs under a Child Reference
	//----------------------------------------------------------------------
	CATIProduct_var  spRefOnChild1 = spChild1->GetReferenceProduct();
	CATIPrdHandleImpactsOnReference * pIPrdHandleImpactsOnReferenceOnFirstRef = NULL;
	rc = spRefOnChild1->QueryInterface(IID_CATIPrdHandleImpactsOnReference,
									  (void **) &pIPrdHandleImpactsOnReferenceOnFirstRef);
	if (SUCCEEDED(rc))
	{
		cout << "Success in retrieving the CATIPrdHandleImpactsOnReference on the Child Product Reference" << endl;
		// rename the publication
		rc = pIPrdHandleImpactsOnReferenceOnFirstRef->RenamePublication(CATUnicodeString("Face"),
																		CATUnicodeString("NewFace"));
		if (FAILED(rc))
			return 1;

	} else
		return 1;

	cout << "Success in renaming the Publication" << endl;

	//----------------------------------------------------------------------
	// 7- Rename a Child Instance
	//----------------------------------------------------------------------
	CATIPrdHandleImpactsOnInstance* pIPrdHandleImpactsOnInstanceOnFirstRef = NULL;
	rc = spChild1->QueryInterface(IID_CATIPrdHandleImpactsOnInstance,
								 (void **) &pIPrdHandleImpactsOnInstanceOnFirstRef);
	
	if (SUCCEEDED(rc))
	{
		cout << "Success in QI for CATIPrdHandleImpactsOnInstance on Child Product Ref" << endl;
		rc = pIPrdHandleImpactsOnInstanceOnFirstRef->RenameInstance(CATUnicodeString("NewInstance"));
		if (FAILED(rc))
			return 1;

	} else
		return 1;

	cout << "Success in renaming the First Instance" << endl;
	
	//----------------------------------------------------------------------
	// 8- check Publication Name is indeed renamed
    //----------------------------------------------------------------------
	CATIPrdObjectPublisher_var spPublisher = spRefOnChild1 ;
    CATListValCATUnicodeString*  opListOfPublicationNames = new CATListValCATUnicodeString;
    int NbrOfPublications = spPublisher->ListPublications(opListOfPublicationNames);
	cout << "the count is " << NbrOfPublications << endl;
 
	for (int i=1; i<=NbrOfPublications; i++)
	{
		CATUnicodeString strPublicationName = (*opListOfPublicationNames)[i];
		if (CATUnicodeString("NewFace")==strPublicationName)
		{
			cout << "The name of the Publication after rename is " << strPublicationName.ConvertToChar() << endl;
			cout << "The name is the same as set by the RenamePublication API" << endl;
		}
	}

	//----------------------------------------------------------------------
	// 9- check Child Instance is indeed renamed
    //----------------------------------------------------------------------
	CATUnicodeString NewInstName;
	rc = spChild1->GetPrdInstanceName(NewInstName);
	if (FAILED(rc))
		return 1;

	cout << "The Instance name after renaming is " << NewInstName.ConvertToChar() << endl;

	if (CATUnicodeString("NewInstance")==NewInstName)
		cout << "The name is the same as set by the RenameInstance API" << endl;

	//----------------------------------------------------------------------
	// 10- Save session and Rename Input V5 Documents
	//----------------------------------------------------------------------
	CATDocument * pPartDocument1 = NULL ;
	CATIProduct_var  spRef = spChild1->GetReferenceProduct();
	if ( NULL_var != spRef )
	{
		CATILinkableObject * piLinkableObject = NULL;
		rc = spRef->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject );                            

		if ( SUCCEEDED(rc) )
		{
			cout << "Success in QI for CATILinkableObject from Child Reference 1" << endl;
			// Do not release this pointer       
			pPartDocument1 = piLinkableObject->GetDocument();

			piLinkableObject->Release();
			piLinkableObject = NULL ;
		} else
			return 1;
	}

	CATDocument * pPartDocument2 = NULL ;
	CATIProduct_var  spRef2 = spChild2->GetReferenceProduct();
	if ( NULL_var != spRef2 )
	{
		CATILinkableObject * piLinkableObject2 = NULL;
		rc = spRef2->QueryInterface( IID_CATILinkableObject, (void**)& piLinkableObject2 );                            

		if ( SUCCEEDED(rc) )
		{
			cout << "Success in QI for CATILinkableObject from Child Reference 2" << endl;
			// Do not release this pointer       
			pPartDocument2 = piLinkableObject2->GetDocument();

			piLinkableObject2->Release();
			piLinkableObject2 = NULL ;
		}
	}

	CATUnicodeString OutputPath1(iArgv[2]);
	cout <<"Output directory=" << OutputPath1.ConvertToChar() << endl;

	CATUnicodeString OutputPath11 = OutputPath1 + Slash;

	CATListOfCATUnicodeString iListOfNewNames;
	iListOfNewNames.Append("CAAxPDMPart1HandleOnImpactNew.CATPart");
	iListOfNewNames.Append("CAAxPDMPart2HandleOnImpactNew.CATPart");
	iListOfNewNames.Append("CAAxPDMProductHandleOnImpactNew.CATProduct");

	CATIxPDMItem_var spItemPart1;
	rc = CATxPDMSessionServices::GetItemFromDocument(pPartDocument1,spItemPart1);
	if (FAILED(rc))
		return rc;

	if (NULL != pPartDocument1)
	{
		CATUnicodeString pathdoc1 = pPartDocument1->StorageName() ; 
		cout << "Success in retrieving the item from " << pathdoc1.ConvertToChar() << endl;
	}

	CATIxPDMItem_var spItemPart2;
	rc = CATxPDMSessionServices::GetItemFromDocument(pPartDocument2,spItemPart2);
	if (FAILED(rc))
		return rc;

	if (NULL != pPartDocument2)
	{
		CATUnicodeString pathdoc2 = pPartDocument2->StorageName() ; 
		cout << "Success in retrieving the item from " << pathdoc2.ConvertToChar() << endl;
	}

	CATIxPDMItem_var spItemProduct;
	rc = CATxPDMSessionServices::GetItemFromDocument(pDoc,spItemProduct);
	if (FAILED(rc))
		return rc;

	if (NULL != pDoc)
	{
		CATUnicodeString pathdoc = pDoc->StorageName(); 
		cout << "Success in retrieving the item from " << pathdoc.ConvertToChar() << endl;
	}

	CATListValCATIxPDMItem_var iListItemToRename;
	iListItemToRename.Append(spItemPart1);
	iListItemToRename.Append(spItemPart2);
	iListItemToRename.Append(spItemProduct);

	CATUnicodeString oErrorMessage;
	rc = CATxPDMSessionServices::SaveSessionToDirectory(OutputPath11, oErrorMessage,
													    &iListItemToRename,&iListOfNewNames);
	if ( FAILED(rc) )
	{
		return rc;
	}
	cout << "Success in Save" << endl;

	//----------------------------------------------------------------------
	// 11- Remove opened document from session
	//----------------------------------------------------------------------
	rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc))
		return 9;

	cout << "Success in removing document from session" << endl;

	//-----------------------------------------------------------------------
	// 12- Delete the session 
	//-----------------------------------------------------------------------
	rc = ::Delete_Session("CAAxPDMProductHandleImpactOn_Session");
	if (FAILED(rc)) 
		return 10;

	cout << "Success in delete Session" << endl;

	//----------------------------------------------------------------------
	// cleanup pointers 
	//----------------------------------------------------------------------
	if (NULL != pIPrdHandleImpactsOnReferenceOnFirstRef)
	{
		pIPrdHandleImpactsOnReferenceOnFirstRef->Release();
		pIPrdHandleImpactsOnReferenceOnFirstRef = NULL;
	}

	if (NULL != pIPrdHandleImpactsOnInstanceOnFirstRef)
	{
		pIPrdHandleImpactsOnInstanceOnFirstRef->Release();
		pIPrdHandleImpactsOnInstanceOnFirstRef = NULL;
	}

	if (NULL != piProductOnRoot)
	{
		piProductOnRoot->Release();
		piProductOnRoot = NULL;
	}

	cout << "Success in executing UC" << endl;

	return 0;
}

