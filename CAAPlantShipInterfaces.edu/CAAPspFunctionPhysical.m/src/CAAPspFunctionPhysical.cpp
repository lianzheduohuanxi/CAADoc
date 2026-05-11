// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CAAPspFunctionPhysical - This sample illustrates how to use the following
// interfaces to query function, physical and spatial objects:  
// CATIPspFunctional, CATIPspPhysical, CATIPspSpatial.
//
#include <iostream.h>

// This framework
#include "CAAPspFunctionPhysical.h"

#include "CATPspListServices.h"

// CATPlantShipInterfaces
#include "CATIPspFunctional.h"
#include "CATIPspPhysical.h"
#include "CATIPspSpatial.h"
#include "CATIPspResource.h"
#include "CATPspFunctionStatus.h"

//ObjectModelerBase
#include "CATDocument.h"
#include "CATISpecObject.h"

// System
#include "CATBooleanDef.h"
#include "CATIUnknownList.h"
#include "IUnknown.h"
#include "CATListOfCATUnicodeString.h"
#include "CATListOfInt.h"

//=============================================================================
//  Constructor
//=============================================================================
CAAPspFunctionPhysical::CAAPspFunctionPhysical() 
{
  cout << "CAAPspFunctionPhysical::CAAPspFunctionPhysical()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAAPspFunctionPhysical::~CAAPspFunctionPhysical()
{
  cout << "CAAPspFunctionPhysical::~CAAPspFunctionPhysical()" << endl;
}

//=============================================================================
//  Query the function, physical and spatial objects.
//=============================================================================
int CAAPspFunctionPhysical::DoSample(const CATUnicodeString &iFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAAPspFunctionPhysical::DoSample               ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc;

  // Interface pointer variables used below in the try section.
  CATIPspFunctional  *piFunction = NULL;
  CATIPspPhysical    *piPhysical = NULL;
  CATIPspSpatial     *piSpatial = NULL;
  CATIPspResource    *piResource = NULL;
  IUnknown           *piUnknown = NULL;
  CATIUnknownList    *piUnkList = NULL;
  CATISpecObject     *piSpecObj = NULL;

  CATListOfCATUnicodeString *pPartTypeList = NULL;
  CATListOfCATUnicodeString *pPartNumberList = NULL;
  CATListOfCATUnicodeString *pCatPartNameList = NULL;
  CATListOfInt *pStatusList = NULL;

  CATBoolean Found = FALSE;
  CATUnicodeString PartType;
  CATUnicodeString PartNumber;
  CATUnicodeString Standard = "ASTL";
  CATUnicodeString CatalogName;
  CATUnicodeString CatPartName;

  CATTry 
  {
    //  Load input document
    CreateCATProductEnv (iFileToBeLoaded);

    //  Initialize Piping Design application
    ApplicationInit();

    CATObject *piApplObj = new CATObject("CATPiping");
    if ( NULL != piApplObj )
    {
       //  Find CATIPspResource interface from application object
       rc = piApplObj->QueryInterface(IID_CATIPspResource,(void **)&piResource);
       piApplObj->Release();
       piApplObj = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspPhysical methods
    //-------------------------------------------------------------------------
    piPhysical = GetAPhysicalObject();
    if ( NULL != piPhysical )
    {
       //----------------------------------------------------------------------
       //  Query if physical object has a function associated with it
       //----------------------------------------------------------------------    
       rc = piPhysical->HasFunction(Found);
       if ( Found )
          cout << "CAAPspFunctionPhysical: "
               << "Physical object was created with a function" << endl;

       //----------------------------------------------------------------------
       //  Get the function associated to the physical object
       //----------------------------------------------------------------------    
       if ( SUCCEEDED(piPhysical->GetFunctional(piUnknown)) && NULL != piUnknown )
       {
          //  Find CATIPspFunctional interface
          rc = piUnknown->QueryInterface(IID_CATIPspFunctional,(void**)&piFunction);
          piUnknown->Release();
          piUnknown = NULL;
       }

       //----------------------------------------------------------------------
       //  Get the spatial object associated to the physical object
       //----------------------------------------------------------------------    
       if ( SUCCEEDED(piPhysical->GetSpatial(piUnknown)) && NULL != piUnknown )
       {
          //  Find CATIPspSpatial interface
          rc = piUnknown->QueryInterface(IID_CATIPspSpatial,(void**)&piSpatial);
          piUnknown->Release();
          piUnknown = NULL;
       }

       //----------------------------------------------------------------------
       //  Find CATISpecObject interface from physical object
       //  And get the physical part type 
       //----------------------------------------------------------------------
       rc = piPhysical->QueryInterface(IID_CATISpecObject,(void**)&piSpecObj);
       if ( NULL != piSpecObj )
       {
          PartType = piSpecObj->GetType();
          cout << "Physical part type: " << PartType.ConvertToChar() << endl;
          piSpecObj->Release();
          piSpecObj = NULL;
       }
    }

    //-------------------------------------------------------------------------
    //  CATIPspSpatial methods
    //-------------------------------------------------------------------------
    if ( NULL != piSpatial )
    {
       //----------------------------------------------------------------------
       //  Get a list of physical objects 
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piSpatial->ListPhysicals(piUnkList))
            && NULL != piUnkList )
       {
          unsigned int ListSize = 0;
          piUnkList->Count(&ListSize);
          piUnkList->Release();  piUnkList = NULL;
          cout << "Number of physical objects associated to the spatial object: "
               << (int)ListSize << endl;
       }

       piSpatial->Release();
       piSpatial = NULL;
    }

    //-------------------------------------------------------------------------
    //  CATIPspFunctional methods
    //-------------------------------------------------------------------------
    if ( NULL != piFunction )
    {
       //-------------------------------------------------------------------
       //  Is function specification driven?
       //-------------------------------------------------------------------
       rc = piFunction->IsSpecDriven(Found);
       if ( Found )
          cout << "Function is specification driven" << endl;

       //-------------------------------------------------------------------
       //  List compatible part types
       //-------------------------------------------------------------------
       int iNum = 0;
       if ( SUCCEEDED(piFunction->ListCompatiblePartTypes(Standard,pPartTypeList))
            && NULL != pPartTypeList )
       {
          iNum = pPartTypeList->Size();
          cout << "Number of compatible part types for function: "
               << iNum << endl;
          delete pPartTypeList;  pPartTypeList = NULL;
       }

       //-------------------------------------------------------------------
       //  List compatible part numbers
       //-------------------------------------------------------------------
       if ( NULL != piResource )
       {
          CATUnicodeString Path;
          rc = piResource->GetPartCatalogPath(Path,CatalogName);
          piResource->Release();
          piResource = NULL;
       }
       if ( SUCCEEDED(piFunction->ListCompatiblePartNumbers(PartType,Standard,
                   CatalogName,pCatPartNameList,pPartNumberList)) )
       {
          if ( NULL != pCatPartNameList )
          {
             delete pCatPartNameList;  pCatPartNameList = NULL;
          }
          if ( NULL != pPartNumberList )
          {
             cout << "Number of compatible part numbers: "
                  << pPartNumberList->Size() << endl;
             delete pPartNumberList;  pPartNumberList = NULL;
          }
       }

       //-------------------------------------------------------------------
       //  Is function realized by a placed part?
       //-------------------------------------------------------------------
       rc = piFunction->IsRealized(Found);
       if ( Found )
          cout << "Function is realized" << endl;

       //----------------------------------------------------------------------
       //  Get a list of physical objects associated to this function
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piFunction->ListPhysicals(piUnkList))
            &&  NULL != piUnkList )
       {
          unsigned int ListSize = 0;
          piUnkList->Count(&ListSize);
          piUnkList->Release();  piUnkList = NULL;
          cout << "Physical objects associated to function: "
               << (int)ListSize << endl;
       }

       //----------------------------------------------------------------------
       //  Check if this function can be realized by the input list of 
       //  physical objects
       //----------------------------------------------------------------------
       CATPspListServices::CreateCATIUnknownList(&piUnkList); // Create a list of unknowns
       if ( NULL != piPhysical )
          rc = piPhysical->QueryInterface (IID_IUnknown, (void **)&piUnknown);

       if (SUCCEEDED(rc) && (NULL != piUnknown) && (NULL != piUnkList))
       {
          rc = piUnkList->Add(0,piUnknown);
          piUnknown->Release(); piUnknown = NULL;
       }

       if ( SUCCEEDED(piFunction->CanBeRealizedBy(piUnkList,pStatusList)) )
          cout << "Function can be realized by a list of physical objects "
               << endl;
       if ( NULL != piUnkList )
       {
          piUnkList->Release();  piUnkList = NULL;
       }
       if ( NULL != pStatusList )
       {
          delete pStatusList;  pStatusList = NULL;
       }

       //----------------------------------------------------------------------
       //  Get the part type of physical object that realizes this function
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piFunction->GetPartType(PartType)) )
          cout << "Part type of physical object that realizes the function: "
               << PartType.ConvertToChar() << endl;

       //----------------------------------------------------------------------
       //  Get the part number of physical object that realizes this function
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piFunction->GetPartNumber(PartNumber)) )
          cout << "Part number of physical object that realizes the function: "
               << PartNumber.ConvertToChar() << endl;

       //----------------------------------------------------------------------
       //  Get the part name of physical object that realizes this function
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piFunction->GetCatalogPartName(CatPartName)) )
          cout << "Part name of physical object that realizes the function: "
               << CatPartName.ConvertToChar() << endl;

       //----------------------------------------------------------------------
       //  Get the standard name
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piFunction->GetStandard(Standard)) )
          cout << "Standard name: " << Standard.ConvertToChar() << endl;

       //----------------------------------------------------------------------
       //  Is it OK to integrate (realize) this function with a physical part?
       //----------------------------------------------------------------------
       CATBoolean IsOK;
       rc = piFunction->IsOKToIntegrate(IsOK);
       if ( IsOK )
          cout << "CAAPspFunctionPhysical: "
               << "It is OK to integrate function" << endl;

       //----------------------------------------------------------------------
       //  Get the part catalog name
       //---------------------------------------------------------------------- 
       if ( SUCCEEDED(piFunction->GetPartCatalogName(CatalogName)) )
          cout << "Catalog name: " << CatalogName.ConvertToChar() << endl;

       //----------------------------------------------------------------------
       //  Get the function status
       //---------------------------------------------------------------------- 
       CATPspFunctionStatus Status;
       if ( SUCCEEDED(piFunction->GetFunctionStatus(Status)) )
          cout << "Get function status succeeded" << endl;

       piFunction->Release();
       piFunction = NULL;
    }

    if ( NULL != piResource )
    {
       piResource->Release();
       piResource = NULL;
    }
    if ( NULL != piPhysical )
    {
       piPhysical->Release();
       piPhysical = NULL;
    }

  } // end CATTry

  CATCatch (CATError, error)
  {
    if ( NULL != piFunction ) { piFunction->Release(); piFunction = NULL; }
    if ( NULL != piPhysical ) { piPhysical->Release(); piPhysical = NULL; }
    if ( NULL != piSpatial ) { piSpatial->Release(); piSpatial = NULL; }
    if ( NULL != piResource ) { piResource->Release(); piResource = NULL; }
    if ( NULL != piUnknown ) { piUnknown->Release(); piUnknown = NULL; }
    if ( NULL != piUnkList ) { piUnkList->Release(); piUnkList = NULL; }
    if ( NULL != piSpecObj ) { piSpecObj->Release(); piSpecObj = NULL; }
    cout << "CAAPspFunctionPhysical::DoSample *** CATRethrow" << endl;
    CATRethrow;
  } 
  CATEndTry;
  return 0;
}
