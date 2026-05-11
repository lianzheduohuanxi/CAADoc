#ifndef CAACafElementPropertyPageEdt_H
#define CAACafElementPropertyPageEdt_H
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Class representing a Tools Options Properties  Page, and implementing 
//  the CATIUserSettings interface.
//
//  Who manages what?:
//  -------------------
//  Options of your page are kept in a setting file.This setting file is
//  controlled by a component controller. You never acceed directly to 
//  the setting file. 
//   
//  CAACafElementPropertyPageEdt retrieves this controller in its 
//  constructor and aks it a pointer to its CATIIniSettingManagment
//  interface.
//  
//  CAACafElementPropertyPageDlg retrieves this controller in its constructor    
//  too and aks it a pointer to its CAAICafGeometryEltSettingAtt
//  interface.
//
//  The CAACafElementPropertyPageDlg class modifies the repository file 
//  (thanks to the CAAICafGeometryEltSettingAtt interface) at 
//  each interaction on the dialog objects of the page. 
//   
//  The CAACafElementPropertyPageEdt class manages the repository 
//  (thanks to the CATIIniSettingManagment interface) for reset,
//  cancel and ok. In the specific case of reset, the dialog class can 
//  be called to replace the values of the page, with the initial one. 
//  
//  Nls/Rsc Files
//  -------------
//  Located in the CNext/resources/msgcatalog of the framework, you find 2
//  files:
//    - CAACafElementPropertyPageEdt.CATNls: to define the title of the page
//    
//    - CAACafElementPropertyPageEdt.CATRsc: to define the category which 
//      belongs this page.The category is the name of the workshop. 
//
//===========================================================================
//  Usage:
//  ------
//  Launch CATIA V5, Tools/Options 
//  
//===========================================================================
//  Inheritance:
//  ------------
// 
//       CATEditor ( CATIAApplicationFrame Framework)
//          CATImplementationAdapter ( ObjectModelerBase Framework)
//              CATEventSubscriber      ( System Framework )
//                 CATBaseUnknown          (System Framework).
//                   
//
//===========================================================================
//  Main Methods:
//  -------------
// 
//  BuildEditor            -> Create and Build the dialog  
//  SetUserSettingsValue   -> Valuation of the Dialog object from settings file
//  ResetUserSettingsValue -> After pushing RESET 
//  CancelModification     -> After pushing CANCEL
//  CommitModification     -> After pushing OK
// 
//===========================================================================

// CATIAApplicationFrame framework
#include "CATEditor.h"                // Needed to derive from CATEditor
class CATIIniSettingManagment ;       // Interface to handle the setting controller

// Local framework
class CAACafElementPropertyPageDlg;   // Dialog Page  

// System framework
class CATSettingRepository ;

class CAACafElementPropertyPageEdt : public CATEditor
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public :

    // The constructor is called once during the application
    // The destructor is called at the end of the application  
    // 
    CAACafElementPropertyPageEdt();
    virtual ~CAACafElementPropertyPageEdt();

    // BuildEditor
    // ------------
    // Instantiates the associated Dialog object class.(_pDialogPage)
    //   
    // iTabPage is the parent of _pDialogPage
    //
    void             BuildEditor           (CATEditorPage * iTabPage);


    // SetUserSettingsValue
    // ----------------------
    // Sets the values and options in the Dialog object 
    // from  the setting file
    // 
    // This method is called in 3 cases:
    //  - when the page is becoming current just after BuildEditor
    //  - when the page is becoming current just after a page swap  
    //  - after the method ResetUserSettingsValue is called if the page is current
    //
    // _pDialogPage, the  dialog object class dedicated to this page, is 
    // always valid in this method
    //
    void             SetUserSettingsValue  (CATSettingRepository * iUselessFileRep);


    // ResetUserSettingsValue
    // ----------------------
    // Resets the values and options in the setting file using the default ones.
    // These default values are those set in the code or set by an administrator.
    //
    // Called when the end user clicks on Reset.
    //
    //
    // _pDialogPage, the  dialog object class dedicated to this page, could be not
    // constructed. So do not use its data in this method. 
    //
    void             ResetUserSettingsValue();

    // CancelModification
    // ------------------
    // Closes the Tools/Options Dialog Box and restores the previous values. 
    // Called when the end user clicks on Cancel.
    // 
    // This method is called if this page has been at least activated once during
    // the current Tools/Options, or if the ResetUserSettingsValue method has
    // been once called. 
    //
    // _pDialogPage, the  dialog object class dedicated to this page, could be not
    // constructed. So do not use its data in this method. 
    //
    void             CancelModification    (CATSettingRepository * iUselessFileRep);
	
    // CommitModification 
    // ------------------
    // Closes the Tools/Options Dialog Box and saves the repository  
    // Called when the end user clicks on Ok 
    // 
    // This method is called if this page has been at least activated once during
    // the current Tools/Options, or if the ResetUserSettingsValue method has
    // been called once. 
    //
    // _pDialogPage, the  dialog object class dedicated to this page, could be not
    // constructed. So do not use its data in this method. 
    //
    void             CommitModification    (CATSettingRepository * iUselessFileRep);

 private:
 
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafElementPropertyPageEdt(const CAACafElementPropertyPageEdt &iObjectToCopy);

   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafElementPropertyPageEdt & operator = (const CAACafElementPropertyPageEdt &iObjectToCopy);

  private : 

   // _pDialogPage Life Cycle
   // -------------------------
   //
   //   -> Created in the BuildEditor method 
   //       
   //   -> Automatically deleted
   //       
   // See each method to know when you can use it.   
   // 
    CAACafElementPropertyPageDlg  *  _pDialogPage;

   // _pISettingManagmentForCtrl
   // --------------------------
   // 
   // The controller of the setting repository 
   // 
    CATIIniSettingManagment        *  _pISettingManagmentForCtrl ;

};
#endif
