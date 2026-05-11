//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Local Framework
#include "CAACafElementPropertyPageEdt.h"
#include "CAACafElementPropertyPageDlg.h"
#include "GetCAACafGeometryEltSettingCtrl.h" // To retrieve the controller which 
                                             // manages the CATSettingRepository

// InteractiveInterfaces Framework
#include <CATIIniSettingManagment.h>        // Interface to manage Commit,Reset,...
                                            // on the CATSettingRepository


// Others
#include <iostream.h>

//----------------------------------------------------------------------------------------------
//
// To Create the TIE Object
//
#include <TIE_CATIUserSettings.h>
TIE_CATIUserSettings(CAACafElementPropertyPageEdt);

// 
// 
// To declare that CAACafElementPropertyPageEdt implements CATIUserSettings, insert 
// the following line in the interface dictionary:
//
//  CAACafElementPropertyPageEdt CATIUserSettings  libCAACafEltToolsOptions
//

// To declare that the class is a component main class 
//
CATImplementClass(CAACafElementPropertyPageEdt, Implementation, CATBaseUnknown, CATNull);

//----------------------------------------------------------------------------------------------

CAACafElementPropertyPageEdt::CAACafElementPropertyPageEdt(): CATEditor(), _pDialogPage(NULL)
  
{
   cout << "CAACafElementPropertyPageEdt::CAACafElementPropertyPageEdt" << endl;

   // Retrieves the Setting Controller with its CATIIniSettingManagment
   // interface pointer.
   _pISettingManagmentForCtrl = NULL ;
   ::GetCAACafGeometryEltSettingCtrl(IID_CATIIniSettingManagment,
	                                   (void**) &_pISettingManagmentForCtrl);
 
}

//----------------------------------------------------------------------------------------------

CAACafElementPropertyPageEdt::~CAACafElementPropertyPageEdt()
{ 
  cout << "CAACafElementPropertyPageEdt::~CAACafElementPropertyPageEdt" << endl; 

  _pDialogPage = NULL ; 

  if ( NULL != _pISettingManagmentForCtrl )
  {
     _pISettingManagmentForCtrl->Release();
     _pISettingManagmentForCtrl = NULL ;
  }
}

//----------------------------------------------------------------------------------------------
void CAACafElementPropertyPageEdt::BuildEditor(CATEditorPage * iDlgPageFather)
{
   cout << "CAACafElementPropertyPageEdt::BuildEditor" << endl;

   if ( NULL != _pISettingManagmentForCtrl )
   {
     // the application gives the father to this current page. 
     _pDialogPage = new CAACafElementPropertyPageDlg(iDlgPageFather);

     if ( NULL != _pDialogPage )
	 {
		 _pDialogPage->Build();
	 }
   }
}

//----------------------------------------------------------------------------------------------
void CAACafElementPropertyPageEdt::SetUserSettingsValue(CATSettingRepository * iUselessFileRep)
{
   cout << "CAACafElementPropertyPageEdt::SetUserSettingsValue" << endl; 
   
   // Set up the dialog object with the setting file values
   if ( NULL != _pDialogPage )
   {
      _pDialogPage->ValueSettings();
   }
}

//----------------------------------------------------------------------------------------------
void CAACafElementPropertyPageEdt::ResetUserSettingsValue()
{
   cout << "CAACafElementPropertyPageEdt::ResetUserSettingsValue" << endl; 

   // If an administrator has created the repository file, we restore 
   // its values, else we restore values set in the constructor of 
   // the setting repository .
   // 
   if ( NULL != _pISettingManagmentForCtrl )
   {
      _pISettingManagmentForCtrl->ResetToAdminValues();  
   }
}

//----------------------------------------------------------------------------------------------
void CAACafElementPropertyPageEdt::CancelModification(CATSettingRepository * iUselessFileRep)
{
   cout << "CAACafElementPropertyPageEdt::CancelModification" << endl;

   // This method is called when the end user clicks Cancel. 
   
   if ( NULL != _pISettingManagmentForCtrl )
   {
      // It restores the values from the last commit.
      _pISettingManagmentForCtrl->Rollback();

      // Saves it again to manage the next cancel 
      _pISettingManagmentForCtrl->Commit();
   }
}

//----------------------------------------------------------------------------------------------
void CAACafElementPropertyPageEdt::CommitModification(CATSettingRepository *iUselessFileRep)
{
   cout << "CAACafElementPropertyPageEdt::CommitModification" << endl;
   
   if ( NULL != _pISettingManagmentForCtrl )
   {
      // The repository is written to the disk file
      // a Commit is done in this method
      _pISettingManagmentForCtrl->SaveRepository();
   }

}
