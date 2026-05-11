#ifndef CAAMmrCombCrvPanelStCmd_H
#define CAAMmrCombCrvPanelStCmd_H

// COPYRIGHT DASSAULT SYSTEMES 2000

// MechanicalModelerUI Framework
#include "CATMMUIPanelStateCmd.h"   // Needed to derive from CATMMUIPanelStateCmd

class CATFeatureImportAgent;
class CATISpecObject;
class CAAMmrCombinedCurveDlg;
class CATHSO;
class CAAIMmrCombinedCurve;
class CATIGSMTool;
class CATIPrtPart;

/**
* Class managing the dialog command to edit Combined Curves.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
class CAAMmrCombCrvPanelStCmd: public CATMMUIPanelStateCmd
{
    CmdDeclareResource(CAAMmrCombCrvPanelStCmd,CATMMUIStateCommand);

public:
    
    // Standard constructors and destructors
    // -------------------------------------
    CAAMmrCombCrvPanelStCmd ( CAAIMmrCombinedCurve *pCombinedCurve  = NULL);
    virtual ~CAAMmrCombCrvPanelStCmd ();
    
    
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
    * This parameter is used by CATMMUIPanelStateCmd services.
    */
    int GetMode(); 
    
    /**
    * Returns the featurebeing created or edited
    * This parameter is used by CATMMUIStateCmd services.
    */
    CATISpecObject_var GiveMyFeature();
        
    /**
    * Returns a pointer to the dialog panel.
    * This pointer is used by CATMMUIPanelStateCmd services.
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
    CAAMmrCombCrvPanelStCmd (CAAMmrCombCrvPanelStCmd &);
    CAAMmrCombCrvPanelStCmd& operator=(CAAMmrCombCrvPanelStCmd&);

    // Manage the combined curve creation
    //
    HRESULT CreateCombinedCurve() ;
    HRESULT CreateTool(CATIPrtPart * pIPrtPart, CATIGSMTool ** pIGsmtool);

    HRESULT LookingForAnyTypeOfBody(CATIGSMTool ** piGsmtool) ;
    HRESULT LookingForGeomSetOrOrderedGeomSet(CATIGSMTool ** piGsmtool) ;
    HRESULT LookingForGeomSet(CATIGSMTool ** piGsmtool) ;

    // Checks if the combined curved is inside an Ordered Geometrical Set
    HRESULT IsCombCrvInsideOrderedBody(CATBoolean & oIsInsideOrderedBody ) ;

    // Manage the current feature in case of ordered and linear body
    //
    CATStatusChangeRC Activate   (CATCommand * iCmd,CATNotification * iNotif);
    CATStatusChangeRC Deactivate   (CATCommand * iCmd,CATNotification * iNotif);
    CATStatusChangeRC Cancel   (CATCommand * iCmd,CATNotification * iNotif);

private :

    CAAIMmrCombinedCurve   *_piCombinedCurve ;

    CATISpecObject_var      _spSpecObjOnPreviousCurrentFeat ;
    
    CATFeatureImportAgent *_pCurveAgent  ;
    CATFeatureImportAgent *_pDirectionAgent ;
    
    CATDialogAgent        *_pCurve1FieldAgent     ,
                          *_pDirection1FieldAgent ,
                          *_pCurve2FieldAgent     ,
                          *_pDirection2FieldAgent ;
    
    CATISpecObject        *_piSpecOnCurve1 , 
                          *_piSpecOnDir1   ,  
                          *_piSpecOnCurve2 , 
                          *_piSpecOnDir2   ;
    
    CAAMmrCombinedCurveDlg *_panel;
    
    CATFrmEditor          *_editor;
    
    CATHSO                *_HSO;
    
    int                   _ActiveField;
    int                   _mode;
};

#endif
