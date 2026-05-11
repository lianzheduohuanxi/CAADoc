#ifndef CAAGSMSewSkinBasicDlg_H
#define CAAGSMSewSkinBasicDlg_H
//---------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2005
//---------------------------------------------------------------------
// CATIA Shape Design And Styling 
// 
//CAAGSMSewSkinBasicDlg
//---------------------------------------------------------------------
// 
//  Sew Skin Basic dialog box 
//
//---------------------------------------------------------------------
// Historique:
// Creation     : 05/xx/xx > PEY 
//---------------------------------------------------------------------

// Dialog Framework
#include "CATDlgDialog.h"  // needed to derive from CATDlgDialog
#include "CATDlgInclude.h" // needed to use Dialog framework objects
#include "CAAGSMSewSkinBasicCmd.h"
#include "CAAGSMSewSkinBasicUINotifications.h"
/**
* Class managing the dialog panel used for a Combined Curve creation / edition.
* 
* refer to programming resources of Dialog framework.
* (consult base class description).
*/
class CAAGSMSewSkinBasicDlg: public CATDlgDialog
{
    
    DeclareResource(CAAGSMSewSkinBasicDlg,CATDlgDialog);

public:
    
    CAAGSMSewSkinBasicDlg(CAAGSMSewSkinBasicCmd* FatherCom);
    virtual ~CAAGSMSewSkinBasicDlg();
    
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
    * Writes name in the field_number-th field.
	* @param iFieldNumber
	*   The ID of the input field
	* @param iFieldNumber
	*   The Prompt to ne written in the field
    */
    void SetName( int iFieldNumber , CATUnicodeString iName );
    
    /**
    * Returns the field_number-th field of the panel.
   	* @param iFieldNumber
	*   The ID of the input field
    */
    CATDlgSelectorList* GetField(int iFieldNumber );

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

	
private:
    
	/**
	*Checks if a feature is Infinite
	* @ param Feat
	*   The Feature to be tested
	*/
	
	boolean IsAnInfiniteFeature(CATISpecObject * Feat);

    CATDlgSelectorList *_sel_SurfaceToSew,
                       *_sel_SurfaceSupport;
    
	CAAGSMSewSkinBasicCmd* _TheCommand;

	CATDlgPushButton * _InvertButton;

	// NOTIF

	enum notifType {
		field_1          = 1,
		field_2          = 2,
		clear			 = 3,
		invert			 = 4,

	};
	CAAGSMSewSkinBasicUIRemoveElement * _ClearSelection ;
    CAASurfaceToSewFieldActivate*	 _Field1Selected   ;
    CAASupportFieldActivate * _Field2Selected  ;
    CAAInvertOrientation * _Invert;
};
    
#endif
