// COPYRIGHT DASSAULT SYSTEMES 2001
/**
* @quickreview F9G AYZ 16:06:16 Correction for IR-446343-V5-6R2017
*/
//=============================================================================
//  Abstract of Use Case "CAAEwrFilter":
//  ---------------------------------------
//
//  This Use Case illustrates how to navigate within electrical harness network  
//
//=============================================================================
//
//  Step by Step :
//  ------------
//
//  1. Prologue :  
//      . Creating the Session and Opening an Existing CATProduct Document.
//      . Retrieving the Root Product of the CATProduct Document.
//  2. Initializing Electrical Environment. 
//  3. Filter session with CRIT1 criteria. 
//  4. Saving new session with new name. 
//  5. Epilogue.
//      . Removing document from Session.
//      . Closing the Session
//
//  Return Errors:
//  -------------
//  1 - ERROR in creating the session
//  2 - ERROR in opening an existing document
//  3 - ERROR in getting root product
//  4 - ERROR in initializing electrical environment 
//  5 - ERROR in filtering session
//  6 - ERROR in saving the filtered session
//  10- ERROR in removing document  
//  11- ERROR in closing session  
//
//  Running the program:
//  -------------------
//  To run this program, you can use the command:
//  copy EwrFilter.dic (found in 'WS'/'OS'/resources/graphic/CAAEwrFilter) in 'WS'/'OS'/code/dictionary
//  mkrun -c "CAAEwrFilter <FullPathofCATProduct> <outputDirectoryPath>" where 
//  'FullPathofCATProduct' is the entire pathname of the directory in which the document is to be found + the name of the root document to open 
//  and 'outputDirectoryPath' is the directory path where the session will be saved. 
//  for example..
//    mkrun -c "CAAEwrFilter E:\AssemblyResource\Electrical\CAA_EwrFilterSample.CATProduct E:\temp"
//
//  You may reference the supplied CATProduct document called "CAA_EwrFilterSample.CATProduct" 
//  found in the 'WS'/'OS'/resources/graphic directory if under Unix.
//      In this case, 'OS' can be any of the following: 
//         aix_a for IBM
//         hpux_a for HP
//         irix_a for SGI
//         solaris_a for SUN
//  Under Windows, the path would indicate:  'WS'\intel_a\resources\graphic directory. 
//
//
//=============================================================================

// C++ includes ( only for result display )
// LRO 08:01:15
#include "CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATSession.h"
#include "CATUnicodeString.h"

#include <iostream.h>
#include "CATLib.h"

// CAA includes 

// ObjectModelerBase interfaces
#include "CATSessionServices.h"      // managing session
#include "CATDocumentServices.h"     // managing documents in session
#include "CATDocument.h"             // manipulating documents
#include "CATIDocRoots.h"            // browsing root objects in documents

// ProductStructure interfaces 
#include "CATIProduct.h"             // managing products  
#include "CATIAProduct.h"             // managing products  

// Electrical Wire interfaces
#include "CATIEwrFilter.h"        // browsing geometrical bundles

// Electrical interfaces
#include "CATIEleDocServices.h"      // initializing electrical environement 

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
  char *sessionName = "CAA_EhiFilter_Session";
  CATSession *pSession = NULL;
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
  
  // --- Opening an existing document 
  //     The input parameter to this sample program must contain 
  //     the entire path and name of the document that is to be opened.  
  
  CATDocument *pDoc = NULL;  // pDoc is a pointer to the document 

  cout << "> open document :"<< argv[1] << endl << flush;
  rc = CATDocumentServices::OpenDocument(CATUnicodeString(argv[1]), pDoc);
  
  CATLockDocument(*pDoc);

  if (SUCCEEDED(rc) && (NULL != pDoc))
  {
    cout << "> document opened " << endl << flush;
  }
  else
  {
    cout << "ERROR in opening document" << endl << flush;
    return 2;
  }
  
  // --- Retrieving root product of the opened document 
  
  CATIProduct* piRootProduct = NULL; // piRootProduct is a handle to document root product  
  //  
  CATIDocRoots * piDocRoots = NULL;
  rc = pDoc->QueryInterface(IID_CATIDocRoots,(void**) &piDocRoots);
  if ( FAILED(rc) || (NULL==piDocRoots) ) return 3;
  CATListValCATBaseUnknown_var* pListRootProduct = piDocRoots->GiveDocRoots();
  piDocRoots->Release();
  piDocRoots=NULL;
  
  if ( pListRootProduct && pListRootProduct->Size() )
  {  
    CATBaseUnknown_var hUnk = (*pListRootProduct)[1];

    if (NULL_var != hUnk) rc = hUnk->QueryInterface(IID_CATIProduct,(void**) &piRootProduct );
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
  if ( SUCCEEDED(rc) && piElecDocServices )
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
// 3. Filter session with CRIT1 criteria.  
//--------------------------------------------------------------------
  
  // --- Retrieving all products under root product  
  
  CATIEwrFilter * pFilter = NULL;
  rc = piRootProduct->QueryInterface(IID_CATIEwrFilter,(void**) &pFilter);;
  if ( (FAILED(rc)) || !pFilter ) 
  {
    cout << "ERROR : during filtering - interface pointer not found" << endl << flush;
    return 5;
  }
  
  CATListValCATUnicodeString * iListOfSystems = new CATListValCATUnicodeString();
  CATListValCATUnicodeString * iListOfCriteria = new CATListValCATUnicodeString();
  if (!iListOfSystems ||!iListOfCriteria)
 {
    cout << "ERROR : during filtering - out of memory" << endl << flush;
    return 5;
  }
 
	iListOfSystems -> Append(CATUnicodeString("SAMPLE")); // As provided implementation does not take system name into account
	iListOfCriteria -> Append(CATUnicodeString("CRIT1")); // As provided implementation recognizes CRIT1 as a criteria

  rc = pFilter->Filter(iListOfSystems, iListOfCriteria, ElecFilterBundleSegment|ElecFilterDevice);

  delete iListOfSystems;
  delete iListOfCriteria;

  CATIAProduct * pProduct = NULL;
  rc = piRootProduct->QueryInterface(IID_CATIAProduct,(void**) &pProduct);
  if ( (FAILED(rc)) || !pProduct ) 
  {
    cout << "ERROR : during filtering - interface pointer not found" << endl << flush;
    return 5;
  }

  rc = pProduct -> Update();
  pProduct -> Release();

  if (SUCCEEDED(rc) )
  {
    cout << "> Session filtered with CRIT1 as criteria" << endl << flush;
  }
  else
  {
    cout << "ERROR : during filtering - Filtering process FAILED" << endl << flush;
    return 5;
  }

  // releasing of unecessary interface pointer
  piRootProduct -> Release();
  piRootProduct = NULL ;

  pFilter-> Release();
  pFilter = NULL;

//--------------------------------------------------------------------
// 4. Saving session 
//--------------------------------------------------------------------
 const CATLISTP(CATDocument)* docList = NULL;
 docList = ListDocuments();
 int nbDoc=docList?docList->Size():0;
 CATUnicodeString Path = argv[2] ;
 CATUnicodeString sSLASH("\\");
#ifdef _WINDOWS_SOURCE
   sSLASH = "\\";
#else
  sSLASH = "/";
#endif
 
 for (int i=nbDoc; i>=1 && SUCCEEDED(rc); i--)
 {
   CATDocument * ptDocument = (*docList)[i];
   
   if (ptDocument && ptDocument->IsAKindOf("CATPart"))
   {
     CATUnicodeString DocName = ptDocument->DisplayName();
     int nSLASHlocation = DocName.SearchSubString(sSLASH,0,CATUnicodeString::CATSearchModeBackward);
     DocName.ReplaceSubString(0,nSLASHlocation,Path);

     rc = CATDocumentServices::SaveAs(*ptDocument, DocName); 
   }
   else if (ptDocument && ptDocument->IsAKindOf("CATProduct"))
   {
     CATUnicodeString DocName = ptDocument->DisplayName();
     int nSLASHlocation = DocName.SearchSubString(sSLASH,0,CATUnicodeString::CATSearchModeBackward);
     DocName.ReplaceSubString(0,nSLASHlocation,Path);

     rc = CATDocumentServices::SaveAs(*ptDocument, DocName); 
   }
 }
  if (SUCCEEDED(rc) )
  {
    cout << "> Session filtered and saved" << endl << flush;
  }
  else
  {
    cout << "ERROR : during save process" << endl << flush;
    return 6;
  }
  
//--------------------------------------------------------------------
// 5. Epilogue 
//--------------------------------------------------------------------

  // --- removing document from session 
  CATUnLockDocument(*pDoc);
  rc = CATDocumentServices::Remove(*pDoc);
  if (SUCCEEDED(rc))
  {
    cout << "> document removed " << endl << flush;
  }
  else
  {
    cout << "ERROR in removing document" << endl << flush;
    return 14;
  }

  // --- closing the session
  rc = ::Delete_Session(sessionName);
  if (SUCCEEDED(rc))
    cout << "> session deleted " << endl << flush;
  else
  {
    cout << "ERROR in deleting session" << endl << flush;
    return 15;
  }
  cout << "----------------------------------------------------------------" << endl << flush;
  cout << endl << flush;
  cout << endl << flush;
  
  //
  return (0);
}
