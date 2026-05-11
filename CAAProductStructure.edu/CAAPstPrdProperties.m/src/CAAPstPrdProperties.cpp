//
// Copyright DASSAULT SYSTEMES 2003
//
#include <iostream.h>

// CATObjectModelerBase Framework
#include "CATSession.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"

// ProductStructure Framework
#include "CATIProduct.h"
#include "CATIPrdProperties.h"

// ProductStructureInterfaces Framework
#include "CatProductSource.h"

// System Framework
#include "CATUnicodeString.h"

/*******************************************************************************
  Abstract :
  --------

  This Sample illustrates the way to 
  -----------------------------------
	- Use the Get methods for the CATProduct and CATPart documents.
	- The methods further show the properties of the Product reference and instance.


  Usage:
  ------
  To run this sample, you can use the command:
  mkrun -c "CAAPstPrdProperties Input.CATProduct"
  
	where:

	* Input.CATPart is an existing CATProduct document
  
 Return Errors:
 -------------
  1 - ERROR bad argument number
  2 - ERROR in Opening of Session
  3 - ERROR in Opening of document
  4 - ERROR in Query Interface to the Root Document
  5 - ERROR in Obtaining the product roots
  6 - ERROR in Query Interface to the CATProduct 
  7 - ERROR in Query Interface to the child Part
  8 - ERROR in Removing document from session
  10- ERROR in Deletion of session.
  
*******************************************************************************/

void PrintPrdProperties(CATIProduct *);

int main(int argc, char **argv)
{
	HRESULT rc = 0;

	//----------------------------------------------------------------------
	//  Control of arguments number        
	//----------------------------------------------------------------------

	if ( 2 != argc ) {
		cout << "ERROR: bad number of arguments " << argc << endl;
		return 1;
	} 

	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA_PrdProp_Session", pSession);
	if (FAILED(rc)) {
		cout << "Opening of Session failed." << endl;
		return 2;
	}
	
	//----------------------------------------------------------------------
	//  Opening an existing document with full path specified	
	//----------------------------------------------------------------------
	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[1], pDoc);
	if (FAILED(rc) || NULL == pDoc) {
		cout << "Opening of document failed." << endl;
		return 3;
	}
	
	//----------------------------------------------------------------------
	// Search for the document's root product
	//----------------------------------------------------------------------
	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
				  (void**) &piDocRootsOnDoc);
	if (FAILED(rc) || NULL == piDocRootsOnDoc) {
		cout << "Query Interface to the Root Document failed." <<endl;
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
		cout << "Root product could not be obtained." << endl;
		return 5;
	}
	if(piDocRootsOnDoc) {
		piDocRootsOnDoc->Release();
		piDocRootsOnDoc=NULL;
	}
		
	//----------------------------------------------------------------------
	// Get CATIProduct handle on the root product.
	//----------------------------------------------------------------------
	CATIProduct *piProductOnRoot = NULL;
	if (spRootProduct != NULL_var)
		rc = spRootProduct->QueryInterface(IID_CATIProduct,
						   (void**) &piProductOnRoot);
	if (FAILED(rc)) {
		cout << "Query Interface to the CATProduct failed." << endl;
		return 6;
	}

	//----------------------------------------------------------------------
	//Print the properties of the root product
	//----------------------------------------------------------------------
	PrintPrdProperties(piProductOnRoot);

	//----------------------------------------------------------------------
	//Get the root product's children
	//----------------------------------------------------------------------
	CATListValCATBaseUnknown_var* childrenList = 
		piProductOnRoot->GetAllChildren();
	if (NULL == childrenList || childrenList->Size() <= 0) {
		cout << "Could not retrieve Root product's children." << endl;
		return 8;
	}
	if (NULL != piProductOnRoot) {	
		piProductOnRoot->Release();
		piProductOnRoot = NULL;
	}
	CATIProduct_var spChild = NULL_var;
	int childrenCount = childrenList->Size();
	for (int i = 1; i <= childrenCount; i++) {
		spChild = (*childrenList)[i];

		//--------------------------------------------------------------
		// Get CATIProduct handle on the child product
		//--------------------------------------------------------------
		CATIProduct *piChildProduct = NULL;
		if (NULL_var != spChild) {
			rc = spChild->QueryInterface(IID_CATIProduct,
						     (void**) &piChildProduct);
			if (FAILED(rc) || NULL == piChildProduct) {
				cout << "Query Interface to the child CATProduct failed." << endl;
				return 7;
			}
		}

		//--------------------------------------------------------------
		//Print the properties of the child part
		//--------------------------------------------------------------
		PrintPrdProperties(piChildProduct);
		if (NULL != piChildProduct) {
			piChildProduct->Release();
			piChildProduct = NULL;
		}		
	}
	delete childrenList;
	childrenList = NULL;

	//----------------------------------------------------------------------
	// Remove opened document from session
	//----------------------------------------------------------------------
	rc = CATDocumentServices::Remove (*pDoc);
	if (FAILED(rc)) {
		cout << "Error in removing document from session." << endl;
		return 9;
	}
 
	//----------------------------------------------------------------------
	//Delete the session 
	//----------------------------------------------------------------------
	rc = ::Delete_Session("CAA_PrdProp_Session");
	if (FAILED(rc)) {
		cout << "Failed to delete session." << endl;
		return 11;
	}
	return 0;
}

//-----------------------------------------------------------------------
// Prints the properties of a CATProduct reference and instance
//-----------------------------------------------------------------------
void PrintPrdProperties(CATIProduct *iInstanceProd)
{
	HRESULT rc;
	CATUnicodeString oValue;

	if (NULL == iInstanceProd) return;

	oValue = iInstanceProd->GetPartNumber();
	cout << endl
	     << "Properties of " << oValue.ConvertToChar();
	rc = iInstanceProd->IsReference();
	if (FAILED(rc)) {
		rc = iInstanceProd->GetPrdInstanceName(oValue);
		if (SUCCEEDED(rc))
			cout << " (" << oValue.ConvertToChar() << ")";
	}
	cout << ":" << endl;

	CATIPrdProperties_var spPrdProps(iInstanceProd);
	if (NULL_var != spPrdProps) {
		spPrdProps->GetNomenclature(oValue);
		cout << "     Nomenclature: " << oValue.ConvertToChar() << endl;

		spPrdProps->GetRevision(oValue);
		cout << "         Revision: " << oValue.ConvertToChar() << endl;

		CatProductSource oSource;
		spPrdProps->GetSource(oSource);
		switch (oSource) {
		case catProductSourceUnknown:
			oValue = "Unknown";
			break;
		case catProductMade:
			oValue = "Made";
			break;
		case catProductBought:
			oValue = "Bought";
			break;
		default:
			oValue = "Undefined";
		}
		cout << "           Source: " << oValue.ConvertToChar() << endl;

		spPrdProps->GetDefinition(oValue);
		cout << "       Definition: " << oValue.ConvertToChar() << endl;

		spPrdProps->GetDescriptionRef(oValue);
		cout << "   Reference Desc: " << oValue.ConvertToChar() << endl;

		spPrdProps->GetDescriptionInst(oValue);
		cout << "   Instance Desc.: " << oValue.ConvertToChar() << endl;
	} else {
		cout << "None" << endl;
	}
}
