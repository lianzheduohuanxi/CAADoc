// COPYRIGHT DASSAULT SYSTEMES  2002
/**
 * @quickReview TVQ 02.02.15
 */

#include "CAAScanningRuleBase.h"

#include "LifeCycleObject.h"
#include "CATIDocRoots.h"
#include "CATIProduct.h"
#include "CATDocumentServices.h"
#include "CATIAlias.h"
#include "CATISpecObject.h"
#include "CATIParmPublisher.h"
#include "CATIReportOptions.h"
#include "CATIInstance.h"
#include "CATLISTV_CATIGenericRuleBaseComponent.h"
#include "CATLISTV_CATIRuleBaseComponent.h"
#include "CATLISTV_CATIRuleSet.h"
#include "CATListOfCATUnicodeString.h"
#include "CATIAllowUserInfo.h"

//System
#include "CATInit.h"
#include "CATSession.h"
#include "CATLib.h"

#ifndef _IRIX_SOURCE
    #include <iostream.h>
#else
    #include <CC/iostream.h>
#endif

//------------------------------------------------------------------------------
CATUnicodeString ReplaceAllCarriageReturns (CATUnicodeString aString)
{
	CATUnicodeString transformedString (aString);
	while (transformedString.ReplaceSubString("\n", "\\n") != -1);
	return transformedString;
}

//------------------------------------------------------------------------------
CATUnicodeString GenericRuleBaseComponentToString (CATIGenericRuleBaseComponent_var ispGenericRuleBaseComponent)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispGenericRuleBaseComponent)
		return returnedString;
	
	CATIRuleSet_var fatherRuleSet = ispGenericRuleBaseComponent->GetFatherRuleSet();

	returnedString.Append(ispGenericRuleBaseComponent->GetGenericRuleBaseComponentName());
	returnedString.Append(" (parent = ");
	if (NULL_var == fatherRuleSet)
		returnedString.Append("<NULL>");
	else
		returnedString.Append(fatherRuleSet->GetGenericRuleBaseComponentName());
	returnedString.Append(")");

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString ReportObjectToString (CATIReportObject_var ispReportObject)
{
	CATUnicodeString returnedString ("{");

	if (NULL_var == ispReportObject)
		return returnedString;

	int taille = ispReportObject->TupleSize();
	int counter;
	for (counter = 1; counter <= taille; counter++)
	{
		CATIInstance_var uneInstance = ispReportObject->GetInstanceFromTuple(counter);
		if (NULL_var == uneInstance)
		{
		}
		else
		{
			CATIValue* nameValue = uneInstance->GetValue("Name");
			if (nameValue)
			{
				CATUnicodeString instanceName;
				HRESULT hr = nameValue->AsString(instanceName);
				
				if (SUCCEEDED(hr))
				{
					if (counter > 1)
						returnedString.Append(", ");
					returnedString.Append(instanceName);
				}
				nameValue->Release();
			}
			else
			{
				returnedString.Append("");
			}
		}
	}

	returnedString.Append("}");

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString CheckToString (CATICheck_var ispCheck, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispCheck)
		return returnedString;
	
	int counter;
	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString checkName = GenericRuleBaseComponentToString(ispCheck);
	boolean checkAutomaticCorrect = ispCheck->GetAutomaticCorrect();
	CATUnicodeString checkCorrectFunction = ispCheck->GetCorrectFunction();
	CATExpertReportEnum::CorrectingFunctionTypeEnum checkCorrectFunctionType = ispCheck->GetCorrectFunctionType();
	CATUnicodeString checkCorrectFunctionComment = ispCheck->GetCorrectFunctionComment();
	CATUnicodeString checkJustification = ispCheck->GetJustification();
	CATIAllowUserInfo_var ispCheckInfo = ispCheck;
	CATUnicodeString checkComment = ReplaceAllCarriageReturns(ispCheckInfo->GetComment());
	CATUnicodeString checkHelp = ispCheck->GetHelp();
	boolean checkStatus = ispCheck->GetStatus();
	CATUnicodeString variables = ispCheck->GetVariables();
	CATUnicodeString bodyRule = ispCheck->GetDescriptionByLanguage();
	CATIRuleBaseComponent::RuleBaseComponentLanguage aLang = ispCheck->GetLanguage();

	returnedString.Append(iOffsetString);
	returnedString.Append(checkName);
	returnedString.Append("\n");
	returnedString.Append(iOffsetString);
	returnedString.Append(variables);
	returnedString.Append("\n");
	returnedString.Append(iOffsetString);
	returnedString.Append(bodyRule);

	CATICheckReport_var ispCheckReport = ispCheck;
	CATListValCATIReportObject_var iolListToBeFilled;
	ispCheckReport->ExtractReportObjects(CATICheckReport::Pass, iolListToBeFilled);
	returnedString.Append(iOffsetString);
	returnedString.Append("  { OK  = [");
	for (counter = 1; counter <= iolListToBeFilled.Size(); counter++)
	{
		CATIReportObject_var aReport = iolListToBeFilled[counter];
		if (counter > 1)
			returnedString.Append(", ");
		returnedString.Append(ReportObjectToString(aReport));
	}
	iolListToBeFilled.RemoveAll();
	ispCheckReport->ExtractReportObjects(CATICheckReport::Fail, iolListToBeFilled);
	returnedString.Append("],\n");
	returnedString.Append(iOffsetString);
	returnedString.Append("    Bad = [");
	for (counter = 1; counter <= iolListToBeFilled.Size(); counter++)
	{
		CATIReportObject_var aReport = iolListToBeFilled[counter];
		if (counter > 1)
			returnedString.Append(", ");
		returnedString.Append(ReportObjectToString(aReport));
	}

	returnedString.Append("] }\n");

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString RuleToString (CATIRule_var ispRule, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispRule)
		return returnedString;

	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString ruleName = GenericRuleBaseComponentToString(ispRule);
	double rulePriority = ispRule->GetPriority();
	CATUnicodeString variables = ispRule->GetVariables();
	CATUnicodeString bodyRule = ispRule->GetDescriptionByLanguage();
	CATIRuleBaseComponent::RuleBaseComponentLanguage aLang = ispRule->GetLanguage();

	returnedString.Append(iOffsetString);
	returnedString.Append(ruleName);
	returnedString.Append("\n");

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString RulesetToString (CATIRuleSet_var ispRuleSet, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispRuleSet)
		return returnedString;

	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString ruleSetName = GenericRuleBaseComponentToString(ispRuleSet);
	CATListValCATIGenericRuleBaseComponent_var iolListToBeFilled;
	int counter;

	returnedString.Append(iOffsetString);
	returnedString.Append(ruleSetName);
	returnedString.Append("\n");

	ispRuleSet->GetDirectGenericRuleBaseComponents(iolListToBeFilled);
	for (counter = 1; counter <= iolListToBeFilled.Size(); counter++)
	{
		CATIGenericRuleBaseComponent_var spComponent = iolListToBeFilled[counter];
		CATIRuleSet_var ruleSetTer = spComponent;
		if (NULL_var == ruleSetTer)
		{
			CATICheck_var ispCheck = spComponent;
			if (NULL_var == ispCheck)
			{
				CATIRule_var ispRule = spComponent;
				if (NULL_var == spComponent)
				{
				}
				else
				{
					returnedString.Append(RuleToString(ispRule, iOffset+2));
				}
			}
			else
			{
				returnedString.Append(CheckToString(ispCheck, iOffset+2));
			}
		}
		else
		{
			returnedString.Append(RulesetToString(ruleSetTer, iOffset+2));
		}
	}

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString RulebaseToString (CATIRuleBase_var ispRuleBase, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispRuleBase)
		return returnedString;

	int counter;
	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString ruleBaseName = GenericRuleBaseComponentToString(ispRuleBase);
	CATExpertSolveModeEnum::SolveModeEnum a5 = ispRuleBase->GetSolveMode();
	CATListValCATBaseUnknown_var* listeRootsFacts = ispRuleBase->GetRootsOfFacts();

	CATIReportOptions_var spRuleBaseReport = ispRuleBase;
	CATExpertReportEnum::OutputFormatEnum a1 = spRuleBaseReport->GetOutputFormat();
	CATExpertReportEnum::DescriptionLengthEnum a2 = spRuleBaseReport->GetDescriptionLength();
	CATExpertReportEnum::ShowResultsEnum a3 = spRuleBaseReport->GetShowResults();
	CATExpertReportEnum::VisualizationTypeEnum a4 = spRuleBaseReport->GetVisualizationType();
	CATListOfCATUnicodeString* path = spRuleBaseReport->GetReportPath();

	CATISpecObject_var ispRuleBaseSpec = ispRuleBase;
	if (!!ispRuleBaseSpec)
		boolean fingerprint = ispRuleBaseSpec->IsUpToDate();

	returnedString.Append(iOffsetString);
	returnedString.Append(ruleBaseName);
	if (listeRootsFacts)
	{
		returnedString.Append(" { Roots = ");
		for (counter = 1; counter <= listeRootsFacts->Size(); counter++)
		{
			CATIAlias_var spRootAlias = (*listeRootsFacts)[counter];
			if (counter > 1)
				returnedString.Append(", ");
			if (NULL_var == spRootAlias)
				returnedString.Append("<No alias>");
			else
				returnedString.Append(spRootAlias->GetAlias());
		}
		returnedString.Append(" }");
	}
	returnedString.Append("\n");
	returnedString.Append(RulesetToString(ispRuleBase, iOffset+2));

	if (path)
		delete path;
	if (listeRootsFacts)
		delete listeRootsFacts;

	return returnedString;
}


void TraceMessage(CATUnicodeString msg)
{
	int l = msg.GetLengthInChar();
	CATUnicodeString dash (CATUnicodeString("-"), l+4);
	cout << dash.CastToCharPtr() << endl << "- " << msg.CastToCharPtr() << " -" << endl << dash.CastToCharPtr() << endl;
}

/**
* Open a document from the Inputdata directory.
*/
CATISpecObject_var OpenDocument (CATUnicodeString nomDocument, CATDocument*& iopDoc)
{
	CATDocument *pDocument = NULL;
	CATDocumentServices::OpenDocument(nomDocument, pDocument, TRUE);
    if(!pDocument)
        return NULL_var;

	CATIProduct_var spRootProduct = NULL_var;
    iopDoc = pDocument;
    if (iopDoc)
	{
        iopDoc->AddRef();

		// Begin navigation through the document => start with the RootProduct.
		CATIDocRoots* piDocRootsOnDoc = NULL;
		iopDoc->QueryInterface(IID_CATIDocRoots,
			(void**) &piDocRootsOnDoc);	
		if (piDocRootsOnDoc)
		{
			// get the root product which is the first element of root elements
			CATListValCATBaseUnknown_var* pRootProducts = piDocRootsOnDoc->GiveDocRoots();
		
			if (pRootProducts && pRootProducts->Size())
			{  
				spRootProduct = (*pRootProducts)[1];
				delete pRootProducts;
				pRootProducts = NULL;
			}
		
			piDocRootsOnDoc->Release();
			piDocRootsOnDoc = NULL;
		}
	}
    
	return spRootProduct;
}


/**
* Retrieve the rule base from the part. In this case, there only exist one rulebase.
*/
CATIRuleBase_var GetRulebase (CATISpecObject_var ispPart)
{
	CATIParmPublisher_var spPublisher = ispPart;
	CATIRuleBase_var spRulebase = NULL_var;
	if (NULL_var != spPublisher)
	{
		CATListValCATISpecObject_var spChildrenList;
		spPublisher->GetAllChildren(CATIRuleBase::ClassName(), spChildrenList);

        //There should only be a single rulebase.
		if (spChildrenList.Size() >= 1)
			spRulebase = spChildrenList[1]; 
	}
	return spRulebase;
}



void CloseDocument(CATDocument *& pDoc)
{
	LifeCycleObject_var spLifeDoc(pDoc);
	if (NULL_var == spLifeDoc)
		TraceMessage("Problem in the implemenation of LifeCycleObject.");
	else
		spLifeDoc->remove();
}
