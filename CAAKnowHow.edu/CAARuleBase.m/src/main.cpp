// COPYRIGHT DASSAULT SYSTEMES  2002

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which shows first:
//      - how to retrieve, solve and display an already existing rulebase (in a part),
//  and second,
//       - how to create, solve and display a rulebase (in a part),
//
// A knowledge expert rule is of the form:
//      H1 : Hole",                                                   
//        "if (H1.Diameter > 15mm) { H1.Diameter = H1.Diameter / 2 }"
//  It can be read as:
//      "For each Hole that can be found under a "RootOfFact" if its diameter is bigger than
//      " 15mm then divide its diameter by two".
//
//  The "RootOfFacts" is an object such as a Part or a Product (or any object implementing CATIParmPublisher)
//  that the solving 
//  mechanism will scan in order to retrieve (CATIParmPublisher::VisitChildren) 
//  all the objects of type "Hole" and that implements CATIInstance.
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
//          HolesWithChecksRules.CATPart and Hole.CATPart should exist.
//          Types can be retrieved from interactive view (knowledge expert wizard).
//          Each type belongs to a package (implemenation of CATIAddTypeLibrary)
//          that can be retrieved from Tools/Option/General/Parameters 
//          
//          To run this sample, you can use the command:
//          mkrun -c "CAARuleBase <root>\CAAKnowHow.edu\CNext\resources\graphic\ "
//          don't forget blank before the last ". 
//          where <root> is the path for CAAKnowHow.edu 
//			<root>\CAAKnowHow.edu\CNext\resources\graphic\ path of all documents use in this sample.
//  
// Restrictions:
// ------------
//
// Cannot apply to Literals types (not yet).
// Do not create and add rulesets from another rulebase into an already existing one.
// Use CATIRuleSet::Import
//  For importing one by one rules and checks, first create empty objects and use 
//  import services on these same objects.
// For importing sets of rules and checks, create an empty ruleset and use the 
//  import facility of this ruleset.
// 
//============================================================================

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
#include "CAACreationRuleBase.h"

#ifndef _IRIX_SOURCE
    #include <iostream.h>
#else
    #include <CC/iostream.h>
#endif



int main(int argc,char **argv)
{

	CATUnicodeString DocumentPath0 = "";
	DocumentPath0 = argv[1];
#ifdef _WINDOWS_SOURCE
	DocumentPath0 = DocumentPath0 + "\\";
#else
	DocumentPath0 = DocumentPath0 + "/";
#endif		
	if( 2!=argc )
	{
		cout <<"mkrun -c \"CAARuleBase <root>/CAAKnowHow.edu/CNext/resources/graphic/\" where <root> is the path for CAAKnowHow.edu"<<endl;
		return 1;
	}

	char* pSessionIdent = "Session";
	CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionIdent, pSession);
    if ((FAILED(rc)) || (NULL == pSession))
        return 1;
	
    /*
    * First example. Load a part document.
    * Retrieve and solve the rulebase.
    * Display the rulebase.
    */
	CATDocument * pDoc = NULL;
	CATUnicodeString OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("HolesWithChecksRules.CATPart");

	CATIRuleBase_var spRulebase = GetRulebase(OpenDocument(OpenDocumentPath, pDoc));

	if (NULL_var != spRulebase)
	{
		spRulebase->Solve();
		
		CATUnicodeString returnString (RulebaseToString(spRulebase));
		cout << returnString.ConvertToChar() << endl;
	}
	CloseDocument(pDoc);


    /*
    * Second example. Load a part document.
    * Create and solve a rulebase.
    * Display the rulebase.
    */
	OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("Hole.CATPart");

	CATISpecObject_var spPart = OpenDocument(OpenDocumentPath, pDoc);

	if (NULL_var != spPart)
	{
		CATIRuleBase_var spRuleBase = CreationRuleBase(spPart);

		if (NULL_var != spRuleBase)
		{
			spRuleBase->Solve();
			CATUnicodeString returnString ( RulebaseToString(spRuleBase) );
			cout << returnString.ConvertToChar() << endl;
		}
	}
	CloseDocument(pDoc);

	if(pSession)
    {	  
        rc = ::Delete_Session(pSessionIdent);
        pSession = NULL;		
        
        if (FAILED(rc))
			return 1;
    }

	TraceMessage("CAA Sample - End of first sample, Start of second sample");

	return 0;
}
