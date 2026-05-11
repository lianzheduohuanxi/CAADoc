// COPYRIGHT DASSAULT SYSTEMES 2003
// ===========================================================================
//
// CAAMaiDumpCompoundTraject
//
// External service called by CAAMaiDumpToolPathCommand to dump a 
//    CATIMfgCompoundTraject object 
//                                      
//=============================================================================

#include "CAAMaiDumpCompoundTraject.h"

// Manufacturing headers
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathConstantSpindle.h"
#include "CATIMfgToolPathConstantToolAxis.h"
#include "CATMfgToolPathDefs.h"
#include "CATIMfgResource.h"

// Local headers
#include "CAAMaiDumpFeedrate.h"
#include "CAAMaiDumpChildren.h"
#include "CAAMaiDumpToolPathCommand.h"

//===========================================================================
void CAAMaiDumpCompoundTraject       (int iLevel,const CATIMfgCompoundTraject_var& iCompound)
{
	if (NULL_var == iCompound) return;

    //=========================================================================
	// Retrieves machining time,total time, number of linear and circular motions
	//=========================================================================
	double MachiningTime,TotalTime;
	long LinearMotions,CircularMotions;
	if (iCompound->GetCharacteristics (MachiningTime,
		                               TotalTime,LinearMotions,CircularMotions))
	{
		CATUnicodeString String1;
		CATUnicodeString String2;

		String2.BuildFromNum (MachiningTime);
		String1 = "Value of machining time (in minutes)";
		String1.Resize(60);
		String1 = String1 + String2;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);

		String2.BuildFromNum (TotalTime);
		String1 = "Value of total time (in minutes)";
		String1.Resize(60);
		String1 = String1 + String2;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
		
		String2.BuildFromNum (LinearMotions);
		String1 = "Number of linear motions";
		String1.Resize(60);
		String1 = String1 + String2;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);

		String2.BuildFromNum (CircularMotions);
		String1 = "Number of circular motions";
		String1.Resize(60);
		String1 = String1 + String2;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
	}

    //====================================================================
	// Retrieves axis guidance mode (Fixed,Variable)
	//====================================================================
	CATBoolean HasAToolAxis;
	CATBoolean HasAFixedToolAxis;
	CATMathVector Dummy;
	if (iCompound->RetrievesFixedToolAxis (HasAToolAxis,HasAFixedToolAxis,Dummy))
	{
		CATUnicodeString String;
		if (HasAToolAxis)
		{
			if (HasAFixedToolAxis)
				String = "Tool Axis is fixed    ";
			else 
				String = "Tool Axis is variable ";
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
	}

	//=======================================
	// Retrieves value of reference tool axis
	//=======================================
	CATIMfgToolPathToolAxis_var ToolAxis;
	if (iCompound->GetToolAxis(ToolAxis))
	{
		CATIMfgToolPathConstantToolAxis_var ConstantToolAxis (ToolAxis);
		if (NULL_var != ConstantToolAxis)
		{
			CATMathVector ToolAxisValue;
			if (ConstantToolAxis->GetToolAxis (ToolAxisValue))
			{
				CATUnicodeString ValueX,ValueY,ValueZ;
				ValueX.BuildFromNum (ToolAxisValue.GetX());
				ValueY.BuildFromNum (ToolAxisValue.GetY());
				ValueZ.BuildFromNum (ToolAxisValue.GetZ());
				CATUnicodeString String = "Coordinates of reference tool axis in absolute axis system";
				String.Resize(60);
				String = String + ValueX+" "+ValueY+" "+ValueZ;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
		}
	}

	//==========================
	// Retrieves feedrate values
	//==========================
	CATUnicodeString FeedrateType = TPMachiningFeedrate;
	CAAMaiDumpFeedrate (iLevel,iCompound,FeedrateType);         // see CAAMaiDumpFeedrate.cpp
	
	FeedrateType = TPApproachFeedrate;
	CAAMaiDumpFeedrate (iLevel,iCompound,FeedrateType);         // see CAAMaiDumpFeedrate.cpp

	FeedrateType = TPRetractFeedrate;
	CAAMaiDumpFeedrate (iLevel,iCompound,FeedrateType);         // see CAAMaiDumpFeedrate.cpp

    FeedrateType = TPFinishingFeedrate; 
	CAAMaiDumpFeedrate (iLevel,iCompound,FeedrateType);         // see CAAMaiDumpFeedrate.cpp

	FeedrateType = TPChamferingFeedrate;
	CAAMaiDumpFeedrate (iLevel,iCompound,FeedrateType);         // see CAAMaiDumpFeedrate.cpp

	FeedrateType = TPPlungeFeedrate;
	CAAMaiDumpFeedrate (iLevel,iCompound,FeedrateType);         // see CAAMaiDumpFeedrate.cpp

	//==================================
	// Retrieves the spindle speed value
	//==================================
	CATIMfgToolPathSpindle_var Spindle;
	if (iCompound->GetSpindle (Spindle))
	{	
		CATIMfgToolPathConstantSpindle_var ConstantSpindle (Spindle);
		if (NULL_var != ConstantSpindle)
		{
			CATICkeParm_var SpindleValue;
			if(ConstantSpindle->GetSpindle (SpindleValue))
			{
				if (NULL_var != SpindleValue)
				{
					CATUnicodeString String = "Value of Spindle speed";
					String.Resize(60);
					String = String+SpindleValue->Show();
					CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
				}
			}
		}
	}

	//====================================
	// Retrieves the tool or tool assembly
	//====================================
	CATIMfgToolPathToolAssembly_var TPTA;
	if (iCompound->GetToolAssembly (TPTA))
	{
		CATBaseUnknown_var ToolOrToolassembly;
		if (TPTA->GetTool(ToolOrToolassembly))
		{
			CATIMfgResource_var spResource (ToolOrToolassembly);
			if (NULL_var != spResource)
			{
				CATUnicodeString Name;
				spResource->GetName(Name);
				CATUnicodeString String =  "Name of tool or tool assembly";
				String.Resize(60);
				String=String+Name;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
		}
	}

	//====================================
	// Retrieves the Tool Corrector Number
	//====================================
	int CorrectorNumber;
	if (iCompound->GetCorrectorNumber (CorrectorNumber))
	{
		CATUnicodeString String;
		String.BuildFromNum (CorrectorNumber);
		CATUnicodeString String1 = "Value of corrector number";
		String1.Resize(60);
		String1 = String1 + String;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
	}

	//===========================================
	// Retrieves the start point of the tool path
	//===========================================
	CATMathPoint StartPoint;
	CATMathVector StartVector;
	if (iCompound->GetStartPoint (StartPoint,StartVector))
	{
		CATUnicodeString ValueX,ValueY,ValueZ;
		ValueX.BuildFromNum (StartPoint.GetX());
		ValueY.BuildFromNum (StartPoint.GetY());
		ValueZ.BuildFromNum (StartPoint.GetZ());
		CATUnicodeString String = "Start Point coordinates in absolute axis system";
		String.Resize(60);
		String=String+ValueX+" "+ValueY+" "+ValueZ+" ";
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		ValueX.BuildFromNum (StartVector.GetX());
		ValueY.BuildFromNum (StartVector.GetY());
		ValueZ.BuildFromNum (StartVector.GetZ());
		String = "Start axis coordinates in absolute axis system";
		String.Resize(60);
		String=String+ValueX+" "+ValueY+" "+ValueZ+" ";
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
	}

	//=========================================
	// Retrieves the end point of the tool path
	//=========================================
	CATMathPoint EndPoint;
	CATMathVector EndVector;
	if (iCompound->GetEndPoint (EndPoint,EndVector))
	{
		CATUnicodeString ValueX,ValueY,ValueZ;
		ValueX.BuildFromNum (EndPoint.GetX());
		ValueY.BuildFromNum (EndPoint.GetY());
		ValueZ.BuildFromNum (EndPoint.GetZ());
		CATUnicodeString String = "End Point coordinates in absolute axis system";
		String.Resize(60);
		String=String+ValueX+" "+ValueY+" "+ValueZ+" ";
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		ValueX.BuildFromNum (EndVector.GetX());
		ValueY.BuildFromNum (EndVector.GetY());
		ValueZ.BuildFromNum (EndVector.GetZ());
		String = "End axis coordinates in absolute axis system";
		String.Resize(60);
		String=String+ValueX+" "+ValueY+" "+ValueZ+" ";
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
	}

	//==========================================================
	// Retrieves the machining tolerance stored on the tool path
	//==========================================================
	double toler;
	if (iCompound->GetMachiningTolerance(toler))
	{
		CATUnicodeString Value;
		Value.BuildFromNum (toler);
		CATUnicodeString String = "Machining Tolerance in MKS unit";
		String.Resize(60);
		String = String + Value;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
	}

	//================================
	// Retrieves the compensation mode
	//================================
	CATIMfgCompoundTraject::CompensationMode CompensationMode;
	if (iCompound->GetCompensationMode(CompensationMode))
	{
		CATUnicodeString Value;
		if (CATIMfgCompoundTraject::None_Compensation==CompensationMode)
			Value = "None_Compensation";
		else if (CATIMfgCompoundTraject::PlanarTip_Compensation==CompensationMode)
			Value = "PlanarTip_Compensation";
		else if (CATIMfgCompoundTraject::PlanarProfile_Compensation==CompensationMode)
			Value = "PlanarProfile_Compensation,";
		else if (CATIMfgCompoundTraject::NormDSVector_Compensation==CompensationMode)
			Value = "NormDSVector_Compensation";
		else if (CATIMfgCompoundTraject::NormDSDirection_Compensation==CompensationMode)
			Value = "NormDSDirection_Compensation,";
		else if (CATIMfgCompoundTraject::NormPSTip_Compensation==CompensationMode)
			Value = "NormPSTip_Compensation";
		else if (CATIMfgCompoundTraject::NormPSContact_Compensation==CompensationMode)
			Value = "NormPSContact_Compensation";

		CATUnicodeString String = "Compensation mode";
		String.Resize(60);
		String = String + Value;
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
	}

	//===================
	// Retrieves children
	//===================
	CAAMaiDumpChildren (iLevel,iCompound);       // see CAAMaiDumpChildren.cpp
}



