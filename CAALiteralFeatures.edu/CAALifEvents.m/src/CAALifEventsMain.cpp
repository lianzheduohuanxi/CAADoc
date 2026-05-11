// COPYRIGHT DASSAULT SYSTEMES  1999

// ObjectModelerSystem
#include "LifeCycleObject.h"
// KnowledgeInterfaces
#include "CATICkeMagnitude.h"
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"
#include "CATICkeType.h"
#include "CATIParmAsStored.h"
// ObjectSpecsLegacy
#include "CATISpecObject.h"
#include "CATOsmSUHandler.h"
// CAALiteralFeatures.edu
#include "CAAILifMyFeatureEvents.h"
#include "CAALifMyFeatureEventsExt.h"
#include "CAALifReturnCodes.h"
#include "CAALifServices.h"

#include "iostream.h"
/** @quickReview tvq 2001:06:25 */
// ============================================================================
// ABSTRACT
// --------
//
// Illustrates:
//  * how to subscribe to parameter modification events
// The subscription to the "change value", "change visu" and "delete: events
// is defined in the CAALifMyFeatureEventsExp.cpp file of the CAALifBasis.m module.
// 
//=============================================================================
//  Usage:
//  ------
//
//  Your dictionary should include the declaration below:
//  CAAMyFeature            CAAILifMyFeatureEvents	         libCAALifBasis
//=============================================================================

CAALifServices CAAliteralFeaturesServices;

int CAALifEventsExit(CATIContainer*& piContainer, int iReturnCode)
{
	if(piContainer != NULL)
		piContainer->Release();

	piContainer = NULL;

	return iReturnCode;
}

int CAALifEvents0 (const char* iCatalogName)
{

	cout << "--------------------" << endl;
	cout << "Start CAALifEvents" << endl;

	CATUnicodeString startupType( "CAALifSimpleFeature" );	
	CATISpecObject_var hStartupFeat;
	CATISpecObject* piFeat = NULL;

	int returnCode = -99;

	CATIContainer* piContainer = NULL;

	// First create a document and get the root container.
	HRESULT rc = CAAliteralFeaturesServices.CAALifCreateInstanceContainer(&piContainer);
	if( FAILED(rc) || (piContainer == NULL) )
		return CAALifKO;

	cout << "Trying to open catalog saved under the name : " << iCatalogName << endl;

	//Third read the startup of the feature.

	// the object that encapsulates a startup
	CATOsmSUHandler suHandler(startupType, "SAMPLES", "CAA2_CAALifFeatCatalog.CATfct");

	// let's retrieve the startup
	suHandler.RetrieveSU(hStartupFeat);

	CATICkeParmFactory* piFact = NULL;
	HRESULT hr = piContainer -> QueryInterface(IID_CATICkeParmFactory,
		(void**) &piFact);


	// Create a Length parameter of length type - its initial value is  1 meter 
	if( FAILED(hr) )
	{
		cout << "Unable to retrieve the factory. " << endl;
		return CAALifEventsExit( piContainer, CAALifKO );
	}

	CATICkeParm_var spLength = piFact->CreateLength ("Length",1);
	piFact->Release();

	cout << "The p1 value is " << spLength->Show().ConvertToChar() << endl;

	// Define the current unit of a magnitude 
	CATICkeType_var type =  spLength->Type();
	CATICkeMagnitude_var spMag = type;
	spMag->SetCurrentUnit ((*(spMag->Units()))[1]);
	cout << "The p1 value is " << spLength->Show().ConvertToChar() << endl;

	CATUnicodeString featureName("OBJ0");
	piFeat = hStartupFeat -> Instanciate(featureName, piContainer);
	if (NULL == piFeat )
	{
		cout << "Unable to instanciate Feature. " << endl;
		return CAALifEventsExit( piContainer, CAALifKO );		
	} 

	cout << "feature SU instance 1 created OK" << endl << flush;

	CAAILifMyFeatureEvents* piFeatureEvents = NULL;    
	hr = piFeat -> QueryInterface(IID_CAAILifMyFeatureEvents,
		(void**) &piFeatureEvents);
	piFeat->Release();
	piFeat = NULL;

	// Create a Length parameter of length type - its initial value is  1 meter 
	if( FAILED(hr) )
	{
		cout << "Unable to retrieve the factory. " << endl;
		return CAALifEventsExit( piContainer, CAALifKO );
	}

	piFeatureEvents->Observe (spLength);
	piFeatureEvents->Init();

	// Modify the "p1" parameter value               
	CATIParmAsStored_var spStore = spLength;
	spStore->ValuateStored (30);

	// Display the p1 value
	cout << "The p1 value is " << spLength->Show().ConvertToChar() << endl;

	int nChangeValue = 0;
	int nChangeVisu = 0;
	int nDelete = 0;

	piFeatureEvents->GetData( nChangeValue, nChangeVisu, nDelete);
	// Display the number of "change value" notifications
	cout << "Number of \"change value\" notifications (1 is expected) " ;
	cout << nChangeValue << endl;

	// Set the "p1" parameter access right to ReadOnly
	spLength->SetUserAccess(CATICkeParm::ReadOnly);
	piFeatureEvents->GetData( nChangeValue, nChangeVisu, nDelete);  
	// Display the number of "change visu" notifications 
	cout << "Number of \"change visu\" notifications (1 is expected) " ;
	cout << nChangeVisu <<  endl;

	// Modify the current unit of length 
	spMag->SetCurrentUnit ((*(spMag->Units()))[2]);
	cout << "The p1 value is " << spLength->Show().ConvertToChar() << endl;

	piFeatureEvents->GetData( nChangeValue, nChangeVisu, nDelete); 
	// Display the number of "change visu" notifications
	cout << "Number of \"change visu\" notifications (2 is expected) " ;
	cout << nChangeVisu<< endl;

	// Delete the "p1" parameter      
	LifeCycleObject_var spLco = spLength;
	spLco->remove ();
	piFeatureEvents->GetData( nChangeValue, nChangeVisu, nDelete); 
	cout << "Number of \"delete\" notifications (1 is expected)" ;
	cout << nDelete << endl;

	// Delete the CAAILifMyfeatureEvents object 
	piFeatureEvents->Suppress(spLength);
	cout << "End of CAALifEvents" << endl;
	cout << "--------------------" << endl;

	piContainer->Release();
	piFeatureEvents->Release();
	piContainer = NULL;
	piFeatureEvents = NULL;

	return CAALifOk;
}

int main (int argc, char** argv)
{
	int rc;

	// Initialize the environement
	rc = CAAliteralFeaturesServices.CAALifInitSession ();

	if( argc > 1 )
	{
		rc = 		CAALifEvents0( argv[1] );
	}
	else
	{
		rc = 		CAALifEvents0( "CAA2_CAALifFeatCatalog.CATfct");
		rc = CAABadSampleArguments;
		cout << " Not enough arguments " << endl;
	}
	CAAliteralFeaturesServices.CAALifCloseSession();

	return rc;
};


