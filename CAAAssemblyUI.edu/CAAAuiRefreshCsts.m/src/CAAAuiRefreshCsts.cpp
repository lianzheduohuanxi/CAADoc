/* -*-c++-*- */
//
// COPYRIGHT DASSAULT SYSTEMES 2004
//
//============================================================================================
// Sample code for : Assembly
// Mission         : Refresh the constraints of an assembly.
//
// Type            : Batch program
// Inputs          : -
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Opening a CATIA session and two document             (1)
//                   o Searching for the documents' root products           (2)
//                   o Importing an existing CATPart under the root product (3)
//                   o Refreshing all the constraints of the root product   (4)
//                   o Saving all documents                                 (5)
//                   o ending the session                                   (6)
//
// Return codes :
//
//  01 - wrong number of arguments  
//  02 - creation of session or open of document failed  
//  03 - access to the root product failed
//  04 - opening a CATPart document failed
//  05 - inserting existing CATPart document failed
//  06 - refreshing constraints failed
//  07 - Saving documents failed
//  08 - removing document or deleting the session failed
//
//
// use: CAAAuiRefreshCsts InputDirectory
//
//============================================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h" 
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerBase Framework
#include "CATDocumentServices.h"   // to open and close document
#include "CATSession.h"
#include "CATSessionServices.h"    // to open and close session
#include "CATIDocRoots.h"          // to identify the root of a document
#include "CATDocument.h"           // to work with documents
 
// CATAssemblyInterfaces Framework
#include "CATAsmConstraintServices.h"  // constraint creation

// ProductStructure Framework
#include "CATIProduct.h"

//-----------------------------------------------------------------

int main (int iArgc, char** iArgv ) 
{
  if ( 3 != iArgc )
  {
    printf("wrong number of arguments\n");
    return 1; // wrong number of arguments
  }

  /* --------------------------------------------------------- */
  /*  0. Open the CATIA session and open the input Documents   */
  /* --------------------------------------------------------- */

  printf("0 - opening a Session\n");
  CATSession * pSession = NULL;
  HRESULT rc = ::Create_Session( "Session_ASSEMBLY", pSession );
  if ( FAILED(rc) ) 
  {
    printf("     -> failed\n");
    return 2;
  }
  printf("     -> done\n");
  
  printf("  - opening Product Document\n");
  CATDocument * pProductDocument = NULL;
  rc = CATDocumentServices::OpenDocument( iArgv[1], pProductDocument, FALSE );
  if ( FAILED(rc) || (NULL == pProductDocument) ) 
  {
    printf("     -> failed\n");
    return 2;
  }
  printf("     -> done\n");

  /* --------------------------------------------------------- */
  /*  1. Search for the documents' root product (RootProduct)  */
  /* --------------------------------------------------------- */

  printf("1 - searching the root product\n");
  CATIProduct * piProductOnRoot = NULL;
  CATIDocRoots * piDocRootsOnDoc = NULL;
  rc = pProductDocument->QueryInterface( IID_CATIDocRoots, (void **) & piDocRootsOnDoc );
  if ( SUCCEEDED(rc) ) 
  {
    CATListValCATBaseUnknown_var * pRootProducts = piDocRootsOnDoc->GiveDocRoots();
    if ( NULL != pRootProducts )
    {
      if ( 0 < pRootProducts->Size() )
      {  
        CATBaseUnknown_var spBU_Root = (*pRootProducts)[1];
        if ( NULL_var != spBU_Root )
        {
          spBU_Root->QueryInterface( IID_CATIProduct,(void **) & piProductOnRoot );
        }
      }
      delete pRootProducts;
      pRootProducts = NULL;
    }
    
    // releasing useless data
    piDocRootsOnDoc->Release();
    piDocRootsOnDoc = NULL;
  }

  if ( NULL == piProductOnRoot ) 
  {
    printf("     -> failed\n");
    return 3;
  }
  printf("     -> done\n");
    

  /* --------------------------------------------------------- */
  /* 	2. Imports an existing CATPart under Root component.    */
  /* --------------------------------------------------------- */

  printf("2 - opening Part Document\n");
  CATDocument * pPartDocument = NULL;
  rc = CATDocumentServices::OpenDocument( iArgv[2], pPartDocument );
  if ( FAILED(rc) || ( NULL == pPartDocument ) ) 
  {
    printf("     -> failed\n");
    piProductOnRoot->Release();
    piProductOnRoot = NULL;
    return 4;
  }
  printf("     -> done\n");
  
  // insert the given part in root product
  printf("  - inserting the part under the root product and changing its instance name\n");
  CATIDocRoots * piDocRootsOnOpenedDoc = NULL;
  CATIProduct_var spProduct;
  rc = pPartDocument->QueryInterface( IID_CATIDocRoots, (void **) & piDocRootsOnOpenedDoc );
  if ( SUCCEEDED(rc) )
  {
    CATListValCATBaseUnknown_var * pRootProducts = piDocRootsOnOpenedDoc->GiveDocRoots();
    if ( NULL != pRootProducts)
    {
      if ( pRootProducts->Size() > 0 )
      {  
        CATIProduct_var spPrd_PartRoot = (*pRootProducts)[1];
        if ( NULL_var != spPrd_PartRoot )
        {
          spProduct = piProductOnRoot->AddProduct( spPrd_PartRoot );
        }
      }
      delete pRootProducts;
      pRootProducts = NULL;
    }
    piDocRootsOnOpenedDoc->Release();
    piDocRootsOnOpenedDoc=NULL;
  }

  if ( NULL_var != spProduct )
  {
    spProduct->SetPrdInstanceName( "Part1.1" );
  }
  else
  {
    printf("     -> failed\n");
    piProductOnRoot->Release();
    piProductOnRoot = NULL;
    return 5;
  }
  printf("     -> done\n");


  /*-------------------------------------------------------------*/
  /*  3. refresh of the constraints of the root product
  /*-------------------------------------------------------------*/      
  
  printf("3 - refreshing constraints\n");
  rc = CATAsmConstraintServices::RefreshConstraintsInProduct( piProductOnRoot );

  // releasing useless data
  piProductOnRoot->Release();
  piProductOnRoot = NULL;

  if ( FAILED( rc ) )
  {
    printf("     -> failed\n");
    return 6;
  }
  printf("     -> done\n");

  //---------------------------
  // 4 - Save all documents
  //---------------------------
  printf("  - saving Root Product\n");
  CATUnicodeString StorageNameDocument = pProductDocument->StorageName();
  rc = CATDocumentServices::SaveAs( * pProductDocument, StorageNameDocument );
  if ( S_OK != rc ) 
  {
    printf("     -> failed\n");
    return 7;
  }  
  printf("     -> done\n");

  /* ----------------------------------------- */
  /*  5 - end the session                        */
  /* ----------------------------------------- */
  
  printf("5 - removing the documents\n");
  // remove opened document
  HRESULT rc1 = CATDocumentServices::Remove (*pProductDocument);
  HRESULT rc2 = CATDocumentServices::Remove (*pPartDocument);
  if ( FAILED(rc1) || FAILED(rc2) ) 
  {
    printf("     -> failed\n");
    return 8;
  }
  printf("     -> done\n");
  
  // delete the session.
  printf("  - ending the session\n");
  rc = ::Delete_Session("Session_ASSEMBLY");
  if ( FAILED(rc) ) 
  {
    printf("     -> failed\n");
    return 8;
  }
  printf("     -> done\n");

  // good bye
  return 0;
}  
