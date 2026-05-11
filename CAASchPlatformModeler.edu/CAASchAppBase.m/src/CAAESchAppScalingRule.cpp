/**
 * @quickreview vso bcy 04:11:29
 */
// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CAAESchAppScalingRule
//
//=============================================================================
//
// This framework
#include "CAAESchAppScalingRule.h"

// ObjectSpecsModeler
#include "CATISpecObject.h"

// System
#include "CATErrorMacros.h"
#include "CATUnicodeString.h"

CATImplementClass (CAAESchAppScalingRule,DataExtension,CATBaseUnknown,CAASCHEDUPart);

#include "TIE_CATISchAppScalingRule.h"
TIEchain_CATISchAppScalingRule(CAAESchAppScalingRule);         


//  ===========================================================================
//  | Constructor
//  ===========================================================================
//
CAAESchAppScalingRule::CAAESchAppScalingRule()
{
}

//  ===========================================================================
//  | Destructor
//  ===========================================================================
//
CAAESchAppScalingRule::~CAAESchAppScalingRule()
{
}

//  ===========================================================================
//  |AppGetScalingPriority
//  |
//  |Through this method, the application specifies a priority number 
//  |to indicate the adjustment (moving)
//  |priority of this object during scaling.  
//  |The number ranges from 1 to 99.  The lower the number, 
//  |the higher the processing priority. 
//  |For example, an object with priority 1 is processed
//  |first and will not move while connected objects adjust. 
//  |
//  |This method will be called by the schematic platform when scaling a
//  |component that is connected to other objects in the network. These
//  |connected objects need to be adjust according to "accommodate" the
//  |increased size of the scaled component.
//  ===========================================================================
//
HRESULT CAAESchAppScalingRule::AppGetScalingPriority (int *oPriority)
{ 
  HRESULT RC = CATReturnFailure;
  CATISpecObject *piSpec = NULL;

  CATTry 
  {
    if ( SUCCEEDED(QueryInterface(IID_CATISpecObject,(void**)&piSpec)) && piSpec )
    {
       CATUnicodeString uName = piSpec->GetName();

       // equipments
       if ( piSpec->IsSubTypeOf("CAASCHEDU_CompressFunction") ||
            piSpec->IsSubTypeOf("CAASCHEDU_PumpFunction") || 
            piSpec->IsSubTypeOf("CAASCHEDU_VesselFunction") )
          *oPriority = 1;
       // piping parts
       else if ( piSpec->IsSubTypeOf("CAASCHEDU_BlockValveFunction") ||
                 piSpec->IsSubTypeOf("CAASCHEDU_CheckValveFunction") ||
                 piSpec->IsSubTypeOf("CAASCHEDU_ControlValveFunction") ||
                 piSpec->IsSubTypeOf("CAASCHEDU_ReducerFunction") )
          *oPriority = 2;
       // equipment parts
       else if ( piSpec->IsSubTypeOf("CAASCHEDU_NozzleFunction") ) 
          *oPriority = 3;
       // catch all
       else
          *oPriority = 99;
       RC = CATReturnSuccess;
    }
  }

  CATCatch (CATError,pError)
  {
     if (pError) Flush (pError);
     RC = CATReturnFailure;
  }
  CATEndTry;
  if (piSpec){piSpec->Release(); piSpec=NULL;}
  return RC;
}
