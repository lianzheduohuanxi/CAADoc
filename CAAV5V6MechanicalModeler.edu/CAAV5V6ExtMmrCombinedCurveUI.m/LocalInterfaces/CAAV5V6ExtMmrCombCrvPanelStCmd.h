#ifndef CAAV5V6ExtMmrCombCrvPanelStCmd_H
#define CAAV5V6ExtMmrCombCrvPanelStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2012
//
// Note : CAAV5V6ExtMmrCombCrvPanelStCmd is the same use case as CAAMmrCombCrvPanelStCmd. 
//        The objective is to have the same source delivered in V5 and V6. 
//        Any specific code to either V5 or V6 is flagged.
//

#include "CATIAV5Level.h"

// CATMecModLiveUseItf framework
#include "CATIMmiMechanicalFeature.h"          

#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
// CATMecModUIExtendItf Framework
#include "CATMmrPanelStateCmd.h"   // Needed to derive from 
#else
//============================================== 
// V5 only
//============================================== 
// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h"   // Needed to derive from
#endif

class CATFeatureImportAgent;
class CAAV5V6ExtMmrCombinedCurveDlg;
class CATHSO;
class CAAIV5V6ExtMmrCombinedCurve;
class CATIGSMTool;
class CATIMmiUsePrtPart;


/**
* Class managing the dialog command to edit Combined Curves.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
#ifdef CATIAR214
//============================================== 
// V6 only
//==============================================
class CAAV5V6ExtMmrCombCrvPanelStCmd: public CATMmrPanelStateCmd
{
	CmdDeclareResource(CAAV5V6ExtMmrCombCrvPanelStCmd,CATMmrPanelStateCmd);
#else
//============================================== 
// V5 only
//============================================== 
class CAAV5V6ExtMmrCombCrvPanelStCmd: public CATMMUIPanelStateCmd
{
	CmdDeclareResource(CAAV5V6ExtMmrCombCrvPanelStCmd,CATMMUIStateCommand);
#endif
   
public:
    
    // Standard constructors and destructors
    // -------------------------------------
    CAAV5V6ExtMmrCombCrvPanelStCmd ( CAAIV5V6ExtMmrCombinedCurve *pCombinedCurve  = NULL);
    virtual ~CAAV5V6ExtMmrCombCrvPanelStCmd ();
    
    
    /**
    * Describes the different states of the command and its transitions.
    */
    void BuildGraph();
    
    /**
    * Method called when pressing the OK button of the panel.
    */
    CATBoolean OkAction(void *);

    /**
    * Method called when pressing the Cancel button of the panel.
    */
    CATBoolean CancelAction(void *);
    
    /**
    * Returns a different value whether the command is used to create or edit a Combined Curve.
    * This parameter is used by CATMmrPanelStateCmd services.
    */
    int GetMode(); 
    
#ifdef CATIAV5R23 
//============================================== 
// V5 only
//============================================== 
    /**
    * Returns the featurebeing created or edited
    * This parameter is used by CATMMUIStateCmd services.
    */
    CATISpecObject_var GiveMyFeature(); // suppress : not used
#endif  

    /**
    * Returns a pointer to the dialog panel.
    * This pointer is used by CATMmrPanelStateCmd services.
    */
    CATDlgDialog* GiveMyPanel();
    
    /**
    * Method called when a curve is selected.
    */
    CATBoolean CurveSelected(void *);
    
    /**
    * Method called when a direction is selected.
    */
    CATBoolean DirectionSelected(void *);
    
    /**
    * Method called when a curve or a line is selected, to add or remove it of
    * the definition of the Combined Curve.
    */
    void ElementSelected(CATFeatureImportAgent *pAgent);
    
    /**
    * Method called when the field correponding to Curve.1 is selected.
    */
    CATBoolean Curve1FieldSelected(void *);
    
    /**
    * Method called when the field correponding to Direction.1 is selected.
    */
    CATBoolean Direction1FieldSelected(void *);
    
    /**
    * Method called when the field correponding to Curve.2 is selected.
    */
    CATBoolean Curve2FieldSelected(void *);
    
    /**
    * Method called when the field correponding to Direction.2 is selected.
    */
    CATBoolean Direction2FieldSelected(void *);
    
    /**
    * Asks the panel to focus on an Active Field
    */
    void SetActiveField(int ActiveField);
        
    /**
    * Ask the panel to update the texts in the fields.
    */
    void UpdatePanelFields();
    
    /**
    * Prevents the user from clicking the OK button if a entry field is not filled in.
    */
    void CheckOKSensitivity();
    
    
private :

    // Default Constructor, Copy constructor and equal operator, to prevent reimplementation
    // ----------------------------------------------------------------
    CAAV5V6ExtMmrCombCrvPanelStCmd (CAAV5V6ExtMmrCombCrvPanelStCmd &);
    CAAV5V6ExtMmrCombCrvPanelStCmd& operator=(CAAV5V6ExtMmrCombCrvPanelStCmd&);

    // Manage the combined curve creation
    HRESULT CreateCombinedCurve();
    HRESULT CreateTool(CATIMmiUsePrtPart * pIPrtPart, CATIGSMTool ** pIGsmtool);

    HRESULT LookingForAnyTypeOfBody(CATIGSMTool ** piGsmtool);
    HRESULT LookingForGeomSetOrOrderedGeomSet(CATIGSMTool ** piGsmtool);
    HRESULT LookingForGeomSet(CATIGSMTool ** piGsmtool);

    // Checks if the combined curved is inside an Ordered Geometrical Set
    HRESULT IsCombCrvInsideOrderedBody(CATBoolean & oIsInsideOrderedBody );

    // Manage the current feature in case of ordered and linear body
    CATStatusChangeRC Activate(CATCommand * iCmd,CATNotification * iNotif);
    CATStatusChangeRC Deactivate(CATCommand * iCmd,CATNotification * iNotif);
    CATStatusChangeRC Cancel(CATCommand * iCmd,CATNotification * iNotif);

private :

    CAAIV5V6ExtMmrCombinedCurve   *_piCombinedCurve;

    CATIMmiMechanicalFeature_var  _spPreviousCurrentFeat;
    
    CATFeatureImportAgent *_pCurveAgent;
    CATFeatureImportAgent *_pDirectionAgent;
    
    CATDialogAgent        *_pCurve1FieldAgent,
                          *_pDirection1FieldAgent,
                          *_pCurve2FieldAgent,
                          *_pDirection2FieldAgent;
    
    CATBaseUnknown        *_piCurve1; 
    CATBaseUnknown        *_piDir1;  
    CATBaseUnknown        *_piCurve2; 
    CATBaseUnknown        *_piDir2;
    
    CAAV5V6ExtMmrCombinedCurveDlg *_panel;
    
    CATFrmEditor          *_editor;
    
    CATHSO                *_HSO;
    
    int                   _ActiveField;
    int                   _mode;
};

#endif
