// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspLightPart - This sample illustrates how to use the following
// interfaces to modify and query for light part and light connector data:  
// CATIPspLightPart, CATIPspLightBend, CATIPspLightConnector.
//
#include <iostream.h>

// This framework
#include "CAAPspLightPart.h"

// CATPlantShipInterfaces
#include "CATIPspLightPart.h"
#include "CATIPspLightBend.h"
#include "CATIPspLightConnector.h"
#include "CATIPspPhysicalProduct.h"

// System
#include "CATErrorMacros.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATListOfDouble.h"
#include "CATLISTV_CATMathPoint.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspLightPart::CAAPspLightPart() 
{
  cout << "CAAPspLightPart::CAAPspLightPart()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspLightPart::~CAAPspLightPart()
{
  cout << "CAAPspLightPart::~CAAPspLightPart()" << endl;
}

//=============================================================================
//  List and query part connectors
//=============================================================================
int CAAPspLightPart::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspLightPart::DoSample                      ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspLightPart       *piLightPart   = NULL;
  CATIPspLightBend       *piLightBend   = NULL;
  CATIPspLightConnector  *piLightCntr   = NULL;
  CATIPspPhysicalProduct *piPhysProd    = NULL;
  IUnknown               *piUnknown     = NULL;
  CATIUnknownList        *piUnkList     = NULL;

  CATListOfDouble *ListOfRadii = NULL;
  CATListValCATMathPoint ListOfPoints;
  CATMathPoint mPt;
  CATMathDirection mDirection;
  int NumOfPts;
  double PtCoord[3]; 
  double X, Y, Z;

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    //  Get a physical light object from the input document
    piLightPart = GetALightObject();

    if ( NULL != piLightPart )
    {
       //  Find CATIPspLightBend interface
       rc = piLightPart->QueryInterface(IID_CATIPspLightBend,(void**)&piLightBend);
       //  Find CATIPspPhysicalProduct interface
       rc = piLightPart->QueryInterface(IID_CATIPspPhysicalProduct,(void**)&piPhysProd);
    }

    //-------------------------------------------------------------------------
    //  CATIPspLightPart methods
    //-------------------------------------------------------------------------
    if ( NULL != piLightPart )
    {
       //----------------------------------------------------------------------
       //  List the definition points for the light part
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piLightPart->GetDefinition(NULL,ListOfPoints)) )
       {
          NumOfPts = ListOfPoints.Size();
          cout << "Number of light part definition points: " << NumOfPts << endl;
          for ( int i = 1; i <= NumOfPts; i++ )
          {
             mPt = ListOfPoints[i];
             mPt.GetCoord(PtCoord);
             X = PtCoord[0]; 
             Y = PtCoord[1];
             Z = PtCoord[2];
          }

          //-------------------------------------------------------------------
          //  Set the definition points for the light part
          //-------------------------------------------------------------------
          if ( SUCCEEDED(piLightPart->SetDefinition(NULL,ListOfPoints)) )
          {
             cout << "Succeeded in setting the light part definition points" << endl;
          }
       }
       piLightPart->Release();
       piLightPart = NULL;
    }       
 
    //-------------------------------------------------------------------------
    //  CATIPspLightBend methods
    //-------------------------------------------------------------------------
    if ( NULL != piLightBend )
    {
       //----------------------------------------------------------------------
       //  List the bend radii
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piLightBend->GetBendData(ListOfRadii)) )
       {
          NumOfPts = ListOfRadii->Size();
          cout << "Number of bend radii: " << NumOfPts << endl;

          //-------------------------------------------------------------------
          //  Set the bend radii
          //-------------------------------------------------------------------
          if ( SUCCEEDED(piLightBend->SetBendData(ListOfRadii)) )
          {
             cout << "Succeeded in setting the bend radii" << endl;
          }
       }
       piLightBend->Release();
       piLightBend = NULL;
    }           

    if ( NULL != piPhysProd )
    {
       //----------------------------------------------------------------------
       //  List part connectors
       //----------------------------------------------------------------------    
       if ( SUCCEEDED(piPhysProd->ListConnectors(NULL,&piUnkList))
            && NULL != piUnkList )
       {
          //  Get a light part connector
          unsigned int ListSize = 0;
          int NumOfCtrs = 0;
          if ( SUCCEEDED(piUnkList->Count(&ListSize)) ) NumOfCtrs = ListSize;
          if ( NumOfCtrs > 0 )
          {
             for ( int i = 0; i < NumOfCtrs; i++ )
             {
                if ( SUCCEEDED(piUnkList->Item(i,&piUnknown)) && (NULL != piUnknown) )
                {
                   rc = piUnknown->QueryInterface(IID_CATIPspLightConnector,
                                   (void**)&piLightCntr);
                   piUnknown->Release();
                   piUnknown = NULL; 
                   if ( NULL != piLightCntr ) break;
                }
             }
          }
          piUnkList->Release();  piUnkList = NULL;
       }
       piPhysProd->Release();
       piPhysProd = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspLightConnector methods
    //-------------------------------------------------------------------------
    if ( NULL != piLightCntr )
    {
       //----------------------------------------------------------------------
       //  Get and set the origin point of a light connector
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piLightCntr->GetOrigin(NULL,mPt)) )
          cout << "Succeeded in getting the origin of a light part connector" << endl;

       if ( SUCCEEDED(piLightCntr->SetOrigin(NULL,mPt)) )
          cout << "Succeeded in setting the origin of a light part connector" << endl;

       //----------------------------------------------------------------------
       //  Get and set the alignment vector of a light connector
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piLightCntr->GetAlignmentVector(NULL,mDirection)) )
          cout << "Succeeded in getting the alignment vector of a light part connector" << endl;

       if ( SUCCEEDED(piLightCntr->SetAlignmentVector(NULL,mDirection)) )
          cout << "Succeeded in setting the alignment vector of a light part connector" << endl;

       //----------------------------------------------------------------------
       //  Get and set the orientation vector of a light connector
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piLightCntr->GetOrientationVector(NULL,mDirection)) )
          cout << "Succeeded in getting the orientation vector of a light part connector" << endl;

       if ( SUCCEEDED(piLightCntr->SetOrientationVector(NULL,mDirection)) )
          cout << "Succeeded in setting the orientation vector of a light part connector" << endl;

       piLightCntr->Release();
       piLightCntr = NULL;
    }
  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piLightPart ) { piLightPart->Release(); piLightPart = NULL; }
    if ( NULL != piLightBend ) { piLightBend->Release(); piLightBend = NULL; }
    if ( NULL != piLightCntr ) { piLightCntr->Release(); piLightCntr = NULL; }
    if ( NULL != piPhysProd ) { piPhysProd->Release(); piPhysProd = NULL; }
    if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
    if ( NULL != piUnkList ) { piUnkList->Release(); piUnkList = NULL; }
    cout << "CAAPspLightPart::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}
