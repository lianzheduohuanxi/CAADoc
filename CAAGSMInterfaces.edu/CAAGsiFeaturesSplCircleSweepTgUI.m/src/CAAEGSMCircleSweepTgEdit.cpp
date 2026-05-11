// COPYRIGHT DASSAULT SYSTEMES 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMCircleSweepTgEdit.cpp
// Provide implementation to interface
//    CATIEdit
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// Local FrameWork
// MINC 
#include "CATCommand.h"

#include "CAAEGSMCircleSweepTgEdit.h"
#include "CAAGSMCircleSweepTgCmd.h" // needed to return the Sew Skin edition command


#include "CATPathElement.h"
// CAAMechanicalModeler.edu Framework
#include "CAAIGSMCircleSweepTg.h"     // needed to build the command from the Sew Skin to edit



CATImplementClass ( CAAEGSMCircleSweepTgEdit ,
                    DataExtension                ,
                    CATBaseUnknown          ,
                    CAACircleSweepTg            );

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgEdit : constructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgEdit::CAAEGSMCircleSweepTgEdit()
{
}

//-----------------------------------------------------------------------------
// CAAEGSMCircleSweepTgEdit : destructor
//-----------------------------------------------------------------------------
CAAEGSMCircleSweepTgEdit::~CAAEGSMCircleSweepTgEdit()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIEdit.h" // needed to tie the implementation to its interface
TIE_CATIEdit( CAAEGSMCircleSweepTgEdit);

// 
// To declare that CircleSweepTg implements CATIEdit , insert 
// the following line in the interface dictionary :
//
// CAACircleSweepTg      CATIEdit    libCAAGsiFeaturesSplCircleSweepTgUI

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand * CAAEGSMCircleSweepTgEdit::Activate (CATPathElement *ipPath)
{

    HRESULT rc = E_FAIL ; 
    CATCommand * comm = NULL;
    CATBaseUnknown_var EditedCircleSweepTg ;
   
	// Retrieves the Edited Spec
	if(ipPath ) EditedCircleSweepTg = ipPath ->SearchObject(CAAIGSMCircleSweepTg::ClassName());
    CAAIGSMCircleSweepTg_var trial = EditedCircleSweepTg ;
	if ( EditedCircleSweepTg != NULL_var) {
        CAAIGSMCircleSweepTg *piCircleSweepTg = NULL;
        HRESULT rc = EditedCircleSweepTg -> QueryInterface ( IID_CAAIGSMCircleSweepTg, (void**) &piCircleSweepTg);
        if (piCircleSweepTg){ 
            // Creates the edition command
            CATCommand *pCommand =  new CAAGSMCircleSweepTgCmd( piCircleSweepTg );
            piCircleSweepTg->Release() ; piCircleSweepTg= NULL;
        }
		        
        EditedCircleSweepTg  -> Release();
    }
  return comm ;
}

