// COPYRIGHT DASSAULT SYSTEMES  2011
//=============================================================================
//
// CAACloPspSpatialPhysical - This sample illustrates how to use the following
// interfaces to query spatial objects: CATIPspSpatial.
// 
//
//=============================================================================

#include <iostream.h>

#include "CAACloPspSpatialPhysical.h"

// CATPlantShipInterfaces
#include "CATIPspPhysical.h"
#include "CATIPspSpatial.h"

//ObjectModelerBase
#include "CATDocument.h"
#include "CATISpecObject.h"

// System
#include "CATBooleanDef.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATListOfInt.h"

#include "CATIArrNode.h" 
#include "CATIArrSegmentsString.h" 
#include "CATIProduct.h" 


//=============================================================================
//  Constructor
//=============================================================================
CAACloPspSpatialPhysical::CAACloPspSpatialPhysical() : CAAPspBaseEnvProtected()
{
  cout << "CAACloPspSpatialPhysical::CAACloPspSpatialPhysical()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAACloPspSpatialPhysical::~CAACloPspSpatialPhysical()
{
  cout << "CAACloPspSpatialPhysical::~CAACloPspSpatialPhysical()" << endl;
}

//===============================================================================================================
//  Retrieve all physical objects and corresponding connectors associated at the extremity of the spatial object.
//===============================================================================================================
HRESULT CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial()
{
  cout <<"======================================================================"<< endl;
  cout <<"===   CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial    ==="<< endl;
  cout <<"======================================================================"<< endl;

  HRESULT rc = E_FAIL;

  CATIPspPhysical    *piPhysical = NULL;
  CATIPspSpatial     *piSpatial = NULL;
  IUnknown           *piUnknown = NULL;
  CATIArrSegmentsString *pRun = NULL; 

  CATIArrNode_var ospEndPoint1 = NULL_var; 
  CATIArrNode_var ospEndPoint2 = NULL_var; 
  CATIArrNode_var spArrNode = NULL_var; 

  CATIUnknownList* piListOfPhysicals = NULL; 
  CATIUnknownList* piListOfConnectors	= NULL; 

  CATTry 
  {
    //-------------------------------------------------------------------------
    //  CATIPspPhysical methods
    //-------------------------------------------------------------------------
    piPhysical = GetAPhysicalObject();
    if ( NULL != piPhysical )
    {
      //----------------------------------------------------------------------
      //  Get the spatial object associated to the physical object
      //----------------------------------------------------------------------    
      if ( SUCCEEDED(piPhysical->GetSpatial(piUnknown)) && NULL != piUnknown )
      {
        //  Find CATIPspSpatial interface
        piUnknown->QueryInterface(IID_CATIPspSpatial,(void**)&piSpatial);
        piUnknown->Release();
        piUnknown = NULL;
      }
      //-------------------------------------------------------------------------
      //  CATIPspSpatial methods
      //-------------------------------------------------------------------------
      if ( NULL != piSpatial )
      {
        //----------------------------------------------------------------------------------------------------
        //  Get a list of physical objects and connectors associated at the extremity of the spatial object.
        //---------------------------------------------------------------------------------------------------- 
        if(SUCCEEDED(piSpatial->QueryInterface(IID_CATIArrSegmentsString, (void**)&pRun)))
        {
          pRun->GetEndPoints(ospEndPoint1,ospEndPoint2);
          if(!!ospEndPoint1)
            spArrNode = ospEndPoint1;

          if ( SUCCEEDED(piSpatial->ListConnectedPhysicals( spArrNode, piListOfPhysicals, piListOfConnectors ))
            && NULL != piListOfPhysicals  && NULL != piListOfConnectors )
          {
            unsigned int ListSize = 0;
            piListOfPhysicals->Count(&ListSize);
            cout << "Number of physical objects associated to the first extremity of the spatial object: " << (int)ListSize << endl;
            piListOfPhysicals->Release();  piListOfPhysicals = NULL;

            piListOfConnectors->Count(&ListSize);
            cout << "Number of connectors connected to the first extremity of the spatial object: " << (int)ListSize << endl;
            piListOfConnectors->Release();  piListOfConnectors = NULL;
            rc = S_OK;
          }
        }
        if ( NULL != pRun )
        { 
          pRun->Release(); 
          pRun = NULL;
        }
        piSpatial->Release();
        piSpatial = NULL;
      } // end piSpatial      
      piPhysical->Release();
      piPhysical = NULL;
    } // end piPhysical
  } // end CATTry
  CATCatch (CATError, error)
  {
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piSpatial ) { piSpatial->Release(); piSpatial = NULL; }
    if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
    cout << "CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  cout << "CAACloPspSpatialPhysical::ListConnectedPhysicalsToSpatial rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Execute the CAACloPspSpatialPhysical sample code.
//=============================================================================
HRESULT CAACloPspSpatialPhysical::DoSample(const CATUnicodeString &iuFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===        CAACloPspSpatialPhysical::DoSample            ==="<< endl;
  cout <<"============================================================"<< endl;
  cout <<" File: " << iuFileToBeLoaded << endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv(iuFileToBeLoaded);
    cout << "Product environment created." << endl;

    //  Initialize Tubing Design application
    ApplicationInit("CATPiping");
    cout << "Piping application initialized." << endl;

    // Retrieve a list of physical objects and connectors associated at the extremity of the spatial object.
    HRESULT rcListCntrPhy = ListConnectedPhysicalsToSpatial();
    cout << "rcListCntrPhy = " << rcListCntrPhy << endl;    

    // Set return code.
    if (SUCCEEDED(rcListCntrPhy))
      rc = CATReturnSuccess;
  } // end CATTry

  CATCatch (CATError, pError)
  {
    cout << "CAACloPspSpatialPhysical::DoSample *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
  } // end CATCatch

  CATEndTry;

  cout << "CAACloPspSpatialPhysical::DoSample rc = " << rc << endl;
  return rc;
}
