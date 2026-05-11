// COPYRIGHT DASSAULT SYSTEMES 2006

//Local Framework 
#include "CAACafCenterGraphCmd.h"

//ApplicationFrame Framework
#include "CATFrmLayout.h"    
#include "CATFrmWindow.h"    

// CATIAApplicationFrame Framework
#include "CATFrmNavigGraphicWindow.h"
#include "CATNavigBox.h"
#include "CATCafCenterGraph.h"

//DialogEngine Framework
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"

//ObjectModelerBase Framework
#include "CATINavigateObject.h"

// Visualization Framework
#include "CATPathElement.h"

// System Framework
#include "CATLISTV_CATBaseUnknown.h"
#include "CATGetEnvValue.h"              

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAACafCenterGraphCmd);

//----------------------LifeCycle's PART ----------------------------------
CAACafCenterGraphCmd::CAACafCenterGraphCmd():
  CATStateCommand("CAACafCenterGraphCmdId"),
  _daObjectToCenterNode(NULL)
{
  printf("CAACafCenterGraphCmd constructor\n");
}

//-----------------------------------------------------------------------

CAACafCenterGraphCmd::~CAACafCenterGraphCmd()
{
  printf("CAACafCenterGraphCmd destructor\n");

  if ( NULL != _daObjectToCenterNode ) 
  {
     _daObjectToCenterNode -> RequestDelayedDestruction() ;
     _daObjectToCenterNode = NULL ;
  }

}

//----------------------BuildGraph PART -----------------------------------

void CAACafCenterGraphCmd::BuildGraph()
{
  printf("CAACafCenterGraphCmd BuildGraph\n");
  
   //1- Creates the dialog agent 
   //    -  it gets only CATINavigateObject element 
   //    -  an element is selected with the left button 
   //    -  the repeat mode allows you to reuse this agent, so to revalue it
   //    -  only the selected object will be highlighted
   _daObjectToCenterNode = new CATPathElementAgent("SelObjectToCenterNodeId");
   _daObjectToCenterNode->AddElementType(IID_CATINavigateObject);
   _daObjectToCenterNode->SetBehavior(CATDlgEngRepeat | CATDlgEngNewHSOManager | CATDlgEngWithPSOHSO );
                            
 
   //2- Creates the state. See NLS file for the message in the status bar
   //
   CATDialogState *stGetObjState = GetInitialState("stGetObjStateId");
   stGetObjState->AddDialogAgent(_daObjectToCenterNode);

   // 3- The transition loops on the transition state 
   //   
   CATDialogTransition *pTransition =    AddTransition
   (
      stGetObjState,
      stGetObjState,
      IsLastModifiedAgentCondition(_daObjectToCenterNode)  , 
      Action((ActionMethod) & CAACafCenterGraphCmd::CenterGraphOnObject)
   );  

}

//----------------------Action methods's PART -----------------------------

CATBoolean CAACafCenterGraphCmd::CenterGraphOnObject(void * iDummy)
{
  printf("CAACafCenterGraphCmd::CenterObject\n");

  // Retrieves the current window 
  CATFrmLayout * pLayout = CATFrmLayout::GetCurrentLayout();
  if ( NULL == pLayout ) return TRUE;

  CATFrmWindow * pCurrentWindow = pLayout->GetCurrentWindow();
  if ( NULL == pCurrentWindow ) return TRUE;

  // If it is a CATFrmNavigGraphicWindow, it is possible to
  // retrieve a CATNavigBox pointer
  //
  if ( 1 != pCurrentWindow->IsAKindOf("CATFrmNavigGraphicWindow") ) return TRUE;

  CATFrmNavigGraphicWindow * pFrmNavigGraphicWindow = 
    (CATFrmNavigGraphicWindow*) pCurrentWindow ;

  CATNavigBox * pNavigBox = NULL ;
  pNavigBox = pFrmNavigGraphicWindow->GetNavigBox();

  if ( NULL == pNavigBox ) return TRUE;

  // Perform center graph action on highlighted object
  //
  CATCafCenterGraph CenterGraphObj;
  CenterGraphObj.CenterGraph("OnHSO",pNavigBox);

  return TRUE ;
}
