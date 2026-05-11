// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAEMaiToolPathDrillingCustomization:
//
// Sample code for : Prismatic Machining Programmer
// Mission         : Customize the Drilling Tool Path Computation
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
//						Drilling  CATIMfgComputeToolPathCustom libCAAMaiToolPathCustomization
//
//					In Prismatic Machining Programmer, 
//                         create a Drilling operation, select geometry and replay the tool path
//
//
//=============================================================================

#include "CAAEMaiToolPathDrillingCustomization.h"

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
TIE_CATIMfgComputeToolPathCustom(CAAEMaiToolPathDrillingCustomization);
CATImplementClass(CAAEMaiToolPathDrillingCustomization,
                  DataExtension,                  
                  CATBaseUnknown,
                  Drilling);



//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAEMaiToolPathDrillingCustomization::CAAEMaiToolPathDrillingCustomization()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAEMaiToolPathDrillingCustomization::~CAAEMaiToolPathDrillingCustomization()
{
}

//-----------------------------------------------------------------------------
// ComputeToolPath
//-----------------------------------------------------------------------------
HRESULT CAAEMaiToolPathDrillingCustomization::ComputeToolPath(const CATIContainer_var   &spContainer,
															  CATIMfgToolPath_var &spToolPath)
{

  HRESULT RC = E_FAIL;
  
  //********************************************************************************************
  // -1- Reading Activity Parameters 
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


  //********************************************************************************************
  // -2- Reading Tool Parameters 
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
  // -3- Building a Simple Tool Path
  // =======================================================================================


  CATIMfgToolPathFactory *piToolPathFactoryOnContainer = NULL;
  RC= spContainer->QueryInterface(IID_CATIMfgToolPathFactory,
	  (void**) &piToolPathFactoryOnContainer);
  if (FAILED (RC)) return E_FAIL;
  
  //==============================
  // Creation of tool path element
  //==============================
  CATIMfgCompoundTraject_var spCompoundTraject = 
	  piToolPathFactoryOnContainer->CreateMfgCompoundTraject();
  if (NULL_var == spCompoundTraject) return E_FAIL;
  CATIMfgToolPathComponents_var spToolPathComponentsOnCompound(spCompoundTraject); 
  if (NULL_var == spToolPathComponentsOnCompound) return E_FAIL;

  //=============================================================================
  // Initialization of tool path from activity (copy of feedrates, spindle, ....)
  //=============================================================================
  spCompoundTraject->Init(spActivity);

  //=========================================
  // Initialization of tool axis on tool path
  //=========================================
  CATIMfgToolPathConstantToolAxis_var spToolAxis = 
	  piToolPathFactoryOnContainer->CreateMfgToolPathConstantToolAxis(machiningToolAxis);
  if (NULL_var == spToolAxis) return E_FAIL;
  spCompoundTraject->SetToolAxis(spToolAxis);

  //==================================================================================
  // Creation of the objet dedicated to the description of motions
  // This objet is linked to the tool path
  //
  // In the sample,only linear motions are described
  // Note that it is also possible to describe circular motions and PP Instructions
  // PP Instructions are described through NC_Commands and NC_Instructions of PP Table
  //==================================================================================
  CATIMfgTPMultipleMotion_var spMultipleMotion = 
	  piToolPathFactoryOnContainer->CreateMfgTPMultipleMotion();
  if (NULL_var == spMultipleMotion) return E_FAIL;
  spToolPathComponentsOnCompound->AddElement(spMultipleMotion);

  //==============================
  // Description of linear motions
  //==============================
  CATMathPoint previousClearPoint;
  for (int I = 1; I<=nbOfPts; I++)      
  {
	  CATListOfDouble X,Y,Z;
	  CATMathPoint point = pointsInPattern.GetPoint(I-1);
	  CATMathPoint clearPoint = point + machiningToolAxis * clearTipValue;
	  CATMathPoint depthPoint = point - machiningToolAxis * depthValue;
	  //=======================================================
	  // Linking traject in rapid feedrate between clear points
	  //=======================================================
	  if (I>1)
	  {
		  CATListOfDouble X2,Y2,Z2;
		  X2.Append (previousClearPoint.GetX()); 
		  Y2.Append (previousClearPoint.GetY()); 
		  Z2.Append (previousClearPoint.GetZ());
		  X2.Append (clearPoint.GetX()); 
		  Y2.Append (clearPoint.GetY()); 
		  Z2.Append (clearPoint.GetZ());
		  spMultipleMotion->AddPolyline (TPLinkingTraject,TPRapidFeedrate,X2,Y2,Z2);
	  }
	  //======================================
	  // Machining Traject to machine the hole
	  //======================================
	  X.Append (clearPoint.GetX()); 
	  Y.Append (clearPoint.GetY()); 
	  Z.Append (clearPoint.GetZ());
	  X.Append (depthPoint.GetX()); 
	  Y.Append (depthPoint.GetY()); 
	  Z.Append (depthPoint.GetZ());
	  X.Append (clearPoint.GetX()); 
	  Y.Append (clearPoint.GetY()); 
	  Z.Append (clearPoint.GetZ());
	  spMultipleMotion->AddPolyline (TPMachiningTraject,TPMachiningFeedrate,X,Y,Z);

	  previousClearPoint = clearPoint;
  }

  //========================
  // Save tool path in model
  //========================
  CATIMfgTPSaveData_var spSaveData (spToolPathComponentsOnCompound);
  if (NULL_var == spSaveData) return E_FAIL;
  spSaveData->SaveData();

  //=======
  // Return
  //=======
  spToolPath = spToolPathComponentsOnCompound;
  if (NULL_var == spToolPath) return E_FAIL;
  
  piToolPathFactoryOnContainer->Release();
  piToolPathFactoryOnContainer = NULL;
  
  return RC;
}
