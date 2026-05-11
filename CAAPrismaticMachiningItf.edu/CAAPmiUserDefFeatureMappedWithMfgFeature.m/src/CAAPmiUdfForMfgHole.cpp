// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfForMfgHole: implementation of the CATIMfgDesignHoleParameters interface
// for the User Defined Features 
//
// Sample code for : Manufacturing Modeler
// Mission         : Support of Udf by the default drilling features mapping
// 
//
// Type            : Design to manufacturing mapping functionality
//
// Illustrates     : 1- use of UdfFeatureInstance interface
//                   2- how to return information for drilling machining features
//
// How to run it   : Set up the run time environment 
//                   In the file CAAManuturingItf.edu.dico, 
//                   decomment the following line  
//  UdfFeature  CATIMfgDesignHoleParameters   libCAAPmiUserDefFeatureMappedWithMfgFeature
//                   
//                   Launch a CATIA V5 session 
//                   Open the CAAPmiUserDefFeatureInMachProcess.CATProcess file
//                   located in: Windows InstallRootDirectory\CAAManufacturingItf.edu\CNext\resources\graphic\ 
//					 
//                   Start Prismatic Machining Workbench
//                   Open the "" machining processes catalog
//                   Double-Click the "Drilling Processes" chapter
//                   Double-Click the "Standard Drilling" Process
//                   Select the Udf UserFeature1.1 as "Geoemtry to machine"
//                   Select the OK command
//
// ===================================================================

// Manufacturing implementation
#include "CAAPmiUdfForMfgHole.h"
#include "CAAPmiUdfEnv.h"

// User Defined Features Interface
#include "CATIUdfFeatureInstance.h"

// Mathematics classes
#include "CATMathPlane.h"
#include "CATMathVector.h"

// Literal Features Interfaces
#include "CATIParmAsStored.h"

#include "CATISpecObject.h"

// Geometrical Interfaces
#include "CATPoint.h"
#include "CATPlane.h"

//-----------------------------------------------------------------------------
// Prototype for machining of User Defined Features as a Mfg Hole
//-----------------------------------------------------------------------------

extern "C" 
{
  ExportedByCAAPmiUdfEnv int CAAPmiUdfIsMachinableAsAMfgHole (CATExtendable *, const GUID &);
}
//-----------------------------------------------------------------------------
// CATMfgIsHoleMachinable: entry to the User Defined Features machined as a
// Mfg Hole validation (see the CAAManufacturingItf.dico file)
//-----------------------------------------------------------------------------

int CAAPmiUdfIsMachinableAsAMfgHole (CATExtendable *Udf, const GUID &)
{
  int oRetCode = 0;
  if (NULL == Udf) return oRetCode;
  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  HRESULT RC = Udf->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);
  
  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC) && NULL != piUdfFeatureInstance)
  {  
    CATUnicodeString role = "";
    CATBaseUnknown_var spInputGeom(NULL_var);
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
    
    //----------------------------------------------------------------------
    // Scan all the Udf Inputs to validate that the right inputs, 
    // identified by their role names are well defined. These right role
    // names are "Drilling_Point" and "Drilling_Face"
    //----------------------------------------------------------------------
    int okDrillingPoint = 0;
    int okDrillingFace = 0;
    int i =1;
    while (i <= InputNb && (0 == okDrillingPoint || 0 == okDrillingFace))
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (role == "Drilling_Point")
      {okDrillingPoint = 1;}
      else if (role == "Drilling_Face")
      {okDrillingFace = 1;}
      i++;
    }
    //----------------------------------------------------------------------
    // Get the list of the Udf published parameters declared at the Udf
    // definition
    //----------------------------------------------------------------------
    CATListValCATBaseUnknown_var * ParametersList = NULL;
    RC = piUdfFeatureInstance->GetParameters(ParametersList);

    int okHoleDiameter = 0;
    int okHoleDepth = 0;
    if (NULL != ParametersList)
    {
      int NbParams = ParametersList->Size();
      
      role = "";
      CATISpecObject_var spec(NULL_var);
      //----------------------------------------------------------------------
      // Verify that the Hole Diameter and the Depth Diameter are defined 
      // Their right role names are "Hole_Diameter" and "Hole_Depth"
      //----------------------------------------------------------------------
      i =1;
      while (i <= NbParams && (0 == okHoleDiameter || 0 == okHoleDepth))
      {
        spec = (*ParametersList)[i];
        RC = piUdfFeatureInstance->GetParameterRole(spec,role);
        if (role == "Hole_Diameter")
        {okHoleDiameter = 1;}
        else if (role == "Hole_Depth")
        {okHoleDepth = 1;}
        i++;
      }
	  delete ParametersList;
	  ParametersList = NULL;
    }
    //----------------------------------------------------------------------
    // All the characteristic roles are defined: the Udf can be machined
    // as a Mfg Hole
    //----------------------------------------------------------------------
    if (1 == okDrillingPoint && 1 == okDrillingFace && 
      1 == okHoleDiameter && 1 == okHoleDepth) oRetCode = 1;
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (oRetCode);
}

//-----------------------------------------------------------------------------
// Supported Interfaces
//-----------------------------------------------------------------------------

#include "TIE_CATIMfgDesignHoleParameters.h"
TIEchain_CATIMfgDesignHoleParameters(CAAPmiUdfForMfgHole);

CATImplementClass (CAAPmiUdfForMfgHole,DataExtension,CATBaseUnknown,UdfFeature);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAPmiUdfForMfgHole::CAAPmiUdfForMfgHole()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAPmiUdfForMfgHole::~CAAPmiUdfForMfgHole()
{
}

//-----------------------------------------------------------------------------
// get_Diameter
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForMfgHole::GetDiameter (CATICkeParm_var &oDiameter)
{
  HRESULT RC = E_FAIL;
  oDiameter  = NULL_var;

  return (RC);
}    

//-----------------------------------------------------------------------------
// get_Depth
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForMfgHole::GetDepth (CATICkeParm_var &oDepth)
{
  HRESULT RC = E_FAIL;
  oDepth     = NULL_var;

  return (RC);
}

//-----------------------------------------------------------------------------
// GetOrigin
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForMfgHole::GetOrigin (double& oX, double& oY, double& oZ)
{
  HRESULT RC = S_FALSE;
  
  oX = 0.0;
  oY = 0.0;
  oZ = 0.0;

  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);
  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC) && NULL != piUdfFeatureInstance)
  {  
    CATUnicodeString role = "";
    CATBaseUnknown_var spInputGeom(NULL_var);
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
    
    //----------------------------------------------------------------------
    // Scan all the Udf Inputs to find the right input, identified by its
    // role name in our case: the right role name is "Drilling_Point"
    // defined at the Udf definition. This is a means to easily access to
    // the right input
    //----------------------------------------------------------------------
    for (int i =1; i <= InputNb && role != "Drilling_Point"; i++)
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (role == "Drilling_Point")
      {
        RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
      }
    } 
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (role == "Drilling_Point")
    {
      //------------------------------------------------------------------
      // Extract the drilling point coordinates
      //------------------------------------------------------------------
      CATPoint *pPoint = NULL;
      RC = spInputGeom->QueryInterface(IID_CATPoint,(void **)&pPoint);
      if (SUCCEEDED(RC) && NULL != pPoint)
      {
        oX = pPoint->GetX();
        oY = pPoint->GetY();
        oZ = pPoint->GetZ();	      
        RC = S_OK;
      }
      if (NULL != pPoint) 
      {
        pPoint->Release();
        pPoint = NULL;
      }
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
 
  return (RC);
}

//-----------------------------------------------------------------------------
// GetDirection
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForMfgHole::GetDirection (double& oX, double& oY, double& oZ)
{
  HRESULT RC = S_FALSE;

  oX = 0.0;
  oY = 0.0;
  oZ = 1.0;
  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);
  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC) && NULL != piUdfFeatureInstance)
  {  
    CATUnicodeString role = "";
    CATBaseUnknown_var spInputGeom(NULL_var);
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
    //----------------------------------------------------------------------
    // Scan all the Udf Inputs to find the right input, identified by its
    // role name in our case: the right role name is "Drilling_Face"
    // defined at the Udf definition. This is a means to easily access to
    // the right input
    //----------------------------------------------------------------------
    for (int i =1; i <= InputNb && role != "Drilling_Face"; i++)
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (role == "Drilling_Face")
      {
        RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
      }
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (role == "Drilling_Face")
    {
      //------------------------------------------------------------------
      // Extract the drilling axis coordinates from the normal
      // to the plane.
      //------------------------------------------------------------------
      CATPlane *pPlane = NULL;
      RC = spInputGeom->QueryInterface(IID_CATPlane,(void **)&pPlane);
      if (SUCCEEDED(RC))
      {
        CATMathPlane MathPlane;
        pPlane->GetAxis(MathPlane);
        CATMathVector Normal;
        MathPlane.GetNormal(Normal);
        Normal.GetCoord (oX, oY, oZ);
        RC = S_OK;
      }
      if (NULL != pPlane) pPlane->Release();
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RC);
}

//-----------------------------------------------------------------------------
// get_Parameter
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForMfgHole::get_Parameter (const CATString &iParameterName, double &oParameter)
{
	HRESULT RC = S_FALSE;
	oParameter = 0.0;
	
	//--------------------------------------------------------------------------
	// Get your object as a CATIUdfFeatureInstance
	//--------------------------------------------------------------------------
	CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
	RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);
	//--------------------------------------------------------------------------
	// Your object is a CATIUdfFeatureInstance: we can use the associated methods
	//--------------------------------------------------------------------------
	if (SUCCEEDED(RC) && NULL != piUdfFeatureInstance)
    {
		//----------------------------------------------------------------------
		// Get the list of the Udf published parameters declared at the Udf
		// definition
		//----------------------------------------------------------------------
		CATListValCATBaseUnknown_var * ParametersList = NULL;
		RC = piUdfFeatureInstance->GetParameters(ParametersList);
		int NbParams = 0;
		if (NULL != ParametersList)
		{
			int NbParams = ParametersList->Size();
			CATUnicodeString role = "";
			CATISpecObject_var spec(NULL_var);
			//----------------------------------------------------------------------
			// Match the right Machining Feature Attribute with the right
			// User Defined Feature attribute. According to the role name
			// of each Udf attribute, you can have a better mapping
			//----------------------------------------------------------------------
			int i =1;
			//----------------------------------------------------------------------
			// For the Drilling Hole Diameter
			//----------------------------------------------------------------------
			if (iParameterName == "Diameter")
			{
				while (i <= NbParams && role != "Hole_Diameter")
				{
					spec = (*ParametersList)[i];
					RC = piUdfFeatureInstance->GetParameterRole(spec,role);
					if (role != "Hole_Diameter") i++;
				}
			}
			//----------------------------------------------------------------------
			// For the Drilling Hole Depth
			//----------------------------------------------------------------------
			else if (iParameterName == "Depth")
			{
				while (i <= NbParams && role != "Hole_Depth")
				{
					spec = (*ParametersList)[i];
					RC = piUdfFeatureInstance->GetParameterRole(spec,role);
					if (role != "Hole_Depth") i++;
				}
			}
			//----------------------------------------------------------------------
			// For the Counterboring Hole Depth
			//----------------------------------------------------------------------
			else if (iParameterName == "CBDepth")
			{
				while (i <= NbParams && role != "Bore_Depth")
				{
					spec = (*ParametersList)[i];
					RC = piUdfFeatureInstance->GetParameterRole(spec,role);
					if (role != "Bore_Depth") i++;
				}
			}
			//----------------------------------------------------------------------
			// Requested attribute found
			//----------------------------------------------------------------------
			if (i <= NbParams)
			{
				//------------------------------------------------------------------
				// Return the value if it is accessible through the CATIParmAsStored
				// interface
				//------------------------------------------------------------------
				CATIParmAsStored_var Parm(spec);
				if (!!Parm)
				{
					oParameter = Parm->ValueStored();
					RC = S_OK;
				}
			}
			delete ParametersList;
			ParametersList = NULL;
		}
    }
	if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
	
	return (RC);
}

//-----------------------------------------------------------------------------
// get_Parameter
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForMfgHole::get_Parameter (const CATString &iParameterName, int &oParameter)
{
  HRESULT RC = S_OK;
  oParameter = 0;
  //--------------------------------------------------------------------------
  // Specific valuation for the Hole Extension type
  // You can make here your own implementation according to the Udf definition
  //--------------------------------------------------------------------------
  if (iParameterName == "MfgHoleExtension")
    {
      //----------------------------------------------------------------------
      // The Drilling Hole is always Blind (= 2 for Through)
      //----------------------------------------------------------------------
      oParameter = 1;
    }
  return (RC);
}

