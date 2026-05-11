// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CAAEMmrCombinedCurveEdit.cpp
// Provide implementation to interface
//    CATIEdit
//
//===================================================================

// Local FrameWork
#include "CAAEMmrCombinedCurveEdit.h"
#include "CAAMmrCombCrvPanelStCmd.h" // needed to return the Combined Curve edition command

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrCombinedCurve.h"     // needed to build the command from the Combined Curve to edit

//System Framework
#include "CATCommand.h"

CATImplementClass ( CAAEMmrCombinedCurveEdit ,
                    DataExtension           ,
                    CATIEdit          ,
                    CombinedCurve            );

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, CAAEMmrCombinedCurveEdit);

// 
// To declare that CombinedCurve implements CATIEdit , insert 
// the following line in the interface dictionary :
//
// CombinedCurve      CATIEdit    libCAAMmrCombinedCurveUI

//-----------------------------------------------------------------------------
// CAAEMmrCombinedCurveEdit : constructor
//-----------------------------------------------------------------------------
CAAEMmrCombinedCurveEdit::CAAEMmrCombinedCurveEdit()
{
}

//-----------------------------------------------------------------------------
// CAAEMmrCombinedCurveEdit : destructor
//-----------------------------------------------------------------------------
CAAEMmrCombinedCurveEdit::~CAAEMmrCombinedCurveEdit()
{
}




//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand * CAAEMmrCombinedCurveEdit::Activate (CATPathElement *ipPath)
{

    // gets a pointer on CAAIMmrCombinedCurve in edition
    CAAIMmrCombinedCurve *piCombinedCurve = NULL;
    HRESULT rc = QueryInterface ( IID_CAAIMmrCombinedCurve, (void**) &piCombinedCurve);
    if ( FAILED(rc) ) 
        return NULL;
    
    // creates the edition command
    CATCommand *pCommand =  new CAAMmrCombCrvPanelStCmd( piCombinedCurve );
    
    // releases useless pointer
    if ( NULL != piCombinedCurve )
    {
       piCombinedCurve->Release();
       piCombinedCurve = NULL ;
    }
    
    return pCommand;
}

