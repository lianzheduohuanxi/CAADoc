// COPYRIGHT DASSAULT SYSTEMES  2002

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which shows how parametrize RuleBase or other KnowledgeExpert Component (Check, Rule,RuleSet).
//  I add a condition into checks to test the value of a parameter under RuleBase
//
//  The first check test parameter with using a user function made in CAA
//  First Check :CheckParameterWithUserFunction
//  H:Hole
//  H\Diameter > 10mm AND FindAttributeReal(ThisCheck.Owner.Owner,"FirstParameter") > 10.0
//    
//
//  The second check test parameter with using delivred method GetAttributeReal
//  Second Check : CheckParameterWithGetAttributeMethode
//  H:Hole
//  H\Diameter > 5mm AND ThisCheck.Owner.Owner->GetAttributeReal("SecondParameter") > 15.0
//
//  Owner is an attribute which contains the father. In this case, ThisCheck.Owner is the ruleset
//  and ThisCheck.Owner.Owner is the rulebase.
//  
//============================================================================
//  Usage:
//  ------
//          ReferenceRuleBaseWithParameter.CATProduct and Hole.CATPart should exist.
//          Types can be retrieved from interactive view (knowledge expert wizard).
//          Each type belongs to a package (implemenation of CATIAddTypeLibrary)
//          that can be retrieved from Tools/Option/General/Parameters 
//          
//          To run this sample, you can use the command:
//          mkrun -c "CAAParametrizeRuleBase <root>\CAAKnowHow.edu\CNext\resources\graphic\ "
//          don't forget blank before the last ". 
//          where <root> is the path for CAAKnowHow.edu 
//			<root>\CAAKnowHow.edu\CNext\resources\graphic\ path of all documents use in this sample.
//  
// Restrictions:
// ------------
//
// 
//============================================================================


#include "CATIDocRoots.h"
#include "CATListValCATIInstance.h"
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"

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
	DocumentPath0 = argv[1] ;
#ifdef _WINDOWS_SOURCE
	DocumentPath0 = DocumentPath0 + "\\";
#else
	DocumentPath0 = DocumentPath0 + "/";
#endif		
	if( 2!=argc )
	{
		cout <<"mkrun -c \"CAAParametrizeRuleBase <root>/CAAKnowHow.edu/CNext/resources/graphic/\" where <root> is the path for CAAKnowHow.edu"<<endl;
		return 1;
	}

	char* pSessionIdent = "Session";
	CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionIdent, pSession);
    if ((FAILED(rc)) || (NULL == pSession))
        return 1;

	TraceMessage("CAA Sample - Load Checks");

	CATDocument * pDoc = NULL;
	CATUnicodeString OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("ReferenceRuleBaseWithParameter.CATProduct");

	CATIRuleBase_var spRulebase = GetRulebase(OpenDocument(OpenDocumentPath, pDoc));

	CATICkeParm_var param1 = NULL_var;
	CATICkeParm_var param2 = NULL_var;

	// I add two parameter on RuleBase
	if (!!spRulebase && pDoc)
	{
		CATInit *pInitOnDoc = NULL ;
		rc = pDoc->QueryInterface(IID_CATInit,(void **) &pInitOnDoc);
		if ( FAILED(rc) )
		{
			cout << "Error in retrieving the CATInit interface"<< endl;
			return 1 ;
		}
		CATIContainer *container = NULL ;
		container = (CATIContainer*)pInitOnDoc->GetRootContainer("CATIContainer");

		pInitOnDoc->Release();
		pInitOnDoc = NULL ;

		if (!!container)
		{
			CATICkeParmFactory* piFact = NULL;
			container->QueryInterface(IID_CATICkeParmFactory, (void**) &piFact);		
			if (piFact)
			{
				TraceMessage("CAA Sample - create parameter FirstParameter");

				param1 = piFact->CreateReal ("FirstParameter",5.0);
				
				CATIParmPublisher_var RuleBasePublisher = spRulebase;
				if (!!RuleBasePublisher)
				{
					RuleBasePublisher->Append (param1);
					
					TraceMessage("CAA Sample - create parameter SecondParameter");
					param2 = piFact->CreateReal ("SecondParameter",1.0);
					RuleBasePublisher->Append (param2);
				}
				piFact->Release();
				piFact = NULL;
			}
			container->Release();
			container = NULL;
		}
	}
	/*
	* Open a second document on which the volatile rule base will be applied.
	*/
	CATDocument * pDoc2 = NULL;
	OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("Hole.CATPart");
	CATISpecObject_var spPart2 = OpenDocument(OpenDocumentPath, pDoc2);
 	TraceMessage("CAA Sample - Load Hole.CATPart");
       
	if( NULL != pDoc2)
	{
		if (NULL_var != spPart2)
		{
			//Add the new part to volatile rule base root of facts.
			spRulebase->AddRootOfFacts( spPart2 );
			// I solve this rulebase
			TraceMessage("CAA Sample - Solve RuleBase");
			spRulebase->Solve();
				
			// I show the results
			CATUnicodeString returnString (RulebaseToString(spRulebase));
			cout << returnString.ConvertToChar() << endl;
		
			// There are 100% of failed element in the checks (CheckParameterWithGetAttributeMethode )
			// because the value of parameter named SecondParameter is under 15.0 and the value of parameter
			// named FirstParameter is under 10.0
			// I modify the value of parameters
			if( NULL_var != param1 )
			{
				// Modify "realParam"
				param1->Valuate (30.0);			
			}
			if( NULL_var != param2 )
			{
				// Modify "realParam"
				param2->Valuate (30.0);			
			}
			// I solve this rulebase in mode no optimize to take the value modification
			// on parameter (argument 1)
			spRulebase->Solve(1);
			// I show the results
			CATUnicodeString returnString2 (RulebaseToString(spRulebase));
			cout << returnString2.ConvertToChar() << endl;

		}
		//Now, the document containing the original rule base can be closed.
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
