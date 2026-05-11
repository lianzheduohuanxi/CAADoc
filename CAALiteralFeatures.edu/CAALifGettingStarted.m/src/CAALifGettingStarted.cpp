// COPYRIGHT DASSAULT SYSTEMES 2000

#include <CAALifGettingStarted.h>
#include <iostream.h>

// ObjectModelerBase headers
#include "CATIContainer.h"
#include "CATIPrtContainer.h"
#include "CATISpecObject.h"

// LiteralFeatures interfaces 
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"
#include "CATICkeType.h"
#include "CATICkeRelation.h"
#include "CATCke.h"

// CAALiteralFeatures headers
#include "CAALifServices.h"
#include "CAALifReturnCodes.h"

// ==============================================================================
//
// ABSTRACT
// --------
//
// This sample is documented in the "Getting Started with Literal Programming"
// article of the LiteralFeaturesDoc.edu framework.
// It is a very simple program which teaches you how to create parameters and
// how to create a formula constraining one of the created parameters.
//
// ==============================================================================  

int main (int argc, char** argv)
{
	  
	  CAALifServices services;
	  
	  // Initialize the session
	  int rc = 0;
	  rc = services.CAALifInitSession ();
	  if( rc != CAALifOk )
			return rc;

	  
	  CATIContainer* piContainer = NULL;
	  HRESULT hr = services.CAALifCreateInstanceContainer(&piContainer);
	  if( FAILED(hr) )
			return CAALifKO;	
	  
	  //Retrieves the parameters factory
	  CATICkeParmFactory* piFact = NULL;
	  HRESULT rc1 = piContainer->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);
	  if (FAILED(rc1)) 
	  {
			cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl << flush;
			piContainer->Release();
			return CAALifParmFactoryError;
	  }		
	  
	  // Create a Length type parameter: Radius 
	  // The radius is described by a length type parameter
	  // Default unit is MKS unit i.e. meters
	  CATICkeParm_var spRadius = piFact->CreateLength ("Radius",2.5);

	  // It is important (but not necessary) to aggregate those parameters especially in part context
      CATIParmPublisher* piPublisher = NULL;
      rc = services.CAALifRetrievePublisherFromCurrentDoc( &piPublisher );
      if (FAILED(rc) || !piPublisher)
        {
          cout << "ERROR in QueryInterface to retreive publisher from container" << endl << flush;
          return CATCke::False;
        }

	  CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,piPublisher,CATCke::True);
	  CATIParmPublisher_var spParmPublisher = NULL_var;
	  if (!!spParameterSet)
		spParmPublisher = spParameterSet;

      if (!!spParmPublisher)
		spParmPublisher->Append(spRadius);

	  CATICkeType_var spType  = spRadius->Type();
	  CATUnicodeString spName = spRadius->Name();
	  cout << "The parameter created (" << spName.ConvertToChar() << ") is of " ; 
	  cout << spType->Name().ConvertToChar() << " type" << endl ; 
	  
	  cout << "Radius value is " ;
	  cout << spRadius->Show().ConvertToChar() << endl;
	  
	  // Create another Length type parameter
	  // The length is described by a length type parameter
	  CATICkeParm_var spLength = piFact->CreateLength ("CylLength",4);

	  // It is important (but not necessary) to aggregate those parameters especially in part context
      if (!!spParmPublisher)
		spParmPublisher->Append(spLength);
 	  
	  cout << "CylLength value is " ;
	  cout << spLength->Show().ConvertToChar() << endl;
	  
	  // Create a Volume type parameter (PI * Radius**2 * CylLength)  
	  CATICkeParm_var
			spVolume = piFact->CreateDimension (CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),"v",2);
	  cout << "Cylinder volume is " ;
	  cout << spVolume->Show().ConvertToChar() << endl;

  	  // It is important (but not necessary) to aggregate those parameters especially in part context
      if (!!spParmPublisher)
		spParmPublisher->Append(spVolume);

	  // Create a formula which calculates the cylinder volume 
	  CATCkeListOf(Parm) paramList;
	  paramList.Append (spVolume);
	  paramList.Append (spRadius);
	  paramList.Append (spLength); 
	  
	  CATICkeRelation_var
			spFormula = piFact->CreateFormula ("VolumeFormula",
			"",
			"", 
			spVolume,
			&paramList,
			"PI*(a2**2)*a3",
			NULL_var,
			CATCke::False); 

	  // It is important (but not necessary) to aggregate those relations especially in part context
	  CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,piPublisher,CATCke::True);
	  if (!!spRelationSet)
      {
	    CATIParmPublisher_var spParmPublisher = spRelationSet;
	    if (!!spParmPublisher)
		   spParmPublisher->Append(spFormula);
      }

	  
	  // Display the volume calculated from the formula
	  cout << "The cylinder volume calculated from VolumeFormula is " ;
	  cout << spVolume->Show().ConvertToChar() << endl;
	  
	  // Modify the CylLength value
	  spRadius -> Valuate(4);
	  cout << "New radius value is " ;
	  cout << spRadius->Show().ConvertToChar() << endl;
	  
	  // Display the new volume
	  cout << "The new cylinder volume calculated from the VolumeFormula is " ;
	  cout << spVolume->Show().ConvertToChar() << endl;

	  piPublisher->Release();
	  piContainer->Release();
	  piFact->Release();
	  
	  // Close the session and environment
	  rc =  services.CAALifCloseSession ();
	  
	  return rc;
}
