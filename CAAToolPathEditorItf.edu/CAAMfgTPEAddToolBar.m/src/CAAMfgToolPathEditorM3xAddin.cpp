// COPYRIGHT DASSAULT SYSTEMES 2001
// ===================================================================
//
// CAAMfgToolPathEditorM3xAddin:
//
// Sample code for : CAA ToolPathEditor
// Mission         : Implementation of the interface CATISmgProgramAddin to create 
//                   an add-in in the Surfacic Machining Workbench.
//					 We want to add a new toolbar in this workbench in order to be able to
//                   add new commands in the tool path editor.
//
// Type            : Interactive functionality.
//
// How to run it   : 1-You need the Use Case CAATPEAddToolBar in order to generate 
//                     a new toolbar
//                   2-Build the CAATPEAddToolBar library.
//                     In this library there is the code that defines a new command, and the code
//                     for an add-in in Surfacic Machining Workbench, to define a new command
//                     header that will enable you to display a distance between two points of 
//                     a tool path.
//                     You need to generate all the Use Cases f the framewor CAAToolPathEditor.edu.
//                   3-Create the runtime view.
//					 4-Launch CATIA.
//                   5-Enter in Surfacic machining workbench in NC Manufacturing workshop.
//                   6-a new tool abr is displayed with two commands.
//
//
//=============================================================================
// Local Framework
// Local Framework
#include "CAAMfgToolPathEditorM3xAddin.h"
 
#include <CATCreateWorkshop.h>   
#include "CATCommandHeader.h"        
MacDeclareHeader(CAAMfgTPEUserCommandHeader);

// Implement the interface CATISmgProgramAddin to create an add-in in the Surfacic Machining Workbench
#include <TIE_CATISmgProgramAddin.h>
TIE_CATISmgProgramAddin(CAAMfgToolPathEditorM3xAddin);

CATImplementClass(CAAMfgToolPathEditorM3xAddin, DataExtension, CATBaseUnknown, CAAMfgTPEM3xAddin);

CAAMfgToolPathEditorM3xAddin::CAAMfgToolPathEditorM3xAddin()
{}

CAAMfgToolPathEditorM3xAddin::~CAAMfgToolPathEditorM3xAddin()
{}

void CAAMfgToolPathEditorM3xAddin::CreateCommands()
{		

// Creation of User's Commands headers

	static CATString TPEDisplayToolPath ("TPEDisplayToolPath");
	new CAAMfgTPEUserCommandHeader ( "TPEDisplayToolPath",
												"CAAMfgTPEDisplayToolPathCommand",
												"CAAMfgTPEDisplayToolPathCom",
												(void *)&TPEDisplayToolPath); 

	static CATString TPESplitToolPath ("TPESplitToolPath");
	new CAAMfgTPEUserCommandHeader ( "TPESplitToolPath",
												"CAAMfgTPESplitToolPathCommand",
												"CAAMfgTPESplitToolPathCom",
												(void *)&TPESplitToolPath); 

	static CATString TPEDisplayDistance ("TPEDisplayDistance");
	new CAAMfgTPEUserCommandHeader ( "TPEDisplayDistance",
												"CAAMfgTPEAddToolBar",
												"CAAMfgTPEDisplayDistanceCom",
												(void *)&TPEDisplayDistance); 

	// Command of the cut area Tool Bar.
	static CATString TPEOnePointSelectionUser ("TPEOnePointSelectionUser");
	new CAAMfgTPEUserCommandHeader ( "TPEOnePointSelectionUser",
												"CAAMfgTPEAddCmdInCutAreaToolBar",
												"CAAMfgTPEOnePointSelectionUserCom",
												(void *)&TPEOnePointSelectionUser); 

	static CATString TPEPolylineSelectionUser ("TPEPolylineSelectionUser");
	new CAAMfgTPEUserCommandHeader ( "TPEPolylineSelectionUser",
												"CAAMfgTPEAddCmdInCutAreaToolBar",
												"CAAMfgTPEPolylineSelectionUserCom",
												(void *)&TPEPolylineSelectionUser); 

}

CATCmdContainer * CAAMfgToolPathEditorM3xAddin::CreateToolbars()
{

// ---------------------------------------------------------
// Creation of User Toolbar
// ---------------------------------------------------------
   NewAccess(CATCmdContainer,PaletteTPEUserCommand,ToolPathEditorUserToolBar);
	SetAccessTitle(PaletteTPEUserCommand,"Tool Path Editor User Tool Bar");
	AddToolbarView(PaletteTPEUserCommand,1,Right);

// ---------------------------------------------------------
// Creation of User's Commands
// ---------------------------------------------------------
	{
		// Split tool path command
		NewAccess(CATCmdStarter,SplitToolPath,TPESplitToolPath);
		SetAccessCommand(SplitToolPath,"TPESplitToolPath");

		// DisplayDistance command
		NewAccess(CATCmdStarter,DisplayDistance,TPEDisplayDistance);
		SetAccessCommand(DisplayDistance,"TPEDisplayDistance");

		// DisplayDistance command
		NewAccess(CATCmdStarter,DisplayToolPath,TPEDisplayToolPath);
		SetAccessCommand(DisplayToolPath,"TPEDisplayToolPath");

		SetAccessChild(PaletteTPEUserCommand,SplitToolPath);
		SetAccessNext (SplitToolPath, DisplayDistance);
		SetAccessNext (DisplayDistance, DisplayToolPath);
	}

	return PaletteTPEUserCommand;
}



