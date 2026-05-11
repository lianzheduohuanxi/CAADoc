/* -*-c++-*- */
//
// COPYRIGHT DASSAULT SYSTEMES 1999
//
//============================================================================================
// Sample code for : Assembly
// Mission         : Create parallelism constraint between two components.
//
// Type            : Batch program
// Inputs          : -
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Searching for the document's root product            (1)
//                   o Adding a new CATPart under the root product          (2)
//                   o Importing an existing CATPart under the root product (3)
//                   o creating of a connector on a reference plane yz      (4)
//                   o creation of a connector on a face                    (5)
//                   o Creating a constraint                                (6)
//                   o Saving all documents                                 (7)
//                   o ending the session                                   (8)
//
// Return codes :
//
//  02 - creation of session or document failed  
//  03 - access to the root product failed
//  04 - creating new .CATPart Document failed
//  05 - adding new document failed
//  06 - opening a CATPart document failed
//  07 - inserting existing CATPart document failed
//  08 - creating connector through idl interface failed
//  09 - creating connector through assembly services failed
//  10 - No constraint created
//
//  11 - Saving documents failed
//
//  12 - Deleting the session failed
//
//
// use: CAAAuiCreateCstOnParts (PATH)\bishop.CATPart (OUTPUTPATH)
//
//============================================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATLib.h"
#include "CATUnicodeString.h" 
#include "CATLISTV_CATBaseUnknown.h"

// ObjectModelerBase Framework
#include "CATSession.h"
#include "CATDocumentServices.h"   // to open and close document
#include "CATSessionServices.h"    // to open and close session
#include "CATIDocRoots.h"          // to identify the root of a document
#include "CATDocument.h"           // to work with documents
#include "CATInit.h"
#include "CATILinkableObject.h"
 
// MecModInterfaces Framework 
#include "CATConstraintType.h"     // constraint type definitions
#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"

// CATAssemblyInterfaces Framework
#include "CATAsmConstraintServices.h"  // constraint creation
#include "CATAsmConnectorServices.h"   // connector creation

// ObjectSpecModeler Framework
#include "CATIConnector.h" 
#include "CATIDescendants.h" // Added by FRG on 07/30/2002
#include "CATISpecObject.h"  
#include "CATLISTV_CATISpecObject.h"

// ProductStructure Framework
#include "CATIProduct.h"

// ConstraintModelerInterfaces Framework
#include "CATICst.h"

//-----------------------------------------------------------------

int main (int iArgc, char** iArgv ) 
{

  int returnCode = 0;

  printf( "iArgC = %d\n", iArgc );
  if(3 != iArgc)
  {
    printf( "creation of session or document failed\n" );
    return 2; // wrong number of arguments
  }

  printf( "0 - opening a Session\n" );
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session("CAA2_Sample_Session",pSession );
  
  CATDocument *pDoc = NULL;
  rc = CATDocumentServices::New("Product",pDoc);

  if ( FAILED(rc) || (NULL==pDoc) ) 
  {
    printf( "creation of session or document failed\n" );
    returnCode = 2;
  }
  else
  {
    printf( "     -> done\n" );
    
    /* --------------------------------------------------------- */
    /*  1. Search for the document's root product (RootProduct)  */
    /* --------------------------------------------------------- */
    
    printf( "1 - searching the root product\n" );
    CATIProduct *piProductOnRoot = NULL;
    CATIDocRoots *piDocRootsOnDoc = NULL;
    rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &piDocRootsOnDoc);
    if ( SUCCEEDED(rc) ) 
    {
      CATListValCATBaseUnknown_var *pRootProducts=piDocRootsOnDoc->GiveDocRoots();
      if (NULL != pRootProducts)
      {
        if (pRootProducts->Size())
        {  
          CATBaseUnknown_var hBU = (*pRootProducts)[1];
          if ( NULL_var != hBU )
          {
            hBU->QueryInterface(IID_CATIProduct,(void**) &piProductOnRoot);
          }
        }
        delete pRootProducts;
        pRootProducts = NULL;
      }
      
      piDocRootsOnDoc->Release();
      piDocRootsOnDoc=NULL;
    }
    
    if ( NULL == piProductOnRoot ) 
    {
      printf( "access to the root product failed\n" );
      returnCode = 3;
    }
    else
    {
      printf( "     -> done\n" );
      
      /* ----------------------------------------------------- */
      /*  2. Adds a new CATPart under the root product.        */
      /* ----------------------------------------------------- */
      
      printf( "2. Adding a new CATPart under the root product\n" );
      
      // creates a new part document
      CATDocument *pPartDoc1 = NULL;
      rc = CATDocumentServices::New( "Part", pPartDoc1 );
      if ( FAILED(rc) || NULL == pPartDoc1 ) 
      {
        printf( "creating new CATPart Document failed\n" );
        returnCode = 4;
      }
      else
      {
        CATIProduct *piInstanceProd1 = NULL;
        CATUnicodeString partName = "Part1";

        // imports the new document in root product
        CATIDocRoots *piDocRootsOnNewDoc = NULL;
        rc = pPartDoc1->QueryInterface(IID_CATIDocRoots, (void**) &piDocRootsOnNewDoc);
        if ( SUCCEEDED( rc ) )
        {		
          rc = E_FAIL;
          CATListValCATBaseUnknown_var * pRootProducts = piDocRootsOnNewDoc->GiveDocRoots();
          if (NULL != pRootProducts)
          {
            if (pRootProducts->Size() > 0)
            {  
              CATIProduct_var spRootProduct = (*pRootProducts)[1];
              if (NULL_var != spRootProduct)
              {
                spRootProduct->SetPartNumber(partName);
                
                CATIProduct_var spProduct = piProductOnRoot->AddProduct(spRootProduct);
                if (NULL_var !=  spProduct )
                {
                  rc = spProduct->QueryInterface(IID_CATIProduct, 
                    (void**) &piInstanceProd1);
                }
              }
            }
            delete pRootProducts;
            pRootProducts = NULL;
          }
          piDocRootsOnNewDoc->Release();
          piDocRootsOnNewDoc=NULL;
        }

        if ( NULL == piInstanceProd1 ) 
        {
          printf( "adding new document failed\n" );
          returnCode = 5;
        }
        else
        {
          printf( "     -> done\n" );
          
          /* --------------------------------------------------------- */
          /* 	3. Imports an existing CATPart under the root product.   */
          /* --------------------------------------------------------- */
          printf( "Importing an existing CATPart under the root product\n" );
          CATDocument *pDocPart2 = NULL;
          CATIProduct *piInstanceProd2 = NULL;
          
          // load the given CATPart
          rc = CATDocumentServices::OpenDocument(iArgv[1],pDocPart2);
          if ( FAILED(rc) || (NULL==pDocPart2) ) 
          {
            printf( "opening a CATPart document failed\n" );
            returnCode = 6;
          }
          else
          {
            // insert the given part in root product
            CATIDocRoots * piDocRootsOnOpenedDoc = NULL;
            rc = pDocPart2->QueryInterface(IID_CATIDocRoots, (void**) &piDocRootsOnOpenedDoc);
            if ( SUCCEEDED(rc) )
            {
              rc = E_FAIL;
              CATListValCATBaseUnknown_var *pRootProducts = piDocRootsOnOpenedDoc->GiveDocRoots();
              if ( NULL != pRootProducts)
              {
                if (pRootProducts->Size() > 0)
                {  
                  CATIProduct_var spRootProduct = (*pRootProducts)[1];
                  if (NULL_var != spRootProduct)
                  {
                    CATIProduct_var spProduct = piProductOnRoot->AddProduct(spRootProduct);
                    if ( NULL_var != spProduct )
                    {
                      rc = spProduct->QueryInterface(IID_CATIProduct, 
                        (void**) &piInstanceProd2);
                    }
                  }
                }
                delete pRootProducts;
                pRootProducts = NULL;
              }
              piDocRootsOnOpenedDoc->Release();
              piDocRootsOnOpenedDoc=NULL;
            }
            
            if ( NULL == piInstanceProd2 ) 
            {
              printf( "inserting existing CATPart document failed\n" );
              returnCode = 7;
            }
            else
            {
              printf( "     -> done\n" );
              
              /*-------------------------------------------------------------*/
              /*  4. creation of a connector on a reference plane yz
              /*-------------------------------------------------------------*/      
              
              printf( "creating a connector on a reference plane yz\n" );
              CATIConnector *pConnector1 = NULL;

              CATILinkableObject_var spLO_InstProd1;      
              if( SUCCEEDED(piInstanceProd1->GetShapeRep(spLO_InstProd1, "Default", CATPrd3D, TRUE)) )
              {
                CATIPrtPart *pPart_InstProd1 = NULL;
                rc = spLO_InstProd1->QueryInterface(IID_CATIPrtPart, (void **) &pPart_InstProd1);
                if( SUCCEEDED(rc) )
                {
                  CATListValCATISpecObject_var spListRefPlanes = pPart_InstProd1->GetReferencePlanes();
                  // defines the yz plane as the first sketch plane
                  CATILinkableObject *pLO_YZPlane = NULL;
                  if( spListRefPlanes.Size() )
                  {
                    CATISpecObject_var spYZPlane = spListRefPlanes[1];
                    if( spYZPlane != NULL_var )
                    {
                      rc = spYZPlane->QueryInterface(IID_CATILinkableObject ,(void **) &pLO_YZPlane);
                      if ( SUCCEEDED(rc) ) 
                      {
                        int  iCreation = 0;
                        ::GetProductConnector(pLO_YZPlane,
                          piInstanceProd1,
                          piProductOnRoot,
                          0,
                          pConnector1,
                          iCreation);
                        
                        pLO_YZPlane->Release();
                        pLO_YZPlane = NULL;
                      }
                    }
                  }

                  pPart_InstProd1->Release();
                  pPart_InstProd1 = NULL;
                }
              }
              
              if ( NULL == pConnector1 ) 
              {
                printf( "creating connector on reference plane failed\n" );
                returnCode = 8;
              }
              else
              {
                printf( "     -> done\n" );
                
                /*-------------------------------------------------------------*/
                /*  5. creation of a connector on a face
                /*-------------------------------------------------------------*/      
                printf( "creating a connector on a face\n" );
                CATIConnector * pConnector2 = NULL;

                CATInit * pInitOnPartDoc = NULL;
                if ( SUCCEEDED( pDocPart2->QueryInterface( IID_CATInit, (void **) & pInitOnPartDoc ) ) )
                {
                  CATIPrtContainer * pSpecContainer = NULL;
                  pSpecContainer = (CATIPrtContainer*) pInitOnPartDoc->GetRootContainer("CATIPrtContainer");
                  if ( pSpecContainer )    
                  {
                    CATIPrtPart_var spPart = pSpecContainer->GetPart();
                    if ( !! spPart )
                    {
                      CATIDescendants *pPartAsDescendant = 0;
                      if( SUCCEEDED(spPart->QueryInterface(IID_CATIDescendants, (void**)&pPartAsDescendant)) )
                      {
                        CATLISTV(CATISpecObject_var) Planes;
                        pPartAsDescendant->GetAllChildren("CATPlane", Planes);  
                        if (Planes.Size())
                        {
                          CATILinkableObject_var geometry = Planes[1];
                          if ( NULL_var != geometry )
                          {
                            int  iCreation = 0;
                            ::GetProductConnector((CATILinkableObject *)geometry,
                              piInstanceProd2,
                              piProductOnRoot,
                              0,
                              pConnector2,
                              iCreation);
                          }
                        }
                        pPartAsDescendant->Release();
                        pPartAsDescendant = NULL;
                      }      
                    }
                    pSpecContainer->Release();
                    pSpecContainer = NULL;
                  }
                  
                  pInitOnPartDoc->Release();
                  pInitOnPartDoc = NULL;
                }
                
                if ( NULL == pConnector2 )
                {
                  printf( "creating connector through idl interface failed\n" );
                  returnCode = 9;
                }
                else
                {
                  printf( "     -> done\n" );

                  //---------------------------
                  // 6 - Creating a constraint
                  //---------------------------
                  
                  printf( "Creating a constraint\n" );
                  CATICst *pCst = NULL;

                  CATLISTV (CATBaseUnknown_var) ConnectorList;
                  ConnectorList.Append(pConnector1);
                  ConnectorList.Append(pConnector2);
                  
                  rc = CreateConstraint(catCstTypeParallelism,ConnectorList,NULL,piProductOnRoot,&pCst);
                  
                  if ( S_OK != rc )
                  {
                    printf( " ERROR: no constraint created\n" );
                    returnCode = 10; 
                  }
                  else
                  {
                    printf( "Constraint successfully created\n" );
                    printf( "     -> done\n" );
                    
                    //---------------------------
                    // 7 - Saving all documents
                    //---------------------------
                    
                    printf( "Saving all documents\n" );
                    CATUnicodeString outputpath = iArgv[2];
                    CATUnicodeString outputname1 = outputpath;
                    outputname1.Append( "bishop.CATPart" );
                    rc = CATDocumentServices::SaveAs(*pDocPart2,outputname1);
                    if ( FAILED(rc) ) 
                    {
                      printf( "Saving documents failed\n" );
                      returnCode = 11;
                    }
                    else
                    {
                      // And by the way, the new CATPart added under the product.
                      CATUnicodeString outputname2 = outputpath;
                      outputname2.Append( "Part1.CATPart" );
                      rc = CATDocumentServices::SaveAs(*pPartDoc1, outputname2 );
                      if ( FAILED(rc) ) 
                      {
                        printf( "Saving documents failed\n" );
                        returnCode = 11;
                      }  
                      else
                      {
                        // now we can save the CATProduct.
                        CATUnicodeString outputname3 = outputpath;
                        outputname3.Append( "CstOnParts.CATProduct" );
                        rc = CATDocumentServices::SaveAs(*pDoc, outputname3 );
                        if ( FAILED(rc) ) 
                        {
                          printf( "Saving documents failed\n" );
                          returnCode = 11;
                        }
                        else
                        {
                          printf( "     -> done\n" );
                        }
                      }
                    }

                    pCst->Release();
                    pCst = NULL;
                  } // if pCst
                  
                  pConnector2->Release(); // pConnector2 no more used
                  pConnector2 = NULL;
                } // if pConnector2
                
                pConnector1->Release();// pConnector1 no more used
                pConnector1 = NULL;
              } // if pConnector1
              
              piInstanceProd2->Release(); // piInstanceProd2 no more used
              piInstanceProd2 = NULL;
            } // if piInstanceProd2
          }
              
          piInstanceProd1->Release(); // piInstanceProd1 no more used
          piInstanceProd1 = NULL;
        } // if piInstanceProd1
      }
          
      piProductOnRoot->Release(); // piProductOnRoot no more used
      piProductOnRoot = NULL;
    } // if piProductOnRoot
    
    /* ----------------------------------------- */
    /*   ends the session                        */
    /* ----------------------------------------- */
    
    printf( "ending the session\n" );
    // remove opened document
    rc = CATDocumentServices::Remove (*pDoc);
    if ( FAILED(rc) ) 
    {
      printf( "Deleting the session failed\n" );
      returnCode = 12;
    }
  }
  
  // delete the session, removes the opened documents also.
  // never forget to delete a created session after usage.
  rc = ::Delete_Session("CAA2_Sample_Session");
  printf( "     -> done\n" );
  return returnCode;
}  
