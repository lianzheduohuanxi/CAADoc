/**
 * @fullreview CVR DCN 03:01:22
 */
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
// ===================================================================
//
// CAAMaiUdfForGeomMacroMotions: implementation of the 
// CATIMfgMacroMotionsGeomMapping CAA interface for a type of User Defined Features
//
// ===================================================================
// DCN V5R11 2003/01/21 Creation 
// ===================================================================
//
#include "CAAMaiUdfForGeomMacroMotions.h"
#include "CAAMaiUdfEnv.h"
#include "CAAMaiUdfUtilities.h"

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


#include "TIE_CATIMfgMacroMotionsGeomMapping.h"
TIEchain_CATIMfgMacroMotionsGeomMapping(CAAMaiUdfForGeomMacroMotions);

CATImplementClass (CAAMaiUdfForGeomMacroMotions,CodeExtension,CATBaseUnknown,UdfFeature);


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAMaiUdfForGeomMacroMotions::CAAMaiUdfForGeomMacroMotions()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAMaiUdfForGeomMacroMotions::~CAAMaiUdfForGeomMacroMotions()
{
}

//-----------------------------------------------------------------------------
// MapGeomOnApproachMacroMotion
//-----------------------------------------------------------------------------

HRESULT CAAMaiUdfForGeomMacroMotions::MapGeomOnApproachMacroMotion (CATUnicodeString iActivityType, int iMacroMotionType,
      CATListOfInt iElementaryMotionTypeList, CATListValCATBaseUnknown_var &oGeometryList)
{
  HRESULT RetCode = MapGeomOnRetractMacroMotion (iActivityType,iMacroMotionType, iElementaryMotionTypeList, oGeometryList);
 
  return (RetCode);
}

//-----------------------------------------------------------------------------
// MapGeomOnRetractMacroMotion
//-----------------------------------------------------------------------------

HRESULT CAAMaiUdfForGeomMacroMotions::MapGeomOnRetractMacroMotion (CATUnicodeString iActivityType, int iMacroMotionType,
      CATListOfInt iElementaryMotionTypeList, CATListValCATBaseUnknown_var &oGeometryList)
{
  HRESULT RetCode = S_FALSE;
  
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
  // Number of macro motions to be solved
  //--------------------------------------------------------------------------
  int NbOfMotions = iElementaryMotionTypeList.Size();

  for (int numMotion = 1; numMotion <= NbOfMotions && SUCCEEDED(RetCode); numMotion++)
  {
    //--------------------------------------------------------------------------
    // Go to a plane motion
    //--------------------------------------------------------------------------
    if (6 == iElementaryMotionTypeList[numMotion])
    {
      CATUnicodeString GeometryName;
      if (1 == iMacroMotionType || 2 == iMacroMotionType)
      {
        if (MappingRuleName == "AxialUdfWithMacroMap")
        {
          if (iActivityType == "ProfileContouring")
          {
            if (1 == numMotion)
              GeometryName = "Lower_Plane";
            else
              GeometryName = "Security_Plane";
          }
          else
            GeometryName = "Security_Plane";
        }
        else 
          GeometryName = "SecurityPlane";
      }
      else
      {
        if (MappingRuleName == "AxialUdfWithMacroMap")
          GeometryName = "Lower_Plane";
        else 
        {
          GeometryName = "Drive";
          if (MappingRuleName == "Upper_Drive_Rule")
            GeometryName = "Upper_Drive";
          else if (MappingRuleName == "Lower_Drive_Rule")
            GeometryName = "Lower_Drive";
        }
      }
      CATBaseUnknown_var Geometry;
      if (SUCCEEDED(RetCode))
      {
        CATBaseUnknown  *piUdf = NULL;
        RetCode = this->QueryInterface(IID_CATBaseUnknown,(void **)&piUdf);
        if (SUCCEEDED(RetCode) && NULL != piUdf) 
        {
          RetCode = CAAMaiUdfUtilities::GetUdfGeometry (piUdf, GeometryName, Geometry);
          piUdf->Release();
          piUdf = NULL;
        }
      }

      if (SUCCEEDED(RetCode))
      {
        CATISketch_var Sketch(Geometry);
        if (NULL_var != Sketch) 
        {
          CATISpecObject_var oPlane;
          
          RetCode = Sketch->GetPlanarSupport(oPlane);
          if (SUCCEEDED(RetCode))
          {
            CATBaseUnknown_var MacroPlane(oPlane);
            oGeometryList.Append(MacroPlane);
          }
          else 
            RetCode = E_FAIL;
        }
        else
          oGeometryList.Append(Geometry);
      }
    }
    //--------------------------------------------------------------------------
    // Go to a point motion
    //--------------------------------------------------------------------------
    else if (7 == iElementaryMotionTypeList[numMotion])
    {
      CATUnicodeString GeometryName;
      if (iActivityType == "Drilling") 
        GeometryName = "Drilling_Point";
      else if (iActivityType == "ProfileContouring" && MappingRuleName == "AxialUdfWithMacroMap")
        GeometryName = "Drilling_Point";
      else
        GeometryName = "HomePoint";

      CATBaseUnknown_var Geometry;
      if (SUCCEEDED(RetCode))
      {
        CATBaseUnknown  *piUdf = NULL;
        RetCode = this->QueryInterface(IID_CATBaseUnknown,(void **)&piUdf);
        if (SUCCEEDED(RetCode) && NULL != piUdf) 
        {
          RetCode = CAAMaiUdfUtilities::GetUdfGeometry (piUdf, GeometryName, Geometry);
          piUdf->Release();
          piUdf = NULL;
        }
      }
      if (SUCCEEDED(RetCode))
        oGeometryList.Append(Geometry);
    }
    //--------------------------------------------------------------------------
    // Other case not supported
    //--------------------------------------------------------------------------
    else
      RetCode = E_FAIL;
  }
 
  return (RetCode);
}

