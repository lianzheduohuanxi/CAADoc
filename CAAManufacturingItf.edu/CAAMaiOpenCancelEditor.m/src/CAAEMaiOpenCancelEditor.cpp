// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAEMaiOpenCancelEditor:
//
// Sample code for : Prismatic Machining Programmer
// Mission         : Customize the Drilling Editor
//
//
// Type            : Interactive functionality
//
// Illustrates     : 1- use of manufacturing interfaces 
//                   2- MO editor customization
//
// How to run it   :  
//					In the file CAAManufacturingItf.dico, decomment the following line  
//						Drilling  CATIMfgActInEditorActivity libCAAMaiToolPathCustomization
//
//					In Prismatic Machining Programmer, 
//                   1- Create a Drilling operation, click on Cancel : a panel should appears
//                   2- Create a Drilling operation, OK, reselect it and click on Cancel : a panel should appears
//
//
//=============================================================================

#include "CAAEMaiOpenCancelEditor.h"

// System
#include "CATString.h"
#include "CATUnicodeString.h"

// ApplicationFrame
#include "CATApplicationFrame.h"

// Dialog
#include "CATDlgWindow.h"
#include "CATDlgNotify.h"

//-----------------------------------------------------------------------------
// Supported Interfaces
//-----------------------------------------------------------------------------


#include "TIE_CATIMfgActInEditorActivity.h"
TIE_CATIMfgActInEditorActivity(CAAEMaiOpenCancelEditor);

CATImplementClass(CAAEMaiOpenCancelEditor,CodeExtension,CATBaseUnknown,Drilling);



//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------

CAAEMaiOpenCancelEditor::CAAEMaiOpenCancelEditor()
{
}

//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------

CAAEMaiOpenCancelEditor::~CAAEMaiOpenCancelEditor()
{
}

//-----------------------------------------------------------------------------
// ComputeToolPath
//-----------------------------------------------------------------------------
HRESULT CAAEMaiOpenCancelEditor::OnCancelButton()
{
    HRESULT rc = S_OK;

    CATDlgWindow * TheWindow = NULL;
    CATString TheName("OnCancelWindow");


    CATApplicationFrame* TheFrame = CATApplicationFrame::GetFrame();
    if (NULL != TheFrame)
        TheWindow = TheFrame->GetMainWindow();

    if (NULL != TheWindow)
    {
        CATDlgNotify* MessageWindow = new CATDlgNotify(TheWindow, TheName, CATDlgNfyInformation);

        if (NULL != MessageWindow)
        {
            CATUnicodeString TheMessage = "CAA action triggered on cancel button";
            CATUnicodeString TheTitle = "";

            int ret = MessageWindow->DisplayBlocked(TheMessage,TheTitle);

            MessageWindow->RequestDelayedDestruction();
            MessageWindow = NULL;
        }

    }


    return rc;
}

