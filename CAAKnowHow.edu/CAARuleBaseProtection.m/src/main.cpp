// COPYRIGHT DASSAULT SYSTEMES  2002

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which shows first:
//      - how to protect your rulebase design with use only,
//  and second,
//       - how to protect your checks with user function which simulate a License,
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
//          mkrun -c "CAARuleBaseProtection <root>\CAAKnowHow.edu\CNext\resources\graphic\ "
//			don't forget blank before the last ". 
//          where <root> is the path for CAAKnowHow.edu 
//			<root>\CAAKnowHow.edu\CNext\resources\graphic\ path of all documents use in this sample.
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


#include "CATIDocRoots.h"

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
	char *slash_tmp = NULL;
	DocumentPath0 = argv[1];
#ifdef _WINDOWS_SOURCE
	DocumentPath0 = DocumentPath0 + "\\";
#else
	DocumentPath0 = DocumentPath0 + "/";
#endif	
	if( 2!=argc )
	{
		cout <<"mkrun -c \"CAARuleBaseProtection <root>/CAAKnowHow.edu/CNext/resources/graphic/\" where <root> is the path for CAAKnowHow.edu"<<endl;
		return 1;
	}
	char* pSessionIdent = "Session";
	CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionIdent, pSession);
    if ((FAILED(rc)) || (NULL == pSession))
        return 1;
	
    /*
    * First Protection :  forbide reading checks or rules
	* Load a reference rulebase.
    * Retrieve rulesets.
	* Protect the rulesets with use only (not editable)
	* Save this rulebase.
    * Try to display the rulebase.
    */
	CATDocument * pDoc = NULL;
	CATUnicodeString OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("ReferenceRuleBase.CATProduct");

	cout << "Document path : " << OpenDocumentPath.ConvertToChar() << endl;
	
	CATIRuleBase_var spRulebase = GetRulebase(OpenDocument(OpenDocumentPath, pDoc));

	if (NULL_var != spRulebase)
	{

		CATUnicodeString returnString (RulebaseToString(spRulebase));
		cout << returnString.ConvertToChar() << endl;

		CATListValCATIRuleSet_var listofruleset;
		spRulebase->FindAnyRuleSet(listofruleset);
		int size = listofruleset.Size();
		for (int i =1;i<=size;i++)
		{
			CATIRuleSet_var spRuleSet = listofruleset[i];
			if (NULL_var != spRuleSet)
				spRuleSet->SetUseOnly();
		}
		
		CATUnicodeString returnString2 (RulebaseToString(spRulebase));
		cout << returnString2.ConvertToChar() << endl;
	

    /*
    * Second Protection : forbide use of check.
    * Make a volatile copy of rulebase.
	* Solve this rulebase.
    */

	/* The first check is : 
	* H:Hole
	* LicensingTest() AND H\Diameter > 15 mm
	*
	* This check return always false if the licensing test is not ok
	* and on interactive session a panel shows the problem 
	* (see TestLicensing function in CAALicensingUserFunction).
	*/


    //Create a volatile instance of the rule base.
    CATIRuleBase_var spVolatileRuleBase = spRulebase->VolatileCopy();
    
    if( NULL_var != spVolatileRuleBase )
    {        
     
	/*
        * Open a second document on which the volatile rule base will be applied.
        */
        CATDocument * pDoc2 = NULL;
		OpenDocumentPath = DocumentPath0;
		OpenDocumentPath.Append("Hole.CATPart");

        CATISpecObject_var spPart2 = OpenDocument("Hole.CATPart", pDoc2);
        
        if( NULL != pDoc2)
        {
            if (NULL_var != spPart2)
            {
                //Add the new part to volatile rule base root of facts.
                spVolatileRuleBase->AddRootOfFacts( spPart2 );
                spVolatileRuleBase->Solve();
            }
            //Now, the document containing the original rule base can be closed.
            CloseDocument(pDoc2);  
        }
    }
	  }
	else
	  {
		cout << " Unable to retreive Rule Base " << endl;
		return 2;
	  }
	
	CloseDocument(pDoc);

	TraceMessage("CAA Sample - End of first sample, Start of second sample");

	if(pSession)
    {	  
        rc = ::Delete_Session(pSessionIdent);
        pSession = NULL;		
        
        if (FAILED(rc))
			return 1;
    }

	return 0;
}
