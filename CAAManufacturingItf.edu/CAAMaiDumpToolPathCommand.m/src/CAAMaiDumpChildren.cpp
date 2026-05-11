// COPYRIGHT DASSAULT SYSTEMES 2003
// ===========================================================================
//
// CAAMaiDumpChildren
//
// External service called by CAAMaiDumpToolPathCommand to dump the 
//    children of a CATIMfgCompoundTraject object 
//                                      
//=============================================================================

#include "CAAMaiDumpChildren.h"

// Infrastructure headers
#include "CATISpecObject.h"

// Manufacturing headers
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathComponents.h"
#include "CATIMfgTPMultipleMotion.h"
#include "CATIMfgTPMultipleMotionWithProfileData.h"
#include "CATIMfgToolPathCycle.h"
#include "CATIMfgToolPathMotionCommand.h"

// Local headers
#include "CAAMaiDumpCompoundTraject.h"
#include "CAAMaiDumpCycle.h"
#include "CAAMaiDumpRotation.h"
#include "CAAMaiDumpMultipleMotion.h"
#include "CAAMaiDumpMultipleMotionWithProfileData.h"
#include "CAAMaiDumpToolPathCommand.h"

//==============================================================================
void CAAMaiDumpChildren (int iLevel,const CATIMfgCompoundTraject_var& iCompound)
{
	if (NULL_var == iCompound) return;

	iLevel++;

	//================================================================
	// Use of CATIMfgToolPathComponents interface to retrieve children
	//================================================================
	CATIMfgToolPathComponents_var Components (iCompound);
	if (NULL_var == Components) return;

	CATListValCATBaseUnknown_var* ListOfChildren = Components->GetAllElements ();
	if (NULL!=ListOfChildren)
	{
		CATUnicodeString Index;
		int size = ListOfChildren->Size();
		CATUnicodeString text1;
		text1.Resize(60,'-');
		for (int i=1;i<=size;i++)
		{
			//===================================================================================================
			// For every child, 5 cases are possible
			// 1) The element is a CATIMfgToolPathMotionCommand object (rotation)
			// 2) The element is a CATIMfgToolPathCycle object (machining cycle)
			// 3) The element is only a CATIMfgCompoundTraject object
			// 4) The element is a CATIMfgTPMultipleMotion object (tool motions)
			// 5) The element is a CATIMfgTPMultipleMotionWithProfileData (tool motions with cutter profile data)
			//===================================================================================================
			CATIMfgTPMultipleMotionWithProfileData_var MultipleMotionWithProfileData ((*ListOfChildren)[i]);
			CATIMfgTPMultipleMotion_var MultipleMotion ((*ListOfChildren)[i]);
			CATIMfgCompoundTraject_var CompoundTraject((*ListOfChildren)[i]);
			CATIMfgToolPathMotionCommand_var Rotation ((*ListOfChildren)[i]);
			CATIMfgToolPathCycle_var Cycle((*ListOfChildren)[i]);
			CATUnicodeString String;
			//=============================================================
			// The child is a CATIMfgTPMultipleMotionWithProfileData object
			//=============================================================
			if (NULL_var != MultipleMotionWithProfileData)
			{
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				Index.BuildFromNum (i);
				String = "Child index "+Index+ " is a CATIMfgTPMultipleMotionWithProfileData object  ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				CAAMaiDumpMultipleMotionWithProfileData (iLevel,MultipleMotionWithProfileData); // see CAAMaiDumpMultipleMotionWithProfileData.cpp
			}
			//==============================================
			// The child is a CATIMfgTPMultipleMotion object
			//==============================================
			else if (NULL_var != MultipleMotion)
			{
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				Index.BuildFromNum (i);
				String = "Child index "+Index+ " is a CATIMfgTPMultipleMotion object  ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				CAAMaiDumpMultipleMotion (iLevel,MultipleMotion);                               // see CAAMaiDumpMultipleMotion.cpp
			}
			//===================================================
			// The child is a CATIMfgToolPathMotionCommand object
			//===================================================
			else if (NULL_var != Rotation)
			{
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				Index.BuildFromNum (i);
				String = "Child index "+Index+ " is a CATIMfgToolPathMotionCommand object  ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				CAAMaiDumpRotation (iLevel,Rotation);                                           // see CAAMaiDumpRotation.cpp
			}
			//===========================================
			// The child is a CATIMfgToolPathCycle object
			//===========================================
			else if (NULL_var != Cycle)
			{
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				Index.BuildFromNum (i);
				String = "Child index "+Index+ " is a CATIMfgToolPathCycle object  ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				CAAMaiDumpCycle (iLevel,Cycle);                                                 // see CAAMaiDumpCycle.cpp
			}
			//======================================
			// The child is a CATIMfgCompoundTraject
			//======================================
			else if (NULL_var != CompoundTraject)
			{
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				Index.BuildFromNum (i);
				String = "Child index "+Index+ " is a CATIMfgCompoundTraject object  ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				CAAMaiDumpCompoundTraject (iLevel,CompoundTraject);                             // see CAAMaiDumpCompoundTraject.cpp
			}
			//==================
			// child not treated
			//==================
			else
			{
				CATISpecObject_var SpecObj ((*ListOfChildren)[i]);
				if (NULL_var != SpecObj)
				{
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
					Index.BuildFromNum (i);
					String = "!!!!!! Child index "+Index+ " which is a " 
						+SpecObj->GetName()+ " is not treated !!!!!";
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
				}
			}
		}
		delete ListOfChildren;
		ListOfChildren=NULL;
	}
}


