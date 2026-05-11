// COPYRIGHT DASSAULT SYSTEMES 2004
// ===================================================================
//
// CAAPmiCreateUserPrismaticOperationCmd:
//
// Sample code for : CAA Manufacturing
// Mission         : Command that create a user defined setup in the process after the selected setup.
//                   
//
// Type            : Interactive functionality
//
// How to run it   : 1-You need the Use Case CAAPmiGenerateUserSetupCatalog in order to generate 
//                     a new type of setup ("UserSetup") in a new catalog of Setup.
//                   2-Build the CAAPmiCreateUserDefinedPrismaticOperationCommand library.
//                     In this library there is the code that defines the command, and the code
//                     for an add-in in Prismatic Machining Workbench, to define a new command
//                     header "UserDefinedXXX" that will enable you to instanciate an operation
//                     "UserDefinedXXX" under program node.
//                   3-Create the runtime view.
//                     You must have a line in your .dico file like this one:
//
//                     CAAPmiCreateUserPrismaticOperationAddin     CATIManufacturingProgramAddin   libCAAPmiCreatePrismaticOperationCommand
//                      
//				     4-Launch CATIA.
//                   5-Enter in Prismatic machining workbench in NC Manufacturing workshop.
//                   6-Click on the "UserDefinedXXX" Command
//                   7-Select the program or a previously created operation
//
//                   => A new operation "UserDefinedXXX.1" will appear in the graph.
//                         You will be abble to edit this operation. 
//                         You will be able to overload its editor.
//
//=============================================================================
// 
// Create User Defined Prismatic Operation Command 
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
#include "CATIMfgNCProgram.h"
#include "CATIAManufacturingProgram.h"

// Includes
#include "CAAPmiCreateUserPrismaticOperationCmd.h" 

#include "CATCreateExternalObject.h"
CATCreateClassArg(CAAPmiCreateUserPrismaticOperationCmd,CATString);

//========================================================================
// Constructor
//========================================================================
CAAPmiCreateUserPrismaticOperationCmd::CAAPmiCreateUserPrismaticOperationCmd(CATString* argument):CATStateCommand ("CreateUserDefinedDrilling")
{ 
	
//	_ResourceContainer  = NULL_var;
	_ActAcq    =  NULL;
	_InitState =  NULL;

	_TypeToCreate = CATUnicodeString (*argument);
	
}


//========================================================================
// Destructor
//========================================================================

CAAPmiCreateUserPrismaticOperationCmd::~CAAPmiCreateUserPrismaticOperationCmd()
{
	
   if(NULL != _ActAcq) _ActAcq->RequestDelayedDestruction();    
   _ActAcq = NULL;
   if(NULL != _InitState) _InitState->Release();    
   _InitState = NULL;

}

//========================================================================
// Build Graph
//========================================================================

void CAAPmiCreateUserPrismaticOperationCmd::BuildGraph()
{  
	// Init of selection agent for father activity	
	_ActAcq = new CATPathElementAgent("ProgramSelectionAgent");
	
	if (NULL != _ActAcq)
	{	   
      _ActAcq->SetElementType(CATIMfgNCProgram::ClassName());
      //_ActAcq->AddElementType(CATIMfgActivity::ClassName());
	  _ActAcq->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngWithUndo);

	}

    // Initial State
	
	AddCSOClient(_ActAcq);
	
	CATDialogState* _InitState = GetInitialState("SelectAProgramOrAnOperation"); 
	if (NULL != _InitState)
		_InitState->AddDialogAgent(_ActAcq);
    
	if (NULL != _ActAcq)
		AddTransition (_InitState, NULL, IsOutputSetCondition(_ActAcq),
        Action((ActionMethod)& CAAPmiCreateUserPrismaticOperationCmd::ManageChildActivityAndSequence));
    
	return;
}

//========================================================================
// ManageChildActivityAndSequence
//========================================================================

boolean CAAPmiCreateUserPrismaticOperationCmd::ManageChildActivityAndSequence (void *)
{  
    HRESULT RC = S_OK;
    
    // -----------------------------------------------
    // Load the User Prismatic Operations Catalog
    // -----------------------------------------------
    char  *oGraphicPath= NULL;
    CATString CatalogName ("UserPrismaticOperationCatalog.CATfct");
    CATString LibAct (CatalogName);
    
    CATLibStatus State = CATGetEnvValue("CATGraphicPath",&oGraphicPath) ;
    if (State == CATLibSuccess)
    {
        LibAct = CATString (CATFindPath(CatalogName,oGraphicPath)) ;	
    }
    free (oGraphicPath);
    oGraphicPath = NULL;
    
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
    // Creation of prismatic operation
    // -----------------------------------------------		
    CATIAManufacturingProgram_var ManufacturingProgram(SelectedObj);
    
    if (NULL_var != ManufacturingProgram)
    {
        int AutoSequence = 1;
        CATIAManufacturingOperation* pCreatedOperation = NULL;
        CATBSTR TypeToCreate;
        _TypeToCreate.ConvertToBSTR (&TypeToCreate);
        
        RC = ManufacturingProgram->AppendOperation (TypeToCreate, AutoSequence, pCreatedOperation);  
        if (FAILED(RC) || (NULL == pCreatedOperation))
        {
            return FALSE;
        }
    }    
    
    
    return TRUE;
}
