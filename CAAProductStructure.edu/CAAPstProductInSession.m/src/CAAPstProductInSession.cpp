// --------------------------------------------------------
#include "iostream.h"


// ObjectModelerBase Framework
#include "CATDocument.h" 
#include "CATSessionServices.h" 
#include "CATIDocRoots.h"  
#include "CATDocumentServices.h" 
#include "CATInit.h"
#include "CATILinkableObject.h"


//CATProductStructure1 Framework
#include "CATIProduct.h"
#include "CATIProductInSession.h"

// System Framework
#include "CATBaseUnknown.h"


/*******************************************************************
	Abstract :
	--------

  This Sample illustrates the way to 
  -----------------------------------
	- Use the Get/Set methods for the active shape associated with a CATproduct.
	- Get the active shape name associated with a CATProduct.


  Usage:
  ------
  To run this sample, you can use the command:
  mkrun -c "CAAPstProductInSession Input.CATProduct ShapeName"
  
	where,
	* Input.CATPart is an existing CATProduct document
	* ShapeName is one of the shapes names associated with Input.CATProduct

 
 Return Errors:
 -------------
  1 - ERROR bad argument number
  2 - ERROR in Opening of Session
  3 - ERROR in Opening of document
  4 - ERROR in Querying the CATIDocRoots interface to the Document
  5 - ERROR in Obtaining the product roots
  6 - ERROR in Querying the CATIProduct interface to the root product
  7 - ERROR in Querying the CATIProductInSession interface to the root product
  8 - ERROR in Retrieving the active shape representation
  9 - ERROR in Retrieving the active shape name
  10- ERROR in Activating a shape representation
  11- The newly active shape representation is not the one expected
  
******************************************************************/

int main (int argc, char** argv)
{
	
	HRESULT rc = 0;

	/* ---------------------------------------*/
	/*  0. control of arguments number        */
	/* ---------------------------------------*/

	if ( 3 != argc ) {
		cout << "ERROR : bad number of arguments " << argc << endl;
		return 1;  
	} 

	const CATUnicodeString inputFilename(argv[1]);
	const CATUnicodeString shapeName(argv[2]);
	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session",pSession );
	
	if (FAILED(rc)) {
		cout << " Failed to open session" << endl;
		return 2;
	}
	cout << "Session opened" << endl;

	/* ---------------------------------------*/
	/*  1. Opening the Document               */
	/* ---------------------------------------*/
	
	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::OpenDocument(inputFilename, pDoc);
	if (FAILED(rc) || NULL == pDoc) {
		cout << "Failed to open" 
		     << inputFilename.ConvertToChar() << endl;
		return 3;
	}
	cout << "Document opened" << endl;

	/* --------------------------------------------------------- */
	/*  2. Search for the document's root product (RootProduct)  */
	/* --------------------------------------------------------- */

	CATIDocRoots *piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &piDocRootsOnDoc);
	if (FAILED(rc) || NULL == piDocRootsOnDoc) {
		cout << "Failed to query CATIDocRoots" << endl;
		return 4;
	}
    
	CATListValCATBaseUnknown_var *pRootProducts =
		piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct;
	if (NULL != pRootProducts && pRootProducts->Size() > 0) {
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	} else {
		cout << "Failed to find root products"<< endl;
		return 5;
	}
	if (NULL != piDocRootsOnDoc) {
		piDocRootsOnDoc->Release();
		piDocRootsOnDoc=NULL;
	}
	
	// Get CATIProduct prointer of the root product.
	CATIProduct *piProductOnRoot = NULL;
	rc = spRootProduct->QueryInterface(IID_CATIProduct,
					   (void**) &piProductOnRoot);
	if (FAILED(rc)) {
		cout << "Failed to query CATIProduct" << endl;
		return 6;
	}
	CATUnicodeString partNumber = piProductOnRoot->GetPartNumber();
	cout << "Working with '" << partNumber.ConvertToChar() << "'" << endl;
	
	//Get the ProductInSession Interface pointer

	CATIProductInSession * piProdInSession = NULL;
	rc = piProductOnRoot->QueryInterface(IID_CATIProductInSession,
					     (void **) &piProdInSession);
	if (FAILED(rc) || NULL == piProdInSession) {
		cout << "Failed to query CATIProductInSession" << endl;
		return 7;
	}
	if (NULL != piProductOnRoot) {
		piProductOnRoot->Release();
		piProductOnRoot=NULL;
	}
	
	/* --------------------------------------------------------- */
	/*  3. Changing the active shape representation.             */
	/*                                                           */
	/*  Note: Since this code a non-interactive,                 */
	/*        SetActiveShapeRep must be called first for the     */
	/*        subsequent GetActiveShapeRep to work               */
	/* --------------------------------------------------------- */

	rc = piProdInSession->SetActiveShapeRep(shapeName, TRUE, FALSE,
						CATPrd3D, TRUE, FALSE);
	if (FAILED(rc)) {
		cout << "Failed to activate " << shapeName.ConvertToChar()
		     << " representation" << endl;
		return 10;
	}
	cout << "Activated '" << shapeName.ConvertToChar() 
	     << "' representation" << endl;
	

	/* --------------------------------------------------------- */
	/*  4. Verifying the active shape representation name.       */
	/* --------------------------------------------------------- */

	CATUnicodeString activeShapeName;
	rc = piProdInSession->GetActiveShapeName(activeShapeName);
	if (FAILED(rc)) {
		cout << "Failed to retrieve the active shape name" << endl;
		return 9;
	}
	if (activeShapeName != shapeName) {
		cout << "ERROR: the active representation is "
		     << activeShapeName.ConvertToChar() << " instead of "
		     << shapeName.ConvertToChar() << endl;
		return 11;
	}
	cout << "Current active representation: '"
	     << activeShapeName.ConvertToChar() << "'" << endl;

	/* --------------------------------------------------------- */
	/*  5. Retrieving the active shape representation.           */
	/* --------------------------------------------------------- */
	
	CATILinkableObject_var spLinkedObject;
	rc = piProdInSession->GetActiveShapeRep(spLinkedObject);
	if (FAILED(rc))	{
		cout << "Failed to retrieve the active shape representation"
		     << endl;
		return 8;
	}
	cout << "Active shape representation retrieved" << endl;

	if(piProdInSession) {
		piProdInSession->Release();
		piProdInSession = NULL;
	}
	
	rc = CATDocumentServices::Remove (*pDoc);
	if (!SUCCEEDED(rc)) return 11;	
	
	rc = ::Delete_Session("CAA2_Sample_Session");
	cout << "Session deleted" << endl;
	
	return rc;
}
