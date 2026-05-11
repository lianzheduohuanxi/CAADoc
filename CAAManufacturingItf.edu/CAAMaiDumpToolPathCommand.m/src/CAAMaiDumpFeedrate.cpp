// COPYRIGHT DASSAULT SYSTEMES 2003
// ===========================================================================
//
// CAAMaiDumpFeedrate
//
// External service called by CAAMaiDumpToolPathCommand to dump a reference
//   feedrate on a CATIMfgCompoundTraject object
//                                      
//=============================================================================

#include "CAAMaiDumpFeedrate.h"

// Manufacturing interfaces
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathConstantFeedrate.h"

// Local headers
#include "CAAMaiDumpToolPathCommand.h"


//==============================================================================================================
void CAAMaiDumpFeedrate (int iLevel,const CATIMfgCompoundTraject_var& iCompound,CATUnicodeString& iFeedrateType)
{
	if (NULL_var == iCompound) return;

	CATIMfgToolPathFeedrate_var Feedrate;
	//==================================================================================
	// Retrieves the CATIMfgToolPathFeedrate object on the CATIMfgCompoundTraject object
	//==================================================================================
	if (iCompound->GetFeedrate (iFeedrateType,Feedrate))
	{	
		CATIMfgToolPathConstantFeedrate_var ConstantFeedrate (Feedrate);
		if (NULL_var != ConstantFeedrate)
		{
			CATICkeParm_var FeedrateValue;
			//====================================
			// Retrieves the value of the feedrate
			//====================================
			if(ConstantFeedrate->GetFeedrate (FeedrateValue))
			{
				if (NULL_var != FeedrateValue)
				{
					CATUnicodeString String = "Value of "+iFeedrateType;
					String.Resize(60);
					String = String + FeedrateValue->Show();
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
				}
			}
		}
	}
}
