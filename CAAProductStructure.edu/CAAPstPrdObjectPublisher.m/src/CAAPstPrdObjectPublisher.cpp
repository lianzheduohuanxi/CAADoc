// COPYRIGHT Dassault Systemes 2003
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

/*******************************************************************
  Abstract :
  --------

  This Sample illustrates the way to 
  -----------------------------------
	- Create and valuate publications
	- Delete and unvaluate publications
	- Listing publications on an object
	- Checking if publications are directly on geometry or 
          point to a subpublication 
	- Listing direct publications and
          final publications which point to further publications


  Usage:
  ------
  To run this sample, you can use the command:
  mkrun -c "CAAPstPrdObjectPublisher <input> <pubName> <newPubName> <output>"
  
	where:

	* <input> is a path to an existing CATProduct document
	* <pubName> is an existing subpublication which will be deleted
	* <newPubName> is the name of a new publication which will be created 
                       at the product level
        * <output> is a path where the modified document will be saved

  Exit code:
        1 - Invalid number of arguments
        2 - Failed to open session
        3 - Failed to open input document
        4 - Failed to get document roots
        5 - Failed to get root product
        6 - Failed to query CATIProduct interface
        7 - Failed to save output document
        8 - Failed to remove document from session
        9 - Failed to delete session
       10 - Failed to get publication object
       11 - Failed to query CATIPrdObjectPublisher interface

*******************************************************************/

static int PrintPublications(CATIProduct *ipiProduct)
{
	int rc;
	CATIPrdObjectPublisher *piPublisher = NULL;

	if (NULL == ipiProduct) return 0;
	rc = ipiProduct->QueryInterface(IID_CATIPrdObjectPublisher,
					(void **) &piPublisher);
	if (FAILED(rc) || NULL == piPublisher) {
		cout << "Failed to query CATIPrdObjectPublisher interface"
		     << endl;
		return 11;
	}
	CATUnicodeString productName = ipiProduct->GetPartNumber();
	cout << endl << "Publications of "
	     << productName.ConvertToChar() << ":" << endl;

	//
	// Retrieve the list of the publications of the current product.
	//
	CATListValCATUnicodeString *pPubList = NULL;
	int pubCount = piPublisher->ListPublications(pPubList);
	if (0 == pubCount || NULL == pPubList) {
		pubCount = 0;
		cout << "  none" << endl;
	}
		
	for (int i = 1; i <= pubCount; i++) {
	
		//
		// Print the publication name
		//
		CATUnicodeString& pubName = (*pPubList)[i];
		cout << "  Publication " << i << ": "
		     << pubName.ConvertToChar() << endl;

		//
		// Retrieve the final publication object pointed to by
		// this publication name. 
		//
		CATBaseUnknown *pPubObject = 
			piPublisher->GetFinalObject(pubName);
		if (NULL == pPubObject) {
			cout << "Failed to get publication object of " 
			     << pubName.ConvertToChar() << endl;
			return 10;
		}

		//
		// List publications pointing to other sub publications
		//
		CATListValCATBaseUnknown_var *pSubPubrList = NULL;
		CATListValCATUnicodeString *pSubPubNameList = NULL;
		rc = piPublisher->IsFinallyPublished(pPubObject, pSubPubrList,
						     pSubPubNameList);
					
		if (rc && NULL != pSubPubrList && NULL != pSubPubNameList &&
		    pSubPubrList->Size() > 0 && pSubPubNameList->Size() > 0) {
			cout << "    is finally published as";
			for (int i = 1; i <= pSubPubNameList->Size(); i++)
				cout << " "
				     << (*pSubPubNameList)[i].ConvertToChar();
			cout << endl;
		}
		if (NULL != pSubPubrList) {
			delete pSubPubrList;
			pSubPubrList = NULL;
		}
		if (NULL != pSubPubNameList) {
			delete pSubPubNameList;
			pSubPubNameList = NULL;
		}
					
		//
		// List publications directly on the geometry
		//
		CATListValCATUnicodeString *pNameList = NULL;
		rc = piPublisher->IsPublished(pPubObject, pNameList);
		if (rc && NULL != pNameList && pNameList->Size() > 0) {
			cout << "    is published as";
			for (int i = 1; i <= pNameList->Size(); i++)
				cout << " " << (*pNameList)[i].ConvertToChar();
			cout << endl;
		}
		if (NULL != pNameList) {
			delete pNameList;
			pNameList = NULL;
		}

		//
		// Get the direct publication object
		//
		CATBaseUnknown *pSubPubr = NULL;
		CATUnicodeString subPubName;
		rc = piPublisher->GetDirectObject(pubName, pSubPubr, subPubName);
		if (2 == rc && NULL != pSubPubr) {
			cout << "    is a subpublication of "
			     << subPubName.ConvertToChar() << endl;
		}
		if (NULL != pSubPubr) {
			pSubPubr->Release();
			pSubPubr = NULL;
		}
		if (NULL != pPubObject) {
			pPubObject->Release();
			pPubObject = NULL;
		}
	}
	if (NULL != piPublisher) {
		piPublisher->Release();
		piPublisher = NULL;
	}
	if (NULL != pPubList) {
		delete pPubList;
		pPubList = NULL;
	}
	return 0;
}

static int ModifyPublications(CATIProduct *ipiProduct,
			      const char *ipubToDelete,
			      const char *isubPubToPublish)
{
	int rc;
	CATBaseUnknown *pSubPubr = NULL;
	CATUnicodeString subPubName;
	CATIPrdObjectPublisher *piPublisher = NULL;

	if (NULL == ipiProduct || NULL == ipubToDelete || 
	    NULL == isubPubToPublish)
		return 0;
	//
	// Get CATIPrdObjectPublisher on product and subpublisher
	//
	rc = ipiProduct->QueryInterface(IID_CATIPrdObjectPublisher,
					(void **) &piPublisher);
	if (FAILED(rc) || NULL == piPublisher) {
		cout << "Failed to query CATIPrdObjectPublisher interface"
		     << endl;
		return 11;
	}
	rc = piPublisher->GetDirectObject(ipubToDelete, pSubPubr, subPubName);
	if (2 != rc || NULL == pSubPubr) {
		cout << ipubToDelete << " is not a subpublication" << endl;
		return 0;
	}

	CATIPrdObjectPublisher *piSubPublisher = NULL;
	rc = pSubPubr->QueryInterface(IID_CATIPrdObjectPublisher,
				      (void **) &piSubPublisher);
	if (FAILED(rc) || NULL == piSubPublisher) {
		cout << "Failed to query CATIPrdObjectPublisher interface" 
		     << endl;
		return 11;
	}

	//
	// Unpublish product publicattion
	// also unvaluate and unpublish corresponding subpublication
	//
	cout << endl;
	rc = piPublisher->Unpublish(ipubToDelete);
	cout << (rc ? ">> unpublished" : ">> failed to unpublish")
	     << " publication "<< ipubToDelete << endl;

	//
	// Create a new publication at the root product level and valuate it
	//
	cout << endl;
	CATBaseUnknown *pPubObject = NULL;
	pPubObject = piSubPublisher->GetFinalObject(isubPubToPublish);
	if (NULL == pPubObject) {
		cout << "Failed to get publication object of " 
		     << isubPubToPublish << endl;
		return 10;
	}
	CATUnicodeString newPubName(isubPubToPublish);
	newPubName += "Prod";
	rc = piPublisher->Publish(newPubName);
	cout << (rc ? ">> created" : ">> failed to create")
	     << " new publication " << newPubName.ConvertToChar() << endl;

	rc = piPublisher->Valuate(newPubName, pPubObject);
	cout << (rc ? ">> valuated" : ">> failed to valuate") 
	     << " publication " << newPubName.ConvertToChar() << endl;

	if (NULL != pSubPubr) {
		pSubPubr->Release();
		pSubPubr = NULL;
	}
	if (NULL != piPublisher) {
		piPublisher->Release();
		piPublisher = NULL;
	}
	if (NULL != piSubPublisher) {
		piSubPublisher->Release();
		piSubPublisher = NULL;
	}
	if (NULL != pPubObject) {
		pPubObject->Release();
		pPubObject = NULL;
	}
	return 0;
}

int main(int argc, char **argv)
{
	HRESULT rc = 0;

	//----------------------------------------------------------------------
	// Control of arguments number        
	//----------------------------------------------------------------------

	if (5 != argc) {
		cout << "ERROR : bad number of arguments " << argc << endl;
		cout<< "Use the command " << endl << "mkrun -c CAAPstPrdObjectPublisher <input> <pubName> <newPubName> <output>"<<endl;
		return 1;  
	}

	const char *inputDoc = argv[1];
	const char *pubToDelete = argv[2];
	const char *pubToCreate = argv[3];
	const char *outputDir = argv[4];

	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA_PrdObjectPub_Session", pSession);
	if (FAILED(rc)) {
		cout << "Failed to create session" << endl;
		return 2;
	}

	//----------------------------------------------------------------------
	//  Opening an existing document with full path specified	
	//----------------------------------------------------------------------
	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::OpenDocument(inputDoc, pDoc);
	if (FAILED(rc) || NULL == pDoc) {
		cout << "Failed to open " << inputDoc << endl;
		return 3;
	}
	
	//----------------------------------------------------------------------
	// Search for the document's root product
	//----------------------------------------------------------------------
	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
				  (void**) &piDocRootsOnDoc);
	if (FAILED(rc) || NULL == piDocRootsOnDoc) {
		cout << "Failed to query CATIDocRoots interface" <<endl;
		return 4;
	}

	CATListValCATBaseUnknown_var* pRootProducts =
		piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	
	if (NULL != pRootProducts && pRootProducts->Size() > 0) {  
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	} else {
		cout << "Failed to get Root Product" << endl;
		return 5;
	}
	if (NULL != piDocRootsOnDoc) {
		piDocRootsOnDoc->Release();
		piDocRootsOnDoc=NULL;
	}
		
	//----------------------------------------------------------------------
	// Get CATIProduct handle on the root product.
	//----------------------------------------------------------------------
	CATIProduct *piProductOnRoot = NULL;
	if (NULL_var != spRootProduct)
		rc = spRootProduct->QueryInterface(IID_CATIProduct,
						   (void**) &piProductOnRoot);
	if (FAILED(rc) || NULL == piProductOnRoot) {
		cout << "Failed to query CATIProduct interface" << endl;
		return 6;
	}

	//----------------------------------------------------------------------
	// Get the root product's children
	//----------------------------------------------------------------------
	CATListValCATBaseUnknown_var *pChildren = NULL;
	pChildren = piProductOnRoot->GetAllChildren();
	int childCount = (pChildren == NULL ? 0 : pChildren->Size());

	//----------------------------------------------------------------------
	// Displaying the publications of the root product and its components
	//----------------------------------------------------------------------
	rc = PrintPublications(piProductOnRoot);
	if (0 != rc) return rc;
	int i = 1;
 for (; i <= childCount; i++) {
		rc = PrintPublications((CATIProduct_var) (*pChildren)[i]);
		if (0 != rc) return rc;
	}

	//----------------------------------------------------------------------
	// Delete and create publications
	//----------------------------------------------------------------------
	rc = ModifyPublications(spRootProduct, pubToDelete, pubToCreate);
	if (0 != rc) return rc;

	//----------------------------------------------------------------------
	// Displaying the publications of the root product and its components
	//----------------------------------------------------------------------
	rc = PrintPublications(piProductOnRoot);
	if (rc != 0) return rc;
	for (i = 1; i <= childCount; i++) {
		rc = PrintPublications((CATIProduct_var) (*pChildren)[i]);
		if (0 != rc) return rc;
	}
	if (NULL != pChildren) {
		delete pChildren;
		pChildren = NULL;
	}
	piProductOnRoot->Release();
	piProductOnRoot = NULL;

	//----------------------------------------------------------------------
	// Save modified document
	//----------------------------------------------------------------------
	char docDir[CATMaxPathSize];
	char docName[CATMaxPathSize];
	CATSplitPath(inputDoc, docDir, docName);
	CATUnicodeString newDoc = CATUnicodeString(outputDir) + "New" + docName;
	rc = CATDocumentServices::SaveAs(*pDoc, newDoc, "", FALSE);
	if (FAILED(rc)) {
		cout << "Failed to save " << newDoc.ConvertToChar() << endl;
		return 7;
	}

	//----------------------------------------------------------------------
	// Remove opened document from session
	//----------------------------------------------------------------------
	rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) {
		cout << "Failed to remove document from session" << endl;
		return 8;
	}

	//-----------------------------------------------------------------------
	// Delete the session 
	//-----------------------------------------------------------------------
	rc = ::Delete_Session("CAA_PrdObjectPub_Session");
	if (FAILED(rc)) {
		cout << "Failed to delete session" << endl;
		return 9;
	}
	return 0;
}

