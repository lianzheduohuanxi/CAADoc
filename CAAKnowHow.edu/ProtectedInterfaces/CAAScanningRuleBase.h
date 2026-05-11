#ifndef CAAScanningRuleBase_H
#define CAAScanningRuleBase_H
#ifndef pDoc
#define CAAParcoursRuleBase_H
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
#include "CAACommonFunction.h"

CATUnicodeString ExportedByCAACommonFunction ReplaceAllCarriageReturns (CATUnicodeString aString);
CATUnicodeString ExportedByCAACommonFunction GenericRuleBaseComponentToString (CATIGenericRuleBaseComponent_var ispGenericRuleBaseComponent);
CATUnicodeString ExportedByCAACommonFunction ReportObjectToString (CATIReportObject_var ispReportObject);
CATUnicodeString ExportedByCAACommonFunction CheckToString (CATICheck_var ispCheck, int iOffset);
CATUnicodeString ExportedByCAACommonFunction RuleToString (CATIRule_var ispRule, int iOffset);
CATUnicodeString ExportedByCAACommonFunction RulesetToString (CATIRuleSet_var ispRuleSet, int iOffset);
CATUnicodeString ExportedByCAACommonFunction RulebaseToString (CATIRuleBase_var ispRuleBase, int iOffset = 0);
void ExportedByCAACommonFunction CloseDocument(CATDocument *& pDoc);
CATIRuleBase_var ExportedByCAACommonFunction GetRulebase (CATISpecObject_var ispPart);
CATISpecObject_var ExportedByCAACommonFunction OpenDocument (CATUnicodeString nomDocument, CATDocument*& iopDoc);
void ExportedByCAACommonFunction TraceMessage(CATUnicodeString msg);


#endif
#endif
