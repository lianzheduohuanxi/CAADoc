/**
 * @fullreview PMT DCN 01:09:28
 */
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfForFollowCurve: implementation of the 
// CATIMfgMappingForFollowCurve CAA interface for a type of User Defined Features
//
// ===================================================================
// DCN V5R8 21/09/01 Creation 
// ===================================================================
//
#include "CAAPmiUdfForFollowCurve.h"
#include "CAAPmiUdfEnv.h"

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
#include "CATPlane.h"


#include "TIE_CATIMfgMappingForFollowCurve.h"
TIEchain_CATIMfgMappingForFollowCurve(CAAPmiUdfForFollowCurve);

CATImplementClass (CAAPmiUdfForFollowCurve,CodeExtension,CATBaseUnknown,UdfFeature);

//-----------------------------------------------------------------------------
// Prototype for machining of User Defined Features as a Mfg Contour
//-----------------------------------------------------------------------------

extern "C" 
{
  ExportedByCAAPmiUdfEnv int CAAPmiUdfIsMachinableAsAFollowCurve (CATExtendable *, const GUID &);
}
//-----------------------------------------------------------------------------
// CATMfgUdfIsMachinableAsAFollowCurve: entry to the User Defined Features machined as a
// Mfg Follow Curve validation
//-----------------------------------------------------------------------------

int CAAPmiUdfIsMachinableAsAFollowCurve (CATExtendable *Udf, const GUID &)
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
    // names is "Follow_Curve"
    //----------------------------------------------------------------------
    int okDrive = 0;
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb && (0 == okDrive))
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && role == "Follow_Curve") okDrive = 1;
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

CAAPmiUdfForFollowCurve::CAAPmiUdfForFollowCurve()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAPmiUdfForFollowCurve::~CAAPmiUdfForFollowCurve()
{
}


//-----------------------------------------------------------------------------
// GetGuidingCurves
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForFollowCurve::GetGuidingCurves (CATListValCATBaseUnknown_var & oGuidingCurves)
{
  HRESULT RetCode = E_FAIL;

  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  HRESULT RC = this->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);

  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC))
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
    // identified by their role names are well defined. This right role
    // name is "Follow_Curve"
    //----------------------------------------------------------------------
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb && role != "Follow_Curve")
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && role == "Follow_Curve")
      {
        RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
      }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && role == "Follow_Curve")
    {
      oGuidingCurves.Append(spInputGeom);
      RetCode = S_OK;
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RetCode);
}
//-----------------------------------------------------------------------------
// GetAuxiliaryGuidingCurves
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForFollowCurve::GetAuxiliaryGuidingCurves (CATListValCATBaseUnknown_var & oAuxiliaryGuidingCurves)
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
  if (SUCCEEDED(RC))
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
    // identified by their role names are well defined. This right role
    // name is "Auxiliary_Follow_Curve"
    //----------------------------------------------------------------------
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb && role != "Auxiliary_Follow_Curve")
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && role == "Auxiliary_Follow_Curve")
      {
        RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
      }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && role == "Auxiliary_Follow_Curve")
    {
      oAuxiliaryGuidingCurves.Append(spInputGeom);
      RetCode = S_OK;
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RetCode);
}
//-----------------------------------------------------------------------------
// GetChecks
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForFollowCurve::GetChecks (CATListValCATBaseUnknown_var & oChecks)
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
  if (SUCCEEDED(RC))
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
    // identified by their role names are well defined. This right role
    // name is "Part" 
    //----------------------------------------------------------------------
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb && role != "Check")
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && role == "Check")
	    {
	      RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
	    }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && role == "Check")
    {
      oChecks.Append(spInputGeom);
      RetCode = S_OK;
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RetCode);
}
//-----------------------------------------------------------------------------
// GetRelimitingElements
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfForFollowCurve::GetRelimitingElements (CATListValCATBaseUnknown_var & oFirstRelimitingElements,
      CATListValCATBaseUnknown_var & oSecondRelimitingElements)
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
  if (SUCCEEDED(RC))
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
    // identified by their role names are well defined. This right role
    // name is "FirstLimit" 
    //----------------------------------------------------------------------
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb && role != "FirstLimit")
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && role == "FirstLimit")
	    {
	      RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
	    }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && role == "FirstLimit")
    {
      oFirstRelimitingElements.Append(spInputGeom);
      RetCode = S_OK;
    }
    
    //----------------------------------------------------------------------
    // Scan all the Udf Inputs to find the right input 
    // identified by their role names are well defined. This right role
    // name is "SecondLimit" 
    //----------------------------------------------------------------------
    i =1;
    while (SUCCEEDED(RC) && i <= InputNb && role != "SecondLimit")
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && role == "SecondLimit")
	    {
	      RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
	    }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && role == "SecondLimit")
    {
      oFirstRelimitingElements.Append(spInputGeom);
      RetCode = S_OK;
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RetCode);
}
