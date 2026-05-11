// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAMaiCreateUserSetupCom:
//
// Sample code for : CAA Manufacturing
// Mission         : Command that create a user defined setup in the process after the selected setup.
//                   
//
// Type            : Interactive functionality
//
// How to run it   : 1-You need the Use Case CAAMaiGenerateUserSetupCatalog in order to generate 
//                     a new type of setup ("UserSetup") in a new catalog of Setup.
//                   2-Build the CAAMaiCreateUserSetupCommand library.
//                     In this library there is the code that defines the command, and the code
//                     for an add-in in Prismatic Machining Workbench, to define a new command
//                     header "User Setup" that will enable you to instanciate a setup
//      				     "UserSetup" under process node.
//                   3-Create the runtime view.
//                     You must have a line in your .dico file like this one:
//
//                     CAAMaiCreateUserSetupAddin     CATIManufacturingProgramAddin   libCAAMaiCreateUserSetupCommand
//                      
//				         4-Launch CATIA.
//                   5-Enter in Prismatic machining workbench in NC Manufacturing workshop.
//                   6-Click on the "UserSetup" Command
//                   7-Select Process or a previously created setup
//
//						      => A new Setup "UserSetup.1" will appear in the graph.
//                         You will be abble to edit this setup. 
//                         You will be able to overload itst editor.
//
//=============================================================================
// 
// Create User Setup Command 
//
//=============================================================================
//
// CATIA Interfaces
#include "CATPathElementAgent.h"
#include "CATGetEnvValue.h"
#include "CATLib.h"
#include "CATISPPActivityRoot.h"
#include "CATISPPProcessContainer.h"
#include "CATInstantiateComponent.h"

// Manufacturing Interfaces
#include "CATIMfgActivity.h"
#include "CATIMfgManufacturingFactories.h"
#include "CATIMfgProcess.h"

// Includes
#include "CAAMaiCreateUserSetupCom.h" 

#include "CATCreateExternalObject.h"
CATCreateClassArg(CAAMaiCreateUserSetupCom,CATString);

//========================================================================
// Constructor
//========================================================================
CAAMaiCreateUserSetupCom::CAAMaiCreateUserSetupCom(CATString* argument):CATStateCommand ("CreateUserAct")
{ 
	
//	_ResourceContainer  = NULL_var;
	_ActAcq    =  NULL;
	_InitState =  NULL;

	_TypeToCreate = CATUnicodeString (*argument);
	
	// Init of selection agent for father activity	
	_ActAcq = new CATPathElementAgent("Act");
	
	if (NULL != _ActAcq)
	{
	   
      _ActAcq->SetElementType(CATISPPActivityRoot::ClassName());
      _ActAcq->AddElementType(CATIMfgActivity::ClassName());
		_ActAcq->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngWithUndo);

	}
}


//========================================================================
// Destructor
//========================================================================

CAAMaiCreateUserSetupCom::~CAAMaiCreateUserSetupCom()
{
	
   if(NULL != _ActAcq) _ActAcq->RequestDelayedDestruction();    
   _ActAcq = NULL;
   if(NULL != _InitState) _InitState->Release();    
   _InitState = NULL;

}

//========================================================================
// Build Graph
//========================================================================

void CAAMaiCreateUserSetupCom::BuildGraph()
{  
	// Initial State
	
	AddCSOClient(_ActAcq);
	
	CATDialogState* _InitState = GetInitialState("InitState"); 
	if (NULL != _InitState)
		_InitState->AddDialogAgent(_ActAcq);
    
	if (NULL != _ActAcq)
		AddTransition (_InitState, NULL, IsOutputSetCondition(_ActAcq),
        Action((ActionMethod)& CAAMaiCreateUserSetupCom::ManageChildActivityAndSequence));
    
	return;
}

//========================================================================
// ManageChildActivityAndSequence
//========================================================================

boolean CAAMaiCreateUserSetupCom::ManageChildActivityAndSequence (void *)
{  
	HRESULT RC = S_OK;
	
	CATTry
	{    
		// -----------------------------------------------
		// Load the User Setups Catalog
		// -----------------------------------------------
		char  *oGraphicPath= NULL;
		CATString CatalogName ("UserSetupCatalog.CATfct");
		CATString LibAct (CatalogName);
		
		CATLibStatus State = CATGetEnvValue("CATGraphicPath",&oGraphicPath) ;
		if (State == CATLibSuccess)
		{
			LibAct = CATString (CATFindPath(CatalogName,oGraphicPath)) ;	
        
            // Deallocates the chars allocated by CATGetEnvValue
            free (oGraphicPath);
            oGraphicPath = NULL;
		}

		// Get Manufacturing Activity Container
		CATIMfgManufacturingFactories *piFact =NULL;

		CATString ClassName("CATMfgManufacturingFactories");
		CATInstantiateComponent (ClassName,
                            CATIMfgManufacturingFactories::ClassId(),
                            (void**)& piFact);
		CATIContainer_var RootContainer = NULL_var;
		if (piFact)
		  {
		    RC = piFact->GetManufacturingActivityFactory (RootContainer);
		    piFact->Release();
		  }

		CATISPPProcessContainer_var RootCont (RootContainer);
		CATListValCATBaseUnknown_var*	ListProcess = RootCont -> GetAllProcess();
		if ( ListProcess )
		{
			int NbProcess = ListProcess -> Size();
			for (int i=1; i<=NbProcess; i++)
			{
				CATISPPActivityRoot_var Root ((*ListProcess)[i]);
                if (NULL_var != Root)
				{
					Root -> AddLibraryToUse(CATUnicodeString(LibAct));
				}
			}
			delete ListProcess ;
			ListProcess=NULL ;
		}   
		
		// -----------------------------------------------
		// Retrieve selected activity
		// -----------------------------------------------
		CATBaseUnknown_var SelectedObj = _ActAcq -> GetElementValue();
		
		// -----------------------------------------------
      // use CATIMfgProcess in order to append a User Setup under Process node
		// -----------------------------------------------
      CATBaseUnknown_var oPartOperation;
      CATIMfgProcess_var hProcess(SelectedObj);
      if (NULL_var != hProcess)
      {
         
         CATUnicodeString ActivityTypeToCreate = _TypeToCreate;
         RC = hProcess->AppendSetup(ActivityTypeToCreate,SelectedObj,oPartOperation);
         
      }
      
	}
	
	CATCatch (CATError, Error);
	{
		return FALSE;
	}
	
	CATEndTry;
	
	return TRUE;
}
