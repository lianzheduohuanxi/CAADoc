// COPYRIGHT DASSAULT SYSTEMES 2000
// ===================================================================
//
// CAAEMaiToolEditionCustomizationDrillTool:
//
// Sample code for : Manufacturing Modeler
// Mission         : Customize the Drilling Tool Editor
//
//
//====================================================================

#ifndef CAAEMaiToolEditionCustomizationDrillTool_h
#define CAAEMaiToolEditionCustomizationDrillTool_h

// Dialog Framework
#include "CATDlgInclude.h"             // For Dialog components

// System Framework
#include "CATBooleanDef.h"             // For CATBoolean
#include "CATListOfCATUnicodeString.h" // For List of CATUnicodeString
#include "CATISpecObject.h"

class CAAEMaiToolEditionCustomizationDrillTool : public CATBaseUnknown
{
  CATDeclareClass;

  public: 
    
	// Constructor and Destructor
	//------------------------------------------------
	CAAEMaiToolEditionCustomizationDrillTool();
    virtual ~CAAEMaiToolEditionCustomizationDrillTool();
	
	// This method allows to get the Tool editor view
	// that will be displayed when editing the tool 
	// through ResourceList access (simple view)
	//------------------------------------------------
	virtual CATDlgFrame* GetPanelEditor     (CATDialog    *iParent, CATDlgStyle  iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=TRUE);
  
	// This method allows to get the Tool editor view
	// that will be displayed when editing the tool 
	// through ResourceList access with selection of the button "more" (advanced view)
	//---------------------------------------------------------------------------
	virtual CATDlgFrame* GetMorePanelEditor (CATDialog    *iParent, CATDlgStyle iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=TRUE);
   
	// This method allows to get the Tool editor view
	// that will be displayed when editing the tool 
	// with access through the Activity editor (tool tab page)
	//---------------------------------------------------------------------------
	virtual CATDlgFrame* GetActivityEditor  (CATDialog    *iParent, CATDlgStyle  iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=FALSE, const CATISpecObject_var &ihSpecAct=NULL_var);
   
	// This method allows to get the Tool graphic view
	// That can be an icon (at least displayed during Tool selection)
	//---------------------------------------------------------------------------
	virtual CATDlgFrame* GetGraphicEditor   (CATDialog    *iParent, CATDlgStyle   iStyle=CATDlgFraNoFrame,
											 const CATBoolean iEditMode=FALSE);

	// Not used (for future use)
	//---------------------------------------------------------------------------
    virtual void GenerateJPEGImageFromGraphicEditor (CATDialog             *iParent,
													 const CATUnicodeString &iImagePathName="");

  private:
	
	// Copy constructor
	//---------------------------------------------------------------------------
    CAAEMaiToolEditionCustomizationDrillTool(const CAAEMaiToolEditionCustomizationDrillTool &iObjectToCopy);

	// Generic method to build the frame content
	//---------------------------------------------------------------------------
	void BuildFrame (CATDlgFrame *iParent, const CATListOfCATUnicodeString &iAttributesList);
};

#endif


