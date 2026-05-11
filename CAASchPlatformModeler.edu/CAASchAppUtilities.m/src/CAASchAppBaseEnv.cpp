/**
 * @fullreview VSO BCY 03:01:16
 * @quickreview vso jsk 08:02:07
 */
// COPYRIGHT DASSAULT SYSTEMES 2001+
//=============================================================================
//
//
#include <iostream.h>

// ObjectModelerBase and System
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATIProperty.h"
#include "CATDocumentServices.h"
#include "CATUnicodeString.h"
#include "CATSession.h"
#include "CATTime.h"
#include "CATLib.h"
#include "CATInit.h"
#include "CATILinkableObject.h"
#include "LifeCycleObject.h"
#include "CATSessionServices.h"

// ObjectSpecsModeler
#include "CATISpecAttrAccess.h"
#include "CATISpecAttrKey.h"
#include "CATISpecAttribute.h"

// This framework
#include "CAASchAppBaseEnv.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppBaseServices.h"

// DraftingInterfaces
#include "CATIDftDocumentServices.h"
#include "CATIDrawing.h"
#include "CATISheet.h"


// CATSchPlatformInterfaces
#include "CATSchGeneralEnum.h"
#include "CATISchInternalFlow.h"
#include "CATISchAppRoute.h"
#include "CATISchAppConnectable.h"
#include "CATISchAppConnector.h"
#include "CATISchCompFlow.h"
#include "CATISchRoute.h"
#include "CATISchGRRRoute.h"
#include "CATISchBaseFactory.h"
#include "CATISchGRRFactory.h"
#include "CATISchComponent.h"

#include "CATISchSession.h"

#include "CATSchListServices.h"
#include "CATSchGeneralEnum.h"

// System 
#include "IUnknown.h"
#include "CATIUnknownList.h"
#include "CATErrorDef.h"
#include "CATString.h"

//=============================================================================
//  Constructor
//=============================================================================
CAASchAppBaseEnv::CAASchAppBaseEnv() 
                 :_pSchDoc (NULL),
                  _pSession (NULL),
                  _pSessionIdent(NULL),
                  _piSchRootCont (NULL),
                  _spSchExtCont (NULL_var),
                  _spSchAppObjCont (NULL_var)
{
  cout << "CAASchAppBaseEnv::CAASchAppBaseEnv()" << endl;
};

//=============================================================================
//  Destructor
//=============================================================================
CAASchAppBaseEnv::~CAASchAppBaseEnv()
{
  cout << "CAASchAppBaseEnv::~CAASchAppBaseEnv()" << endl;
  CleanupSession();
  cout << "CAASchAppBaseEnv::Done CleanupSession" << endl;
}

//=============================================================================
//  CATProduct Environment
//=============================================================================
void CAASchAppBaseEnv::CreateCATProductEnv(const char *iFileNameToBeLoaded,
  boolean iBMode2D)
{
  cout <<"============================================================"<< endl;
  cout <<"===   CAASchAppBaseEnv::CreateCATProductEnv              ==="<< endl;
  cout <<"============================================================"<< endl;

  CleanupSession();

	//---------------------------------------------------------------------------
  // Create Session
  //---------------------------------------------------------------------------
  _pSessionIdent = "Session DSA CAASchAppBaseEnv CATProduct";
  ::Create_Session (_pSessionIdent, _pSession);
  if (NULL == _pSession)
  {
     cout << "Cannot create session" << endl;
     return;
  }
  cout << "Create_Session successfully" <<endl;  

  CATInit_var spInit = NULL_var;
  //---------------------------------------------------------------------------
  // Load document if any
  //---------------------------------------------------------------------------	
  if (NULL != iFileNameToBeLoaded)
  {
     cout << "Loading ... " << iFileNameToBeLoaded << endl;
	 if (SUCCEEDED (CATDocumentServices::OpenDocument (iFileNameToBeLoaded,_pSchDoc)))
	 {
	    spInit = _pSchDoc;
		cout << "Loading successfully ..." << endl;
	 }
	 else
	 {
		cout << "*** Loading failed ..." << endl;
	 }
  }
  else
  {
     //------------------------------------------------------------------------
     // Create CATProduct document 2D
     //------------------------------------------------------------------------	
     if (iBMode2D)
	 {
        cout << "Creating Product document with Schematic data ... " << endl;
        boolean BInteractiveSession = FALSE;

        CATISchSession* piSchSession = NULL;
        if ( SUCCEEDED( _pSession->QueryInterface (IID_CATISchSession,(void**)&piSchSession) ) )
        {
          piSchSession->CreateDocument (NULL,BInteractiveSession, &_pSchDoc);
          piSchSession->Release(); piSchSession = NULL;
        }

	 }
     //------------------------------------------------------------------------
     // Create CATProduct document 3D
     //------------------------------------------------------------------------	
     else
	 {
        cout << "Creating regular 3D Product document ... " << endl;
        CATDocumentServices::New ("CATProduct",_pSchDoc);
	 }
	 if (NULL != _pSchDoc) 
	 {
		 spInit = _pSchDoc;
     spInit->Init(TRUE);	
	 }
  }

  //---------------------------------------------------------------------------
  // Get root container
  //---------------------------------------------------------------------------
  if (NULL_var != spInit)
  {
     cout << "Get RootContainer" << endl;
     _piSchRootCont = (CATIContainer *)spInit->GetRootContainer (CATIContainer::ClassName());
     GetSubContainers();
  }

  if (NULL_var != _spSchExtCont)
  {
     cout << "found _spSchExtCont" << endl;
  }
  else
  {
     cout << "cannot find _spSchExtCont" << endl;
  }
}


//=============================================================================
//  Get Document
//=============================================================================
CATDocument * CAASchAppBaseEnv::GetDocument ()
{
  return (_pSchDoc);
}

//=============================================================================
//  Get Root Container
//=============================================================================
CATIContainer_var CAASchAppBaseEnv::GetRootContainer ()
{
  return (_piSchRootCont);
}

//=============================================================================
//  Get Schematic Extension Object Container
//=============================================================================
CATIContainer_var CAASchAppBaseEnv::GetSchExtContainer ()
{
  return (_spSchExtCont);
}

//=============================================================================
//  Get Application Object Container
//=============================================================================
CATIContainer_var CAASchAppBaseEnv::GetAppObjContainer ()
{
  return (_spSchAppObjCont);
}

//=============================================================================
//  Save Document
//=============================================================================
void CAASchAppBaseEnv::SaveDocument (const char *iFileName)
{
	//---------------------------------------------------------------------------
  // Save Document
	//---------------------------------------------------------------------------
  if (NULL != _pSchDoc)
  {
     HRESULT RC = CATDocumentServices::SaveAs ( *_pSchDoc, iFileName);
     cout << "Document : " << iFileName << " saved !!!" << endl;
  }
  else
  {
     cout << "Document : " << iFileName << " NOT saved !!!" << endl;
     cout << "pointer to document is NULL, perhaps, it has been released !!!"
          <<endl;
  }
}


//=============================================================================
//  Set current sheet to a non-detail sheet.
//=============================================================================
void CAASchAppBaseEnv::SetMainSheet ()
{
  HRESULT rc = S_OK;
  if (NULL == _pSchDoc)
  {
    cout << "CAASchAppBaseEnv::Cannot find DOCUMENT " << endl;
    return;
  }
  CATTry 
	{
    CATIDftDocumentServices *piService = NULL;
    rc = _pSchDoc->QueryInterface (
         IID_CATIDftDocumentServices,(void**)&piService);
    if (FAILED(rc)) return;

    CATIDrawing* piDrawing = NULL;
    rc = piService->GetDrawing (IID_CATIDrawing,(void**)&piDrawing);
    piService->Release(); piService = NULL;
    if (FAILED(rc)) return; 
    
    CATLISTV(CATISpecObject_var) LSheet = piDrawing->GetSheetList();
    int SizeOfLSheet = LSheet.Size();
    CATISheet_var spSheet;
    boolean BYes = FALSE;

    for (int iSheet = 1; iSheet <= SizeOfLSheet; iSheet++)
    {
       spSheet = LSheet[iSheet];
       spSheet->IsDetail(&BYes);
       if (BYes == FALSE)
       {
         piDrawing->SetCurrentSheet(spSheet);
         piDrawing->Release(); piDrawing = NULL;
         break;
       }
    }
  } // end CATTry

  CATCatch (CATError, error)
	{
    cout << "CAASchAppBaseEnv::SetMainSheet *** CATRethrow" 
         << endl;
	  CATRethrow;
	}	
  CATEndTry;
}


//=============================================================================
//  CleanupSession
//=============================================================================
void CAASchAppBaseEnv::CleanupSession ()
{
  cout << "CleanupSession ---" << endl;

  if (NULL != _piSchRootCont) 
  {
    _piSchRootCont->Release();
    _piSchRootCont = NULL;
  }

  if (NULL != _pSchDoc)
  {
	   LifeCycleObject_var spLifeCycle = _pSchDoc;
	   spLifeCycle->remove();
     cout << "document removed !!!!" << endl;
     _pSchDoc = NULL;
  }

  if (NULL != _pSession)
  {
     ::Delete_Session (_pSessionIdent);
     cout << "Session released !!!!" << endl ;
     _pSession = NULL;
  }

  _pSessionIdent = NULL;

}

//=============================================================================
//  GetSubContainers
//=============================================================================
void CAASchAppBaseEnv::GetSubContainers ()
{
  cout << "GetSubContainers ---" << endl;

	//---------------------------------------------------------------------------
  // Create/Get Schematic Extension container
  //---------------------------------------------------------------------------
  if (!_pSession) return;

  CATISchSession* piSchSession = NULL;
  if ( SUCCEEDED( _pSession->QueryInterface (IID_CATISchSession,
       (void**)&piSchSession) ) && piSchSession)
  {
     IUnknown* piUnk = NULL;
     if ( SUCCEEDED(piSchSession->GetSchExtContainer( _pSchDoc, &piUnk)) )
     {
       CATIContainer*  piContainer = NULL;
       if ( SUCCEEDED(piUnk->QueryInterface(IID_CATIContainer,(void**)&piContainer) ) )
       {
          _spSchExtCont = piContainer;
          piContainer->Release(); piContainer = NULL;
       }
       piUnk->Release(); piUnk = NULL;
     }
     piSchSession->Release(); piSchSession = NULL;
  }

  if (NULL_var != _spSchExtCont)
  {
     cout << "found _spSchExtCont" << endl;
  }
  else
  {
     cout << "cannot find _spSchExtCont" << endl;
  }

  _spSchAppObjCont = _piSchRootCont;

}
