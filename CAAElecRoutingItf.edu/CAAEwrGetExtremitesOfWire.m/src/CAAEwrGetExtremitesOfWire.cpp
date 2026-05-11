// COPYRIGHT DASSAULT SYSTEMES 2011

//=============================================================================
//  Abstract of Use Case "CAAEwrGetExtremitesOfWire":
//  --------------------------------------------------
//
//  This Use Case illustrates how to retrieve the device instances connected to wire extremities.
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session and Opening an Existing CATProduct Document
//      . Retrieving the Root Product of the CATProduct Document
//  2. Initializing Electrical Environment 
//  3. Retrieving an Electrical Bundle under the Root Product and Selecting it to analyze 
//  4. Retrieving List of Wires under the Electrical Bundle
//  5. Query the CATIEwrInterface on these wires and retrieve the extremity devices for each one.
//  6. Epilogue.
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document
//  3 - ERROR in getting root product
//  4 - ERROR in initializing electrical environment 
//  5 - ERROR in searching and retrieveing Electrical Bundle inside Root Product
//  6 - ERROR in retrieving wires inside Electrical Bundle.
//  7 - ERROR in retrieving the Device Instances Linked to the wire at its extremities.
//  8 - ERROR in removing document
//  9 - ERROR in deleting session
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAEwrGetExtremitesOfWire input.CATProduct" where the prefix "input" is the 
//  entire pathname of the directory in which the document is to be found and the
//  name of the of the document itself ().
//
//
//  You may reference the supplied CATProduct document called "RootPRD.CATProduct"
//  found in the 'WS'/'OS'/resources/graphic directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic directory. 
//
//=============================================================================

// System
#include "CATBaseUnknown.h"           // Generic Object
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"  // list of generic objects

// ObjectModelerBase interfaces
#include "CATSessionServices.h"       // managing session
#include "CATDocumentServices.h"      // managing documents in session
#include "CATDocument.h"              // manipulating documents
#include "CATIDocRoots.h"             // browsing root objects in documents
#include "CATSession.h"

// ProductStructure interfaces 
#include "CATIProduct.h"              // managing products    
 
// Electrical interfaces
#include "CATIEleDocServices.h"       // initializing electrical environement 

// ElecAttrAccess
#include "CATIElecAttrAccess.h"		   // interface to get electrical attributes

// ElecRoutingItf
#include "CATIEwrWire.h"             // Interface on ElecWireLight/ElecWire feature to retrieve the device instances at extremities

int main (int argc, char * argv[] )
{ 
  //--------------------------------------------------------------------
  // 1. Prologue 
  //--------------------------------------------------------------------
  HRESULT rc = E_FAIL;
  int retVal = 0;

  CATSession          *   pSession                  = NULL; // NOT to be Released
  CATIEleDocServices  *   pIElecDocServices         = NULL; // pointer to be released
  CATIElecAttrAccess  *   pIElecObjectAttribute     = NULL; // pointer to be released
  CATDocument         *   pDocument                 = NULL; // pDocument is a pointer to the document - NOT to be released
  CATIProduct         *   pIRootProduct             = NULL; // pIRootProduct is a handle to document root product
  CATIDocRoots        *   pIDocRoots                = NULL; // pointer to be released
  CATBaseUnknown      *   pIUnkFirstExtrDeviceInst  = NULL; // pointer to be released after use
  CATBaseUnknown      *   pIUnkFirstExtrCnctPt      = NULL; // pointer to be released after use
  CATBaseUnknown      *   pIUnkSecondExtrDeviceInst = NULL; // pointer to be released after use
  CATBaseUnknown      *   pIUnkSecondExtrCnctPt     = NULL; // pointer to be released after use
  char                *   sessionName               = "CAAEwrGetExtremitesOfWire_Session";

  CATIEwrWire_var         hCurrentEwrWire           = NULL_var;
  CATBaseUnknown_var      hUnkRootPrd               = NULL_var;
  CATIProduct_var         hElectricalBundleProduct  = NULL_var;
  CATBaseUnknown_var      hUnkElectricalBundle      = NULL_var;
  CATUnicodeString        strObjElecType            = "";
  CATUnicodeString        strEBNType                = "ElecBundle";
  
  int i                   = 0;
  int j                   = 0;
  int NumberOfWires       = 0;
  int NumberOfChildren    = 0;
  CATBoolean blnEBNFound  = CATFalse;

  CATListValCATBaseUnknown_var * pListChildrenProductsInElecBundle  = NULL; // list to be deleted
  CATListValCATBaseUnknown_var * pListChildrenProducts              = NULL; // list to be deleted
  CATListValCATBaseUnknown_var * pListRootProduct                   = NULL; // list to be deleted

  // 1.a/ Creating the Session: A session must always be created in a batch
  rc = ::Create_Session(sessionName, pSession);
  if ((FAILED(rc)) || (NULL == pSession)) {retVal = 1; goto EscapeWay;}

  // 1.b/ Opening an existing document
  // The input parameter to this sample program must contain the entire path and name of the document that is to be opened.
  rc = CATDocumentServices::Open(argv[1], pDocument);
  if ((FAILED(rc)) || (NULL == pDocument)) {retVal = 2; goto EscapeWay;}

  // --- Retrieving root product of the opened document
  rc = pDocument->QueryInterface(IID_CATIDocRoots,(void**) &pIDocRoots);
  if ((FAILED(rc)) || (NULL == pIDocRoots)) {retVal = 3; goto EscapeWay;}

  pListRootProduct = pIDocRoots->GiveDocRoots();
  if (NULL == pListRootProduct) {retVal = 3; goto EscapeWay;}
  if ( 0 == pListRootProduct->Size() ) {retVal = 3; goto EscapeWay;}

  hUnkRootPrd = (*pListRootProduct)[1];
  if(NULL_var == hUnkRootPrd) {retVal = 3; goto EscapeWay;}

  rc = hUnkRootPrd->QueryInterface(IID_CATIProduct,(void **)&pIRootProduct);
  if ((FAILED(rc)) || (NULL == pIRootProduct)) {retVal = 3; goto EscapeWay;}
  //--------------------------------------------------------------------
  // 2. Initializing Electrical Environment 
  //--------------------------------------------------------------------
  rc = pDocument->QueryInterface(IID_CATIEleDocServices,(void**) &pIElecDocServices);
  if((FAILED(rc)) || (NULL == pIElecDocServices)) {retVal = 4; goto EscapeWay;}

  rc = pIElecDocServices->Initialize();
  if(FAILED(rc)) {retVal = 4; goto EscapeWay;}

  //--------------------------------------------------------------------
  // 3. Retrieving the Electrical Bundle Inside the Root Product.
  //--------------------------------------------------------------------
  // 3.1/ List all the Products inside 
  pListChildrenProducts = pIRootProduct->GetAllChildren();
  if((FAILED(rc)) || (NULL == pListChildrenProducts)) {retVal = 5; goto EscapeWay;}

  NumberOfChildren = pListChildrenProducts->Size();

  for (i = 1; ((i <= NumberOfChildren) && (CATFalse == blnEBNFound)); i++)
  {
    if(NULL != pIElecObjectAttribute)
    {
      pIElecObjectAttribute->Release();
      pIElecObjectAttribute = NULL;
    }

    hUnkElectricalBundle = NULL_var;
    hUnkElectricalBundle = (*pListChildrenProducts)[i];

    if(NULL_var == hUnkElectricalBundle) {retVal = 6; goto EscapeWay;}

    rc = hUnkElectricalBundle->QueryInterface(IID_CATIElecAttrAccess, (void **)&pIElecObjectAttribute);

    if ((SUCCEEDED(rc)) && (NULL != pIElecObjectAttribute))
    {
      pIElecObjectAttribute->GetElecType(strObjElecType);
      if (2 == strObjElecType.Compare(strEBNType))
        blnEBNFound = CATTrue;
    }
  }
  if(CATFalse == blnEBNFound) {retVal = 5; goto EscapeWay;}

  //--------------------------------------------------------------------
  // 5. List the Wires Inside the Electrical Bundle
  //--------------------------------------------------------------------
  hElectricalBundleProduct = hUnkElectricalBundle;
  if(NULL_var == hElectricalBundleProduct) {retVal = 6; goto EscapeWay;}

  pListChildrenProductsInElecBundle = hElectricalBundleProduct->GetAllChildren(CATIEwrWire::ClassName());
  if((FAILED(rc)) || (NULL == pListChildrenProductsInElecBundle)) {retVal = 6; goto EscapeWay;}

  NumberOfWires = pListChildrenProductsInElecBundle->Size();
  if(0 == NumberOfWires) {retVal = 6; goto EscapeWay;}

  for (j = 1; j <= NumberOfWires; j++)
  {
    if(NULL != pIUnkFirstExtrDeviceInst)
    {
      pIUnkFirstExtrDeviceInst->Release();
      pIUnkFirstExtrDeviceInst = NULL;
    }
    if(NULL != pIUnkFirstExtrCnctPt)
    {
      pIUnkFirstExtrCnctPt->Release();
      pIUnkFirstExtrCnctPt = NULL;
    }
    if(NULL != pIUnkSecondExtrDeviceInst)
    {
      pIUnkSecondExtrDeviceInst->Release();
      pIUnkSecondExtrDeviceInst = NULL;
    }
    if(NULL != pIUnkSecondExtrCnctPt)
    {
      pIUnkSecondExtrCnctPt->Release();
      pIUnkSecondExtrCnctPt = NULL;
    }
    hCurrentEwrWire = NULL_var;

    hCurrentEwrWire = (*pListChildrenProductsInElecBundle)[j];
    if(NULL_var == hCurrentEwrWire){continue;}

    rc = hCurrentEwrWire->GetExtremities(pIUnkFirstExtrDeviceInst, pIUnkFirstExtrCnctPt, pIUnkSecondExtrDeviceInst, pIUnkSecondExtrCnctPt);

    if((FAILED(rc)) || (NULL == pIUnkFirstExtrDeviceInst) || (NULL == pIUnkSecondExtrDeviceInst)) {retVal = 7; goto EscapeWay;}
    // pIUnkFirstExtrDeviceInst is the Device Instance Connected to the First Wire Extremity.
    // pIUnkSecondExtrDeviceInst is the Device Instance Connected to the Second Wire Extremity.
  }
  //--------------------------------------------------------------------
  // 6. Epilogue  
  //--------------------------------------------------------------------
  // --- removing document from session 
  rc = CATDocumentServices::Remove(*pDocument);
  if (FAILED(rc)){retVal = 8; goto EscapeWay;}
  
  // --- closing the session
  rc = ::Delete_Session(sessionName);
  if (FAILED(rc)){retVal = 9; goto EscapeWay;}

EscapeWay:
  if(NULL != pIDocRoots)
  {
    pIDocRoots->Release();
    pIDocRoots = NULL;
  }
  if(NULL != pIRootProduct)
  {
    pIRootProduct->Release();
    pIRootProduct = NULL;
  }
  if(NULL != pIElecDocServices)
  {
    pIElecDocServices->Release();
    pIElecDocServices = NULL;
  }
  if(NULL != pIElecObjectAttribute)
  {
    pIElecObjectAttribute->Release();
    pIElecObjectAttribute = NULL;
  }
  if(NULL != pIUnkFirstExtrDeviceInst)
  {
    pIUnkFirstExtrDeviceInst->Release();
    pIUnkFirstExtrDeviceInst = NULL;
  }
  if(NULL != pIUnkFirstExtrCnctPt)
  {
    pIUnkFirstExtrCnctPt->Release();
    pIUnkFirstExtrCnctPt = NULL;
  }
  if(NULL != pIUnkSecondExtrDeviceInst)
  {
    pIUnkSecondExtrDeviceInst->Release();
    pIUnkSecondExtrDeviceInst = NULL;
  }
  if(NULL != pIUnkSecondExtrCnctPt)
  {
    pIUnkSecondExtrCnctPt->Release();
    pIUnkSecondExtrCnctPt = NULL;
  }
  if(NULL != pListChildrenProductsInElecBundle)
  {
    delete pListChildrenProductsInElecBundle;
    pListChildrenProductsInElecBundle = NULL;
  }
  if(NULL != pListRootProduct)
  {
    delete pListRootProduct;
    pListRootProduct = NULL;
  }
  if(NULL != pListChildrenProducts)
  {
    delete pListChildrenProducts;
    pListChildrenProducts = NULL;
  }

  return retVal;
}
