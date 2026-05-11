#ifndef CAAGSMCircleSweepTgCmd_H
#define CAAGSMCircleSweepTgCmd_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMCircleSweepTgCmd
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent command 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------

// MechanicalModelerUI Framework
#include "CATBoolean.h"
#include "CATMMUIPanelStateCmd.h"   // Needed to derive from CATMMUIPanelStateCmd
#include "CATShowAttribut.h"

class CAAIGSMCircleSweepTg;
class CAAGSMCircleSweepTgDlg;

class CATFeatureImportAgent;
class CATISpecObject;
class CATHSO;




/**
* Class managing the dialog command to edit Sew Skins.
* 
* refer to programming resources of MechanicalModelerUI framework.
* (consult base class description).
*/
class CAAGSMCircleSweepTgCmd: public CATMMUIPanelStateCmd
{
    
public:
    
    // Standard constructors and destructors
    // -------------------------------------
    CAAGSMCircleSweepTgCmd ( );
    CAAGSMCircleSweepTgCmd ( CAAIGSMCircleSweepTg *pSpecCircleSweepTg );
    virtual ~CAAGSMCircleSweepTgCmd ();
    

	///////////////////////////
	// Launching the Command //
	///////////////////////////
	
	/**
    *   Creates the Starting Feature 
    *   <br><b>Cases</b>:
    *   <ul><li>- Creation Mode : Creates an empty Feature and Insert it in the procedural view.
    *   <li>- Edition Mode : Retrieves the edited Spec and update the panel fields</ul> 
    */
	void CreateStartFeat();

    /**
    * Describes the different states of the command and its transitions.
    */
    void BuildGraph();


	////////////////////////////////////////////////////////////////////
	// Actions launched with UI notifications received from the panel //
	////////////////////////////////////////////////////////////////////

    CATBoolean Highlight_Field1(void *);
	CATBoolean Highlight_Field2(void *);
	CATBoolean Reset_Highlight(void *);

    /**
    * Clear selection.
    */
	CATBoolean ClearSelection(void * data);
    
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	// Methods used by father command CATMMUIPanelStateCommand or by the dialog Panel to Retrieve data   //
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	/**
    *  Retrieves the Mode 
	*  @return 
	*		- Creation Mode :result = 1.
	*		- Edition Mode : result = 0.
	*  @see CATMMUIPanelStateCommand
    */
    int GetMode(); 
	/**
    *  Retrieves the current working CircleSweepTg feature 
	*  @return 
	*		CATISpecObject_var
	*  @see CATMMUIPanelStateCommand
    */

    CATISpecObject_var GiveMyFeature();

	/**
    *  Retrieves the UI panel 
	*  @return 
	*		CATDlgDialog *
	*/

    CATDlgDialog* GiveMyPanel();
	
	/**
    *  Retrieves the support of the Sew
	*  @return 
	*		CATISpecObject_var
	*/
	CATISpecObject_var  GetSurfaceSupport();
	
	/**
    *  Retrieves the Spec to be Sewed
	*  @return 
	*		CATISpecObject_var
	*/

	CATISpecObject_var GetCurveRef();

	/**
    *  Retrieves ID of the selected field of the panel
	*  @return 
	*		int , the Active field
	*/

	int GetActiveField();


 
	//////////////////////
	// Panel Management //
	//////////////////////

 
    /**
    * Asks the panel to focus on an Active Field
    */
    void SetActiveField(int ActiveField);
    
	/**
    * Updates the panel fields
    */
    void UpdatePanelFields();
    
	/**
	 * GetContext for Trim Mode (Trim can  be set up only if Creation mode  ) 
	 */ 
	int GetContext();

	/////////////////////////////////////
	// Dialog with GSD shared commands //
	/////////////////////////////////////

	/**
	* Method called by a notification from an item of a contextual menu
	*/
	CATStatusChangeRC Activate(CATCommand *iCmd, CATNotification *iNotif);

	///////////////
	// UNDO/REDO //
	///////////////
	
	/**
	* Retrieves the Model after an UNDO/REDO and update the panel fields
	*/
	CATBoolean SynchronizeViewWithModel(void* data);	

	CATBoolean UndoClearSelection(void *);


	///////////////////////////////////////////////////////////
	// Actions launched at pushing OK/Preview/Cancel Buttons //
	///////////////////////////////////////////////////////////
	
	/**
	* Method called after pushing OK in the panel
	*/
    CATBoolean OkAction(void * data);
	
	/**
	* Method called after pushing Preview in the panel
	*/
    CATBoolean PreviewAction(void *data);
	
	/**
	* Method called after pushing Cancel in the panel
	*/
	CATBoolean CancelAction(void* iData);
	
  	/**
	* Method called after an update error
	*/
	CATBoolean UpdateOKAction(void*data);
	
	/**
	* Method at the End of the command
	*/
	CATStatusChangeRC Cancel(CATCommand *iCommand, CATNotification *iNotif);

	
	
	////////////////////////
	// Visulization tools //
	////////////////////////
    CATBoolean ValueChanged (void *data);
    CATBoolean TrimChanged (void *data);
	boolean IsAValidCurve(CATDialogAgent * iAgent, void * data);

	///////////////////
	// General tools //
	///////////////////
	void ErrorPanel(CATUnicodeString Title, CATUnicodeString Text, int iType );


private :

 
    
    // Default Constructor, Copy constructor and equal operator, to prevent reimplementation
    // ----------------------------------------------------------------
    CAAGSMCircleSweepTgCmd (CAAGSMCircleSweepTgCmd &);
    CAAGSMCircleSweepTgCmd& operator=(CAAGSMCircleSweepTgCmd&);

	////////////////////////////////////////////////////////////
	// Selection of Feature, Update of the Model, Computation //
	////////////////////////////////////////////////////////////

   	/**
	* Method called at the selection of an input feature
	*/

	CATBoolean ElementSelected(void * Data);

	/**
	* Method called to set the input feature in the attribute of the Sew Skin
	*  @param pSelection
	*		the spec to be setted
	*/

	void UpdateDataInModel(CATISpecObject *  pSelection);

	/**
	* Method called to compute the Sew Skin
	*/

    int   ComputeBody();

  /**
	* Method to set an UndoTitle to the command
	*/

    void   SetUndoTitleToTheCmd();

	/**
	* Method called to Invert the Sew Skin result 
	*/

	CATBoolean InvertInputOrientation(void* data);	
    CATBoolean SetRadius (double Rad );


    CAAIGSMCircleSweepTg            *_piCircleSweepTg  ;
    
    CATFeatureImportAgent *_pCurveRefAgent     ,
                          *_pSurfaceSupportAgent ;
    
    CATDialogAgent        *_pCurveRefFieldAgent     ,
                          *_pSurfaceSupportFieldAgent ;
    
    
    int                      _ActiveField;
    CAAGSMCircleSweepTgDlg  *_panel;
    
    CATFrmEditor          *_editor;
    CATHSO                *_HSO;
    
    int                   _mode;

	// Notifs
	CATDialogAgent        * _RemoveElement,
					      * _InvertOri,
                          *_ValueChanged,
                          *_TrimChanged;
	CATBoolean _FeatureModeChanged;
};

#endif
