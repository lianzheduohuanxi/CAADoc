#ifndef CAAScanningRuleBase2_H
#define CAAScanningRuleBase2_H
//#ifndef pDoc
//#define CAAParcoursRuleBase_H
// COPYRIGHT DASSAULT SYSTEMES 2002

//KnowHow
#include "CATICheck.h"
#include "CATICheckReport.h"
#include "CATIReportObject.h"
#include "CATIRuleBase.h"
#include "CATIRuleSet.h"
#include "CATIRule.h"
#include "CATICheck.h"
#include "CATIRuleBaseComponent.h"
#include "CATIGenericRuleBaseComponent.h"

CATUnicodeString ReplaceAllCarriageReturns2 (CATUnicodeString aString);
CATUnicodeString GenericRuleBaseComponentToString2 (CATIGenericRuleBaseComponent_var ispGenericRuleBaseComponent);
CATUnicodeString ReportObjectToString2 (CATIReportObject_var ispReportObject);
CATUnicodeString CheckToString2 (CATICheck_var ispCheck, int iOffset);
CATUnicodeString RuleToString2 (CATIRule_var ispRule, int iOffset);
CATUnicodeString RulesetToString2 (CATIRuleSet_var ispRuleSet, int iOffset);
CATUnicodeString RulebaseToString2 (CATIRuleBase_var ispRuleBase, int iOffset = 0);

#endif
