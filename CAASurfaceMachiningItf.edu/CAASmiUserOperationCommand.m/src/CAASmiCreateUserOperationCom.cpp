// COPYRIGHT DASSAULT SYSTEMES 2002
// ===================================================================
//
// CAASmiCreateUserOperationCom :
//
// Sample code for : CAA Activities Management (sample 1)
//
// Mission         : Command that :
//                    - create and sequence an operation in the selected program. 
//                    - associate a default tool to the operation.
//                    - launch the edition panel of the operation.
//                   The type of the operation is given as input argument ("CAASmgOperation").
//
// Type            : Interactive functionality
//
// How to run it   : 1- Launch CATIA
//                   2- Click on the Command
//                   3- Select a Manufacturing Program
//
//=============================================================================

// Includes
#include "CAASmiCreateUserOperationCom.h" 

// Process Interfaces
#include "CATISPPActivityRoot.h"
#include "CATISPPProcessContainer.h"

// Manufacturing Interfaces
#include "CATIMfgManufacturingSettings.h"
#include "CATIMfgActivity.h"
#include "CATIMfgTool.h"
#include "CATIMfgToolActivity.h"
#include "CATIAManufacturingProgram.h"
#include "CATIAManufacturingOperation.h"
#include "CATIMfgNCProgram.h"
#include "CATIMfgManufacturingFactories.h"

// Object Specs Modeler Interfaces
#include "CATISpecObject.h"
#include "CATIEdit.h"

// System Interfaces
#include "CATInstantiateComponent.h"
#include "CATGetEnvValue.h"
#include "CATLib.h"
#include "CATBSTR.h"
#include "CATString.h"

// DialogEngine Interfaces
#include "CATPathElementAgent.h"

#include "CATMfgNewUserActEdit.h"

#include "CATDlgNotify.h"
#include "CATApplicationFrame.h"

#include "CATCreateExternalObject.h"
CATCreateClassArg( CAASmiCreateUserOperationCom, CATString);


//========================================================================
// Constructor
//========================================================================
CAASmiCreateUserOperationCom::CAASmiCreateUserOperationCom(CATString* argument) :
  CATStateCommand ("CAASmiCreateUserOperationCom", CATDlgEngOneShot, CATCommandModeExclusive) 
{
	_spCreatedActivity = NULL_var;	
	_pActAcq =  NULL;	
	_TypeToCreate = CATUnicodeString (*argument);
		
	// Selection agent for father activity	
	_pActAcq = new CATPathElementAgent("Act");
	if (_pActAcq)
	{	
		_pActAcq->SetElementType(CATIMfgActivity::ClassName());		
		_pActAcq->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngWithUndo);
	}
}

//========================================================================
// Destructor
//========================================================================
CAASmiCreateUserOperationCom::~CAASmiCreateUserOperationCom()
{
	if(_pActAcq) _pActAcq->RequestDelayedDestruction();    
	_pActAcq = NULL;
}

//========================================================================
// BuildGraph()
//========================================================================
void CAASmiCreateUserOperationCom::BuildGraph()
{	
	AddCSOClient(_pActAcq);
	
	CATDialogState * pInitState = GetInitialState("InitState");  
	if (pInitState) pInitState->AddDialogAgent(_pActAcq);
    
	if (_pActAcq)
		AddTransition (pInitState, NULL, IsOutputSetCondition(_pActAcq),
			Action((ActionMethod)& CAASmiCreateUserOperationCom::CreateActivity));
    
	return;
}

//========================================================================
// CreateActivity
//========================================================================
CATBoolean CAASmiCreateUserOperationCom::CreateActivity (void * data)
{  
	HRESULT RC = S_OK;
	
	// -----------------------------------------------
	// Loads CAAUserOperationCatalog
	// -----------------------------------------------
	CATUnicodeString CatalogName ("CAAUserOperationCatalog.CATfct");
	CATUnicodeString LibAct (CatalogName);
		
	// Gets lib path
	char * pGraphicPath = NULL;
	CATLibStatus State = CATGetEnvValue("CATGraphicPath",&pGraphicPath) ;
	if (State == CATLibSuccess)
	{
		LibAct = CATFindPath(CatalogName.ConvertToChar(),pGraphicPath) ;
        
        // Deallocates the chars allocated by CATGetEnvValue
        free (pGraphicPath);
        pGraphicPath = NULL;
	}

    // Sends Error Window if catalog is not found
    if (0 == LibAct.GetLengthInChar())
    {
        CATApplicationFrame * pAppFrame = CATApplicationFrame::GetFrame();
        if (pAppFrame)
        {
            CATDlgWindow * pMainWindow = pAppFrame->GetMainWindow();
            if (pMainWindow)
            {
                CATDlgNotify * pErrPanel = new CATDlgNotify(pMainWindow, "Err",CATDlgNfyOK|CATDlgNfyError);
                if (pErrPanel)
                {
                    CATUnicodeString Title = "Error";
                    CATUnicodeString Message = "CAAUserOperationCatalog.CATfct is not in the resources + graphic directory of the runtime view.\nSee CAASmiUserOperationCatalog use case.";
                    pErrPanel->DisplayBlocked (Message,Title);
                    pErrPanel->RequestDelayedDestruction(); pErrPanel = NULL;         
                    return FALSE;
                }
            }
        }
    }

	// Gets Manufacturing Activity Container
	CATIMfgManufacturingFactories *piFact =NULL;
	CATString ClassName("CATMfgManufacturingFactories");
	CATInstantiateComponent (ClassName, CATIMfgManufacturingFactories::ClassId(), (void**)& piFact);
	CATIContainer_var spRootContainer = NULL_var;
	if (piFact)
	{
	    piFact->GetManufacturingActivityFactory (spRootContainer);
	    piFact->Release();
	}

	// Loads lib
	CATISPPProcessContainer_var spProcessContainer (spRootContainer);
	if (!!spProcessContainer)
	{
		CATListValCATBaseUnknown_var * pListProcess = spProcessContainer->GetAllProcess();
		if ( pListProcess )
		{
			int NbProcess = pListProcess->Size();
			for (int i=1; i<=NbProcess; i++)
			{
				CATISPPActivityRoot_var spRoot ((*pListProcess)[i]);
				if (!!spRoot)
				{				
					spRoot->AddLibraryToUse(LibAct);
				}
			}
			delete pListProcess;
			pListProcess=NULL;
		}  
	}
		
	// -----------------------------------------------
	// Retrieve selected activity
	// -----------------------------------------------
	CATBaseUnknown * pSelectedObj = _pActAcq->GetElementValue();
		
	// -----------------------------------------------
	// Searching for a good father if no activity selected
	// -----------------------------------------------
	CATBaseUnknown_var spReferenceActivity(pSelectedObj);		
	CATBaseUnknown_var spAuthorizedActivityFather = FindActivityFather(spReferenceActivity);    		
	if (NULL_var == spAuthorizedActivityFather)
	{
		// Impossible Operation 
		return FALSE;
	}
				
	// -----------------------------------------------
	// Creation + sequencing of activity
	// -----------------------------------------------		
	CATIAManufacturingProgram_var spSeqFather(spAuthorizedActivityFather);
	if (!!spSeqFather)
	{
		CATIAManufacturingOperation * pManufacturingOperation = NULL;
		CATBSTR TypeToCreate;
		_TypeToCreate.ConvertToBSTR (&TypeToCreate);
		
		int AutoSequence = 1;
		RC = spSeqFather->AppendOperation (TypeToCreate, AutoSequence, pManufacturingOperation);  
		if(FAILED(RC))
		{
			return FALSE;
		}

		_spCreatedActivity = pManufacturingOperation;
		if(NULL_var == _spCreatedActivity)
		{
			return FALSE;
		}
		
		// -----------------------------------------------
		// Update after creation (Tool...)
		// -----------------------------------------------		
		SetLinksAndDataOnActivity();    
	}	
		
	return TRUE;
}

//========================================================================
// FindActivityFather
//========================================================================
CATBaseUnknown_var CAASmiCreateUserOperationCom::FindActivityFather(CATBaseUnknown_var &ioRefActivity)
{	
	CATBaseUnknown_var oAuthorizedActivityFather = NULL_var;

	if (!!ioRefActivity)
	{
		CATIMfgActivity * pRefActivity = NULL;
		HRESULT RC = ioRefActivity->QueryInterface(IID_CATIMfgActivity, (void**) &pRefActivity);
		if (SUCCEEDED(RC))
		{
			// Read Activity Father
			CATBaseUnknown_var spChildActivity = NULL_var;
			RC = pRefActivity->GetAuthorizedFatherActivity(_TypeToCreate,
														   oAuthorizedActivityFather,
														   spChildActivity); 
			if (SUCCEEDED (RC) && !!oAuthorizedActivityFather)
			{
				if (oAuthorizedActivityFather != ioRefActivity && !!spChildActivity)
				{
					ioRefActivity = spChildActivity;
				}  
			}
			pRefActivity->Release();
			pRefActivity = NULL;
		}
	}
	
	return oAuthorizedActivityFather;
}

//========================================================================
// SetLinksAndDataOnActivity
//========================================================================
HRESULT CAASmiCreateUserOperationCom::SetLinksAndDataOnActivity()
{	
	HRESULT oRC = E_FAIL;
	
	if (!!_spCreatedActivity)
	{
		CATISpecObject * pNewOperation = NULL;
		oRC = _spCreatedActivity->QueryInterface(IID_CATISpecObject, (void**) &pNewOperation);
		if (SUCCEEDED(oRC))
		{
			// --------------------------
			// Tool
			// --------------------------
			oRC = InitTool ();
			
			// --------------------------
			// Update The Operation
			// --------------------------
			oRC = pNewOperation->Update();          
					
			// --------------------------
			// Edition of Operation  
			// --------------------------
			CATIEdit * pEdit = NULL;
			oRC = pNewOperation->QueryInterface(IID_CATIEdit, (void**) &pEdit);
			if (SUCCEEDED(oRC))
			{
				MfgNewUserActEdit = 1;
				pEdit->Activate(NULL);
				pEdit->Release();
				pEdit = NULL;
			}

			pNewOperation->Release();
			pNewOperation = NULL;
		}
	}
			
	return oRC;
}

//========================================================================
// InitTool
//========================================================================
HRESULT CAASmiCreateUserOperationCom::InitTool ()
{	
	HRESULT oRC = S_FALSE;
	
	// --------------------------------------------------------------------
	// Settings for tool searching
    //
	// SearchToolInProgram = 0 and CreateDefTool = 0 :
	//    No Tool on Operation
	//
	// SearchToolInProgram = 1 and CreateDefTool = 0 :
	//    Search for compatible tools in programm
	//       if KO -> it must be defined in current MO
	//
	// SearchToolInProgram = 0 and CreateDefTool = 1 :
	//    Search for compatible tools in Document (all programms, or resource list)
	//       if KO -> it must be defined in current MO
	//
	// SearchToolInProgram = 1 and CreateDefTool = 1 :
	//    Search for compatible tools in programm
	//       if KO -> Search for compatible tools in Document (all programms, or resource list)
	//          if KO -> it will be the default Tool
	//   
	// --------------------------------------------------------------------
	int SearchToolInProgram = 1;	
	int CreateDefTool = 1;	
	
	CATIMfgManufacturingSettings *piSetting =NULL;
	CATString ClassName("CATMfgManufacturingSettings");
	CATInstantiateComponent (ClassName,
                            CATIMfgManufacturingSettings::ClassId(),
                            (void**)&piSetting);
	if (piSetting)
	{
	   piSetting->GetSearchToolInProgramSetting(SearchToolInProgram);
	   piSetting->GetCreateDefaultToolSetting(CreateDefTool);
	   piSetting->Release();
	   piSetting = NULL;
	}
    
	//------------------------
	// Test data
	//------------------------
	CATIMfgToolActivity_var spToolAct(_spCreatedActivity);
	if (NULL_var == spToolAct) 
	{
		return oRC;    
	}

	CATIMfgActivity_var spActivity(_spCreatedActivity);
	if (NULL_var == spActivity) 
	{
		return oRC;    
	}
			
	//------------------------
	// Tool management
	//------------------------
	CATListOfCATUnicodeString ToolTypeList;
	oRC = spToolAct->GetAuthorizedToolTypeList (ToolTypeList);
	if(FAILED(oRC) && ToolTypeList.Size() == 0)
	{
		return oRC;    
	}
        
	CATBaseUnknown_var spToolOnActivity(NULL_var);
	if (SearchToolInProgram == 1)
    { 
		// --------------------------------------------------------------------
		// Associate tool to the operation
		// --------------------------------------------------------------------
		CATBaseUnknown_var spCurProgram(NULL_var);
		oRC = spActivity->GetProgram(spCurProgram);

		CATIMfgNCProgram_var spCurrentProgram(spCurProgram);
		if (!!spCurrentProgram)
		{
			oRC = spCurrentProgram->SetCurrentAuthorizedTool (spActivity);
			if(SUCCEEDED(oRC))
			{
				spToolOnActivity = spActivity->GetTool();
			}	
		}
    } 
		
	if (NULL_var == spToolOnActivity)
    {		
		if(CreateDefTool >0)
		{  
			//-----------------------------------------------------------------------
			// Search tool in document or create a default one
			//-----------------------------------------------------------------------
			CATBaseUnknown_var spCompatibleTool = NULL_var;
			oRC = SetCompatibleToolingFromDocument (ToolTypeList, spCompatibleTool);
			if (FAILED(oRC))
			{   
				// no compatible tool in document
				// create a default one
				CATBaseUnknown_var spDefaultTool = NULL_var;				
				oRC = spToolAct->CreateDefaultTool (spDefaultTool);	      				
				if(!!spDefaultTool)
				{     
					const CATBoolean doNotCheckToolChanges = FALSE;
					oRC = spActivity->SetTool(spDefaultTool, doNotCheckToolChanges);
					if(SUCCEEDED(oRC))
						spToolOnActivity = spDefaultTool;
				} 
			} 
			else
			{ 
				spToolOnActivity = spCompatibleTool;
			} 
		}
    }
	
	//----------------------------------------------
	// Update ToolChanges if necessary
	//----------------------------------------------
	if(!!spToolOnActivity) 
		spActivity->CheckToolChanges();
	
	
	return oRC;
}

//========================================================================
// SetCompatibleToolingFromDocument
//========================================================================
HRESULT CAASmiCreateUserOperationCom::SetCompatibleToolingFromDocument (const CATListOfCATUnicodeString &iToolTypeRefList,
																	    CATBaseUnknown_var& oTooling)
{
	HRESULT oRC = S_OK;	
	oTooling = NULL_var;
		
	//------------------------
	// Test input data
	//------------------------	
	int NbToolTypeRef = iToolTypeRefList.Size();	
	if (NbToolTypeRef == 0)
	{
		oRC = E_FAIL;
		return oRC;
	}
	
	//--------------------------------------------------------------
	// Get Manufacturing Resources Container
	//--------------------------------------------------------------
    CATIContainer_var spResourceContainer = NULL_var;
	CATIMfgManufacturingFactories *piFact =NULL;
	CATString ClassName("CATMfgManufacturingFactories");
	CATInstantiateComponent (ClassName,
                            CATIMfgManufacturingFactories::ClassId(),
                            (void**)& piFact);
	if (piFact)
	{
	    piFact->GetManufacturingToolFactory(spResourceContainer);
	    piFact->Release();
	}

	//--------------------------------------------------------------
	// Search for a tool in ResourceList
	//--------------------------------------------------------------	
	SEQUENCE(CATBaseUnknown_ptr) DocToolsList;
	if (!!spResourceContainer)

// VIOI - mkCheckSource error filtered (ListMembersHere)
// @CSC-Filter VIOI

	    spResourceContainer->ListMembersHere(CATIMfgTool::ClassName(),DocToolsList);

	int NbDocTool = DocToolsList.length();	
	if(NbDocTool)
	{
		CATISpecObject_var DocToolSpec;
		CATUnicodeString   DocToolType;
		
		int iDocTool = DocToolsList.length() - 1;
		while (NULL_var == oTooling && iDocTool >= 0)
		{  
			DocToolSpec = DocToolsList[iDocTool];
			DocToolType = DocToolSpec->GetType();
			DocToolType = DocToolType.Strip(CATUnicodeString::CATStripModeBoth, ' ');
			
			if(iToolTypeRefList.Locate(DocToolType) > 0)
			{  
				// Tool found
				CATBaseUnknown_var spDocTool(DocToolSpec);
				if (!!spDocTool)
				{ 
					oTooling = spDocTool;
				}  
			}			
			iDocTool--;			
		} 
				
		// Release of all container's object
		for (int i = 0; i < NbDocTool  ; i++)
			DocToolsList[i]->Release();
	}
		
	//--------------------------------------------------------------
	// Set found tool
	//--------------------------------------------------------------	
	if(!!oTooling && !!_spCreatedActivity)
	{
		CATIMfgActivity * pActivity = NULL;
		oRC = _spCreatedActivity->QueryInterface(IID_CATIMfgActivity, (void**) &pActivity);
		if (SUCCEEDED(oRC))
		{
			oRC = pActivity->SetTool(oTooling);  
			
			pActivity->Release();
			pActivity = NULL;
		}
	}
	else
        oRC = E_FAIL;
	
	return oRC;
}





