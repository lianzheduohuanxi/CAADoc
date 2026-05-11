// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAEMaiToolPathDrillingDwellDelayCustomization:
//
// Sample code for : Prismatic Machining Programmer
// Mission         : Customize the "Drilling Dwell Delay" Tool Path Computation
//                   
//
// Type            : Interactive functionality
//
// Illustrates     : 1- use of manufacturing interfaces 
//                   2- read activity parameters, tool parameter
//                   3- Tool path creation 
//
// How to run it   :  
//					In the file CAAManufacturingItf.dico, decomment the following line  
//	                DrillingDwellDelay  CATIMfgComputeToolPathCustom libCAAMaiToolPathWithCycleCustomization
//
//					In Prismatic Machining Programmer, 
//                         create a Drilling operation, select geometry and replay the tool path
//
//                  You can also generate APT Code: depending of value of "Output CYCLE Syntax" option,
//                  a NC_DRILLING syntax OR related GOTO/ are generated
//                  
//
//
//=============================================================================

#include "CAAEMaiToolPathDrillingDwellDelayCustomization.h"

// Manufacturing Interfaces
#include "CATIMfgActivity.h"
#include "CATIMfgAxialOperation.h"
#include "CATIMfgAxialToolPathGeneratorBase.h"
#include "CATIMfgTool.h"
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathComponents.h"
#include "CATIMfgToolPathConstantToolAxis.h"
#include "CATIMfgToolPathFactory.h"
#include "CATIMfgTPSaveData.h"

// Manufacturing Includes
#include "CATMfgAxialOperationDefs.h"
#include "CATMfgToolPathDefs.h"
#include "CATMfgToolConstant.h"

// Mathematics
#include "CATMathSetOfPoints.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

//-----------------------------------------------------------------------------
// Supported Interfaces
//-----------------------------------------------------------------------------


#include "TIE_CATIMfgComputeToolPathCustom.h"
TIE_CATIMfgComputeToolPathCustom(CAAEMaiToolPathDrillingDwellDelayCustomization);
CATImplementClass(CAAEMaiToolPathDrillingDwellDelayCustomization,
                  DataExtension,                  
                  CATBaseUnknown,
                  DrillingDwellDelay);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAEMaiToolPathDrillingDwellDelayCustomization::CAAEMaiToolPathDrillingDwellDelayCustomization()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAEMaiToolPathDrillingDwellDelayCustomization::~CAAEMaiToolPathDrillingDwellDelayCustomization()
{
}

//-----------------------------------------------------------------------------
// ComputeToolPath
//-----------------------------------------------------------------------------
HRESULT CAAEMaiToolPathDrillingDwellDelayCustomization::ComputeToolPath(const CATIContainer_var   &spContainer,
																		CATIMfgToolPath_var &spToolPath)
{

  HRESULT RC = E_FAIL;
  
  //********************************************************************************************
  // - Reading Activity Parameters 
  //********************************************************************************************

  CATIMfgAxialOperation *piAxialOperationOnDrilling = NULL;
  RC = QueryInterface(IID_CATIMfgAxialOperation,(void**) &piAxialOperationOnDrilling);  
  if (FAILED(RC))
    return RC;
  
  CATUnicodeString depthMode;
  CATMathVector machiningToolAxis(0,0,0);
  double clearTipValue = .0;
  double depthValue = .0;
  
  // -1.1-b Read Tip Approach Clearance 2nd Solution
  RC = piAxialOperationOnDrilling->GetClearTip(clearTipValue);
  if (SUCCEEDED(RC))    
  {
	  // -1.2- Read Tip Depth Mode : by Tip, by Shoulder, by Diameter
	  RC = piAxialOperationOnDrilling->GetDepthComputationMode(depthMode); 
	  if (SUCCEEDED(RC))      
	  {        // -1.3- Read the Machining Tool Axis
		  RC = piAxialOperationOnDrilling->GetOperationAxis(machiningToolAxis);
		  if (SUCCEEDED(RC))        
		  {          
			  // -1.4- Read the hole Depth 
			  RC = piAxialOperationOnDrilling->GetFeatureDepth(depthValue);
		  }
		  
	  }   
	  
  }
  
  piAxialOperationOnDrilling->Release();
  piAxialOperationOnDrilling = NULL;
  if (FAILED(RC))   
	  return RC;  


  // -1.5- Read Pattern Information
  CATMathSetOfPoints pointsInPattern; // Points in the pattern
  CATListOfDouble    entryDistances;  // Entry distances associated with the points
  CATListOfDouble    exitDistances;   // Exit distances associated with the points
  int                nbOfPts = 0;     // Number of points in the pattern 
  
  CATIMfgAxialToolPathGeneratorBase * piAxialTPGenBaseOnDrilling = NULL;
  RC = QueryInterface(IID_CATIMfgAxialToolPathGeneratorBase, 
	  (void**) &piAxialTPGenBaseOnDrilling);
  if (SUCCEEDED(RC)) 
  {
      piAxialTPGenBaseOnDrilling->GetOperationPattern(pointsInPattern, 
		  entryDistances, exitDistances, nbOfPts);
      piAxialTPGenBaseOnDrilling->Release();    
      piAxialTPGenBaseOnDrilling = NULL;
  }  
  else    
      return RC;

  if (nbOfPts <=0) return E_FAIL;


  //********************************************************************************************
  // - Reading Tool Parameters 
  //********************************************************************************************
  CATIMfgActivity_var spActivity(this);
  if (NULL_var == spActivity) 
      return E_FAIL;
  
  CATBaseUnknown_var spUnknownOnTool;
  spUnknownOnTool = spActivity->GetTool();  
  if (NULL_var == spUnknownOnTool)
      return E_FAIL;  
  
  CATIMfgTool * piToolOnTool = NULL;
  RC = spUnknownOnTool->QueryInterface(IID_CATIMfgTool, (void**) & piToolOnTool);
  if (FAILED(RC))
      return E_FAIL;  
  
  // -3.1- Tool Diameter
  double toolDiamValue = .0;
  RC = piToolOnTool->GetValue(MfgNominalDiameter, toolDiamValue);
  
  // -3.2- Way Of Rotation  
  CATUnicodeString wayOfRotation;  
  if (SUCCEEDED(RC))
      RC = piToolOnTool->GetValue(MfgWayOfRotation, wayOfRotation);
  
  piToolOnTool->Release();  
  piToolOnTool = NULL;  
  if (FAILED(RC))    
      return RC;
  
  // =======================================================================================
  // - Building The Tool Path
  // The structure of the tool path is as follows :
  //  Drilling Dwell Delay Operation --> CompoundTraject
  //                                                    --> MfgToolPathCycle
  //                                                             --> MultipleMotion
  //  "MfgToolPathCycle" models the "Drilling Dwell Delay" cycle
  //      --> storage of the NC_Command NC_DRILLING_DWELL_DELAY   
  //      --> storage of the tool motions ("MultipleMotion")
  //  "MultipleMotion"
  //      --> For each hole
  //          * Rapid path from previous hole to current one
  //          * Downward machining path of the hole 
  //          * Insertion of a NC_DELAY instruction
  //          * Upward machining path of the hole
  //      
  // =======================================================================================


  CATIMfgToolPathFactory *piToolPathFactoryOnContainer = NULL;
  RC= spContainer->QueryInterface(IID_CATIMfgToolPathFactory,
	                             (void**) &piToolPathFactoryOnContainer);
  if (FAILED (RC)) return E_FAIL;
  
  //
  // Creation of tool path element
  //
  CATIMfgCompoundTraject_var spCompoundTraject = 
	  piToolPathFactoryOnContainer->CreateMfgCompoundTraject();
  if (NULL_var == spCompoundTraject) return E_FAIL;
  CATIMfgToolPathComponents_var spToolPathComponentsOnCompound(spCompoundTraject); 
  if (NULL_var == spToolPathComponentsOnCompound) return E_FAIL;

  //
  // Initialization of tool path from activity (copy of feedrates, spindle, ....)
  //
  spCompoundTraject->Init(spActivity);

  //
  // Initialization of tool axis on tool path
  //
  CATIMfgToolPathConstantToolAxis_var spToolAxis = piToolPathFactoryOnContainer
	  ->CreateMfgToolPathConstantToolAxis(machiningToolAxis);
  if (NULL_var == spToolAxis) return E_FAIL;
  spCompoundTraject->SetToolAxis(spToolAxis);

  //
  // Description of machining cycle
  //
  CATUnicodeString NC_Command ("NC_DRILLING_DWELL_DELAY");
  CATIMfgToolPathCycle_var ToolPathCycle = 
	  piToolPathFactoryOnContainer->CreateMfgToolPathCycle(NC_Command);
  if (NULL_var == ToolPathCycle) return E_FAIL;
  spToolPathComponentsOnCompound->AddElement(ToolPathCycle);

  // Location points for the cycle description
  CATMathSetOfPoints LocationPoints;
  LocationPoints.SetNumberOfPoints (nbOfPts);
  int I = 1;
  for (;I<=nbOfPts; I++)
  {
	  CATMathPoint LocationPoint = pointsInPattern.GetPoint(I-1);
	  LocationPoints.SetPoint (LocationPoint,I-1);
  }
  ToolPathCycle->SetCycleLocationPoints (LocationPoints);

  // Description of tool motions for the machining cycle
  CATIMfgToolPathComponents_var spToolPathComponentsOnCycle (ToolPathCycle);
  if (NULL_var == spToolPathComponentsOnCycle) return E_FAIL;
  CATIMfgTPMultipleMotion_var MultipleMotion = 
	  piToolPathFactoryOnContainer->CreateMfgTPMultipleMotion();
  if (NULL_var == MultipleMotion) return E_FAIL;
  spToolPathComponentsOnCycle->AddElement(MultipleMotion);

  CATMathPoint previousClearPoint;
  for (I = 1; I<=nbOfPts; I++)      
  {
	  CATMathPoint point = pointsInPattern.GetPoint(I-1);
	  CATMathPoint clearPoint = point + machiningToolAxis * clearTipValue;
	  CATMathPoint depthPoint = point - machiningToolAxis * depthValue;
	  CATListOfDouble X,Y,Z;
	  //
	  // Linking path in rapid feedrate between clearance points
	  //
	  if (I>1)
	  {
		  X.RemoveAll(); Y.RemoveAll(); Z.RemoveAll();
		  X.Append (previousClearPoint.GetX()); 
		  Y.Append (previousClearPoint.GetY()); 
		  Z.Append (previousClearPoint.GetZ());
		  X.Append (clearPoint.GetX()); 
		  Y.Append (clearPoint.GetY()); 
		  Z.Append (clearPoint.GetZ());
		  MultipleMotion->AddPolyline (TPLinkingTraject,TPRapidFeedrate,X,Y,Z);
	  }
	  //
	  // Downward machining path to machine the hole
	  //
	  X.RemoveAll(); Y.RemoveAll(); Z.RemoveAll();
	  X.Append (clearPoint.GetX()); 
	  Y.Append (clearPoint.GetY()); 
	  Z.Append (clearPoint.GetZ());
	  X.Append (depthPoint.GetX()); 
	  Y.Append (depthPoint.GetY()); 
	  Z.Append (depthPoint.GetZ());
	  MultipleMotion->AddPolyline (TPMachiningTraject,TPMachiningFeedrate,X,Y,Z);
	  
	  //
	  // NC_DELAY Command
	  //
	  CATUnicodeString NCCommandName ("NC_DELAY");
	  MultipleMotion->AddPPCommand (NCCommandName);
	  
	  //
	  //Downward machining path to machine the hole
	  // 
	  X.RemoveAll(); Y.RemoveAll(); Z.RemoveAll();
	  X.Append (depthPoint.GetX()); 
	  Y.Append (depthPoint.GetY()); 
	  Z.Append (depthPoint.GetZ());
	  X.Append (clearPoint.GetX()); 
	  Y.Append (clearPoint.GetY()); 
	  Z.Append (clearPoint.GetZ());
	  MultipleMotion->AddPolyline (TPMachiningTraject,TPMachiningFeedrate,X,Y,Z);
	  
	  previousClearPoint = clearPoint;
  }

  //
  // Save tool path in model
  //
  CATIMfgTPSaveData_var spSaveData (spToolPathComponentsOnCompound);
  if (NULL_var == spSaveData) return E_FAIL;
  spSaveData->SaveData();

  //
  // Return
  //
  spToolPath = spToolPathComponentsOnCompound;
  if (NULL_var == spToolPath) return E_FAIL;
  
  piToolPathFactoryOnContainer->Release();
  piToolPathFactoryOnContainer = NULL;
  
  return RC;
}
