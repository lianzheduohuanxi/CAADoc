/**
 * @quickReview DVE 04:10:28
 */
/* -*-c++-*- */
//
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//============================================================================================
// Sample code for : Assembly
// Mission         : Create and manage sets of constraints.
//
// Type            : Batch program
// Inputs          : Product file
// Outputs         : Return code is O if program worked Ok, >0 otherwise
//
// Illustrates     : o Loading document in session            (1)
//                   o Creating the root set                  (2)
//                   o Add 3 new sets child                   (3)
//                   o Grouping some constraints in a set     (4)
//                   o Move a Set in another set              (5)
//                   o Delete of Set                          (6)
//                   o Remove of Set                          (7)
// Return codes :
//
//  10 - File could not be found or has problem  
//  11 - QI on CATIDocRoots failed
//  12 - Root product could not be found
//
//  22 - Root Set cannot be neither created nor got
//  23 - New Set child failed
//  24 - Move of the constraints failed
//  25 - Move of Set failed
//  26 - Delete of Set unavailable
//  27 - GetFatherSet failed
//  28 - RemoveSetChild failed
//
//
//
// use: CAAAsmCstSet xxx.CATProduct
// xxx.CATProduct need at least one component under the root product.
//
//============================================================================================

// System Framework
#include "CATBaseUnknown.h"
#include "CATLib.h"
#include "CATUnicodeString.h" 
#include "CATLISTV_CATBaseUnknown.h"

// CATAssemblyInterfaces Framework
#include "CATIAsmCstSetFeature.h"
#include "CATAsmConstraintSetServices.h"

// ObjectModelerBase Framework
#include "CATDocumentServices.h"   // to open and close document
#include "CATSession.h"
#include "CATSessionServices.h"    // to open and close session
#include "CATIDocRoots.h"          // to identify the root of a document
#include "LifeCycleObject.h"       // to delete objects
#include "CATDocument.h"           // to work with documents
#include "CATIAlias.h"

// ObjectSpecModeler Framework
#include "CATLISTV_CATISpecObject.h"
 

// ProductStructure Framework
#include "CATIProduct.h"

//-----------------------------------------------------------------

int main (int iArgc, char** iArgv ) 
{

  //--------------------------------
  // 1 - Loading document in session
  //--------------------------------

  printf(" Test CAAAsmCstSet \n");
  printf(" ============================= \n");

  // Checking arguments
  if(2 != iArgc)
    return 10; // wrong number of arguments
  
  // Opening a session  
  CATSession* pSession = NULL;
  HRESULT rc = Create_Session("Session_ASSEMBLY",pSession);
  printf( "Session Created\n");  

  // Opening a document
  CATDocument * pProductDocument = NULL;
  rc = CATDocumentServices::OpenDocument(iArgv[1],pProductDocument);

  if ( FAILED(rc) || (NULL == pProductDocument) )
  {
    printf( " ERROR: Document not found\n");
    return 11;
  }
  printf( "Document opened\n");
  
  // Searching the root product  
  CATIDocRoots *piDocRootsOnDoc = NULL;
  rc = pProductDocument->QueryInterface(IID_CATIDocRoots, (void**) &piDocRootsOnDoc);
  if ( FAILED(rc) )
  {
    printf( " ERROR: QI on CATIDocRoots failed\n");
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
    printf( " ERROR: No root product !!\n");
    return 12; 
  }
  printf("Root product found successfully\n");

  //---------------------------------------
  // 2 - Creating the root set
  //---------------------------------------
  CATIAsmCstSetFeature_var rootSet;
  
  // does the root set exist ? if not, create it
  HRESULT hr_root = CATAsmConstraintSetServices::GetRootSet( spRootProduct, rootSet, TRUE );
  
  if ( SUCCEEDED( hr_root ) && NULL_var != rootSet)
  {
    //---------------------------------------
    // 3 - Add 3 new sets child
    //---------------------------------------
    CATIAsmCstSetFeature_var iPreviousSet ;
    CATIAsmCstSetFeature_var newSet1;
    CATIAsmCstSetFeature_var newSet2;
    CATIAsmCstSetFeature_var newSet3;
    
    printf("Add a new set child :\n");
    HRESULT rc1 = CATAsmConstraintSetServices::AddNewSetChild(rootSet,newSet1,iPreviousSet);
    HRESULT rc2 = CATAsmConstraintSetServices::AddNewSetChild(rootSet,newSet2,iPreviousSet);
    iPreviousSet = newSet1;
    HRESULT rc3 = CATAsmConstraintSetServices::AddNewSetChild(rootSet,newSet3,iPreviousSet);
    
    if (SUCCEEDED(rc1)    && SUCCEEDED(rc2)    && SUCCEEDED(rc3) 
      && NULL_var!=newSet1 && NULL_var!=newSet2 && NULL_var!=newSet3)
    {
      printf( "3 new Sets child : ok \n"); 
      //--------------------------------------------
      // 4 - grouping some constraints in a set 
      //--------------------------------------------
      CATListValCATISpecObject_var listFromSet;
      CATLISTV(CATBaseUnknown_var) cstToGroup;
      
      CATLISTV(CATBaseUnknown_var) cstChildrenList;
      rc = rootSet->ListCstChildren(cstChildrenList);
      int nbCst = cstChildrenList.Size();
      for (int cc=1; cc<= nbCst; cc++)
      {
        CATIAlias_var alias(cstChildrenList[cc]);
        if (NULL_var != alias)
        {
          CATUnicodeString cstName = alias->GetAlias();
          printf("Constraints under set root : %d / %d %s\n", cc, nbCst, (const char*) cstName);
          
          //-- for example, we choice to group in the same set all "Coincidence.*" 
          if (cstName.SearchSubString("Coincidence") >0 )    // (-1 if not found)
          {
            cstToGroup.Append(cstChildrenList[cc]); 
            listFromSet.Append(rootSet);
          }
        }
      }
      
      // group in the last created set
      HRESULT rc2 = newSet3->MoveConstraintsFrom(listFromSet, cstToGroup);
      if (SUCCEEDED(rc2)) 
      {
        printf( "Move of the constraints : ok\n"); 
        
        //--------------------------------------------
        // 5 - Move a Set in another set 
        //--------------------------------------------
        // List of set child on set root
        CATListValCATISpecObject_var setChildrenList;
        rootSet->ListSetChildren(setChildrenList) ;
        int nbSet = setChildrenList.Size();
        
        //-- normaly we have the order:
        //   Set.1
        //   Set.3
        //   Set.2
        for (int s=1; s<= nbSet; s++)
        {
          CATIAlias_var alias(setChildrenList[s]);
          if (NULL_var != alias)
          {
            CATUnicodeString setName = alias->GetAlias();
            printf("Under Root:  set child %d / %d : %s\n", s, nbSet, (const char*) setName);
          }
        }
        
        //-- Move of Set.2 inside Set.1
        //                        fromSet, setToMove, previousSet
        rc = newSet1->MoveSetFrom(rootSet, newSet2  , NULL_var);
        if (SUCCEEDED(rc))
        {
          printf( "Move of Set.2 inside Set.1 : ok \n"); 
          
          //--------------------------------------------
          // 6 - Delete of Set.1 
          //--------------------------------------------
          LifeCycleObject_var lco_set(newSet1);
          if (NULL_var != lco_set)
          {
            lco_set->remove();
            lco_set = NULL_var;
            
            //--------------------------------------------
            // 7 - Remove of Set.3
            //--------------------------------------------
            // Who is the father of Set.3 ?
            CATIAsmCstSetFeature_var fatherSet;
            if ( SUCCEEDED(newSet3->GetFatherSet(fatherSet)) && NULL_var!=fatherSet )
            {
              printf( "GetFatherSet :ok\n");
              if ( SUCCEEDED(fatherSet->RemoveSetChild(newSet3)) && NULL_var!=fatherSet )
              {
                printf( "RemoveSetChild : ok\n");
                rc = 0;
                // end
              }
              else
              {
                printf( "RemoveSetChild FAILED\n");
                rc = 28;
              }
              
            }
            else
            {
              printf( "GetFatherSet FAILED\n");
              rc = 27;
            }
          }
          else
          {
            printf( "ERROR: Set not destroyed\n");
            rc = 26;
          }
          
        }
        else
        {
          printf( "Move of Set FAILED\n"); 
          rc = 25;
        } 
        
      }
      else
      {
        printf( "Move of the constraints FAILED\n"); 
        rc = 24;
      } 
      
    }
    else
    {
      printf( "New Set child FAILED !!\n"); 
      rc = 23;
    } 
    
  }
  else
  {
    printf( "Root Set UNAVAILABLE  !!\n"); 
    rc = 22;
  } 
    
  	  
  //-------------
  // - Exiting
  //------------

  // closing document
  CATDocumentServices::Remove(*pProductDocument);

  // closing session
  Delete_Session("Session_ASSEMBLY");
  printf( "Session cleaned succesfully\n");
  printf( "Normal End\n");
  printf( "Return Code = %d\n", rc);

  return rc;
}
