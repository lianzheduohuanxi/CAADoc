// COPYRIGHT DASSAULT SYSTEMES  2002
//==========================================================================
//
//      Abstract: This use case explains how to use the CATICatalogQuery and
//                CATICatalogQueryResult to filter descriptions.
//
//                The CAATool.catalog created with the CAACciCatalogCreate 
//                use case contains the Nuts chapter. This chapter contains
//                the SideNumber keyword. Each description of this chapter 
//                contains a valuation for this keyword. The use case makes
//                three queries:
//                   - a first, with valid query, with 1 answer
//                   - a second, with valid query without answer
//                   - a third, with unvalid query
//
//  Steps :
//
//    0- Checking input arguments
//    1 - Creating the session 
//    2- Retrieving the path
//    3- Opening the catalog 
//    4- Retrieving the CATICatalogChapterFactory interface pointer 
//       4-1 Retrieving the CATInit interface pointer on the document
//       4-2 Retrieving the Root container of the document
//       4-3 Retrieving the CATICatalogChapterFactory interface pointer
//    5- Filtering on the Nuts chapter
//       5-1 Retrieving the chapter
//       5-2 Retrieving its keyword liste
//       5-3 Verifying the SideNumber keyword existance
//       5-4  First filtering with the SideNumber keyword
//          5-4-1 Creating the expression 
//          5-4-2 Doing the query
//          5-4-3 Verifying the result
//          5-4-4 Releasing the pointer
//       5-5  Second Filtering with the SideNumber keyword
//          5-5-1 Creating the expression
//          5-5-2 Doing the query
//          5-5-3 Verifying the result
//          5-5-4 Releasing the pointer
//       5-6  Filtering with a bad keyword
//          5-6-1 Creating the expression
//          5-6-2 Doing the query
//       5-7  Releasing the pointers
//    6- Closing the document
//    7- Deleting the session
//
//==========================================================================
// How to execute :
//
//   CAACciCatalogQuery  InputPath 
//
//   with      InputPath   : path of the CAATool catalog 
//                           
//   you find it in: $WSROOT/CAAComponentsCatalogs.edu/InputData/CAATool.catalog
//           
//   where WSROOT is the installation directory path
//
// Return code :
//   0 successful execution
//   1 execution failed
// 
//==========================================================================

// ObjectModelerBase Framework
#include "CATSessionServices.h"  // Create, delete a session
#include "CATDocumentServices.h" // Open,close a document
#include "CATDocument.h"         // 
#include "CATInit.h"             // To retrieve the root container

// ObjectSpecsBase Framework
#include "CATIContainer.h"       // To handle the roor container

// ComponentsCatalogsInterfaces Framework
#include "CATICatalogChapterFactory.h"
#include "CATICatalogChapter.h"
#include "CATICatalogQuery.h"
#include "CATICatalogQueryResult.h"
#include "CATListValCATICatalogChapter_var.h"
#include "CATListValCATICatalogDescription_var.h"
#include "CATListValCATICatalogKeyword_var.h"
          
// System Framework
#include "CATUnicodeString.h"

// Standard C++ library
#include "iostream.h"

// To manage path names for both UNIX and Windows
#ifdef _WINDOWS_SOURCE
#define Slash     "\\"
#else
#define Slash     "/"
#endif

int main(int iArgc, char *iArgv[])

{
  cout << "The CAACciCatalogQuery main program begins ...."<< endl << endl;

  //----------------------------
  // 0- Checking input arguments
  //----------------------------
  if ( 2 != iArgc )
  {
     cout << endl;
     cout << "CAACciCatalogCreate InputPath "<< endl;
     cout << "with : InputPath : $WSROOT/CAAComponentsCatalogs.edu/InputData/"<< endl;
     cout << endl;
     return 1;
  }

  //------------------------------------------------------------------
  //1 - Creating the session
  // A session must always be created in a batch
  // environment.  Deleting the session at the end of the program is
  // also necessary.
  //------------------------------------------------------------------
  char * pSessionName = "CAA_CreationSample_Session";
  CATSession *pSession = NULL;
  HRESULT rc = ::Create_Session(pSessionName,pSession);

  if (FAILED(rc) )
  {
      cout << "Error in creating session" << endl ;
      return 1;
  }

  //-------------------------
  // 2- Retrieving the path
  //-------------------------
  CATUnicodeString CatalogPath = iArgv[1] ;
  CATUnicodeString Filename = CatalogPath + Slash + "CAATool.catalog";

  //-------------------------
  // 3- Opening the catalog 
  //-------------------------
  CATDocument * pDocument = NULL ;
  rc = CATDocumentServices::OpenDocument(Filename.CastToCharPtr(), pDocument);
  if ( FAILED(rc) ) 
  {
      cout <<" Error in opening the " << Filename.CastToCharPtr() << endl; 
      return 1 ;
  }
  cout <<"   The " << Filename.CastToCharPtr() << " is opened" << endl ;
  cout << endl;

  //--------------------------------------------------------------
  // 4- Retrieving the CATICatalogChapterFactory interface pointer 
  //--------------------------------------------------------------

  // 4-1 Retrieving the CATInit interface pointer on the document
  // ------------------------------------------------------------
  CATInit *pInitOnDoc = NULL ;
  rc = pDocument->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
  if ( FAILED(rc) )
  {
       cout << "Error in retrieving the CATInit interface"<< endl;
       return 1 ;
  }

  // 4-2 Retrieving the Root container of the document
  // -------------------------------------------------
  CATIContainer *pIRootCont = NULL ;
  pIRootCont = (CATIContainer*)pInitOnDoc->GetRootContainer("CATIContainer");
  
  pInitOnDoc->Release();
  pInitOnDoc = NULL ;
  
  if ( NULL == pIRootCont )
  {
     cout << "The root container is NULL"<< endl;
     return 1 ;
  }

  // 4-3 Retrieving the CATICatalogChapterFactory interface pointer
  // --------------------------------------------------------------
  CATICatalogChapterFactory * pICatalogChapterFactory = NULL ;        
  rc = pIRootCont->QueryInterface(IID_CATICatalogChapterFactory,
                                              (void **) &pICatalogChapterFactory);
  pIRootCont->Release();
  pIRootCont = NULL ;

  if ( FAILED(rc) )
  {
     cout << "Error in retrieving the CATICatalogChapterFactory interface"<< endl;
     return 1;
  }

  //-------------------------------------------------
  // 5- Filtering on the Nuts chapter
  //-------------------------------------------------
  
  // 5-1 Retrieving the chapter
  // ---------------------------
  CATUnicodeString NutsChapter = "Nuts" ;
  CATICatalogChapter * piNutsChapter = NULL ;
  rc = pICatalogChapterFactory->FindChapter(NutsChapter,piNutsChapter);

  if ( FAILED(rc) ) 
  {
      cout <<"Error in retrieving the Nuts chapter" << endl;
      return 1;
  }

  // No more need of this pointer
  pICatalogChapterFactory->Release();
  pICatalogChapterFactory = NULL ;

  // 5-2 Retrieving its keyword liste
  // --------------------------------
  CATListValCATICatalogKeyword_var *pListKeyword = NULL;
  rc = piNutsChapter->ListKeywords(pListKeyword);
  if ( FAILED(rc) || (NULL==pListKeyword) )
  {
      cout <<"Error in retrieving the keyword list of the Nuts chapter" << endl;
      return 1;
  }

  int SizeKWList = pListKeyword->Size();
  if ( SizeKWList != 1 )
  {
      cout <<"Error, the CAATool document is false" << endl;
      return 1 ;
  }
  
  // 5-3 Verifying the SideNumber keyword 
  // -----------------------------------
  CATICatalogKeyword_var Keyword = (*pListKeyword)[1];
  CATUnicodeString KeywordName = Keyword->GetKeywordName();
  CATUnicodeString SideNumberKW = "SideNumber";
  if ( SideNumberKW != KeywordName )
  {
      cout <<"Error, the CAATool document is false" << endl;
      return 1 ;
  }

  // No more need of this pointer
  delete pListKeyword ;
  pListKeyword = NULL ;
 
  // Retrieving the CATICatalogQuery interface pointer
  CATICatalogQuery * piCatalogQueryOnNutsChapter = NULL ;
  rc = piNutsChapter->QueryInterface(IID_CATICatalogQuery,
                                     (void **) &piCatalogQueryOnNutsChapter);
  if ( FAILED(rc) )
  {
      cout <<"Error in retrieving the CATICatalogQuery interface pointer" << endl;
      return 1 ;
  }
  
  // 5-4  First filtering with the SideNumber keyword
  // ------------------------------------------------

  // 5-4-1 Creating the expression 
  CATUnicodeString Expression = "(x.SideNumber==6)";
  CATICatalogQueryResult * piQueryResult = NULL;

  // 5-4-2 Doing the query
  rc = piCatalogQueryOnNutsChapter->Query(piQueryResult,Expression);
  if ( FAILED(rc) || ( NULL == piQueryResult) )
  {
      cout <<"Error with the Query:" << Expression.CastToCharPtr() << endl;
      return 1;
  }

  if ( 0 != piQueryResult->GetQueryMode() )
  {
      cout <<"Error with GetQueryMode:" << piQueryResult->GetQueryMode()<< endl;
      return 1;
  }
  
  // 5-4-3 Verifying the result

  int nbResult = piQueryResult->Size();
  if ( 1 != nbResult) 
  {
      cout <<" Error with the CAATool document" << endl;
      return 1;
  }

  CATListValCATICatalogDescription_var * pListDescription = NULL;
  rc = piQueryResult->AsAList(pListDescription);

  if ( FAILED(rc) || (NULL == pListDescription) )
  {
      cout <<" Error in retrieving the list of description" << endl;
      return 1;
  }
   
  int SizeDescList = pListDescription->Size();

  if ( 1 != SizeDescList )
  {
      cout <<" Error with the CAATool document" << endl;
      return 1;
  }
  cout<< "   There is 1 description with the " << Expression.CastToCharPtr() << " expression" << endl ;
  
  // 5-4-4 Displaying the description
  CATICatalogDescription_var Description = (*pListDescription)[1];
  if ( NULL_var == Description )
  {
      cout <<" Error the description is empty" << endl;
      return 1;
  }

  CATUnicodeString DescriptionName ;
  rc = Description->GetName(DescriptionName);
  if ( FAILED(rc) )
  {
      cout << " Error in retrieving the description's name " << endl;
      return 1;
  }

  cout<< "   The name of this description is=" << DescriptionName.CastToCharPtr() << endl;
  cout << endl;

  // 5-4-6 Releasing the pointer
  piQueryResult->Release();
  piQueryResult = NULL ;

  delete pListDescription;
  pListDescription = NULL ;
  
  // 5-5  Second Filtering with the SideNumber keyword
  // -------------------------------------------------
  
  // 5-5-1 Creating the expression 
  Expression = "(x.SideNumber<0)";

  // 5-5-2 Doing the query
  rc = piCatalogQueryOnNutsChapter->Query(piQueryResult, Expression);
  if ( FAILED(rc) || ( NULL == piQueryResult) )
  {
      cout <<"Error with the Query:" << Expression.CastToCharPtr() << endl;
      return 1;
  }

  // 5-5-3 Verifying the result
  nbResult = piQueryResult->Size();
  if ( 0 !=  nbResult )
  {
      cout <<" Error the number of description should be null" << endl;
      return 1 ;
  }

  rc = piQueryResult->AsAList(pListDescription);

  if ( SUCCEEDED(rc) || (NULL != pListDescription) )
  {
      cout <<" Error in the description list " << endl;
      return 1 ;
  }
  
  cout<< "   There is 0 description with the" << Expression.CastToCharPtr() << " expression" ;
  cout << endl << endl;

  // 5-5-4 Verifying the result
  piQueryResult->Release();
  piQueryResult = NULL ;

  // 5-6  Filtering with a bad keyword
  // -----------------------------------

  // 5-6-1 Creating the expression
  Expression = "(x.Number>=6)";
  
  // 5-6-2 Doing the query
  rc = piCatalogQueryOnNutsChapter->Query(piQueryResult, Expression);
  if ( SUCCEEDED(rc) )
  {
      cout <<"Error with the Query:" << Expression.CastToCharPtr() << endl;
      return 1;
  }

  cout<< "   There is 0 description with the" << Expression.CastToCharPtr() << " expression" ;
  cout<< endl;
  
  // 5-7  Releasing the pointer
  // ---------------------------
  piNutsChapter->Release();
  piNutsChapter = NULL ;

  piCatalogQueryOnNutsChapter->Release();
  piCatalogQueryOnNutsChapter = NULL ;

  //-------------------------
  // 6- Closing the document
  //-------------------------
  rc = CATDocumentServices::Remove(*pDocument);
  if ( FAILED(rc) )
  {
      cout <<"Error in closing the document" << endl;
      return 1;
  }

  //-------------------------
  // 7- Deleting the session
  //-------------------------
  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc))
  {
     cout << "Error in deleting session" << endl ;
     return 1;
  }

  cout << endl;
  cout << "The CAACciCatalogQuery main program is ended."<< endl << endl;

  return 0;
}
