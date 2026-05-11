// COPYRIGHT DASSAULT SYSTEMES  2001+
//=============================================================================
//
// CAASchAppSample3: 
//    
//=============================================================================
#include <iostream.h>

// This framework
#include "CAASchAppSample3.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppBaseServices.h"

// CATSchPlatformInterfaces
#include "CATISchBaseFactory.h"
#include "CATISchGRRFactory.h"
#include "CATISchRoute.h"
#include "CATISchGRRRoute.h"
#include "CATISchSession.h"
#include "CATSchListServices.h"
#include "CATISchAppObjectFactory2.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATIAlias.h"
#include "CATSession.h"

// System
#include "CAASchAppErrors.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"

// Drafting
#include "CATIDftDocumentServices.h"
#include "CATIDrawing.h"
#include "CATISheet.h"
#include "CATIView.h"
#include "CATI2DDetail.h"


//=============================================================================
//  Constructor
//=============================================================================
CAASchAppSample3::CAASchAppSample3() 
             :
              _pSchDoc (NULL),
              _piBaseFact (NULL),
              _piGRRFact (NULL),
              _piSchRoute1 (NULL),
              _piSchRoute2 (NULL),
              _piUKAppRoute1 (NULL),
              _piUKAppRoute2 (NULL),
              _piSpecSchRoute1 (NULL),
              _piSpecSchRoute2 (NULL),
              _piSchGRRRoute1 (NULL),
              _piSchGRRRoute2 (NULL),
              _piUK (NULL),
              _piLUK (NULL),
              _piSchAppObjFact (NULL)
{
  cout << "CAASchAppSample3::CAASchAppSample3()" << endl;
};

//=============================================================================
//  Destructor
//=============================================================================
CAASchAppSample3::~CAASchAppSample3()
{
  cout << "CAASchAppSample3::~CAASchAppSample3()" << endl;

  _pSchDoc = NULL;

  if ( NULL != _piBaseFact ) { _piBaseFact->Release(); _piBaseFact = NULL; }
  if ( NULL != _piGRRFact ) { _piGRRFact->Release(); _piGRRFact = NULL; }
  if ( NULL != _piSchRoute1 ) { _piSchRoute1->Release(); _piSchRoute1 = NULL; }
  if ( NULL != _piSchRoute2 ) { _piSchRoute2->Release(); _piSchRoute2 = NULL; }
  if ( NULL != _piUKAppRoute1 ) { _piUKAppRoute1->Release(); _piUKAppRoute1 = NULL; }
  if ( NULL != _piUKAppRoute2 ) { _piUKAppRoute2->Release(); _piUKAppRoute2 = NULL; }
  if ( NULL != _piSpecSchRoute1 ) { _piSpecSchRoute1->Release(); _piSpecSchRoute1 = NULL; }
  if ( NULL != _piSpecSchRoute2 ) { _piSpecSchRoute2->Release(); _piSpecSchRoute2 = NULL; }
  if ( NULL != _piSchGRRRoute1 ) { _piSchGRRRoute1->Release(); _piSchGRRRoute1 = NULL; }
  if ( NULL != _piSchGRRRoute2 ) { _piSchGRRRoute2->Release(); _piSchGRRRoute2 = NULL; }
  if ( NULL != _piUK ) { _piUK->Release(); _piUK = NULL; }
  if ( NULL != _piLUK ) { _piLUK->Release(); _piLUK = NULL; }
  if ( NULL != _piSchAppObjFact ) { _piSchAppObjFact->Release(); _piSchAppObjFact = NULL; }
}

//=============================================================================
//  DoSample
//=============================================================================
int CAASchAppSample3::DoSample (
   const char *iFileToBeLoaded, const char *iPathToOutputFile)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAASchAppSample3::DoSample                     ==="<< endl;
  cout <<"============================================================"<< endl;

  InitEnvironment(iFileToBeLoaded);

  HRESULT RC;

  CATTry 
	{
	  //-------------------------------------------------------------------------
    // Get Schematic Extension container created in InitEnvironment
    //-------------------------------------------------------------------------
    CATIContainer_var spSchExtCont = GetSchExtContainer();

    if (NULL_var == spSchExtCont)
    {
       cout << "CreateRouteTest:"
            << "Cannot find schematic extension container"
            << endl;
    }
            
    //-------------------------------------------------------------------------
    //  Get all factory interfaces
    //-------------------------------------------------------------------------
    RC = spSchExtCont->QueryInterface (IID_CATISchBaseFactory,
         (void **)&_piBaseFact);      
    if (FAILED(RC) || (NULL == _piBaseFact))
    {
       cout << "CreateRouteTest: "
            << "Cannot find CATISchBaseFactory interface adhesion"
            << endl;
       return 0;
    }

    RC = spSchExtCont->QueryInterface (IID_CATISchGRRFactory,
         (void **)&_piGRRFact);       
    if (FAILED(RC) || (NULL == _piGRRFact))
    {
       cout << "CreateRouteTest: "
            << "Cannot find CATISchGRRFactory interface adhesion"
            << endl;
       return 0;
    }

    SetMainSheet();

 	  //---------------------------------------------------------------------------
    // Get the Current Session
    //---------------------------------------------------------------------------
    CATSession *pSession = CATSession::GetPtrSession();
    if (NULL == pSession)
    {
      cout << "Cannot Get session" << endl;
      return E_FAIL;
    }

	  //---------------------------------------------------------------------------
    // QueryInterface for Schematic Session
    //---------------------------------------------------------------------------
    CATISchSession* piSchSession = NULL;
    if ( SUCCEEDED( pSession->QueryInterface (IID_CATISchSession,(void**)&piSchSession)))
    {
      piSchSession->GetSchObjInterface(SCHEDUApplication_Name,
        IID_CATISchAppObjectFactory2, (void**)&_piSchAppObjFact);

      piSchSession->Release(); piSchSession = NULL;
    } 
    else
    {
      cout << "Cannot get schematic session" << endl;
      return E_FAIL;
    }

    // Remove dummy instance from the doc
    RC = CAASchAppBaseServices::RemoveAppObjInstByClass (SCHEDUClass_String,_pSchDoc);

    //-------------------------------------------------------------------------
    //  Create two application route instances
    //-------------------------------------------------------------------------
    if (NULL != _piSchAppObjFact)
    {
      if (SUCCEEDED(_piSchAppObjFact->AppCreateRoute2 (SCHEDUClass_String,NULL,NULL,
           &_piUKAppRoute1)))
      {
        cout << "CAASchAppSample3::DoSample: First application route found" << endl;
      }
      else
      {
        cout << "Route: "
             << "Fail to find application object"
             << endl;
        return E_FAIL;
      } 

      if (SUCCEEDED(_piSchAppObjFact->AppCreateRoute2 (SCHEDUClass_String,NULL,NULL,
           &_piUKAppRoute2)))
      {
        cout << "CAASchAppSample3::DoSample: Second application route found" << endl;
      }
      else
      {
        cout << "Route: "
             << "Fail to find application object"
             << endl;
        return E_FAIL;
      } 
    }
    else
    {
      cout << "Cannot get Schematic Application Object Factory" << endl;
      return E_FAIL;
    } 

    //-------------------------------------------------------------------------
    //  Create schematic route by points
    //-------------------------------------------------------------------------
    if ( NULL != _piUKAppRoute1 )
    {
      double LDbPts[4] = {20.0, 20.0, 120.0, 20.0};
      int iSize = 4;
      RC = _piBaseFact->CreateSchRouteByPoints (_piUKAppRoute1, 
                        LDbPts, iSize, &_piSchRoute1);
      if (SUCCEEDED(RC) && (NULL != _piSchRoute1))
      {
        RC = _piSchRoute1->QueryInterface (IID_CATISpecObject, 
             (void **) &_piSpecSchRoute1);
        if (SUCCEEDED(RC) && (NULL != _piSpecSchRoute1))
        {
          cout << "App_RouteInstance created" <<endl;
        }
      }
    }

    //-------------------------------------------------------------------------
    //  Create 2 graphical representations (GRRRoute)
    //-------------------------------------------------------------------------
    if ( NULL != _piUKAppRoute2 )
    {
       double iLDbLinePath[4];
       int iSizeOfPath = 4;
       iLDbLinePath[0] = 150.0;
       iLDbLinePath[1] = 50.0;
       iLDbLinePath[2] = 150.0;
       iLDbLinePath[3] = 200.0;
       RC = _piGRRFact->CreateGRRRoute (iLDbLinePath, iSizeOfPath, &_piSchGRRRoute1);
       if (FAILED(RC) || (NULL == _piSchGRRRoute1))
       {
          cout << "CreateRouteTest: "
               << "Cannot create route graphical representation"
               << endl;
          return 0;
       } 
       iLDbLinePath[0] = 150.0;
       iLDbLinePath[1] = 150.0;
       iLDbLinePath[2] = 250.0;
       iLDbLinePath[3] = 150.0;
       RC = _piGRRFact->CreateGRRRoute (iLDbLinePath, iSizeOfPath, &_piSchGRRRoute2);
       if (FAILED(RC) || (NULL == _piSchGRRRoute2))
       {
          cout << "CreateRouteTest: "
               << "Cannot create route graphical representation"
               << endl;
          return 0;
       }
       cout << "CreateRouteTest: GRRRoutes created" << endl;
    }

    CATSchListServices SchList;
    if (SUCCEEDED(SchList.CreateCATIUnknownList (&_piLUK)))
    {
       if (NULL != _piLUK)
       {
          if (SUCCEEDED (_piSchGRRRoute1->QueryInterface (IID_IUnknown, 
              (void **) &_piUK)) )
          {
             _piLUK->Add(0,_piUK);
             _piUK->Release(); _piUK = NULL;
          }
          if (SUCCEEDED (_piSchGRRRoute2->QueryInterface (IID_IUnknown, 
              (void **) &_piUK)) )
          {
             _piLUK->Add(1,_piUK);
             _piUK->Release(); _piUK = NULL;
          }
       } 
    }

    //-------------------------------------------------------------------------
    //  Create schematic route by primitives
    //-------------------------------------------------------------------------
    RC = _piBaseFact->CreateSchRouteByPrim (_piUKAppRoute2, _piLUK, &_piSchRoute2);               
    if (SUCCEEDED(RC) && (NULL != _piSchRoute2))
    {
      RC = _piSchRoute2->QueryInterface (IID_CATISpecObject, 
           (void **) &_piSpecSchRoute2);
      if (SUCCEEDED(RC) && (NULL != _piSpecSchRoute2))
      {
        cout << "App_RouteInstance2 created" <<endl;
      }
    }
  } // end CATTry

  if (NULL != iPathToOutputFile) 
  {
    cout << "Document saved as : " << iPathToOutputFile << endl;
    SaveDocument (iPathToOutputFile);
  }

  CATCatch (CATError, error)
	{
    cout << "CAASchAppSample3::DoSample *** CATRethrow" 
         << endl;
    RC = E_FAIL;
	  CATRethrow;
	}

  CATEndTry;
  if ( SUCCEEDED(RC) )
	  return 0;
  else
    return 999;
}

//=============================================================================
//  Initialize the environment for testing objects.
//=============================================================================
void CAASchAppSample3::InitEnvironment (const char *iFileToBeLoaded)
{
  CATTry
  {
     CreateCATProductEnv (iFileToBeLoaded);
     _pSchDoc = GetDocument();
    
     if (NULL == _pSchDoc)
     {
       cout << "CAASchAppSample3::Cannot find DOCUMENT " << endl;
       return;
     }
  }
  CATCatch (CATError, error)
	{
    cout << "CAASchAppSample3::InitEnvironment *** CATRethrow" 
         << endl;
	  CATRethrow;
	}	
  CATEndTry;
}


