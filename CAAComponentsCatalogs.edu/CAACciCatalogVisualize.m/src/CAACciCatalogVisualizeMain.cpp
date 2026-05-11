// COPYRIGHT DASSAULT SYSTEMES  2002
//==========================================================================
//
//      Abstract: This use case browses the contents of a catalog document.
//
//
//
///  Steps :
//    0-    Checking input arguments
//    1-    Creating the session
//    2-    Retrieving the catalog path
//    3-    Opening the catalog 
//    4-    Retrieving the CATICatalogChapterFactory interface pointer 
//    5-    Retrieving and displaying the chapters
//    6-    Browsing recursively the catalog
//    7-    Closing the catalog
//    8-    Deleting the session
//
//
//==========================================================================
// How to execute :
//
//   CAACciCatalogVisualize  CatalogFilename
//
//   with      CatalogFilename   : complete filename of a catalog document
//                           
//   There is an example: $WSROOT/CAAComponentsCatalogs.edu/InputData/CAATool.catalog
//           
//   where WSROOT is the installation directory path
//
//   Return code :
//     0 successful execution
//     1 execution failed
// 
//==========================================================================

// Local Framework
#include "CAACciChapterBrowser.h"     // 

// ObjectModelerBase Framework
#include "CATSessionServices.h"  // Create, delete a session
#include "CATDocumentServices.h" // Open,close a document
#include "CATDocument.h"         // 
#include "CATInit.h"             // To retrieve the root container

// ObjectSpecsBase Framework
#include "CATIContainer.h" 

// ComponentsCatalogsInterfaces Framework
#include "CATICatalogChapterFactory.h"
#include "CATICatalogChapter.h"
#include "CATListValCATICatalogChapter_var.h"

// System Framework
#include "CATUnicodeString.h"

// Standard C++ library
#include "iostream.h"

int main(int iArgc, char *iArgv[])

{
  cout << "The CAACciCatalogVisualize main program begins ...."<< endl << endl;

  //----------------------------
  // 0- Checking input arguments
  //----------------------------
  if ( 2 != iArgc )
  {
     cout << endl;
     cout << "CAACciCatalogCreate CatalogFilename"<< endl;
     cout << "with : CatalogFilename : $WSROOT/CAAComponentsCatalogs.edu/InputData/CAATool.catalog"<< endl;
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

  //--------------------------------
  // 2- Retrieving the catalog path
  //--------------------------------
  CATUnicodeString CatalogPath = iArgv[1] ;

  //-------------------------
  // 3- Opening the catalog 
  //-------------------------
  CATDocument * pDocument = NULL ;
  rc = CATDocumentServices::OpenDocument(CatalogPath.CastToCharPtr(), pDocument);
  if ( FAILED(rc) ) 
  {
      cout <<" Error in opening the " << CatalogPath.CastToCharPtr() << endl; 
      return 1 ;
  }
  cout <<"   The " << CatalogPath.CastToCharPtr() << " is opened" << endl ;

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
  // 5- Retrieving and displaying the chapters
  //-------------------------------------------------
  cout << endl;
  CATListValCATICatalogChapter_var * ListOfChapter = NULL ;
  rc = pICatalogChapterFactory->ListChapters(ListOfChapter);
  if ( SUCCEEDED(rc) && (NULL != ListOfChapter) )
  {
     int SizeList = ListOfChapter->Size();
     cout <<"   The catalog contains " << SizeList << " chapter(s)" << endl;
     for ( int i=1 ; i <= SizeList ; i++)
     {
        CATICatalogChapter_var CurrentChapter = (*ListOfChapter)[i] ;
        if ( NULL_var != CurrentChapter )
        {
            CATUnicodeString ChapterName ;
            ChapterName = CurrentChapter->GetChapterName();

            cout <<"      " << ChapterName.CastToCharPtr() << endl;
        }
     }
     cout << endl;
     delete ListOfChapter ;
     ListOfChapter = NULL ;
  }
  cout << endl;
   
  //-------------------------------------------------
  // 6- Browsing recursively the catalog 
  //-------------------------------------------------
  CATICatalogChapter * pICatalogChapter = NULL ;
  rc = pICatalogChapterFactory->GetRootChapter(pICatalogChapter) ;
  if ( FAILED(rc) )
  {
    cout <<" Error in retrieving the root chapter" << endl;
    return 1;
  }

  CATUnicodeString TypeChapter = "Chapter" ;
  if ( TRUE == pICatalogChapter->KindIsEndChapter() )
  {
      TypeChapter = "Family" ;
  }

  rc = ::CAABrowsingChapter(pICatalogChapter,TypeChapter, 3); 
  if ( FAILED(rc) )
  {
    cout <<" Error in browing the root chapter" << endl;
    return 1;
  }
  cout << endl;

  pICatalogChapter->Release();
  pICatalogChapter = NULL ;   

  pICatalogChapterFactory->Release();
  pICatalogChapterFactory = NULL ;


  //-------------------------
  // 7- Closing the catalog
  //-------------------------
  rc = CATDocumentServices::Remove(*pDocument);
  if ( FAILED(rc) )
  {
      cout <<"Error in closing the document" << endl;
      return 1;
  }

  //-------------------------
  // 8- Deleting the session
  //-------------------------
  rc = ::Delete_Session(pSessionName);
  if (FAILED(rc))
  {
     cout << "Error in deleting session" << endl ;
     return 1;
  }

  cout << endl;
  cout << "The CAACciCatalogVisualize main program is ended."<< endl << endl;

  return 0;
}
