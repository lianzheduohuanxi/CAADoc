//===================================================================
// COPYRIGHT Dassault Systemes 2005
//===================================================================
//
//===================================================================
#include "CAAPmiUserPrismaticOperationToolActivity.h"

 
// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIMfgToolActivity.h"
TIE_CATIMfgToolActivity( CAAPmiUserPrismaticOperationToolActivity);

//CATImplementClass( CAAPmiUserPrismaticOperationToolActivity,CodeExtension,CATBaseUnknown,UserDrilling );
CATBeginImplementClass (CAAPmiUserPrismaticOperationToolActivity,CodeExtension,CATBaseUnknown,UserDrilling );
CATAddClassExtension   (UserPocketing);
CATAddClassExtension   (UserProfileContouring);
CATAddClassExtension   (UserCircularMilling);
CATEndImplementClass   (CAAPmiUserPrismaticOperationToolActivity);
 
//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationToolActivity : constructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationToolActivity::CAAPmiUserPrismaticOperationToolActivity():
    CATBaseUnknown()
{
}

//-----------------------------------------------------------------------------
// CAAPmiUserPrismaticOperationToolActivity : destructor
//-----------------------------------------------------------------------------
CAAPmiUserPrismaticOperationToolActivity::~CAAPmiUserPrismaticOperationToolActivity()
{
}
 
//-----------------------------------------------------------------------------
// Implements CATIMfgToolActivity::GetAuthorizedToolTypeList
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationToolActivity::GetAuthorizedToolTypeList (CATListOfCATUnicodeString & oToolTypeList)
{

   return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATIMfgToolActivity::CreateDefaultTool
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationToolActivity::CreateDefaultTool (CATBaseUnknown_var & oTool)
{

   return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATIMfgToolActivity::GetFirstToolCompensation
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationToolActivity::GetFirstToolCompensation (int & oFirstNumber)
{

   return S_OK;
}

//-----------------------------------------------------------------------------
// Implements CATIMfgToolActivity::GetSecondToolCompensation
//-----------------------------------------------------------------------------
HRESULT CAAPmiUserPrismaticOperationToolActivity::GetSecondToolCompensation (int & oSecondNumber)
{

   return S_OK;
}

