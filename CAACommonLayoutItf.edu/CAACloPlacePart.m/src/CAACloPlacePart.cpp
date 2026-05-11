// COPYRIGHT DASSAULT SYSTEMES  2007
//=============================================================================
//
// CAACloPlacePart 
//   This sample illustrates how to use the CATIPspPlacePartOnRun 
//   interface to place parts.
//
//=============================================================================

#include <iostream.h>

#include "CAACloPlacePart.h"

#include "CATIPspPhysicalProduct.h"
#include "CATIPspPhysical.h"
#include "CATIPspPartConnector.h"
#include "CATPspPartConnectorTypeEnum.h"
#include "CATIPspPlacePartOnRun.h"
#include "CATIPspLogicalLine.h"
#include "CATDocument.h"
#include "CATIConnector.h"
#include "CATIAPartDocument.h"
#include "CATIAPart.h"
#include "CATILinkableObject.h"
#include "CATISpecObject.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATIProduct.h"
#include "CATIAProduct.h"
#include "CATIAProducts.h"
#include "CATMathPoint.h"
#include "CATMathPlane.h"
#include "CATMathDirection.h"
#include "CATIAHybridShapeFactory.h"
#include "CATIAHybridShapePointCoord.h"
#include "CATIUnknownListImpl.h"
#include "CATIMovable.h"
#include "CATIArrSegmentsString.h"
#include "CATIArrSegment.h"
#include "CATIArrNode.h"
#include "CATIPspConnector.h"
#include "CATIPspConnection.h"
#include "CATIPspConnectable.h"

//=============================================================================
//  Constructor
//=============================================================================
CAACloPlacePart::CAACloPlacePart() : CAAPspBaseEnvProtected()
{
  cout << "CAACloPlacePart::CAACloPlacePart()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAACloPlacePart::~CAACloPlacePart()
{
  cout << "CAACloPlacePart::~CAACloPlacePart()" << endl;
}

//=============================================================================
// Get a part connector.
//=============================================================================
HRESULT CAACloPlacePart::GetPartConnector(const IUnknown *ipiPartUnk, 
                                          const int &iConnectorNumber, 
                                          IUnknown *&opiPartConnector)
{
  cout <<"============================================================"<< endl;
  cout <<"===    CAACloPlacePart::GetPartConnector                 ==="<< endl;
  cout <<"============================================================"<< endl;
  cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;
  cout <<" Connector number " << iConnectorNumber << endl;

  opiPartConnector = NULL;
  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATIPspPhysicalProduct *piPhysProd = NULL;
  CATIUnknownList *piListCtrs = NULL;

  int NumOfCtrs = 0;
  unsigned int ListSize = 0;

  CATTry 
  {
    if (ipiPartUnk && 
        SUCCEEDED(((IUnknown*)ipiPartUnk)->QueryInterface(IID_CATIPspPhysicalProduct,(void**)&piPhysProd)))
    {
  
      //----------------------------------------------------------------------
      //  List part connectors
      //----------------------------------------------------------------------    
      if ( SUCCEEDED(piPhysProd->ListConnectors(NULL,&piListCtrs))
           && NULL != piListCtrs )
      {
         //  Get list of part connectors
         if ( SUCCEEDED(piListCtrs->Count(&ListSize)) ) NumOfCtrs = ListSize;
         cout << "Number of connectors on part: " << NumOfCtrs << endl;
         if (0 < iConnectorNumber && 
             NumOfCtrs >= iConnectorNumber)
         {
           rc = piListCtrs->Item(iConnectorNumber-1,&opiPartConnector);
         } // End if valid ctr number.
       } // End if valid list of part ctrs.
    } // End if valid input part.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::GetPartConnector *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piPhysProd) {piPhysProd->Release(); piPhysProd = NULL;}
  if (piListCtrs) {piListCtrs->Release(); piListCtrs = NULL;}

  cout <<" opiPartConnector = " << opiPartConnector << endl;
  cout << "CAACloPlacePart::GetPartConnector rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Get location data for a part connector.
//=============================================================================
HRESULT CAACloPlacePart::GetPartConnectorData(const IUnknown *ipiPartUnk, 
                                              const int &iConnectorNumber, 
                                              IUnknown *ipiRelAxisUnk, 
                                              CATMathPoint &oCtrPosition, 
                                              CATMathDirection &oCtrAlign, 
                                              CATMathDirection &oCtrUp)
{
  cout <<"============================================================"<< endl;
  cout <<"===    CAACloPlacePart::GetPartConnectorData             ==="<< endl;
  cout <<"============================================================"<< endl;
  cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;
  cout <<" Connector number " << iConnectorNumber << endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATIMovable *piRelAxis = NULL;
  IUnknown *piCtrUnk = NULL;
  CATIPspPartConnector *piPartCntr = NULL;

  CATTry 
  {
    rc = GetPartConnector(ipiPartUnk, 
                          iConnectorNumber, 
                          piCtrUnk);
    if (SUCCEEDED(rc) && piCtrUnk)
    {
  
      if (ipiRelAxisUnk)
        ((IUnknown*)ipiRelAxisUnk)->QueryInterface(IID_CATIMovable,(void**)&piRelAxis);
      cout << "piRelAxis = " << piRelAxis << endl;

      if (SUCCEEDED(piCtrUnk->QueryInterface(IID_CATIPspPartConnector,(void**)&piPartCntr)))
      {
        rc = CATReturnSuccess;

        //  Get connector position
        piPartCntr->GetPosition(piRelAxis,oCtrPosition);

        //  Get connector alignment direction
        piPartCntr->GetAlignmentDirection(piRelAxis,oCtrAlign);

        //  Get connector up direction
        piPartCntr->GetUpDirection(piRelAxis,oCtrUp);

        if (piPartCntr) {piPartCntr->Release(); piPartCntr = NULL;}
      } // End if valid part connector.
      if (piCtrUnk) {piCtrUnk->Release(); piCtrUnk = NULL;}
    } // End if valid part ctr.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::GetPartConnectorData *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piRelAxis) {piRelAxis->Release(); piRelAxis = NULL;}
  if (piCtrUnk) {piCtrUnk->Release(); piCtrUnk = NULL;}
  if (piPartCntr) {piPartCntr->Release(); piPartCntr = NULL;}

  cout << "oCtrPosition = " << oCtrPosition << endl;
  cout << "oCtrAlign = " << oCtrAlign << endl;
  cout << "oCtrUp = " << oCtrUp << endl;
  cout << "CAACloPlacePart::GetPartConnectorData rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Get part connected to a part ctr.
//=============================================================================
HRESULT CAACloPlacePart::GetConnectedPart(const IUnknown *ipiPartUnk, 
                                          const int &iConnectorNumber, 
                                          IUnknown *&opiConnectedCtr, 
                                          IUnknown *&opiConnectedPart)
{
  cout <<"============================================================"<< endl;
  cout <<"===    CAACloPlacePart::GetConnectedPart                 ==="<< endl;
  cout <<"============================================================"<< endl;
  cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;
  cout <<" Connector number " << iConnectorNumber << endl;

  opiConnectedCtr = NULL;
  opiConnectedPart = NULL;
  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  IUnknown *piCtrUnk = NULL;
  CATIPspConnection *piPspConnection = NULL;
  CATIPspConnector *piPspConnector = NULL;
  CATIUnknownList *piListConnections  = NULL;
  IUnknown *piUnk = NULL;
  CATIUnknownList *piListCtr  = NULL;
  CATIPspConnector *piPspConnectedCtr = NULL;
  CATIPspConnectable *piPspConnectedPart = NULL;

  CATTry 
  {
    rc = GetPartConnector(ipiPartUnk, 
                          iConnectorNumber, 
                          piCtrUnk);
    if (SUCCEEDED(rc) && piCtrUnk)
    {
      // Get connected objects.
      if (SUCCEEDED(piCtrUnk->QueryInterface(IID_CATIPspConnector,(void**)&piPspConnector)))
      {
        if ( SUCCEEDED(piPspConnector->ListConnections (NULL, &piListConnections)) &&
             piListConnections )          
        {
          cout << "piListConnections = " << piListConnections << endl;
          // Get a connection 
          unsigned int numCnx = 0;
          piListConnections->Count(&numCnx);
          for ( unsigned int iiCnx = 0; iiCnx < numCnx; iiCnx++ )
          {
            if ( SUCCEEDED(piListConnections->Item(iiCnx,&piUnk)) && (NULL != piUnk) )
            {
              piUnk->QueryInterface(IID_CATIPspConnection,(void**)&piPspConnection);
              cout << "piPspConnection = " << piPspConnection << endl;
              if (piUnk) {piUnk->Release(); piUnk = NULL;}
              if (piPspConnection && 
                  SUCCEEDED(piPspConnector->ListConnectedCntrs (piPspConnection, &piListCtr)) &&
                  piListCtr )          
              {
                unsigned int numCtr = 0;
                piListCtr->Count(&numCtr);
                for ( unsigned int iiCtr = 0; iiCtr < numCtr; iiCtr++ )
                {
                  if ( SUCCEEDED(piListCtr->Item(iiCtr,&piUnk)) && (NULL != piUnk) )
                  {
                    piUnk->QueryInterface(IID_CATIPspConnector,(void**)&piPspConnectedCtr);
                    cout << "piPspConnectedCtr = " << piPspConnectedCtr << endl;
                    if (piUnk) {piUnk->Release(); piUnk = NULL;}
                    if (piPspConnectedCtr)
                    {
                      piPspConnectedCtr->GetAssociatedConnectable(&piPspConnectedPart);
                      cout << "piPspConnectedPart = " << piPspConnectedPart << endl;
                      if (piPspConnectedPart)
                      {
                        piPspConnectedCtr->QueryInterface(IID_IUnknown,(void**)&opiConnectedCtr);
                        piPspConnectedPart->QueryInterface(IID_IUnknown,(void**)&opiConnectedPart);
                        break;
                      }
                      if (piPspConnectedCtr) {piPspConnectedCtr->Release(); piPspConnectedCtr = NULL;}
                      if (piPspConnectedPart) {piPspConnectedPart->Release(); piPspConnectedPart = NULL;}
                    }
                  } // End if valid ctr list item.
                } // End loop on connected ctrs.
                if (piListCtr) {piListCtr->Release(); piListCtr = NULL;}
              } // End if valid list of ctrs.
              if (piPspConnection) {piPspConnection->Release(); piPspConnection = NULL;}
            } // End if valid cnx list item.
          } // End loop on connections.
          if (piListConnections) {piListConnections->Release(); piListConnections = NULL;}
        } // End if valid list of connections.
      } // End if valid psp ctr
      if (piCtrUnk) {piCtrUnk->Release(); piCtrUnk = NULL;}
    } // End if valid ctr.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::GetConnectedPart *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piCtrUnk) {piCtrUnk->Release(); piCtrUnk = NULL;}
  if (piPspConnection) {piPspConnection->Release(); piPspConnection = NULL;}
  if (piPspConnector) {piPspConnector->Release(); piPspConnector = NULL;}
  if (piListConnections) {piListConnections->Release(); piListConnections = NULL;}
  if (piUnk) {piUnk->Release(); piUnk = NULL;}
  if (piListCtr) {piListCtr->Release(); piListCtr = NULL;}
  if (piPspConnectedCtr) {piPspConnectedCtr->Release(); piPspConnectedCtr = NULL;}
  if (piPspConnectedPart) {piPspConnectedPart->Release(); piPspConnectedPart = NULL;}

  cout <<" opiConnectedCtr = " << opiConnectedCtr << endl;
  cout <<" opiConnectedPart = " << opiConnectedPart << endl;
  if (opiConnectedCtr && opiConnectedCtr)
    rc = CATReturnSuccess;
  cout << "CAACloPlacePart::GetConnectedPart rc = " << rc << endl;
  return rc;
}

#define PointTolerance  0.01 // mm
int ArePointsEqual(const CATMathPoint &iPoint0, 
                   const CATMathPoint &iPoint1)
{
  return (iPoint0.DistanceTo(iPoint1) <= PointTolerance);
}

int AreVectorsEqual(const CATMathVector &iVector0, 
                    const CATMathVector &iVector1)
{
  return ArePointsEqual(CATMathO+iVector0, CATMathO+iVector1);
}

//=============================================================================
//  Test location data for a part connector.
//=============================================================================
HRESULT CAACloPlacePart::TestPartConnectorData(const IUnknown *ipiPartUnk, 
                                               const int &iConnectorNumber, 
                                               IUnknown *ipiRelAxisUnk, 
                                               const CATMathPoint &iCtrPosition, 
                                               const CATMathDirection &iCtrAlign, 
                                               const CATMathDirection &iCtrUp)
{
  cout <<"============================================================"<< endl;
  cout <<"===    CAACloPlacePart::TestPartConnectorData            ==="<< endl;
  cout <<"============================================================"<< endl;
  cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;
  cout <<" Connector number " << iConnectorNumber << endl;
  cout << "iCtrPosition = " << iCtrPosition << endl;
  cout << "iCtrAlign = " << iCtrAlign << endl;
  cout << "iCtrUp = " << iCtrUp << endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATIMovable *piRelAxis = NULL;
  IUnknown *piCtrUnk = NULL;
  CATIPspPartConnector *piPartCntr = NULL;

  CATMathPoint ctrPosition;
  CATMathDirection ctrAlign;
  CATMathDirection ctrUp;

  CATTry 
  {
    if (SUCCEEDED(GetPartConnectorData(ipiPartUnk, 
                                       iConnectorNumber, 
                                       ipiRelAxisUnk, 
                                       ctrPosition, 
                                       ctrAlign, 
                                       ctrUp)))
    {
      cout << "ctrPosition = " << ctrPosition << endl;
      cout << "ctrAlign = " << ctrAlign << endl;
      cout << "ctrUp = " << ctrUp << endl;

      if (ArePointsEqual(ctrPosition, iCtrPosition) && 
          AreVectorsEqual(ctrAlign, iCtrAlign) && 
          AreVectorsEqual(ctrUp, ctrUp))
      {
        rc = CATReturnSuccess;
      }
  
    } // End if get valid part ctr data succeeded.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::TestPartConnectorData *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piRelAxis) {piRelAxis->Release(); piRelAxis = NULL;}
  if (piCtrUnk) {piCtrUnk->Release(); piCtrUnk = NULL;}
  if (piPartCntr) {piPartCntr->Release(); piPartCntr = NULL;}

  cout << "CAACloPlacePart::TestPartConnectorData rc = " << rc << endl;
  return rc;
}

int AreObjectsEqual(const IUnknown *ipiObject0, 
                    const IUnknown *ipiObject1)
{
  int rc = 0;

  IUnknown *piObjectUnk0 = NULL;
  IUnknown *piObjectUnk1 = NULL;

  if (ipiObject0 == ipiObject1)
  {
    rc = 1;
  }
  else if (!ipiObject0 || !ipiObject1)
  {
    rc = 0;
  }
  else if (SUCCEEDED(((IUnknown*)ipiObject0)->QueryInterface(IID_IUnknown,(void**)&piObjectUnk0)) && 
           SUCCEEDED(((IUnknown*)ipiObject1)->QueryInterface(IID_IUnknown,(void**)&piObjectUnk1)) && 
           piObjectUnk0 == piObjectUnk1)
  {
    rc = 1;
  }

  if (piObjectUnk0) {piObjectUnk0->Release(); piObjectUnk0 = NULL;}
  if (piObjectUnk1) {piObjectUnk1->Release(); piObjectUnk1 = NULL;}

  return rc;
}

//=============================================================================
//  Test part connected to a part ctr.
//=============================================================================
HRESULT CAACloPlacePart::TestConnectedPart(const IUnknown *ipiPartUnk, 
                                           const int &iConnectorNumber, 
                                           const IUnknown *ipiConnectedPart, 
                                           const int &iConnectedConnectorNumber)
{
  cout <<"============================================================"<< endl;
  cout <<"===    CAACloPlacePart::TestConnectedPart                ==="<< endl;
  cout <<"============================================================"<< endl;
  cout <<" Part: " << ipiPartUnk << ": " << GetObjectName(ipiPartUnk) << endl;
  cout <<" Connector number " << iConnectorNumber << endl;
  cout <<" ipiConnectedPart = " << ipiConnectedPart << endl;
  cout <<" iConnectedConnectorNumber = " << iConnectedConnectorNumber << endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  IUnknown *piConnectedCtr = NULL;
  IUnknown *piConnectedPart = NULL;
  IUnknown *piConnectedCtrExpected = NULL;

  CATTry 
  {
    if (SUCCEEDED(GetConnectedPart(ipiPartUnk, 
                                   iConnectorNumber, 
                                   piConnectedCtr, 
                                   piConnectedPart)) && 
        piConnectedCtr && 
        piConnectedPart && 
        AreObjectsEqual(piConnectedPart, ipiConnectedPart))
    { 
      cout <<" piConnectedCtr = " << piConnectedCtr << endl;
      if (SUCCEEDED(GetPartConnector(ipiConnectedPart, 
                                     iConnectedConnectorNumber, 
                                     piConnectedCtrExpected)) && 
          piConnectedCtrExpected)
      {
        cout <<" piConnectedCtrExpected = " << piConnectedCtrExpected << endl;
        if (AreObjectsEqual(piConnectedCtr, piConnectedCtrExpected))
          rc = CATReturnSuccess;
      }
    } // End if valid ctr.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::TestConnectedPart *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piConnectedCtr) {piConnectedCtr->Release(); piConnectedCtr = NULL;}
  if (piConnectedPart) {piConnectedPart->Release(); piConnectedPart = NULL;}
  if (piConnectedCtrExpected) {piConnectedCtrExpected->Release(); piConnectedCtrExpected = NULL;}

  cout << "CAACloPlacePart::TestConnectedPart rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Place parts in space.
//=============================================================================
HRESULT CAACloPlacePart::PlacePartInSpace()
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloPlacePart::PlacePartInSpace              ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATObject *piAppObject = NULL;
  CATIPspPlacePartOnRun *piPlacePart = NULL;
  IUnknown *piReferencePart = NULL;
  CATIProduct *piParentProduct = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  IUnknown *piInstancePart = NULL;

  CATUnicodeString uCatalogPartName = "";
  CATUnicodeString uPlacePartErrorMessage;
  CATUnicodeString uStandard = "SSTL";
  CATUnicodeString uSpecName = "";
  CATUnicodeString uPartType;
  CATUnicodeString uPartNumber;
  CATUnicodeString uFunctionType;
  CATUnicodeString uPlacedPartID;
  CATMathDirection upDirection;
  CATMathDirection horizontalOrientation;
  CATMathPoint position;
  CATMathPoint ctrPosition;
  CATMathDirection ctrAlign;
  CATMathDirection ctrUp;

  CATTry 
  {
    // Get application object.
    piAppObject = new CATObject("CATTubing");
    cout << "piAppObject = " << piAppObject << endl;

    if (piAppObject && 
        SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
    {
      cout << "piPlacePart = " << piPlacePart << endl;

      piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
      cout << "piParentProduct = " << piParentProduct << endl;

      piLogicalLine = GetALogicalLine(piParentProduct);
      cout << "piLogicalLine = " << piLogicalLine << endl;

      // Get reference part
      //uPartType = "CATTubControlValve";
      uPartType = ""; // Null string option used to search entire catalog.
      cout << "Part type null" << endl;
      uPartNumber = "V_BALL-TF-16S";
      rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                     uSpecName, 
                                                     uPartType, 
                                                     uPartNumber, 
                                                     piParentProduct, 
                                                     piReferencePart, 
                                                     uCatalogPartName);
      cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

      if (SUCCEEDED(rc) && 
          piReferencePart)
      {
        // Place part in space.
        uFunctionType = "CATTubControlValveFunction";
        uPlacedPartID = ""; // Null string uses name generated by PP engine
        upDirection.SetCoord(0, 0, 1); // Part up direction parallel to z-axis.
        horizontalOrientation.SetCoord(0,1,0); // Align part parallel to y-axis.
        position.SetCoord(1000,2000,4000); // Position part at (1000, 2000, 4000) in mm.
        rc = piPlacePart->PlacePartInSpace (uStandard, 
                                            uFunctionType, 
                                            piReferencePart, 
                                            piParentProduct, 
                                            piLogicalLine, 
                                            uPlacedPartID, 
                                            upDirection, 
                                            horizontalOrientation, 
                                            position, 
                                            piInstancePart);
        cout << "piInstancePart = " << piInstancePart << endl;

        if (piInstancePart)
        {
          // Set catalog part name
          piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

          // Test part connectors.
          ctrPosition.SetCoord(1014.61,2000,4000);
          ctrAlign.SetCoord(1,0,0);
          ctrUp.SetCoord(0,0,1);
          rc = TestPartConnectorData(piInstancePart, 
                                     1, 
                                     piParentProduct, 
                                     ctrPosition, 
                                     ctrAlign, 
                                     ctrUp);
          if (SUCCEEDED(rc))
          {
            ctrPosition.SetCoord(985.395,2000,4000);
            ctrAlign.SetCoord(-1,0,0);
            ctrUp.SetCoord(0,0,1);
            rc = TestPartConnectorData(piInstancePart, 
                                       2, 
                                       piParentProduct, 
                                       ctrPosition, 
                                       ctrAlign, 
                                       ctrUp);
          }
        }
        else
        {
          rc = CATReturnFailure;
        }
      }
      if (FAILED(rc))
      {
        piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
        cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
      }
    } // End if valid place part object.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::PlacePartInSpace *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piAppObject) {piAppObject->Release(); piAppObject = NULL;}
  if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
  if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
  if (piParentProduct) {piParentProduct->Release(); piParentProduct = NULL;}
  if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}
  if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}

  cout << "CAACloPlacePart::PlacePartInSpace rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Place string parts in space.
//=============================================================================
HRESULT CAACloPlacePart::RouteStringPartInSpace()
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloPlacePart::RouteStringPartInSpace        ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATObject *piAppObject = NULL;
  CATIPspPlacePartOnRun *piPlacePart = NULL;
  IUnknown *piReferencePart = NULL;
  CATIProduct *piParentProduct = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  CATIUnknownList *piListPoints = NULL;
  IUnknown *piInstancePart = NULL;
  CATIAProducts *piParentProducts = NULL;
  CATIAProduct *piPartForPointsProduct = NULL;
  CATBaseDispatch *piPartForPointsShape = NULL;
  CATIAPartDocument *piPartForPointsDoc = NULL;
  CATIAPart *piPartForPoints = NULL;
  CATIAFactory *piShapeFactory = NULL;
  CATIAHybridShapeFactory *piHybridShapeFactory = NULL;
  CATIAHybridShapePointCoord *piPoint = NULL;
  CATIUnknownListImpl *piListImpl = NULL;

  CATUnicodeString uCatalogPartName = "";
  CATUnicodeString uPlacePartErrorMessage;
  CATUnicodeString uStandard = "SSTL";
  CATUnicodeString uSpecName = "";
  CATUnicodeString uPartType;
  CATUnicodeString uPartNumber;
  CATUnicodeString uDocumentType;
  CATBSTR documentTypeBSTR;
  CATBSTR partNumberBSTR;
  CATUnicodeString uFunctionType;
  CATUnicodeString uPlacedPartID;
  CATMathDirection firstPointUpDirection;
  CATListOfDouble listBendRadii;
  CATMathPoint ctrPosition;
  CATMathDirection ctrAlign;
  CATMathDirection ctrUp;

  CATTry 
  {
    // Get application object.
    piAppObject = new CATObject("CATTubing");
    cout << "piAppObject = " << piAppObject << endl;

    if (piAppObject && 
        SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
    {
      cout << "piPlacePart = " << piPlacePart << endl;

      piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
      cout << "piParentProduct = " << piParentProduct << endl;

      piLogicalLine = GetALogicalLine(piParentProduct);
      cout << "piLogicalLine = " << piLogicalLine << endl;

      // Get reference part
      uPartType = "CATTubBendableTube";
      uPartNumber = "TUBE-BENDABLE-TIV-16S";
      rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                     uSpecName, 
                                                     uPartType, 
                                                     uPartNumber, 
                                                     piParentProduct, 
                                                     piReferencePart, 
                                                     uCatalogPartName);
      cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

      if (SUCCEEDED(rc) && 
          piReferencePart)
      {
        // Create points for bendable routing.
        if (piParentProduct && 
            SUCCEEDED(piParentProduct->QueryInterface(IID_CATIAProducts,(void**)&piParentProducts)))
        {
          cout << "piParentProducts = " << piParentProducts << endl;

          // Create part to hold points.
          uDocumentType = "Part";
          uDocumentType.ConvertToBSTR(&documentTypeBSTR);
          uPartNumber = "PartForPointsTubing";
          uPartNumber.ConvertToBSTR(&partNumberBSTR);
          HRESULT rcPointsPart = piParentProducts->AddNewComponent(documentTypeBSTR, 
                                                                   partNumberBSTR, 
                                                                   piPartForPointsProduct);
          cout << "rcPointsPart = " << rcPointsPart << endl;
          cout << "piPartForPointsProduct = " << piPartForPointsProduct << endl;
          if (piPartForPointsProduct)
          {
            piPartForPointsProduct->GetMasterShapeRepresentation(TRUE, piPartForPointsShape);
            cout << "piPartForPointsShape = " << piPartForPointsShape << endl;
            if (piPartForPointsShape && 
                SUCCEEDED(piPartForPointsShape->QueryInterface(IID_CATIAPartDocument,(void**)&piPartForPointsDoc)))
            {
              cout << "piPartForPointsDoc = " << piPartForPointsDoc << endl;
              piPartForPointsDoc->get_Part(piPartForPoints);
              cout << "piPartForPoints = " << piPartForPoints << endl;
              if (piPartForPoints)
              {
                piPartForPoints->get_HybridShapeFactory(piShapeFactory);
                if (piShapeFactory)
                  piShapeFactory->QueryInterface(IID_CATIAHybridShapeFactory,(void**)&piHybridShapeFactory);
                cout << "piHybridShapeFactory = " << piHybridShapeFactory << endl;
                if (piHybridShapeFactory)
                {
                  piListImpl = new CATIUnknownListImpl();
                  if (piListImpl)
                    piListImpl->QueryInterface (IID_CATIUnknownList,(void**)&piListPoints);         
                  cout << "piListPoints = " << piListPoints << endl;
                  if (piListPoints)
                  {
                    double points[4][3] = { {-1500.0, -1000.0, 0.0}, 
                                            {-2500.0, -1000.0, 0.0}, 
                                            {-2500.0, 500.0, 0.0}, 
                                            {-3500.0, 500.0, 0.0} };
                    for (unsigned int iiPoint = 0; iiPoint < 4; iiPoint++)
                    {
                      cout << "iiPoint = " << iiPoint << endl;
                      piHybridShapeFactory->AddNewPointCoord(points[iiPoint][0], 
                                                             points[iiPoint][1], 
                                                             points[iiPoint][2], 
                                                             piPoint);
                      cout << "piPoint = " << piPoint << endl;
                      piListPoints->Add(iiPoint, piPoint);
                      if (piPoint) {piPoint->Release(); piPoint = NULL;}
                    } // End loop on points.
                  } // End valid list of points.
                } // End valid shape factory.
              } // End valid part for points.
            } // End valid shape.
          } // End valid part for points product.
        } // End valid parent product.

        // Place part in space.
        uFunctionType = "CATTubTubeFunction";
        uPlacedPartID = "TestTubeWithBends";
        firstPointUpDirection.SetCoord(0, 0, 1); // Up direction parallel to z-axis.
        listBendRadii.RemoveAll();
        listBendRadii.Append(25.4); // Bend radius in mm (1in).
        listBendRadii.Append(25.4);
        listBendRadii.Append(25.4);
        listBendRadii.Append(25.4);
        rc = piPlacePart->RouteStringPartInSpace (uStandard, 
                                                  uFunctionType, 
                                                  piReferencePart, 
                                                  piParentProduct, 
                                                  piLogicalLine, 
                                                  uPlacedPartID, 
                                                  firstPointUpDirection, 
                                                  piListPoints, 
                                                  listBendRadii, 
                                                  piInstancePart);
        cout << "piInstancePart = " << piInstancePart << endl;

        if (piInstancePart)
        {
          // Set catalog part name
          piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

          // Test part connectors.
          ctrPosition.SetCoord(-1500,-1000,0);
          ctrAlign.SetCoord(1,0,0);
          ctrUp.SetCoord(0,0,1);
          rc = TestPartConnectorData(piInstancePart, 
                                     1, 
                                     piParentProduct, 
                                     ctrPosition, 
                                     ctrAlign, 
                                     ctrUp);
          if (SUCCEEDED(rc))
          {
            ctrPosition.SetCoord(-3500,500,0);
            ctrAlign.SetCoord(-1,0,0);
            ctrUp.SetCoord(0,0,1);
            rc = TestPartConnectorData(piInstancePart, 
                                       2, 
                                       piParentProduct, 
                                       ctrPosition, 
                                       ctrAlign, 
                                       ctrUp);
          }
        }
        else
        {
          rc = CATReturnFailure;
        }
      }
      if (FAILED(rc))
      {
        piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
        cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
      }
    } // End if valid place part object.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::RouteStringPartInSpace *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piAppObject) {piAppObject->Release(); piAppObject = NULL;}
  if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
  if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
  if (piParentProduct) {piParentProduct->Release(); piParentProduct = NULL;}
  if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}
  if (piListPoints) {piListPoints->Release(); piListPoints = NULL;}
  if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
  if (piParentProducts) {piParentProducts->Release(); piParentProducts = NULL;}
  if (piPartForPointsProduct) {piPartForPointsProduct->Release(); piPartForPointsProduct = NULL;}
  if (piPartForPointsShape) {piPartForPointsShape->Release(); piPartForPointsShape = NULL;}
  if (piPartForPointsDoc) {piPartForPointsDoc->Release(); piPartForPointsDoc = NULL;}
  if (piPartForPoints) {piPartForPoints->Release(); piPartForPoints = NULL;}
  if (piShapeFactory) {piShapeFactory->Release(); piShapeFactory = NULL;}
  if (piHybridShapeFactory) {piHybridShapeFactory->Release(); piHybridShapeFactory = NULL;}
  if (piPoint) {piPoint->Release(); piPoint = NULL;}
  if (piListImpl) {piListImpl->Release(); piListImpl = NULL;}

  cout << "CAACloPlacePart::RouteStringPartInSpace rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Place parts on run segments.
//=============================================================================
HRESULT CAACloPlacePart::PlacePartOnRunSegment()
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloPlacePart::PlacePartOnRunSegment         ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATObject *piAppObject = NULL;
  CATIPspPlacePartOnRun *piPlacePart = NULL;
  CATIProduct *piParentProduct = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  CATIArrSegmentsString *piRun = NULL;
  IUnknown *piReferencePart = NULL;
  CATIArrSegment *piSegment = NULL;
  IUnknown *piInstancePart = NULL;
  IUnknown *piConnectedPart = NULL;
  IUnknown *piInstanceUnion = NULL;

  CATUnicodeString uCatalogPartName = "";
  CATUnicodeString uPlacePartErrorMessage;
  CATListValCATBaseUnknown_var listOfSegments;
  CATUnicodeString uStandard = "SSTL";
  CATUnicodeString uSpecName = "";
  CATUnicodeString uPartType;
  CATUnicodeString uPartNumber;
  CATUnicodeString uFunctionType;
  CATUnicodeString uPlacedPartID;
  CATMathPoint position;
  CATMathPoint ctrPosition;
  CATMathDirection ctrAlign;
  CATMathDirection ctrUp;
  CATIArrSegment_var spSegment;

  CATTry 
  {
    // Get application object.
    piAppObject = new CATObject("CATTubing");
    cout << "piAppObject = " << piAppObject << endl;

    if (piAppObject && 
        SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
    {
      cout << "piPlacePart = " << piPlacePart << endl;

      piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
      cout << "piParentProduct = " << piParentProduct << endl;

      //piLogicalLine = GetALogicalLine(piParentProduct);
      cout << "piLogicalLine = " << piLogicalLine << endl;

      piRun = (CATIArrSegmentsString*)GetChildObject(IID_CATIArrSegmentsString, "Run-0043", piParentProduct);
      cout << "piRun = " << piRun << endl;

      if (piRun)
      {
        piRun->ListSegments(listOfSegments);
        cout << "listOfSegments.Size() = " << listOfSegments.Size() << endl;

        do
        { // Dummy loop to allow easy exit on fail.
          // ==============================================================================
          // Place union on segment
          // ==============================================================================
          // Get reference part
          uPartType = "CATTubUnion";
          uPartNumber = "UNION-BULKHEAD-FFSM-16";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {

            if (listOfSegments.Size() >= 1)
            {
              spSegment = listOfSegments[1];
              if (!!spSegment)
                spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);
              cout << "piSegment = " << piSegment << endl;
            }

            if (piSegment)
            {
              // Place part on run segment.
              uFunctionType = "CATTubTubeFunction";
              uPlacedPartID = ""; // Null string uses name generated by PP engine
              position.SetCoord(-200,-800,0); // in mm.
              rc = piPlacePart->PlacePartOnRunSegment (uStandard, 
                                                       uFunctionType, 
                                                       piReferencePart, 
                                                       piSegment, 
                                                       piLogicalLine, 
                                                       uPlacedPartID, 
                                                       position, 
                                                       piInstancePart);
              cout << "piInstancePart = " << piInstancePart << endl;

              if (piInstancePart)
              {
                // Set catalog part name
                piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

                piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceUnion);

                // Test part connectors.
                ctrPosition.SetCoord(-171.006,-800,0);
                ctrAlign.SetCoord(1,0,0);
                ctrUp.SetCoord(0,0,1);
                cout << "Union after placement" << endl;
                rc = TestPartConnectorData(piInstancePart, 
                                           1, 
                                           piParentProduct, 
                                           ctrPosition, 
                                           ctrAlign, 
                                           ctrUp);
                if (SUCCEEDED(rc))
                {
                  ctrPosition.SetCoord(-228.994,-800,0);
                  ctrAlign.SetCoord(-1,0,0);
                  ctrUp.SetCoord(0,0,1);
                  rc = TestPartConnectorData(piInstancePart, 
                                             2, 
                                             piParentProduct, 
                                             ctrPosition, 
                                             ctrAlign, 
                                             ctrUp);
                  // ------------------------------------------
                  // Test flip of union.
                  // ------------------------------------------
                  if (SUCCEEDED(rc))
                  {
                    // Flip first time.
                    rc = piPlacePart->FlipPlacedPart(piInstancePart);
                    if (SUCCEEDED(rc))
                    {
                      cout << "Union after first flip" << endl;
                      // Test part connectors.
                      ctrPosition.SetCoord(-171.006,-800,0);
                      ctrAlign.SetCoord(1,0,0);
                      ctrUp.SetCoord(0,0,1);
                      rc = TestPartConnectorData(piInstancePart, 
                                                 2, 
                                                 piParentProduct, 
                                                 ctrPosition, 
                                                 ctrAlign, 
                                                 ctrUp);
                      if (SUCCEEDED(rc))
                      {
                        ctrPosition.SetCoord(-228.994,-800,0);
                        ctrAlign.SetCoord(-1,0,0);
                        ctrUp.SetCoord(0,0,1);
                        rc = TestPartConnectorData(piInstancePart, 
                                                   1, 
                                                   piParentProduct, 
                                                   ctrPosition, 
                                                   ctrAlign, 
                                                   ctrUp);
                        if (SUCCEEDED(rc))
                        {
                          // Flip second time. Union should be back to original flip
                          rc = piPlacePart->FlipPlacedPart(piInstancePart);
                          if (SUCCEEDED(rc))
                          {
                            cout << "Union after second flip" << endl;
                            // Test part connectors.
                            ctrPosition.SetCoord(-171.006,-800,0);
                            ctrAlign.SetCoord(1,0,0);
                            ctrUp.SetCoord(0,0,1);
                            rc = TestPartConnectorData(piInstancePart, 
                                                       1, 
                                                       piParentProduct, 
                                                       ctrPosition, 
                                                       ctrAlign, 
                                                       ctrUp);
                            if (SUCCEEDED(rc))
                            {
                              ctrPosition.SetCoord(-228.994,-800,0);
                              ctrAlign.SetCoord(-1,0,0);
                              ctrUp.SetCoord(0,0,1);
                              rc = TestPartConnectorData(piInstancePart, 
                                                         2, 
                                                         piParentProduct, 
                                                         ctrPosition, 
                                                         ctrAlign, 
                                                         ctrUp);
                            } // End if connector test succeeded
                          } // End if flip succeeded
                        } // End if connector test succeeded.
                      } // End if connector test succeeded
                    } // End if flip succeeded
                  } // End if connector test succeeded.
                }
              }
              else
              {
                rc = CATReturnFailure;
              }
            } // End if valid segment.
          } // End if valid reference part.
          if (FAILED(rc)) break;

          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piSegment) {piSegment->Release(); piSegment = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}

          // ==============================================================================
          // Place bendable on segment
          // ==============================================================================
          // Get reference part
          uPartType = "CATTubBendableTube";
          uPartNumber = "TUBE-BENDABLE-TIV-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {

            if (listOfSegments.Size() >= 2)
            {
              spSegment = listOfSegments[2];
              if (!!spSegment)
                spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);
              cout << "piSegment = " << piSegment << endl;
            }

            if (piSegment)
            {
              // Place part on run segment.
              uFunctionType = "CATTubTubeFunction";
              uPlacedPartID = ""; // Null string uses name generated by PP engine
              position.SetCoord(-800,-600,0); // in mm.
              rc = piPlacePart->PlacePartOnRunSegment (uStandard, 
                                                       uFunctionType, 
                                                       piReferencePart, 
                                                       piSegment, 
                                                       piLogicalLine, 
                                                       uPlacedPartID, 
                                                       position, 
                                                       piInstancePart);
              cout << "piInstancePart = " << piInstancePart << endl;

              if (piInstancePart)
              {
                // Set catalog part name
                piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

                // Test part connectors.
                ctrPosition.SetCoord(-228.994,-800,0);
                ctrAlign.SetCoord(1,0,0);
                ctrUp.SetCoord(0,0,1);
                rc = TestPartConnectorData(piInstancePart, 
                                           1, 
                                           piParentProduct, 
                                           ctrPosition, 
                                           ctrAlign, 
                                           ctrUp);
                if (SUCCEEDED(rc))
                {
                  rc = TestConnectedPart(piInstancePart, 
                                         1, 
                                         piInstanceUnion, 
                                         2);
                  if (SUCCEEDED(rc))
                  {
                    ctrPosition.SetCoord(-1600,-1500,0);
                    ctrAlign.SetCoord(1,0,0);
                    ctrUp.SetCoord(0,0,1);
                    rc = TestPartConnectorData(piInstancePart, 
                                               2, 
                                               piParentProduct, 
                                               ctrPosition, 
                                               ctrAlign, 
                                               ctrUp);

                  } // End if connected part test succeeded.
                } // End if ctr 1 test succeeded.
              } // End if valid instance part.
              else
              {
                rc = CATReturnFailure;
              }
            } // End if valid segment.
          } // End if valid reference part.
        } while (0); // End dummy loop for easy exit on fail.
      } // End if valid run.
      if (FAILED(rc))
      {
        piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
        cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
      }
    } // End if valid place part object.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::PlacePartOnRunSegment *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piAppObject) {piAppObject->Release(); piAppObject = NULL;}
  if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
  if (piParentProduct) {piParentProduct->Release(); piParentProduct = NULL;}
  if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}
  if (piRun) {piRun->Release(); piRun = NULL;}
  if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
  if (piSegment) {piSegment->Release(); piSegment = NULL;}
  if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
  if (piConnectedPart) {piConnectedPart->Release(); piConnectedPart = NULL;}
  if (piInstanceUnion) {piInstanceUnion->Release(); piInstanceUnion = NULL;}

  cout << "CAACloPlacePart::PlacePartOnRunSegment rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Place parts on run nodes.
//=============================================================================
HRESULT CAACloPlacePart::PlacePartOnRunNode()
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloPlacePart::PlacePartOnRunNode            ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATObject *piAppObject = NULL;
  CATIPspPlacePartOnRun *piPlacePart = NULL;
  CATIProduct *piParentProduct = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  CATIArrSegmentsString *piRun = NULL;
  IUnknown *piReferencePart = NULL;
  CATIArrNode *piNode = NULL;
  IUnknown *piInstancePart = NULL;
  IUnknown *piConnectedPart = NULL;
  IUnknown *piInstanceValve = NULL;
  IUnknown *piInstanceElbow = NULL;

  CATUnicodeString uCatalogPartName = "";
  CATUnicodeString uPlacePartErrorMessage;
  CATListValCATBaseUnknown_var listOfNodes;
  CATUnicodeString uStandard = "SSTL";
  CATUnicodeString uSpecName = "";
  CATUnicodeString uPartType;
  CATUnicodeString uPartNumber;
  CATUnicodeString uFunctionType;
  CATUnicodeString uPlacedPartID;
  CATMathPoint ctrPosition;
  CATMathDirection ctrAlign;
  CATMathDirection ctrUp;
  CATIArrNode_var spNode;

  CATTry 
  {
    // Get application object.
    piAppObject = new CATObject("CATTubing");
    cout << "piAppObject = " << piAppObject << endl;

    if (piAppObject && 
        SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
    {
      cout << "piPlacePart = " << piPlacePart << endl;

      piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
      cout << "piParentProduct = " << piParentProduct << endl;

      //piLogicalLine = GetALogicalLine(piParentProduct);
      cout << "piLogicalLine = " << piLogicalLine << endl;

      piRun = (CATIArrSegmentsString*)GetChildObject(IID_CATIArrSegmentsString, "Run-0044", piParentProduct);
      cout << "piRun = " << piRun << endl;

      if (piRun)
      {
        piRun->ListNodes(listOfNodes);
        cout << "listOfNodes.Size() = " << listOfNodes.Size() << endl;

        do
        { // Dummy loop to allow easy exit on fail.
          // ==============================================================================
          // Place valve on exterior node
          // ==============================================================================
          // Get reference part
          uPartType = "CATTubControlValve";
          uPartNumber = "V_BALL-TF-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {

            if (listOfNodes.Size() >= 1)
            {
              spNode = listOfNodes[1];
              if (!!spNode)
                spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);
              cout << "piNode = " << piNode << endl;
            }

            if (piNode)
            {
              uFunctionType = "CATTubControlValveFunction";
              uPlacedPartID = ""; // Null string uses name generated by PP engine
              rc = piPlacePart->PlacePartOnRunNode(uStandard, 
                                                   uFunctionType, 
                                                   piReferencePart, 
                                                   piNode, 
                                                   piLogicalLine, 
                                                   uPlacedPartID, 
                                                   piInstancePart);
              cout << "piInstancePart = " << piInstancePart << endl;

              if (piInstancePart)
              {
                // Set catalog part name
                piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

                piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceValve);

                // Test part connectors.
                ctrPosition.SetCoord(-500,800,0);
                ctrAlign.SetCoord(-1,0,0);
                ctrUp.SetCoord(0,0,1);
                rc = TestPartConnectorData(piInstancePart, 
                                           1, 
                                           piParentProduct, 
                                           ctrPosition, 
                                           ctrAlign, 
                                           ctrUp);
                if (SUCCEEDED(rc))
                {
                  ctrPosition.SetCoord(-470.79,800,0);
                  ctrAlign.SetCoord(1,0,0);
                  ctrUp.SetCoord(0,0,1);
                  rc = TestPartConnectorData(piInstancePart, 
                                             2, 
                                             piParentProduct, 
                                             ctrPosition, 
                                             ctrAlign, 
                                             ctrUp);
                }
              }
              else
              {
                rc = CATReturnFailure;
              }
            } // End if valid segment.
          } // End if valid reference part.
          if (FAILED(rc)) break;

          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piNode) {piNode->Release(); piNode = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}

          // ==============================================================================
          // Place elbow on interior node.
          // ==============================================================================
          // Get reference part
          uPartType = "CATTubNonReducingElbow";
          uPartNumber = "ELBOW-90-BULKHEAD-FFSM-16";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart,
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {

            if (listOfNodes.Size() >= 5)
            {
              spNode = listOfNodes[5];
              if (!!spNode)
                spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);
              cout << "piNode = " << piNode << endl;
            }

            if (piNode)
            {
              uFunctionType = "CATTubTubeFunction";
              uPlacedPartID = ""; // Null string uses name generated by PP engine
              rc = piPlacePart->PlacePartOnRunNode(uStandard, 
                                                   uFunctionType, 
                                                   piReferencePart, 
                                                   piNode, 
                                                   piLogicalLine, 
                                                   uPlacedPartID, 
                                                   piInstancePart);
              cout << "piInstancePart = " << piInstancePart << endl;

              if (piInstancePart)
              {
                // Set catalog part name
                piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

                piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstanceElbow);

                // Test part connectors.
                ctrPosition.SetCoord(-741.3,2000,1800);
                ctrAlign.SetCoord(-1,0,0);
                ctrUp.SetCoord(0,0,-1);
                rc = TestPartConnectorData(piInstancePart, 
                                           1, 
                                           piParentProduct, 
                                           ctrPosition, 
                                           ctrAlign, 
                                           ctrUp);
                if (SUCCEEDED(rc))
                {
                  ctrPosition.SetCoord(-700,2063.53,1800);
                  ctrAlign.SetCoord(0,1,0);
                  ctrUp.SetCoord(0,0,-1);
                  rc = TestPartConnectorData(piInstancePart, 
                                             2, 
                                             piParentProduct, 
                                             ctrPosition, 
                                             ctrAlign, 
                                             ctrUp);
                }
              }
              else
              {
                rc = CATReturnFailure;
              }
            } // End if valid segment.
          } // End if valid reference part.
          if (FAILED(rc)) break;

          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piNode) {piNode->Release(); piNode = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}

          // ==============================================================================
          // Place bendable on node.
          // ==============================================================================
          // Get reference part
          uPartType = "CATTubBendableTube";
          uPartNumber = "TUBE-BENDABLE-TIV-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {

            if (listOfNodes.Size() >= 2)
            {
              spNode = listOfNodes[2];
              if (!!spNode)
                spNode->QueryInterface(IID_CATIArrNode,(void**)&piNode);
              cout << "piNode = " << piNode << endl;
            }

            if (piNode)
            {
              uFunctionType = "CATTubTubeFunction";
              uPlacedPartID = ""; // Null string uses name generated by PP engine
              rc = piPlacePart->PlacePartOnRunNode(uStandard, 
                                                   uFunctionType, 
                                                   piReferencePart, 
                                                   piNode, 
                                                   piLogicalLine, 
                                                   uPlacedPartID, 
                                                   piInstancePart);
              cout << "piInstancePart = " << piInstancePart << endl;

              if (piInstancePart)
              {
                // Set catalog part name
                piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

                // Test part connectors.
                ctrPosition.SetCoord(-500,800,0);
                ctrAlign.SetCoord(1,0,0);
                ctrUp.SetCoord(0,0,1);
                rc = TestPartConnectorData(piInstancePart, 
                                           1, 
                                           piParentProduct, 
                                           ctrPosition, 
                                           ctrAlign, 
                                           ctrUp);
                if (SUCCEEDED(rc))
                {
                  rc = TestConnectedPart(piInstancePart, 
                                         1, 
                                         piInstanceValve, 
                                         1);
                  if (SUCCEEDED(rc))
                  {
                    ctrPosition.SetCoord(-741.3,2000,1800);
                    ctrAlign.SetCoord(1,0,0);
                    ctrUp.SetCoord(0,-1,0);
                    rc = TestPartConnectorData(piInstancePart, 
                                               2, 
                                               piParentProduct, 
                                               ctrPosition, 
                                               ctrAlign, 
                                               ctrUp);
                    if (SUCCEEDED(rc))
                    {
                      rc = TestConnectedPart(piInstancePart, 
                                             2, 
                                             piInstanceElbow, 
                                             1);
                    } // End if part ctr 2 test succeeded.
                  } // End if part ctr 1 connected part test succeeded
                } // End if part ctr 1 test succeeded.
              }
              else
              {
                rc = CATReturnFailure;
              }
            } // End if valid segment.
          } // End if valid reference part.

          // ==============================================================================
          // Test BreakAndTrimRuns and ConnectRunToPart
          // ==============================================================================
          IUnknown *opiRun1 = NULL;
          IUnknown *opiRun2 = NULL;

          rc = piPlacePart->BreakAndTrimRuns ( piInstanceElbow, 
                                               opiRun1,
                                               opiRun2);
          cout << "BreakAndTrimRuns rc = " << rc << endl;

          rc = piPlacePart->ConnectRunToPart ( opiRun2,piInstanceElbow);
          cout << "ConnectRunToPart rc = " << rc << endl;

          if (opiRun1) {opiRun1->Release(); opiRun1 = NULL;}
          if (opiRun2) {opiRun2->Release(); opiRun2 = NULL;}   

        } while (0); // End dummy loop for easy exit on fail.
      } // End if valid run.
      if (FAILED(rc))
      {
        piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
        cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
      }
    } // End if valid place part object.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::PlacePartOnRunNode *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piAppObject) {piAppObject->Release(); piAppObject = NULL;}
  if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
  if (piParentProduct) {piParentProduct->Release(); piParentProduct = NULL;}
  if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}
  if (piRun) {piRun->Release(); piRun = NULL;}
  if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
  if (piNode) {piNode->Release(); piNode = NULL;}
  if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
  if (piConnectedPart) {piConnectedPart->Release(); piConnectedPart = NULL;}
  if (piInstanceValve) {piInstanceValve->Release(); piInstanceValve = NULL;}
  if (piInstanceElbow) {piInstanceElbow->Release(); piInstanceElbow = NULL;}

  cout << "CAACloPlacePart::PlacePartOnRunNode rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Place parts on part connectors.
//=============================================================================
HRESULT CAACloPlacePart::PlacePartOnPartConnector()
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloPlacePart::PlacePartOnPartConnector      ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATObject *piAppObject = NULL;
  CATIPspPlacePartOnRun *piPlacePart = NULL;
  IUnknown *piReferencePart = NULL;
  CATIProduct *piParentProduct = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  IUnknown *piInstancePart = NULL;
  IUnknown *piInstancePartPrevious = NULL;
  IUnknown *piPlaceOnCtr = NULL;
  CATIArrSegmentsString *piRun = NULL;
  CATIArrSegment *piSegment = NULL;

  CATUnicodeString uCatalogPartName = "";
  CATUnicodeString uPlacePartErrorMessage;
  CATUnicodeString uStandard = "SSTL";
  CATUnicodeString uSpecName = "";
  CATUnicodeString uPartType;
  CATUnicodeString uPartNumber;
  CATUnicodeString uFunctionType;
  CATUnicodeString uPlacedPartID;
  CATMathDirection upDirection;
  CATMathDirection horizontalOrientation;
  CATMathPoint position;
  CATMathPoint ctrPosition;
  CATMathDirection ctrAlign;
  CATMathDirection ctrUp;
  CATListValCATBaseUnknown_var listOfSegments;
  CATIArrSegment_var spSegment;

  CATTry 
  {
    // Get application object.
    piAppObject = new CATObject("CATTubing");
    cout << "piAppObject = " << piAppObject << endl;

    if (piAppObject && 
        SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
    {
      cout << "piPlacePart = " << piPlacePart << endl;

      piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
      cout << "piParentProduct = " << piParentProduct << endl;

      piLogicalLine = GetALogicalLine(piParentProduct);
      cout << "piLogicalLine = " << piLogicalLine << endl;

      piRun = (CATIArrSegmentsString*)GetChildObject(IID_CATIArrSegmentsString, "Run-0044", piParentProduct);
      cout << "piRun = " << piRun << endl;

      if (piRun)
      {
        piRun->ListSegments(listOfSegments);
        cout << "listOfSegments.Size() = " << listOfSegments.Size() << endl;

        if (listOfSegments.Size() >= 5)
        {
          spSegment = listOfSegments[5];
          if (!!spSegment)
            spSegment->QueryInterface(IID_CATIArrSegment,(void**)&piSegment);
          cout << "piSegment = " << piSegment << endl;
        }
      } // End if valid run.

      if (piSegment)
      {
        do
        { // Dummy loop to allow easy exit on fail.


          // ==============================================================================
          // Place valve in space.
          // ==============================================================================
          // Get reference part
          uPartType = "CATTubControlValve";
          uPartNumber = "V_BALL-TF-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {
            // Place part in space.
            uFunctionType = "CATTubControlValveFunction";
            uPlacedPartID = ""; // Null string uses name generated by PP engine
            upDirection.SetCoord(0, 0, 1); // Part up direction parallel to z-axis.
            horizontalOrientation.SetCoord(0,1,0); // Align part parallel to y-axis.
            position.SetCoord(1000,2000,-4000); // Position part at (1000, 2000, 4000) in mm.
            rc = piPlacePart->PlacePartInSpace (uStandard, 
                                                uFunctionType, 
                                                piReferencePart, 
                                                piParentProduct, 
                                                piLogicalLine, 
                                                uPlacedPartID, 
                                                upDirection, 
                                                horizontalOrientation, 
                                                position, 
                                                piInstancePart);
            cout << "piInstancePart = " << piInstancePart << endl;

            if (piInstancePart)
            {
              // Set catalog part name
              piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

              // Test part connectors.
              ctrPosition.SetCoord(1014.61,2000,-4000);
              ctrAlign.SetCoord(1,0,0);
              ctrUp.SetCoord(0,0,1);
              rc = TestPartConnectorData(piInstancePart, 
                                         1, 
                                         piParentProduct, 
                                         ctrPosition, 
                                         ctrAlign, 
                                         ctrUp);
              if (SUCCEEDED(rc))
              {
                ctrPosition.SetCoord(985.395,2000,-4000);
                ctrAlign.SetCoord(-1,0,0);
                ctrUp.SetCoord(0,0,1);
                rc = TestPartConnectorData(piInstancePart, 
                                           2, 
                                           piParentProduct, 
                                           ctrPosition, 
                                           ctrAlign, 
                                           ctrUp);
              }
            }
            else
            {
              rc = CATReturnFailure;
            }
          }
          if (FAILED(rc)) break;

          if (piInstancePartPrevious) {piInstancePartPrevious->Release(); piInstancePartPrevious = NULL;}
          piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}

          // ==============================================================================
          // Place union on valve.
          // ==============================================================================
          // Get reference part
          uPartType = "TubingUnion";
          uPartNumber = "UNION-BULKHEAD-TMFL-16-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {
            // Get valve ctr 2.
            rc = GetPartConnector(piInstancePartPrevious, 
                                  2, 
                                  piPlaceOnCtr);
            cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

            // Place part on connector.
            uFunctionType = "CATTubTubeFunction";
            uPlacedPartID = ""; // Null string uses name generated by PP engine
            rc = piPlacePart->PlacePartOnPartConnector (uStandard, 
                                                        uFunctionType, 
                                                        piReferencePart, 
                                                        piPlaceOnCtr, 
                                                        piLogicalLine, 
                                                        uPlacedPartID, 
                                                        piInstancePart);
            cout << "piInstancePart = " << piInstancePart << endl;

            if (piInstancePart)
            {
              // Set catalog part name
              piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

              // Test part connectors.
              ctrPosition.SetCoord(985.395,2000,-4000);
              ctrAlign.SetCoord(1,0,0);
              ctrUp.SetCoord(0,0,1);
              rc = TestPartConnectorData(piInstancePart, 
                                         1, 
                                         piParentProduct, 
                                         ctrPosition, 
                                         ctrAlign, 
                                         ctrUp);
              if (SUCCEEDED(rc))
              {
                rc = TestConnectedPart(piInstancePart, 
                                       1, 
                                       piInstancePartPrevious, 
                                       2);
                if (SUCCEEDED(rc))
                {
                  ctrPosition.SetCoord(905.639,2000,-4000);
                  ctrAlign.SetCoord(-1,0,0);
                  ctrUp.SetCoord(0,0,1);
                  rc = TestPartConnectorData(piInstancePart, 
                                             2, 
                                             piParentProduct, 
                                             ctrPosition, 
                                             ctrAlign, 
                                             ctrUp);
                }
              }
            }
            else
            {
              rc = CATReturnFailure;
            }
          }
          if (FAILED(rc)) break;

          if (piInstancePartPrevious) {piInstancePartPrevious->Release(); piInstancePartPrevious = NULL;}
          piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
          if (piPlaceOnCtr) {piPlaceOnCtr->Release(); piPlaceOnCtr = NULL;}

          // ==============================================================================
          // Place valve on run segment.
          // ==============================================================================
          // Get reference part
          uPartType = "CATTubControlValve";
          uPartNumber = "V_BALL-TF-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {
            // Place part on segment.
            uFunctionType = "CATTubControlValveFunction";
            uPlacedPartID = ""; // Null string uses name generated by PP engine
            position.SetCoord(-700,3000,1800); // in mm.
            rc = piPlacePart->PlacePartOnRunSegment (uStandard, 
                                                     uFunctionType, 
                                                     piReferencePart, 
                                                     piSegment, 
                                                     piLogicalLine, 
                                                     uPlacedPartID, 
                                                     position, 
                                                     piInstancePart);
            cout << "piInstancePart = " << piInstancePart << endl;

            if (piInstancePart)
            {
              // Set catalog part name
              piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

              // Test part connectors.
              ctrPosition.SetCoord(-700,2985.395,1800);
              ctrAlign.SetCoord(0,-1,0);
              ctrUp.SetCoord(1,0,0);
              rc = TestPartConnectorData(piInstancePart, 
                                         1, 
                                         piParentProduct, 
                                         ctrPosition, 
                                         ctrAlign, 
                                         ctrUp);
              if (SUCCEEDED(rc))
              {
                ctrPosition.SetCoord(-700,3014.61,1800);
                ctrAlign.SetCoord(0,1,0);
                ctrUp.SetCoord(1,0,0);
                rc = TestPartConnectorData(piInstancePart, 
                                           2, 
                                           piParentProduct, 
                                           ctrPosition, 
                                           ctrAlign, 
                                           ctrUp);
              }
            }
            else
            {
              rc = CATReturnFailure;
            }
          }
          if (FAILED(rc)) break;

          if (piInstancePartPrevious) {piInstancePartPrevious->Release(); piInstancePartPrevious = NULL;}
          piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}

          // ==============================================================================
          // Place union on valve on run.
          // ==============================================================================
          // Get reference part
          uPartType = "TubingUnion";
          uPartNumber = "UNION-BULKHEAD-TMFL-16-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {
            // Get valve ctr 2.
            rc = GetPartConnector(piInstancePartPrevious, 
                                  2, 
                                  piPlaceOnCtr);
            cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

            // Place part on connector.
            uFunctionType = "CATTubTubeFunction";
            uPlacedPartID = ""; // Null string uses name generated by PP engine
            rc = piPlacePart->PlacePartOnPartConnector (uStandard, 
                                                        uFunctionType, 
                                                        piReferencePart, 
                                                        piPlaceOnCtr, 
                                                        piLogicalLine, 
                                                        uPlacedPartID, 
                                                        piInstancePart);
            cout << "piInstancePart = " << piInstancePart << endl;

            if (piInstancePart)
            {
              // Set catalog part name
              piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

              // Test part connectors.
              ctrPosition.SetCoord(-700,3014.61,1800);
              ctrAlign.SetCoord(0,-1,0);
              ctrUp.SetCoord(1,0,0);
              rc = TestPartConnectorData(piInstancePart, 
                                         1, 
                                         piParentProduct, 
                                         ctrPosition, 
                                         ctrAlign, 
                                         ctrUp);
              if (SUCCEEDED(rc))
              {
                rc = TestConnectedPart(piInstancePart, 
                                       1, 
                                       piInstancePartPrevious, 
                                       2);
                if (SUCCEEDED(rc))
                {
                  ctrPosition.SetCoord(-700,3094.366,1800);
                  ctrAlign.SetCoord(0,1,0);
                  ctrUp.SetCoord(1,0,0);
                  rc = TestPartConnectorData(piInstancePart, 
                                             2, 
                                             piParentProduct, 
                                             ctrPosition, 
                                             ctrAlign, 
                                             ctrUp);
                }
              }
            }
            else
            {
              rc = CATReturnFailure;
            }
          }
          if (FAILED(rc)) break;

          if (piInstancePartPrevious) {piInstancePartPrevious->Release(); piInstancePartPrevious = NULL;}
          piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
          if (piPlaceOnCtr) {piPlaceOnCtr->Release(); piPlaceOnCtr = NULL;}

          // ==============================================================================
          // Place sleeve on union.
          // ==============================================================================
          // Get reference part
          uPartType = "TubingBNutSleeve";
          uPartNumber = "SLEEVE-CSFR-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {
            // Get union ctr 2.
            rc = GetPartConnector(piInstancePartPrevious, 
                                  2, 
                                  piPlaceOnCtr);
            cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

            // Place part on connector.
            uFunctionType = "CATTubTubeFunction";
            uPlacedPartID = ""; // Null string uses name generated by PP engine
            rc = piPlacePart->PlacePartOnPartConnector (uStandard, 
                                                        uFunctionType, 
                                                        piReferencePart, 
                                                        piPlaceOnCtr, 
                                                        piLogicalLine, 
                                                        uPlacedPartID, 
                                                        piInstancePart);
            cout << "piInstancePart = " << piInstancePart << endl;

            if (piInstancePart)
            {
              // Set catalog part name
              piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

              // Test part connectors.
              ctrPosition.SetCoord(-700,3094.366,1800);
              ctrAlign.SetCoord(0,-1,0);
              ctrUp.SetCoord(1,0,0);
              rc = TestPartConnectorData(piInstancePart, 
                                         1, 
                                         piParentProduct, 
                                         ctrPosition, 
                                         ctrAlign, 
                                         ctrUp);
              if (SUCCEEDED(rc))
              {
                rc = TestConnectedPart(piInstancePart, 
                                       1, 
                                       piInstancePartPrevious, 
                                       2);
                if (SUCCEEDED(rc))
                {
                  ctrPosition.SetCoord(-700,3094.366,1800);
                  ctrAlign.SetCoord(0,1,0);
                  ctrUp.SetCoord(1,0,0);
                  rc = TestPartConnectorData(piInstancePart, 
                                             2, 
                                             piParentProduct, 
                                             ctrPosition, 
                                             ctrAlign, 
                                             ctrUp);
                }
              }
            }
            else
            {
              rc = CATReturnFailure;
            }
          }
          if (FAILED(rc)) break;

          if (piInstancePartPrevious) {piInstancePartPrevious->Release(); piInstancePartPrevious = NULL;}
          piInstancePart->QueryInterface(IID_IUnknown,(void**)&piInstancePartPrevious);
          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
          if (piPlaceOnCtr) {piPlaceOnCtr->Release(); piPlaceOnCtr = NULL;}

          // ==============================================================================
          // Place nut on sleeve.
          // ==============================================================================
          // Get reference part
          uPartType = "TubingNut";
          uPartNumber = "B-NUT-CSFR-16S";
          rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
                                                         uSpecName, 
                                                         uPartType, 
                                                         uPartNumber, 
                                                         piParentProduct, 
                                                         piReferencePart, 
                                                         uCatalogPartName);
          cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

          if (SUCCEEDED(rc) && 
              piReferencePart)
          {
            // Get sleeve ctr 2.
            rc = GetPartConnector(piInstancePartPrevious, 
                                  2, 
                                  piPlaceOnCtr);
            cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

            // Place part on connector.
            uFunctionType = "CATTubTubeFunction";
            uPlacedPartID = ""; // Null string uses name generated by PP engine
            rc = piPlacePart->PlacePartOnPartConnector (uStandard, 
                                                        uFunctionType, 
                                                        piReferencePart, 
                                                        piPlaceOnCtr, 
                                                        piLogicalLine, 
                                                        uPlacedPartID, 
                                                        piInstancePart);
            cout << "piInstancePart = " << piInstancePart << endl;

            if (piInstancePart)
            {
              // Set catalog part name
              piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);

              // Test part connectors.
              ctrPosition.SetCoord(-700,3094.366,1800);
              ctrAlign.SetCoord(0,-1,0);
              ctrUp.SetCoord(1,0,0);
              rc = TestPartConnectorData(piInstancePart, 
                                         1, 
                                         piParentProduct, 
                                         ctrPosition, 
                                         ctrAlign, 
                                         ctrUp);
              if (SUCCEEDED(rc))
              {
                rc = TestConnectedPart(piInstancePart, 
                                       1, 
                                       piInstancePartPrevious, 
                                       2);
                if (SUCCEEDED(rc))
                {
                  ctrPosition.SetCoord(-700,3094.366,1800);
                  ctrAlign.SetCoord(0,1,0);
                  ctrUp.SetCoord(1,0,0);
                  rc = TestPartConnectorData(piInstancePart, 
                                             2, 
                                             piParentProduct, 
                                             ctrPosition, 
                                             ctrAlign, 
                                             ctrUp);
                }
              }
            }
            else
            {
              rc = CATReturnFailure;
            }
          }
          if (FAILED(rc)) break;

          if (piInstancePartPrevious) {piInstancePartPrevious->Release(); piInstancePartPrevious = NULL;}
          if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
          if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
          if (piPlaceOnCtr) {piPlaceOnCtr->Release(); piPlaceOnCtr = NULL;}

        } while (0); // End dummy loop for easy exit on fail.
      } // End if valid run segment.
      if (FAILED(rc))
      {
        piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
        cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
      }
    } // End if valid place part object.
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::PlacePartInSpace *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piAppObject) {piAppObject->Release(); piAppObject = NULL;}
  if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
  if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
  if (piParentProduct) {piParentProduct->Release(); piParentProduct = NULL;}
  if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}
  if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
  if (piInstancePartPrevious) {piInstancePartPrevious->Release(); piInstancePartPrevious = NULL;}
  if (piPlaceOnCtr) {piPlaceOnCtr->Release(); piPlaceOnCtr = NULL;}
  if (piRun) {piRun->Release(); piRun = NULL;}
  if (piSegment) {piSegment->Release(); piSegment = NULL;}

  cout << "CAACloPlacePart::PlacePartOnPartConnector rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Place part on part connector and reconnect run to the placed part. 
//=============================================================================
HRESULT CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun()
{
  cout <<"===================================================================="<< endl;
  cout <<"===   CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun   ==="<< endl;
  cout <<"===================================================================="<< endl;
  HRESULT rc = E_FAIL;

  
  CATObject *piAppObject = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  CATIPspPlacePartOnRun *piPlacePart = NULL;  
  CATIProduct *piValve = NULL;
  IUnknown *pUnkPart = NULL;  
  IUnknown *piReferencePart = NULL;
  IUnknown *piInstancePart = NULL;
  IUnknown *piPlaceOnCtr = NULL;
  CATIProduct_var spiParentProduct = NULL_var;
  IUnknown *piUkParentProduct_valve = NULL; 
  CATUnicodeString uStandard = "SSTL";
  CATUnicodeString uSpecName = "";
  CATUnicodeString uPartType;
  CATUnicodeString uPartNumber;  
  CATUnicodeString uCatalogPartName = "";
  CATMathPoint ctrPosition;
  CATMathDirection ctrAlign;
  CATMathDirection ctrUp;
    
  CATTry 
  {	
    // Get application object.
    piAppObject = new CATObject("CATTubing");
    cout << "piAppObject = " << piAppObject << endl;

    if (piAppObject && 
      SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)))
    {
      cout << "piPlacePart = " << piPlacePart << endl; 

      spiParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");     
      cout << "spiParentProduct = " << spiParentProduct << endl;

      piLogicalLine = GetALogicalLine(spiParentProduct);
      cout << "piLogicalLine = " << piLogicalLine << endl;

      piValve = (CATIProduct*)GetChildObject(IID_CATIProduct, "T-001", spiParentProduct);
      cout << "piValve = " << piValve << endl;

      if(piValve)
      {
        piValve->QueryInterface(IID_IUnknown,(void**)&pUnkPart);
        
        // Get reference part
        uPartType = "TubingUnion";
        uPartNumber = "UNION-BULKHEAD-TMFL-12-16S";
        spiParentProduct = piValve->GetFatherProduct();
        
        if(!!spiParentProduct)  
		    spiParentProduct->QueryInterface(IID_IUnknown,(void**)&piUkParentProduct_valve);  
		if(piUkParentProduct_valve)
		{
			rc = piPlacePart->GetReferencePartFromCatalog (uStandard, 
				uSpecName, 
				uPartType, 
				uPartNumber, 
				piUkParentProduct_valve, 
				piReferencePart, 
				uCatalogPartName);
		}

        cout << "piReferencePart = " << piReferencePart << "uCatalogPartName = " << uCatalogPartName.ConvertToChar() << endl;

        if (SUCCEEDED(rc) && 
          piReferencePart)
        {          
          rc = GetPartConnector(pUnkPart, 2,  piPlaceOnCtr);

          cout << "piPlaceOnCtr = " << piPlaceOnCtr << endl;

          // Place part on connector.
          CATUnicodeString uFunctionType = "CATTubTubeFunction";
          CATUnicodeString uPlacedPartID = ""; // Null string uses name generated by PP engine        
          
          rc = piPlacePart->PlacePartOnPartConnector (uStandard, 
                                                      uFunctionType, 
                                                      piReferencePart, 
                                                      piPlaceOnCtr, 
                                                      piLogicalLine, 
                                                      uPlacedPartID, 
                                                      piInstancePart,
                                                      1);

          if(SUCCEEDED(rc) && piInstancePart)
          {
            // Set catalog part name
            piPlacePart->SetCatalogPartName(piInstancePart, uCatalogPartName);             

            // Test part connectors.
            ctrPosition.SetCoord(646.329,1587.59,0);
            ctrAlign.SetCoord(-0.05,-1,0);
            ctrUp.SetCoord(0,0,1);           
			if(!!spiParentProduct)
			spiParentProduct->QueryInterface(IID_IUnknown,(void**)&piUkParentProduct_valve);  
			if(piUkParentProduct_valve)
			{
				rc = TestPartConnectorData(piInstancePart, 
					2, 
					piUkParentProduct_valve, 
					ctrPosition, 
					ctrAlign, 
					ctrUp);
			}
            if (SUCCEEDED(rc))
            {
              rc = TestConnectedPart(piInstancePart, 
                                     2, 
                                     pUnkPart, 
                                     2);
              if (SUCCEEDED(rc))
              {
                ctrPosition.SetCoord(651.013,1667.21,0);
                ctrAlign.SetCoord(0.05,1,0);
                ctrUp.SetCoord(1,0,0);	
               
				if(!!spiParentProduct)
				spiParentProduct->QueryInterface(IID_IUnknown,(void**)&piUkParentProduct_valve);
				if(piUkParentProduct_valve)
				{
					rc = TestPartConnectorData(piInstancePart, 
						1, 
						piUkParentProduct_valve, 
						ctrPosition, 
						ctrAlign, 
						ctrUp);
				}
              }
            }
          }
        }          
      }       
    }
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun *** Error Caught ***" << endl;
    cout << pError;
    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;  

  if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}
  if (piPlaceOnCtr) {piPlaceOnCtr->Release(); piPlaceOnCtr = NULL;}
  if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
  if (pUnkPart) {pUnkPart->Release(); pUnkPart = NULL;}
  if (piValve) {piValve->Release(); piValve = NULL;}
  if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}  
  if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
  if (piAppObject) {piAppObject->Release(); piAppObject = NULL;} 
  if (piUkParentProduct_valve) {piUkParentProduct_valve->Release();
                                 piUkParentProduct_valve = NULL;} 


  cout << "CAACloPlacePart::PlacePartOnPartConnectorAndReconnectRun rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Execute the CAACloPlacePart sample code.
//=============================================================================
HRESULT CAACloPlacePart::DoSample(const CATUnicodeString &iuFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloPlacePart::DoSample                      ==="<< endl;
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
    ApplicationInit("CATTubing");
    cout << "Tubing application initialized." << endl;

    // Place a part in space.
    HRESULT rcSpace = PlacePartInSpace();
    cout << "rcSpace = " << rcSpace << endl;

    // Route a string in space.
    HRESULT rcStringInSpace = RouteStringPartInSpace();
    cout << "rcStringInSpace = " << rcStringInSpace << endl;

    // Place parts on run segments.
    HRESULT rcSegment = PlacePartOnRunSegment();
    cout << "rcSegment = " << rcSegment << endl;

    // Place parts on part conntectors.
    HRESULT rcPartCtr = PlacePartOnPartConnector();
    cout << "rcPartCtr = " << rcPartCtr << endl;

    // Place parts on run nodes.
    HRESULT rcNode = PlacePartOnRunNode();
    cout << "rcNode = " << rcNode << endl;

    // Place part on part conntector and reconnect run.
    HRESULT rcPartCtrNCnt = PlacePartOnPartConnectorAndReconnectRun();
    cout << "rcPartCtrNCnt = " << rcPartCtrNCnt << endl;

    // Set return code.
    if (SUCCEEDED(rcSpace) && 
        SUCCEEDED(rcStringInSpace) && 
        SUCCEEDED(rcSegment) && 
        SUCCEEDED(rcPartCtr) && 
        SUCCEEDED(rcNode) && 
        SUCCEEDED(rcPartCtrNCnt) )
      rc = CATReturnSuccess;
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloPlacePart::DoSample *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  cout << "CAACloPlacePart::DoSample rc = " << rc << endl;
  return rc;
}
