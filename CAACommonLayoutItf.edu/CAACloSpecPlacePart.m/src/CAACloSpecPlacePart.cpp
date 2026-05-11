// COPYRIGHT DASSAULT SYSTEMES  2010
//=============================================================================
//
// CAACloSpecPlacePart 
//   This sample illustrates how to use the CATICloPartRules,CATIPspDefinePhysicalPart 
//   interface to place parts.
//
//=============================================================================

#include <iostream.h>

#include "CAACloSpecPlacePart.h"

#include "CATIPspPhysicalProduct.h"
#include "CATIPspPhysical.h"
#include "CATIPspPartConnector.h"
#include "CATPspPartConnectorTypeEnum.h"
#include "CATICloPartRules.h"
#include "CATIPspPlacePartOnRun.h"
#include "CATIPspDefinePhysicalPart.h"

#include "CATIPspLogicalLine.h"
#include "CATDocument.h"
#include "CATIProduct.h"
#include "CATMathDirection.h"

//=============================================================================
//  Constructor
//=============================================================================
CAACloSpecPlacePart::CAACloSpecPlacePart() : CAAPspBaseEnvProtected()
{
  cout << "CAACloSpecPlacePart::CAACloSpecPlacePart()" << endl;
}

//=============================================================================
//  Destructor
//=============================================================================
CAACloSpecPlacePart::~CAACloSpecPlacePart()
{
  cout << "CAACloSpecPlacePart::~CAACloSpecPlacePart()" << endl;
}

//=============================================================================
//  Place parts in space.
//=============================================================================
HRESULT CAACloSpecPlacePart::PlaceSpecPartInSpace()
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloSpecPlacePart::PlaceSpecPartInSpace              ==="<< endl;
  cout <<"============================================================"<< endl;

  HRESULT rc = CATReturnFailure;

  // Interface pointer variables used below in the try section.
  CATObject *piAppObject = NULL;
  CATIPspDefinePhysicalPart *piDefPhyPart = NULL;
  CATICloPartRules *piPartRules = NULL;
  CATIPspPlacePartOnRun *piPlacePart = NULL;
  IUnknown *piReferencePart = NULL;
  CATIProduct *piParentProduct = NULL;
  CATIPspLogicalLine *piLogicalLine = NULL;
  IUnknown *piInstancePart = NULL;

  CATUnicodeString uCatalogPartName = "";
  CATUnicodeString uPlacePartErrorMessage;
  CATUnicodeString uStandard = "SSTL";
  CATUnicodeString uSpecName = "SS150R";
  CATUnicodeString uPartType = "Union"; 
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

    if (piAppObject)
    {
      piParentProduct = (CATIProduct*)GetChildObject(IID_CATIProduct, "TubingWP.1");
      cout << "piParentProduct = " << piParentProduct << endl;

      piLogicalLine = GetALogicalLine(piParentProduct);
      cout << "piLogicalLine = " << piLogicalLine << endl;

      if(
          SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspDefinePhysicalPart,(void**)&piDefPhyPart)) &&
          SUCCEEDED(piAppObject->QueryInterface(IID_CATIPspPlacePartOnRun,(void**)&piPlacePart)) &&
          SUCCEEDED(piAppObject->QueryInterface(IID_CATICloPartRules,(void**)&piPartRules))
        )
      {
        cout << "piDefPhyPart = " << piDefPhyPart << endl; 
        cout << "piPlacePart = " << piPlacePart << endl; 
        cout << "piPartRules = " << piPartRules << endl; 

        // Get the part number
        CATListOfCATUnicodeString oListPartNumbers;

			  piDefPhyPart->GetPartNumbers (uStandard, 
                                      uPartType, 
                                      uSpecName,
                                      piLogicalLine, 
                                      oListPartNumbers);

        uPartNumber = oListPartNumbers[1];       
        
        // Get reference part
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
          // Get the Function type.
				  CATListOfCATUnicodeString lFunctionTypes;
				  CATListOfInt lSectionTypes;
				  CATUnicodeString uNominalSize = "1/4in";

				  piPartRules->GetPartFunctions (piReferencePart, 
                                         uStandard, 
                                         uSpecName, 
                                         uNominalSize, 
                                         lFunctionTypes, 
                                         lSectionTypes);					  

				  uFunctionType = lFunctionTypes[1];


          // Place part in space.          
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

            // Set specification
           	piDefPhyPart->SetSpecification(piInstancePart,uSpecName);            

            // Verification
            // Specification set and Function type used, can be verified by saving the document and
            // Launching the CATIA. (Go to properties of the placed part, by right clicking the mouse.)
          }
          else
          {
            rc = CATReturnFailure;
          }
        } //piReferencePart
        if (FAILED(rc))
        {
          piPlacePart->GetErrorMessage(uPlacePartErrorMessage);
          cout << "uPlacePartErrorMessage = " << uPlacePartErrorMessage << endl;
        } 
      } // piDefPhyPart piPlacePart piPartRules
    } // piAppObject
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloSpecPlacePart::PlaceSpecPartInSpace *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  if (piAppObject) {piAppObject->Release(); piAppObject = NULL;}
  if (piDefPhyPart) {piDefPhyPart->Release(); piDefPhyPart = NULL;}
  if (piPlacePart) {piPlacePart->Release(); piPlacePart = NULL;}
  if (piPartRules) {piPartRules->Release(); piPartRules = NULL;}
  if (piReferencePart) {piReferencePart->Release(); piReferencePart = NULL;}
  if (piParentProduct) {piParentProduct->Release(); piParentProduct = NULL;}
  if (piLogicalLine) {piLogicalLine->Release(); piLogicalLine = NULL;}
  if (piInstancePart) {piInstancePart->Release(); piInstancePart = NULL;}

  cout << "CAACloSpecPlacePart::PlacePartSpecInSpace rc = " << rc << endl;
  return rc;
}

//=============================================================================
//  Execute the CAACloSpecPlacePart sample code.
//=============================================================================
HRESULT CAACloSpecPlacePart::DoSample(const CATUnicodeString &iuFileToBeLoaded)
{
  cout <<"============================================================"<< endl;
  cout <<"===       CAACloSpecPlacePart::DoSample                      ==="<< endl;
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
    HRESULT rcSpace = PlaceSpecPartInSpace();
    cout << "rcSpace = " << rcSpace << endl;    

    // Set return code.
    if (SUCCEEDED(rcSpace))
      rc = CATReturnSuccess;
  } // end CATTry

	CATCatch (CATError, pError)
	{
    cout << "CAACloSpecPlacePart::DoSample *** Error Caught ***" << endl;
    cout << pError;

    rc = CATReturnError(pError);
	} // end CATCatch

  CATEndTry;

  cout << "CAACloSpecPlacePart::DoSample rc = " << rc << endl;
  return rc;
}
