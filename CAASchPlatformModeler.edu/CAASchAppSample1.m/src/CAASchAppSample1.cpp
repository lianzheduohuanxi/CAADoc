// COPYRIGHT DASSAULT SYSTEMES  2000+
//=============================================================================
//
// CAASchAppSample1 - Creates a component with two connectors and an internal flow between them.
//
#include <iostream.h>

// This framework
#include "CAASchAppSample1.h"
#include "CAASchAppClassNames.h"
#include "CAASchAppBaseServices.h"
#include "CAASchAppErrors.h"

// CATSchPlatformInterfaces
#include "CATISchBaseFactory.h"
#include "CATISchComponent.h"
#include "CATISchCompGraphic.h"
#include "CATISchAppConnector.h"
#include "CATISchInternalFlow.h"
#include "CATISchGRRComp.h"
#include "CATISchCntrLocation.h"
#include "CATISchCompConnector.h"
#include "CATISchCompFlow.h"
#include "CATISchSession.h"
#include "CATSchListServices.h"
#include "CATISchAppObjectFactory2.h"

// ObjectModelerBase
#include "CATDocument.h"
#include "CATIContainer.h"
#include "CATIAlias.h"
#include "CATSession.h"

// System
#include "CATIUnknownList.h"
#include "IUnknown.h"

// Drafting
#include "CATIDftDocumentServices.h"
#include "CATIDrawing.h"
#include "CATISheet.h"
#include "CATI2DDetail.h"

//=============================================================================
//  Constructor
//=============================================================================
CAASchAppSample1::CAASchAppSample1() 
             :_spDetailSpec (NULL_var),
              _spDetailSheet(NULL_var),
              _spDrawing(NULL_var),
              _pSchDoc (NULL),
              _piSchComp (NULL),
              _piUKAppRef (NULL),
              _piBaseFact (NULL),
              _piUK (NULL),
              _piLUK (NULL),
              _piSpecSchComp (NULL),
              _piSchAppObjFact (NULL)
{
  cout << "CAASchAppSample1::CAASchAppSample1()" << endl;
};

//=============================================================================
//  Destructor
//=============================================================================
CAASchAppSample1::~CAASchAppSample1()
{
  cout << "CAASchAppSample1::~CAASchAppSample1()" << endl;

  _pSchDoc = NULL;

  if ( NULL != _piBaseFact ) { _piBaseFact->Release(); _piBaseFact = NULL; }
  if ( NULL != _piSchComp ) { _piSchComp->Release(); _piSchComp = NULL; }
  if ( NULL != _piUKAppRef ) { _piUKAppRef->Release(); _piUKAppRef = NULL; }
  if ( NULL != _piSpecSchComp ) { _piSpecSchComp->Release(); _piSpecSchComp = NULL; }
  if ( NULL != _piUK ) { _piUK->Release(); _piUK = NULL; }
  if ( NULL != _piLUK ) { _piLUK->Release(); _piLUK = NULL; }
  if ( NULL != _piSchAppObjFact ) { _piSchAppObjFact->Release(); _piSchAppObjFact = NULL; }
}

//=============================================================================
//  CreateComponent
//=============================================================================
int CAASchAppSample1::DoSample(const char *iFileToBeLoaded, const char *iPathToOutputFile)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAASchAppSample1::DoSample                     ==="<< endl;
  cout <<"============================================================"<< endl;

  InitEnvironment(iFileToBeLoaded);

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  IUnknown              *piUnknown = NULL;  
  CATISpecObject        *piSpec = NULL;
  CATISchCompConnector  *piCompCtr = NULL;
  CATISchCompGraphic    *piCompGrr = NULL;
  CATIUnknownList       *pLIGRRs = NULL;
  CATISchGRRComp        *piGrr = NULL;
  CATISchCntrLocation   *piCtrLoc = NULL;
  CATISchAppConnector   *piAppCtr1 = NULL;
  CATISchAppConnector   *piAppCtr2 = NULL;
  CATISchCompFlow       *piCompFlow = NULL;
  CATIUnknownList       *pLICtrs = NULL;
  CATISchInternalFlow   *piInternalFlow1 = NULL;
  CATISchComponent      *piSchComp = NULL;

  CATTry 
	{
    if ( (NULL_var != _spDrawing) && (NULL_var != _spDetailSheet) ) 
    {
       _spDrawing->SetCurrentSheet(_spDetailSheet);
    }

    //-------------------------------------------------------------------------
    // Get Schematic Extension container created in InitEnvironment
    //-------------------------------------------------------------------------
    CATIContainer_var spSchExtCont = GetSchExtContainer();
    if (NULL_var == spSchExtCont)
    {
       cout << "CreateComponent:"
            << "Cannot find schematic extension container"
            << endl;
       return E_FAIL;
    }
            
    //-------------------------------------------------------------------------
    // Get all factory interfaces
    //-------------------------------------------------------------------------
    rc = spSchExtCont->QueryInterface (IID_CATISchBaseFactory,(void **)&_piBaseFact);      
    if (FAILED(rc) || (NULL == _piBaseFact))
    {
       cout << "CreateComponent: "
            << "Cannot find CATISchBaseFactory interface adhesion"
            << endl;
       return E_FAIL;
    }

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

    //-------------------------------------------------------------------------
    //  Find the application component reference
    //-------------------------------------------------------------------------
    if (NULL != _piSchAppObjFact)
    {
      if (SUCCEEDED(_piSchAppObjFact->AppCreateCompRef (SCHEDUClass_Part,NULL,
           &_piUKAppRef)))
      {
        cout << "Successfully retrieved the application reference component "
             << endl;
      }
      else
      {
        cout << "Component: "
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
    //  Get graphical representation
    //-------------------------------------------------------------------------
    if (NULL_var == _spDetailSpec)
    {
       cout << "CreateComponent: "
            << "Cannot find component graphical representation (detail)"
            << endl;
       return E_FAIL;
    }

    //-------------------------------------------------------------------------
    //  _piUK, _piLUK and _piSpecSchComp have not be used up to here
    //-------------------------------------------------------------------------
    CATSchListServices SchList;
    rc = SchList.CreateCATIUnknownList(&_piLUK);

    if ( SUCCEEDED(rc) )
    {
       if (NULL != _piLUK)
       {
          if (SUCCEEDED (_spDetailSpec->QueryInterface (IID_IUnknown,(void **) &_piUK)) )
          {
             _piLUK->Add(0,_piUK);  // This list will only have 1 graphical representation
          }
       } 
    }

    //-------------------------------------------------------------------------
    //  Create schematic object
    //-------------------------------------------------------------------------
    rc = _piBaseFact->CreateSchComponent (_piUKAppRef, _piLUK, &_piSchComp);               
    if (SUCCEEDED(rc) ) 
    {
      if ( NULL != _piSchComp)
      {
        rc = _piSchComp->QueryInterface (IID_CATISpecObject,(void **) &_piSpecSchComp);
      }
    }
    if ( NULL == _piSchComp ) return E_FAIL;

    // We will now add two connectors and an internal flow between them.

    // Find CATISchCompConnector interface 
    rc = _piSchComp->QueryInterface (IID_CATISchCompConnector,(void **) &piCompCtr);
    if ( FAILED(rc) || (NULL == piCompCtr) ) 
    {
       cout << "CreateComponent: "
            << "QI Failed for IID_CATISchCompConnector"
            << endl;
       return E_FAIL;
    }

    // Find CATISchCompGraphic interface 
    rc = _piSchComp->QueryInterface (IID_CATISchCompGraphic,(void **) &piCompGrr);
    if ( FAILED(rc) || (NULL == piCompGrr) ) 
    {
       cout << "CreateComponent: "
            << "QI Failed for IID_CATISchCompGraphic"
            << endl;
       return E_FAIL;
    }

    // Find Grrs
    rc = piCompGrr->ListGraphicalRepresentations (&pLIGRRs);
    if ( NULL == pLIGRRs ) return E_FAIL;
    rc = pLIGRRs->Item (0,&piUnknown); // We know this component has only 1 graphical rep (since we created it with one, above) 
    if ( NULL == piUnknown ) return E_FAIL;

    rc = piUnknown->QueryInterface (IID_CATISchGRRComp,(void **) &piGrr);
    if ( FAILED(rc) || (NULL == piGrr) ) 
    {
       cout << "CreateComponent: "
            << "QI Failed for IID_CATISchGRRComp"
            << endl;
       return E_FAIL;
    }

    // Remove dummy instance from the doc
    rc = CAASchAppBaseServices::RemoveAppObjInstByClass (SCHEDUClass_Part,_pSchDoc);

    // Create connectors

    // Connector 1
    double ctr1Loc[2] = { -30.0, 0.0 };
    double vector1[2] = { -1.0, 0.0 };

    rc = piCompCtr->AddConnector (SCHEDUClass_Connector, piGrr, ctr1Loc, &piAppCtr1);
    if ( FAILED(rc) || (NULL == piAppCtr1) ) 
    {
       cout << "CreateComponent: "
            << "Add Connector 1 Failed"
            << endl;
       return E_FAIL;
    }

    rc = piAppCtr1->QueryInterface (IID_CATISchCntrLocation,(void **) &piCtrLoc);
    if (SUCCEEDED (rc) && (NULL != piCtrLoc) )
    {
      piCtrLoc->SetAlignVector(NULL, vector1);
      piCtrLoc->Release(); piCtrLoc = NULL;
    }
    rc = piAppCtr1->QueryInterface (IID_CATISpecObject,(void **) &piSpec);
    if (SUCCEEDED (rc) && (NULL != piSpec) )
    {
      piSpec->Release(); piSpec = NULL;
    }    

    // Connector 2
    double ctr2Loc[2] = { 30.0, 0.0 };
    double vector2[2] = { 1.0, 0.0 };

    rc = piCompCtr->AddConnector (SCHEDUClass_Connector, piGrr, ctr2Loc, &piAppCtr2);
    if ( FAILED(rc) || (NULL == piAppCtr2) ) 
    {
       cout << "CreateComponent: "
            << "Add Connector 2 Failed"
            << endl;
       return E_FAIL;
    }

    rc = piAppCtr2->QueryInterface (IID_CATISchCntrLocation,(void **) &piCtrLoc);
    if (SUCCEEDED (rc) && (NULL != piCtrLoc) )
    {
      piCtrLoc->SetAlignVector(NULL, vector2);
      piCtrLoc->Release(); piCtrLoc = NULL;
    }
    rc = piAppCtr2->QueryInterface (IID_CATISpecObject,(void **) &piSpec);
    if (SUCCEEDED (rc) && (NULL != piSpec) )
    {
      piSpec->Release(); piSpec = NULL;
    } 

    // Now add flow between the two connectors created above.
    // First get the CATISchCompFlow interface from our reference object, so 
    // that we can use it's methods to create a flow.

    rc = _piSchComp->QueryInterface (IID_CATISchCompFlow, (void **) &piCompFlow);
    if ( FAILED(rc) || (NULL == piCompFlow) ) 
    {
       cout << "CreateComponent: "
            << "QI Failed for IID_CATISchCompFlow"
            << endl;
       return E_FAIL;
    }

    // We are going to use the CATISchCompFlow::AddInternalFlow method, which takes two arguments:
    // 1. a list of unknown pointers to the connector pairs.
    // 2. an output internal flow interface pointer to the internal flow created.

    CATSchListServices aList;
    aList.CreateCATIUnknownList(&pLICtrs); // Create a list of unknowns

    rc = piAppCtr1->QueryInterface (IID_IUnknown, (void **) &piUnknown);
    if (SUCCEEDED(rc) && (NULL != piUnknown) && (NULL != pLICtrs))
    {
      rc = pLICtrs->Add(0,piUnknown);
      piUnknown->Release(); piUnknown = NULL;
    }
    rc = piAppCtr2->QueryInterface (IID_IUnknown, (void **) &piUnknown);
    if (SUCCEEDED(rc) && (NULL != piUnknown) && (NULL != pLICtrs))
    {
      rc = pLICtrs->Add(1,piUnknown);
      piUnknown->Release(); piUnknown = NULL;
    }

    rc = piCompFlow->AddInternalFlow(pLICtrs, &piInternalFlow1);
    if ( FAILED(rc) || (NULL == piInternalFlow1) ) 
    {
       cout << "CreateComponent: "
            << "AddInternalFlow failed"
            << endl;
       return E_FAIL;
    }

    rc = (piInternalFlow1)->QueryInterface (IID_CATISpecObject,(void **) &piSpec);
    if (SUCCEEDED (rc) && (NULL != piSpec))
    {
      piSpec->Release(); piSpec = NULL;
    }


    // Now Instanciate the reference...
    //-------------------------------------------------------------------------
    //  Create component instance from reference
    //  First set the main sheet
    //-------------------------------------------------------------------------

    SetMainSheet();

    double aDb6Axis[6] = {1.0,0.0,0.0,1.0,50.0,100.0};
    rc = _piSchComp->PlaceInSpace (NULL, aDb6Axis, &piSchComp);
    if (SUCCEEDED (rc))
    {
      CATISpecObject *piSpecObjInst = NULL;
      CATISpecObject *piSchCompInst = NULL;
      CATTry 
      {
        if (SUCCEEDED (piSchComp->QueryInterface(IID_CATISpecObject,(void **) &piSpecObjInst)))
        {
        }
        if (SUCCEEDED (piSchComp->QueryInterface (IID_CATISpecObject,(void **) &piSchCompInst)))
        {
        }
      }
       
      if ( NULL != piSchCompInst ) { piSchCompInst->Release(); piSchCompInst = NULL; }
      if ( NULL != piSpecObjInst ) { piSpecObjInst->Release(); piSpecObjInst = NULL; }

      CATCatch (CATError, error)
      {
        if ( NULL != piSchCompInst ) { piSchCompInst->Release(); piSchCompInst = NULL; }
        if ( NULL != piSpecObjInst ) { piSpecObjInst->Release(); piSpecObjInst = NULL; }
        CATRethrow;
      }
      CATEndTry;
    }
    else
    {
       cout << "Fail in PlaceInSpace for creating first instance " 
            << "from the reference"
            << endl;
    }


  } // end CATTry

  if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
  if ( NULL != piSpec ) { piSpec->Release(); piSpec = NULL; }
  if ( NULL != piCompCtr ) { piCompCtr->Release(); piCompCtr = NULL; }
  if ( NULL != piCompGrr ) { piCompGrr->Release(); piCompGrr = NULL; }
  if ( NULL != pLIGRRs ) { pLIGRRs->Release(); pLIGRRs = NULL; }
  if ( NULL != piGrr ) { piGrr->Release(); piGrr = NULL; }
  if ( NULL != piCtrLoc ) { piCtrLoc->Release(); piCtrLoc = NULL; }
  if ( NULL != piAppCtr1 ) { piAppCtr1->Release(); piAppCtr1 = NULL; }
  if ( NULL != piAppCtr2 ) { piAppCtr2->Release(); piAppCtr2 = NULL; }
  if ( NULL != piCompFlow ) { piCompFlow->Release(); piCompFlow = NULL; }
  if ( NULL != pLICtrs ) { pLICtrs->Release(); pLICtrs = NULL; }
  if ( NULL != piInternalFlow1 ) { piInternalFlow1->Release(); piInternalFlow1 = NULL; }
  if ( NULL != piSchComp ) { piSchComp->Release(); piSchComp = NULL; }

  if (NULL != iPathToOutputFile) 
  {
    cout << "Document saved as : " << iPathToOutputFile << endl;
    SaveDocument (iPathToOutputFile);
  }

  CATCatch (CATError, error)
	{
    if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
    if ( NULL != piSpec ) { piSpec->Release(); piSpec = NULL; }
    if ( NULL != piCompCtr ) { piCompCtr->Release(); piCompCtr = NULL; }
    if ( NULL != piCompGrr ) { piCompGrr->Release(); piCompGrr = NULL; }
    if ( NULL != pLIGRRs ) { pLIGRRs->Release(); pLIGRRs = NULL; }
    if ( NULL != piGrr ) { piGrr->Release(); piGrr = NULL; }
    if ( NULL != piCtrLoc ) { piCtrLoc->Release(); piCtrLoc = NULL; }
    if ( NULL != piAppCtr1 ) { piAppCtr1->Release(); piAppCtr1 = NULL; }
    if ( NULL != piAppCtr2 ) { piAppCtr2->Release(); piAppCtr2 = NULL; }
    if ( NULL != piCompFlow ) { piCompFlow->Release(); piCompFlow = NULL; }
    if ( NULL != pLICtrs ) { pLICtrs->Release(); pLICtrs = NULL; }
    if ( NULL != piInternalFlow1 ) { piInternalFlow1->Release(); piInternalFlow1 = NULL; }
    if ( NULL != piSchComp ) { piSchComp->Release(); piSchComp = NULL; }

    cout << "CAASchAppSample1::DoSample *** CATRethrow" << endl;
	  CATRethrow;
	}	
  CATEndTry;
	return 0 ;
}

//=============================================================================
//  Initialize the environment for testing objects.
//=============================================================================
void CAASchAppSample1::InitEnvironment (const char *iFileToBeLoaded)
{
  CATTry
  {
     CreateCATProductEnv (iFileToBeLoaded);

     _pSchDoc = GetDocument();

     GetDraftingObjects ();


  }
  CATCatch (CATError, error)
	{
    cout << "CAASchAppSample1::InitEnvironment *** CATRethrow" 
         << endl;
	  CATRethrow;
	}	
  CATEndTry;
}

//=============================================================================
//  Get drafting objects
//=============================================================================
void CAASchAppSample1::GetDraftingObjects ()
{

  HRESULT rc;
  if (NULL == _pSchDoc)
  {
    cout << "CAASchAppSample1::Cannot find DOCUMENT " << endl;
    return;
  }
  CATTry 
	{
    //-------------------------------------------------------------------------
    //  
    //-------------------------------------------------------------------------
    CATIDftDocumentServices *piService = NULL;

    rc = _pSchDoc->QueryInterface (IID_CATIDftDocumentServices,(void**)&piService);
    if (FAILED(rc)) return;

    CATIDrawing* piDrawing = NULL;
    rc = piService->GetDrawing (IID_CATIDrawing,(void**)&piDrawing);
    piService->Release();
    piService = NULL;
    if (FAILED(rc)) return; 
    
    _spDrawing = piDrawing;
    CATLISTV(CATISpecObject_var) LSheet = piDrawing->GetSheetList();
    piDrawing->Release();
    piDrawing = NULL;

    int SizeOfLSheet = LSheet.Size();
    int SizeOfLView = 0;
    _spDetailSpec = NULL_var;
    cout << "Size of sheet list = " << SizeOfLSheet << endl;

    for (int iSheet = 1; (iSheet <= SizeOfLSheet) && (NULL_var == _spDetailSpec); iSheet++)
    {
       CATISheet_var spSheet = LSheet[iSheet];
       CATIAlias_var spShAlias = spSheet;
       cout << "Member sheet: " << iSheet << "is "
            << (spShAlias->GetAlias()).CastToCharPtr() << endl;

       boolean BYes = FALSE;
       spSheet->IsDetail(&BYes);
       if (BYes == TRUE)
       {
         cout << "detail sheet" << endl;
         _spDetailSheet = spSheet;
         CATLISTV(CATISpecObject_var) LView = spSheet->GetViewList();
         CATISpecObject_var spSpecView;
         SizeOfLView = LView.Size();
         cout << "Size of view list = " << SizeOfLView << endl;

         if (SizeOfLView < 3)
            continue; 

         for (int iView = 3; (iView <= SizeOfLView) && (NULL_var == _spDetailSpec); iView++) 
         {
            spSpecView = LView[iView];
            if (!!spSpecView)
            {
              CATI2DDetail *piDetail = NULL;
              rc = spSpecView->QueryInterface (IID_CATI2DDetail,(void **) &piDetail);
              cout << "Member " << iView << endl;
              if (NULL != piDetail)
              {
                cout << "Got CATI2DDetail pointer " << endl;
                piDetail->Release();
                piDetail = NULL;
              }
              
              CATISpecObject *piDtlSpec = NULL;
              rc = spSpecView->QueryInterface (IID_CATISpecObject,(void **) &piDtlSpec);
              if (NULL != piDtlSpec)
              {
                _spDetailSpec = piDtlSpec;
                cout << "Got CATISpecObject pointer " << endl;
                piDtlSpec->Release();
                piDtlSpec = NULL;
              }           
            } // if (!!spSpecView)
         } // end for each view

       } // end if IsDetail
       else
       {
         cout << "not detail sheet" << endl;
       }
    }// end for each sheet

  } // end CATTry

  CATCatch (CATError, error)
	{
    cout << "CAASchAppSample1::GetDraftingObjects *** CATRethrow" 
         << endl;
	  CATRethrow;
	}	
  CATEndTry;
}


