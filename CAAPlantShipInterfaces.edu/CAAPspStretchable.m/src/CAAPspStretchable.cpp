// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspStretchable - This sample illustrates how to use the following
// interface to query for stretchable part information:  
// CATIPspStretchableData.
//
#include <iostream.h>

// This framework
#include "CAAPspStretchable.h"

// CATPlantShipInterfaces
#include "CATIPspStretchableData.h"
#include "CATIPspPhysical.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATLISTV_CATMathPoint.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspStretchable::CAAPspStretchable() 
{
  cout << "CAAPspStretchable::CAAPspStretchable()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspStretchable::~CAAPspStretchable()
{
  cout << "CAAPspStretchable::~CAAPspStretchable()" << endl;
}

//=============================================================================
//  Query stretchable part
//=============================================================================
int CAAPspStretchable::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspStretchable::DoSample                    ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspPhysical        *piPhysical = NULL;
  CATIPspStretchableData *piStretchable = NULL;

  CATListValCATMathPoint ListOfPoints;
  CATListOfDouble ListOfRadii;
  CATMathPoint mPt;
  int NumOfPts;
  double PtCoord[3]; 
  double Radius;
  double X, Y, Z;

  CATTry
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    //  Get a bendable pipe from the input document
    piPhysical = GetABendablePipeObject();

    if ( NULL != piPhysical )
    {
       // Find CATIPspStretchableData interface
       rc = piPhysical->QueryInterface(IID_CATIPspStretchableData,(void**)&piStretchable);
       piPhysical->Release();
       piPhysical = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspStretchableData methods
    //-------------------------------------------------------------------------
    if ( NULL != piStretchable )
    {
       //----------------------------------------------------------------------
       //  List the definition points for the pipe
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piStretchable->ListDefinitionPoints(NULL,ListOfPoints)) )
       {
          NumOfPts = ListOfPoints.Size();
          cout << "Number of pipe definition points: " << NumOfPts << endl;
          for ( int i = 1; i <= NumOfPts; i++ )
          {
             mPt = ListOfPoints[i];
             mPt.GetCoord(PtCoord);
             X = PtCoord[0]; 
             Y = PtCoord[1];
             Z = PtCoord[2];
          }
       }

       //----------------------------------------------------------------------
       //  List the bend radii
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piStretchable->ListBendData(ListOfRadii)) )
       {
          NumOfPts = ListOfRadii.Size();
          for ( int i = 1; i <= NumOfPts; i++ )
          {
             Radius = ListOfRadii[i];
          }
       }

       piStretchable->Release();
       piStretchable = NULL;
    }
  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piStretchable ) { piStretchable->Release(); piStretchable = NULL; }
    cout << "CAAPspStretchable::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}
