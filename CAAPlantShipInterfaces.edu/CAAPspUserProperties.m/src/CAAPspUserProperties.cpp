// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAPspUserProperties - 
//  This sample illustrates how to use the CAA Plant Ship interfaces to:
//
//  1. Get the value of the computed attribute that was added in use case CAAPspDefineUserProperties
//
#include <iostream.h>

// This framework
#include "CAAPspUserProperties.h"

// CATPlantShipInterfaces
#include "CATIPspPhysical.h"

// KWe 
#include "CATITypeDictionary.h"
#include "CATGlobalFunctions.h"

#include "CATIInstance.h"
#include "CATIValue.h"

//ObjectModelerBase
#include "CATDocument.h"


// System
#include "CATUnicodeString.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspUserProperties::CAAPspUserProperties() 
{
  cout << "CAAPspUserProperties::CAAPspUserProperties()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspUserProperties::~CAAPspUserProperties()
{
  cout << "CAAPspUserProperties::~CAAPspUserProperties()" << endl;
}

//=============================================================================
//  List and query attributes and ID
//=============================================================================
int CAAPspUserProperties::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspUserProperties::DoSample                     ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspPhysical        *piPhysical = NULL;  
  CATIInstance           *piInstance = NULL;
  CATIValue*             piVal = NULL;
  
  CATTry 
  { 
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    //  Get a physical object from the input document
    piPhysical = GetAPhysicalObject();

    CATITypeDictionary_var spDico = CATGlobalFunctions::GetTypeDictionary();

    if(!!spDico )
    {
      spDico->LoadPackage( "PipingLayout" );
    }
    // get CATIInstance and call GetValue() 

    if ( NULL != piPhysical )
    {
	    rc = piPhysical->QueryInterface (IID_CATIInstance,(void **)&piInstance);
		 
      if( SUCCEEDED(rc) &&  piInstance)
      {
        piVal = piInstance->GetValue("TotalWallThickness");
        if( NULL != piVal )
        {
          CATUnicodeString uAttrVal = piVal->Show();
           cout << "TotalWallThickness value is:" << uAttrVal.ConvertToChar() << endl;
        }
        else
        {
           cout << "Failed in getting computer attribute value for TotalWallThickness." << endl;
        }
      }      
    }    
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piInstance ) { piInstance->Release(); piInstance = NULL; }
    if ( NULL != piVal ) { piVal->Release(); piVal = NULL; }
  } // end CATTry

  CATCatch (CATError, error)
  {    
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piInstance ) { piInstance->Release(); piInstance = NULL; }
    if ( NULL != piVal ) { piVal->Release(); piVal = NULL; }
    
    cout << "CAAPspUserProperties::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
  if ( NULL != piInstance ) { piInstance->Release(); piInstance = NULL; }
  if ( NULL != piVal ) { piVal->Release(); piVal = NULL; }
    
  CATEndTry;
  return 0;
}

