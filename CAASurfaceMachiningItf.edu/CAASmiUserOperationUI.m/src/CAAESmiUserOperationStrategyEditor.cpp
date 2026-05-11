// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAAESmiUserOperationStrategyEditor :
//
// Sample code for : CAA Activities Management (sample 2)
//
// Mission         : Overloads the Strategy Tabpage of the edition panel of an user operation ("CAASmgOperation").
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Edit a CAASmg operation
//                   3- Select the strategy tabpage
//
// IMPORTANT :      To use this sample, you need to :
//                  * Copy CAAUserOperationCatalog.CATfct and CAAUserMachiningFeatures.CATfct
//                    in the resources\graphic directory of the runtime view.
//					 
//                  * In the file CAASurfaceMachiningItf.dico, uncomment lines by removing '#CAA#' characters
//
//=============================================================================

// Includes
#include "CAAESmiUserOperationStrategyEditor.h"

// Manufacturing Interfaces
#include "CATIMfgActivityParameters.h"

// Literals Interfaces
#include "CATICkeParamFrame.h"

// Dialog Interfaces
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgGridConstraints.h"
#include "CATMsgCatalog.h"
 
// Tie the implementation to its interface
CATImplementBOA (CATIMfgStrategyActivity, CAAESmiUserOperationStrategyEditor);
CATImplementClass( CAAESmiUserOperationStrategyEditor,
                   CacheExtension,
                   CATIMfgStrategyActivity,
                   CAASmgOperation );
 
//========================================================================
// Constructor
//========================================================================
CAAESmiUserOperationStrategyEditor::CAAESmiUserOperationStrategyEditor()
{
}

//========================================================================
// Destructor
//========================================================================
CAAESmiUserOperationStrategyEditor::~CAAESmiUserOperationStrategyEditor()
{
}
 
//========================================================================
// GetMainPanelEditor
//========================================================================
HRESULT CAAESmiUserOperationStrategyEditor::GetMainPanelEditor (CATDialog * iFather , CATDlgFrame*&  oFrame , CATDlgStyle  iStyle)
{
   HRESULT oRC = E_FAIL;

   // Creates a new frame
   oFrame = new CATDlgFrame (iFather, "StrategyFrame", CATDlgGridLayout|CATDlgFraNoTitle);	
   if (oFrame)
   {  
	   // Gets strategy parameters
	   CATIMfgActivityParameters * pActivityParameters = NULL;
	   oRC = QueryInterface(IID_CATIMfgActivityParameters, (void**) &pActivityParameters);
	   if (SUCCEEDED(oRC))
	   {
			CATBaseUnknown_var spBaseParm = NULL_var; 
			oRC = pActivityParameters->FindElement("CAAStep",spBaseParm);
			CATICkeParamFrame_var spParamFrame (spBaseParm);
			if (!!spParamFrame)
			{
				// Creates a label
				CATDlgLabel *pDlgLabel = new CATDlgLabel(oFrame, "StepLabel");
				if (pDlgLabel)
				{
					CATUnicodeString ParamTitle = CATMsgCatalog::BuildMessage("CAASmiParameters","CAAStep");				
                    pDlgLabel->SetTitle(ParamTitle);
					pDlgLabel->SetGridConstraints( 0, 0, 1, 1, CATGRID_4SIDES);
				}

				// Creates a frame-editor linked to the parameter
				CATDlgFrame *pDlgFrame = spParamFrame->GetInPanelEdition(NULL_var,oFrame,CATCkeWithSpinner|CATCkeNoLabel);
				if (pDlgFrame)
					pDlgFrame->SetGridConstraints( 0, 1, 1, 1, CATGRID_4SIDES);
			}

			pActivityParameters->Release();
			pActivityParameters = NULL;
	   }
   }

   return oRC;
}

