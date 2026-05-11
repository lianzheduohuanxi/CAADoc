#ifndef CAACafViewPropertyPageEdt_H
#define CAACafViewPropertyPageEdt_H
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
//  See CAACafElementPropertyPageEdt for all details.
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
//  ResetUserSettingsValue -> After push RESET 
//  CancelModification     -> After push CANCEL
//  CommitModification     -> After push OK
// 
//===========================================================================

#include "CATEditor.h"                // Needed to derive from CATEditor
class CATIIniSettingManagment ;       // Interface to handle the setting controller

// Local Framework
class CAACafViewPropertyPageDlg;   // Dialog Page  

class CAACafViewPropertyPageEdt : public CATEditor
{
  // Used in conjunction with CATImplementClass in the .cpp file 
  CATDeclareClass;

  public :

    CAACafViewPropertyPageEdt();
    virtual ~CAACafViewPropertyPageEdt();

    void             BuildEditor           (CATEditorPage * iTabPage);

    void             SetUserSettingsValue  (CATSettingRepository * iUselessFileRep);

    void             ResetUserSettingsValue();

    void             CancelModification    (CATSettingRepository * iUselessFileRep);
	
    void             CommitModification    (CATSettingRepository * iUselessFileRep);

 private:
 
   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafViewPropertyPageEdt(const CAACafViewPropertyPageEdt &iObjectToCopy);

   // Assignment operator , not implemented
   // Set as private to prevent from compiler automatic creation as public.
   CAACafViewPropertyPageEdt & operator = (const CAACafViewPropertyPageEdt &iObjectToCopy);

  private : 

    CAACafViewPropertyPageDlg     *  _pDialogPage;

   // _pISettingManagmentForCtrl
   // --------------------------
   // 
   // The controller of the setting repository 
   // 
    CATIIniSettingManagment        *  _pISettingManagmentForCtrl ;

};
#endif
