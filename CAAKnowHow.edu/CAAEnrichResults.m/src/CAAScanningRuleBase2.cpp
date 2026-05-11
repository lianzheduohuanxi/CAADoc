// COPYRIGHT DASSAULT SYSTEMES  2002
/**
 * @quickReview TVQ 02.02.15
 */

#include "CAAScanningRuleBase.h"

#include "CATICkeParm.h"
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


//------------------------------------------------------------------------------
CATUnicodeString ReplaceAllCarriageReturns2 (CATUnicodeString aString)
{
	CATUnicodeString transformedString (aString);
	while (transformedString.ReplaceSubString("\n", "\\n") != -1);
	return transformedString;
}

//------------------------------------------------------------------------------
CATUnicodeString GenericRuleBaseComponentToString2 (CATIGenericRuleBaseComponent_var ispGenericRuleBaseComponent)
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
#include "iostream.h"
//------------------------------------------------------------------------------
CATUnicodeString ReportObjectToString2 (CATIReportObject_var ispReportObject)
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
				nameValue = NULL;
			}
			else
			{
				returnedString.Append("");
			}
			
			// I show the parameter justification if this parameter exists on ReportObject
			CATIParmPublisher_var publisherreportobject = ispReportObject;
			if (!!publisherreportobject)
			{
				CATListValCATISpecObject_var lst;
				publisherreportobject->GetDirectChildren(CATICkeParm::ClassName(),lst);
				int size = lst.Size();
				int i = 1;
				CATICkeParm_var parm = NULL_var;
				CATUnicodeString name = "defaultname";
				CATUnicodeString testString = "Justification";
				while(i<= size && name != testString)
				{
					parm = lst[i];
					if (!!parm)
						name = parm->InternalRole();
					i++;
				}
				testString = "Justification";
				if (name == testString && !!parm)
				{
					CATICkeInst_var inst = parm->Value();
					if (!!inst)
					{
						if (counter > 1)
							returnedString.Append(", ");
						returnedString.Append(inst->AsString());
					}
				}
			}
		}
	}

	returnedString.Append("}");

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString CheckToString2 (CATICheck_var ispCheck, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispCheck)
		return returnedString;
	
	int counter;
	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString checkName = GenericRuleBaseComponentToString2(ispCheck);
	boolean checkAutomaticCorrect = ispCheck->GetAutomaticCorrect();
	CATUnicodeString checkCorrectFunction = ispCheck->GetCorrectFunction();
	CATExpertReportEnum::CorrectingFunctionTypeEnum checkCorrectFunctionType = ispCheck->GetCorrectFunctionType();
	CATUnicodeString checkCorrectFunctionComment = ispCheck->GetCorrectFunctionComment();
	CATUnicodeString checkJustification = ispCheck->GetJustification();
	CATIAllowUserInfo_var ispCheckInfo = ispCheck;
	CATUnicodeString checkComment = ReplaceAllCarriageReturns2(ispCheckInfo->GetComment());
	CATUnicodeString checkHelp = ispCheck->GetHelp();
	boolean checkStatus = ispCheck->GetStatus();	
	returnedString.Append(iOffsetString);
	returnedString.Append(checkName);
	returnedString.Append("\n");

	CATUnicodeString Variables = ispCheck->GetVariables();
	CATUnicodeString Body =	ispCheck->GetDescription();
	returnedString.Append(iOffsetString);
	returnedString.Append(Variables);
	returnedString.Append("\n");
	returnedString.Append(iOffsetString);
	returnedString.Append(Body);
	returnedString.Append("\n");




	CATICheckReport_var ispCheckReport = ispCheck;
	if (NULL_var != ispCheckReport)
	{
		CATListValCATIReportObject_var iolListToBeFilled;
		ispCheckReport->ExtractReportObjects(CATICheckReport::Pass, iolListToBeFilled);
		returnedString.Append(iOffsetString);
		returnedString.Append("  { OK  = [");
		for (counter = 1; counter <= iolListToBeFilled.Size(); counter++)
		{
			CATIReportObject_var aReport = iolListToBeFilled[counter];
			if (counter > 1)
				returnedString.Append(", ");
			returnedString.Append(ReportObjectToString2(aReport));
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
			returnedString.Append(ReportObjectToString2(aReport));
		}
	}

	returnedString.Append("] }\n");

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString RuleToString2 (CATIRule_var ispRule, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispRule)
		return returnedString;

	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString ruleName = GenericRuleBaseComponentToString2(ispRule);
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
CATUnicodeString RulesetToString2 (CATIRuleSet_var ispRuleSet, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispRuleSet)
		return returnedString;

	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString ruleSetName = GenericRuleBaseComponentToString2(ispRuleSet);
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
					returnedString.Append(RuleToString2(ispRule, iOffset+2));
				}
			}
			else
			{
				returnedString.Append(CheckToString2(ispCheck, iOffset+2));
			}
		}
		else
		{
			returnedString.Append(RulesetToString2(ruleSetTer, iOffset+2));
		}
	}

	return returnedString;
}

//------------------------------------------------------------------------------
CATUnicodeString RulebaseToString2 (CATIRuleBase_var ispRuleBase, int iOffset)
{
	CATUnicodeString returnedString;

	if (NULL_var == ispRuleBase)
		return returnedString;

	int counter;
	CATUnicodeString iOffsetString(CATUnicodeString(" "), iOffset);
	CATUnicodeString ruleBaseName = GenericRuleBaseComponentToString2(ispRuleBase);
	CATExpertSolveModeEnum::SolveModeEnum a5 = ispRuleBase->GetSolveMode();
	CATListValCATBaseUnknown_var* listeRootsFacts = ispRuleBase->GetRootsOfFacts();

	CATIReportOptions_var spRuleBaseReport = ispRuleBase;
	CATExpertReportEnum::OutputFormatEnum a1 = spRuleBaseReport->GetOutputFormat();
	CATExpertReportEnum::DescriptionLengthEnum a2 = spRuleBaseReport->GetDescriptionLength();
	CATExpertReportEnum::ShowResultsEnum a3 = spRuleBaseReport->GetShowResults();
	CATExpertReportEnum::VisualizationTypeEnum a4 = spRuleBaseReport->GetVisualizationType();
	CATListOfCATUnicodeString* path = spRuleBaseReport->GetReportPath();

	CATISpecObject_var ispRuleBaseSpec = ispRuleBase;
	if (NULL_var != ispRuleBaseSpec)
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

		delete listeRootsFacts;
		listeRootsFacts = NULL;
	}
	returnedString.Append("\n");
	returnedString.Append(RulesetToString2(ispRuleBase, iOffset+2));

	if (path)
	{
		delete path;
		path = NULL;
	}

	return returnedString;
}
