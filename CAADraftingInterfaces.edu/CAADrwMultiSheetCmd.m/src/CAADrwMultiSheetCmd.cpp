// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAADrwMultiSheetCmd.h"

// System
#include "CATCreateExternalObject.h"   // Define the CATDeclareClass macro
#include "CATBaseUnknown.h"

// dialog
#include "CATPathElementAgent.h"  // needed to create an agent dedicated to selection

// ApplicationFrame
#include "CATApplicationFrame.h"  // needed to retrieve the application
#include "CATIAApplication.h"     // needed to retrieve the application

// Visualization
#include "CATPathElement.h"       // needed to create a path element 
#include "CATSO.h"                // needed to retrieve selected elements
#include "CATIModelEvents.h"      // needed to take account the text modification
#include "CATModify.h"            // needed to take account the text modification

// DraftingInterfaces
#include "CATIDrwText.h"            // needed to manage text 
#include "CATIDftMultiSheetMode.h"  // needed to manage MultiSheet mode
#include "CATIADrawingDocument.h"   // needed to get Drawing document  
#include "CATIDrwTextProperties.h"  // needed to modify text properties

// The command name
CATCreateClass (CAADrwMultiSheetCmd);

// ----------------------------------------------------------------------------
CAADrwMultiSheetCmd::CAADrwMultiSheetCmd():CATStateCommand(CATString("AlignText"))
, _pObjectAgent(NULL)
{
   // Get the current drawing from the frame 
    _piSheetsOnDrawing = NULL;
	CATApplicationFrame *appFrame = CATApplicationFrame::GetFrame();
	CATIAApplication *ptApp = NULL;
	if (appFrame)
	{
		if (SUCCEEDED(appFrame->QueryInterface(IID_CATIAApplication, (void**) &ptApp)))
		{
			CATIADocument *ptDoc = NULL;
			if (SUCCEEDED(ptApp->get_ActiveDocument(ptDoc)))
			{
				CATIADrawingDocument *piDrawing = NULL;
				if (SUCCEEDED(ptDoc->QueryInterface(IID_CATIADrawingDocument, (void**) &piDrawing)))
				{
					piDrawing->get_Sheets(_piSheetsOnDrawing);
					piDrawing->Release(); piDrawing = NULL;
				}
				ptDoc->Release(); ptDoc = NULL;
			}
			ptApp->Release(); ptApp = NULL;
		}
	}

   // Save Multi sheet mode value to restore it at the end of the command
   GetMultiSheetMode(_PreviousMode);

   // Active Multi sheet mode
   if (!_PreviousMode) SetMultiSheetMode(TRUE);

   _Xposition =0.0;
   _Yposition =0.0;
}

// ----------------------------------------------------------------------------
CAADrwMultiSheetCmd::~CAADrwMultiSheetCmd()
{
   // Restore the previous Multi Sheet mode value
   SetMultiSheetMode(_PreviousMode);

   if (_pObjectAgent) {_pObjectAgent->RequestDelayedDestruction(); _pObjectAgent = NULL;}
   
   if (_piSheetsOnDrawing)
   {
       _piSheetsOnDrawing->Release();
       _piSheetsOnDrawing=NULL;

   }
}
// ----------------------------------------------------------------------------
void CAADrwMultiSheetCmd::BuildGraph()
{  
   // Creation of the acquisition agent
   _pObjectAgent = new CATPathElementAgent("pObjectAgent");
   _pObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation | 
                               CATDlgEngMultiAcquisition | 
                               CATDlgEngWithCSO); 

   // We want to select text
   _pObjectAgent ->SetElementType("CATIDrwText");
   AddCSOClient(_pObjectAgent);
   
   //  States definition
   CATDialogState* state1 = GetInitialState("Sel reference text");
   CATDialogState* state2 = AddDialogState("Sel text to align");
   state1->AddDialogAgent(_pObjectAgent);
   state2->AddDialogAgent(_pObjectAgent);
   
   // Transition definition: Check the selected text
   AddTransition(state1, state2, IsOutputSetCondition(_pObjectAgent),
                 Action((ActionMethod)&CAADrwMultiSheetCmd::CheckText, NULL, NULL));

   // Transition definition: Move the text
   AddTransition(state2, NULL, IsOutputSetCondition(_pObjectAgent),
                 Action((ActionMethod)&CAADrwMultiSheetCmd::MoveText, NULL, NULL));
}

// ----------------------------------------------------------------------------
boolean CAADrwMultiSheetCmd::CheckText(void *)
{ 
   // We get the Selected set of objects
   CATSO* pObjSO = _pObjectAgent->GetListOfValues(); 
   CATPathElement *pElemPath = NULL;
   
   
   if (NULL != pObjSO)  
   {
      // There is a selection, we will scan it from the beginning
      pObjSO->InitElementList();
      while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement()))
      {
         // Make sure the element is a text
         CATIDrwText *piText = (CATIDrwText *)pElemPath->FindElement(IID_CATIDrwText);
         
         if (NULL != piText)
         {            
            piText->GetPosition(_Xposition,_Yposition);
            piText->Release(); piText = NULL;
         }
      }
      
      _pObjectAgent -> InitializeAcquisition();
      return TRUE;
   }
   return FALSE;
}

// ----------------------------------------------------------------------------
boolean CAADrwMultiSheetCmd::MoveText(void *)
{ 
   // We get the Selected set of objects
   CATSO* pObjSO = _pObjectAgent->GetListOfValues(); 
   CATPathElement *pElemPath = NULL;
   
   if (NULL != pObjSO)  
   {
      // There is a selection, we will scan it from the beginning
      pObjSO->InitElementList();
      while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement()))
      {
          // Make sure the element is a text
        CATIDrwText *piText = (CATIDrwText *)pElemPath->FindElement(IID_CATIDrwText);
         
         if (NULL != piText)
         {            
            piText->SetPosition(_Xposition,_Yposition);
            CATIModelEvents_var event(piText);
            if (event !=NULL_var)
            {
                CATModify info((CATBaseUnknown *)piText);
                event->Dispatch(info);
            }
            piText->Release(); piText = NULL;
         }
      }
      
      _pObjectAgent -> InitializeAcquisition();
      return TRUE;
   }

      // Restore the previous Multi Sheet mode value
   SetMultiSheetMode(_PreviousMode);
   return FALSE;
}

// Method To Get working mode from CATIDftMultiSheetMode interface
void  CAADrwMultiSheetCmd::SetMultiSheetMode(boolean  iMode)
{
   if (_piSheetsOnDrawing)
   {
	   CATIDftMultiSheetMode *multiSheetManager=NULL;
	   if (SUCCEEDED(_piSheetsOnDrawing->QueryInterface(IID_CATIDftMultiSheetMode, (void **) &multiSheetManager)))
	   {
		   multiSheetManager->SetMultiSheetMode(iMode);
		   multiSheetManager->Release();multiSheetManager = NULL;
	   }
   }
}

// Method To Set working mode from CATIDftMultiSheetMode interface
void  CAADrwMultiSheetCmd::GetMultiSheetMode(boolean  &oMode)
{
	oMode = FALSE;
   if (_piSheetsOnDrawing)
   {
	   CATIDftMultiSheetMode *multiSheetManager=NULL;
	   if (SUCCEEDED(_piSheetsOnDrawing->QueryInterface(IID_CATIDftMultiSheetMode, (void **) &multiSheetManager)))
	   {
		   multiSheetManager->GetMultiSheetMode(&oMode);
		   multiSheetManager->Release(); multiSheetManager = NULL;
	   }
   }
}
