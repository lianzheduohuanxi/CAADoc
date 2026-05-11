/**
 * @fullreview RCI RCI 01:08:24
 * @error UNP Y err_1 iThisProduct not tested before use
 * @error UNP Y err_2 iThisProduct not tested before use
 * @error UDOO Y err_3 spRootProduct : tester la valeur du pointeur ( !! )
 * @error UNP Y err_4 iThisProduct not tested before use
 */
// --------------------------------------------------------
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

//Local Framework
#include "CAAPstAddServices.h"    


// ObjetModelerBase Framework
#include "CATIDocRoots.h"         
#include "CATDocumentServices.h"  


#include "iostream.h"             

//-------------------------------------------------------------------------
//                Service to import an external component 
//-------------------------------------------------------------------------
HRESULT AddExternalComponent(CATIProduct *iThisProd, CATDocument *iDocument, CATIProduct **oNewProduct)
{
	if ( ! iThisProd ) return 1;

	HRESULT rc = E_FAIL;
	
	if ( NULL != iDocument)
	{
		// Get RootProduct of the document to import.
		CATIDocRoots *piDocRootsOnDoc = NULL;
		rc = iDocument->QueryInterface(IID_CATIDocRoots,
			                           (void**) &piDocRootsOnDoc);
		if ( FAILED(rc) )
		{
			cout << "** QI on CATIDocRoots failed " << endl<< flush;
			return rc;
		}
		
		CATListValCATBaseUnknown_var *pRootProducts = 
			piDocRootsOnDoc->GiveDocRoots();
		CATIProduct_var spRootProduct = NULL_var;
		if ( NULL != pRootProducts)
			if (pRootProducts->Size())
			{  
				// the root product is first element of
				// the list of root elements.
				spRootProduct = (*pRootProducts)[1];
				delete pRootProducts;
				pRootProducts = NULL;
			}
			
		piDocRootsOnDoc->Release();
		piDocRootsOnDoc=NULL;
		
		CATIProduct_var spProduct = NULL_var;
		if (NULL_var != spRootProduct)
		{
		// We have the root product from which one
			// will be agregated in "this"
/** @anchor err_1 iThisProduct not tested before use */ 
		spProduct = iThisProd->AddProduct   (spRootProduct);
		}
		else
		{
			CATUnicodeString docName = iDocument-> StorageName();
/** @anchor err_2 iThisProduct not tested before use */ 
			iThisProd->AddShapeRepresentation(CATUnicodeString("model"),
				                              docName);
			return 3;
		}

		rc = spProduct->QueryInterface(IID_CATIProduct, 
			                           (void**) &*oNewProduct);
		
	}
	return rc; 
} 



//-------------------------------------------------------------------------
//       Creates a CATProduct or CATPart document and then imports it 
//-------------------------------------------------------------------------
HRESULT AddNewExternalComponent(CATIProduct* iThisProd, const CATUnicodeString iDocumentType,const CATUnicodeString iPartNumber, CATIProduct** oNewProduct)
{
	if ( ! iThisProd ) return 1;

	HRESULT rc = E_FAIL;
	*oNewProduct = NULL;
	
	CATUnicodeString product = "Product";
	CATUnicodeString part = "Part";

	if ( (iDocumentType != product) &&  (iDocumentType != part) )
	{
		cout << " ERROR in AddNewExternalComponent : document type : " << iDocumentType.CastToCharPtr() << " is not allowed "<< endl << flush;
		return rc;
	}

	// Creation of document CATProduct/CATPart
	CATDocument *pNewDoc = NULL;
	rc = CATDocumentServices::New(iDocumentType,
		                          pNewDoc );
	if ( FAILED(rc) || (NULL==pNewDoc) )
	{
		cout << "ERROR : document Creation Failed" << endl<< flush;
		return rc;
	}

	
	cout << endl << "CAAPstAddServices.m:	document of type " <<  iDocumentType.CastToCharPtr() << " created " << endl << flush;
	

	// Import document in this product
	if ( SUCCEEDED( rc ) )
	{
		// Get RootProduct of the created document.
		CATIDocRoots *piDocRootsOnNewDoc = NULL;
		rc = pNewDoc->QueryInterface(IID_CATIDocRoots,
			                         (void**) &piDocRootsOnNewDoc);
		if ( SUCCEEDED( rc ) )
		{			
			CATListValCATBaseUnknown_var *pRootProducts =
				piDocRootsOnNewDoc->GiveDocRoots();
			CATIProduct_var spRootProduct;
			if (NULL != pRootProducts)
				if (pRootProducts->Size())
				{  
					// the root product is first element of
					// the list of root elements.
					spRootProduct = (*pRootProducts)[1];
					delete pRootProducts;
					pRootProducts = NULL;
				}
				
				piDocRootsOnNewDoc->Release();
				piDocRootsOnNewDoc=NULL;
			
				if (NULL_var != spRootProduct)
					{
					// Set PartNumber to the created root
					// ATTENTION : be sure that the part number is single
					// in a document .
					spRootProduct -> SetPartNumber(iPartNumber);
	
					// We have the root product from which one
					// will be agregated in "this"
/** @anchor err_3 spRootProduct : tester la valeur du pointeur ( !! ) */ 
					CATIProduct_var spProduct;
/** @anchor err_4 iThisProduct not tested before use */ 
					spProduct = iThisProd->AddProduct   (spRootProduct);
					if (NULL_var ==  spProduct ) return 2;
					rc = spProduct->QueryInterface(IID_CATIProduct, 
						                           (void**) &*oNewProduct);

				}
		}
	}
	return rc; 

}
