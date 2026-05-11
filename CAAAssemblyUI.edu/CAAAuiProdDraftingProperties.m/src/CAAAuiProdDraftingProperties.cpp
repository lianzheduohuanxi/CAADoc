/* -*-c++-*- */
//
// COPYRIGHT DASSAULT SYSTEMES 2004
//
//============================================================================================
// Sample code for : Assembly
// Mission         : Retrieves and sets the drafting properties for a product's component.
//
// Type            : Batch program
// Inputs          : -
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Opening a CATIA session and two document             (0)
//                   o Searching for the documents' root products           (1)
//                   o Searching for instances in the document              (2)
//                   o Modifying drafting properties on instances           (3)
//                   o Saving all documents                                 (4)
//                   o ending the session                                   (5)
//
// Return codes :
//
//  01 - wrong number of arguments  
//  02 - creation of session or open of document failed  
//  03 - access to the root product failed
//  04 - instance not found
//  05 - drafting properties not found on given instance
//  06 - Saving documents failed
//  07 - removing document failed
//  08 - deleting the session failed
//
//
// use: CAAAuiProdDraftingProperties InputDocument OutputDocument
//
//============================================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h" 
#include "CATLISTV_CATBaseUnknown.h"
#include "CATBoolean.h"

// ObjectModelerBase Framework
#include "CATDocumentServices.h"   // to open and close document
#include "CATSession.h"
#include "CATSessionServices.h"    // to open and close session
#include "CATIDocRoots.h"          // to identify the root of a document
#include "CATDocument.h"           // to work with documents
 
// CATAssemblyInterfaces Framework
#include "CATIProdDraftingProperties.h"  // constraint creation

// ProductStructure Framework
#include "CATIProduct.h"

//-----------------------------------------------------------------

int main (int iArgc, char** iArgv ) 
{
  if ( 3 != iArgc )
  {
    printf("wrong number of arguments\n");
    printf("Correct use: CAAAuiProdDraftingProperties InputDocument OutputDocument\n");
    return 1; // wrong number of arguments
  }

  int ReturnCode = 0;

  /* --------------------------------------------------------- */
  /*  0. Open the CATIA session and open the input Document   */
  /* --------------------------------------------------------- */

  printf("0 - opening a Session\n");
  CATSession * pSession = NULL;
  HRESULT rc = ::Create_Session( "CAA2_Sample_Session", pSession );
  if ( SUCCEEDED(rc) ) 
  {
    printf("     -> done\n");
    
    printf("  - opening the document:\n  %s", iArgv[1]);
    CATDocument * pDoc = NULL;
    rc = CATDocumentServices::OpenDocument( iArgv[1], pDoc, FALSE );
    if ( SUCCEEDED(rc) && NULL != pDoc ) 
    {
      printf("     -> done\n");
      
      /* --------------------------------------------------------- */
      /*  1. Search for the document's root product                */
      /* --------------------------------------------------------- */
      
      printf("1 - searching the root product\n");
      CATIProduct * piProductOnRoot = NULL;
      CATIDocRoots * piDocRootsOnDoc = NULL;
      rc = pDoc->QueryInterface( IID_CATIDocRoots, (void **) & piDocRootsOnDoc );
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
      
      if ( NULL != piProductOnRoot ) 
      {
        printf("     -> done\n");
        
        /* ----------------------------------------------------------- */
        /* 	2. Search for Screw.1, Nut.1 and Washer.1 instances.       */
        /* ----------------------------------------------------------- */
        
        printf("2 - searching the instances\n");

        CATIProduct * piProd_Screw = NULL;
        CATIProduct * piProd_Nut = NULL;
        CATIProduct * piProd_Washer = NULL;
        
        CATUnicodeString strScrewName = "Screw.1";
        CATUnicodeString strNutName = "Nut.1";
        CATUnicodeString strWasherName = "Washer.1";
        
        CATListValCATBaseUnknown_var * pLst_Children = piProductOnRoot->GetChildren();
        if ( NULL != pLst_Children )
        {
          int size = pLst_Children->Size();
          for ( int i = 1; i <= size; i++ )
          {
            CATIProduct_var hiProd_Child = (*pLst_Children)[i];
            if ( NULL_var != hiProd_Child )
            {
              CATUnicodeString strName;
              hiProd_Child->GetPrdInstanceName( strName );
              if ( strName == strScrewName )
              {
                printf("     -> Screw.1 found\n");
                hiProd_Child->QueryInterface( IID_CATIProduct, (void **) & piProd_Screw );
              }
              else if ( strName == strNutName )
              {
                printf("     -> Nut.1 found\n");
                hiProd_Child->QueryInterface( IID_CATIProduct, (void **) & piProd_Nut );
              }
              else if ( strName == strWasherName )
              {
                printf("     -> Washer.1 found\n");
                hiProd_Child->QueryInterface( IID_CATIProduct, (void **) & piProd_Washer );
              }
            }
          }
          
          delete pLst_Children;
          pLst_Children = NULL;
        }
        
        /*-------------------------------------------------------------*/
        /*  3. Modify drafting properties of the instances             */
        /*-------------------------------------------------------------*/
        
        printf("2 - modifying Screw.1 properties\n");
        if ( NULL != piProd_Screw )
        {
          CATIProdDraftingProperties * piProd_DftProp = NULL;
          if ( SUCCEEDED( piProd_Screw->QueryInterface( IID_CATIProdDraftingProperties, (void **) & piProd_DftProp ) ) )
          {
            CATBoolean showHiddenLines = FALSE;
            piProd_DftProp->GetHiddenLineMode( showHiddenLines );
            if ( FALSE == showHiddenLines )
            {
              piProd_DftProp->SetHiddenLineMode( TRUE );
            }
            printf("     -> done\n");
            piProd_DftProp->Release();
            piProd_DftProp = NULL;
          }
          else
          {
            printf("     -> failed\n");
            ReturnCode = 5;
          }
          piProd_Screw->Release();
          piProd_Screw = NULL;  
        }
        else
        {
          printf("     -> failed\n");
          ReturnCode = 4;
        }
        
        printf("2 - modifying Nut.1 properties\n");
        if ( NULL != piProd_Nut )
        {
          CATIProdDraftingProperties * piProd_DftProp = NULL;
          if ( SUCCEEDED( piProd_Nut->QueryInterface( IID_CATIProdDraftingProperties, (void **) & piProd_DftProp ) ) )
          {
            CATBoolean cut = FALSE;
            piProd_DftProp->GetCutStatus( cut );
            if ( TRUE == cut )
            {
              piProd_DftProp->SetCutStatus( FALSE );
            }
            printf("     -> done\n");
            piProd_DftProp->Release();
            piProd_DftProp = NULL;
          }
          else
          {
            printf("     -> failed\n");
            ReturnCode = 5;
          }
          piProd_Nut->Release();
          piProd_Nut = NULL;  
        }
        else
        {
          printf("     -> failed\n");
          ReturnCode = 4;
        }
        
        printf("2 - modifying Washer.1 properties\n");
        if ( NULL != piProd_Washer )
        {
          CATIProdDraftingProperties * piProd_DftProp = NULL;
          if ( SUCCEEDED( piProd_Washer->QueryInterface( IID_CATIProdDraftingProperties, (void **) & piProd_DftProp ) ) )
          {
            CATBoolean use = FALSE;
            piProd_DftProp->GetUseStatus( use );
            if ( TRUE == use )
            {
              piProd_DftProp->SetUseStatus( FALSE );
            }
            printf("     -> done\n");
            piProd_DftProp->Release();
            piProd_DftProp = NULL;
          }
          else
          {
            printf("     -> failed\n");
            ReturnCode = 5;
          }
          piProd_Washer->Release();
          piProd_Washer = NULL;  
        }
        else
        {
          printf("     -> failed\n");
          ReturnCode = 4;
        }
        
        piProductOnRoot->Release();
        piProductOnRoot = NULL;
        
        /*-------------------------------------------------------------*/
        /* 4 - Save the document if necessary                          */
        /*-------------------------------------------------------------*/
        
        if ( 0 == ReturnCode )
        {
          printf("  - saving the CATProduct\n");
          rc = CATDocumentServices::SaveAs( * pDoc, iArgv[2] );
          if ( S_OK != rc ) 
          {
            printf("     -> failed\n");
            ReturnCode = 6;
          }  
          printf("     -> done\n");
        }
      }
      else
      {
        printf("     -> failed\n");
        ReturnCode = 3;
      }
      
      /* ----------------------------------------- */
      /*  5 - End the session                      */
      /* ----------------------------------------- */
      
      printf("5 - removing the documents\n");
      // remove opened document
      rc = CATDocumentServices::Remove (*pDoc);
      if ( FAILED(rc) ) 
      {
        printf("     -> failed\n");
        ReturnCode = 7;
      }
      printf("     -> done\n");
    }
    else
    {
      printf("     -> failed\n");
      ReturnCode = 2;
    }

    // delete the session.
    printf("  - ending the session\n");
    rc = ::Delete_Session("CAA2_Sample_Session");
    if ( FAILED(rc) ) 
    {
      printf("     -> failed\n");
      ReturnCode = 8;
    }
    printf("     -> done\n");
  }
  else
  {
    printf("     -> failed\n");
    ReturnCode = 2;
  }

  // good bye
  return ReturnCode;
}  
