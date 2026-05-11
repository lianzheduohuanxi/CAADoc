/**
 * @fullreview RCI RCI 01:08:31
 * @error UDOO Y err_1 aPositionAlt not set to NULL after delete
 * @error UDOO Y err_2 aPositionAxis not set to NULL after delete
 * @error UDOO Y err_3 aAbsoluteCoeff not set to NULL after delete
 * @error UDOO Y err_4 aRelativeCoeff not set to NULL after delete
 */
// --------------------------------------------------------
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//

/***********************************************************************************/
/*                   CAAPstMovable.m                                                 */
/***********************************************************************************/
/*

	Abstract :
	--------
	This sample illustrates the way to position products.
	- Creation of a CATProduct Document
	- Insert an existing CATPart
	- Insert it again under a local product
	- Positioning CATParts to separate geometries
	- Move the local product
	- Get absolute position of the second imported CATPart.
	- Retrieve it's relative position with no context => the 
	  local product is the context.

	Usage:
	------
	To run this sample, you can use the command:
     mkrun -c "CAAPstMovable input.CATPart output.CATProduct"
	where input.CATPart is an existing document containing a CATIA part and
    output.CATProduct is the resulting document.

 Return Errors:
 -------------
  1 - ERROR bad argument number
  2 - ERROR in creating CATProduct
  3 - ERROR in Query Interface
  4 - ERROR in Opening the CATPart
  5 - ERROR in Adding an existing external component
  6 - ERROR in retrieving reference of the local product instance
  7 - ERROR in retrieving instance in context of reference
  8 - ERROR in saving document
  9 - ERROR in removing CATProduct document
  

*/
/***********************************************************************************/


#include "CAAPstAddServices.h"

// ObjectModelerBase Framework
#include "CATSessionServices.h" 
#include "CATIDocRoots.h"  
#include "CATDocumentServices.h"  

// System Framework
#include "CATBaseUnknown.h"

// ProductStructure Framework
#include "CATIProduct.h"
#include "CATIMovable.h"

// Mathematics Framework
#include "CATMathTransformation.h"  // matrix to apply to an instance to move it.


#include "iostream.h"

/* --------------------------------------------------------------------------------- */

int main (int argc, char** argv)
{
	HRESULT rc = 0;
	/* ---------------------------------------*/
	/*  0. control of arguments number        */
	/* ---------------------------------------*/
	 if ( 3 != argc )
	 {
		 cout << "ERROR : bad number of arguments " << argc << endl << flush;
		 return 1;  
	 } 

	/* -------------------------------------- */
	/*   1. Creation of a CATProduct document */
	/* -------------------------------------- */
	
	CATSession *pSession = NULL;
	rc = ::Create_Session("CAA2_Sample_Session",
		                   pSession );

	CATDocument *pDoc = NULL;
	rc = CATDocumentServices::New("Product",
		                          pDoc);
	if ( FAILED(rc) || (NULL==pDoc) ) return 2;
	
	cout << endl << "CAAPstMovable.m:	CATProductDocument created " << endl << flush;
	
	
	/* --------------------------------------------------------- */
	/*  2. Search for the document's root product (RootProduct)  */
	/* --------------------------------------------------------- */

	CATIDocRoots *piDocRootsOnDoc = NULL;
	rc = pDoc->QueryInterface(IID_CATIDocRoots,
		                      (void**) &piDocRootsOnDoc);
	if ( FAILED(rc) ) return 3;
	
	// the root product is the first element of root elements
	CATListValCATBaseUnknown_var *pRootProducts =
		piDocRootsOnDoc->GiveDocRoots();
	CATIProduct_var spRootProduct = NULL_var;
	if (pRootProducts)
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
	rc = spRootProduct->QueryInterface(IID_CATIProduct, 
		                               (void**) &piProductOnRoot);
	if ( FAILED(rc) ) return 3;
	           
	/* --------------------------------------------------------------- */
	/* 	3. imports twice an existing CATPart                           */
	/*        - one under the root                                     */
	/*        - another one under an alternate product .            */
	/* --------------------------------------------------------------- */

	CATDocument *pPartDoc = NULL;
	CATIProduct *piInstanceProd1 = NULL;
	cout << endl <<"CAAPstMovable.m:	Let's import the component " << argv[1] << " under the root of created CATProduct"<< endl << flush;
	
	// load of the CATPart to import
	rc = CATDocumentServices::OpenDocument(argv[1],
		                           pPartDoc);
	if ( FAILED(rc) || (!pPartDoc)) return 4;
    cout << "load OK" << endl << flush;
	
	// import the CATPart under the root.
	rc = ::AddExternalComponent(piProductOnRoot, 
		                        pPartDoc,
								&piInstanceProd1);
	if ( FAILED(rc) ) return 5;
    cout << "add catpart under root OK" << endl << flush;

	// creation of a local product under the root.
	CATIProduct_var spAlternateProduct = piProductOnRoot->AddProduct ( "AlternatProd" );
    piProductOnRoot -> Release();
    piProductOnRoot = NULL;
    cout << "add local product OK" << endl << flush;

    CATIProduct *piAlternateProduct = NULL;
	rc = spAlternateProduct->QueryInterface(IID_CATIProduct, (void**) &piAlternateProduct);
	if ( FAILED(rc) ) return 3;
		
	// imports the same CATPart under the local product.
	CATIProduct *piInstanceProd2 = NULL;
	rc = ::AddExternalComponent(piAlternateProduct,
                                pPartDoc,
                                &piInstanceProd2);
	if ( FAILED(rc) ) return 5;
	    cout << "add part under local product OK" << endl << flush;



	/* ------------------------------------------------------------ */
	/*          Positioning CATParts                               */
	/* ------------------------------------------------------------ */

	// Get CATIMovable handle on the instance of product in the context of the
    // reference of the local product.
    CATIProduct_var spReferenceAlternateProduct = piAlternateProduct ->
        GetReferenceProduct();
    piAlternateProduct -> Release();
    piAlternateProduct = NULL;
    if (spReferenceAlternateProduct == NULL_var)
    {
        cout << "ERROR in retrieving the reference of the local product instance" << endl << flush;
        return 6;
    }
    else
        cout << "Reference of the local product instance retrieved OK" << endl << flush;

    CATIProduct_var spMovableInstanceInContext = piInstanceProd2 ->
        FindInstance(spReferenceAlternateProduct);
    if (spMovableInstanceInContext == NULL_var) 
    {
        cout << "ERROR in retrieving the instance in the context of the local reference product" << endl << flush;
        return 7;
    }
    else cout << "Instance in the context of the local reference product retrieved OK" << endl << flush;
    
    
    CATIMovable *piMovableInContext = NULL;
    rc = spMovableInstanceInContext -> QueryInterface(IID_CATIMovable,
                                                      (void**) &piMovableInContext);
	if ( FAILED(rc) ) return 3;
	
	// Get CATIMovable handle on the instance of the local product.
	CATIMovable *piMovableOnAlternate = NULL;
	rc = spAlternateProduct->QueryInterface(IID_CATIMovable,
		                                   (void**) &piMovableOnAlternate);
	if ( FAILED(rc) ) return 3;
	
	// description of the transformation matrix to the local product.
	// 1 0 0 12
	// 0 1 0 12
	// 0 0 1 12

    double *aPositionAlt = new double [12];
	for (int l=0; l < 12; l++)
    	aPositionAlt[l]=0.;
	
	aPositionAlt[0] = 1.;
	aPositionAlt[4] = 1.;
	aPositionAlt[8] = 1.;
	aPositionAlt[9] = 12.;
	aPositionAlt[10] = 12.;
	aPositionAlt[11] = 12.;
	 
	cout << " Applied transformation on the local product: " << endl << flush;
	int m = 0;
 for ( ; m<3; m++)
		cout << aPositionAlt[m] << " " << aPositionAlt[m+3]<< " " << aPositionAlt[m+6] << " " << aPositionAlt[m+9]<< endl << flush;

	// applying the matrix moves the local product.
	CATMathTransformation newRefPosition(aPositionAlt);
	piMovableOnAlternate -> SetPosition(newRefPosition,
		                                NULL_var);
/** @anchor err_1 aPositionAlt not set to NULL after delete */ 
    delete [] aPositionAlt;
	aPositionAlt = NULL;

	// description of the transformation matrix to apply to the imported part under the local product
	// 1 0 0 77
	// 0 1 0 77
	// 0 0 1 77
    double *aPositionAxis = new double [12];
	for (int i=0; i < 12; i++)
    	aPositionAxis[i]=0.;
	
	aPositionAxis[0] = 1.;
	aPositionAxis[4] = 1.;
	aPositionAxis[8] = 1.;
	aPositionAxis[9] = 77.;
	aPositionAxis[10] = 77.;
	aPositionAxis[11] = 77.;
	 
	cout << " Applied transformation on the instance under the local product : " << endl << flush;
	for ( m=0; m<3; m++)
		cout << aPositionAxis[m] << " " << aPositionAxis[m+3]<< " " << aPositionAxis[m+6] << " " << aPositionAxis[m+9]<< endl << flush;
	
	// applying the matrix moves the instance
	CATMathTransformation newPosition(aPositionAxis);
	piMovableInContext -> SetPosition(newPosition,
		                              NULL_var);
/** @anchor err_2 aPositionAxis not set to NULL after delete */ 
    delete [] aPositionAxis;
	aPositionAxis = NULL;

    piMovableInContext -> Release();
    piMovableInContext = NULL;
	
	// let's get absolutes and relatives positions :
	
	// absolute position
    CATIMovable *piMovableOnInstance = NULL;
    rc = piInstanceProd2 -> QueryInterface (IID_CATIMovable,
                                            (void**) &piMovableOnInstance);
    if ( FAILED(rc) ) return 3;

	CATMathTransformation absolutePosition;
	piMovableOnInstance -> GetAbsPosition(absolutePosition );

    double *aAbsoluteCoeff = new double [12];
	absolutePosition.GetCoef(aAbsoluteCoeff);	
	cout << " Absolute position of the instance: " << endl << flush;
	int k = 0;
 for ( ; k<3; k++)
		cout << aAbsoluteCoeff[k] << " " << aAbsoluteCoeff[k+3]<< " " << aAbsoluteCoeff[k+6] << " " << aAbsoluteCoeff[k+9]<< endl << flush;
/** @anchor err_3 aAbsoluteCoeff not set to NULL after delete */ 
	delete[] aAbsoluteCoeff;
	aAbsoluteCoeff = NULL;

	// relative position in the context of the local product.
	// no specification for the context, means default movable will be used.
	CATIMovable_var spContext = NULL_var;
	CATMathTransformation relativePositon = 
		piMovableOnInstance -> GetPosition(spContext);
    double *aRelativeCoeff = new double [12];
	relativePositon.GetCoef(aRelativeCoeff);	
	cout << " Relative position of the instance in the context of the local product: " << endl << flush;
	for ( k=0; k<3; k++)
		cout << aRelativeCoeff[k] << " " << aRelativeCoeff[k+3]<< " " << aRelativeCoeff[k+6] << " " << aRelativeCoeff[k+9]<< endl << flush;
/** @anchor err_4 aRelativeCoeff not set to NULL after delete */ 
	delete[] aRelativeCoeff;
	aRelativeCoeff = NULL;

	piInstanceProd1 -> Release();
	piInstanceProd1 = NULL;
	piInstanceProd2 -> Release();
	piInstanceProd2 = NULL;
	piMovableOnInstance -> Release();
	piMovableOnInstance = NULL;
	piMovableOnAlternate -> Release();
	piMovableOnAlternate = NULL;

	/* ----------------------------------------- */
	/*  save the resulting product               */
	/* ----------------------------------------- */
	cout << endl << "CAAPstMovable.m:	Now we can save the created and modified CATProduct in " << argv[2] << endl << flush;
	rc = CATDocumentServices::SaveAs(*pDoc, 
		                             argv[2]);
	if ( FAILED(rc)  ) return 8;
	

	/* ----------------------------------------- */
	/*   ends the session                        */
	/* ----------------------------------------- */
	
	// remove opened document
	rc = CATDocumentServices::Remove (*pPartDoc);
	if (!SUCCEEDED(rc))  return 9;

	// delete the session, removes the opened documents also.
	// never forget to delete a creating session after usage.
	rc = ::Delete_Session("CAA2_Sample_Session");
	return rc;

};
