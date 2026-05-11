//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Local Framework
#include "CAACafViewPropertyPageEdt.h"
#include "CAACafViewPropertyPageDlg.h"
#include "GetCAACafGeometryViewSettingCtrl.h"  // To retrieve the controller which 
                                               // manages the CATSettingRepository

// InteractiveInterfaces Framework
#include <CATIIniSettingManagment.h>           // Interface to manage Commit,Reset,...
                                               // on the CATSettingRepository

// Others
#include <iostream.h>

//----------------------------------------------------------------------------------------------
//
// To create the TIE Object
//
#include <TIE_CATIUserSettings.h>
TIE_CATIUserSettings(CAACafViewPropertyPageEdt);

// 
// 
// To declare that CAACafViewPropertyPageEdt implements CATIUserSettings, insert 
// the following line in the interface dictionary:
//
//  CAACafViewPropertyPageEdt CATIUserSettings  libCAACafViewToolsOptions
//

// To declare that the class is a component main class 
//
CATImplementClass(CAACafViewPropertyPageEdt, Implementation, CATBaseUnknown, CATNull);

//----------------------------------------------------------------------------------------------

CAACafViewPropertyPageEdt::CAACafViewPropertyPageEdt(): CATEditor(), _pDialogPage(NULL)
  
{
   cout << "CAACafViewPropertyPageEdt::CAACafViewPropertyPageEdt" << endl;

   // Retrieves the Setting Controller with its CATIIniSettingManagment
   // interface pointer.
   //
   _pISettingManagmentForCtrl = NULL ;
   ::GetCAACafGeometryViewSettingCtrl(IID_CATIIniSettingManagment,
	                                          (void**) &_pISettingManagmentForCtrl);
}

//-------------------------------------------------------------------------------------------
CAACafViewPropertyPageEdt::~CAACafViewPropertyPageEdt()
{ 
  cout << "CAACafViewPropertyPageEdt::~CAACafViewPropertyPageEdt" << endl; 

  _pDialogPage = NULL ;

  if ( NULL != _pISettingManagmentForCtrl )
  {
     _pISettingManagmentForCtrl->Release();
     _pISettingManagmentForCtrl = NULL ;
  }
}

//-------------------------------------------------------------------------------------------
void CAACafViewPropertyPageEdt::BuildEditor(CATEditorPage * iDlgPageFather)
{
   cout << "CAACafViewPropertyPageEdt::BuildEditor" << endl;

   if ( NULL != _pISettingManagmentForCtrl )
   {
     // the application gives the father to this current page. 
     _pDialogPage = new CAACafViewPropertyPageDlg(iDlgPageFather);

     if ( NULL != _pDialogPage )
	 {
		 _pDialogPage->Build();
	 }
   }
}

//-------------------------------------------------------------------------------------------
void CAACafViewPropertyPageEdt::SetUserSettingsValue(CATSettingRepository * iUselessFileRep)
{
   cout << "CAACafViewPropertyPageEdt::SetUserSettingsValue" << endl; 

   // Set up the dialog object with the setting file values
   if ( NULL != _pDialogPage )
   {
      _pDialogPage->ValueSettings();
   }
   
}

//-------------------------------------------------------------------------------------------
void CAACafViewPropertyPageEdt::ResetUserSettingsValue()
{
   cout << "CAACafViewPropertyPageEdt::ResetUserSettingsValue" << endl; 
   
   // If an administrator has created the repository file, we restore 
   // its values, else we restore values set in the constructor of 
   // the setting repository .
   // 
   if ( NULL != _pISettingManagmentForCtrl )
   {
      _pISettingManagmentForCtrl->ResetToAdminValues();  
   }
}

//-------------------------------------------------------------------------------------------
void CAACafViewPropertyPageEdt::CancelModification(CATSettingRepository *iUselessFileRep)
{
   cout << "CAACafViewPropertyPageEdt::CancelModification" << endl;

   if ( NULL != _pISettingManagmentForCtrl )
   {
      // It restores the values from the last commit.
      _pISettingManagmentForCtrl->Rollback();

      // Saves it again to manage the next cancel 
      _pISettingManagmentForCtrl->Commit();
   }

}


void CAACafViewPropertyPageEdt::CommitModification(CATSettingRepository *iUselessFileRep)
{
   cout << "CAACafViewPropertyPageEdt::CommitModification" << endl;

   if ( NULL != _pISettingManagmentForCtrl )
   {
      // The repository is written to the disk file
      // a Commit is done in this method
      _pISettingManagmentForCtrl->SaveRepository();
   }
}
