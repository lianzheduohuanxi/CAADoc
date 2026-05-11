// COPYRIGHT DASSAULT SYSTEMES 2012
//====================================================================================
//
//  CAAEV5V6ExtMmrCombinedCurveEdit
//    Implementation of interface CATIEdit for V5V6ExtCombinedCurve 
//
//====================================================================================

// Local CAAV5V6MechanicalModeler.edu framework 
#include "CAAEV5V6ExtMmrCombinedCurveEdit.h"
#include "CAAV5V6ExtMmrCombCrvPanelStCmd.h" // needed to return the Combined Curve edition command
#include "CAAIV5V6ExtMmrCombinedCurve.h"    // needed to build the command from the Combined Curve to edit

// System framework
#include "CATCommand.h"

CATImplementClass(CAAEV5V6ExtMmrCombinedCurveEdit, DataExtension, CATIEdit, V5V6ExtCombinedCurve);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, CAAEV5V6ExtMmrCombinedCurveEdit);

// 
// To declare that V5V6ExtCombinedCurve implements CATIEdit , insert 
// the following line in the interface dictionary :
//
// V5V6ExtCombinedCurve      CATIEdit    libCAAV5V6ExtMmrCombinedCurveUI

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurveEdit : constructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurveEdit::CAAEV5V6ExtMmrCombinedCurveEdit()
{}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrCombinedCurveEdit : destructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrCombinedCurveEdit::~CAAEV5V6ExtMmrCombinedCurveEdit()
{}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand * CAAEV5V6ExtMmrCombinedCurveEdit::Activate (CATPathElement *ipPath)
{
  // gets a pointer on CAAIV5V6ExtMmrCombinedCurve in edition
  CAAIV5V6ExtMmrCombinedCurve *piCombinedCurve = NULL;
  HRESULT rc = QueryInterface(IID_CAAIV5V6ExtMmrCombinedCurve, (void**) &piCombinedCurve);
  if ( FAILED(rc) ) 
    return NULL;
    
  // creates the edition command
  CATCommand *pCommand =  new CAAV5V6ExtMmrCombCrvPanelStCmd(piCombinedCurve);
    
  // releases useless pointer
  if (NULL != piCombinedCurve)
  {
    piCombinedCurve->Release();
    piCombinedCurve = NULL ;
  }
    
  return pCommand;
}

