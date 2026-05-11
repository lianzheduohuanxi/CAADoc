// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpNurbsData
//
// External service called by CAAMaiDumpToolPathCommand to dump data from 
// a CATIMfgTPNurbsDescription object (description of nurbs data)
//                                      
//=============================================================================
#include "CAAMaiDumpNurbsData.h"

// Infrastructure headers
# include "CATUnicodeString.h"

// Manufacturing headers
#include "CATIMfgTPNurbsDescription.h"

// Local headers
#include "CAAMaiDumpToolPathCommand.h"

//===========================================================================
void CAAMaiDumpNurbsData       (int iLevel,const CATIMfgTPNurbsDescription_var& iNurbsData)

{
	if (NULL_var==iNurbsData) return;

	iLevel++;

	CATUnicodeString String1,String2;
	
	//======================================
	// Retrieves the number of sets of nurbs
	//======================================
	int NumberOfSetsOfNurbs;
	if (iNurbsData->GetNumberOfNurbsPacket(NumberOfSetsOfNurbs))
	{
		String1.BuildFromNum (NumberOfSetsOfNurbs);
		String2="Number of sets of nurbs";
		String2.Resize(60);
		String2 = String2+String1;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);
	}

	for (int iIndexOfSet=1;iIndexOfSet<=NumberOfSetsOfNurbs;iIndexOfSet++)
	{
		String1.BuildFromNum (iIndexOfSet);
		String2="Set of nurbs index";
		String2.Resize(60);
		String2=String2+String1;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

		//============================================
		// Retrieves characteristics of a set of nurbs
		//============================================
		int StartPolyline, EndPolyline, StartNurbs, EndNurbs;
		if (iNurbsData->GetNurbsPacketCharacteristics(iIndexOfSet,StartPolyline,EndPolyline,StartNurbs,EndNurbs))
		{
			String1.BuildFromNum (StartPolyline);
			String2="+++ Index of start polyline";
			String2.Resize(60);
			String2 = String2+String1;
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

			String1.BuildFromNum (EndPolyline);
			String2="+++ Index of end polyline";
			String2.Resize(60);
			String2 = String2+String1;
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

			String1.BuildFromNum (StartNurbs);
			String2="+++ Index of start nurbs";
			String2.Resize(60);
			String2 = String2+String1;
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

			String1.BuildFromNum (EndNurbs);
			String2="+++ Index of end nurbs";
			String2.Resize(60);
			String2 = String2+String1;
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

			for (int iIndexOfNurbs=StartNurbs;iIndexOfNurbs<=EndNurbs;iIndexOfNurbs++)
			{
				String1.BuildFromNum (iIndexOfNurbs);
				String2="+++ Index of nurbs";
				String2.Resize(60);
				String2=String2+String1;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

				//=====================================
				// Retrieves characteristics of a nurbs
				//=====================================
				int Degree,StartPole,EndPole;
				if (iNurbsData->GetNurbsCharacteristics(iIndexOfNurbs,Degree,StartPole,EndPole))
				{
					String1.BuildFromNum (Degree);
					String2="++++++ Nurbs degree";
					String2.Resize(60);
					String2 = String2+String1;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);
					
					String1.BuildFromNum (StartPole);
					String2="++++++ index of start pole";
					String2.Resize(60);
					String2 = String2+String1;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);
					
					String1.BuildFromNum (EndPole);
					String2="++++++ index of end pole";
					String2.Resize(60);
					String2 = String2+String1;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

					for (int iPole=StartPole;iPole<=EndPole;iPole++)
					{
						String1.BuildFromNum (iPole);
						String2="++++++ Index of pole";
						String2.Resize(60);
						String2=String2+String1;
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);
	
						//====================================
						// Retrieves characteristics of a pole
						// ===================================
						double Xt,Yt,Zt,W,Dk;
						if (iNurbsData->GetPoleCharacteristics (iPole,Xt,Yt,Zt,W,Dk))
						{
							CATUnicodeString String,String1,String2,String3,String4,String5;
							String1.BuildFromNum (Xt);
							String2.BuildFromNum (Yt);
							String3.BuildFromNum (Zt);
							String4.BuildFromNum (W);
							String5.BuildFromNum (Dk);
							String = "+++++++++ Characteristics of pole";
							String.Resize(60);
							String = String + String1 + " " + String2 + " " + String3 + " " + String4 + " " + String5;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
						}

						//====================================================
						// Retrieves possible 5 axes characteristics of a pole
						//====================================================
						double Xh,Yh,Zh;
						if (iNurbsData->GetPoleCharacteristics2 (iPole,Xh,Yh,Zh))
						{
							CATUnicodeString String,String1,String2,String3;
							String1.BuildFromNum (Xh);
							String2.BuildFromNum (Yh);
							String3.BuildFromNum (Zh);
							String = "+++++++++ 5 axis characteristics of pole";
							String.Resize(60);
							String = String + String1 + " " + String2 + " " + String3;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
						}
					}
				}
			}
		}
	}
}

