/**
 * @quickreview DCN 03:06:16
 */
/**
 * @fullreview PMT DCN 02:12:06
 */
// ===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAMaiUdfForMachiningAxis: implementation of the 
// CATIMfgMappingForMachiningAxis CAA interface for a type of User Defined Features
//
// ===================================================================
// DCN V5R11 04/12/02 Creation 
// DCN V5R12 13/06/03 ENhancement of use case for User Features Outputs
// ===================================================================
//
#include "CAAMaiUdfForMachiningAxis.h"

#include "CATIMfgMappingRuleName.h"


// User Defined Features Interface
#include "CATIUdfFeatureInstance.h"
#include "CATIUdfFeatureUser.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"


#include "TIE_CATIMfgMappingForMachiningAxis.h"
TIEchain_CATIMfgMappingForMachiningAxis(CAAMaiUdfForMachiningAxis);

CATImplementClass (CAAMaiUdfForMachiningAxis,CodeExtension,CATBaseUnknown,UdfFeature);


//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAMaiUdfForMachiningAxis::CAAMaiUdfForMachiningAxis()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAMaiUdfForMachiningAxis::~CAAMaiUdfForMachiningAxis()
{
}


//-----------------------------------------------------------------------------
// GetGuidingCurves
//-----------------------------------------------------------------------------

HRESULT CAAMaiUdfForMachiningAxis::GetAxisSystem (CATBaseUnknown_var & oAxisSystem)
{
  HRESULT RetCode = E_FAIL;

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
  if (SUCCEEDED(RC))
  { 
    //
    CATUnicodeString role = "";
    CATBaseUnknown_var spGeom;
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);
    
    //----------------------------------------------------------------------
    // Scan all the Udf Inputs to find the right data 
    // identified by their role names are well defined. This right role
    // name is "Axis_System"
    //----------------------------------------------------------------------
    int i =1;
    while (SUCCEEDED(RC) && i <= InputNb && NULL_var == spGeom)
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      if (SUCCEEDED(RC) && 
        ((MappingRuleName != "AxialUdfWithAxisMap" && role == "Axis_System") ||
         (MappingRuleName == "AxialUdfWithAxisMap" && role == "LocalAxis"  )   ) )
      {
        RC = piUdfFeatureInstance->GetInput(i,spGeom);
      }
      i++;
    }
    //----------------------------------------------------------------------
    // Scan all the Udf Outputs to find the right data 
    // identified by their role names are well defined. This right role
    // name is "Axis_System"
    //----------------------------------------------------------------------
    if (NULL_var == spGeom)
    {
      // ---> Rechercher parmi les Outputs de l'Udf
      CATListValCATBaseUnknown_var * oOutputs = NULL;
      CATIUdfFeatureUser *piUdfFeatureUser = NULL;
      
      RC = this->QueryInterface(IID_CATIUdfFeatureUser,(void **)&piUdfFeatureUser);
      if (SUCCEEDED(RC) && NULL != piUdfFeatureUser)
      { 
        // ---> Extraction de la liste des Outputs
        piUdfFeatureUser->GetOutputs (oOutputs);
        int OutputNb = 0;
        if (NULL != oOutputs) OutputNb = oOutputs->Size();
        
        //----------------------------------------------------------------------
        // At least, one output is available
        //----------------------------------------------------------------------
        if (0 < OutputNb)
        {
          for (int i = 1; i <= OutputNb && NULL_var == spGeom; i++)
          {
            RC = piUdfFeatureUser->GetOutputRole (i, role);
            
            // ---> Reference trouvee parmi les Ouputs
            if (SUCCEEDED(RC) && 
              ((MappingRuleName != "AxialUdfWithAxisMap" && role == "Axis_System") ||
              (MappingRuleName == "AxialUdfWithAxisMap" && role == "LocalAxis"  )   ) )
            {
              spGeom = (*oOutputs)[i];
            }
          } 
        }
        if (NULL != oOutputs) delete oOutputs;
      }
      if (NULL != piUdfFeatureUser) piUdfFeatureUser->Release();
      piUdfFeatureUser = NULL;
    }
    //----------------------------------------------------------------------
    // The right data (Input or Output) is found
    //----------------------------------------------------------------------
    if (NULL_var != spGeom)
    {
      oAxisSystem = spGeom;
      RetCode = S_OK;
    }
  }
  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();

  return (RetCode);
}
