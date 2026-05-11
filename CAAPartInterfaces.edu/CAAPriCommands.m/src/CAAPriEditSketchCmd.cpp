// COPYRIGHT Dassault Systemes 2002

//Local Framework
#include "CAAPriEditSketchCmd.h"
#include "CAAPriEditSketchDlg.h"         // Dialog box associated with the state command

//DialogEngine Framework
#include "CATFeatureImportAgent.h"       // To select a feature
#include "CATDialogTransition.h"         // To set NLS resource to the transition
#include "CATEditAgent.h"                // To stack an another workbench 
#include "CATPanelState.h"               // To manage OK, Cancel, Apply, Preview buttons
#include "CATAcquisitionFilter.h"

//ApplicationFrame Framework
#include "CATApplicationFrame.h"         // To retrieve the parent dialog boxes
#include "CATFrmEditor.h"                // To retrieve the editor
#include "CATStackableCommandSet.h"      // To create a list of command available
                                         // in the stacked workbench

// PartInterfaces Framework
#include "CATIPad.h"
#include "CATIPrism.h"
#include "CATIPrtProfile.h"

// SketcherInterfaces Framework
#include "CATISketch.h"

// InteractiveInterfaces
#include "CATIBuildPath.h"                // needed to build a path element

//Visualization framework
#include "CATPathElement.h"

//C++ Standard Library
#include <iostream.h>


// To declare that the class is a component main class which OM
// derives from the CATStateCommand component
//
CATImplementClass(CAAPriEditSketchCmd,Implementation,CATStateCommand,CATNull);

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAPriEditSketchCmd);

//-------------------------------------------------------------------------
CAAPriEditSketchCmd::CAAPriEditSketchCmd():
CATStateCommand ("CAAPriEditSketchCmd"),
_pDialogBox(NULL),_pFeatureAgent(NULL),_pEditAgent(NULL),_pTriggerAgent(NULL)
{
    // Build the dialog box associated with the state command
    CATApplicationFrame * pFrame = NULL ;
    pFrame = CATApplicationFrame::GetFrame();
    if ( NULL != pFrame )
    {
       if ( NULL != pFrame->GetMainWindow() )
       {
          _pDialogBox = new CAAPriEditSketchDlg(pFrame->GetMainWindow());
          _pDialogBox -> Build();
       }
    }
}

//-------------------------------------------------------------------------

CAAPriEditSketchCmd::~CAAPriEditSketchCmd()
{
    cout <<" destructor CAAPriEditSketchCmd::~CAAPriEditSketchCmd " << endl;

    if ( NULL != _pDialogBox )
    {
        _pDialogBox->RequestDelayedDestruction();
        _pDialogBox = NULL ;
    }

    if ( NULL != _pFeatureAgent )
    {
        _pFeatureAgent->RequestDelayedDestruction();
        _pFeatureAgent = NULL ;
    }

    if ( NULL != _pEditAgent )
    {
        _pEditAgent->RequestDelayedDestruction();
        _pEditAgent = NULL ;
    }

    if ( NULL != _pTriggerAgent )
    {
       _pTriggerAgent->RequestDelayedDestruction();
       _pTriggerAgent = NULL ;
    }
    
}

//-------------------------------------------------------------------------

void CAAPriEditSketchCmd::BuildGraph()
{
    cout <<" CAAPriEditSketchCmd::BuildGraph" << endl;

    if ( (NULL != _pDialogBox) && GetEditor() )
    {    
     // 1- Agent Definition
     // -------------------

        // To select the Pad 
        _pFeatureAgent = new CATFeatureImportAgent("PadAgentId");
        _pFeatureAgent->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);
        _pFeatureAgent->AddElementType(IID_CATIPad);

                
        // Thanks this filter, the element selected is OK when the transition is done
        CATAcquisitionFilter * pFilterForProfile = Filter(
                           (FilterMethod) & CAAPriEditSketchCmd::TestProfile,
										   (void*)NULL);
										  
        _pFeatureAgent->SetFilter(pFilterForProfile);

        // Reads the cso for object - action
        AddCSOClient(_pFeatureAgent); 

        // To execute the workbench's stack 
        _pEditAgent = new CATEditAgent("EditAgentId");
        _pEditAgent->SetPanel(_pDialogBox);
 
        // The workbench will be automatically those of the Sketcher. Therefore,
        // no need to call the SetWorkbench method. 
        
        // List of available commands for the sketcher workbench. These commands
        // (3 here) are added to those which are automaticalley set in the 
        // CATStackableCommandSet class constructor. Among them there is
        // the command to exit the workbench.
        //
        CATStackableCommandSet * pCommandSet = new CATStackableCommandSet();
        pCommandSet->AddCommand("2DConstraint");
        pCommandSet->AddCommand("2DAutoCst");
        pCommandSet->AddCommand("2DAnimateCst");
 
        _pEditAgent->SetCommandSet(pCommandSet);
        pCommandSet->Release();
        pCommandSet = NULL ;

        // ProvideProfileToEdit is the method to provide the object to edit
        _pEditAgent->SetElementProvider(this, 
                        (CATEditAgent::ElementProvider)&CAAPriEditSketchCmd::ProvideProfileToEdit);

        // To ask the profile edition
        _pTriggerAgent = new CATDialogAgent("TriggerAgentid");
        _pTriggerAgent->AcceptOnNotify(_pDialogBox,"CAAPriEditSketchNotification");


     // 2- State Definition
     // -------------------

        // State to get the Pad
        CATDialogState * pInputPadState = GetInitialState("InputPadStateId");
        if ( NULL != pInputPadState )
        {
           pInputPadState->AddDialogAgent(_pFeatureAgent);
        }
     
        // State to receive the events coming from the dialog box:
        //   - OK, CANCEL notifications ( automatically managed by the CATPanelState )
        //   - Button Sketch  
        //  
        CATPanelState * pDialogState = new CATPanelState(this,"DialogStateId",_pDialogBox);
        if ( NULL != pDialogState )
        {
           AddDialogState(pDialogState);
           pDialogState->AddDialogAgent(_pTriggerAgent); 
        }

        // State to launch the profile edition
        // Caution: _pEditAgent is a state command, this agent should be always attached 
        // to a state without other agent.
        //
        CATDialogState * pEditSketchState = AddDialogState("EditSketchStateId");
        if ( NULL != pEditSketchState )
        {
           pEditSketchState->AddDialogAgent(_pEditAgent);
        }
        

     // 3- Transition Definition
     // -------------------------     
        if ( (NULL != pInputPadState) && (NULL != pEditSketchState) && (NULL != pDialogState) )
        {
           CATDialogTransition * pFirstTransition = AddTransition(pInputPadState,pDialogState,
                       IsOutputSetCondition(_pFeatureAgent),
                      Action((ActionMethod) & CAAPriEditSketchCmd::SelectPad,
                             (ActionMethod) & CAAPriEditSketchCmd::UndoSelectPad,
                             (ActionMethod) & CAAPriEditSketchCmd::RedoSelectPad) );

           CATDialogTransition * pEditSketchTransition = AddTransition(pDialogState,pEditSketchState,
                    IsOutputSetCondition(_pTriggerAgent),
                    Action((ActionMethod) & CAAPriEditSketchCmd::TriggerEditSketch));   

           CATDialogTransition * pBackTransition = AddTransition(pEditSketchState,pDialogState,
                    IsOutputSetCondition(_pEditAgent),
                    Action((ActionMethod) & CAAPriEditSketchCmd::EditSketch));                  
        }

     // 4- Cleaning Step 
     // ----------------

     // The panel state should be released 
     // 
        if ( NULL != pDialogState )
        {
           pDialogState -> Release();
           pDialogState=NULL;
        }
    }
    
}

CATBoolean CAAPriEditSketchCmd::TestProfile( CATDialogAgent * iAgent, void * iUsefulData)
{
   cout <<" CAAPriEditSketchCmd::TestProfile" << endl ;

   CATBoolean rcheck = FALSE ;

   if ( (NULL != iAgent) && ( 1==iAgent->IsAKindOf("CATFeatureImportAgent")) )
   {
      // GetElementValue does not addref the returned pointer
      CATBaseUnknown * pSelectedElt= ((CATFeatureImportAgent *)iAgent)->GetElementValue();
      if ( NULL != pSelectedElt )
      {
         CATISpecObject * pISpecObjectOnProfile = NULL ;
         HRESULT rc = FindProfile(pSelectedElt,&pISpecObjectOnProfile) ;
         if ( SUCCEEDED(rc) && (NULL !=pISpecObjectOnProfile) )
         {
            pISpecObjectOnProfile->Release();
            pISpecObjectOnProfile = NULL ;
            rcheck = TRUE ;
         }
      }
   }

   return rcheck ;
}
//-------------------------------------------------------------------------

CATBoolean CAAPriEditSketchCmd::SelectPad( void *UsefulData)
{
   cout <<" CAAPriEditSketchCmd::SelectPad" << endl;

   // GetElementValue does not addref the returned pointer
   CATBaseUnknown * pSelectedElt= _pFeatureAgent->GetElementValue();

   if ( (NULL != pSelectedElt) && (NULL != _pDialogBox) )
   {
       CATISpecObject * pISpecObjectOnProfile = NULL ;
       HRESULT rc = FindProfile(pSelectedElt,&pISpecObjectOnProfile) ;
       if ( SUCCEEDED(rc) && (NULL !=pISpecObjectOnProfile))
       {
          // The name of the profile is displayed in the dialog box
          _pDialogBox->SetElement(pISpecObjectOnProfile);

          pISpecObjectOnProfile->Release();
          pISpecObjectOnProfile = NULL ;
       }
   }

   if ( NULL != _pDialogBox )
   {
      _pDialogBox->SetVisibility(CATDlgShow);
   }

   return TRUE ;
}

//-------------------------------------------------------------------------
CATBoolean CAAPriEditSketchCmd::UndoSelectPad( void *UsefulData)
{
    if ( NULL != _pDialogBox )
    {
       _pDialogBox->SetVisibility(CATDlgHide);
    }
    return TRUE ;
}
//-------------------------------------------------------------------------
CATBoolean CAAPriEditSketchCmd::RedoSelectPad( void *UsefulData)
{
    if ( NULL != _pDialogBox )
    {
       _pDialogBox->SetVisibility(CATDlgShow);
    }
    return TRUE ;
}
//-------------------------------------------------------------------------

CATPathElement * CAAPriEditSketchCmd::ProvideProfileToEdit(CATClassId iDummy)
{
   cout <<" CAAPriEditSketchCmd::ProvideProfileToEdit" << endl;

   CATPathElement * pPathToReturn = NULL ;

   if ( (NULL == GetEditor()) || (NULL == _pFeatureAgent) ) return NULL ;

   // GetElementValue does not addref the returned pointer
   CATBaseUnknown * pSelectedElt= _pFeatureAgent->GetElementValue();

   // Retrieve the profile to edit
   CATISpecObject * pISpecObjectOnProfile = NULL ;
   HRESULT rc = FindProfile(pSelectedElt,&pISpecObjectOnProfile) ;

   // Create a path from the profile to the root
   if ( SUCCEEDED(rc) && (NULL!=pISpecObjectOnProfile))
   {
      CATIBuildPath *piBuildPath = NULL;
      rc = pISpecObjectOnProfile->QueryInterface( IID_CATIBuildPath, (void**) &piBuildPath );
                                                       
      if ( SUCCEEDED(rc) )
      {
         CATPathElement Context = GetEditor()->GetUIActiveObject();
         rc = piBuildPath->ExtractPathElement(&Context,&pPathToReturn);

         piBuildPath->Release();
         piBuildPath = NULL ;
      }
      
      pISpecObjectOnProfile->Release();
      pISpecObjectOnProfile = NULL ;
   }

   return pPathToReturn ;
}

//-------------------------------------------------------------------------

CATBoolean CAAPriEditSketchCmd::EditSketch(void *iDummy)
{
   cout << "CAAPriEditSketchCmd::EditSketch" << endl ;

   // The workbench's stack is ended, the dialog box can be set visible

   if ( NULL != _pDialogBox)
   {
       _pDialogBox->SetVisibility(CATDlgShow) ;
   }

   // to enable the agent reusage
   if ( NULL != _pEditAgent)
   {
       _pEditAgent->InitializeAcquisition();
   }

   return TRUE ;
}
//-------------------------------------------------------------------------

CATBoolean CAAPriEditSketchCmd::TriggerEditSketch(void *iDummy)
{
   cout << "CAAPriEditSketchCmd::TriggerEditSketch" << endl ;

   // The dialog box should not disturb the stacked's workbench
   if ( NULL != _pDialogBox)
   {
       _pDialogBox->SetVisibility(CATDlgHide) ;
   }
   
   // To enable the agent reusage
   if ( NULL != _pTriggerAgent )
   {
      _pTriggerAgent->InitializeAcquisition();
   }

   return TRUE ;
}

//-------------------------------------------------------------------------

HRESULT CAAPriEditSketchCmd::FindProfile(CATBaseUnknown  * iSelectedPad, 
                                         CATISpecObject ** oSpecObjectOnProfile)
{
   HRESULT rc = E_FAIL;

   if ( NULL != iSelectedPad )
   {
      CATIPrism * piPrismOnPad = NULL ;
      rc = iSelectedPad->QueryInterface(IID_CATIPrism, (void**) & piPrismOnPad) ;
      if ( SUCCEEDED(rc) )
      {
          CATISpecObject_var spISpecOnProfile = piPrismOnPad->GetProfile();
          if ( NULL_var != spISpecOnProfile )
          {
             CATIPrtProfile_var spIProfileOnProfile = spISpecOnProfile ;
             if ( NULL_var != spIProfileOnProfile )
             {
                int nbelt = spIProfileOnProfile->GetElementCount() ;
                
                if (  nbelt == 1 )
                {
                    CATISpecObject_var spSpecOnFirstElt ;
                    spIProfileOnProfile->GetElement(1,spSpecOnFirstElt) ;
                    
                    if ( NULL_var != spSpecOnFirstElt )
                    {
                       // Just verify that it's a sketch
                       CATISketch * pISketch = NULL ;
                       rc = spSpecOnFirstElt->QueryInterface(IID_CATISketch, (void**) & pISketch) ;
                       if ( SUCCEEDED(rc) )
                       {
                          pISketch->Release();
                          pISketch = NULL ;

                          rc = spSpecOnFirstElt->QueryInterface(IID_CATISpecObject, 
                                            (void**) oSpecObjectOnProfile) ;
                       }
                    }else rc = E_FAIL ;
          
                } else rc = E_FAIL ;
             } else rc = E_FAIL ;
          } else rc = E_FAIL ;

          piPrismOnPad->Release();
          piPrismOnPad = NULL ;
      }
   }

   return rc ;
}

