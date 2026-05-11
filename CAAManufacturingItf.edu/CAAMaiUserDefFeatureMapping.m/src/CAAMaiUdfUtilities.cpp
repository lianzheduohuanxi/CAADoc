/**
 * @fullreview CVR DCN 03:01:23
 */
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2003
//-----------------------------------------------------------------------------
// class CAAMaiUdfUtilities
// 
//-----------------------------------------------------------------------------
// Usage Notes:
// This class is dedicated to Udf methods 
//-----------------------------------------------------------------------------
// 2003/01/21 V5R11 Creation                                                DCN
//-----------------------------------------------------------------------------

#include "CAAMaiUdfEnv.h"

// User Defined Features Interface
#include "CATIUdfFeatureInstance.h"
#include "CATIUdfFeatureUser.h"

#include "CATLISTV_CATBaseUnknown.h"

#include "CATUnicodeString.h"


#include "CAAMaiUdfUtilities.h"

// ----------------------------------------------------------
// CAAMaiUdfUtilities : CONSTRUCTOR DESTRUCTOR
//-----------------------------------------------------------

CAAMaiUdfUtilities::CAAMaiUdfUtilities ()
{
}

CAAMaiUdfUtilities::~CAAMaiUdfUtilities ()
{
}

//-----------------------------------------------------------------------------
// GetUdfGeometry: Generic method to get a User Feature geometry from its role name
//-----------------------------------------------------------------------------

HRESULT CAAMaiUdfUtilities::GetUdfGeometry (CATBaseUnknown* iUdf, CATUnicodeString iGeometryName, CATBaseUnknown_var &oGeometry)
{
  oGeometry = NULL_var;
  HRESULT RC = E_FAIL;

  if (NULL == iUdf) return RC;
  //--------------------------------------------------------------------------
  // Get your object as a CATIUdfFeatureInstance
  //--------------------------------------------------------------------------
  CATIUdfFeatureInstance *piUdfFeatureInstance = NULL;
  RC = iUdf->QueryInterface(IID_CATIUdfFeatureInstance,(void **)&piUdfFeatureInstance);
  //--------------------------------------------------------------------------
  // Your object is a CATIUdfFeatureInstance: we can use the associated methods
  //--------------------------------------------------------------------------
  if (SUCCEEDED(RC) && NULL != piUdfFeatureInstance)
  {  
    CATUnicodeString role = "";
    CATBaseUnknown_var spGeom;
    
    //----------------------------------------------------------------------
    // Read the Inputs number: this is the geometrical inputs of your Udf
    //                         defined when creating the Udf template
    //----------------------------------------------------------------------
    int InputNb = 0;
    RC = piUdfFeatureInstance->GetInputsNumber(InputNb);

    int i = 1;
    while (SUCCEEDED(RC) && i <= InputNb && role != iGeometryName)
    {
      RC = piUdfFeatureInstance->GetInputRole(i, role);
      //----------------------------------------------------------------------
      // The right Input is found
      //----------------------------------------------------------------------
      if (role == iGeometryName)
      {
        RC = piUdfFeatureInstance->GetInput(i,spGeom);
      }
      i++;
    }
    //----------------------------------------------------------------------
    // The right Input was not found
    //----------------------------------------------------------------------
    if (FAILED(RC) || role != iGeometryName)
    {
      //----------------------------------------------------------------------
      // Annalyse the Outputs : this is the geometrical outputs of your Udf
      //                         added in the Outputs List when creating the Udf template
      //----------------------------------------------------------------------
      CATListValCATBaseUnknown_var * oOutputs = NULL;
      CATIUdfFeatureUser *piUdfFeatureUser = NULL;
      
      RC = iUdf->QueryInterface(IID_CATIUdfFeatureUser,(void **)&piUdfFeatureUser);
      if (SUCCEEDED(RC) && NULL != piUdfFeatureUser)
      { 
        //----------------------------------------------------------------------
        // Read the Outputs list
        //----------------------------------------------------------------------
        piUdfFeatureUser->GetOutputs (oOutputs);
        int OutputNb = 0;
        if (NULL != oOutputs) OutputNb = oOutputs->Size();
        
        //----------------------------------------------------------------------
        // At least, one output is available
        //----------------------------------------------------------------------
        if (0 < OutputNb)
        {
          for (int i = 1; i <= OutputNb && role != iGeometryName; i++)
          {
            RC = piUdfFeatureUser->GetOutputRole (i, role);
            //----------------------------------------------------------------------
            // The right Output is found
            //----------------------------------------------------------------------
            if (role == iGeometryName)
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

    oGeometry = spGeom;
  }

  if (NULL_var != oGeometry)
    RC = S_OK;
  else
    RC = E_FAIL;

  if (NULL != piUdfFeatureInstance) piUdfFeatureInstance->Release();
  piUdfFeatureInstance = NULL;

  return (RC);
}
