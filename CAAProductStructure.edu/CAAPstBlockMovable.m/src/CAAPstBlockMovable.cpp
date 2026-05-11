//
// Copyright DASSAULT SYSTEMES 2003
//
// This sample purpose is to illustrate the CATIBlockMovable interface usage.
//
// - Load a CATProduct document
// - Find the specified part and its parent product
// - Make the parent product flexible
// - Move the specified part by adding <x,y,z>
// - Save the modified document
//

#include "CAAPstBlockMovable.h"
#include <iostream.h> 

// System Framework
#include "CATLib.h"

// ObjectModelerBase Framework
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "CATIDocRoots.h"
#include "CATDocument.h"

// ProductStructure Framework 
#include "CATIProduct.h"
#include "CATIMovable.h"
#include "CATIBlockMovable.h"

// Mathematics Framework
#include "CATMathTransformation.h"

#define ERROR_RETURN(code)	\
	{ cout << "Error: " << #code << "(" << code << ") at line " << __LINE__ << endl;\
          CleanUp();\
          return code;\
        }

const char *CAAPstBlockMovable::_sessionName = "CAA2_Sample_Session";

CAAPstBlockMovable::CAAPstBlockMovable()
{
	_pSession = NULL;
	_pDocument = NULL;
}

CAAPstBlockMovable::~CAAPstBlockMovable()
{
	CleanUp();
}

int CAAPstBlockMovable::Run (int argc, const char* argv[])
{
	HRESULT rc = 0;
	const char *inputFilename = NULL;
	const char *outputFilename = NULL;

	//
	// Check arguments
	//
	if (7 != argc) {
		cout << "Usage: " << argv[0] << " <input> <output> <part> <x> <y> <z>" << endl;
		ERROR_RETURN(S_Usage);
	} 
	// 
	// Decode options
	//
	argv++;
	inputFilename = *argv++;
	outputFilename = *argv++;
	CATUnicodeString partName(*argv++);
	int deltaX = strtol(*argv++, 0, NULL);
	int deltaY = strtol(*argv++, 0, NULL);
	int deltaZ = strtol(*argv++, 0, NULL);

	//
	// Start session and load CATProduct
	//
	rc = ::Create_Session((char *) _sessionName, _pSession);
	if (FAILED(rc) || NULL == _pSession) {
		ERROR_RETURN(S_Session);
		return S_Session;
	}
	
	rc = CATDocumentServices::OpenDocument(inputFilename, _pDocument);
	if (FAILED(rc) || NULL == _pDocument) {
		cout << "Can't open " << inputFilename << endl;
		ERROR_RETURN(S_OpenInput);
		return S_OpenInput;
	}
	cout << "Document " << inputFilename << " opened" << endl;
	
	//
	// Get Root Product
	//
	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = _pDocument->QueryInterface(IID_CATIDocRoots,
					(void**) &piDocRootsOnDoc);
	if (FAILED(rc) || NULL == piDocRootsOnDoc) {
		ERROR_RETURN(S_RootProduct);
		return S_RootProduct;
	}
	
	//
	// The root product is the first element of root elements
	//
	CATListValCATBaseUnknown_var* pRootProducts = 
		piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	
	if (pRootProducts && pRootProducts->Size()) {  
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	}
	piDocRootsOnDoc->Release();
	piDocRootsOnDoc = NULL;
	
	//
	// Get CATIProduct handle on the root product.
	//
	CATIProduct *piProductOnRoot = NULL;
	rc = spRootProduct->QueryInterface(IID_CATIProduct,
					   (void**) &piProductOnRoot);
	if (FAILED(rc) || NULL == piProductOnRoot) {
		ERROR_RETURN(S_RootCATIProduct);
		return S_RootCATIProduct;
	}

	//
	// Retrieve the part with specified name
	//
	CATIProduct_var spPart = FindPart(partName, piProductOnRoot);
	piProductOnRoot->Release();
	piProductOnRoot = NULL;
	if ( NULL_var == spPart) {
		cout << partName.ConvertToChar() << " not found" << endl;
		ERROR_RETURN(S_PartNotFound);
	}

	//
	// Retrieve the parent product of the part
	//
	CATIProduct_var spParentProduct = spPart->GetFatherProduct();
	if (NULL_var == spParentProduct) {
		cout << "Can't find parent product of " << partName.ConvertToChar() << endl;
		ERROR_RETURN(S_ParentNotFound);
	}
	
	//
	// Get the CATIBlockMovable interface on the parent product
	//
	CATIBlockMovable *piBlockMovable = NULL;
	rc = spParentProduct->QueryInterface(IID_CATIBlockMovable,
					     (void **) &piBlockMovable);
	if (FAILED(rc) || NULL == piBlockMovable) {
		ERROR_RETURN(S_ParentCATIBlockMovable);
		return S_ParentCATIBlockMovable;
	}

	//
	// Check whether the rigid/flexible modification needs to be applied to
	// the parent product
	//
	int isFlexibleFlag = piBlockMovable->IsSoft();
	CATUnicodeString parentName;
	spParentProduct->GetPrdInstanceName(parentName);
	cout << parentName.ConvertToChar();
	if (isFlexibleFlag)
		cout << " is already Flexible" << endl;
	else {
		cout << " is rigid, making it flexible" << endl;
		piBlockMovable->MakeSoftAssembly(); 
	}
	isFlexibleFlag = piBlockMovable->IsSoft();
	piBlockMovable->Release();
	piBlockMovable = NULL;

	//
	// If the parent product is flexible then move the part:
	// Get the CATIMovable Interface and move the part on the Y axis
	//
	if (isFlexibleFlag) {
		CATIMovable *piMovable = NULL;
		rc = spPart->QueryInterface(IID_CATIMovable, 
					    (void **) &piMovable);
		if (FAILED(rc) || NULL == piMovable) {
			ERROR_RETURN(S_PartCATIMovable);
			return S_PartCATIMovable;
		}
		CATMathTransformation position;
		rc = piMovable->GetAbsPosition(position);
		if (FAILED(rc))
			ERROR_RETURN(S_GetPosition);
		double array[12];
		position.GetCoef(array, sizeof(array)/sizeof(array[0]));
		//
		// move the part 20mm in the Y axis
		//
		array[9]  += double(deltaX);
		array[10] += double(deltaY);
		array[11] += double(deltaZ);
		position.SetCoef(array);
		rc = piMovable->SetAbsPosition(position);
		if (FAILED(rc)) 
			ERROR_RETURN(S_SetPosition);
		cout << "Part " << partName.ConvertToChar() << " moved" << endl;
		piMovable->Release();
		piMovable = NULL;
	} else {
		cout << parentName.ConvertToChar() << " is rigid. Can't move " << partName.ConvertToChar() << endl;
	}


	//
	// All done. save the modified document into the specified output file
	//
	rc = CATDocumentServices::SaveAs(*_pDocument, outputFilename);
	if (FAILED(rc)) {
		cout << "Can't save to " << outputFilename << endl;
		ERROR_RETURN(S_SaveOutput);
	}
	cout << "Document " << outputFilename << " saved" << endl;
	
	//
	// Remove the opened document and close the session
	//
	CleanUp();

	return S_Success;
}

//
// Retrieve the first part with given name
//
CATIProduct_var CAAPstBlockMovable::FindPart(CATUnicodeString& ipartName,
					     CATIProduct *ipiProductOnRoot)
{
	CATIProduct_var ospPart = NULL_var;

	if (NULL == ipiProductOnRoot)
		return ospPart;
	CATListValCATBaseUnknown_var* childrenList =
		ipiProductOnRoot->GetAllChildren();
	if (NULL == childrenList)
		return ospPart;
		
	int childrenCount = childrenList->Size();
	CATIProduct_var spChild = NULL_var;
	CATUnicodeString instanceName;
	for (int i=1; i <= childrenCount; i++) {
		spChild = (*childrenList)[i];
		if (NULL_var == spChild)
			break;
		HRESULT rc = spChild->GetPrdInstanceName(instanceName);
		if  (FAILED(rc))
			break;
		if (instanceName == ipartName) {
			ospPart = spChild;
			break;
		}
	}
	delete childrenList;
	childrenList = NULL;
	return ospPart;
}

//
// Clean up before exiting
//
void CAAPstBlockMovable::CleanUp()
{
	//
	// Remove the document
	//
	if (NULL != _pDocument) {
		CATDocumentServices::Remove (*_pDocument);
		_pDocument = NULL;
	}
	//
	// Delete the session
	//
	if (NULL != _pSession) {
		::Delete_Session((char *) _sessionName); 
		_pSession = NULL;
	}
}
