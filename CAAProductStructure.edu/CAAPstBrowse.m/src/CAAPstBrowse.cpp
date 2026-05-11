/**
 * @fullreview RCI RCI 01:08:24
 * @error UDOO Y err_1 piDocRootsOnDoc not set to NULL after release
 * @error UDOO Y err_2 piProductOnRoot not set to NULL after release
 * @error UNH Y err_3 spChild not tested before use ( if !! )
 */
// --------------------------------------------------------
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

/**************************************************************/
/*               CAAPstBrowse                                 */
/**************************************************************/

/* 
* This sample illustrates navigation in an existing product structure.
*     
*	  - 1. Opens an existing product
*     - 2. Retrieves Root Product
*     - 3. Retrieves all chidren under the root
*     - 4. Get their name
*     
* To run this sample, you can use the command:
*    mkrun -c "CAAPstBrowse input.CATProduct "
* where input.CATProduct is an existing document to browse.
* Return Errors:
* -------------
*  1 - ERROR bad argument number
*  2 - ERROR in opening CATProduct
*  3 - ERROR in Query Interface
*  4 - ERROR in Getting Instance Name
*  5 - ERROR in removing document
*/
/***********************************************************************************/

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

// ------------------------------------------------------------------------------------------
int main (int argc, char** argv)
{
	HRESULT rc = 0;

	/* ---------------------------------------*/
	/*  0. Control of arguments number        */
	/* ---------------------------------------*/
	 if ( 2 != argc )
	 {
		 cout << "ERROR : bad number of arguments " << argc << endl << flush;
		 return 1;  
	 } 
	/* ----------------------------------------*/
	/* 1. Load an existing CATProduct document */
	/* ----------------------------------------*/
	CATSession* pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session",
		                  pSession);
	
	CATDocument* pDoc = NULL;
	rc = CATDocumentServices::OpenDocument(argv[1],
		                           pDoc);
	if ( FAILED(rc) || (NULL==pDoc)) return 2;
	cout << endl << "CAAPstBrowse.m:	product document opened : " << argv[1] << endl << flush;
	
	/* ----------------------------*/
	/* 2. Retrieves Root Product   */
	/* ----------------------------*/
	
	// Begin navigation through the document => start with the RootProduct.
	CATIDocRoots* piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
		                      (void**) &piDocRootsOnDoc);
	if ( FAILED(rc) ) return 3;
	
	// get the root product which is the first element of root elements
	CATListValCATBaseUnknown_var* pRootProducts = 
		piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	
	if (pRootProducts && pRootProducts->Size())
	{  
		spRootProduct = (*pRootProducts)[1];
		delete pRootProducts;
		pRootProducts = NULL;
	}
/** @anchor err_1 piDocRootsOnDoc not set to NULL after release */ 
	piDocRootsOnDoc->Release();
	piDocRootsOnDoc = NULL;
	
	// Get CATIProduct handle on the root product.
	CATIProduct *piProductOnRoot = NULL;
	rc = spRootProduct->QueryInterface(IID_CATIProduct,
		                               (void**) &piProductOnRoot);
	if ( FAILED(rc) ) return 3;

	/* ---------------------------------------*/
	/* 3. Retrieves children under the root   */
	/* ---------------------------------------*/
	
	int nbOfDirectChidren = piProductOnRoot -> GetChildrenCount() ;
	cout << " Number of direct children under the root = " << nbOfDirectChidren << endl << flush;
	
	// then on a root product, get all the children agregated to it.
	CATListValCATBaseUnknown_var*   ListChildren =
		piProductOnRoot->GetAllChildren();
/** @anchor err_2 piProductOnRoot not set to NULL after release */ 
	piProductOnRoot -> Release();
	piProductOnRoot = NULL;
	if(NULL != ListChildren)
	{
		
		int numberOfChildren = ListChildren->Size();
		cout << " Number of all children under the root = " << numberOfChildren << endl << flush;

		/* -----------------------------------------------------------*/
		/*  4. For each child, get its partNumber, and InstanceName   */
		/* -----------------------------------------------------------*/
		CATIProduct_var spChild = NULL_var;
		for (int i=1;i<=numberOfChildren;i++)
		{
			spChild = (*ListChildren)[i];
/** @anchor err_3 spChild not tested before use ( if !! ) */ 
			if ( NULL_var == spChild ) return 4;
			CATUnicodeString partNumber = spChild -> GetPartNumber();
			CATUnicodeString instanceName (" ");
			rc = spChild -> GetPrdInstanceName ( instanceName ) ;
			if  ( FAILED(rc) ) return 4;
			
			cout << " child number : " << i << endl << flush;
			cout << " has as part number : " << partNumber.CastToCharPtr()  << endl << flush;
			cout << " and as instanceName : " << instanceName.CastToCharPtr() << endl << endl << flush;
		}
		delete ListChildren;
		ListChildren=NULL;
	}	
	/* -------------------------------------------- */
	/*   Ends the session                        */
	/* -------------------------------------------- */
	
	// remove opened document
	rc = CATDocumentServices::Remove (*pDoc);
	if (!SUCCEEDED(rc)) return 5;
	
	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	
	rc = ::Delete_Session("CAA2_Sample_Session"); 
	
	return rc;
		
};


