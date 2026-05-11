// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpRotation
//
// External service called by CAAMaiDumpToolPathCommand to dump data from 
// a CATIMfgToolPathMotionCommand object (description of rotation)
//                                      
//=============================================================================
#include "CAAMaiDumpRotation.h"

// Manufacturing headers
#include "CATIMfgToolPathMotionCommand.h"

// Local headers
#include "CAAMaiDumpCompoundTraject.h"
#include "CAAMaiDumpToolPathCommand.h"

//===========================================================================
void CAAMaiDumpRotation       (int iLevel,const CATIMfgToolPathMotionCommand_var& iRotation)

{
	if (NULL_var == iRotation) return;

	//=======================================================================
	// Retrieves syntax of the rotation
	//=======================================================================
	CATListValCATUnicodeString Liste;
	if (iRotation->GetCommandEvaluation (Liste))
	{
		int size = Liste.Size();
		for (int i=1;i<=size;i++)
		{
			CATUnicodeString String = "NC_command evaluation";
			String.Resize(60);
			String = String + Liste[i];
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
	}

	//==================================================================================
	// As a CATIMfgToolPathMotionCommand object is also a CATIMfgCompoundTraject object,
	// dump of its "CATIMfgCompoundTraject" attributes
	//==================================================================================
	CAAMaiDumpCompoundTraject (iLevel,iRotation);      // see DumpCompoundTraject.cpp
}



