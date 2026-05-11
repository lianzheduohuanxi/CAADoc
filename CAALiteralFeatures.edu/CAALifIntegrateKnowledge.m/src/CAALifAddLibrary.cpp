// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CAALifAddLibrary.cpp
//
// Provides implementation to interface CATIAddTypeLibrary in order to
// create 2 new user types:
//		- Screw
//		- Bolt
//
// and 1 new user function:
//		- EvaluateScrewVolume
// 
// Types are grouped in a "DoItYourself" package.
// The function is in the associated method package.
//
//===================================================================


#include "CAALifAddLibrary.h"
#include "CATGlobalFunctions.h"
#include "CATCkeGlobalFunctions.h"
#include "CATITypeDictionary.h"
#include "CATIParmDictionary.h"
#include "CATICkeParm.h"
#include "CATICkeInst.h"
#include "CATISpecObject.h"
#include "iostream.h"

CATImplementClass(CAALifAddLibrary, Implementation, CATBaseUnknown, CATnull );

#include "TIE_CATIAddTypeLibrary.h"
TIE_CATIAddTypeLibrary( CAALifAddLibrary );

//-----------------------------------------------------------------------------
// CAALifAddLibrary : constructor
//-----------------------------------------------------------------------------
CAALifAddLibrary::CAALifAddLibrary()
{
}

//-----------------------------------------------------------------------------
// CAALifAddLibrary : destructor
//-----------------------------------------------------------------------------
CAALifAddLibrary::~CAALifAddLibrary()
{
}

//-----------------------------------------------------------------------------
// Evaluator of user function
//-----------------------------------------------------------------------------
void VolumeFunction (CATCkeListOfParm lis,const CATICkeParm_var &res,const CATCkeEvalContext *pevalcontext)
{

  // getting the arguments
  CATICkeParm_var pa1 =  (*lis)[1];
  
  double pL = 0.0;

  if (pa1 != NULL_var)
  {
  
	CATICkeInst_var inst = pa1->Value();
  
	if (inst != NULL_var)
	{
		CATISpecObject_var ScrewObj = inst->AsObject();

		CATIInstance* piInstance = NULL;
		HRESULT rc = ScrewObj->QueryInterface(IID_CATIInstance, (void**) &piInstance);

		double d1 = 0.0;
		double d2 = 0.0;
		double d3 = 0.0;

		if (piInstance)
		{
			CATIValue_var value = NULL_var;

			value = piInstance->GetValue("ScrewLength");
			if (value != NULL_var)
			{
				value->AsReal(d1);
				value->Release();
			}
		
			value = piInstance->GetValue("ScrewHeadDiameter");
			if (value != NULL_var)
			{
				value->AsReal(d2);
				value->Release();
			}

			value = piInstance->GetValue("ScrewStemDiameter");
			if (value != NULL_var)
			{
				value->AsReal(d3);
				value->Release();
			}

			piInstance->Release();
		}

		pL = ((3.14 * d2 * d2) * 0.05) + ((3.14 * d3 * d3) * d1);

	}	

  }
  
  res->Valuate(pL);

}

//-----------------------------------------------------------------------------
// CAALifAddLibrary : Add - Add 2 user types and 1 user function
//-----------------------------------------------------------------------------
void CAALifAddLibrary::Add()
{
	CATITypeDictionary_var dico = CATGlobalFunctions::GetTypeDictionary();
	if (NULL_var == dico)  return;
	
	HRESULT rc;
	
	// Adding the "DoItYourself" package
	CATListOfCATUnicodeString iListOfPrerequisites;
	rc = dico->AddPackage( "DoItYourself", iListOfPrerequisites );
	
	if (FAILED(rc)) return;

	// Type "Screw" and "Bolt"
	CATIType_var typeScrew = NULL_var;
	CATIType_var typeBolt = NULL_var;

	CATIParmDictionary_var spParmDictionary = CATCkeGlobalFunctions::GetParmDictionary();
   	CATICkeType_var spType = NULL_var;
   	CATICkeType_var spType2 = NULL_var;
  	spType = spParmDictionary->GetLengthType();
  	spType2 = spParmDictionary->GetFeatureType();
  
	// Screw type creation
	CATAttributeInfos attributeScrewDiameter( spType, "HeadDiameter", "HeadDiameter", 1, 1 );
	CATAttributeInfos attributeScrewSmallDiameter( spType, "StemDiameter", "StemDiameter", 1, 1 );
	CATAttributeInfos attributeScrewLength( spType, "ScrewLength", "ScrewLength", 1, 1 );
	CATAttributeInfos attributeCenterPoint( spType2, "CenterPoint", "CenterPoint", 1, 1 );
	
	CATListValCATAttributeInfos listAttributesScrew;
	listAttributesScrew.Append( attributeScrewDiameter );
	listAttributesScrew.Append( attributeScrewSmallDiameter );
	listAttributesScrew.Append( attributeScrewLength );
	listAttributesScrew.Append( attributeCenterPoint );
	
	dico->CreateType( "Screw", "Screw", NULL_var, typeScrew, &listAttributesScrew);
	dico->AddTypeForPackage( typeScrew, "DoItYourself" );

	// Bolt type creation
	CATAttributeInfos attributeBoltInDiameter( spType, "InDiameter", "InDiameter", 1, 1 );
	CATAttributeInfos attributeBoltOutDiameter( spType, "OutDiameter", "OutDiameter", 1, 1 );
	
	CATListValCATAttributeInfos listAttributesBolt;
	listAttributesBolt.Append( attributeBoltInDiameter );
	listAttributesBolt.Append( attributeBoltOutDiameter );
	
	dico->CreateType( "Bolt", "Bolt", NULL_var, typeBolt, &listAttributesBolt);
	dico->AddTypeForPackage( typeBolt, "DoItYourself" );


    // User Function creation
    CATICkeType_var ReturnedType = NULL_var;
    ReturnedType = spParmDictionary->GetRealType();
    
    CATICkeFunctionFactory_var funcFactory = CATCkeGlobalFunctions::GetFunctionFactory();

    CATICkeSignature_var spSign = funcFactory->CreateFunction ("EvaluateScrewVolume",ReturnedType,VolumeFunction,NULL,CATICkeSignature::Function);

    //Arguments of the user function
	spSign->AddArgument (funcFactory->CreateArg ("iA",typeScrew));

	rc = dico->AddPackage( "CATPackageMethodDoItYourself", iListOfPrerequisites );
	if (FAILED(rc)) return;

    dico->AddMethodForPackage( spSign, "CATPackageMethodDoItYourself" );

}
