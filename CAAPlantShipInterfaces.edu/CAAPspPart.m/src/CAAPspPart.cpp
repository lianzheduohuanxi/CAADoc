// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspPart - This sample illustrates how to use the following
// interfaces to manage and query for part connector information:  
// CATIPspPhysicalProduct, CATIPspPartConnector.
//
#include <iostream.h>

// This framework
#include "CAAPspPart.h"

// CATPlantShipInterfaces
#include "CATIPspPhysicalProduct.h"
#include "CATIPspPhysical.h"
#include "CATIPspPartConnector.h"
#include "CATPspPartConnectorTypeEnum.h"

//ObjectModelerBase
#include "CATDocument.h"
#include "CATIConnector.h"

// ObjectModelerBase
#include "CATILinkableObject.h"
#include "CATISpecObject.h"

// System
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATListOfCATUnicodeString.h"

// Product Structure
#include "CATIProduct.h"

// Mathematics
#include "CATMathPoint.h"
#include "CATMathPlane.h"
#include "CATMathDirection.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspPart::CAAPspPart() 
{
  cout << "CAAPspPart::CAAPspPart()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspPart::~CAAPspPart()
{
  cout << "CAAPspPart::~CAAPspPart()" << endl;
}

//=============================================================================
//  List and query part connectors
//=============================================================================
int CAAPspPart::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspPart::DoSample               ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspPhysical        *piPhysical    = NULL;
  CATIPspPhysicalProduct *piPhysProd    = NULL;
  CATIPspPartConnector   *piPartCntr    = NULL;
  CATISpecObject         *piSpecCntr    = NULL;
  IUnknown               *piUnknown     = NULL;
  IUnknown               *piUKFaceCtr   = NULL;
  IUnknown               *piUKAlignCtr  = NULL;
  IUnknown               *piUKOrientCtr = NULL;
  IUnknown               *piUKDatumCtr  = NULL;
  CATIUnknownList        *piUnkList     = NULL;

  int CtrNum = 0;
  CATUnicodeString PartCtrType;
  CATMathPoint Position;
  CATMathDirection Direction;
  CATMathPlane MathPlane;
  CATPspPartConnectorTypeEnum FaceCntrType;
  CATPspPartConnectorTypeEnum AlignCntrType;
  CATPspPartConnectorTypeEnum ClockCntrType;
  CATListValCATUnicodeString *pAttrNameList = NULL;

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    //  Get a physical object from the input document
    piPhysical = GetAPhysicalObject();

    if ( NULL != piPhysical )
    {
       //  Find CATIPspPhysicalProduct interface
       rc = piPhysical->QueryInterface(IID_CATIPspPhysicalProduct,(void**)&piPhysProd);
       piPhysical->Release();
       piPhysical = NULL;
    }

    if ( NULL != piPhysProd )
    {
       int NumOfCtrs = 0;

       //----------------------------------------------------------------------
       //  Get number of connectors on physical object
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piPhysProd->GetNumberOfConnectors(NumOfCtrs)) )
          cout << "Number of connectors on part: " << NumOfCtrs << endl;

       //----------------------------------------------------------------------
       //  List part connectors
       //----------------------------------------------------------------------    
       if ( SUCCEEDED(piPhysProd->ListConnectors(NULL,&piUnkList))
            && NULL != piUnkList )
       {
          //  Get a part connector
          unsigned int ListSize = 0;
          if ( SUCCEEDED(piUnkList->Count(&ListSize)) ) NumOfCtrs = ListSize;
          if ( NumOfCtrs > 0 )
          {
             for ( int i = 0; i < NumOfCtrs; i++ )
             {
                if ( SUCCEEDED(piUnkList->Item(i,&piUnknown)) && (NULL != piUnknown) )
                {
                   rc = piUnknown->QueryInterface(IID_CATIPspPartConnector,(void**)&piPartCntr);
                   piUnknown->Release();
                   piUnknown = NULL; 
                   if ( NULL != piPartCntr ) break;
                }
             }
          }
          piUnkList->Release();  piUnkList = NULL;
       }
    }

    if ( NULL != piPartCntr )
    {
       if ( SUCCEEDED(piPartCntr->QueryInterface(IID_CATISpecObject,
            (void**)&piSpecCntr)) && (NULL != piSpecCntr) )
       {
          PartCtrType = piSpecCntr->GetType();
          piSpecCntr->Release();  piSpecCntr = NULL;
       }

       //----------------------------------------------------------------------
       //  Get face connector pointer
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetFaceConnector(&piUKFaceCtr)) )
          cout << "Get face connector succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get alignment connector pointer
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetAlignmentConnector(&piUKAlignCtr)) )
          cout << "Get alignment connector succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get orientation connector pointer
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetOrientationConnector(&piUKOrientCtr)) )
          cout << "Get orientation connector succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get datum connector pointer
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetDatumConnector(&piUKDatumCtr)) )
          cout << "Get datum connector succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector number
       //----------------------------------------------------------------------
       if ( SUCCEEDED(piPartCntr->GetConnectorNumber(CtrNum)) )
          cout << "Connector number: " << CtrNum << endl;

       //----------------------------------------------------------------------
       //  Get connector position
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetPosition(NULL,Position)) )
          cout << "Get connector position succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector alignment direction
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetAlignmentDirection(NULL,Direction)) )
          cout << "Get connector alignment direction succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector up direction
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetUpDirection(NULL,Direction)) )
          cout << "Get connector up direction succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector math plane
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetConnectorMathPlane(NULL,MathPlane)) )
          cout << "Get connector math plane succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector face type
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetFaceType(FaceCntrType)) )
          cout << "Get connector face type succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector alignment type
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetAlignType(AlignCntrType)) )
          cout << "Get connector alignment type succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector clocking type
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->GetClockType(ClockCntrType)) )
          cout << "Get connector clocking type succeeded" << endl;

       //----------------------------------------------------------------------
       //  Get connector attribute names
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piPartCntr->ListAttrNames(pAttrNameList))
            && NULL != pAttrNameList )
       {
          int iNum = pAttrNameList->Size();
          cout << "Number of connector attributes: " << iNum << endl;
          for ( int i = 1; i <= iNum; i++ )
          {
             CATUnicodeString AttrName = (*pAttrNameList)[i];
             cout << AttrName.ConvertToChar() << endl;
          }
       }

       piPartCntr->Release();
       piPartCntr = NULL;
    }

    if ( (NULL != piPhysProd) && (NULL != piUKFaceCtr) && 
         (NULL != piUKAlignCtr) && (NULL != piUKOrientCtr) )
    {
       //----------------------------------------------------------------------
       //  Remove part connector on physical object
       //----------------------------------------------------------------------   
       if ( SUCCEEDED(piPhysProd->RemoveConnector(CtrNum)) )
          cout << "Removed connector on part" << endl;

       //----------------------------------------------------------------------
       //  Add a new part connector to physical object
       //----------------------------------------------------------------------   
       if ( SUCCEEDED(piPhysProd->AddConnector(PartCtrType,
            CtrNum, piUKFaceCtr, FaceCntrType, piUKAlignCtr,
            AlignCntrType, piUKOrientCtr, ClockCntrType, &piPartCntr)) )
          cout << "Added a connector to part" << endl;

       if ( (NULL != piPartCntr) && (NULL != pAttrNameList) )
       {
          //-------------------------------------------------------------------
          //  Set face connector pointer
          //------------------------------------------------------------------- 
          if ( SUCCEEDED(piPartCntr->SetFaceConnector(piUKFaceCtr,FaceCntrType)) )
             cout << "Set face connector succeeded" << endl;

          //-------------------------------------------------------------------
          //  Set alignment connector pointer
          //-------------------------------------------------------------------
          if ( SUCCEEDED(piPartCntr->SetAlignmentConnector(piUKAlignCtr,AlignCntrType)) )
             cout << "Set alignment connector succeeded" << endl;

          //-------------------------------------------------------------------
          //  Set orientation connector pointer
          //-------------------------------------------------------------------
          if ( SUCCEEDED(piPartCntr->SetOrientationConnector(piUKOrientCtr,ClockCntrType)) )
             cout << "Set orientation connector succeeded" << endl;

          //-------------------------------------------------------------------
          //  Set datum connector pointer
          //-------------------------------------------------------------------
          if ( (NULL != piUKDatumCtr) &&
			   SUCCEEDED(piPartCntr->SetDatumConnector(piUKDatumCtr)) )
             cout << "Set datum connector succeeded" << endl;

          //-------------------------------------------------------------------
          //  Set connector attribute names
          //-------------------------------------------------------------------
          if ( SUCCEEDED(piPartCntr->SetAttrNames(pAttrNameList)) )
             cout << "Set connector attribute names succeeded" << endl;
       }
    }

    if ( NULL != piPhysProd ) { piPhysProd->Release(); piPhysProd = NULL; }
    if ( NULL != piPartCntr ) { piPartCntr->Release(); piPartCntr = NULL; }
    if ( NULL != piUKFaceCtr ) { piUKFaceCtr->Release(); piUKFaceCtr = NULL; }
    if ( NULL != piUKAlignCtr ) { piUKAlignCtr->Release(); piUKAlignCtr = NULL; }
    if ( NULL != piUKOrientCtr ) { piUKOrientCtr->Release(); piUKOrientCtr = NULL; }
    if ( NULL != piUKDatumCtr ) { piUKDatumCtr->Release(); piUKDatumCtr = NULL; }
    if ( NULL != pAttrNameList ) { delete pAttrNameList; pAttrNameList = NULL; }

  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piPhysProd ) { piPhysProd->Release(); piPhysProd = NULL; }
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piPartCntr ) { piPartCntr->Release(); piPartCntr = NULL; }
    if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
    if ( NULL != piUnkList ) { piUnkList->Release(); piUnkList = NULL; }
    cout << "CAAPspPart::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}
