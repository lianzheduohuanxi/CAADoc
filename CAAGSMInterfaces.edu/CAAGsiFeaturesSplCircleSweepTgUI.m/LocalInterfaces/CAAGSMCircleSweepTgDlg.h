#ifndef CAAGSMCircleSweepTgDlg_H
#define CAAGSMCircleSweepTgDlg_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// Shape Design And Styling 
//---------------------------------------------------------------------
// Responsable: BIW
//---------------------------------------------------------------------
// CAAGSMCircleSweepTgDlg
//---------------------------------------------------------------------
// 
//  Circle Sweep tangent dialog box 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------

// Activate Contextual Feature Mode 
#define  V5R17_DLGEDITOR_CTXMENU

// Dialog Framework
#include "CATDlgDialog.h"  // needed to derive from CATDlgDialog
#include "CATDlgInclude.h" // needed to use Dialog framework objects
#include "CAAGSMCircleSweepTgCmd.h"
#include "CAAGSMCircleSweepTgUINotifications.h"

#ifdef V5R17_DLGEDITOR_CTXMENU 
class CAAGSMFrmSelectorCtx ; 
#endif  
/**
* Class managing the dialog panel used for a Combined Curve creation / edition.
* 
* refer to programming resources of Dialog framework.
* (consult base class description).
*/
class CAAGSMCircleSweepTgDlg: public CATDlgDialog
{
    
    DeclareResource(CAAGSMCircleSweepTgDlg,CATDlgDialog);

public:
    
    CAAGSMCircleSweepTgDlg(CAAGSMCircleSweepTgCmd* FatherCom);
    virtual ~CAAGSMCircleSweepTgDlg();
    
    /**
    * Builds the panel with its control.
    */
    void Build ();

	/** 
	* Sets the focus on the active entry field
	* @param iFieldNumber
	*   The ID of the input field to be Highlighted
	*   <dl>
	*   <dt> = 1 for <tt>Surface to Sew</tt><dd> 
	*   <dt> = 2 for <tt>Surface Support</tt><dd> 
	*   </dl>
	*/
    void HighLightCurrentPanelField( int iFieldNumber );

    /**
    * Writes Feature  in the field_number-th field.
	* @param iFieldNumber
	*   The ID of the input field
	* @param Spec 
	*   The Prompt to ne written in the field
    */
	void SetUserSelectedFeature(int iFieldNumber , const CATISpecObject_var iSpInput  );

	/**
	*  Analyse notifications from the panel elements and sends the correct data to the father command.
	*/
	void AnalyseNotifs(CATCommand* fromClient,CATNotification* Notif,CATCommandClientData modifId);

    	
	/**
    * Simulate selection in panel field 
   	* @param SelectField
	*   The field_number-th field
    */

    void AutoFieldSelection  (	CATDlgSelectorList* SelectField );
    
    double  GetRadiusValue();
    int     GetTrimMode() ; 

    void SetRadiusValue(double  Rad );
    void SetTrimMode(int iTrim, int sensitivity = 1 );

	void UpdatePanel();
private:
    
	/**
	*Checks if a feature is Infinite
	* @ param Feat
	*   The Feature to be tested
	*/
	
	boolean IsAnInfiniteFeature(CATISpecObject * Feat);
#ifdef V5R17_DLGEDITOR_CTXMENU 
	CAAGSMFrmSelectorCtx *_selCtx_CurveRef,
                         *_selCtx_SurfaceSupport;
	CATDlgSelectorList *_sel_CurveRef,
		               *_sel_SurfaceSupport;
#else  
	CATDlgSelectorList *_sel_CurveRef,
                       *_sel_SurfaceSupport;
#endif 
	CAAGSMCircleSweepTgCmd* _pFatherCommand;
	CATListPV				 _InfosList;

	CATDlgPushButton * _InvertButton;
    CATDlgFrame   * _pFraValue;
    CATDlgSpinner  *_pDlgVal ;
    CATDlgCheckButton *_pDlgCheckTrim; 
	// NOTIF

	enum notifType {
		field_1          = 1,
		field_2          = 2,
		clear			 = 3,
		invert			 = 4,
        val      		 = 5,
        trimmode  		 = 6
	};
	CAACircleSweepTgUIRemoveElement * _ClearSelection ;
    CAACircleSweepTgUICurveRefFieldActivate*	 _Field1Selected   ;
    CAACircleSweepTgUISupportFieldActivate * _Field2Selected  ;
    CAACircleSweepTgUIInvertOrientation * _Invert;
    CAACircleSweepTgUIValueChanged * _ValueChanged;
    CAACircleSweepTgUITrimChanged * _TrimChanged;
};
    
#endif
