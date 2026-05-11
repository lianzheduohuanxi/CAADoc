// COPYRIGHT DASSAULT SYSTEMES  2002

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which shows how use Reference RuleBase. You have 3 possibilities to use
//  a RuleBase :
//  - import RuleBase into document
//  - import RuleBase with a link to the document which contains RuleBase
//  - use volatile RuleBase
//
//
//
//  Note on rule bases structure:
//  KnowledgeExpert rules are regrouped inside Rulesets.
//  Rulesets are aggregated by a single Rulebase.    
//  This RuleBase can then be "solved".
//  
//  
//============================================================================
//  Usage:
//  ------
//          ReferenceRuleBase.CATProduct and Hole.CATPart should exist.
//          Types can be retrieved from interactive view (knowledge expert wizard).
//          Each type belongs to a package (implemenation of CATIAddTypeLibrary)
//          that can be retrieved from Tools/Option/General/Parameters 
//          
//          To run this sample, you can use the command:
//          mkrun -c "CAARuleBaseImport <root>\CAAKnowHow.edu\CNext\resources\graphic\ "
//          don't forget blank before the last ". 
//          where <root> is the path for CAAKnowHow.edu 
//			<root>\CAAKnowHow.edu\CNext\resources\graphic\ path of all documents use in this sample.
//  
// Restrictions:
// ------------
//
// Do not create and add rulesets from another rulebase into an already existing one.
// Use CATIRuleSet::Import
//  For importing one by one rules and checks, first create empty objects and use 
//  import services on these same objects.
// For importing sets of rules and checks, create an empty ruleset and use the 
//  import facility of this ruleset.
// 
//============================================================================


#include "CATIDocRoots.h"
#include "CATIRuleBaseFactory.h"

//System
#include "CATInit.h"
#include "CATSession.h"
#include "CATSessionServices.h"
#include "CATLib.h"
#include "CATGetEnvValue.h"

//ObjectModelerBase
#include "CATDocument.h"
#include "CATDocumentServices.h"
#include "CATIAlias.h"
#include "LifeCycleObject.h"
#include "CATIContainer.h"

//ObjectSpecModeler
#include "CATISpecObject.h"

//LiteralFeatures
#include "CATIParmPublisher.h"
#include "CATCkeGlobalFunctions.h"

//KnowHow
#include "CATIRuleBase.h"

//Local headers.
#include "CAAScanningRuleBase.h"

#ifndef _IRIX_SOURCE
    #include <iostream.h>
#else
    #include <CC/iostream.h>
#endif


int main(int argc,char **argv)
{
	CATUnicodeString DocumentPath0 = "";
	char *slash_tmp = NULL;
	DocumentPath0 = argv[1];
#ifdef _WINDOWS_SOURCE
	DocumentPath0 = DocumentPath0 + "\\";
#else
	DocumentPath0 = DocumentPath0 + "/";
#endif	
	if( 2!=argc )
	{
		cout <<"mkrun -c \"CAARuleBaseImport <root>/CAAKnowHow.edu/CNext/resources/graphic/\" where <root> is the path for CAAKnowHow.edu "<<endl;
		return 1;
	}
	
	char* pSessionIdent = "Session";
	CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionIdent, pSession);
    if ((FAILED(rc)) || (NULL == pSession))
        return 1;
	
	CATDocument * pDoc = NULL;

	/* First : 
	*      import in your design (Hole.CATPart) the RuleBase.
	*      You must create a RuleBase and import reference RuleBase.
	*      The failed results is saved in design document
	*/
	
	
	CATDocument * pDoc2 = NULL;
 	CATUnicodeString OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("Hole.CATPart");

	CATISpecObject_var spPart2 = OpenDocument(OpenDocumentPath, pDoc2);
	if (!spPart2)
		return 1;
	CATIContainer_var spContainer = spPart2->GetFeatContainer();

    if(NULL_var == spContainer  )
        return 0;

    // Get The Rulebase factory.
	CATIRuleBaseFactory_var spRuleBaseFactory = spContainer;
    if(NULL_var == spRuleBaseFactory )
        return 0;

    // Create the rulebase. The second argument is the Root of facts.
    // This Root of facts is the hierarchically highest objects that 
    // will be scanned by the solving mechanism in order to feeds the rules
    // and checks of the rulebase. Note that additional Roots of facts can be 
    // added to the Rulebase (CATIRuleBase::AddRootOfFacts).
	CATIRuleBase_var spRuleBase = spRuleBaseFactory->CreateBase("aRuleBase", spPart2);
    if(NULL_var == spRuleBase )
        return 0;

	// I aggregate the rulebase under the tree
	CATIParmPublisher_var spPubPart2 = spPart2;
	CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation,spPubPart2,CATCke::True);
	if (!!spRelationSet)
	{
		CATIParmPublisher_var spParmPublisher = spRelationSet;
		if (!!spParmPublisher)
		{
			spParmPublisher->Append(spRuleBase);
		}
	}
    // I can indicate a path to reference RuleBase
	CATUnicodeString location = DocumentPath0;
    location.Append("ReferenceRuleBaseEnrichResults.CATProduct");

	// Second argument : if during import there are same name of RuleSet or Check or Rule
	// we replace there with new one
	// I import all the checks and ruleset 
	spRuleBase->Import(location,TRUE);

	// I have my RuleBase into design document 
	// I can solve
	spRuleBase->Solve();

	// I show the results (see CAAScaningRuleBase file) 
	CATUnicodeString returnString (RulebaseToString(spRuleBase));
	cout << returnString.ConvertToChar() << endl;


	// I look for the new check to change its name
	CATICheck_var CheckToRename = spRuleBase->FindRuleBaseComponent("CATKWECheck.1",1);
	if (!!CheckToRename)
	{
		CheckToRename->SetGenericRuleBaseComponentName("MyCheck");

		// I can increase the priority of this check.
		// This check was solved in priority because the default priority is 1.
		CATIRule_var CheckToChgPriority = CheckToRename;
		if (!!CheckToChgPriority)
			CheckToChgPriority->SetPriority(10);
	}


	// Now, I import another check, only one

	CATDocument * pDoc3 = NULL;
 	OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("ReferenceRuleBaseEnrichResults2.CATProduct");

	// see CAAKnowHow.edu\CAACommonFunction.m\src\CAAScanningRuleBase.cpp for these methods
	CATIRuleBase_var spRuleBaseToImport = GetRulebase(OpenDocument(OpenDocumentPath, pDoc2));

	location = DocumentPath0;
    location.Append("ReferenceRuleBaseEnrichResults2.CATProduct");

	// I create a new ruleset to import new check into
	CATIRuleSet_var ruleset;
	spRuleBase->CreateRuleset(ruleset,"MyRuleSet");
	if (!!spRuleBaseToImport)
	{
		CATICheck_var CheckToImport = spRuleBaseToImport->FindRuleBaseComponent("CATKWECheck.1",1);
		if (!!CheckToImport)
			// I import only one check
			ruleset->ImportRuleBaseComponent(CheckToImport);
		// I solve with non optimize solve to take the new importing check
		spRuleBase->Solve(1);


		// the failed results is saved in design document

		// I show the results (see CAAScaningRuleBase file) 
		returnString  = RulebaseToString(spRuleBase);
		cout << returnString.ConvertToChar() << endl;
	}

	CloseDocument(pDoc2);  

	
    /* Second : 
	*      create a link between your design (Hole.CATPart) 
	*      and your reference RuleBase  (ReferenceRuleBaseEnrichResults.CATProduct).
	*      You must import with link from reference RuleBase.
	*      The failed results is saved in design document
	*
	*/

	CATIRuleBase_var ReferenceRulebase = GetRulebase(OpenDocument(location, pDoc));
	OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("Hole.CATPart");
	spPart2 = OpenDocument(OpenDocumentPath, pDoc2);
	
	// I create a link from reference RuleBase to design document(Hole.CATPart)
	// A LinkedRuleBase is created in design document

	// Second argument : if during import there are same name of RuleSet or Check or Rule
	// we replace there with new one
	ReferenceRulebase->ImportWithLink(spPart2,TRUE);

	// I search linked RuleBase in design document
	CATIRuleBase_var LinkedRuleBase = GetRulebase(spPart2);

	// I have my RuleBase into design document 
	// I can solve
	LinkedRuleBase->Solve();

	// the failed results is saved in design document

	// I show the results (see CAAScaningRuleBase file) 
	CATUnicodeString returnString2 (RulebaseToString(LinkedRuleBase));
	cout << returnString2.ConvertToChar() << endl;

	CloseDocument(pDoc2);  
	CloseDocument(pDoc);


	/* Third : 
	*      create a volatile RuleBase
	*      add a new root of facts, your design document 
	*      Solve
	*      The failed results isn't saved
	*/

	ReferenceRulebase = GetRulebase(OpenDocument(location, pDoc));

    //Create a volatile instance of the rule base.
    CATIRuleBase_var spVolatileRuleBase = ReferenceRulebase->VolatileCopy();
    
    if( NULL_var != spVolatileRuleBase )
    {        
     
	/*
        * Open a second document on which the volatile rule base will be applied.
        */
        CATDocument * pDoc2 = NULL;
        CATISpecObject_var spPart2 = OpenDocument(OpenDocumentPath, pDoc2);
        
        if( NULL != pDoc2)
        {
            if (NULL_var != spPart2)
            {
                //Add the new part to volatile rule base root of facts.
                spVolatileRuleBase->AddRootOfFacts( spPart2 );
                spVolatileRuleBase->Solve();
				// I show the results (see CAAScaningRuleBase file) 
				CATUnicodeString returnString3 (RulebaseToString(spVolatileRuleBase));
				cout << returnString3.ConvertToChar() << endl;
            }
        }
		CloseDocument(pDoc2);  

    }
	
	CloseDocument(pDoc);

	TraceMessage("CAA Sample - End of first sample, Start of second sample");

	CloseDocument(pDoc);

	if(pSession)
    {	  
        rc = ::Delete_Session(pSessionIdent);
        pSession = NULL;		
        
        if (FAILED(rc))
			return 1;
    }

	return 0;
}
