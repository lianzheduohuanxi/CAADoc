// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiDumpMultipleMotion
//
// External service called by CAAMaiDumpToolPathCommand to dump data from 
// a CATIMfgTPMultipleMotion object (description of tool motions)
//                                      
//=============================================================================

#include "CAAMaiDumpMultipleMotion.h"

// Manufacturing headers
#include "CATIMfgTPMultipleMotion.h"
#include "CATIMfgTPMultipleMotionNurbs.h"
#include "CATIMfgTPNurbsDescription.h"
#include "CATIMfgResource.h"
#include "CATMfgToolPathDefs.h"

// Local headers
#include "CAAMaiDumpNurbsData.h"
#include "CAAMaiDumpToolPathCommand.h"

//===========================================================================
void CAAMaiDumpMultipleMotion       (int iLevel,const CATIMfgTPMultipleMotion_var& iMultipleMotion)

{
	if (NULL_var == iMultipleMotion) return;

	CATUnicodeString String1,String2;
	CATUnicodeString ValueX,ValueY,ValueZ;
	//===================================
	// Retrieves the number of tip points
	//===================================
	int NumberOfTipPoints = iMultipleMotion->GetNumberOfTipPoints();
	String1.BuildFromNum (NumberOfTipPoints);
	String2="Number of tip points";
	String2.Resize(60);
	String2 = String2+String1;
	CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

	//=======================================
	// Retrieves the number of contact points
	//=======================================
	int NumberOfContactPoints = iMultipleMotion->GetNumberOfContactPoints();
	String1.BuildFromNum (NumberOfContactPoints);
	String2="Number of contact points";
	String2.Resize(60);
	String2 = String2+String1;
	CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

	//========================================
	// Retrieves the number of contact normals
	//========================================
	int NumberOfContactNormals = iMultipleMotion->GetNumberOfContactNormals();
	String1.BuildFromNum (NumberOfContactNormals);
	String2="Number of contact normals";
	String2.Resize(60);
	String2 = String2+String1;
	CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

	//==================================
	// Retrieves the number of tool axis
	//==================================
	int NumberOfToolAxis = iMultipleMotion->GetNumberOfToolAxisPoints();
	String1.BuildFromNum (NumberOfToolAxis);
	String2="Number of tool axis";
	String2.Resize(60);
	String2 = String2+String1;
	CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);

	//================================
	// Retrieves number of sub-motions
	//================================
	int NumberOfSubMotions;
	if (iMultipleMotion->GetNumberOfSubTrajects (NumberOfSubMotions))
	{
		String1 = "Number of sub-motions   ";
		String1.Resize(60);
		String2.BuildFromNum (NumberOfSubMotions);
		String1 = String1 + String2;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
	}

	//================================
	// Retrieves Tool or Tool Assembly
	//================================
	CATBaseUnknown_var ToolOrToolAssembly;
	if (iMultipleMotion->GetToolAssembly (ToolOrToolAssembly))
	{
		CATIMfgResource_var Resource (ToolOrToolAssembly);
		if (NULL_var != Resource)
		{
			CATUnicodeString Name;
			Resource->GetName(Name);
			CATUnicodeString String =  "Name of tool or tool assembly";
			String.Resize(60);
			String=String+Name;
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
	}

	//============================
	// Retrieves possible PQR data
	//============================
	int TotalNumberOfPQRData=0;
	if (iMultipleMotion->GetTotalNumberOfPQRDatas(TotalNumberOfPQRData))
	{
		if (TotalNumberOfPQRData)
		{
			CATUnicodeString String =  "The object has PQR data";
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
		else
		{
			CATUnicodeString String =  "The object have not PQR data";
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
	}

	//=========================================
	// Retrieves information on each sub-motion
	//=========================================
	for (int i=1;i<=NumberOfSubMotions;i++)
	{
		CATUnicodeString Index;
		
		//===================
		// Type of sub-motion
		//===================
		CATIMfgTPMultipleMotion::SubTrajectType SubTrajectType;
		if (iMultipleMotion->GetSubTrajectType (i,SubTrajectType))
		{
			Index.BuildFromNum (i);
			if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine)
			{
				CATUnicodeString String = "+++ Sub-motion "+Index+" is a polyline   ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
			else if (SubTrajectType == CATIMfgTPMultipleMotion::Circle)
			{
				CATUnicodeString String = "+++ Sub-motion "+Index+" is a circle   ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
			else if (SubTrajectType == CATIMfgTPMultipleMotion::UserSyntax)
			{	
				CATUnicodeString String = "+++ Sub-motion "+Index+" is a user syntax   ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);	
			}
			else if (SubTrajectType == CATIMfgTPMultipleMotion::PPCommand)
			{	
				CATUnicodeString String = "+++ Sub-motion "+Index+" is a PP command   ";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);	
			}
		}
		
		//=========================================================
		// Path type (Machining, Linking, ....)
		// --> For a polyline or a circle arc
		// --> See CATMfgToolPathDefs for reference values 
		//              (TPMachiningTraject, TPLinkingTraject, ...)
		//=========================================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine || 
			SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			CATUnicodeString TrajectType;
			if (iMultipleMotion->GetTrajectType (TrajectType,i))
			{
				String1 = "++++++ Type of path";
				String1.Resize(60);
				String1 = String1 + TrajectType;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
		}
		
		//============================================================================
		// Index of start point and end point in the list of tip points
		//  and, it they exist, in the list of tool path axis, contact points, etc ...
		// --> For a polyline or a circle arc
		// --> To get a tip point, use "GetTipPoint (i,x,y,z) with a value of "i"
		//     between index of start point and index of end point
		//============================================================================
		int StartIndex=0,EndIndex=0;
		if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine || 
			SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			if (iMultipleMotion->GetStartAndEndNumber (i,StartIndex,EndIndex))
			{
				ValueX.BuildFromNum (StartIndex);
				ValueY.BuildFromNum (EndIndex);
				String1 = "++++++ Index of Start and End tip points";
				String1.Resize(60);
				String1 = String1 + ValueX + " " + ValueY;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
		}

		//====================================
		// Retrieves coordinates of tip points
		//====================================
		if (EndIndex-StartIndex+1 > 100)
		{
			String1="More than 100 tip points";
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
		}
		else
		{
			double x,y,z;
			CATUnicodeString Index;
			for (int i=StartIndex;i<=EndIndex;i++)
			{
				if (iMultipleMotion->GetTipPoint (i,x,y,z))
				{
					ValueX.BuildFromNum (x);
					ValueY.BuildFromNum (y);
					ValueZ.BuildFromNum (z);
					Index.BuildFromNum (i);
					String1 = "+++++++++ Tip point number "+Index;
					String1.Resize(60);
					String2 = String1 + ValueX + " " + ValueY + " " + ValueZ;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);
				}
			}
		}
		
		//=====================================
		// Retrieves feedrate of the sub-motion
		// --> For a polyline or a circle arc
		//=====================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine || 
			SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			CATICkeParm_var FeedrateValue;
			double Ratio;
			CATUnicodeString Feedrate;
			if (iMultipleMotion->GetFeedrateConstantValue (FeedrateValue,Ratio,i))
			{
				if (NULL_var != FeedrateValue)
				{
					String1 = "++++++ Feedrate value";
					String1.Resize(60);
					String1 = String1 + FeedrateValue->Show();
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
					
					ValueX.BuildFromNum (Ratio);
					String1 = "++++++ Ratio to apply on feedrate";
					String1.Resize(60);
					String1 = String1 + ValueX;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				}
			}
			//================================
			// Special test for RAPID Feedrate
			//================================
			else if (iMultipleMotion->GetFeedrate (Feedrate,Ratio,i) && 
				     TPRapidFeedrate == Feedrate)
			{
					String1 = "++++++ RAPID feedrate for the motion";
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
		}
		
		//=================================================
		// Retrieves spindle speed value for the sub-motion
		// --> For a polyline or a circle arc
		//=================================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine || 
			SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			CATICkeParm_var SpindleValue;
			double Ratio;
			if (iMultipleMotion->GetSpindleConstantValue (SpindleValue,Ratio,i))
			{
				if (NULL_var != SpindleValue)
				{
					String1 = "++++++ Spindle value";
					String1.Resize(60);
					String1 = String1 + SpindleValue->Show();
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
					
					ValueX.BuildFromNum (Ratio);
					String1 = "++++++ Ratio to apply on spindle";
					String1.Resize(60);
					String1 = String1 + ValueX;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				}
			}
		}
		
		//======================================================
		// Retrieves spindle rotation direction for a sub-motion
		// --> For a polyline or a circle arc
		//======================================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine || 
			SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			int RotationWay;
			if (iMultipleMotion->GetSpindleRotationWay (RotationWay,i))
			{
				if (-1 == RotationWay)
				{
					String1 = "++++++ Inverse rotation direction for the spindle";
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				}
				else
				{
					String1 = "++++++ Normal rotation direction for the spindle";
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				}
			}
		}
		
		//====================================================
		// Retrieves tool axis for the sub-motion 
		// --> For a polyline or a circle arc
		// --> If fixed for the sub-motion
		//====================================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine || 
			SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			CATMathVector ToolAxis;
			if (iMultipleMotion->GetToolAxisConstantValue (ToolAxis,i))
			{
				ValueX.BuildFromNum (ToolAxis.GetX()); 
				ValueY.BuildFromNum (ToolAxis.GetY()); 
				ValueZ.BuildFromNum (ToolAxis.GetZ()); 
				String1 = "++++++ Fixed Tool Axis value";
				String1.Resize(60);
				String1 = String1 + ValueX + " " + ValueY + " " + ValueZ;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
		}
		
		//====================================================
		// Retrieves characteristics if sub-motion is a circle
		// --> Normal vector to the plane containing the circle
		// --> Center of the circle arc
		// --> Radius of the circle arc
		// --> Angle of the circle arc
		// --> Tangent vector at the start of the circle
		//====================================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			CATMathVector Normal,StartTangent;
			CATMathPoint Center;
			double Radius;
			CATAngle Angle;
			if (iMultipleMotion->GetCircleCharacteristics (i,
				Normal,Center,Radius,Angle,StartTangent))
			{	
				ValueX.BuildFromNum (Normal.GetX()); 
				ValueY.BuildFromNum (Normal.GetY()); 
				ValueZ.BuildFromNum (Normal.GetZ()); 
				String1 = "++++++ Normal to the plane ";
				String1.Resize(60);
				String1 = String1 + ValueX + " " + ValueY + " " + ValueZ;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				
				ValueX.BuildFromNum (Center.GetX()); 
				ValueY.BuildFromNum (Center.GetY()); 
				ValueZ.BuildFromNum (Center.GetZ()); 
				String1 = "++++++ Center of the circle arc";
				String1.Resize(60);
				String1 = String1 + ValueX + " " + ValueY + " " + ValueZ;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				
				ValueX.BuildFromNum (Radius);
				String1 = "++++++ Radius of the circle arc";
				String1.Resize(60);
				String1 = String1 + ValueX;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				
				ValueX.BuildFromNum (Angle);
				String1 = "++++++ Angle of the circle arc";
				String1.Resize(60);
				String1 = String1 + ValueX;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				
				ValueX.BuildFromNum (StartTangent.GetX()); 
				ValueY.BuildFromNum (StartTangent.GetY()); 
				ValueZ.BuildFromNum (StartTangent.GetZ()); 
				String1 = "++++++ Tangent at the start of the circle arc";
				String1.Resize(60);
				String1 = String1 + ValueX + " " + ValueY + " " + ValueZ;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
		}
		
		//======================================
		// Retrieves tool corrector number value
		// --> For a polyline or a circle arc
		//======================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::PolyLine || 
			SubTrajectType == CATIMfgTPMultipleMotion::Circle)
		{
			int CorrectorNumber;
			if (iMultipleMotion->GetCorrectorNumber (CorrectorNumber,i))
			{
				ValueX.BuildFromNum (CorrectorNumber);
				String1 = "++++++ Tool corrector number";
				String1.Resize(60);
				String1 = String1 + ValueX;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
		}
		
		//=======================================================
		// Retrieves evaluation of a NC_Command or NC_Instruction
		//=======================================================
		if (SubTrajectType == CATIMfgTPMultipleMotion::PPCommand)
		{
			CATListValCATUnicodeString CommandValue;
			if (iMultipleMotion->GetCommandEvaluation (i,CommandValue))
			{
				int NumberOfValue = CommandValue.Size();
				for (int j=1;j<=NumberOfValue;j++)
				{
					String1 = "++++++ NC_Command value";
					String1.Resize(60);
					String1 = String1 + CommandValue[j];
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				}
			}
		}

		//===============================================
		// Retrieves possible PQR data for the sub-motion
		//===============================================
		int NumberOfPQRData=0;
		if (TotalNumberOfPQRData)
		{
			if (iMultipleMotion->GetNumberOfPQRDatas(i,NumberOfPQRData))
			{
				if (NumberOfPQRData)
				{
					String2.BuildFromNum (NumberOfPQRData);
					String1 = "++++++ Number of PQR data";
					String1.Resize(60);
					String1 = String1 + String2;
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				}
				else
				{
					String1 = "++++++ No PQR data for the sub-motion";
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				}
			}
		}

		//===========================================
		// Retrieves coordinates of possible PQR data
		//===========================================
		if (NumberOfPQRData)
		{
			if (NumberOfPQRData > 100)
			{
				String1="More than 100 PQR vectors";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
			else
			{
				double x,y,z;
				CATUnicodeString Index;
				for (int iPQR=1;iPQR<=NumberOfPQRData;iPQR++)
				{
					if (iMultipleMotion->GetPQRData (i,iPQR,x,y,z))
					{
						ValueX.BuildFromNum (x);
						ValueY.BuildFromNum (y);
						ValueZ.BuildFromNum (z);
						Index.BuildFromNum (iPQR);
						String1 = "+++++++++ PQR vector number "+Index;
						String1.Resize(60);
						String2 = String1 + ValueX + " " + ValueY + " " + ValueZ;
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String2);
					}
				}
			}
		}
	}

	//==========================================================================
	// Retrieves possible nurbs data with CATIMfgTPMultipleMotionNurbs interface
	//==========================================================================
	CATIMfgTPMultipleMotionNurbs_var MultipleMotionNurbs (iMultipleMotion);
	if (NULL_var!=MultipleMotionNurbs)
	{
		CATIMfgTPNurbsDescription_var NurbsData;
		if (MultipleMotionNurbs->GetNurbsDescription (NurbsData))
		{
			if (NULL_var == NurbsData) 
			{
				String1 = "No nurbs data linked to the object";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
			}
			else
			{
				String1 = "Nurbs data exist on the object";
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
				CAAMaiDumpNurbsData (iLevel,NurbsData);    // see CAAMaiDumpNurbsData.cpp
			}
		}
	}
}

