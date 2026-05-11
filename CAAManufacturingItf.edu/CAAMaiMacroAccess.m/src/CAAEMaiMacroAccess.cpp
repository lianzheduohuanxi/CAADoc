// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAEMaiMacroAccess:
//
// Sample code for : Prismatic Machining Programmer
// Mission         : User Access on all macro motion datas defined on an activity
//
//
// Type            : Interactive functionality
//
// Illustrates     : 1- sample of use of manufacturing macro interfaces 
//                   2- read macro motion parameters with CATIMfgActivityMacroParameters
//                   CATIMfgActivityMacroMotion, CATIMfgActivityElementaryMotion interfaces
//                 
//
//
//
//=============================================================================

#include "CAAEMaiMacroAccess.h"
#include "CATBaseUnknown.h"
#include "CATListOfCATUnicodeString.h"
// Manufacturing Interfaces
#include "CATIMfgActivity.h"
#include "CATIMfgActivityMacroParameters.h"
#include "CATIMfgActivityMacroMotion.h"
#include "CATIMfgActivityElementaryMotion.h"
// Mathematics
#include "CATMathPlane.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"






//-----------------------------------------------------------------------------
// Constructeur
//-----------------------------------------------------------------------------

CAAEMaiMacroAccess::CAAEMaiMacroAccess(const CATIMfgActivity_var   &iActivity)
{
	_iActivity=iActivity;
}



//-----------------------------------------------------------------------------
// Destructeur
//-----------------------------------------------------------------------------

CAAEMaiMacroAccess::~CAAEMaiMacroAccess()
{
}

//-----------------------------------------------------------------------------
// GetMacroDatas
//-----------------------------------------------------------------------------
HRESULT CAAEMaiMacroAccess::GetMacroDatas()
{

  HRESULT RC = E_FAIL;

  CATListOfCATUnicodeString ListeCAAMacroTypes;

  ListeCAAMacroTypes.Append("MfgApproachMacro");
  ListeCAAMacroTypes.Append("MfgRetractMacro");
  ListeCAAMacroTypes.Append("MfgReturnOneLevelMacro");
  ListeCAAMacroTypes.Append("MfgReturnTwoLevelMacro");
  ListeCAAMacroTypes.Append("MfgLinkingMacro");
  ListeCAAMacroTypes.Append("MfgReturnFinishPathMacro");
  ListeCAAMacroTypes.Append("MfgClearanceMacro");
  
  CATIMfgActivityMacroParameters_var ParamMacro(_iActivity);
  
  if (NULL_var != ParamMacro)
  {
	  
	  for ( int K = 1; K <= ListeCAAMacroTypes.Size(); K++)
	  {
		  // Reading  Macro on  Activity with Type : ListeCAAMacroTypes[K].ConvertToChar() 
		  
		  
		  //
		  int oActive=0;
		  RC=ParamMacro->IsActive (K,oActive);
		  //			
		  if (SUCCEEDED(RC) && oActive==1)
		  {
			  if (K != ListeCAAMacroTypes.Size())
			  {
				  
				  // for all types of macros except clearance
				  // access to macro motions
				  for ( int MotionNature= 1; MotionNature<=2 ;MotionNature++)
				  {	
					  CATBaseUnknown_var BU1;
					  if (MotionNature==1)
					  {
						  // Reading Retract Part of Macro  
						  RC = ParamMacro->GetRetractMacroMotions(K,BU1);
						  
					  }
					  else if (MotionNature==2)
					  {
						  // Reading Approach Part of Macro 
						  RC = ParamMacro->GetApproachMacroMotions(K,BU1);
						  
					  }									
					  
					  if (SUCCEEDED(RC)) 
					  {
						  CATIMfgActivityMacroMotion_var MacroMotion(BU1);
						  if (NULL_var != MacroMotion)
						  {
							  
							  // Access to elementary motions of MacroMotion
							  
							  int MacroType=K;
							  RC=this->ReadElementaryMotionDatas(MacroType,MacroMotion);
						  }
					  }
				  }
			  }
			  else
			  {
				  CATBaseUnknown_var BU1;
				  HRESULT RC;
				  // Access to Clearance           
				  RC = ParamMacro->GetClearanceMacroMotions(BU1);
				  
				  if (SUCCEEDED(RC)) 
				  {
					  CATIMfgActivityMacroMotion_var MacroMotion(BU1);
					  if (NULL_var != MacroMotion)
					  {
						  int oMode=0;
						  // Access to clerance mode
						  RC=  MacroMotion->GetClearanceMode  (oMode); 
						  if (SUCCEEDED(RC)) 
						  {
							  
							  if (oMode==1)
							  {
								  // clearance mode = distance
								  double oDist=0.0;
								  RC=  MacroMotion->GetClearanceDistance  (oDist); 
								  
							  }
							  
						  }
						  int MacroType=K;
						  RC=this->ReadElementaryMotionDatas(MacroType,MacroMotion);
					  }
				  }
			  }
		  }
	  }
  }
  
  return RC;
}
//-----------------------------------------------------------------------------
// ReadElementaryMotionData - read datas on elementary macro motions 
//-----------------------------------------------------------------------------
HRESULT CAAEMaiMacroAccess::ReadElementaryMotionDatas(const int & iTypeMacro, 
						      CATIMfgActivityMacroMotion_var& MacroMotion)

                                           
{
	HRESULT RC = E_FAIL;
	
	int oNumber;
	RC=MacroMotion->GetNumberOfElementaryMotions(oNumber);
	if (SUCCEEDED(RC)) 
	{
		// for all macro types except clearance
		if (iTypeMacro != 7)
		{
			// loop on each elementary macro motion of MacroMotion
			for (int iPos = 1; iPos <= oNumber; iPos++)
			{
				CATBaseUnknown_var BU2; 
				RC= MacroMotion->GetElementaryMotion  (iPos,BU2);
				if (SUCCEEDED(RC)) 
				{
					CATIMfgActivityElementaryMotion_var ElementaryMotion(BU2);
					if (NULL_var != ElementaryMotion)
					{
						
						int oActive=0;
						int oType=0;
						RC=ElementaryMotion->IsActive(oActive);
						if (SUCCEEDED(RC) ) 
						{
							
							RC = ElementaryMotion->GetElementaryMotionType(oType);
							
						}
						
						// the motion must be active to be taken into account
						if (SUCCEEDED(RC) && oActive==1) 
						{							
							
							if (oType==1 || oType==2 || oType==8)
							{
								// horizontal - axial 
								double oDist=0.0;
								RC = ElementaryMotion->GetDistanceValue(oDist);
								
							}
							if (oType==6)
							{
								// goto plane
								CATMathPlane oPlane;
								RC = ElementaryMotion->GetMotionPlane(oPlane);
								
							    // read type of motion to reach the plane : axial move or perpendicular to plane move
								
								
								int oMode=0;
								RC = ElementaryMotion->GetMotionToPlaneMode (oMode);							
																	
							}
							if (oType==4)
							{
								// PP
                                CATListOfCATUnicodeString oPPWordList;
								RC = ElementaryMotion->GetPPWordList(oPPWordList);
								
								if (SUCCEEDED(RC)) 
								{	
									int NbOfPPWords=oPPWordList.Size();
									
								}								
								
							}
							if (oType==2)
							{
								// horizontal motion (equivalent to tangent - normal motion icons in macro tabpage in
								// activity Panel editor
								double oHAngle=0.0;
								RC = ElementaryMotion->GetHorizontalAngleValue(oHAngle);
								if (SUCCEEDED(RC)) 
								{	
									double oVAngle=0.0;
									RC = ElementaryMotion->GetVerticalAngleValue(oVAngle);
									
								}
							}
							if (oType==3)
							{
								// circle motion
								double oSector=0.0;
								double oOrientAngle=0.0;
								double oRadius=0.0;
								RC = ElementaryMotion->GetAngularSectorValue(oSector);
								if (SUCCEEDED(RC)) 
								{	
									RC = ElementaryMotion->GetAngularOrientationValue(oOrientAngle);
									if (SUCCEEDED(RC)) 
									{
										RC = ElementaryMotion->GetCircleRadiusValue(oRadius);
									}
									
								}								
								
							}
							if (oType==5)
							{
								// ramping motion
								double oRampAngle=0.0;
								double oHDist=0.0;
								double oVDist=0.0;
								RC = ElementaryMotion->GetRampingAngleValue(oRampAngle);
								if (SUCCEEDED(RC)) 
								{	
									RC = ElementaryMotion->GetHorizontalSafetyDistanceValue(oHDist);
									if (SUCCEEDED(RC)) 
									{	
										RC = ElementaryMotion->GetVerticalSafetyDistanceValue(oVDist);
									}
									
								}																
								
							}
						}
					}
					int oFeedType=-1;
					RC = ElementaryMotion->GetFeedrateType(oFeedType);
					if (SUCCEEDED(RC)) 
					{							
						
						if (oFeedType==5)
						{
							// local feedrate : access to feedrate value
                            double oFeedValue;
							RC=ElementaryMotion->GetFeedrateValue(oFeedValue);
							
						}
					}
					
					int oSpeedType=-1;
					RC = ElementaryMotion->GetSpindleSpeedType(oSpeedType);
					if (SUCCEEDED(RC)) 
					{							
						if (oSpeedType==5)
						{
							// access to local value
                            double oSpeedValue;
							RC=ElementaryMotion->GetSpindleSpeedValue(oSpeedValue);
						}
					}
					
				}
			}
		}
	}   
	return RC;	
   
}
