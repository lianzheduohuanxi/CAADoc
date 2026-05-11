// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpMultipleMotionWithProfileData :
//
// External service called by CAAMaiDumpToolPathCommand to dump data from 
// a CATIMfgTPMultipleMotionWithProfileData object (description of cutter
// profile data inside tool motions)
//                                      
//=============================================================================

#include "CAAMaiDumpMultipleMotionWithProfileData.h"

// Manufacturing headers
#include "CATIMfgTPMultipleMotionWithProfileData.h"

// Local headers
#include "CAAMaiDumpMultipleMotion.h"
#include "CAAMaiDumpToolPathCommand.h"


//===========================================================================
void CAAMaiDumpMultipleMotionWithProfileData      (int iLevel,const CATIMfgTPMultipleMotionWithProfileData_var& iMultipleMotionWithProfileData)

{
	//=============================================================================================
	// As a CATIMfgTPMultipleMotionWithProfileData object is also a CATIMfgTPMultipleMotion object,
	// dump of its "CATIMfgTPMultipleMotion" attributes
	//=============================================================================================
	CAAMaiDumpMultipleMotion (iLevel,iMultipleMotionWithProfileData);    // see CAAMaiDumpMultipleMotion.cpp

	//=========================================================================================
	// Now we dump the specific attributes of the CATIMfgTPMultipleMotionWithProfileData object
	//=========================================================================================
	CATUnicodeString text1;
	text1.Resize(60,'=');
	CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);
	CATUnicodeString String = "+++ Dump of cutter profile datas   ";
	CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
	CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,text1);

	int number;
	iMultipleMotionWithProfileData->GetNumberOfSubTrajects (number);

	for (int i=1;i<=number;i++)
	{
		CATUnicodeString Index;
		Index.BuildFromNum (i);

		//=======================================================================
		// Retrieves type of profile data for a sub-motion (Polyline,Circle,None)
		//=======================================================================
		CATIMfgTPMultipleMotionWithProfileData::ProfileType ProfileType;
		if (iMultipleMotionWithProfileData->GetProfileType (i,ProfileType))
		{
			if (ProfileType == CATIMfgTPMultipleMotionWithProfileData::UndefType)
			{
				CATUnicodeString String = "+++ No cutter profile datas for sub-motion "+Index;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
			else if (ProfileType == CATIMfgTPMultipleMotionWithProfileData::Polyline)
			{
				CATUnicodeString String = "+++ Cutter profile datas described by a polyline for sub-motion "+Index;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
			else if (ProfileType == CATIMfgTPMultipleMotionWithProfileData::Circle)
			{
				CATUnicodeString String = "+++ Cutter profile datas described by a circle for sub-motion "+Index;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
		}

		//=============================================================================
		// Retrieves the side on which are located cutter profile data for a sub-motion
		//=============================================================================
		CATIMfgTPMultipleMotionWithProfileData::ProfileSide ProfileSide;
		if (iMultipleMotionWithProfileData->GetProfileSide (i,ProfileSide))
		{
			if (ProfileSide == CATIMfgTPMultipleMotionWithProfileData::UndefType)
			{
				CATUnicodeString String = "+++ No cutter profile datas for sub-motion "+Index;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
			else if (ProfileSide == CATIMfgTPMultipleMotionWithProfileData::Left)
			{
				CATUnicodeString String = "+++ Cutter profile datas located on the left for sub-motion "+Index;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
			else if (ProfileSide == CATIMfgTPMultipleMotionWithProfileData::Right)
			{
				CATUnicodeString String = "+++ Cutter profile datas located on the right for sub-motion "+Index;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
		}

		//==========================================
		// Retrieves profile points for a sub-motion
		//==========================================
		int NumberOfProfilePoints;
		if (iMultipleMotionWithProfileData->GetNumberOfProfilePoints (i,NumberOfProfilePoints))
		{
			Index.BuildFromNum (NumberOfProfilePoints);
			CATUnicodeString String = "+++ Number of cutter profile points "+Index;
			CATUnicodeString ValueX,ValueY,ValueZ;
			CATUnicodeString String1,String2;
			double x,y,z;
			for (int j=1;j<=NumberOfProfilePoints;j++)
			{
				if (iMultipleMotionWithProfileData->GetProfilePoint (i,j,x,y,z))
				{
					ValueX.BuildFromNum (x);
					ValueY.BuildFromNum (y);
					ValueZ.BuildFromNum (z);
					Index.BuildFromNum (j);
					String1 = "++++++ Profile point number "+Index;
					String1.Resize(60);
					String2 = String1 + ValueX + " " + ValueY + " " + ValueZ;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);
				}
			}
		}
	}
}
