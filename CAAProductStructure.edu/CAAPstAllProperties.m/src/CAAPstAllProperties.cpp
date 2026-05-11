//
// Copyright DASSAULT SYSTEMES 2004
//
#include <iostream.h>

// CATObjectModelerBase Framework
#include "CATSession.h"
#include "CATSessionServices.h"
#include "CATDocumentServices.h"
#include "CATIDocRoots.h"

// ProductStructure Framework
#include "CATIProduct.h"

// ProductStructureInterfaces Framework
#include "CatProductSource.h"

// KnowledgeInterfaces Framework
#include "CATIInstance.h"
#include "CATIAttributesDescription.h"
#include "CATIValue.h"

// System Framework
#include "CATUnicodeString.h"

/*******************************************************************************
  Abstract :
  --------

  This Sample illustrates the way to 
  -----------------------------------
	- Use the Get methods for the CATProduct and CATPart documents.
	- The methods further show all the properties of the Product reference
          and instance.


  Usage:
  ------
  To run this sample, you can use the command:
  mkrun -c "CAAPstAllProperties Input.CATProduct Property"
  
	where:

	* Input.CATPart is an existing CATProduct document
        * Property is a user defined property to be retrieved
  
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

void PrintAllProperties(CATIProduct *);

int main(int argc, char **argv)
{
	HRESULT rc = 0;

	//----------------------------------------------------------------------
	//  Control of arguments number        
	//----------------------------------------------------------------------

	if (2 != argc) {
		cout << "ERROR: bad number of arguments " << argc << endl;
		return 1;
	} 
	CATUnicodeString documentPath(argv[1]);

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
	rc = CATDocumentServices::OpenDocument(documentPath, pDoc);
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
	//Print all the properties of the root product
	//----------------------------------------------------------------------
	PrintAllProperties(piProductOnRoot);

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
		//Print all the properties of the child part
		//--------------------------------------------------------------
		PrintAllProperties(piChildProduct);
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
// Prints all the properties of a CATProduct reference and instance
//-----------------------------------------------------------------------
void PrintAllProperties(CATIProduct *iInstanceProd)
{
	HRESULT rc;

	if (iInstanceProd == NULL) {
		cout << "InstanceProd is NULL!!" << endl;
		return;
	}
	CATIAttributesDescription *piAttrDesc = NULL;
	rc = iInstanceProd->QueryInterface(IID_CATIAttributesDescription,
					   (void **) &piAttrDesc);
	if (FAILED(rc) || piAttrDesc == NULL) {
		cout << "Failed to query CATIAttributesDescription interface"
		     << endl;
		return;
	}
	CATIInstance *piInstance = NULL;
	rc = iInstanceProd->QueryInterface(IID_CATIInstance,
					   (void **) &piInstance);
	if (FAILED(rc) || piInstance == NULL) {
		cout << "Failed to query CATIInstance interface" << endl;
		piAttrDesc->Release();
		piAttrDesc = NULL;
		return;
	}

	// List all the properties and their types
	CATUnicodeString partNum = iInstanceProd->GetPartNumber();
	cout << endl << "Properties of " << partNum.ConvertToChar() << ":"
	     << endl;
	CATListValCATAttributeInfos attrInfoList;
	rc = piAttrDesc->List(&attrInfoList);
	if (FAILED(rc)) {
		cout << "Failed to List AttributesDescription" << endl;
	} else {
		int attrCount = attrInfoList.Size();
		for (int i = 1; i <= attrCount; i++) {
			CATAttributeInfos attrInfo = attrInfoList[i];
			const CATUnicodeString& propertyName = attrInfo.Name();
			const CATUnicodeString& valueType = attrInfo.Type()->Name();
			CATIValue *pValue = piInstance->GetValue(propertyName);
			CATUnicodeString valueString;
			if (pValue == NULL) {
				valueString = "** undefined **";
			} else {
				rc = pValue->AsString(valueString);
				if (FAILED(rc))
					valueString = "** failed to convert **";
				pValue->Release();
				pValue = NULL;
			}
			cout.width(20); cout.setf(ios::right);
			cout << propertyName.ConvertToChar();
			cout << " (";
			cout.width(7); cout.setf(ios::right);
			cout << valueType.ConvertToChar() << "): ";
			cout << valueString.ConvertToChar() << endl;
		}
	}
	piAttrDesc->Release();
	piAttrDesc = NULL;
	piInstance->Release();
	piInstance = NULL;
}
