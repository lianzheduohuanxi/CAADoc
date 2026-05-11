// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAADrwCenterLineCmd.h"

// System
#include "CATBaseUnknown.h"
#include "CATCreateExternalObject.h"   // Define the CATDeclareClass macro

// Visualization
#include "CATPathElementAgent.h"
#include "CATPathElement.h"
#include "CATSO.h"

// DraftingInterface
#include "IDMCircle2D.h"
#include "CATIDrwCenterLine.h"
#include "CATIDrwAnnotationFactory.h"

// The command name
CATCreateClass (CAADrwCenterLineCmd);

// ----------------------------------------------------------------------------
CAADrwCenterLineCmd::CAADrwCenterLineCmd():CATStateCommand(CATString("CreateCenterLines"))
, _pObjectAgent(NULL)
{
}

// ----------------------------------------------------------------------------
CAADrwCenterLineCmd::~CAADrwCenterLineCmd()
{
   if (NULL != _pObjectAgent) {_pObjectAgent->RequestDelayedDestruction(); _pObjectAgent = NULL;}
}

// ----------------------------------------------------------------------------
void CAADrwCenterLineCmd::BuildGraph()
{  
   // Creation of the acquisition agent
   _pObjectAgent = new CATPathElementAgent("_pObjectAgent A");
   _pObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation | 
                               CATDlgEngMultiAcquisition | 
                               CATDlgEngWithCSO); 

   // We only want to get circles
   _pObjectAgent ->AddElementType("IDMCircle2D");
   AddCSOClient(_pObjectAgent);
   
   //  States definition
   CATDialogState* pState1 = GetInitialState("Sel circle");
   pState1->AddDialogAgent(_pObjectAgent);
   
   // Transition definition
   AddTransition(pState1, NULL, IsOutputSetCondition(_pObjectAgent),
                 Action((ActionMethod)&CAADrwCenterLineCmd::CreateCtrLine, NULL, NULL));
}

// ----------------------------------------------------------------------------
boolean CAADrwCenterLineCmd::CreateCtrLine(void *iData)
{ 
   CATSO* pObjSO = _pObjectAgent->GetListOfValues(); 
   CATPathElement *pElemPath = NULL;
   
   if (NULL != pObjSO)  
   {
      // We will scan the CSO from the begining
      pObjSO->InitElementList();
      while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement())  )
      {
         
         // Make sure the element is a circle type
         // Thi circle can be interactive or a generative result (from part, model, ...)
         IDMCircle2D *piElementRef = (IDMCircle2D *)pElemPath->FindElement(IID_IDMCircle2D);
         
         if (NULL != piElementRef)
         {
            // Find the annotation factory (on the view)
            CATIDrwAnnotationFactory *piDrwFact = (CATIDrwAnnotationFactory *)pElemPath->FindElement(IID_CATIDrwAnnotationFactory);
            if (NULL != piDrwFact)
            {
               // Let's create the center line
               piDrwFact->CreateDrwCenterLine((CATBaseUnknown *)piElementRef);
               piDrwFact->Release(); piDrwFact=NULL;
            }
            piElementRef->Release(); piElementRef=NULL;
         }
      }
      
      _pObjectAgent -> InitializeAcquisition();
      return TRUE;
   }
   return FALSE;
}

