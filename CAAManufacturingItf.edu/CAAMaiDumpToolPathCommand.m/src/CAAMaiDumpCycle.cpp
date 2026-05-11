// COPYRIGHT DASSAULT SYSTEMES 2003
// ===========================================================================
//
// CAAMaiDumpCycle
//
// External service called by CAAMaiDumpToolPathCommand to dump a 
//    CATIMfgToolPathCycle object (description of a machining cycle)
//                                      
//=============================================================================

#include "CAAMaiDumpCycle.h"

// Manufacturing headers
#include "CATIMfgToolPathCycle.h"
#include "CATIMfgTPCycleLinkingMotion.h"
#include "CATIMfgToolPathConstantFeedrate.h"

// Local headers
#include "CAAMaiDumpCompoundTraject.h"
#include "CAAMaiDumpToolPathCommand.h"

//===========================================================================
void CAAMaiDumpCycle       (int iLevel,const CATIMfgToolPathCycle_var& iCycle)

{
	if (NULL_var == iCycle) return;

	//==========================
	// Retrieves location points
	//==========================
	CATMathSetOfPoints Points;
	int NumberOfLocationPoints=0;
	if (iCycle->GetCycleLocationPoints (Points))
	{
		NumberOfLocationPoints=Points.GetNumberOfPoints ();
		if (NumberOfLocationPoints > 100)
		{
			CATUnicodeString String ("More than 100 location points    ");
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
		else
		{
			CATMathPoint Pt;
			CATUnicodeString ValueX,ValueY,ValueZ;
			CATUnicodeString Index;
			for (int i=1;i<=NumberOfLocationPoints;i++)
			{
				Pt = Points.GetPoint (i-1);
				Index.BuildFromNum (i);
				ValueX.BuildFromNum (Pt.GetX());
				ValueY.BuildFromNum (Pt.GetY());
				ValueZ.BuildFromNum (Pt.GetZ());
				CATUnicodeString String = "Location point index ";
				String = String + Index;
				String.Resize(60);
				String = String + ValueX + " " + ValueY + " " + ValueZ;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
		}
	}

	//==================================================
	// Retrieves axis (if they exist) on location points
	//==================================================
	CATMathSetOfVectors Vectors;
	if (iCycle->GetCycleLocationAxis (Vectors))
	{
		int size=Vectors.GetNumberOfVectors ();
		if (size > 100)
		{
			CATUnicodeString String ("More than 100 location axis    ");
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
		else
		{
			CATMathVector Vec;
			CATUnicodeString ValueX,ValueY,ValueZ;
			CATUnicodeString Index;
			for (int i=1;i<=size;i++)
			{
				Vec = Vectors.GetVector (i-1);
				Index.BuildFromNum (i);
				ValueX.BuildFromNum (Vec.GetX());
				ValueY.BuildFromNum (Vec.GetY());
				ValueZ.BuildFromNum (Vec.GetZ());
				CATUnicodeString String = "Location axis index " + Index;
				String.Resize(60);
				String=String + ValueX + " " + ValueY + " " + ValueZ;
				CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
			}
		}
	}

	//=======================================================================
	// Retrieves syntax of the cycle
	// --> UserSyntax    OR
	// --> Syntax evaluated from NC_Command or NC_Instruction of the PP Table
	//=======================================================================
	CATListValCATUnicodeString Liste;
	if (iCycle->GetUserSyntax (Liste))
	{
		int size = Liste.Size();
		for (int i=1;i<=size;i++)
		{
			CATUnicodeString String = "User syntax associated to the cycle";
			String.Resize(60);
			String = String + Liste[i];
			CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
		}
	}
	else if (iCycle->GetCommandEvaluation (Liste))
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

	//==============================================================================
	//==============================================================================
	// Management of linking motions between cycle location points machining motions
	//    with CATIMfgTPCycleLinkingMotion interface
	//==============================================================================
	//==============================================================================
	CATIMfgTPCycleLinkingMotion_var TPCycleLinkingMotion (iCycle);
	if (NULL_var==TPCycleLinkingMotion) return;

	//=================================================
	// Are there linking motions stored on the object ?
	//=================================================
	int LinkingMotions = TPCycleLinkingMotion->AreThereLinkingMotions ();
	if (LinkingMotions)
	{
		CATUnicodeString String ("At least one linking motion stored in the cycle");
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
	}
	else
	{
		CATUnicodeString String ("No linking motion stored in the cycle");
		CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
	}

	if (LinkingMotions)
	{
		for (int iLocationPoint=0;iLocationPoint<=NumberOfLocationPoints;iLocationPoint++)
		{
			int NumberOfMotions=0;

			//=================================================================
			// Is there a linking motion for the current cycle location point ?
			//=================================================================
			if (TPCycleLinkingMotion->GetNumberOfSubMotions (iLocationPoint,NumberOfMotions))
			{
				if (NumberOfMotions)
				{
					if (0==iLocationPoint)
					{
						CATUnicodeString String ("An approach traject to the first location point is defined");
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
					}
					else if (NumberOfLocationPoints==iLocationPoint)
					{
						CATUnicodeString String ("A retract traject from the last location point is defined   ");
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
					}
					else
					{
						CATUnicodeString Value1,Value2;
						Value1.BuildFromNum (iLocationPoint);
						Value2.BuildFromNum (iLocationPoint+1);
						CATUnicodeString String = "A linking motion is defined from location point " + Value1 + " to location point " + Value2;
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
					}
				}

				for (int iIndexOfMotion=1;iIndexOfMotion<=NumberOfMotions;iIndexOfMotion++)
				{
					CATUnicodeString IndexOfMotion;
					IndexOfMotion.BuildFromNum (iIndexOfMotion);
					CATUnicodeString String = "+++ SubMotion " + IndexOfMotion + " is a ";
					int SubMotionType;

					//==================================================================
					// Retrieves the type of the current submotion of the linking motion
					//==================================================================
					if (TPCycleLinkingMotion->GetSubMotionType (iLocationPoint,iIndexOfMotion,SubMotionType))
					{
						if (CATIMfgTPCycleLinkingMotion::PolyLine==SubMotionType)
						{
							String = String + "PolyLine";
						}
						else if (CATIMfgTPCycleLinkingMotion::Circle == SubMotionType)
						{
							String = String + "Circle";
						}
						else if (CATIMfgTPCycleLinkingMotion::PPCommand == SubMotionType)
						{
							String = String + "PP Command";
						}
						else if (CATIMfgTPCycleLinkingMotion::UserSyntax == SubMotionType)
						{
							String = String + "User Syntax";
						}
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
					}

					//====================================
					// The current submotion is a PolyLine
					//====================================
					if (CATIMfgTPCycleLinkingMotion::PolyLine==SubMotionType)
					{
						CATUnicodeString TrajectType;
						CATListOfDouble ListOfX,ListOfY,ListOfZ;
						if (TPCycleLinkingMotion->GetPolylineCharacteristics (iLocationPoint,iIndexOfMotion,
							                                                  TrajectType,ListOfX,ListOfY,ListOfZ))
						{
							CATUnicodeString String = "++++++ Traject type";
							String.Resize(60);
							String = String + TrajectType;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);

							String = "++++++ Number of tip points";
							String.Resize(60);
							int NumberOfTipPoints = ListOfX.Size();
							CATUnicodeString String2;
							String2.BuildFromNum (NumberOfTipPoints);
							String = String + String2;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);

							if (NumberOfTipPoints>100)
							{
								String = "More than 100 tip points";
								CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
							}
							else
							{
								for (int iTipPoint=1;iTipPoint<=NumberOfTipPoints;iTipPoint++)
								{
									if (iTipPoint <= ListOfY.Size() && iTipPoint <= ListOfZ.Size())
									{
										CATUnicodeString String;
										CATUnicodeString String2;
										String2.BuildFromNum (iTipPoint);
										String = "+++++++++ TipPoint number "+String2;
										String.Resize(60);
										double x = ListOfX[iTipPoint]; double y = ListOfY[iTipPoint]; double z = ListOfZ[iTipPoint];
										CATUnicodeString ValueX,ValueY,ValueZ;
										ValueX.BuildFromNum(x); ValueY.BuildFromNum(y); ValueZ.BuildFromNum(z);
										String = String + ValueX + " " + ValueY + " " + ValueZ;
										CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
									}
								}
							}
						}
					}

					//======================================
					// The current submotion is a Circle Arc
					//======================================
					if (CATIMfgTPCycleLinkingMotion::Circle==SubMotionType)
					{
						CATUnicodeString TrajectType;
						CATListOfDouble ListOfX,ListOfY,ListOfZ;
						CATMathPoint  Center;
						CATMathVector Normal;
						double        Radius;
						if (TPCycleLinkingMotion->GetCircleArcCharacteristics (iLocationPoint,iIndexOfMotion,
							                                                   TrajectType,ListOfX,ListOfY,ListOfZ,
																			   Normal,Center,Radius))
						{
							CATUnicodeString String = "++++++ Traject type";
							String.Resize(60);
							String = String + TrajectType;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
							
							String = "++++++ Number of tip points";
							String.Resize(60);
							int NumberOfTipPoints = ListOfX.Size();
							CATUnicodeString String2;
							String2.BuildFromNum (NumberOfTipPoints);
							String = String + String2;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
							
							if (NumberOfTipPoints>100)
							{
								String = "More than 100 tip points";
								CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
							}
							else
							{
								for (int iTipPoint=1;iTipPoint<=NumberOfTipPoints;iTipPoint++)
								{
									if (iTipPoint <= ListOfY.Size() && iTipPoint <= ListOfZ.Size())
									{
										CATUnicodeString String;
										CATUnicodeString String2;
										String2.BuildFromNum (iTipPoint);
										String = "+++++++++ TipPoint number "+String2;
										String.Resize(60);
										double x = ListOfX[iTipPoint]; double y = ListOfY[iTipPoint]; double z = ListOfZ[iTipPoint];
										CATUnicodeString ValueX,ValueY,ValueZ;
										ValueX.BuildFromNum(x); ValueY.BuildFromNum(y); ValueZ.BuildFromNum(z);
										String = String + ValueX + " " + ValueY + " " + ValueZ;
										CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
									}
								}
							}

							String = "++++++ Coordinates of normal to plane "; 
							String.Resize(60);
							CATUnicodeString ValueX,ValueY,ValueZ;
							ValueX.BuildFromNum (Normal.GetX()); ValueY.BuildFromNum (Normal.GetY()); ValueZ.BuildFromNum (Normal.GetZ());
							String = String + ValueX + " " + ValueY + " " + ValueZ;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);

							String = "++++++ Coordinates of center "; 
							String.Resize(60);
							ValueX.BuildFromNum (Center.GetX()); ValueY.BuildFromNum (Center.GetY()); ValueZ.BuildFromNum (Center.GetZ());
							String = String + ValueX + " " + ValueY + " " + ValueZ;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);

							String = "++++++ Radius "; 
							String.Resize(60);
							ValueX.BuildFromNum (Radius); 
							String = String + ValueX;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
						}
					}

					//======================================
					// The current submotion is a PP Command
					//======================================
					if (CATIMfgTPCycleLinkingMotion::PPCommand==SubMotionType)
					{
						CATListValCATUnicodeString CommandValue;
						if (TPCycleLinkingMotion->GetCommandEvaluation (iLocationPoint,iIndexOfMotion,CommandValue))
						{
							int NumberOfValue = CommandValue.Size();
							for (int j=1;j<=NumberOfValue;j++)
							{
								CATUnicodeString String1 = "++++++ NC_Command value";
								String1.Resize(60);
								String1 = String1 + CommandValue[j];
								CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
							}
						}
					}

					//=======================================
					// The current submotion is a user syntax
					//=======================================
					if (CATIMfgTPCycleLinkingMotion::UserSyntax==SubMotionType)
					{
						CATUnicodeString UserSyntax;
						if (TPCycleLinkingMotion->GetUserSyntaxCharacteristics(iLocationPoint,iIndexOfMotion,UserSyntax))
						{
							CATUnicodeString String1 = "++++++ User syntax value";
							String1.Resize(60);
							String1 = String1 + UserSyntax;
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String1);
						}
					}

					//=============================
					// Retrieves possible tool axis
					//=============================
					CATListOfDouble ListOfX,ListOfY,ListOfZ;
					if (TPCycleLinkingMotion->GetToolAxis (iLocationPoint,iIndexOfMotion,
														   ListOfX,ListOfY,ListOfZ))
					{
						String = "++++++ Number of tool axis";
						String.Resize(60);
						int NumberOfToolAxis = ListOfX.Size();
						CATUnicodeString String2;
						String2.BuildFromNum (NumberOfToolAxis);
						String = String + String2;
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
						
						if (NumberOfToolAxis>100)
						{
							String = "More than 100 tool axis";
							CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
						}
						else
						{
							for (int iToolAxis=1;iToolAxis<=NumberOfToolAxis;iToolAxis++)
							{
								if (iToolAxis <= ListOfY.Size() && iToolAxis <= ListOfZ.Size())
								{
									CATUnicodeString String;
									CATUnicodeString String2;
									String2.BuildFromNum (iToolAxis);
									String = "+++++++++ Tool axis number "+String2;
									String.Resize(60);
									double x = ListOfX[iToolAxis]; double y = ListOfY[iToolAxis]; double z = ListOfZ[iToolAxis];
									CATUnicodeString ValueX,ValueY,ValueZ;
									ValueX.BuildFromNum(x); ValueY.BuildFromNum(y); ValueZ.BuildFromNum(z);
									String = String + ValueX + " " + ValueY + " " + ValueZ;
									CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
								}
							}
						}
					}

					//=======================================
					// Retrieves possible 'symbolic' feedrate
					//=======================================
					double Ratio;
					CATUnicodeString FeedrateSymbol;
					if (TPCycleLinkingMotion->GetSymbolicFeedrate (iLocationPoint,iIndexOfMotion,
																   FeedrateSymbol,Ratio))
					{
						CATUnicodeString String = "++++++ Feedrate symbol type";
						String.Resize(60);
						String = String + FeedrateSymbol;
						CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
					}

					//=======================================
					// Retrieves possible 'specific' feedrate
					//=======================================
					CATIMfgToolPathFeedrate_var SpecificFeedrate;
					if (TPCycleLinkingMotion->GetSpecificFeedrate (iLocationPoint,iIndexOfMotion,
																   SpecificFeedrate))
					{
						CATIMfgToolPathConstantFeedrate_var ConstantFeedrate (SpecificFeedrate);
						if (NULL_var != ConstantFeedrate)
						{
							CATICkeParm_var FeedrateValue;
							if(ConstantFeedrate->GetFeedrate (FeedrateValue))
							{
								if (NULL_var != FeedrateValue)
								{
									String = "++++++ Value of specific feedrate";
									String.Resize(60);
									String = String + FeedrateValue->Show();
									CAAMaiDumpToolPathCommand::CAAMaiWriteString (iLevel,String);
								}
							}
						}
					}
					
				}
			}
		}
	}


	//==========================================================================
	// As a CATIMfgToolPathCycle object is also a CATIMfgCompoundTraject object,
	// dump of its "CATIMfgCompoundTraject" attributes
	//========================================================================
	CAAMaiDumpCompoundTraject (iLevel,iCycle);     // see CAAMaiDumpCompoundTraject.cpp
}

