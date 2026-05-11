// COPYRIGHT DASSAULT SYSTEMES 2002

//CAAV5V6MechanicalModeler.edu Framework
#include "CAAV5V6MmrDatumWindowCmd.h"

// CATMecModUseItf Framework for V6
// MecModInterfaces Framework for V5
#include "CATIMmiPartInfrastructurePreferencesAtt.h" 

// ApplicationFrame Framework for V5
// AfrFoundation Framework for V6
#include "CATApplicationFrame.h"
#include "CATFrmEditor.h"

// Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgPushButton.h"

//System Framework
#include "CATString.h"
#include "CATUnicodeString.h"
#include "CATErrorDef.h"                         
//#include "CATLISTP_CATBaseUnknown.h"
#include "CATEventSubscriberTypedefs.h"
#include "CATInstantiateComponent.h"            
 
// C++ standard library    
#include <iostream.h>     
    

//-------------------------------------------------------------------------
// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAAV5V6MmrDatumWindowCmd);

//-----------------------------------------------------------------------------
// 
#define  COMBO_ITEM0 0 
#define  COMBO_ITEM1 1 
#define  COMBO_ITEM2 2 


// ----------------------------------------------------------------------------
// Constructor/Destructor 
// ----------------------------------------------------------------------------

CAAV5V6MmrDatumWindowCmd::CAAV5V6MmrDatumWindowCmd()
:CATDlgDialog ((CATApplicationFrame::GetFrame())->GetMainWindow(), 
               "CAAV5V6MmrDatumWindowCmdId",
               CATDlgGridLayout | CATDlgWndNoResize | CATDlgWndBtnClose ),
               _piCATIMmiPartInfrastructurePreferencesAtt(NULL),_pDatumCurrentState(NULL),_pDatumChoice(NULL)
               
               
{

   cout << "CAAV5V6MmrDatumWindowCmd constructor"<< endl ;  
  
   
   // -------------------------------------------------------------------------------
   // Creates the component and retrieves a CATIMmiPartInfrastructurePreferencesAtt interface pointer
   // -------------------------------------------------------------------------------
   cout << "    CAAV5V6MmrDatumWindowCmd ----CreateInstance ....."<< endl;

   HRESULT rc = S_OK;
   rc = ::CATInstantiateComponent ("CATMmuPartInfrastructurePreferencesCtrl",
      IID_CATIMmiPartInfrastructurePreferencesAtt, (void**) &_piCATIMmiPartInfrastructurePreferencesAtt);   

   if (FAILED(rc))
	   cout <<" Error" << endl;
	 else
     cout << "    CAAV5V6MmrDatumWindowCmd ----CreateInstance OK "<< endl;  
   

   if (SUCCEEDED (rc) && _piCATIMmiPartInfrastructurePreferencesAtt )
	 {
      
   // -------------------------------------------------------------------------------
   // Dialog Box
   //  -------------------------------------------------------------------------------
      // CreateWindow 
      Build();
      
      // Init Window 
      InitWindow();
      
      
      // The Window is visible
      SetVisibility(CATDlgShow);
      
   
   // -------------------------------------------------------------------------------
   // Add callBack Methods 
   // -------------------------------------------------------------------------------
   
   // ========================================
   // To Manage Modification of CreateDatum Icon 
   // is already active
   // ========================================
      // I want to be prevent when CreateDatum icon (FGSD/Part/FreeStyle...) is pressed 
	  CATCallbackEvent eventName="";
	  _piCATIMmiPartInfrastructurePreferencesAtt->GetDatumModeEvent(eventName);

       ::AddCallback(this,
           _piCATIMmiPartInfrastructurePreferencesAtt,eventName,
         (CATSubscriberMethod)&CAAV5V6MmrDatumWindowCmd::ReceiveDatumModify, 
         NULL);
      
      
   }    
   // ========================================
   // To delete the command when the editor is closed, and that the command
   // is already active
   // ========================================
   _pEditor = CATFrmEditor::GetCurrentEditor();
   if ( (NULL != _pEditor) && (NULL != CATFrmLayout::GetCurrentLayout()) )
   {
      // I want to stop the command when the editor is closed 
      ::AddCallback(this,
         CATFrmLayout::GetCurrentLayout(),
         CATFrmEditor::EDITOR_CLOSE_ENDED(),
         (CATSubscriberMethod)&CAAV5V6MmrDatumWindowCmd::EditorClose,
         NULL);
   }

   cout << "( CAAV5V6MmrDatumWindowCmd::CAAV5V6MmrDatumWindowCmd) end "<< endl ;   
   
   
}
//-------------------------------------------------------------------------------

CAAV5V6MmrDatumWindowCmd::~CAAV5V6MmrDatumWindowCmd() 
{

   cout << "( CAAV5V6MmrDatumWindowCmd::~CAAV5V6MmrDatumWindowCmd)"<< endl ;  
  
   
   _pDatumCurrentState = NULL;
   _pDatumChoice       = NULL;

   // The Window is visible
   SetVisibility(CATDlgHide);
   
   
   // Note: 
   // warning : if the end user exits from CNEXT without closing this panel 
   // the ClickClose method is not called 
   //
 
  if ( NULL != _piCATIMmiPartInfrastructurePreferencesAtt)
  {    
      // Remove Subscriber 
      
      ::RemoveSubscriberCallbacks(this,_piCATIMmiPartInfrastructurePreferencesAtt);
      
      // Callback set in the constructor
      
      _piCATIMmiPartInfrastructurePreferencesAtt->Release();
      _piCATIMmiPartInfrastructurePreferencesAtt = NULL;
   }
   
   
   //
   if ( (NULL !=  _pEditor) && ( NULL != CATFrmLayout::GetCurrentLayout()) )
   {
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());
   }
   
   _pEditor = NULL ;
   
   // Command destruction
   RequestDelayedDestruction();

   cout << "( CAAV5V6MmrDatumWindowCmd::~CAAV5V6MmrDatumWindowCmd) end "<< endl ;  
   


}


// ----------------------------------------------------------------------------
// Build
// ----------------------------------------------------------------------------

HRESULT  CAAV5V6MmrDatumWindowCmd::Build() 
{
   
   HRESULT rc = S_OK; 
  
   cout << "( CAAV5V6MmrDatumWindowCmd::Build)" << endl;  
   
   // -------------------------------------------------------------------------------
   // Retrieves the NLS text of each combo's line
   // -------------------------------------------------------------------------------
   char pcKey[30];
   CATString sKey;
   CATUnicodeString DatumText;
   
   for ( int i = 0; i < 3; i++)
   {
      // Transformation of an int in a char *
      sprintf(pcKey, "DatumState%d", i);
      
      // Set this char * in a CATSTring
      sKey = pcKey;
      
      // retrieves the NLS text 
      if ( 0 != GetResourceValueFromKey(sKey, DatumText))
      {
         DatumValueMode[i]=DatumText;
      }
   }
   
   // -------------------------------------------------------------------------------
   // Constructs the contents of the dialog box
   // -------------------------------------------------------------------------------
   CATDlgFrame * pFrameViewer = new CATDlgFrame(this,"DatumFrameId", CATDlgGridLayout);
   pFrameViewer ->SetGridConstraints(0,0,1,1,CATGRID_4SIDES );
   //   CATDlgFraNoFrame|CATDlgGridLayout|CATDlgFraNoTitle);

   //----------------------------------------------------------------
   // All Dialog's object whose pointer are not kept as data member. 
   // while we don't have need after the new operation.
   //---------------------------------------------------------------
   CATDlgLabel           * pDatumCurrentLbl = NULL ;
   CATDlgPushButton      * pApply          = NULL ;
   
   // Line1  Current CreateDatum CurrentState : - Stata-
   // -----------------------------------------------------------------------
   pDatumCurrentLbl  = new CATDlgLabel(pFrameViewer, "DatumCurrentLblId");
   pDatumCurrentLbl ->SetGridConstraints(0,0,1,1,CATGRID_LEFT );
   
   _pDatumCurrentState = new  CATDlgSelectorList( pFrameViewer , "DatumCurrentStateId ",CATDlgDataModify);
   _pDatumCurrentState ->SetVisibleTextHeight(1);
   _pDatumCurrentState ->SetGridConstraints(0,1,1,1,CATGRID_4SIDES );
   _pDatumCurrentState ->SetLine(DatumValueMode[0], 0,CATDlgDataModify );
   _pDatumCurrentState ->SetVisibleTextWidth(22 );
   
   // Line2   NoDatumCreation                    / Apply 
   // -----------------------------------------------------------------------
   _pDatumChoice       = new CATDlgCombo(pFrameViewer , "DatumComboId", CATDlgCmbOptionStyle);
   _pDatumChoice        ->SetGridConstraints(1,0,1,1,CATGRID_4SIDES );
   _pDatumChoice        ->SetLine(DatumValueMode[0], COMBO_ITEM0);
   _pDatumChoice        ->SetLine(DatumValueMode[1], COMBO_ITEM1);
   _pDatumChoice        ->SetLine(DatumValueMode[2], COMBO_ITEM2);
   _pDatumChoice        ->SetVisibleTextWidth(22 );
   _pDatumChoice        ->SetSelect(0);
   
   
   pApply              = new CATDlgPushButton(pFrameViewer, "DatumApplyId");
   pApply               ->SetGridConstraints(1,1,1,1,CATGRID_4SIDES );
   
   
   
   //========================================
   // Subscribes to Event
   //========================================
   
   AddAnalyseNotificationCB (pApply, pApply->GetPushBActivateNotification(),
      (CATCommandMethod)&CAAV5V6MmrDatumWindowCmd::Apply, NULL);
   
   AddAnalyseNotificationCB (this, this->GetWindCloseNotification(),
      (CATCommandMethod)&CAAV5V6MmrDatumWindowCmd::Close,NULL);
   
   AddAnalyseNotificationCB (this, this->GetDiaCLOSENotification(),
      (CATCommandMethod)&CAAV5V6MmrDatumWindowCmd::Close,NULL);
   
   return rc ;
 
   cout << "( CAAV5V6MmrDatumWindowCmd::Build) end " << endl;
    

} 

// ----------------------------------------------------------------------------
// InitWindow
// ----------------------------------------------------------------------------
HRESULT CAAV5V6MmrDatumWindowCmd::InitWindow()
{
   
   HRESULT rc = S_OK;
 
   cout << "( CAAV5V6MmrDatumWindowCmd::InitWindow)" << endl;
   

   // Retrieves the interface which gives values of each attribut of the
   // setting file. 
   if ( NULL != _piCATIMmiPartInfrastructurePreferencesAtt)
   {
      
      CATIMmiPartInfrastructurePreferencesAtt::PreferenceMode TheMode ; 
      rc = _piCATIMmiPartInfrastructurePreferencesAtt->GetDatumMode(TheMode);
      
      // Init Panel TextField and Combo 
      // ------------------------------------------------------------------------
      // Initialize the second line ( indices start from 0 )
 
      cout << "    CAAV5V6MmrDatumWindowCmd  - Init" << endl;
  
      
      _pDatumChoice->SetSelect(0);
      _pDatumCurrentState -> SetLine("NoDatumCreation", 0,CATDlgDataModify );
      
  
      cout << "    CAAV5V6MmrDatumWindowCmd  - Set dialog box with "; 
   
      
      if ( TheMode == CATIMmiPartInfrastructurePreferencesAtt::NoMode){

         cout << "    NoDatumCreation mode "  << endl;
   
         _pDatumChoice->SetSelect(COMBO_ITEM0);
         _pDatumCurrentState -> SetLine(DatumValueMode[0], 0,CATDlgDataModify );
      }

      else if (TheMode == CATIMmiPartInfrastructurePreferencesAtt::PermanentMode){

         cout << "    DatumCreationPermanent mode "  << endl;
    
         _pDatumChoice->SetSelect(COMBO_ITEM1);
         _pDatumCurrentState -> SetLine(DatumValueMode[1],0,CATDlgDataModify );
      }

      else if (TheMode == CATIMmiPartInfrastructurePreferencesAtt::TemporaryMode){

         cout << "    DatumCreationTemporary mode "  << endl;
  
         _pDatumChoice->SetSelect(COMBO_ITEM2);
         _pDatumCurrentState -> SetLine(DatumValueMode[2],0,CATDlgDataModify );
         
      }
      else  {

         cout << endl;

      }
   }

   cout << "( CAAV5V6MmrDatumWindowCmd::InitWindow) end " << endl;
 

   return rc ;

}

// ----------------------------------------------------------------------------
// Apply 
// ----------------------------------------------------------------------------
void CAAV5V6MmrDatumWindowCmd::Apply (CATCommand           * iPublishingCommand,
                                  CATNotification      * iNotification,
                                  CATCommandClientData   iUsefulData)
{

   cout << "( CAAV5V6MmrDatumWindowCmd::Apply)" << endl;

   
   HRESULT rc = S_OK; 
   
   
    
   // ----------------------------------
   // Title of the Combo
   // ---------------------------------- 
   CATUnicodeString usParam[2];
   usParam[0] = "CAAV5V6MmrDatumWindowCmd";
   
   // ----------------------------------------------------
   // Retrieves the text of the selected line in the Combo
   // ----------------------------------------------------
   int LineSelected = _pDatumChoice->GetSelect() ;
   _pDatumChoice->GetLine(usParam[1],LineSelected);
   

   cout << "    CAAV5V6MmrDatumWindowCmd  - Read Combo in window = "<< usParam[0].ConvertToChar() <<"/ Value="<<usParam[1].ConvertToChar() << endl;
   
   
   // -----------------------------------
   // Message sent in the standard output 
   // -----------------------------------
   
   // Retrieves the interface which gives values of each attribut of the
   // setting file. 
   
   if ( NULL != _piCATIMmiPartInfrastructurePreferencesAtt){
      
      CATIMmiPartInfrastructurePreferencesAtt::PreferenceMode TheMode ; 


      cout << "    CAAV5V6MmrDatumWindowCmd  - Set CreateDatum mode "<<endl; 
    
      if (LineSelected == COMBO_ITEM0) {
         TheMode = CATIMmiPartInfrastructurePreferencesAtt::NoMode;
         rc = _piCATIMmiPartInfrastructurePreferencesAtt->SetDatumMode(TheMode);
      }

      else if (LineSelected ==COMBO_ITEM1) {
         TheMode = CATIMmiPartInfrastructurePreferencesAtt::PermanentMode;
         rc = _piCATIMmiPartInfrastructurePreferencesAtt->SetDatumMode(TheMode);
      }

      else if (LineSelected ==COMBO_ITEM2) {
         TheMode = CATIMmiPartInfrastructurePreferencesAtt::TemporaryMode;
         rc = _piCATIMmiPartInfrastructurePreferencesAtt->SetDatumMode(TheMode);
      }
      
      //FeedBack 
      

      if  ( SUCCEEDED(rc) ) {
         cout << "    CAAV5V6MmrDatumWindowCmd  - Ok Send Set new value  for CreateDatum "  << endl;
      }
      
      else {
         cout << "    CAAV5V6MmrDatumWindowCmd  - Ko CreateDatum not set " << endl;
      }
    
      
   }

   cout << "( CAAV5V6MmrDatumWindowCmd::Apply) end " << endl;
    

}

// ----------------------------------------------------------------------------
// Close
// ----------------------------------------------------------------------------

void CAAV5V6MmrDatumWindowCmd::Close(CATCommand           * iPublishingCommand,
                                 CATNotification      * iNotification,
                                 CATCommandClientData   iUsefulData)
{

   cout << "( CAAV5V6MmrDatumWindowCmd::Close)" << endl;
    
   
   // Hide
   SetVisibility(CATDlgHide);
   
   // Terminate the command 
   RequestDelayedDestruction();

  cout << "( CAAV5V6MmrDatumWindowCmd::Close) end " << endl;
    
    
}



//-------------------------------------------------------------------------------

void CAAV5V6MmrDatumWindowCmd::EditorClose(CATCallbackEvent  iEvent, 
                                       void            * iFrom,
                                       CATNotification * iNotification,
                                       CATSubscriberData iClientData,
                                       CATCallback       iCallBack ) 
{
   

   cout << "( CAAV5V6MmrDatumWindowCmd::EditorClose)" << endl;
    
   
   if ( _pEditor == iFrom )
   {
      
      // Now this extension will receive any message.
      ::RemoveSubscriberCallbacks(this,CATFrmLayout::GetCurrentLayout());
      _pEditor = NULL ; 
      
       // Terminate the command 
       RequestDelayedDestruction();
      
   }

   cout << "( CAAV5V6MmrDatumWindowCmd::EditorClose) end " << endl;
    

}

//-------------------------------------------------------------------------------

void CAAV5V6MmrDatumWindowCmd::ReceiveDatumModify(CATCallbackEvent  iEvent, 
                                              void            * iFrom,
                                              CATNotification * iNotification,
                                              CATSubscriberData iClientData,
                                              CATCallback       iCallBack ) 
{
   

   cout << "( CAAV5V6MmrDatumWindowCmd::ReceiveDatumModify)" << endl;
    
   if ( NULL !=  _piCATIMmiPartInfrastructurePreferencesAtt )    {
      
     // Setting datun has been modified / Update windiow 
      InitWindow () ; 
      
   }   

   cout << "( CAAV5V6MmrDatumWindowCmd::ReceiveDatumModify) end " << endl;
    

}
