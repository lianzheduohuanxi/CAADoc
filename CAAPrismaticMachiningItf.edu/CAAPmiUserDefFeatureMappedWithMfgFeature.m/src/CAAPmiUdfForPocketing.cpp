// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfForPocketing: implementation of the 
// CATIMfgMappingForPocketing CAA interface for a type of User Defined Features
//
// ===================================================================
// DCN V5R8 10/09/01 Creation 
// ===================================================================
//
#include "CAAPmiUdfForPocketing.h"
#include "CAAPmiUdfEnv.h"

#include "CATIMfgMappingRuleName.h"

// User Defined Features Interface
#include "CATIUdfFeatureInstance.h"
#include "CATIUdfFeatureUser.h"

// LiteralFeatures
#include "CATICkeParm.h"
#include "CATIParmAsStored.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// Geometrical Interfaces
#include "CATIPrism.h"
#include "CATISketch.h"
#include "CATPlane.h"

#include "CATMathPlane.h"
#include "CATMathVector.h"


#include "TIE_CATIMfgMappingForPocketing.h"
TIEchain_CATIMfgMappingForPocketing(CAAPmiUdfForPocketing);

CATImplementClass (CAAPmiUdfForPocketing,CodeExtension,CATBaseUnknown,UdfFeature);

//-----------------------------------------------------------------------------
// Prototype for machining of User Defined Features as a Mfg Contour
//-----------------------------------------------------------------------------

extern "C" 
{
  ExportedByCAAPmiUdfEnv int CAAPmiUdfIsMachinableAsAPocketing (CATExtendable *, const GUID &);
}
//-----------------------------------------------------------------------------
// CATMfgUdfIsMachinableAsAPocketing: entry to the User Defined Features machined as a
// Mfg Pocketing validation
//-----------------------------------------------------------------------------

int CAAPmiUdfIsMachinableAsAPocketing (CATExtendable *Udf, const GUID &)
{
  int  oRetCode = 0; 
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
    // identified by their role names are well defined. One of these right role
    // names are "Drive" or "Lower_Drive"
    //----------------------------------------------------------------------
    int okDrive = 0;
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb && (0 == okDrive))
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && (role == "Drive" || role == "Lower_Drive")) okDrive = 1;
      i++;
    }
    if (0 != okDrive) oRetCode = 1;
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (oRetCode);
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAPmiUdfForPocketing::CAAPmiUdfForPocketing()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAPmiUdfForPocketing::~CAAPmiUdfForPocketing()
{
}

//-----------------------------------------------------------------------------
// GetPart
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForPocketing::GetPart (CATBaseUnknown_var & oPart)
{
  HRESULT RetCode = E_FAIL;
  oPart = NULL_var;
 
  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  HRESULT RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);

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

    int i = 1;
    while (SUCCEEDED(RC) && i <= InputNb && (role != "Drive" && role != "Upper_Drive"))
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (role == "Drive" || role == "Upper_Drive")
      {
        RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
      }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && (role == "Drive" || role == "Upper_Drive"))
    {
      //----------------------------------------------------------------------
      // This Input is a sketch from which the support plane is extracted
      //----------------------------------------------------------------------
      CATISketch_var Sketch(spInputGeom);
      CATISpecObject_var oPlane;

      if (NULL_var != Sketch) RC = Sketch->GetPlanarSupport(oPlane);
      if (SUCCEEDED(RC))
      {
        oPart = oPlane;
        
        if (NULL_var != oPart)
          RetCode = S_OK;
        else
          RetCode = E_FAIL;
      }
      else 
        RetCode = RC;
    }
    else
      RetCode = E_FAIL;
    //
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
  piUdfFeatureInstance = NULL;

return (RetCode);
}

//-----------------------------------------------------------------------------
// GetRelimitingPlane
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForPocketing::GetRelimitingPlane (CATBaseUnknown_var & oRelimitingPlane)
{
  HRESULT RetCode = S_FALSE;

  oRelimitingPlane = NULL_var;

  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  HRESULT RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);
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

    int i = 1;
    while (SUCCEEDED(RC) && i <= InputNb && (role != "Drive" && role != "Upper_Drive"))
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (role == "Drive" || role == "Upper_Drive")
      {
        RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
      }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && (role == "Drive" || role == "Upper_Drive"))
    {
      //----------------------------------------------------------------------
      // This Input is a sketch from which the support plane is extracted
      //----------------------------------------------------------------------
      CATISketch_var Sketch(spInputGeom);
      CATISpecObject_var oPlane;

      if (NULL_var != Sketch) RC = Sketch->GetPlanarSupport(oPlane);
      if (SUCCEEDED(RC))
      {
        oRelimitingPlane = oPlane;
        
        if (NULL_var != oRelimitingPlane)
          RetCode = S_OK;
        else
          RetCode = S_FALSE;
      }
      else 
        RetCode = RC;
    }
  }

  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
  piUdfFeatureInstance = NULL;

  return (RetCode);
}

//-----------------------------------------------------------------------------
// GetGuidingCurves
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForPocketing::GetGuidingCurves (CATListValCATBaseUnknown_var & oGuidingCurves)
{
  HRESULT RetCode = E_FAIL;
  //
  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  HRESULT RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);

  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC) && NULL != piUdfFeatureInstance)
  { 
    //
    CATUnicodeString role = "";
    CATBaseUnknown_var spInputGeom(NULL_var);
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
    
    //----------------------------------------------------------------------
    // Read the mapping rule name associated to the Pocketing operation 
    //----------------------------------------------------------------------
    CATUnicodeString MappingRuleName = "";
    CATIMfgMappingRuleName  *piMappRuleName = NULL;
    RC = this->QueryInterface(IID_CATIMfgMappingRuleName,(void **)&piMappRuleName);
    if (SUCCEEDED(RC) && NULL != piMappRuleName) 
    {
      MappingRuleName = piMappRuleName->GetMappingRuleName();
      piMappRuleName->Release();
      piMappRuleName = NULL;
    }
    
    //----------------------------------------------------------------------
    // Scan all the Udf Inputs to find the right input 
    // identified by their role names are well defined. This right role
    // name is "Drive" or "Upper_Drive" if either the mapping rule name is "Upper_Drive" or
    // not defined
    //----------------------------------------------------------------------
    int i =1;
    if (MappingRuleName == "Upper_Drive_Rule" || MappingRuleName == "")
    {
      while (SUCCEEDED(RC) && i <= InputNb && (role != "Drive" && role != "Upper_Drive"))
      {
        RC = piUdfFeatureInstance->GetInputRole(i, role);
        if (role == "Drive" || role == "Upper_Drive")
        {
          RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
        }
        i++;
      }
      //----------------------------------------------------------------------
      // The right Input is found
      //----------------------------------------------------------------------
      if (SUCCEEDED(RC) && (role == "Drive" || role == "Upper_Drive"))
      {
        oGuidingCurves.Append(spInputGeom);
        RetCode = S_OK;
      }
    }
    //----------------------------------------------------------------------
    // The right role name is "Lower_Drive" in case of "Lower_Drive_Rule" mapping rule name
    //----------------------------------------------------------------------
    else if (MappingRuleName == "Lower_Drive_Rule")
    {
      while (SUCCEEDED(RC) && i <= InputNb && role != "Lower_Drive")
      {
        RC = piUdfFeatureInstance->GetInputRole(i, role);
        if (SUCCEEDED(RC) && role == "Lower_Drive")
        {
          RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
        }
        i++;
      }
      //----------------------------------------------------------------------
      // The right Input is found
      //----------------------------------------------------------------------
      if (SUCCEEDED(RC) && role == "Lower_Drive")
      {
        oGuidingCurves.Append(spInputGeom);
        RetCode = S_OK;
      }
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RetCode);
}

//-----------------------------------------------------------------------------
// GetIslands
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForPocketing::GetIslands (CATListValCATBaseUnknown_var& oListOfIslands, CATListOfInt& oNbOfCurvesByIsland)
{
  HRESULT RetCode = S_FALSE;
  //
  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  HRESULT RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);

  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC) && NULL != piUdfFeatureInstance)
  { 
    //
    CATUnicodeString role = "";
    CATBaseUnknown_var spInputGeom(NULL_var);
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
    
    //----------------------------------------------------------------------
    // Scan all the Udf Inputs to find the right input 
    // identified by their role name containing "Island" 
    //----------------------------------------------------------------------
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb)
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      //----------------------------------------------------------------------
      // The right Input is found
      //----------------------------------------------------------------------
      if (SUCCEEDED(RC) && role.SearchSubString("Island",0) >= 0)
	    {
	      RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
        oListOfIslands.Append(spInputGeom);
        oNbOfCurvesByIsland.Append(1);
	    }
      i++;
    }    
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RetCode);
}
