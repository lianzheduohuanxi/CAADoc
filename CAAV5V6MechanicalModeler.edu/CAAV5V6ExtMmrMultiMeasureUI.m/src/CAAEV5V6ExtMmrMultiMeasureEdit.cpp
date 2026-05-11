// COPYRIGHT DASSAULT SYSTEMES 2012
//===================================================================
//
// CAAEV5V6ExtMmrMultiMeasureEdit.cpp
// Provide implementation to interface
//    CATIEdit
//
// Note : CAAEV5V6ExtMmrMultiMeasureEdit is the same use case as CAAEMmrMultiMeasureEdit. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//===================================================================

// Local  CAAV5V6MechanicalModeler.edu FrameWork
#include "CAAEV5V6ExtMmrMultiMeasureEdit.h"
#include "CAAV5V6ExtMmrMultiMeasureStCmd.h" // needed to return the CAAV5V6MmrMultiMeasure Edition command
#include "CAAIV5V6ExtMmrMultiMeasure.h"     // needed to build the command from the CAAV5V6ExtMmrMultiMeasure to edit

// System Framework
#include "CATCommand.h"

CATImplementClass(CAAEV5V6ExtMmrMultiMeasureEdit, DataExtension, CATIEdit, CAAV5V6ExtMmrMultiMeasure);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, CAAEV5V6ExtMmrMultiMeasureEdit);

// 
// To declare that CAAV5V6ExtMmrMultiMeasure implements CATIEdit , insert 
// the following line in the interface dictionary :
//
// CAAV5V6ExtMmrMultiMeasure   CATIEdit    libCAAV5V6ExtMmrMultiMeasureUI

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasureEdit : constructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasureEdit::CAAEV5V6ExtMmrMultiMeasureEdit()
{
}

//-----------------------------------------------------------------------------
// CAAEV5V6ExtMmrMultiMeasureEdit : destructor
//-----------------------------------------------------------------------------
CAAEV5V6ExtMmrMultiMeasureEdit::~CAAEV5V6ExtMmrMultiMeasureEdit()
{
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand * CAAEV5V6ExtMmrMultiMeasureEdit::Activate(CATPathElement *ipPath)
{
  // gets a pointer on CAAIMmrMultiMeasure in edition
  CAAIV5V6ExtMmrMultiMeasure *piMultiMeasure = NULL;
  HRESULT rc = QueryInterface(IID_CAAIV5V6ExtMmrMultiMeasure, (void**) &piMultiMeasure);
  if (FAILED(rc)) 
    return NULL;
    
  // creates the edition command
  CATCommand *pCommand =  new CAAV5V6ExtMmrMultiMeasureStCmd(piMultiMeasure);
    
  // releases useless pointer
  if (NULL != piMultiMeasure)
  {
    piMultiMeasure->Release();
    piMultiMeasure = NULL;
  }
    
  return pCommand;
}

