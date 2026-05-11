// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CAALifFormula.h"
#include "iostream.h"

// ObjectModelerBase
#include "CATIContainer.h"
#include "CATISpecObject.h"

// LiteralFeatures
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"
#include "CATICkeInst.h"
#include "CATICkeRelation.h"
#include "CATICkeRelationExp.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"
#include "CATIKweActivable.h"


//CAALiteralFeatures
#include "CAALifReturnCodes.h"
// =========================================================================
//
// ABSTRACT
// --------
// 
// Illustrates how to:
//   * create parameters
//   * create a formula which extracts a substring from a string
//   * modify the formula expression
//   * retrieve and modify the activity of the formula.
//
// =========================================================================

void ExtractStringFromParm( CATICkeParm* iParm, CATUnicodeString& oString)
{
	  if( NULL != iParm )
	  {
			CATICkeInst_var spInst = iParm->Value();
			oString = spInst->AsString();
	  }
}



CATCke::Boolean CAALifFormula(CATIParmPublisher* ipRoot)
{
	cout << "Example of Formulas creation" << endl << endl;  

	CATCkeListOf(Parm) list;
	CATICkeParm_var spString1,spString2,spString3;
	
	// find the parameterset
	CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,ipRoot,CATCke::True);
	if (!!spParameterSet)
	{
		// find the factory
		CATICkeParmFactory_var spParmFactory = spParameterSet->GetFeatContainer();
		if (!!spParmFactory)
		{
			// Create the required literals into correct container
			spString1 = spParmFactory->CreateString ("ModuleName","CAALifRelations");
			spString2 = spParmFactory->CreateString ("ProjectKey","");   
			spString3 = spParmFactory->CreateString ("Topic","Formulas");  
			
			// It is important (but not necessary) to aggregate those parameters especially in part context
			CATIParmPublisher_var spParmPublisher = spParameterSet;
			if (!!spParmPublisher)
			{
				spParmPublisher->Append(spString1);
				spParmPublisher->Append(spString2);
				spParmPublisher->Append(spString3);
				
				// deprecated
				/*CATCkeGlobalFunctions::GetFunctionFactory()->AddToCurrentParameterSet(spString1);
				CATCkeGlobalFunctions::GetFunctionFactory()->AddToCurrentParameterSet(spString2);
				CATCkeGlobalFunctions::GetFunctionFactory()->AddToCurrentParameterSet(spString3);*/
			}
			
			// Build the parameter list 
			list.Append (spString1);
			list.Append (spString2);
			list.Append (spString3);
		}
	}
	CATICkeRelation_var	spFormula;

	CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,ipRoot,CATCke::True);
	if (!!spRelationSet)
	{
		// find the factory
		CATICkeParmFactory_var spParmFactory = spRelationSet->GetFeatContainer();
		if (!!spParmFactory)
		{
			
			// Create a formula which extracts a substring from a string
			spFormula = spParmFactory->CreateFormula ("ExtractForm",
				"",
				"",
				spString2,
				&list,
				"a1.Extract(0,6)",
				NULL_var,
				CATCke::False);
			
			// It is important (but not necessary) to aggregate those parameters especially in part context
			CATIParmPublisher_var spParmPublisher = spRelationSet;
			if (!!spParmPublisher)
				spParmPublisher->Append(spFormula);
			// deprecated
//			CATCkeGlobalFunctions::GetFunctionFactory()->AddToCurrentRelationSet(spFormula);
			
		}
	}

	
	// Display the string extracted - 'CAALif' is expected
	CATUnicodeString key;
	ExtractStringFromParm( spString2, key );
	cout << "The project key is (Extract0,6) -> CAALif: " ;
	cout << key.ConvertToChar() << endl; 
	  
	// Modify the formula - Replace a1.Extract(0,6) with a3.Extract(0,5)
	CATICkeRelationExp* ipExpForm = NULL;
	HRESULT rc = spFormula->QueryInterface(IID_CATICkeRelationExp, (void**) &ipExpForm);
	if (FAILED(rc)) 
	{
		cout << "ERROR in QueryInterface on CATICkeRelationExp from Formula" << endl << flush;
		return CAALifKO;
	}	
	ipExpForm->Modify(&list,"a3.Extract(0,5)", NULL_var, CATCke::False);
	  
	// Test the relation activity
	CATIKweActivable_var hKweActivable = spFormula;
	int IsActive=1;
	hKweActivable->IsActivated(IsActive);
	cout << "Formula activation is : " << IsActive << endl;
	  
	// Display the string extracted 
	ExtractStringFromParm( spString2, key );
	cout << "The project key now is (still the same): " ;
	cout << key.ConvertToChar()  << endl; 
	  
	// Re-activate the formula
	hKweActivable->SetActivationStatus(1);
	ExtractStringFromParm( spString2, key );	
	cout << "The project key after the re-activation is: " ;
	cout << key.ConvertToChar()  << endl;
	  
	ipExpForm->Release();	
	
	cout << "End of Formulas Test." << endl << endl;
	
	return CATCke::True;
}

