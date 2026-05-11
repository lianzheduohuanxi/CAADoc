// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspBuildPart - This sample illustrates how to use the following
// interface to create a new physical part reference, set and query its 
// parametric attribute names and modify the part type:  
// CATIPspBuildPart.
//
#include <iostream.h>

// This framework
#include "CAAPspBuildPart.h"

// CATPlantShipInterfaces
#include "CATIPspBuildPart.h"

//ObjectModelerBase
#include "CATObject.h"

// Product Structure
#include "CATIProduct.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATListOfCATUnicodeString.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspBuildPart::CAAPspBuildPart() 
{
  cout << "CAAPspBuildPart::CAAPspBuildPart()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspBuildPart::~CAAPspBuildPart()
{
  cout << "CAAPspBuildPart::~CAAPspBuildPart()" << endl;
}

//=============================================================================
//  Create and modify a physical part reference.
//=============================================================================
int CAAPspBuildPart::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspBuildPart::DoSample                      ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspBuildPart *piBuildPart = NULL;
  CATIProduct *piPartPrdRef = NULL;
  CATIProduct *piPartPrdNewRef = NULL;
  CATIUnknownList *piListOfShapeDocs = NULL;

  CATUnicodeString PartType = "CATPipGateValve"; 
  CATUnicodeString NewPartType = "CATPipGlobeValve";
  CATUnicodeString PartNumber = "GateValve"; 
  CATUnicodeString NewPartNumber = "GlobeValve";
  CATUnicodeString LightPartType = "CATPipStraightPipe"; 

  CATTry
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    CATObject *piApplObj = new CATObject("CATPiping");
    if ( NULL != piApplObj )
    {
       //  Find CATIPspBuildPart interface from application object
       rc = piApplObj->QueryInterface(IID_CATIPspBuildPart,(void **)&piBuildPart);
       piApplObj->Release();
       piApplObj = NULL;
    }

    if ( NULL != piBuildPart )
    {
       //  Create a new Piping part reference document
       if ( SUCCEEDED(piBuildPart->NewPart(PartType,PartNumber,&piPartPrdRef))
            && NULL != piPartPrdRef )
       {
          cout << "CAAPspBuildPart: "
               << "A new part reference was created" << endl;

          //  Set the part parametric attribute names
          CATListValCATUnicodeString *pListAttrNames = new CATListValCATUnicodeString;
          if ( pListAttrNames )
          {
             pListAttrNames->Append("Nominal size");
             pListAttrNames->Append("Standard");
             if ( SUCCEEDED(piBuildPart->SetPartParametricAttributes(piPartPrdRef,
                  pListAttrNames)) )
                cout << "Saved the part parametric attribute names" << endl;
             delete pListAttrNames;
             pListAttrNames = NULL;
          }

          //  List the part parametric attributes
          if ( SUCCEEDED(piBuildPart->ListPartParametricAttributes(piPartPrdRef,
                  pListAttrNames)) )
          {
             delete pListAttrNames;
             pListAttrNames = NULL;
          }

          //  Change the part type
          if ( SUCCEEDED(piBuildPart->ChangePartType(piPartPrdRef,
               NewPartType,NewPartNumber,&piPartPrdNewRef)) )
          {
             cout << "The class type of the part was changed" << endl;
             piPartPrdNewRef->Release();
             piPartPrdNewRef = NULL;
          }
          piPartPrdRef->Release();
          piPartPrdRef = NULL;
       }

       //  Create a new Piping light part reference document
       int LightPart = 1;
       if ( SUCCEEDED(piBuildPart->NewPart(PartType,PartNumber,
            &piPartPrdRef,LightPart)) && NULL != piPartPrdRef )
       {
          cout << "CAAPspBuildPart: "
               << "A new light part reference was created" << endl;
          piPartPrdRef->Release();
          piPartPrdRef = NULL;
       }

       piBuildPart->Release();
       piBuildPart = NULL;
    }
  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piBuildPart ) { piBuildPart->Release(); piBuildPart = NULL; }
    if ( NULL != piPartPrdRef ) { piPartPrdRef->Release(); piPartPrdRef = NULL; }
    if ( NULL != piPartPrdNewRef ) { piPartPrdNewRef->Release(); piPartPrdNewRef = NULL; }
    cout << "CAAPspBuildPart::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}
