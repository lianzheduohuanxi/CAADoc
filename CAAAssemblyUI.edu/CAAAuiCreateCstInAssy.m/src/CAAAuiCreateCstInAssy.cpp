/* -*-c++-*- */
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//============================================================================================
// Sample code for : Assembly
// Mission         : Create and modify a fix constraint on a component of a CATProduct.
//
// Type            : Batch program
// Inputs          : Product file
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Loading document in session   (1)
//                   o Creating a connector          (2)
//                   o Creating a constraint         (3)
//                   o Modifying the constraint      (4)
//                   o Deleting the constraint       (5)
//
// Return codes :
//
//  10 - File could not be found or has problem  
//  11 - QI on CATIDocRoots failed
//  12 - Root product could not be found
//
//  21 - No component under root product
//  22 - QI failed on products
//  23 - No connector created
//
//  30 - No constraint created
//
//  40 - No constraint modified
//
//  50 - Constraint not destroyed
//
//
// use: CAAAuiCreateCstInAssembly xxx.CATProduct
// xxx.CATProduct need at least one component under the root product.
//
//============================================================================================

#include <iostream.h>

// System Framework
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATLib.h"
#include "CATUnicodeString.h" 

// ObjectModelerBase Framework
#include "CATDocumentServices.h"   // to open and close document
#include "CATSessionServices.h"    // to open and close session
#include "CATIDocRoots.h"          // to identify the root of a document
#include "LifeCycleObject.h"       // to delete objects
#include "CATDocument.h"           // to work with documents
 
// MecModInterfaces Framework 
#include "CATConstraintType.h"     // constraint type definitions

// CATAssemblyInterfaces Framework
#include "CATAsmConstraintServices.h"  // constraint creation
#include "CATAsmConnectorServices.h"   // connector creation

// ObjectSpecModeler Framework
#include "CATIConnector.h" 

// ConstraintModelerInterfaces Framework
#include "CATICst.h"

// ProductStructure Framework
#include "CATIProduct.h"

//-----------------------------------------------------------------

int main (int iArgc, char** iArgv ) 
{

  //--------------------------------
  // 1 - Loading document in session
  //--------------------------------

  cout <<" Test CAAUiCreateCstInAssembly "<<endl;
  cout <<" ============================= "<<endl;

  // Checking arguments
  if(2 != iArgc)
    return 10; // wrong number of arguments
  
  // Opening a session  
  CATSession* pSession = NULL;
  HRESULT rc = Create_Session("Session_ASSEMBLY",pSession);
  cout << "Session Created" << endl;  

  // Opening a document
  CATDocument * pProductDocument = NULL;
  rc = CATDocumentServices::OpenDocument(iArgv[1],pProductDocument);

  if ( FAILED(rc) || (NULL == pProductDocument) )
  {
    cout << " ERROR: Document not found " << endl<< flush;
    return 11;
  }
  cout << "Document opened" <<endl;
  
  // Searching the root product  
  CATIDocRoots *piDocRootsOnDoc = NULL;
  rc = pProductDocument->QueryInterface(IID_CATIDocRoots, (void**) &piDocRootsOnDoc);
  if ( FAILED(rc) )
  {
    cout << " ERROR: QI on CATIDocRoots failed " << endl<< flush;
    return 11;
  }
  CATListValCATBaseUnknown_var *pRootProducts = piDocRootsOnDoc->GiveDocRoots();
  CATIProduct_var spRootProduct = NULL_var;
  if( NULL != pRootProducts )
  {  
    if( 0 != pRootProducts->Size() )
    {
      spRootProduct = (*pRootProducts)[1];
      delete pRootProducts;
      pRootProducts = NULL;
    }  
    piDocRootsOnDoc->Release();
    piDocRootsOnDoc = NULL;
  }
  if (NULL_var == spRootProduct)
  {
    cout << " ERROR: No root product !!  " << endl << flush;
    return 12; 
  }
  cout <<"Root product found successfully"<<endl;

  //--------------------------
  // 2 - Creating a connector
  //--------------------------

  // Searching a product to constraint
  int nbChild =  spRootProduct->GetChildrenCount();
  CATListValCATBaseUnknown_var* pListChild = spRootProduct->GetChildren("CATIProduct");
  CATIProduct_var spProdToConstraint;
  if( (NULL != pListChild) && (0 != pListChild->Size()) )
  {
    spProdToConstraint = ( (*pListChild)[1] );
    delete pListChild;
    pListChild = NULL;
  }
  if (NULL_var == spProdToConstraint)
  {
    cout << " ERROR: No component under root product" << endl << flush;
    return 21; 
  }
  cout << " component found under root product"<<endl;

  // creating connector
  CATIConnector       * pConnector = NULL;
  CATIProduct         * pActiveComponent = NULL;
  CATIProduct         * pInstanceComponent = NULL;
  CATILinkableObject  * pGeometry = NULL;
  int                   iCreation = 0;

  rc = spRootProduct->QueryInterface(IID_CATIProduct,(void **)&pActiveComponent);
  if (rc != S_OK)
    return 22;
  rc = spProdToConstraint->QueryInterface(IID_CATIProduct,(void **)&pInstanceComponent);
  if (rc != S_OK)
    return 22;
  rc = spProdToConstraint->QueryInterface(IID_CATILinkableObject,(void **)&pGeometry);
  if (rc != S_OK)
    return 22;
  GetProductConnector(pGeometry,pInstanceComponent,pActiveComponent,0,pConnector,iCreation);

  if (NULL == pConnector)
  {
    cout << " ERROR: No connector created  " << endl << flush;
	return 23;
  }
  cout <<" connector created "<<endl;

  pGeometry->Release();
  pGeometry = NULL;
  pInstanceComponent->Release();
  pInstanceComponent = NULL;

  //---------------------------
  // 3 - Creating a constraint
  //---------------------------

  CATICst *pCst = NULL;
  CATLISTV (CATBaseUnknown_var) ConnectorList;
  ConnectorList.Append(pConnector);

  pConnector->Release();
  
  rc = CreateConstraint(catCstTypeReference,ConnectorList,NULL,pActiveComponent,&pCst);

  pActiveComponent->Release();
  pActiveComponent = NULL;

  if (S_OK != rc)
  {
    cout << " ERROR: no constraint created  " << endl << flush;
    return 30; 
  }
  cout << "Constraint adress = " << pCst << endl;
  cout << "Constraint created with success"<<endl;

  //------------------------------
  // 4 - Modifying the constraint
  // -----------------------------

  if (NULL != pCst)
   pCst->SetCstAttrValue(CATCstAttr_Reference,CATCstVal_Reference_Relative);
  else
  {
    cout << "ERROR: no constraint modified" << endl << flush;
    return 40; 
  }
  cout << "Constraint modified successfully"<<endl;

  //-----------------------------
  // 5 - Deleting the constraint
  // -----------------------------

  LifeCycleObject *pLCO_Cst = NULL;
  rc = pCst->QueryInterface(IID_LifeCycleObject,(void **)&pLCO_Cst);
  pCst->Release();  
  pCst = NULL;
  if( SUCCEEDED(rc) )
  {
    pLCO_Cst->remove();
    pLCO_Cst->Release();
    pLCO_Cst = NULL;
  }
  else
  {
    cout << "ERROR: Constraint not destroyed  " << endl << flush;
    return 50; 
  }
  cout << "Constraint deleted successfully"<<endl;
  	  
  //-------------
  // 6 - Exiting
  //------------

  // closing document
  CATDocumentServices::Remove(*pProductDocument);

  // closing session
  Delete_Session("Session_ASSEMBLY");
  cout << "Session cleaned succesfully"<<endl;
  cout << "Normal End"<<endl;

  return rc;
}
