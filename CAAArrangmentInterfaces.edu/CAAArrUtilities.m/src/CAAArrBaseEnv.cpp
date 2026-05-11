// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
//
// This framework
#include "CAAArrBaseEnv.h"

// ObjectModelerBase and System
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATDocumentServices.h"
#include "CATSessionServices.h"
#include "LifeCycleObject.h"
//#include "CATIDocRoots.h"
#include "CATInit.h"
#include "CATIUserId.h"
#include "CATIPspApplication.h"
#include <iostream.h>

//=============================================================================
//  Constructor
//=============================================================================
CAAArrBaseEnv::CAAArrBaseEnv() 
                 :_pDocument (NULL),
                  _pSession (NULL),
                  _pSessionIdent(NULL),
                  _piRootCont (NULL)
{
  cout << "CAAArrBaseEnv::CAAArrBaseEnv()" << endl;
};

//=============================================================================
//  Destructor
//=============================================================================
CAAArrBaseEnv::~CAAArrBaseEnv()
{
  cout << "CAAArrBaseEnv::~CAAArrBaseEnv()" << endl;
  CleanupSession();
  cout << "CAAArrBaseEnv::Done CleanupSession" << endl;
}

//=============================================================================
//  CATProduct Environment
//=============================================================================
void CAAArrBaseEnv::CreateCATProductEnv(const CATUnicodeString &iFileNameToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===   CAAArrBaseEnv::CreateCATProductEnv                 ==="<< endl;
  cout <<"============================================================"<< endl;

  CleanupSession();

  //---------------------------------------------------------------------------
  // Create Session
  //---------------------------------------------------------------------------
  _pSessionIdent = "Session DSA CAAArrBaseEnv CATProduct";
  HRESULT hrCreateSession = Create_Session (_pSessionIdent, _pSession);
  if ((NULL == _pSession) || (hrCreateSession != S_OK))
  {
     cout << "Cannot create session" << endl;
     return;
  }
  cout << "Create_Session successfully" <<endl;  

  //---------------------------------------------------------------------------
  // Load document if any
  //--------------------------------------------------------------------------- 
  CATInit_var spInit = NULL_var;
  if ( iFileNameToBeLoaded.GetLengthInChar() )
  {
     cout << "Loading ... " << iFileNameToBeLoaded.ConvertToChar() << endl;
     if (SUCCEEDED (CATDocumentServices::OpenDocument (iFileNameToBeLoaded,_pDocument)))
     {
        spInit = _pDocument;
        
        if(_pDocument)
          cout << "\n _pDocument is OK "<< endl;
        else
          cout << "\n _pDocument is KO "<< endl;
        
        cout << "Loading successfully ..." << endl;
     }
     else
     {
        cout << "*** Loading failed ..." << endl;
     }
  }

  //---------------------------------------------------------------------------
  // Get root container
  //--------------------------------------------------------------------------- 
  if (NULL_var != spInit)
  {
     cout << "Get RootContainer" << endl;
     _piRootCont = (CATIContainer *)spInit->GetRootContainer (CATIContainer::ClassName());
  }
}

//=============================================================================
//  Get Document
//=============================================================================
CATDocument * CAAArrBaseEnv::GetDocument ()
{
        if(_pDocument)
          cout << "\n GetDocument _pDocument is OK "<< endl;
        else
          cout << "\n GetDocument _pDocument is KO "<< endl;

  return (_pDocument);
}

//=============================================================================
//  Get Root Container
//=============================================================================
CATIContainer * CAAArrBaseEnv::GetRootContainer ()
{
  return (_piRootCont);
}

//=============================================================================
//  Initialize Spatial application
//=============================================================================
void CAAArrBaseEnv::ApplicationInit ()
{
  //------------------------------------------------------------------------
  // Create Spatial application object and initialize the application
  //------------------------------------------------------------------------
  CATObject *piObj = new CATObject("CATSpatial");
  if ( NULL != piObj )
  {
     CATIPspApplication *piPspApp = NULL;
     if ( SUCCEEDED(piObj->QueryInterface(IID_CATIPspApplication,(void **)&piPspApp)) && piPspApp )
     {
        if ( NULL != _piRootCont )
        {
           if ( SUCCEEDED(piPspApp->Initialization(_piRootCont)) )
              cout << "Spatial application initialized" << endl;
           else
              cout << "Spatial application initialization failed" << endl;
        }
        piPspApp->Release();
        piPspApp = NULL;
     }
     piObj->Release();
     piObj = NULL;
  }
}

//=============================================================================
//  Save Document
//=============================================================================
void CAAArrBaseEnv::SaveDocument (const CATUnicodeString &iFileName)
{
  if (NULL != _pDocument)
  {
     HRESULT RC = CATDocumentServices::SaveAs ( *_pDocument, iFileName);
     cout << "Document : " << iFileName.ConvertToChar() << " saved !!!" << endl;
  }
  else
  {
     cout << "Document : " << iFileName.ConvertToChar() << " NOT saved !!!" << endl;
     cout << "pointer to document is NULL, perhaps, it has been released !!!"
          <<endl;
  }
}

//=============================================================================
//  CleanupSession
//=============================================================================
void CAAArrBaseEnv::CleanupSession ()
{
  cout << "CleanupSession ---" << endl;

  if (NULL != _piRootCont) 
  {
    _piRootCont->Release();
    _piRootCont = NULL;
  }

  if (NULL != _pDocument)
  {
    LifeCycleObject_var spLifeCycle = _pDocument;
    spLifeCycle->remove();
    cout << "document removed !!!!" << endl;
    _pDocument = NULL;
  }

  if (NULL != _pSession)
  {
     Delete_Session (_pSessionIdent);
     cout << "Session released !!!!" << endl ;
     _pSession = NULL;
  }

  _pSessionIdent = NULL;
}
