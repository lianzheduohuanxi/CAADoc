// COPYRIGHT DASSAULT SYSTEMES 2000
//==============================================================================================
//
// CAAMaiToolEditionCustomizationDrillTool:
//
// Sample code for : Manufacturing Modeler
// Mission         : Customize the Drilling Tool Editor
//
//
// Type            : Interactive functionality
//
// Illustrates     : 1- use of manufacturing interfaces 
//                   2- read tool parameters
//                   3- Editor creation 
//
// How to run it   : Set up the run time environment 
//						In the file CAAManuturingItf.edu.dico, decomment the following line  
//						MfgDrillTool  CATIMfgToolEditorCustom   libCAAMaiToolEditionCustomization
//                   
//                   Launch a CATIA V5 session 
//                   Open the CAAMaiToolEditionCustomization.CATPart file located in: Windows InstallRootDirectory\CAAManufacturingItf.edu\CNext\resources\graphic\ 
//					 
//					 Start Prismatic Machining Workbench
//                   Create a Drill Tool Change and see the Tool editor
//
//
//==============================================================================================
#include "CAAEMaiToolEditionCustomizationDrillTool.h"

// Manufacturing Interfaces Framework
#include "CATIMfgTool.h"                // For Tool management
#include "CATMfgResourceConstant.h"     // For Resource constant declarations
#include "CATMfgToolConstant.h"         // For Tool constant declaration

// Dialog Framework
#include "CATDlgInclude.h"              // For Dialog components

// LiteralFeatures Framework 
#include "CATICkeParamFrame.h"          // For Editors dedicated to literals

// System Framework
#include "CATMsgCatalog.h"              // For NLS messages management

//-----------------------------------------------------------------------------
// Supported Interfaces
//-----------------------------------------------------------------------------
//	In the file CAAManuturingItf.edu.dico, the following line must be available  
//	MfgDrillTool  CATIMfgToolEditorCustom   libCAAMaiToolEditionCustomization
#include "TIE_CATIMfgToolEditorCustom.h"
TIE_CATIMfgToolEditorCustom(CAAEMaiToolEditionCustomizationDrillTool);
CATImplementClass(CAAEMaiToolEditionCustomizationDrillTool,
                  DataExtension,                  
                  CATBaseUnknown,
                  CATEMfgDrillTool);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAAEMaiToolEditionCustomizationDrillTool::CAAEMaiToolEditionCustomizationDrillTool()
:CATBaseUnknown()
{
}
//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAAEMaiToolEditionCustomizationDrillTool::~CAAEMaiToolEditionCustomizationDrillTool()
{
}
//-----------------------------------------------------------------------------
// GetPanelEditor
// This method allows to get the Tool editor view
// that will be displayed when editing the tool 
// through ResourceList access (simple view)
//-----------------------------------------------------------------------------
CATDlgFrame* CAAEMaiToolEditionCustomizationDrillTool::GetPanelEditor
													(CATDialog *iParent, 
													 CATDlgStyle iStyle, 
													 const CATBoolean iMode)
{
	//-----------------------------------------------------------
	// Create a Dialog Frame
	//-----------------------------------------------------------
	CATDlgStyle Style = CATDlgFraNoFrame;
	CATDlgFrame *pFr = new CATDlgFrame (iParent, CATString("theFrame"), Style);
	
	if (CATFalse == iMode) pFr->SetSensitivity(CATDlgDisable);
	pFr->SetDefaultOrientation(Horizontal);

	//-----------------------------------------------------------
	// Get the graphic editor
	//-----------------------------------------------------------
	CATDlgFrame *pGrFrame = GetGraphicEditor (pFr);

	//-----------------------------------------------------------
	// Describe the list of Tool attributes to be displayed
	// Constants are described in CATMfgResourceConstant.h and 
	//                            CATMfgToolConstant.h
	//-----------------------------------------------------------
	CATListOfCATUnicodeString ListNames;
	ListNames.Append (MfgName);
	ListNames.Append (MfgNominalDiameter);
	ListNames.Append (MfgCuttingLength);
	ListNames.Append (MfgCuttingAngle);
	ListNames.Append (MfgOverallLength);
	ListNames.Append (MfgLength);
	ListNames.Append (MfgBodyDiameter);
	
	//-----------------------------------------------------------
	// Build the Frame content
	//-----------------------------------------------------------
	CATDlgFrame *pFrAtt = new CATDlgFrame (pFr, CATString("Frame"), Style);
	pFrAtt->SetDefaultOrientation(Vertical);

	BuildFrame (pFrAtt, ListNames);

	return (pFr);
}
//-----------------------------------------------------------------------------
// GetMorePanelEditor
// This method allows to get the Tool editor view
// that will be displayed when editing the tool 
// through ResourceList access with selection of the button "more" (advanced view)
//---------------------------------------------------------------------------
CATDlgFrame* CAAEMaiToolEditionCustomizationDrillTool::GetMorePanelEditor 
		(CATDialog *iParent, CATDlgStyle iStyle, const  CATBoolean   iMode)
{
	//-----------------------------------------------------------
	// Create a Dialog Frame
	//-----------------------------------------------------------
	CATDlgFrame *pFr = new CATDlgFrame (iParent, CATString("theFrame"), iStyle);
	if (CATFalse == iMode) pFr->SetSensitivity(CATDlgDisable);
	pFr->SetDefaultOrientation(Vertical);

	//-----------------------------------------------------------
	// Describe the list of Tool attributes to be displayed
	// Constants are described in CATMfgResourceConstant.h and 
	//                            CATMfgToolConstant.h
	//-----------------------------------------------------------
	CATListOfCATUnicodeString ListNames;
	ListNames.Append (MfgNumberOfFlutes);
	ListNames.Append (MfgToolRakeAngle);
	ListNames.Append (MfgWayOfRotation);
	ListNames.Append (MfgToothMat);
	ListNames.Append (MfgMachQuality);
	ListNames.Append (MfgMaxMilTime);
	ListNames.Append (MfgMaxMilLength);
	ListNames.Append (MfgCoolantSyntax);	
	ListNames.Append (MfgWeightSyntax);

	BuildFrame (pFr, ListNames);

	return (pFr);
}
//-----------------------------------------------------------------------------
// GetGraphicEditor
// This method allows to get the Tool graphic view
// That can be an icon (at least displayed during Tool selection)
//---------------------------------------------------------------------------
CATDlgFrame* CAAEMaiToolEditionCustomizationDrillTool::GetGraphicEditor 
		(CATDialog *iParent, CATDlgStyle iStyle, const  CATBoolean iMode)
{
	//-----------------------------------------------------------
	// Create a Dialog Frame
	//-----------------------------------------------------------
	CATDlgFrame *pFr = new CATDlgFrame (iParent, CATString("theFrame"), iStyle);
	if (CATFalse == iMode) pFr->SetSensitivity(CATDlgDisable);
	pFr->SetDefaultOrientation(Vertical);

	//-----------------------------------------------------------
	// Add the standard graphic icon
	//-----------------------------------------------------------
	CATDlgLabel *pLab = new CATDlgLabel (pFr, CATString("Lab"));
	CATString Icon("F_MfgDrillTool");
	pLab->SetIconName(Icon); 
		
	return (pFr);
}
//-----------------------------------------------------------------------------
// GetActivityEditor
// This method allows to get the Tool editor view
// that will be displayed when editing the tool 
// with access through the Activity editor (tool tab page)
//---------------------------------------------------------------------------
CATDlgFrame* CAAEMaiToolEditionCustomizationDrillTool::GetActivityEditor 
		(CATDialog *iParent, CATDlgStyle iStyle, const  CATBoolean iMode, const CATISpecObject_var &ihSpecAct)
{
	//-----------------------------------------------------------
	// Create a Dialog Frame
	//-----------------------------------------------------------
	CATDlgStyle Style = CATDlgFraNoFrame;
	CATDlgFrame *pFr = new CATDlgFrame (iParent, CATString("theFrame"), Style);
	if (CATFalse == iMode) pFr->SetSensitivity(CATDlgDisable);
	pFr->SetDefaultOrientation(Horizontal);

	//-----------------------------------------------------------
	// Get the graphic editor
	//-----------------------------------------------------------
	CATDlgFrame *pGrFrame = GetGraphicEditor (pFr);

	//-----------------------------------------------------------
	// Describe the list of Tool attributes to be displayed
	// Constants are described in CATMfgResourceConstant.h and 
	//                            CATMfgToolConstant.h
	//-----------------------------------------------------------
	CATListOfCATUnicodeString ListNames;
	ListNames.Append (MfgNominalDiameter);
	ListNames.Append (MfgCuttingLength);
	ListNames.Append (MfgCuttingAngle);
	ListNames.Append (MfgOverallLength);
	ListNames.Append (MfgLength);
	ListNames.Append (MfgBodyDiameter);
	
	CATDlgFrame *pFrAtt = new CATDlgFrame (pFr, CATString("Frame"), Style);
	pFrAtt->SetDefaultOrientation(Vertical);

	BuildFrame (pFrAtt, ListNames);

	return (pFr);
}
//-----------------------------------------------------------------------------
// GenerateJPEGImageFromGraphicEditor (not used)
//-----------------------------------------------------------------------------
void CAAEMaiToolEditionCustomizationDrillTool::GenerateJPEGImageFromGraphicEditor
		 (CATDialog *iParent, const CATUnicodeString &iImagePathName)
{
}
//-----------------------------------------------------------------------------
// BuildFrame
// Generic method to build the frame content
//-----------------------------------------------------------------------------
void CAAEMaiToolEditionCustomizationDrillTool::BuildFrame 
			(CATDlgFrame *iParent, const CATListOfCATUnicodeString &iAttributesList)
{
	//-----------------------------------------------------------
	// Retrieve the resource object 
	//-----------------------------------------------------------
	CATIMfgTool *piMfgToolOnMfgDrillTool = NULL;
	HRESULT Res = this->QueryInterface(CATIMfgTool::ClassId(), (void **)&piMfgToolOnMfgDrillTool);

	if (FAILED(Res) || NULL == piMfgToolOnMfgDrillTool) return;

	//-----------------------------------------------------------
	// Managing NLS file access 
	//-----------------------------------------------------------
	CATString CatalogName = MfgResourceNLSFile.ConvertToChar();
	CATMsgCatalog MsgCat;
	int NLSOK = MsgCat.LoadMsgCatalog(CatalogName);

	//-----------------------------------------------------------
	// For each parameter, define the standard editor
	//-----------------------------------------------------------
	CATBaseUnknown_var Parm;
	CATUnicodeString ParmName, Text, NlsText;
	CATString Key;
	CATDlgFrame *pFratt=NULL, *pFrEdt=NULL;
	CATDlgLabel *pLabEdt=NULL;

	CATDlgStyle StyleEdit = CATCkeNoRename|CATCkeWithSpinner|CATCkeNoLabel;
	for (int i=1; i<=iAttributesList.Size(); i++)
	{
		ParmName = iAttributesList[i];

		// Read into NLS file the attribute title
		//----------------------------------------------------
		if (NLSOK)
		{
			Text = ParmName;
			NlsText = MsgCat.BuildMessage (CatalogName, Key);
/*
			CATMsg Msg = MsgCat.GetCatalogMsg(CATString(ParmName));
			if (!(Msg.IsEmpty())) Text = Msg.BuildMessage();
			*/

			if (0 < NlsText.GetLengthInChar()) Text = NlsText;
			Text.Append(":");
			Text.Resize(20);
		}
		
		// Read the parameter
		//----------------------------------------------------
		HRESULT res = piMfgToolOnMfgDrillTool->GetValue(ParmName, Parm);
		if (FAILED(res) || NULL_var == Parm) return;
		
		// Define the label and editor for the tool parameter
		//----------------------------------------------------
		pFratt = new CATDlgFrame (iParent, CATString("fr"), CATDlgFraNoFrame);
		pFratt->SetDefaultOrientation(Horizontal);

		CATString name = CATString(Text);
		pLabEdt = new CATDlgLabel (pFratt,name);   

		CATICkeParamFrame_var ParamFrame(Parm);
		if (NULL_var == ParamFrame) return;

		pFrEdt = ParamFrame->GetInPanelEdition(piMfgToolOnMfgDrillTool, pFratt, StyleEdit, ParmName);
	}
	if (NULL != piMfgToolOnMfgDrillTool) piMfgToolOnMfgDrillTool->Release();
}
