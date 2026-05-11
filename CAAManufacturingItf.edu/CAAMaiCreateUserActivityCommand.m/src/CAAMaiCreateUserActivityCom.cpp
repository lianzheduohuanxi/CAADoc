/**
	*@quickreview PFE SMU 05:04:19
	*@quickreview DCN CVR 04:03:10
	*@quickreview NNU 03:03:11
	*/
// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAEMaiCreateUserActitvityCom:
//
// Sample code for : CAA Manufacturing
// Mission         : Command that create and sequence an operation in the selected program.
//                   Depending on the setting, this command can launch the edition panel
//					 of the operation, and associate a default tool to the operation
//                   by creating a default tool or by retrieving the last possible tool used in
//                   the program or by retrievimg a compatible tool in the resources list.
//                   
//
// Type            : Interactive functionality
//
// How to run it   : 1-You need the Use Case CAAMaiGenerateUserActivityCatalog in order to generate 
//                     a ne type of operation ("UserActivity") in a new catalog of activity.
//                   2-Build the CAAEMaiCreateUserActitvityCommand library.
//                     In this library ther is the code that defines the command, and the code
//                     for an add-in in Prismatic Machining Workbench, to define a new command
//                     header "User Activity" that will enable you to instanciate an operation
//					   "UserActivity" in a manufacturing program.
//                   3-Create the runtime view.
//					 4-Launch CATIA.
//                   5-Enter in Prismatic machining workbench in NC Manufacturing workshop.
//                   6-Click on the "User Activity" Command
//                   7-Select the program
//
//						=> A new activity "UserActivity.1" will appear in the graph. You will be abble 
//                         to edit this operation. By default, there is three TabPages in the edition
//                         panel. First one is the stratregy parameters editor (You will see the two
//                         parameters defined in the activity catalog 
//                         see Use Case CAAMaiGenerateUserActivityCatalog).
//                         The second one corresponds to the geometry tabpage (By default it is empty).
//                         The last one correspond to the Tool tabpage.
//                         You will be able to overload each one of them.
//
//=============================================================================
//=============================================================================
// 
// Create User Activity Command 
//
//============================================================================= 
//=============================================================================
//
// Interfaces CATIA
#include "CATISpecObject.h"
#include "CATISPPActivityType.h"
#include "CATIEdit.h"
#include "CATString.h"
#include "CATBaseUnknown.h"
#include "CATPathElementAgent.h"
#include "CATPathElement.h"
#include "CATGetEnvValue.h"
#include "CATLib.h"
#include "CATBSTR.h"
#include "CATISPPActivityRoot.h"
#include "CATISPPProcessContainer.h"
#include "CATInstantiateComponent.h"

// Interfaces Mfg
#include "CATIMfgManufacturingSettings.h"
#include "CATIMfgActivity.h"
#include "CATIMfgTool.h"
#include "CATIMfgToolActivity.h"
#include "CATIAManufacturingProgram.h"
#include "CATIAManufacturingOperation.h"
#include "CATIMfgNCProgram.h"
#include "CATIMfgManufacturingFactories.h"
#include "CATIMfgActivityDefaultValuesMngt.h"
#include "CATMfgNewUserActEdit.h"


// Includes
#include "CAAMaiCreateUserActivityCom.h" 

#include "CATCreateExternalObject.h"
CATCreateClassArg(CAAMaiCreateUserActivityCom, CATString);

//========================================================================
// Constructor
//========================================================================
CAAMaiCreateUserActivityCom::CAAMaiCreateUserActivityCom(CATString* argument):CATStateCommand ("CreateUserAct")
{ 
	_CreatedActivity = NULL_var;
	
	_RootContainer = NULL_var;
	_ResourceContainer  = NULL_var;
	_ActAcq    =  NULL;
	_InitState =  NULL;

	_TypeToCreate = CATUnicodeString (*argument);
	
	// Get Manufacturing Resources Container
	CATIMfgManufacturingFactories *piFact =NULL;

	CATString ClassName("CATMfgManufacturingFactories");
	CATInstantiateComponent (ClassName,
                            CATIMfgManufacturingFactories::ClassId(),
                            (void**)& piFact);
	if (piFact)
	  {
	    HRESULT RC = piFact->GetManufacturingToolFactory(_ResourceContainer);
	    piFact->Release();
	  }
	
	// Init of selection agent for father activity	
	_ActAcq = new CATPathElementAgent("Act");
	
	if (NULL != _ActAcq)
	{
		_ActAcq->SetElementType(CATIMfgActivity::ClassName());
		
		_ActAcq->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithPrevaluation|CATDlgEngWithCSO|CATDlgEngWithUndo);
	}
}


//========================================================================
// Destructor
//========================================================================

CAAMaiCreateUserActivityCom::~CAAMaiCreateUserActivityCom()
{
	
	if(NULL != _ActAcq) _ActAcq->RequestDelayedDestruction();    
	_ActAcq = NULL;
	if(NULL != _InitState) _InitState->Release();    
	_InitState = NULL;

}

//========================================================================
// Build Graph
//========================================================================

void CAAMaiCreateUserActivityCom::BuildGraph()
{  
	// Initial State
	
	AddCSOClient(_ActAcq);
	
	CATDialogState* _InitState = GetInitialState("InitState"); 
	if (NULL != _InitState)
		_InitState->AddDialogAgent(_ActAcq);
    
	if (NULL != _ActAcq)
		AddTransition (_InitState, NULL, IsOutputSetCondition(_ActAcq),
        Action((ActionMethod)& CAAMaiCreateUserActivityCom::ManageChildActivityAndSequence));
    
	return;
}

//========================================================================
// ManageChildActivityAndSequence
//========================================================================

boolean CAAMaiCreateUserActivityCom::ManageChildActivityAndSequence (void *)
{  
	HRESULT RC = S_OK;
	
	CATTry
	{    
		// -----------------------------------------------
		// Load the User Activities Catalog
		// -----------------------------------------------
		char  *oGraphicPath= NULL;
		CATString CatalogName ("UserActivityCatalog.CATfct");
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
		// Searching for a good father if no activity selected
		// -----------------------------------------------
		CATIMfgActivity_var SelectedMfgActivity = SelectedObj;
		
		CATBaseUnknown_var AuthorizedActivityFather; 
		CATIMfgActivity_var ReferenceActivity(SelectedMfgActivity);
		
		AuthorizedActivityFather = FindActivityFather(_TypeToCreate, ReferenceActivity);    
		
		if(! AuthorizedActivityFather)
		{
			// Impossible Operation 
			return FALSE;
		}
		
		
		// ***********************************************************************
		//               Creation + sequencing of activity
		// ***********************************************************************
		
		
		CATIAManufacturingProgram_var SeqFather(AuthorizedActivityFather);
		
		int AutoSequence=1;
		CATIAManufacturingOperation* oManufacturingOperation=NULL;
		CATBSTR TypeToCreate;
		_TypeToCreate.ConvertToBSTR (&TypeToCreate);
		
		RC = SeqFather->AppendOperation (TypeToCreate, AutoSequence, oManufacturingOperation);  
		if(FAILED(RC))
		{
			return FALSE;
		}
		CATIAManufacturingOperation_var CreatedActivity(oManufacturingOperation);
		if (!!CreatedActivity) CreatedActivity->Release();
		_CreatedActivity = CreatedActivity;
		
		if(! _CreatedActivity)
		{
			return FALSE;
		}
		
		// ***********************************************************************
		//               Update after creation (Tool...)
		// ***********************************************************************    
		
		SetLinksAndDataOnActivity(_CreatedActivity);        
		
	}
	
	CATCatch (CATError, Error);
	{
		return FALSE;
	}
	
	CATEndTry;
	
	return TRUE;
}

//========================================================================
// FindActivityFather
//========================================================================

CATBaseUnknown_var CAAMaiCreateUserActivityCom::FindActivityFather(CATUnicodeString &iTypeToCreate, CATBaseUnknown_var &RefActivity)
{
	
	// ***********************************************************************
	//           	 Read Father Activity
	// ***********************************************************************
	
	CATBaseUnknown_var oAuthorizedActivityFather(NULL_var);
	CATBaseUnknown_var FatherChildActivity(NULL_var);
	
	CATIMfgActivity_var RefMfgActivity(RefActivity); 
	
	HRESULT RC = S_OK;
	
    
	RC = RefMfgActivity->GetAuthorizedFatherActivity(iTypeToCreate,oAuthorizedActivityFather,FatherChildActivity); 
    
	if(SUCCEEDED (RC))
    {
		if(!!oAuthorizedActivityFather)
		{ 
			if(oAuthorizedActivityFather != RefMfgActivity && !!FatherChildActivity)
			{   
				RefActivity = FatherChildActivity;
			}  
		} 
    }
	
	return oAuthorizedActivityFather;
}
//========================================================================
// SetLinksAndDataOnActivity
//========================================================================

void CAAMaiCreateUserActivityCom::SetLinksAndDataOnActivity(CATBaseUnknown_var &iActivity)
{
	
	HRESULT RC = E_FAIL;
	
	CATIMfgActivity_var NewMfgAct(iActivity);
	
    // ********************************************************************
	// Default Values Initialization
	// ********************************************************************

	int UseBlockInit=0;
    CATIMfgActivityDefaultValuesMngt_var ActDV (iActivity);
    if (NULL_var != ActDV)
	{ 
      RC = ActDV->ManageDefaultValues(1,UseBlockInit);
	}



	RC = NewMfgAct->SetCreationMode(CATIMfgActivity::Manually);
	
	// ********************************************************************
	// Tool Initialization
	// ********************************************************************
	
	int NewOpIsSequencedInProgram = NewMfgAct->IsSequencedInProgram();	  
	if(NewOpIsSequencedInProgram == 1)
	{	
		
		RC = InitTool (NewMfgAct);
		
	}       
	
	// ********************************************************************
	// Add Activity in CSO 
	// ********************************************************************
	
	int AutoEditOper = 1;
	
	CATIMfgManufacturingSettings *piSetting =NULL;

	CATString ClassName("CATMfgManufacturingSettings");
	CATInstantiateComponent (ClassName,
                            CATIMfgManufacturingSettings::ClassId(),
                            (void**)& piSetting);
	if (piSetting)
	  {
	    RC = piSetting->GetStartEditModeSetting(AutoEditOper);
	    piSetting->Release();
	  }
	

	
	// --------------------------------------------------------------------
	// Update The Operation
	// --------------------------------------------------------------------
	RC = NewMfgAct->Update();          
	
	// --------------------------------------------------------------------
	// If Panel Edition has to be open when creating the operation
	// --------------------------------------------------------------------
	if(AutoEditOper == 1)
	{
		
		// --------------------------------------------------------------------
		// Edition of Operation  
		// --------------------------------------------------------------------
		
		// Edition
		CATPathElement *Path = new CATPathElement;
		CATBaseUnknown_var NewMfgAct2 (NewMfgAct);
		if (Path) Path->AddChildElement (NewMfgAct2);
		
		CATIEdit_var Edit(NewMfgAct);
		if (NULL_var != Edit)
		{
			// To allow the activity being deleted on cancel of Edit Command. Remove the comment before next line.
			// MfgNewUserActEdit = 1;
			Edit->Activate (Path);
		}
      if (NULL != Path) Path->Release();
      Path = NULL;
		
	}
	
	
	return;
}

//========================================================================
// InitToolOnActivity
//========================================================================
HRESULT CAAMaiCreateUserActivityCom::InitTool (const CATBaseUnknown_var& iActivity)
{
	
	HRESULT oRC = S_FALSE;
	
	CATIMfgToolActivity_var ToolAct(iActivity);
	if (!ToolAct) 
	{
		return oRC;    
	}
	
	
	if (!_ResourceContainer)
	{
		oRC = E_FAIL;
		return oRC;    
	}
	
	
	CATBaseUnknown_var ToolingSetOnActivity(NULL_var);
	
	const boolean doNotCheckToolChanges = FALSE;
	
	CATIMfgActivity_var MfgAct(iActivity);
	
	//------------------------
	// Tool management
	//------------------------
	CATListOfCATUnicodeString ToolTypeList;
	oRC = ToolAct->GetAuthorizedToolTypeList (ToolTypeList);
	if(FAILED(oRC) && ToolTypeList.Size() == 0)
	{
		return oRC;    
	}
	
	// --------------------------------------------------------------------
	// Settings for tool searching
	// --------------------------------------------------------------------
	int SearchToolInProgram = 1;
	
	CATIMfgManufacturingSettings *piSetting =NULL;

	CATString ClassName("CATMfgManufacturingSettings");
	CATInstantiateComponent (ClassName,
                            CATIMfgManufacturingSettings::ClassId(),
                            (void**)& piSetting);
	if (piSetting)
	  oRC = piSetting->GetSearchToolInProgramSetting(SearchToolInProgram);

  
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
    
    
	if(SearchToolInProgram)
    { 
		// *******************************************************************
		// Associate tool to the operation
		// *******************************************************************
		CATBaseUnknown_var CurProgram(NULL_var);
		 oRC = MfgAct->GetProgram(CurProgram);

		CATIMfgNCProgram_var CurrentProgram(CurProgram);
		oRC = CurrentProgram->SetCurrentAuthorizedTool (MfgAct);
		if(oRC == S_OK)
		{
		  ToolingSetOnActivity = MfgAct->GetTool();
		}
		
    } 
	
	
	if (!ToolingSetOnActivity)
    {
		int CreateDefTool = 1;
		
		if (piSetting)
		  oRC = piSetting->GetCreateDefaultToolSetting(CreateDefTool);
		
		if(CreateDefTool)
		{  
			// *******************************************************************
			// Search tool in document or create a default one
			// *******************************************************************
			CATBaseUnknown_var CompatibleToolingSetOnActivity;
			oRC = SetCompatibleToolingFromDocument (ToolTypeList, CompatibleToolingSetOnActivity);
			if(oRC != S_OK)
			{   
				// no compatible tool in document
				// create a default one
				//-----------------------------------------------------------------------
				CATBaseUnknown_var DefaultToolToSet;
				
				oRC =  ToolAct->CreateDefaultTool (DefaultToolToSet);	      
				
				if(!!DefaultToolToSet)
				{     
					oRC = MfgAct->SetTool(DefaultToolToSet, doNotCheckToolChanges);
					if(SUCCEEDED(oRC))
						ToolingSetOnActivity = DefaultToolToSet;
				} 
			} 
			else
			{ 
				ToolingSetOnActivity = CompatibleToolingSetOnActivity;
			} 
		}
    }
	
	//----------------------------------------------
	// Update ToolChanges if necessary
	//----------------------------------------------
	if(!!ToolingSetOnActivity) 
		MfgAct->CheckToolChanges();
	
 	if (piSetting) piSetting->Release();
	
	return oRC;
}

//========================================================================
// SetCompatibleToolingFromDocument
//========================================================================
HRESULT CAAMaiCreateUserActivityCom::SetCompatibleToolingFromDocument (const CATListOfCATUnicodeString &iToolTypeRefList,
																	   CATBaseUnknown_var& oTooling)
{
	HRESULT oRC = S_OK;
	
	oTooling = NULL_var;
	
	
	CATIMfgActivity_var MfgAct(_CreatedActivity);
	if(! MfgAct)
	{
		oRC = E_FAIL;
		return oRC;
	}
	
	int NbToolTypeRef = iToolTypeRefList.Size();
	
	if(! NbToolTypeRef)
	{
		oRC = E_FAIL;
		return oRC;
	}
	
	//--------------------------------------------------------------
	// Search for a tool in ResourceList
	//--------------------------------------------------------------
	if(!_ResourceContainer)
	{
		oRC = E_FAIL;
		return oRC;
	}
	
	CATBaseUnknown_var DocToolBase;
	CATISpecObject_var DocToolSpec;
	CATUnicodeString   DocToolType;

    // @CSC-Filter VIOI  mkCheckSource error filtered: do not remove or move comment link to next line   
	SEQUENCE(CATInterfaceObject_ptr) DocToolsList  = _ResourceContainer->ListMembers(CATIMfgTool::ClassName());
	
	int NbDocTool = DocToolsList.length();
	
	if(NbDocTool)
	{
		int iDocTool = DocToolsList.length() - 1;
		while (!oTooling && iDocTool >= 0)
		{  
			DocToolSpec = DocToolsList[iDocTool];
			DocToolType = DocToolSpec->GetType();
			DocToolType = DocToolType.Strip(CATUnicodeString::CATStripModeBoth, ' ');
			
			if(iToolTypeRefList.Locate(DocToolType) > 0)
			{  
				// Tool found
				//--------------------------------------------------------------
				CATBaseUnknown_var DocTool(DocToolSpec);
				if (!!DocTool)
				{ 
					oTooling = DocTool;
				}  
			}
			
			iDocTool--;
			
		} 
		
		
		// Release of all container's object
		for (int i = 0; i < NbDocTool  ; i++)
			DocToolsList[i] -> Release();
	}
	
	
	if(!!oTooling)
	{
		oRC = MfgAct->SetTool(oTooling);   
		return oRC;
	}
	
	if(!oTooling) oRC = S_FALSE;
	
	return oRC;
}





