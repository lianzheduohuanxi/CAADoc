// COPYRIGHT DASSAULT SYSTEMES  1999

#include <CAALifRuleCheck.h>
#include "iostream.h"

// ObjectModelerBase
#include "CATIContainer.h"
#include "CATISpecObject.h"

// LiteralFeatures
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"
#include "CATICkeRelationExp.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"

// ======================================================================
// 
// ABSTRACT
// --------
//
// Illustrates how to:
//   * create the rule below:
//      If (Width > 9 m)
//        {v=Width*Length*Height}
//      else{v=100*surface*Length}
//   * display its body or expression
//   * create a check.
//
// ======================================================================
 


CATCke::Boolean CAALifRuleCheck(CATIParmPublisher* ipRoot)
{

	// find the root to aggregate the relationset
	CATCkeListOf(Parm) list;
	CATICkeParm_var spWidth, spLength, spHeight, spVolume, spArea;

	// find the parameterset
	CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter,ipRoot,CATCke::True);
	if (!!spParameterSet)
	{
		// find the factory
		CATICkeParmFactory_var spParmFactory = spParameterSet->GetFeatContainer();
		if (!!spParmFactory)
		{

			// Create the required literals
			spWidth   = spParmFactory->CreateLength("Width",10);   
			spLength  = spParmFactory->CreateLength("Length",12);   
			spHeight  = spParmFactory->CreateLength("Height",18);   
			spVolume  = spParmFactory->CreateDimension (CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("VOLUME"),
				"v",
				0.2); 
			spArea    = spParmFactory->CreateDimension (CATCkeGlobalFunctions::GetParmDictionary()->FindMagnitude("AREA"),
				"surface",
				0.1); 

			// It is important (but not necessary) to aggregate those parameters especially in part context
			CATIParmPublisher_var spParmPublisher = spParameterSet;
			if (!!spParmPublisher)
			{
				spParmPublisher->Append(spWidth);
				spParmPublisher->Append(spLength);
				spParmPublisher->Append(spHeight);
				spParmPublisher->Append(spVolume);
				spParmPublisher->Append(spArea);
			}

			// Build the parameter list 
			list.Append (spWidth);
			list.Append (spLength);
			list.Append (spHeight);
			list.Append (spVolume);
			list.Append (spArea);
		}
	}

	CATICkeRelation_var spRule1;
	CATICkeParmFactory_var spRelationFactory ;

	CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,ipRoot,CATCke::True);
	if (!!spRelationSet)
	{
		// find the factory
		spRelationFactory = spRelationSet->GetFeatContainer();
		if (!!spRelationFactory)
		{

			// Create a rule
			spRule1 = spRelationFactory->CreateProgram ("rel1",
				"",
				"",
				&list,
				" if (a1 > 9 m) \n {a4 = a1*a2*a3} \n else {a4 = 100*a5*a2}",
				NULL_var,
				CATCke::False);
			
			// It is important (but not necessary) to aggregate those parameters especially in part context
			CATIParmPublisher_var spParmPublisher = spRelationSet;
			if (!!spParmPublisher)
				spParmPublisher->Append(spRule1);

		}
	}
	
	// Display the rule body
	CATICkeRelationExp_var spExp0 = spRule1 ;
	if (spExp0 != NULL_var)
	{
		cout << "The rule body is: ";
		cout << (spExp0->Body(1,NULL_var)).ConvertToChar() << endl;  
	}
	else
	{
		cout << "The rule cannot be created" << endl;
	}
	
	// Display the Volume     
	cout << "Volume calculated from rule (2160 m3 expected): " ;
	cout << spVolume->Show().ConvertToChar() << endl;
	
	// Modify the Width parameter
	spWidth->Valuate(3);
	
	// Check the volume update
	cout << "Volume calculated from rule after Width is modified (120 m2 expected):" ;
	cout << spVolume->Show().ConvertToChar() << endl;
	
	// Create a check                          
	CATICkeRelation_var 
		spCheck1 = spRelationFactory->CreateCheck ("chl","","",&list,"a2 > a3",NULL_var,CATCke::False);

	// It is important (but not necessary) to aggregate those parameters especially in part context
	CATIParmPublisher_var spParmPublisher = spRelationSet;
	if (!!spParmPublisher)
		spParmPublisher->Append(spCheck1);
		
	
	CATICkeRelationExp_var spExp1 = spCheck1 ;
	if (spExp1 != NULL_var)
    {
		cout << "The check body is: ";
		cout << (spExp1->Body(1,NULL_var)).ConvertToChar() << endl;  
    }  
	else
    {
		cout << "The check cannot be created" << endl;
    }
	return CATCke::True;
}
