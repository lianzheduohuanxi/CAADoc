/**
 * @fullreview RCI RCI 01:08:24
 * @error UNH Y err_1 spRootProduct not tested before use ( if !! )
 */
// --------------------------------------------------------
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

/***********************************************************************************/
/*                   CAAPstAddComponent.m                                          */
/***********************************************************************************/
/*

	Abstract :
	--------
    This sample illustrates the way to insert components in a ProductStructure.
	While using ProductStructure interactively, it is possible to insert a component
	in a product.
	A component is whether a part or another product.
 
	This sample:

		- 1. Creates a CATProduct document.
   		Note that the type to use as parameter for CATDocumentServices::New is "Product".

		- 2. Retrieves the root product of the document.

		- 3. Imports an existing CATPart under the root product.
		( use AddExternalComponent)
	
		- 4. Adds New CATPart in the product. ( named here "NewPart.CATPart" )
		( use AddNewExternalComponent)
		
		- 5. And also a New CATProduct. ( named here "NewProduct.CATProduct" )

		- 6. Saves the CATProduct document. ( SaveAs )
		Note that new external components have to be saved before.

	Usage:
	------
	To run this sample, you can use the command:
		mkrun -c "CAAPstAddComponent input.CATPart PartName ProductName pathNewPart pathNewProduct output.CATProduct"
		where input.CATPart is a path to the CATPart that will be imported, 
			  PartName is the part number to give to the new part imported
			  ProductName is the part number to give to the new product imported
			  pathNewPart is the path where to save the new created part which has name : PartName
			  pathNewProduct is the path where to save the new created product which has name : ProductName
			  output.CATProduct is the path of the created CATProduct
	
* Return Errors:
* -------------
*  1 - ERROR bad argument number
*  2 - ERROR in creating CATProduct
*  3 - ERROR in Query Interface
*  4 - ERROR in Opening the CATPart
*  5 - ERROR in Adding an existing external component
*  6 - ERROR in Adding a new external component
*  7 - ERROR in retrieving document in session.
*  8 - ERROR in saving document
*  9 - ERROR in removing CATProduct document
/***********************************************************************************
*/
#include <iostream.h>

//Local Framework
#include "CAAPstAddServices.h"

// ProductStructure Framework
#include "CATIProduct.h"

// ObjectModelerBase Framework
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "CATIDocRoots.h"

// System Framework
#include "CATUnicodeString.h"
#include "CATLib.h"

/* ----------------------------------------------------------------------------- */

int main (int argc, char** argv)
{
	HRESULT rc = 0;
	/* ---------------------------------------*/
	/*  0. Control of arguments number        */
	/* ---------------------------------------*/
	 if ( 7 != argc )
	 {
		 cout << "ERROR : bad number of arguments " << argc << endl << flush;
		 return 1;  
	 } 

	/* ------------------------------------- */
	/*  1. Creation of a CATProduct document */
	/* ------------------------------------- */
	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session",
		                  pSession );
	
	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::New("Product",
		                          pDoc);
	if ( FAILED(rc) || (NULL==pDoc) ) return 2;

	cout << endl << "CAAPstAddComponent.m:	CATProductDocument created " << endl << flush;
	
	/* --------------------------------------------------------- */
	/*  2. Search for the document's root product (RootProduct)  */
	/* --------------------------------------------------------- */
	CATIDocRoots *piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
		                      (void**) &piDocRootsOnDoc);
	if ( FAILED(rc) ) return 3;
	
	CATListValCATBaseUnknown_var *pRootProducts =
		piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	if (NULL != pRootProducts)
		if (pRootProducts->Size())
		{  
			spRootProduct = (*pRootProducts)[1];
			delete pRootProducts;
			pRootProducts = NULL;
		}
		
	piDocRootsOnDoc->Release();
	piDocRootsOnDoc=NULL;
	
	// Get CATIProduct handle on the root product.
	CATIProduct *piProductOnRoot = NULL;
/** @anchor err_1 spRootProduct not tested before use ( if !! ) */ 
	if ( NULL_var == spRootProduct ) return 2;
	rc = spRootProduct->QueryInterface(IID_CATIProduct,
		                               (void**) &piProductOnRoot);
	if ( FAILED(rc) ) return 3;


	
	/* --------------------------------------------------------- */
	/* 	3. Imports an existing CATPart under the root product.   */
	/* --------------------------------------------------------- */
	CATDocument *pDocPart = NULL;
	CATIProduct *piInstanceProd = NULL;
	cout << endl <<"CAAPstAddComponent.m:	Let's import the component " << argv[1] << " under the root of created CATProduct"<< endl << flush;
	
	// load the given CATPart
	rc = CATDocumentServices::OpenDocument(argv[1],
		                           pDocPart);
	if ( FAILED(rc) || (NULL==pDocPart) ) return 4;
	
	// agregates an instance of the CATPart root element under the product
	rc = ::AddExternalComponent(piProductOnRoot,
		                        pDocPart,
								&piInstanceProd);
	if ( FAILED(rc) ) return 5;
	
	
	/* ----------------------------------------------------- */
	/*  4. Adds a new CATPart under the root product.        */
	/* ----------------------------------------------------- */
	CATIProduct *piInstanceProd2 = NULL;
	CATUnicodeString partName (argv[2]);
	cout << endl <<"CAAPstAddComponent.m:	Let's add a new CATPart under the root product : "<< partName.CastToCharPtr() << endl << flush;
	
	// creates a new part document and imports it under the product
	rc = ::AddNewExternalComponent(piProductOnRoot,
		                           "Part",
								   partName,
								   &piInstanceProd2);
	if ( FAILED(rc) ) return 6;
	
	// search for the document associate to the created new part.
	CATDocument *pPartDoc2 = NULL;
	CATUnicodeString partDocName = partName + ".CATPart";
	rc = CATDocumentServices::GetDocumentInSession (partDocName,
		                                            pPartDoc2);
	if ( FAILED(rc) ) return 7;

	/* ------------------------------------------------------ */
	/*   5. Adds a new CATProduct under the root product.     */
	/* ------------------------------------------------------ */
	CATIProduct *piInstanceProd3 = NULL;
	CATUnicodeString productName (argv[3]);
	cout << endl <<"CAAPstAddComponent.m:  Let's add a new CATProduct under the root product: "<<productName.CastToCharPtr()<< endl << flush;
	
	// creates a new product document and imports it under the product.
	rc = ::AddNewExternalComponent(piProductOnRoot,
		                           "Product",
								   productName,
								   &piInstanceProd3);
	if ( FAILED(rc) ) return 6;

	
	piProductOnRoot -> Release();
	piProductOnRoot = NULL;

	// search for the document associate to the created new product.
	CATDocument *pProdDoc = NULL;
	CATUnicodeString productDocName = productName + ".CATProduct";
	rc = CATDocumentServices::GetDocumentInSession (productDocName ,
		                                            pProdDoc);
	if ( FAILED(rc) ) return 7;

	// do not forget to release imported product 
	piInstanceProd -> Release();
	piInstanceProd = NULL;
	piInstanceProd2 -> Release();
	piInstanceProd2 = NULL;
	piInstanceProd3 -> Release();
	piInstanceProd3 = NULL;


	/* ------------------------------------------------------------ */
	/*  6. Saves all documents concerned by the CATProduct document */
	/* ------------------------------------------------------------ */
	// Don't forget to save the new CATPart imported in the product.
	cout << endl <<"CAAPstAddComponent.m:	Let's save all the documents: "<< endl << flush;
	CATUnicodeString partPath( argv[4]);
	rc = CATDocumentServices::SaveAs(*pPartDoc2, 
		                             partPath);
	if ( FAILED(rc) ) return 8;
	cout << endl <<"CAAPstAddComponent.m:	First the  NewPart.CATPart has been saved in " << partPath.CastToCharPtr() << endl << flush;

	
	// And by the way, the new CATProduct imported in the product.
	CATUnicodeString prodPath( argv[5]);
	rc = CATDocumentServices::SaveAs(*pProdDoc, 
		                             prodPath );
	if ( FAILED(rc) ) return 8;
	cout << endl <<"CAAPstAddComponent.m:	and the NewProduct.CATProduct has been saved in " << prodPath.ConvertToChar() << endl << flush;



	// now we can save the CATProduct.
	cout << endl << "CAAPstAddComponent.m:	Now we can save the created and modified CATProduct in " << argv[6] << endl << flush;
	rc = CATDocumentServices::SaveAs(*pDoc,
		                             argv[6]);
	if ( FAILED(rc) ) return 8;
	
	
	/* ----------------------------------------- */
	/*   ends the session                        */
	/* ----------------------------------------- */
	
	// remove opened document
	rc = CATDocumentServices::Remove (*pDocPart);
	if ( FAILED(rc) ) return 9;

	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	rc = ::Delete_Session("CAA2_Sample_Session");
	return rc;
	
};

