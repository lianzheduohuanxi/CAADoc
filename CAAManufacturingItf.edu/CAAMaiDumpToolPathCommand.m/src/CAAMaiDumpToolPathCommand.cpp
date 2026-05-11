// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAMaiDumpToolPathCommand:
//
// Sample code for : CAA Manufacturing
// Mission         : Command that dumps the content of the tool path stored on an operation.
//                   The command can be set as a user command in order to be called in each
//                   Manufacturing product.
//                   The source of this command is helpful to understand , for a CAA developer,
//                       how to access datas of the tool path.
//                   
// Type            : Interactive functionality
//
// How to run it   : 1-Build the CAAMaiDumpToolPathCommand library.
//                   2-Launch CATIA.
//					 3-Add the command as a user command.
//                   4-Enter in Prismatic machining workbench (for example) in NC Manufacturing workshop.
//                   5-Select an operation
//                   6-Click on the command
//
//=============================================================================

#include "CAAMaiDumpToolPathCommand.h" 

//Infrastructure headers
#include "CATPathElement.h"
#include "CATPathElementAgent.h"
#include "CATLib.h"

//Manufacturing headers
#include "CATIMfgActivity.h"
#include "CATIMfgToolPathManagement.h"
#include "CATIMfgCompoundTraject.h"
#include "CATIMfgToolPathCycle.h"
#include "CATIMfgTPCycleLinkingMotion.h"
#include "CATIMfgToolPathMotionCommand.h"

//Local headers
#include "CAAMaiDumpRotation.h"
#include "CAAMaiDumpCompoundTraject.h"
#include "CAAMaiDumpCycle.h"

//Declared as a command
#include "CATCreateExternalObject.h"
CATCreateClassArg(CAAMaiDumpToolPathCommand, CATString);

FILE* CAAMaiDumpToolPathCommand::_File = NULL;

//========================================================================
// Constructor
//========================================================================
CAAMaiDumpToolPathCommand::CAAMaiDumpToolPathCommand(CATString* argument)
:CATStateCommand ()
{ 
	//===============================================
	// Init of selection agent for activity	selection
	//===============================================
	_ActAcq = new CATPathElementAgent("Act");
	_ActAcq->SetElementType(CATIMfgActivity::ClassName());
	_ActAcq->SetBehavior(CATDlgEngWithPrevaluation|CATDlgEngWithCSO);
}

//========================================================================
// Destructor
//========================================================================
CAAMaiDumpToolPathCommand::~CAAMaiDumpToolPathCommand()
{
	//======================
	// Close the report file
	//======================
	if (_File) fclose(_File);
	_File = NULL;
	
	if(_ActAcq) _ActAcq->RequestDelayedDestruction();    
	_ActAcq = NULL;
}

//========================================================================
// Build Graph
//========================================================================
void CAAMaiDumpToolPathCommand::BuildGraph()
{  
	if (NULL!=_ActAcq)
	{
		AddCSOClient(_ActAcq);
		CATDialogState* InitState = GetInitialState("InitState");  
		if (NULL!=InitState)
		{
			InitState->AddDialogAgent(_ActAcq);
 
			AddTransition (InitState, NULL, IsOutputSetCondition(_ActAcq),
			  Action((ActionMethod)& CAAMaiDumpToolPathCommand::DumpToolPath));
		}
	}
	return;
}




//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// DumpToolPath
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CATBoolean CAAMaiDumpToolPathCommand::DumpToolPath (void *)
{
	//========================================
	// Creates log file in temporary directory
	//========================================
	const char* cTemporaryDirectory = CATGetTempDirectory ();
    char cNom_complet[CATMaxPathSize];
	CATUnicodeString sFileName ("DumpToolPath.txt");
	CATMakePath (cTemporaryDirectory,sFileName.ConvertToChar(),cNom_complet);
	CATUnicodeString sNom_complet (cNom_complet);

	_File = fopen (sNom_complet.ConvertToChar(),"w");

	//============================
	// Retrieves selected activity
	//============================
	CATBaseUnknown_var SelectedObj = _ActAcq -> GetElementValue();	

	//=========================================
	// Retrieves tool path on selected activity
	// --> End if no tool path found
	//=========================================
	CATIMfgToolPathManagement_var Manage (SelectedObj);
	if (NULL_var == Manage) 
	{
		CATUnicodeString String (">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> No Tool path on selected object");
		CAAMaiWriteString (0,String);
		return FALSE;
	}

	CATIMfgToolPath_var ToolPath;
	Manage->GetToolPath (ToolPath);
	if (NULL_var == ToolPath)
	{
		CATUnicodeString String (">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> No Tool path on selected object");
		CAAMaiWriteString (0,String);
		return FALSE;
	}

    //========================================================
	// Retrieves CATIMfgCompoundTraject interface on tool path
	//========================================================
	CATIMfgCompoundTraject_var CompoundTraject (ToolPath);
	if (NULL_var == CompoundTraject)
	{
		CATUnicodeString String (">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> CATIMfgCompoundTraject interface not found");
		CAAMaiWriteString (0,String);
		return FALSE;
	}
	
	//================================
	// Checks consistency of tool path
	//================================
	HRESULT RC = CompoundTraject->CheckToolPath();
	if (S_OK==RC)
	{
        CATUnicodeString String ("--> Tool Path consistent");
		CAAMaiWriteString (0,String);
	}
	else
	{
		CATUnicodeString String ("--> Tool Path not consistent");
		CAAMaiWriteString (0,String);
	}

	//============================================================
	// Loads PP Table for current activity (for syntax evaluation)
	//============================================================
	CompoundTraject->LoadsPPTable (SelectedObj);

	//==================================================================
	// Dump of the tool path
	// Three cases are possible :
	// 1) The element is a CATIMfgToolPathMotionCommand object (rotation)
	// 2) The element is a CATIMfgToolPathCycle object (machining cycle)
	// 3) The element is only a CATIMfgCompoundTraject object
	//==================================================================
	CATIMfgToolPathCycle_var Cycle (ToolPath);
	CATIMfgToolPathMotionCommand_var Rotation (ToolPath);
	if (NULL_var != Rotation)
	{
		//=================================================
		// The object is a CATIMfgToolPathMotionCommand one
		//=================================================
		CATUnicodeString text1;
		text1.Resize(60,'=');
		CAAMaiWriteString (0,text1);
		CATUnicodeString text2 ("=========== Dump of CATIMfgToolPathMotionCommand object ============");
		CAAMaiWriteString (0,text2);
		CAAMaiWriteString (0,text1);
		CAAMaiDumpRotation (0,Rotation);                        // see CAAMaiDumpRotation.cpp
	}
	else if (NULL_var != Cycle)
	{
		//=========================================
		// The object is a CATIMfgToolPathCycle one
		//=========================================
		CATUnicodeString text1;
		text1.Resize(60,'=');
		CAAMaiWriteString (0,text1);
		CATUnicodeString text2 ("=========== Dump of CATIMfgToolPathCycle object ============");
		CAAMaiWriteString (0,text2);
		CAAMaiWriteString (0,text1);
		CAAMaiDumpCycle (0,Cycle);                              // see CAAMaiDumpCycle.cpp
	}
	else if (NULL_var != CompoundTraject)
	{
		//===========================================
		// The object is a CATIMfgCompoundTraject one
		//===========================================
		CATUnicodeString text1;
		text1.Resize(60,'=');
		CAAMaiWriteString (0,text1);
		CATUnicodeString text2 ("=========== Dump of CATIMfgCompoundTraject object ==========");
		CAAMaiWriteString (0,text2);
		CAAMaiWriteString (0,text1);
		CAAMaiDumpCompoundTraject (0,CompoundTraject);          // see CAAMaiDumpCompoundTraject.cpp
	}
	else return FALSE;

	//===============
	// End of command
	//===============
	RequestDelayedDestruction ();

	return TRUE;
}

void CAAMaiDumpToolPathCommand::CAAMaiWriteString (int iLevel,const CATUnicodeString& iString)
{
	if (NULL == _File) return;

	CATUnicodeString String (iString);
	for (int i=1;i<=iLevel;i++)
	{
		String = "          " + String;
	}

	fprintf (_File,"%s\n",String.ConvertToChar());
}


//========
// Private
//========
void CAAMaiDumpToolPathCommand::Valuate (const CATBaseUnknown_var& iActivity)
{
  if (_ActAcq) 
  {
     CATPathElement * pPath = new CATPathElement (iActivity);
     if (pPath)
     {
        _ActAcq->SetValue (pPath);
        _ActAcq->SetValuation();
        pPath->Release();
        pPath=NULL;
     }
  }
}
