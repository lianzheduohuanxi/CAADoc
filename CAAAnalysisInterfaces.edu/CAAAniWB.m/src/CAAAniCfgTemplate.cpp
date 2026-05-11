// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================================
//
// CAAAniCfgTemplate.cpp
// Provide implementation to interface CATISamWorkbenchTemplate
//
// Provide the list of transtion authorized for a Workbench.
// One methode to implement: GetTemplates
//
// Output Argument:
// --------------
// CATListOfCATString& oList : The authorized transition.
//===================================================================================
#include "CAAAniCfgTemplate.h"
	
// System prereq
#include "CATString.h"
#include "CATError.h"

CATImplementClass(CAAAniCfgTemplate,DataExtension,CATBaseUnknown,CAAAniCfg_TempList);
 
//-----------------------------------------------------------------------------
// CAAAniCfgTemplate : constructor
//-----------------------------------------------------------------------------
CAAAniCfgTemplate::CAAAniCfgTemplate():CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAAniCfgTemplate : destructor
//-----------------------------------------------------------------------------
CAAAniCfgTemplate::~CAAAniCfgTemplate()
{
}
 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATISamWorkbenchTemplate.h"
TIE_CATISamWorkbenchTemplate(CAAAniCfgTemplate);
//-----------------------------------------------------------------------------
// Implements CATIAlias::SetAlias
//-----------------------------------------------------------------------------
HRESULT CAAAniCfgTemplate::GetTemplates(CATListOfCATString& oList)
{
  oList.Append("AeroDynamic");	
//  oList.Append("CATGPSStressAnalysis_template");	
//  oList.Append("CATGPSModalAnalysis_template");	
  return S_OK;
}


