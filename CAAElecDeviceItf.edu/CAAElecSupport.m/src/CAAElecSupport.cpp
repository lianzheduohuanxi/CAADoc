/**
 * @fullreview AYZ UOK 09:05:20
 * @error MISC Y
 * @error MISC Y
*/
/**
* @quickReview GK3 CVV 09:12:31 fix for MLK-440828
**/
// =================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ================================= 

//=============================================================================
//  Abstract of Use Case "CAAElecSupport":
//  ---------------------------------------
//
//  This Use Case illustrates how to use APIs on CATIElbSupport
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Opening the Session.
//
//  2. Opening the document depending on the case.
//
//  3. Retrieving the Root product of the opened document. 
// 
//  4. Initializing Electrical Environment 
//
//  5. Retrieving  all Supports under the Root Product 
//
//  6. Testing APIs on each support.
//
//  7. Epilogue:
//     . Removing the ducument and closing the session.
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session.
//  2 - ERROR in opening an existing document.
//  3 - ERROR in getting root product.
//  4 - ERROR in electrical environment initialization.
//  5 - ERROR if supports not found in assembly.
//  6 - ERROR if Case 1 and 2:GetNumberOfSections failed.
//  7 - ERROR if Case 1 and 2:ListSegments failed.
//  8 - ERROR if Case 1 and 2:SetSegmentPositions failed.
//  9 - ERROR if Case 1 and 2:SetSegmentPositions failed.
// 10 - ERROR if Case 1 and 2:Invalid Args - ListSegments failed.
// 11 - ERROR if Case 1 and 2:Invalid Args - SetSegmentPositions failed.
// 12 - ERROR if Case 3 and 4:ListSegments failed.
// 13 - ERROR if Case 3 and 4:ListSegments failed.
// 14 - ERROR if Case 5 and 6:ListSegments failed.
// 15 - ERROR if Case 7:ListSegments failed.
// 16 - ERROR in Case 7:ListSegments failed.
// 17 - ERROR in removing document.
// 18 - ERROR in closing session.
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  mkrun -c "CAAElecSupport input N" where the prefix "input" is the 
//  entire pathname of the directory in which the document for different cases is to be found
//  N is the number of the cases to be tested
//
//
//  You may reference the supplied CATProduct document called "Top.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic/CAAElecSupport directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic\CAAElecSupport directory. 
//
//
//=============================================================================

//system
#include "CATLib.h"
#include "CATUnicodeString.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATBaseUnknown.h"
#include "CATListOfDouble.h"

// C++ include ( result display )
#include <iostream.h>

// ObjectModelerBase interfaces
#include "CATSessionServices.h"    // managing session
#include "CATDocumentServices.h"   // managing documents in session
#include "CATDocument.h"           // manipulating documents
#include "CATIDocRoots.h"          // browsing root objects in documents
#include "CATSession.h"

// ProductStructure interfaces 
#include "CATIProduct.h"           // managing products  

// Electrical interfaces
#include "CATIEleDocServices.h"    // initializing electrical environement 
#include "CATIElbSupport.h"


int main (int argc, char * argv[] )
{ 
  //--------------------------------------------------------------------
  // 1. Prologue 
  //--------------------------------------------------------------------
  cout << endl << flush;
  cout << endl << flush;
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;

  // --- Creating the Session:  A session must always be created in a batch

  CATSession *pSession = NULL;

  char *sessionName = "CAA_ElbSupport_Session";
  HRESULT rc = ::Create_Session(sessionName,pSession);
  if ((SUCCEEDED(rc)) && (NULL != pSession))
  {
    cout << "> session created : " << sessionName <<endl << flush;
  }
  else
  {
    cout << "ERROR in creating session" << sessionName << endl << flush;
    return 1;
  }

  //Loop for all the cases-->
  CATUnicodeString sNum(argv[2]);
  int nbOfCases = -1;
  sNum.ConvertToNum(&nbOfCases);
  if((nbOfCases<1)|| (nbOfCases>6)) {cout<<"Invalid number of the Cases to be tested"<<endl; return -1;}

  const CATUnicodeString DocumentPath(argv[1]);
  CATUnicodeString ODT_SLASH = "\\";
  CATUnicodeString sRootPrdName = "Top.CATProduct";
  
  for( int iCase = 1; iCase <= nbOfCases; iCase++ )
  {
    CATUnicodeString sIndex;
    CATUnicodeString sTmpDocPath = DocumentPath;
    sIndex.BuildFromNum(iCase);
    sTmpDocPath = sTmpDocPath+sIndex+ODT_SLASH+sRootPrdName;


    // --- Opening an existing document 
    //     The input parameter to this sample program must contain 
    //     the entire path and name of the document that is to be opened.  

    //-------------------------------------------
    //Opening the document depending on the case.
    //--------------------------------------------

    CATDocument *pDoc = NULL; // pDoc is a pointer to the document 

    cout << "> open document :"<< sTmpDocPath.ConvertToChar() << endl << flush;
    rc = CATDocumentServices::OpenDocument(sTmpDocPath, pDoc);
    if (SUCCEEDED(rc) && (NULL != pDoc))
    {
      cout << "> document opened " << endl << flush;
    }
    else
    {
      cout << "ERROR in opening document" << endl << flush;
      return 2;
    }

    //---------------------------------------------------
    // --- Retrieving the root product of the opened document 
    //--------------------------------------------------

    CATIProduct* piRootProduct = NULL;// piRootProduct is a handle to document root product

    CATIDocRoots * pDocRoots = NULL;
    rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &pDocRoots);
    if (FAILED(rc)||(NULL==pDocRoots))
      return 3;

    CATListValCATBaseUnknown_var* pListRootProduct = pDocRoots->GiveDocRoots();
    pDocRoots->Release();
    pDocRoots=NULL;

    if ( (NULL != pListRootProduct) && (0 < pListRootProduct->Size()) )
    {  
      CATBaseUnknown_var spCBU ((*pListRootProduct)[1]);
      if (NULL_var != spCBU)
        rc = spCBU->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
      if (pListRootProduct) delete pListRootProduct;
      pListRootProduct = NULL;
      //
      if  (SUCCEEDED(rc) && (NULL != piRootProduct))
        cout << "> root product found in document " << endl << flush;
      else
      {
        cout << "ERROR : Root product not found in document " << endl << flush;
        return 3;
      }
    }

    //--------------------------------------------------------------------
    // 2. Initializing Electrical Environment 
    //--------------------------------------------------------------------

    CATIEleDocServices * piElecDocServices = NULL;

    rc = pDoc->QueryInterface(IID_CATIEleDocServices,(void**) &piElecDocServices );
    if ( (SUCCEEDED(rc)) && (NULL != piElecDocServices) )
    {
      rc = piElecDocServices->Initialize();
    }

    if (SUCCEEDED(rc) )
    {
      cout << "> electrical environment initialized " << endl << flush;
    }
    else
    {
      cout << "ERROR : electrical environment initialization failed " << endl << flush;
      return 4;
    }

    if ( NULL != piElecDocServices )
    {
      piElecDocServices->Release();
      piElecDocServices=NULL;
    }

    //--------------------------------------------------------------------
    // 3. Retrieving all the supports under the root product   
    //--------------------------------------------------------------------

    CATListValCATBaseUnknown_var* pListAll = NULL;
    CATListValCATBaseUnknown_var* pListSupports = NULL;
    pListSupports =  new CATListValCATBaseUnknown_var();
    
    pListAll = piRootProduct->GetAllChildren();

    piRootProduct -> Release();
    piRootProduct = NULL ;
    
    int allChildren = 0;

    if(NULL != pListAll)
      allChildren = pListAll->Size();

    for ( int m=1; m<=allChildren ; m++)
    {
      CATIElbSupport *pSupport = NULL;
      CATBaseUnknown_var hUnkSupport = ((*pListAll)[m]);
      if (NULL_var != hUnkSupport)
        rc = hUnkSupport->QueryInterface(IID_CATIElbSupport,(void**) &pSupport);
       if( (SUCCEEDED(rc)) && (NULL!= pSupport) && (NULL!=pListSupports) )
       {
         pListSupports->Append(hUnkSupport);
       }
       if(NULL != pSupport)
         pSupport->Release();
    }

    int NumberOfSupp = 0;
    if ((NULL!=pListSupports) && (0 < pListSupports->Size())) 
    {
      NumberOfSupp = pListSupports->Size();	
      cout << "> number of supports found in assembly : "<< NumberOfSupp << endl << flush;
    }
    else
    {
      cout << "ERROR : no supports found in assembly " << endl << flush;
      return 5;
    }

    //LOOP for each support
    for ( int i=1; i<=NumberOfSupp ; i++)
    {
      CATIElbSupport *pSupport = NULL;
      int NbSections=0;
      CATListValCATBaseUnknown_var *pListOfSegments = NULL;
      CATListOfDouble *pListOfSegmentU = NULL;
      CATListOfDouble *pListOfSegmentV = NULL;   
      CATListValCATBaseUnknown_var *pListOfSegments2 = NULL;
      CATListOfDouble *pListOfSegmentU2 = NULL;
      CATListOfDouble *pListOfSegmentV2 = NULL;
      CATListOfDouble *pListOfSegmentU3 = NULL;
      CATListOfDouble *pListOfSegmentV3 = NULL; 

      CATBaseUnknown_var hUnkSupport = ((*pListSupports)[i]); 

      if (NULL_var != hUnkSupport)
        rc = hUnkSupport->QueryInterface(IID_CATIElbSupport,(void**) &pSupport);
      
      //----------------------------------
      //Testing APIs on each support.
      //----------------------------------

      if (SUCCEEDED(rc) && (NULL!= pSupport))
      {
        rc = pSupport->GetNumberOfSections(NbSections);
        if(SUCCEEDED(rc) && (((1 == i%2)&&(1 == NbSections))||((0 == i%2)&&(2 == NbSections))))
          cout << "GetNumberOfSections successful. " << endl << flush;
        else
        {
          cout << "ERROR : GetNumberOfSections failed. " << endl << flush;
          return 6;
        }

        if((1==iCase)||(2==iCase))
        {
          rc = pSupport->ListSegments(&pListOfSegments,1,&pListOfSegmentU,&pListOfSegmentV);
          if(SUCCEEDED(rc) && ((1 == pListOfSegments->Size())))
            cout << "ListSegments successful. " << endl << flush;
          else
          {
            cout << "ERROR : ListSegments failed. " << endl << flush;
            return 7;
          }

          pListOfSegmentU3 = new CATListOfDouble;
          pListOfSegmentV3 = new CATListOfDouble;
          pListOfSegmentU3->Append(0.20);
          pListOfSegmentV3->Append(0.30);

          rc = pSupport->SetSegmentPositions(pListOfSegments,pListOfSegmentU3,pListOfSegmentV3,1);
          if(SUCCEEDED(rc))
            cout << "SetSegmentPositions successful. " << endl << flush;
          else
          {
            cout << "ERROR : SetSegmentPositions failed. " << endl << flush;
            return 8;
          }

          rc = pSupport->ListSegments(&pListOfSegments2,1,&pListOfSegmentU2,&pListOfSegmentV2);
          if((SUCCEEDED(rc)) && (0.20==(*pListOfSegmentU2)[1]) && (0.30==(*pListOfSegmentV2)[1]))
            cout << "SetSegmentPositions successful. " << endl << flush;
          else
          {
            cout << "ERROR : SetSegmentPositions failed. " << endl << flush;
            return 9;
          }

          if((1==iCase)&&(1==i))
          {
            CATListValCATBaseUnknown_var *pListOfSegments1 = NULL;
            CATListOfDouble *pListOfSegmentU1 = NULL;
            CATListOfDouble *pListOfSegmentV1 = NULL; 

            rc = pSupport->ListSegments(&pListOfSegments1,2,&pListOfSegmentU1,&pListOfSegmentV1);
            //GK3 start 09:12:31 - fix for  MLK-440828 
            if ( NULL != pListOfSegments1 )
            {
              delete pListOfSegments1;
              pListOfSegments1 = NULL;
            }
            if ( NULL != pListOfSegmentU1 )
            {
              delete pListOfSegmentU1;
              pListOfSegmentU1 = NULL;
            }
            if ( NULL != pListOfSegmentV1 )
            {
              delete pListOfSegmentV1;
              pListOfSegmentV1 = NULL;
            }
            //GK3 end 09:12:31
            if(E_INVALIDARG == rc)
              cout << "Invalid Arguments.ListSegments successful. " << endl << flush;
            else
            {
              cout << "ERROR : ListSegments failed. " << endl << flush;
              return 10;
            }

            rc = pSupport->SetSegmentPositions(pListOfSegments,pListOfSegmentU3,pListOfSegmentV3,2);
            if(E_INVALIDARG == rc)
              cout << "Invalid Arguments.SetSegmentPositions successful. " << endl << flush;
            else
            {
              cout << "ERROR : SetSegmentPositions failed. " << endl << flush;
              return 11;
            }
          }
        }

        if((3==iCase)||(4==iCase))
        {
          if((1<=i)&&(i<=4))
          {
            rc = pSupport->ListSegments(&pListOfSegments,1,&pListOfSegmentU,&pListOfSegmentV);
            if(SUCCEEDED(rc) && ((1 == pListOfSegments->Size())))
              cout << "ListSegments successful. " << endl << flush;
            else
            {
              cout << "ERROR : ListSegments failed. " << endl << flush;
              return 12;
            }
          }

          if((5<=i)&&(i<=8))
          {
            rc = pSupport->ListSegments(&pListOfSegments,1,&pListOfSegmentU,&pListOfSegmentV);
            if( (S_OK == rc) && (NULL != pListOfSegments) && (0 == pListOfSegments->Size()))
              cout << "ListSegments successful.Zero Segments found in Support " << endl << flush;
            else if( (S_FALSE == rc) && (NULL != pListOfSegments) && (0 == pListOfSegments->Size()))
              cout << "ListSegments successful. Zero Segments found in Support." << endl << flush;
            else
            {
              cout << "ERROR : ListSegments failed. " << endl << flush;
              return 13;
            }
          }
        }

        if((5==iCase)||(6==iCase))
        {
          rc = pSupport->ListSegments(&pListOfSegments,1,&pListOfSegmentU,&pListOfSegmentV);
          if((S_OK == rc) && ((0 == pListOfSegments->Size())))
            cout << "ListSegments successful.Zero Segments found in Support. " << endl << flush;
          else if( (S_FALSE == rc) && (NULL != pListOfSegments) && (0 == pListOfSegments->Size()))
            cout << "ListSegments successful. Zero Segments found in Support." << endl << flush;
          else
          {
            cout << "ERROR : ListSegments failed. " << endl << flush;
            return 14;
          }
        }
      }
      // UOK NEW END
      
      delete pListOfSegments;
      delete pListOfSegmentU;
      delete pListOfSegmentV;
      delete pListOfSegments2;
      delete pListOfSegmentU2;
      delete pListOfSegmentV2;
      delete pListOfSegmentU3;
      delete pListOfSegmentV3;
      if(NULL != pSupport)
        pSupport->Release();

    }//LOOP for Support closes...

    delete pListSupports;
    delete pListAll;

    //--------------------------------------------------------------------
    // 6. Epilogue  
    //--------------------------------------------------------------------
    //------------------------------------
    // --- removing document from session 
    //------------------------------------

    rc = CATDocumentServices::Remove(*pDoc);
    if (SUCCEEDED(rc))
    {
      cout << "> document removed " << endl << flush;
    }
    else
    {
      cout << "ERROR in removing document" << endl << flush;
      return 17;
    }

  }//LOOP for cases closes

  //--------------------------
  // --- closing the session
  //-------------------------

  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 18;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;  
  //
  return (0);
}
