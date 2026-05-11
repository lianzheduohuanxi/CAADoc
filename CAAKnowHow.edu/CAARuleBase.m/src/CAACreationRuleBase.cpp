// COPYRIGHT DASSAULT SYSTEMES  2002
/**
 * @quickReview TVQ 02.02.15
 */

#include "CAACreationRuleBase.h"

//ObjectModelerBase
#include "CATIContainer.h"

//KnowHow
#include "CATIRuleBaseFactory.h"
#include "CATIRuleSet.h"
#include "CATICheck.h"
#include "CATIRule.h"

//ObjectSpecsModeler
#include "CATISpecObject.h"

#ifndef _IRIX_SOURCE
    #include <iostream.h>
#else
    #include <CC/iostream.h>
#endif

// aggragation
#include "CATIParmPublisher.h"
#include "CATCkeGlobalFunctions.h"

// CAA Services
#include "CATIPrtContainer.h"

/**
* Create the rulebase inside the part.
*/
CATIRuleBase_var CreationRuleBase(CATISpecObject_var ispPart)
{

    if(NULL_var == ispPart  )
        return NULL_var;

	CATIContainer_var spContainer = ispPart->GetFeatContainer();

    if(NULL_var == spContainer  )
        return NULL_var;

    // Get The RUlebase factory.
	CATIRuleBaseFactory_var spRuleBaseFactory = spContainer;
    if(NULL_var == spRuleBaseFactory )
        return NULL_var;

    // Create the rulebase. The second argument is the Root of facts.
    // This Root of facts is the hierarchically highest objects that 
    // will be scanned by the solving mechanism in order to feeds the rules
    // and checks of the rulebase. Note that additional Roots of facts can be 
    // added to the Rulebase (CATIRUleBase::AddRootOfFacts).
	CATIRuleBase_var spRuleBase = spRuleBaseFactory->CreateBase("aRuleBase", ispPart);
    if(NULL_var == spRuleBase )
        return NULL_var;

	//To Replace
	CATIParmPublisher_var root;
	CATIPrtContainer_var prtcont = spContainer;
	if (NULL_var!=prtcont) root= prtcont->GetPart();

	// aggregation to relationset
	 CATCkeGlobalFunctions::GetFunctionFactory()->AddToCurrentRelationSet(spRuleBase,root);
	//-------------------------------------------

    // Create the ruleset in which rules and sets will be agregated.
	CATIRuleSet_var spRuleSet = NULL_var;
    
    HRESULT hr = spRuleBase->CreateRuleset(spRuleSet, "aRuleSetForHoles");
    if( FAILED(hr) )
    {
        cout << "Ruleset creation failed. " << endl;
        return NULL_var;
    }
    else if (NULL_var == spRuleSet )
    {
        cout << "A Ruleset with the same name already exists." << endl;
        return NULL_var;
    }
    else
    {
        cout << "RuleSet creation OK." << endl;
    }
	    
    CATICheck_var spCheck = NULL_var;
    HRESULT hr2 = spRuleSet->CreateCheck(spCheck, "CheckOnHoles", 
        "H1 : Hole", 
        "H1.Diameter <= 15mm");

    if( FAILED(hr2) )
    {
        cout << "Check creation failed. " << endl;
        return NULL_var;
    }
    else if (NULL_var == spCheck )
    {
        cout << "A Check with the same name already exists in this ruleset." << endl;
        return NULL_var;
    }
    else
    {
        cout << "Check creation OK." << endl;
    }
    cout<<" nom du check "<<spCheck->GetGenericRuleBaseComponentName().ConvertToChar()<<endl;
	CATISpecObject_var speccheck = spCheck;
	if (!!speccheck)
		speccheck->SetDisplayName("toto");
    cout<<" nom du check "<<spCheck->GetGenericRuleBaseComponentName().ConvertToChar()<<endl;
	if (!!speccheck)
		cout<<" nom du check "<<speccheck->GetDisplayName().ConvertToChar()<<endl;

    
    
    //Create the rule.
    CATIRule_var spRule = NULL_var;
    HRESULT hr3 = spRuleSet->CreateRule(spRule, "RuleOnHoles", //name
        "H1 : Hole",                                                    //scope
        "if (H1.Diameter > 15mm) { H1.Diameter = H1.Diameter / 2 }"); // body
    if( FAILED(hr3) )
    {
        cout << "Rule creation failed. " << endl;
        return NULL_var;
    }
    else if (NULL_var == spRule )
    {
        cout << "A rule with the same name already exists in this ruleset." << endl;
        return NULL_var;
    }
    else
    {
        cout << "Rule creation OK." << endl;
    }


    //Creating a second ruleset in the rulebase.
	CATIRuleSet_var spRuleSet2 = NULL_var;
    
    HRESULT hr4 =spRuleBase->CreateRuleset(spRuleSet2, "aRuleSetForDrafts");
    if( FAILED(hr4) )
    {
        cout << "Ruleset creation failed. " << endl;
        return NULL_var;
    }
    else if (NULL_var == spRuleSet2 )
    {
        cout << "A Ruleset with the same name already exists." << endl;
        return NULL_var;
    }
    else
    {
        cout << "RuleSet creation OK." << endl;
    }
	

    CATICheck_var spCheck2 = NULL_var;   
    HRESULT hr5 =spRuleSet2->CreateCheck(spCheck2, "CheckOnDrafts", 
        "D1 : Draft; D2 : Draft", 
        "D1 > D2 => D1.Angle > D2.Angle");
    if( FAILED(hr5) )
    {
        cout << "Check creation failed. " << endl;
        return NULL_var;
    }
    else if (NULL_var == spCheck2 )
    {
        cout << "A Check with the same name already exists in this ruleset." << endl;
        return NULL_var;
    }
    else
    {
        cout << "Check creation OK." << endl;
    }

	return spRuleBase;
}
