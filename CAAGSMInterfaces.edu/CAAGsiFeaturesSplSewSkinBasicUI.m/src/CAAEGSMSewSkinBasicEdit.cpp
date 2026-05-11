// COPYRIGHT DASSAULT SYSTEMES 2006
//===================================================================
// CATIA ShapeDesign And Styling  
// ------------------------------------------------------------------
//
// CAAEGSMSewSkinBasicEdit.cpp
// Provide implementation to interface
//    CATIEdit
//
//===================================================================
//June 2006 : Creation CAA Sample 
//===================================================================

// Local FrameWork
// MINC 
#include "CATCommand.h"

#include "CAAEGSMSewSkinBasicEdit.h"
#include "CAAGSMSewSkinBasicCmd.h" // needed to return the Sew Skin edition command


#include "CATPathElement.h"
// CAAMechanicalModeler.edu Framework
#include "CAAIGSMSewSkinBasic.h"     // needed to build the command from the Sew Skin to edit

CATImplementClass ( CAAEGSMSewSkinBasicEdit ,
                    DataExtension           ,
                    CATBaseUnknown          ,
                    CAASewSkinBasic            );

//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicEdit : constructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicEdit::CAAEGSMSewSkinBasicEdit()
{
}

//-----------------------------------------------------------------------------
// CAAEGSMSewSkinBasicEdit : destructor
//-----------------------------------------------------------------------------
CAAEGSMSewSkinBasicEdit::~CAAEGSMSewSkinBasicEdit()
{
}

// Tie the implementation to its interface
// ---------------------------------------
#include "TIE_CATIEdit.h" // needed to tie the implementation to its interface
TIE_CATIEdit( CAAEGSMSewSkinBasicEdit);

// 
// To declare that SewSkin implements CATIEdit , insert 
// the following line in the interface dictionary :
//
// SewSkin      CATIEdit    libCAASewSkinUI

//-----------------------------------------------------------------------------
// Implements CATIEdit::Activate
//-----------------------------------------------------------------------------
CATCommand * CAAEGSMSewSkinBasicEdit::Activate (CATPathElement *ipPath)
{

    HRESULT rc = E_FAIL ; 
    CATCommand * comm = NULL;
    CATBaseUnknown_var EditedSewSkin ;
   
	// Retrieves the Edited Spec
	if(ipPath ) EditedSewSkin = ipPath ->SearchObject(CAAIGSMSewSkinBasic::ClassName());
    CAAIGSMSewSkinBasic_var trial = EditedSewSkin ;
	if ( EditedSewSkin != NULL_var) {
        CAAIGSMSewSkinBasic *piGSMSewSkinBasic = NULL;
        HRESULT rc = EditedSewSkin -> QueryInterface ( IID_CAAIGSMSewSkinBasic, (void**) &piGSMSewSkinBasic);
        if (piGSMSewSkinBasic){ 
            // Creates the edition command
            CATCommand *pCommand =  new CAAGSMSewSkinBasicCmd( piGSMSewSkinBasic );
            piGSMSewSkinBasic->Release() ; piGSMSewSkinBasic= NULL;
        }
		        
        EditedSewSkin  -> Release();
    }
  return comm ;
}

