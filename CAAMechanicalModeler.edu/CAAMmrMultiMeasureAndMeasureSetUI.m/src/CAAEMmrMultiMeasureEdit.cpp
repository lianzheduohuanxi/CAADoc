// COPYRIGHT DASSAULT SYSTEMES 2007
//===================================================================
//
// CAAEMmrMultiMeasureEdit.cpp
// Provide implementation to interface
//    CATIEdit
//
//===================================================================

// Local FrameWork
#include "CAAEMmrMultiMeasureEdit.h"
#include "CAAMmrMultiMeasureStCmd.h" // needed to return the MmrMultiMeasure Edition command

// CAAMechanicalModeler.edu Framework
#include "CAAIMmrMultiMeasure.h"     // needed to build the command from the MmrMultiMeasure to edit

// Include System Fw
#include "CATCommand.h"

CATImplementClass ( CAAEMmrMultiMeasureEdit ,
                    DataExtension ,
                    CATIEdit ,
                    CAAMmrMultiMeasure);

// Tie the implementation to its interface by BOA
// ----------------------------------------------
CATImplementBOA(CATIEdit, CAAEMmrMultiMeasureEdit);

// 
// To declare that MultiMeasure implements CATIEdit , insert 
// the following line in the interface dictionary :
//
// CAAMmrMultiMeasure      CATIEdit    libCAAMmrMultiMeasureAndMeasureSetUI

//-----------------------------------------------------------------------------
// CAAEMmrMultiMeasureEdit : constructor
//-----------------------------------------------------------------------------
CAAEMmrMultiMeasureEdit::CAAEMmrMultiMeasureEdit()
{
}

//-----------------------------------------------------------------------------
// CAAEMmrMultiMeasureEdit : destructor
//-----------------------------------------------------------------------------
CAAEMmrMultiMeasureEdit::~CAAEMmrMultiMeasureEdit()
{
}

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand * CAAEMmrMultiMeasureEdit::Activate (CATPathElement *ipPath)
{
    // gets a pointer on CAAIMmrMultiMeasure in edition
    CAAIMmrMultiMeasure *piMultiMeasure = NULL;
    HRESULT rc = QueryInterface ( IID_CAAIMmrMultiMeasure, (void**) &piMultiMeasure);
    if ( FAILED(rc) ) 
        return NULL;
    
    // creates the edition command
    CATCommand *pCommand =  new CAAMmrMultiMeasureStCmd( piMultiMeasure );
    
    // releases useless pointer
    if ( NULL != piMultiMeasure )
    {
       piMultiMeasure->Release();
       piMultiMeasure = NULL ;
    }
    
    return pCommand;
}

