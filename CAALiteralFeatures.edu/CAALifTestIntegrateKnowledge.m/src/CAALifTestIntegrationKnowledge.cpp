// COPYRIGHT DASSAULT SYSTEMES  2003

//============================================================================
//  Abstract:
//  ---------
//	This Use Case tastes:
//		- the creation and the usage of User types
//		- the manipulation of an instance of a user type
//
//    
//============================================================================

// OS
#include <iostream.h>
// ObjectModelerSystem
#include "LifeCycleObject.h"
// ObjectModelerBase
#include "CATIContainer.h"
// KnowledgeInterfaces
#include "CATCkeGlobalFunctions.h"
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"
#include "CATICkeRelation.h"
#include "CATICkeSignature.h"
#include "CATIParmDictionary.h"
#include "CATITypeDictionary.h"
// ObjectSpecsLegacy
#include "CATISpecAttrAccess.h"
#include "CATISpecAttribute.h"
#include "CATISpecAttrKey.h"
#include "CATISpecObject.h"
#include "CATOsmSUHandler.h"
// CAALiteralFeatures.edu
#include "CAALifReturnCodes.h"
#include "CAALifServices.h"

//-----------------------------------------------------------------------------------------
// Manage the program exit
//-----------------------------------------------------------------------------------------
int CAALifProgramExit(CATIContainer*& piContainer, int iReturnCode)
{
	if( piContainer != NULL)
		piContainer->Release();

	piContainer = NULL;

	return iReturnCode;
}

CAALifServices CAAliteralFeaturesServices;

//-----------------------------------------------------------------------------------------
// What to do
//-----------------------------------------------------------------------------------------
CATCke::Boolean CAALifObjectUserView0()
{
	CATUnicodeString startupType( "CAALifFeatureScrew" );	
	CATISpecObject_var hStartupFeat;
	CATIContainer* piContainer = NULL;


	//Creating a document and get the root container
	//--------------------------------------------
	HRESULT rc = CAAliteralFeaturesServices.CAALifCreateInstanceContainer(&piContainer);
	if( FAILED(rc) )
		return CAALifKO;



	//Reading the startup "CAALifFeatureScrew"
	//-------------------------------------
	
	// the object that encapsulates a startup
	CATOsmSUHandler suHandler(startupType, "SAMPLES", "CAA2_CAALifFeatCatalog.CATfct");

	// let's retrieve the startup
	suHandler.RetrieveSU(hStartupFeat);

	
	//Loading the package defined by the user and testing its contents
	//----------------------------------------------------------------
	CATITypeDictionary_var dico = CATGlobalFunctions::GetTypeDictionary();
	CATUnicodeString package_name = "DoItYourself";
	rc = dico->LoadPackage(package_name);

	//The package has not been found
	if( FAILED(rc) )
	{
		cout << "ERROR in searching the DoItYourself package" << endl;
		return CAALifProgramExit( piContainer, CAALifKO );
	}
	//The package has been found - Let's check its contents
	else
	{
		cout << "The DoItYourself package has been found" << endl;

		//Checking the number of types in the package (there must be 2)
		CATListValCATIType_var listTypes;
		dico->ListTypesForPackage(package_name,listTypes,0);
		int numberTypes = listTypes.Size();

		if (numberTypes != 2)
		{
			cout << "ERROR: Invalid number of types : " << numberTypes <<  endl;
			return CAALifProgramExit( piContainer, CAALifKO );
		}
		else
			cout << "The package DoItYourself contains the right number of types (2)" << endl;

		//Searching the first type
		CATIType_var ScrewType;
		rc = dico->FindType("Screw",ScrewType);
		if (ScrewType != NULL_var)
			cout << ScrewType->Name().ConvertToChar() << " has been found" << endl;
		else
		{
			cout << "ERROR Invalid type" << endl;
			return 1;
		}

		//Searching the second type
		CATIType_var BoltType;
		rc = dico->FindType("Bolt",BoltType);
		if (BoltType != NULL_var)
			cout << BoltType->Name().ConvertToChar() << " has been found" << endl;
		else
		{
			cout << "ERROR Invalid type" << endl;
			return 1;
		}
	}

	//Retrieving the parameters factory
	//---------------------------------
	CATICkeParmFactory* piFact = NULL;
	rc = piContainer->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);

	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATICkeParmFactory from container" << endl;
		return CAALifProgramExit( piContainer, CAALifKO );
	}


	//Creating an instance of the startup
	//------------------------------------
	CATISpecObject* ScrewObj = hStartupFeat->Instanciate ("my_screw_obj",piContainer);
	
	//ScrewObj released at the end

	if (ScrewObj == NULL)
	{
		cout << "Unable to instanciate the startup. " << endl;
		piFact->Release();
		return CAALifProgramExit( piContainer, CAALifKO );
	}	


	//Creating data to valuate the screw instance
	//--------------------------------------------
	CATICkeParm_var length_parm   = piFact->CreateLength ("Length",0.1);
	CATICkeParm_var headdiam_parm = piFact->CreateLength ("HeadDiam",0.05);
	CATICkeParm_var stemdiam_parm = piFact->CreateLength ("StemDiam",0.02);



	// Putting the data into the screw attributes
	//--------------------------------------------

	// Sets the ScrewLength Attribute
	CATISpecAttrAccess * piSpecAttrAccessOnScrewLength = NULL; 
	rc = ScrewObj->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnScrewLength);
	if ( SUCCEEDED(rc) ) 
	{ 
		CATISpecAttrKey * piSpecAttrKeyOnScrewLength = NULL;    
		piSpecAttrKeyOnScrewLength = piSpecAttrAccessOnScrewLength->GetAttrKey("ScrewLength");

		if ( NULL != piSpecAttrKeyOnScrewLength )
		{
			piSpecAttrAccessOnScrewLength->SetSpecObject(piSpecAttrKeyOnScrewLength,length_parm);
			piSpecAttrKeyOnScrewLength->Release();
			piSpecAttrKeyOnScrewLength = NULL;
		}
	}
	piSpecAttrAccessOnScrewLength->Release();
	piSpecAttrAccessOnScrewLength = NULL;

	// Sets the ScrewHeadDiameter Attribute
	CATISpecAttrAccess * piSpecAttrAccessOnScrewHeadDiam = NULL; 
	rc = ScrewObj->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnScrewHeadDiam);
	if ( SUCCEEDED(rc) ) 
	{ 
		CATISpecAttrKey * piSpecAttrKeyOnScrewHeadDiam = NULL;    
		piSpecAttrKeyOnScrewHeadDiam = piSpecAttrAccessOnScrewHeadDiam->GetAttrKey("ScrewHeadDiameter");

		if ( NULL != piSpecAttrKeyOnScrewHeadDiam )
		{
			piSpecAttrAccessOnScrewHeadDiam->SetSpecObject(piSpecAttrKeyOnScrewHeadDiam,headdiam_parm);
			piSpecAttrKeyOnScrewHeadDiam->Release();
			piSpecAttrKeyOnScrewHeadDiam = NULL;
		}
	}
	piSpecAttrAccessOnScrewHeadDiam->Release();
	piSpecAttrAccessOnScrewHeadDiam = NULL;


	// Sets the ScrewStemDiameter Attribute
	CATISpecAttrAccess * piSpecAttrAccessOnScrewStemDiam = NULL; 
	rc = ScrewObj->QueryInterface(IID_CATISpecAttrAccess, (void**) & piSpecAttrAccessOnScrewStemDiam);
	if ( SUCCEEDED(rc) ) 
	{ 
		CATISpecAttrKey * piSpecAttrKeyOnScrewStemDiam = NULL;    
		piSpecAttrKeyOnScrewStemDiam = piSpecAttrAccessOnScrewStemDiam->GetAttrKey("ScrewStemDiameter");

		if ( NULL != piSpecAttrKeyOnScrewStemDiam )
		{
			piSpecAttrAccessOnScrewStemDiam->SetSpecObject(piSpecAttrKeyOnScrewStemDiam,stemdiam_parm);
			piSpecAttrKeyOnScrewStemDiam->Release();
			piSpecAttrKeyOnScrewStemDiam = NULL;
		}
	}
	piSpecAttrAccessOnScrewStemDiam->Release();
	piSpecAttrAccessOnScrewStemDiam = NULL;



	// Retrieving the CATIInstance interface on the SpecObject
	//---------------------------------------------------------
	CATIInstance* piInstance = NULL;
	rc = ScrewObj->QueryInterface(IID_CATIInstance, (void**) &piInstance);

	//piInstance released at the end

	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATIInstance from spec object" << endl ;
		piFact->Release();
		ScrewObj->Release();
		return CAALifProgramExit( piContainer, CAALifKO );
	} 

	// Checking the type of the screw object with CATIInstance
	//---------------------------------------------------------
	CATIType_var TypeInDico = piInstance->Type();  

	if (TypeInDico != NULL_var)
	{
		TypeInDico->Release();
		CATUnicodeString TypeName = TypeInDico->Name();
		CATUnicodeString StrTest = "Screw";
		if (TypeName != StrTest)
		{
			cout << "The type name " << TypeName.ConvertToChar() << " is uncorrect." << endl;
			piFact->Release();
			ScrewObj->Release();
			piInstance->Release();
			return CAALifProgramExit( piContainer, CAALifKO );
		}
		else
		{
			cout << "The type name " << TypeName.ConvertToChar() << " is correct." << endl;

			//Let's check if the type is in the correct package
			CATIType_var TypeInPackage = NULL_var;
			rc = dico->FindTypeInPackage(TypeName,package_name,TypeInPackage);
			if (FAILED(rc))
			{
				cout << "Type hasn't been found in the package " << package_name.ConvertToChar() << endl;
				piFact->Release();
				ScrewObj->Release();
				piInstance->Release();
				return CAALifProgramExit( piContainer, CAALifKO );
			}
			else
				cout << "The type is in the correct package " << package_name.ConvertToChar() << endl;
		}

	}
	else
	{
		cout << "ERROR: the type hasn't been found" << endl;
		piFact->Release();
		ScrewObj->Release();
		piInstance->Release();
		return CAALifProgramExit( piContainer, CAALifKO );
	}

	// Reading the attribute of the screw object through CATIInstance
	//----------------------------------------------------------------
	CATIValue_var value = NULL_var;
	int cleaning = 0;

	// Attribute 1
	double V = 0.0;
	value = piInstance->GetValue("ScrewLength");
	if (value != NULL_var)
	{
		value->AsReal(V);
		value->Release(); 
		if (V != 0.1)
		{
			cout << "uncorrect value for ScrewLength = " <<V << endl;
			cleaning = 1;
		}
		else
			cout << "ScrewLength value is OK = " <<V <<endl;
	}

	// Attribute 2
	value = piInstance->GetValue("ScrewHeadDiameter");
	if (value != NULL_var)
	{
		value->AsReal(V);
		value->Release();
		if (V != 0.05)
		{
			cout << "uncorrect value for ScrewHeadDiameter = " << V << endl;
			cleaning = 1;
		}
		else
			cout << "ScrewHeadDiameter value is OK = " << V <<endl;
	}

	// Attribute 3
	value = piInstance->GetValue("ScrewStemDiameter");
	if (value != NULL_var)
	{
		value->AsReal(V);
		value->Release();
		if (V != 0.02)
		{
			cout << "uncorrect value for ScrewStemDiameter = " << V << endl;
			cleaning = 1;
		}
		else
			cout << "ScrewStemDiameter value is OK = " << V <<endl;
	}

	// If attribute 1,2 or 3 is uncorrect ...
	if (cleaning)
	{
		piFact->Release();
		ScrewObj->Release();
		piInstance->Release();
		return CAALifProgramExit( piContainer, CAALifKO );
	}


	// Modifying the attributes of the screw object through CATIInstance
	//-------------------------------------------------------------------

	CATICkeParmFactory_var VolFactory = CATCkeGlobalFunctions::GetVolatileFactory();
	if(VolFactory == NULL_var)
	{
		cout << "Unable to retrieve the volatile factory" << endl << endl;
		cleaning = 1;
	}

	rc = piInstance->SetValue("ScrewLength", VolFactory->CreateLength("L1",0.25));
	if (FAILED(rc)) 
	{
		cout << "ERROR in SetValue of CATIInstance on ScrewLength Attr" << endl << flush;
		cleaning = 1;
	} 

	piInstance->SetValue("ScrewHeadDiameter", VolFactory->CreateLength("L2",0.045));
	if (FAILED(rc)) 
	{
		cout << "ERROR in SetValue of CATIInstance on ScrewHeadDiameter Attr" << endl << flush;
		cleaning = 1;
	} 

	piInstance->SetValue("ScrewStemDiameter", VolFactory->CreateLength("L3",0.01));
	if (FAILED(rc)) 
	{
		cout << "ERROR in SetValue of CATIInstance on ScrewStemDiameter Attr" << endl << flush;
		cleaning = 1;
	} 


	if (cleaning)
	{
		piFact->Release();
		ScrewObj->Release();
		piInstance->Release();
		return CAALifProgramExit( piContainer, CAALifKO );
	}

	// Re - Reading the attribute of the screw object through CATIInstance
	//---------------------------------------------------------------------

	// Attribute 1
	value = piInstance->GetValue("ScrewLength");
	if (value != NULL_var)
	{	
		value->AsReal(V);
		value->Release();
		if (V != 0.25)
		{
			cout << "uncorrect value for ScrewLength = " <<V << endl;
			cleaning = 1;
		}
		else
			cout << "ScrewLength value is OK = " <<V <<endl;
	}

	// Attribute 2
	value = piInstance->GetValue("ScrewHeadDiameter");
	if (value != NULL_var)
	{
		value->AsReal(V);
		value->Release();
		if (V != 0.045)
		{
			cout << "uncorrect value for ScrewHeadDiameter = " <<V << endl;
			cleaning = 1;
		}
		else
			cout << "ScrewHeadDiameter value is OK = " <<V <<endl;
	}

	// Attribute 3
	value = piInstance->GetValue("ScrewStemDiameter");
	if (value != NULL_var)
	{
		value->AsReal(V);
		value->Release();
		if (V != 0.01)
		{
			cout << "uncorrect value for ScrewStemDiameter = " <<V << endl;
			cleaning = 1;
		}
		else
			cout << "ScrewStemDiameter value is OK = " <<V <<endl;
	}

	// If attribute 1,2 or 3 is uncorrect ...
	if (cleaning)
	{
		piFact->Release();
		ScrewObj->Release();
		piInstance->Release();
		return CAALifProgramExit( piContainer, CAALifKO );
	}


	// Searching the user function in the package
	//-------------------------------------------
	CATListValCATBaseUnknown_var listOfSignatures;
	rc = dico->ListMethodsForPackage("CATPackageMethodDoItYourself", listOfSignatures);
	CATICkeParm_var spVolume;
	CATICkeRelation_var	spFormula;
	if (SUCCEEDED(rc))
	{
		cleaning = 0;
		int nbOfMethods = listOfSignatures.Size();
		if (nbOfMethods != 1)
		{
			cout << "Error: this package has no methods" << endl;
			cleaning = 1;
		}
		else
		{
			CATICkeSignature_var aSignature = listOfSignatures[1];
			CATUnicodeString name = aSignature->Name();
			CATUnicodeString StrTest = "EvaluateScrewVolume";
			if (name != StrTest)
			{
				cout << "The method EvaluateScrewVolume has not been found" << endl;
				cleaning = 1;
			}
			else
			{
				cout << "The method EvaluateScrewVolume has been found" << endl;
			}
		}

		// Executing the user function through a formula
		//----------------------------------------------
		CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();

		// creating the returned volume parameter 
		CATICkeMagnitude_var spVolumeMagnitude = spParmDictionary->FindMagnitude("VOLUME");

		if (NULL_var != spVolumeMagnitude)
		{      
			CATUnicodeString VolumeName("ScrewVolume");
			double VolumeValue = 0.0;
			spVolume = piFact->CreateDimension(spVolumeMagnitude,VolumeName,VolumeValue);

			// Transformation of the screw in a parameter
			CATICkeParm_var ScrewParm = VolFactory->CreateObjectReference(ScrewObj);

			// Create the list of parameters to be used in the formula
			CATCkeListOf(Parm) pParamList;
			pParamList.Append (spVolume);
			pParamList.Append (ScrewParm);

			//creation of the formula
			spFormula = piFact->CreateFormula ("VolumeFormula",
				"",
				"", 
				spVolume, 
				&pParamList,
				"EvaluateScrewVolume(a2)",
				NULL_var,
				CATCke::False);

			if (spFormula != NULL_var)
			{
				cout << "The old screw volume calculated from the VolumeFormula is " ;
				cout << spVolume->Show().ConvertToChar() << endl;

				rc = piInstance->SetValue("ScrewLength", VolFactory->CreateLength("L1",0.19));
				if (FAILED(rc)) 
				{
					cout << "ERROR in SetValue of CATIInstance on ScrewLength Attr" << endl << flush;
					cleaning = 1;
				} 
				else
				{
					spFormula->SetNotUpdated(ScrewParm);
					spFormula->Evaluate();
					cout << "The new screw volume calculated from the VolumeFormula is " ;
					cout << spVolume->Show().ConvertToChar() << endl;
				}

			}
			else
				cout << "Error when creating the formula "<< endl;
		}


		if (cleaning)
		{
			piFact->Release();
			ScrewObj->Release();
			piInstance->Release();
			LifeCycleObject_var life = spVolume;
			if (life != NULL_var)
				life->remove();
			life = spFormula;
			if (life != NULL_var)
				life->remove();
			return CAALifProgramExit( piContainer, CAALifKO );
		}

	}

	// managing the end ...
	//-----------------------

	piFact->Release();
	ScrewObj->Release();
	piInstance->Release();
	LifeCycleObject_var life = spVolume;
	if (life != NULL_var)
		life->remove();
	life = spFormula;
	if (life != NULL_var)
		life->remove();


	piFact = NULL;
	ScrewObj = NULL;
	piInstance = NULL;

	CAALifProgramExit( piContainer, CAALifOk );

	return CATCke::True;
}


//-----------------------------------------------------------------------------------------
// Main Function
//-----------------------------------------------------------------------------------------
int main (int argc, char** argv)
{
	int rc = 0;

	// Initialize the session
	rc = CAAliteralFeaturesServices.CAALifInitSession ();
	if( rc != CAALifOk )
		return rc;

	CAALifObjectUserView0();

	// Close the session and environment
	CAAliteralFeaturesServices.CAALifCloseSession();

	return rc;
};
