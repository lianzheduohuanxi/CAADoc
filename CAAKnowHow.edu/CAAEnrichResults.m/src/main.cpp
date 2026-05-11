// COPYRIGHT DASSAULT SYSTEMES  2002

//============================================================================
//  Abstract:
//  ---------
//
//  Batch program which shows how to enrich the results.
//  For example, I solve RuleBase which check the hole diameter. But for a specific hole
//  which is failed with this check, the user decided that isn't important and he has a justification
//
//  H:Hole
//  H\Diameter > 15mm
//
//  
//  
//============================================================================
//  Usage:
//  ------
//          ReferenceRuleBaseEnrichResults.CATProduct and Hole.CATPart should exist.
//          Types can be retrieved from interactive view (knowledge expert wizard).
//          Each type belongs to a package (implemenation of CATIAddTypeLibrary)
//          that can be retrieved from Tools/Option/General/Parameters 
//          To run this sample, you can use the command:
//          mkrun -c "CAAEnrichResults $WSROOT\CAAKnowHow.edu\CNext\resources\graphic\ "
//          don't forget blank before the last ". 
//          where <root> is the path for CAAKnowHow.edu 
//			<root>\CAAKnowHow.edu\CNext\resources\graphic\ path of all documents use in this sample.
//                            
//  
// Restrictions:
// ------------
//          You can enrich result (add parameter) on failed report object and not on
//          volatile RuleBase
// 
//============================================================================


#include "CATIDocRoots.h"
#include "CATListValCATIInstance.h"
#include "CATICkeParmFactory.h"
#include "CATICkeParm.h"

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
#include "CAAScanningRuleBase2.h"

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
	int i = 1;
	if( 2!=argc )
	{
		cout <<"mkrun -c \"CAAEnrichResults <root>/CAAKnowHow.edu/CNext/resources/graphic/\" where <root> is the path for CAAKnowHow.edu"<<endl;
		return 1;
	}

	char* pSessionIdent = "Session";
	CATSession *pSession = NULL;
    HRESULT rc = ::Create_Session(pSessionIdent, pSession);
    if ((FAILED(rc)) || (NULL == pSession))
        return 1;
    
	
	CATDocument * pDoc = NULL;
	CATUnicodeString OpenDocumentPath = DocumentPath0;
	OpenDocumentPath.Append("ReferenceRuleBaseEnrichResults.CATProduct");
	CATIRuleBase_var spRulebase = GetRulebase(OpenDocument(OpenDocumentPath, pDoc));


    
    if( NULL_var != spRulebase && pDoc)
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
                //Add the new part to rulebase  root of facts.
                spRulebase->AddRootOfFacts( spPart2 );
				// I solve this rulebase
                spRulebase->Solve();
				TraceMessage("CAA Sample - I Solve my RuleBase");
															
				// Find check to add a justification (parameter) on a result (Hole.6)
				CATICheck_var CheckSimpleHole = spRulebase->FindRuleBaseComponent("CATKWECheck.1",1);
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
										CATISpecObject_var spec = uneInstance;
										CATUnicodeString testString = "Hole.6";
										if (!!spec)
										{
											if (spec->GetName() == testString)
											{
												CATICkeParm_var param = NULL_var;

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
														param = piFact->CreateString ("Justification","This hole is breaking check because ...");
													
														// I add parameter on Report Object
														CATIParmPublisher_var publishreport = aReport;
														if (!!publishreport)
														{
															publishreport->Append (param);
															TraceMessage("CAA Sample - I add parameter on Report Object");
															cout<<" rapport "<<endl;
															cout<<ReportObjectToString2(aReport).ConvertToChar()<<endl;
														}
														piFact->Release();
														piFact = NULL;
													}
													container->Release();
													container = NULL;

												}
											}
										}
									}
								}
							}
						}
					}
				}
				// I show the results (see ReportObjectToString method in CAAScaningRuleBase file) 
				CATUnicodeString returnString (RulebaseToString2(spRulebase));
				cout << returnString.ConvertToChar() << endl;

            }
            //Now, the document containing the original rule base can be closed.
            CloseDocument(pDoc2);  
        }
		else
			TraceMessage("CAA Sample - Document Hole.CATPart not find");

    }
	else
		TraceMessage("CAA Sample - Document ReferenceRuleBaseEnrichResults.CATProduct not find");

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
