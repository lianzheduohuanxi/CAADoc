// COPYRIGHT DASSAULT SYSTEMES  2002

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which shows how to fill the results with an user function (GenerateResults).
//  For example, I want compute a check on Holes but interresting information is the father
//  of these Holes.
//
//  H:SimpleHole
//  GenerateResults(ThisCheck,H)
//
//  GenerateResults is a user function describe in module CAACommonFunction
//  
//============================================================================
//  Usage:
//  ------
//          ReferenceRuleBase.CATProduct and Hole.CATPart should exist.
//          Types can be retrieved from interactive view (knowledge expert wizard).
//          Each type belongs to a package (implemenation of CATIAddTypeLibrary)
//          that can be retrieved from Tools/Option/General/Parameters 
//          mkrun -c "CAAGenerateResults <root>\CAAKnowHow.edu\CNext\resources\graphic\ "
//          don't forget blank before the last ". 
//          where <root> is the path for CAAKnowHow.edu 
//			<root>\CAAKnowHow.edu\CNext\resources\graphic\ path of all documents use in this sample.
//          
//  
// Restrictions:
// ------------
//
// 
//============================================================================


#include "CATIDocRoots.h"
#include "CATListValCATIInstance.h"

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
#include "CATIParmDictionary.h"

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
	DocumentPath0 = argv[1];
#ifdef _WINDOWS_SOURCE
	DocumentPath0 = DocumentPath0 + "\\";
#else
	DocumentPath0 = DocumentPath0 + "/";
#endif	
	if( 2!=argc )
	{
		cout <<"mkrun -c \"CAAGenerateResults <root>/CAAKnowHow.edu/CNext/resources/graphic/\" where <root> is the path for CAAKnowHow.edu"<<endl;
		return 1;
	}

	char* pSessionIdent = "Session";
	CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionIdent, pSession);
    if ((FAILED(rc)) || (NULL == pSession))
        return 1;
	
	CATDocument * pDoc = NULL;
	CATUnicodeString OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("ReferenceRuleBase.CATProduct");
	CATIRuleBase_var spRulebase = GetRulebase(OpenDocument(OpenDocumentPath, pDoc));

	// To load the definition of the user function "GenerateResults"
	CATCkeGlobalFunctions::GetParmDictionary()->LoadLibrary("CAAGenerateResultsUserFunction");

    //Create a volatile instance of the rule base.
    if (!!spRulebase)
	{
		CATIRuleBase_var spVolatileRuleBase = spRulebase->VolatileCopy();
    
		if( NULL_var != spVolatileRuleBase )
		{        
			
		/*
        * Open a second document on which the volatile rule base will be applied.
			*/
			CATDocument * pDoc2 = NULL;
			OpenDocumentPath = DocumentPath0;
			OpenDocumentPath.Append("Hole.CATPart");
			CATISpecObject_var spPart2 = OpenDocument(OpenDocumentPath, pDoc2);
			
			if( NULL != pDoc2)
			{
				if (NULL_var != spPart2)
				{
					//Add the new part to volatile rule base root of facts.
					spVolatileRuleBase->AddRootOfFacts( spPart2 );
					// I solve this rulebase
					spVolatileRuleBase->Solve();
					
					// I verify that my results are correctled save.
					// We search for my check where I generate results
					CATICheck_var CheckSimpleHole = spVolatileRuleBase->FindRuleBaseComponent("CheckSimpleHole",1);
					if (!!CheckSimpleHole)
					{
						CATICheckReport_var ispCheckReport = CheckSimpleHole;
						if (!!ispCheckReport)
						{
							CATListValCATIReportObject_var iolListToBeFilled;
							ispCheckReport->ExtractReportObjects(CATICheckReport::Fail, iolListToBeFilled);
							int counter = 0;
							for (counter = 1; counter <= iolListToBeFilled.Size(); counter++)
							{
								CATIReportObject_var aReport = iolListToBeFilled[counter];
								if (!!aReport)
								{
									int taille = aReport->TupleSize();
									int counter;
									for (counter = 1; counter <= taille; counter++)
									{
										CATIInstance_var uneInstance = aReport->GetInstanceFromTuple(counter);
										if (NULL_var != uneInstance)
										{
											CATIValue* nameValue = uneInstance->GetValue("Name");
											if (nameValue)
											{
												CATUnicodeString instanceName;
												CATUnicodeString testString = "PartBody";

												HRESULT hr = nameValue->AsString(instanceName);
												
												if (SUCCEEDED(hr) && instanceName == testString)
													TraceMessage("We succeed to generate results.");
												else
													TraceMessage("Problem with generation of result.");
												
												nameValue->Release();
												nameValue = NULL;
											}
										}
									}
								}
							}
						}
					}
					// I show the results
					CATUnicodeString returnString (RulebaseToString(spVolatileRuleBase));
					cout << returnString.ConvertToChar() << endl;
					
				}
				//Now, the document containing the original rule base can be closed.
				CloseDocument(pDoc2);  
			}
		}
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
