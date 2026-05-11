/**
 * @fullreview CVR DCN 03:01:22
 */
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAPmiUdfFor2DContouring: implementation of the 
// CATIMfgMappingForProfileContouring CAA interface for a type of User Defined Features
//
// ===================================================================
// DCN V5R8 10/09/01 Creation 
// DCN V5R11 01/2003 Update to support CAA Use case for geometrical macro motions mapping 
// ===================================================================
//
#include "CAAPmiUdfFor2DContouring.h"
#include "CAAPmiUdfEnv.h"
#include "CAAPmiUdfUtilities.h"

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
#include "CATIPocket.h"
#include "CATIPad.h"
#include "CATINewHole.h"

#include "CATPlane.h"

#include "CATISketch.h"

#include "CATMathPlane.h"
#include "CATMathVector.h"


#include "TIE_CATIMfgMappingForProfileContouring.h"
TIEchain_CATIMfgMappingForProfileContouring(CAAPmiUdfFor2DContouring);

CATImplementClass (CAAPmiUdfFor2DContouring,CodeExtension,CATBaseUnknown,UdfFeature);

//-----------------------------------------------------------------------------
// Prototype for machining of User Defined Features as a Mfg Contour
//-----------------------------------------------------------------------------

extern "C" 
{
  ExportedByCAAPmiUdfEnv int CAAPmiUdfIsMachinableAsAMfgContour (CATExtendable *, const GUID &);
}
//-----------------------------------------------------------------------------
// CATMfgUdfIsMachinableAsAMfgContour: entry to the User Defined Features machined as a
// Mfg Contouring validation
//-----------------------------------------------------------------------------

int CAAPmiUdfIsMachinableAsAMfgContour (CATExtendable *Udf, const GUID &)
{
  int  oRetCode = 0; 
  if (NULL == Udf) return oRetCode;

  //--------------------------------------------------------------------------
  // Apply a filter to validate the implementation of the CAA interface
  //--------------------------------------------------------------------------
  CATBaseUnknown  *piUdf = NULL;
  HRESULT RC = Udf->QueryInterface(IID_CATBaseUnknown,(void **)&piUdf);

  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC) && NULL != piUdf)
  {  
    CATUnicodeString GeometryName = "Drive";
    CATBaseUnknown_var spGeom;
    RC = CAAPmiUdfUtilities::GetUdfGeometry (piUdf, GeometryName, spGeom);

    if (NULL_var == spGeom)
    {
      GeometryName = "Lower_Drive";
      RC = CAAPmiUdfUtilities::GetUdfGeometry (piUdf, GeometryName, spGeom);
    }
    
    if (NULL_var != spGeom) oRetCode = 1;
  }
  if (NULL != piUdf) piUdf->Release();
  piUdf = NULL;

  return (oRetCode);
}

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAPmiUdfFor2DContouring::CAAPmiUdfFor2DContouring()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAPmiUdfFor2DContouring::~CAAPmiUdfFor2DContouring()
{
}

//-----------------------------------------------------------------------------
// GetPart
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfFor2DContouring::GetPart (CATBaseUnknown_var & oPart)
{
  HRESULT RetCode = E_FAIL;
  oPart = NULL_var;

  //----------------------------------------------------------------------
  // Read the mapping rule name associated to the operation 
  //----------------------------------------------------------------------
  CATUnicodeString MappingRuleName = "";
  CATIMfgMappingRuleName  *piMappRuleName = NULL;
  RetCode = this->QueryInterface(IID_CATIMfgMappingRuleName,(void **)&piMappRuleName);
  if (SUCCEEDED(RetCode) && NULL != piMappRuleName) 
  {
    MappingRuleName = piMappRuleName->GetMappingRuleName();
    piMappRuleName->Release();
    piMappRuleName = NULL;
  }
 
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
    CATUnicodeString GeometryName;
    CATBaseUnknown_var spInputGeom(NULL_var);

    CATBaseUnknown  *piUdf = NULL;
    RetCode = this->QueryInterface(IID_CATBaseUnknown,(void **)&piUdf);
    
    //----------------------------------------------------------------------
    // Get the right geometry according to the mapping rule name
    //----------------------------------------------------------------------
    if (MappingRuleName == "AxialUdfWithMacroMap")
    {
      GeometryName = "Lower_Plane";
      if (SUCCEEDED(RetCode) && NULL != piUdf) 
      {
        RetCode = CAAPmiUdfUtilities::GetUdfGeometry (piUdf, GeometryName, spInputGeom);
      }
    }
    else 
    {
      int InputNb = 0;
      RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
      
      CATUnicodeString role = "";
      int i = 1;
      while (SUCCEEDED(RC) && i <= InputNb && (role != "Drive" && role != "Lower_Drive"))
      {
        RC = piUdfFeatureInstance->GetInputRole(i, role);
        if (role == "Drive" || role == "Lower_Drive")
        {
          RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
        }
        i++;
      }
    }
    if (NULL != piUdf) 
    {
      piUdf->Release();
      piUdf = NULL;
    }
    //----------------------------------------------------------------------
    // The right geometry is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && NULL_var != spInputGeom)
    {
      //----------------------------------------------------------------------
      // This geometry is a sketch from which the support plane is extracted
      //----------------------------------------------------------------------
      CATISketch_var Sketch(spInputGeom);
      CATISpecObject_var oPlane;

      if (NULL_var != Sketch) 
        RC = Sketch->GetPlanarSupport(oPlane);
      else
        oPlane = spInputGeom;
      oPart = oPlane;
      CATPlane_var Plane = oPlane;
      if (NULL_var != Plane)
      {
        CATMathPoint ioOrigin;
        CATMathVector ioNormal;
        Plane->GetNormal(ioOrigin ,ioNormal);
        double oZ = ioOrigin.GetZ();
      }

      RetCode = RC;
    }
    else
      RetCode = E_FAIL;
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
  piUdfFeatureInstance = NULL;

return (RetCode);
}

//-----------------------------------------------------------------------------
// GetRelimitingPlane
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfFor2DContouring::GetRelimitingPlane (CATBaseUnknown_var & oRelimitingPlane)
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
    // Read the mapping rule name associated to the operation 
    //----------------------------------------------------------------------
    CATUnicodeString MappingRuleName = "";
    CATIMfgMappingRuleName  *piMappRuleName = NULL;
    RetCode = this->QueryInterface(IID_CATIMfgMappingRuleName,(void **)&piMappRuleName);
    if (SUCCEEDED(RetCode) && NULL != piMappRuleName) 
    {
      MappingRuleName = piMappRuleName->GetMappingRuleName();
      piMappRuleName->Release();
      piMappRuleName = NULL;
    }
    //----------------------------------------------------------------------
    // Get the right geometry according to the mapping rule name
    //----------------------------------------------------------------------
    if (MappingRuleName == "AxialUdfWithMacroMap")
    {
      if (SUCCEEDED(RetCode))
      {
        CATBaseUnknown  *piUdf = NULL;
        RC = this->QueryInterface(IID_CATBaseUnknown,(void **)&piUdf);
        if (SUCCEEDED(RC) && NULL != piUdf) 
        {
          CATUnicodeString GeometryName = "Upper_Plane";
          RC = CAAPmiUdfUtilities::GetUdfGeometry (piUdf, GeometryName, spInputGeom);
          piUdf->Release();
          piUdf = NULL;
        }
      }
    }
    else
    {
      int InputNb = 0;
      RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
      
      int i = 1;
      while (SUCCEEDED(RC) && i <= InputNb && (role != "Drive" && role != "Lower_Drive"))
      {
        RC = piUdfFeatureInstance->GetInputRole(i, role);
        if (role == "Drive" || role == "Lower_Drive")
        {
          RC = piUdfFeatureInstance->GetInput(i,spInputGeom);
        }
        i++;
      }
    }
    //----------------------------------------------------------------------
    // The right geometry is found
    //----------------------------------------------------------------------
    if (SUCCEEDED(RC) && NULL_var != spInputGeom)
    {
      CATISketch_var Sketch(spInputGeom);
      CATISpecObject_var oPlane;

      //----------------------------------------------------------------------
      // This geometry is a sketch from which the support plane is extracted
      //----------------------------------------------------------------------
      if (NULL_var != Sketch) 
        RC = Sketch->GetPlanarSupport(oPlane);
      //----------------------------------------------------------------------
      // Other case: the found geometry is the plane
      //----------------------------------------------------------------------
      else
        oPlane = spInputGeom;
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
    else
      RetCode = S_FALSE;
  }
 
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
  piUdfFeatureInstance = NULL;

  return (RetCode);
}

//-----------------------------------------------------------------------------
// GetGuidingCurves
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfFor2DContouring::GetGuidingCurves (CATListValCATBaseUnknown_var & oGuidingCurves,
                                                    int & oSide, CATPoint * oExtremity)
{
  HRESULT RetCode = E_FAIL;
  oSide = 0;
  oExtremity = NULL;
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
    CATBaseUnknown_var spGeom(NULL_var);
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
    
    //----------------------------------------------------------------------
    // Read the mapping rule name associated to the Profile Contouring operation 
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

    CATBaseUnknown  *piUdf = NULL;
    RetCode = this->QueryInterface(IID_CATBaseUnknown,(void **)&piUdf);
    CATUnicodeString GeometryName;
    
    //----------------------------------------------------------------------
    // Get the right geometrical dat according to the mapping rule name 
    //----------------------------------------------------------------------
    int i =1;
    if (MappingRuleName == "")
    {
      GeometryName = "Drive";
    }
    else if (MappingRuleName == "Mapping_On_Lower_Drive")
    {
      GeometryName = "Lower_Drive";
    }
    else if (MappingRuleName == "Mapping_On_Upper_Drive")
    {
      GeometryName = "Upper_Drive";
    }
    else if (MappingRuleName == "AxialUdfWithMacroMap")
    {
      GeometryName = "Drive";
    }
    if (NULL != piUdf) 
    {
      RetCode = CAAPmiUdfUtilities::GetUdfGeometry (piUdf, GeometryName, spGeom);
      piUdf->Release();
      piUdf = NULL;

      //----------------------------------------------------------------------
      // The right geometry is found
      //----------------------------------------------------------------------
      if (SUCCEEDED(RetCode) && (NULL_var != spGeom))
      {
        oGuidingCurves.Append(spGeom);
        RetCode = S_OK;
      }
    }
    //----------------------------------------------------------------------
    // The side is defined from the first Udf Output returned 
    // through the CATIUdfFeatureUser interface
    // In this case, this is a pad or a pocket
    //----------------------------------------------------------------------
    CATListValCATBaseUnknown_var * oOutputs = NULL;
    CATBaseUnknown_var OutputGeom;
    CATIUdfFeatureUser *piUdfFeatureUser = NULL;
    
    //--------------------------------------------------------------------------
    // Your object is a CATIUdfFeatureUser: we can use the associated methods
    //--------------------------------------------------------------------------
    RC = this->QueryInterface(IID_CATIUdfFeatureUser,(void **)&piUdfFeatureUser);
    if (SUCCEEDED(RC) && NULL != piUdfFeatureUser)
    {  
      piUdfFeatureUser->GetOutputs (oOutputs);
      int OutputNb = 0;
      if (NULL != oOutputs) OutputNb = oOutputs->Size();
      
      //----------------------------------------------------------------------
      // At least, one output is available
      //----------------------------------------------------------------------
      if (0 < OutputNb)
      {
        OutputGeom = (*oOutputs)[1];
        
        //----------------------------------------------------------------------
        // is it a Pad ?
        //----------------------------------------------------------------------
        CATIPad_var Pad = OutputGeom;
        if (NULL_var != Pad)
        {
          oSide = 1;
          RetCode = S_OK;
        }
        else
        {
          //----------------------------------------------------------------------
          // is it a Pocket ?
          //----------------------------------------------------------------------
          CATIPocket_var Pocket = OutputGeom;
          if (NULL_var != Pocket)
          {
            oSide = 0;
            RetCode = S_OK;
          }
          else
          {
            //----------------------------------------------------------------------
            // is it a Hole ?
            //----------------------------------------------------------------------
            CATINewHole_var Hole = OutputGeom;
            if (NULL_var != Hole)
            {
              oSide = 1;
              RetCode = S_OK;
            }
          }
        }
      }
      if (NULL != oOutputs) delete oOutputs;
    }
    if (NULL != piUdfFeatureUser) piUdfFeatureUser->Release();
    piUdfFeatureUser = NULL;

  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
  piUdfFeatureInstance = NULL;

  return (RetCode);
}
//-----------------------------------------------------------------------------
// GetChecks
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfFor2DContouring::GetChecks (CATListValCATBaseUnknown_var & oChecks)
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
  piUdfFeatureInstance = NULL;

  return (RetCode);
}
//-----------------------------------------------------------------------------
// GetRelimitingElements
//-----------------------------------------------------------------------------

HRESULT CAAPmiUdfFor2DContouring::GetRelimitingElements (CATListValCATBaseUnknown_var & oFirstRelimitingElements,
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
    else if (FAILED(RC))
      RetCode = RC;
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
  piUdfFeatureInstance = NULL;

  return (RetCode);
}
