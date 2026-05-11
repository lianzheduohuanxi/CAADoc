// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAADlgBurgerWindow.h"

// Dialog Framework
#include "CATDlgFrame.h"               // Dialog's object 
#include "CATDlgLabel.h"
#include "CATDlgRadioButton.h"
#include "CATDlgCheckButton.h"
#include "CATDlgSlider.h"
#include "CATDlgCombo.h"
#include "CATDlgEditor.h"
#include "CATDlgSelectorList.h"
#include "CATDlgSpinner.h"
#include "CATDlgSeparator.h"
#include "CATDlgPushButton.h"          // Dialog's object 

#include "CATMsgCatalog.h"             // NLS Message
#include "CATDlgNotify.h"              // To create a window with a text
#include "CATInteractiveApplication.h" // The class application
#include "CATDlgGridConstraints.h"     // To have easy Dialog's object alignment 

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAADlgBurgerWindow::CAADlgBurgerWindow(CATInteractiveApplication * iParentCommand,
                                       const CATString           & iDialogboxId,
                                       CATDlgStyle                 iDialogBoxStyle)
       : CATDlgDocument(iParentCommand, iDialogboxId, iDialogBoxStyle),
         _pCAABurgerApplication(iParentCommand),
         _pRare(NULL) ,_pMedium(NULL),_pWellDone(NULL),
         _pKetchup(NULL), _pMustard(NULL), _pPickle(NULL),
         _pOnion(NULL), _pMayonnaise(NULL),_pHamburgerQuantity(NULL),
         _pFriesSize(NULL),_pFriesQuantity(NULL),
         _pDrinkList(NULL),_pDrinkQuantity(NULL),
         _pOrderWindow(NULL)
{
  cout << "------- Burger constructor -------" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAADlgBurgerWindow::~CAADlgBurgerWindow()
{ 
  cout << "CAADlgBurgerWindow::~CAADlgBurgerWindow" << endl; 

  // All Dialog's Object children of this Window are
  // automatically deleted.
  _pCAABurgerApplication = NULL ;
  _pRare= NULL ; 
  _pMedium= NULL ;
  _pWellDone= NULL ;
  _pKetchup= NULL ;
  _pMustard= NULL ; 
  _pPickle= NULL ;
  _pOnion= NULL ;
  _pMayonnaise= NULL ;
  _pHamburgerQuantity= NULL ;
  _pFriesSize= NULL ;
  _pFriesQuantity= NULL ;
  _pDrinkList= NULL ;
  _pDrinkQuantity= NULL ;
  _pOrderWindow= NULL ;
}

//--------------------------------------------------------------------------------------

void CAADlgBurgerWindow::Build()
{
  cout << "CAADlgBurgerWindow::Build" << endl;

  //----------------------------------------------------------------
  // All Dialog's object whose pointer are not kept as data member. 
  // while we don't have need after the new operation.
  //---------------------------------------------------------------
  CATDlgFrame           * pHamburgerFrame = NULL ;
  CATDlgFrame           * pFriesFrame     = NULL ;
  CATDlgFrame           * pDrinkFrame     = NULL ;
  CATDlgLabel           * pHamburgerLabel = NULL ;
  CATDlgLabel           * pFriesLabel     = NULL ; 
  CATDlgLabel           * pDrinkLabel     = NULL ;
  CATDlgLabel           * pSizeOfFriesLabel = NULL ; 
  CATDlgLabel           * pQuantityOfFriesLabel = NULL ;
  CATDlgLabel           * pQuantityOfDrinksLabel = NULL ;
  CATDlgSeparator       * pSeparator1     = NULL ;
  CATDlgSeparator       * pSeparator2     = NULL ;
  CATDlgPushButton      * pApply          = NULL ;
  CATDlgPushButton      * pDismiss        = NULL ;
  CATDlgPushButton      * pReset          = NULL ;


  //--------------------------------------------------------------------
  // The dialog window elements are organized in three columns.
  // Each column contains a CATDlgLabel, a set of other widgets grouped
  // in a CATDlgFrame, and a CATDlgButton. The columns are separated by
  // CATDlgSeparators. 
  // CATDlgGridConstraints are used to specify the layout of the elements.
  //--------------------------------------------------------------------


/*
         ----------------------------------------
            -------      -------       -------       
            |hamb.|      |fries|       |drink|
            -------      -------       -------

            -------  |   -------    |  -------
            |     |  |   |     |    |  |     |
            |     |  |   |     |    |  |     |
            |     |  |   |     |    |  |     |
            -------  |   -------    |  -------
                     
            -------      -------       -------
            |apply |     |dism.|       |reset|
            -------      -------       -------
         ----------------------------------------
          
*/

    
  pHamburgerLabel = new CATDlgLabel(this, "HamburgerLabelId");
  CATDlgGridConstraints GC1;
  GC1.Row = 0; GC1.Column = 0; GC1.H_Span = 1; GC1.V_Span = 1; 
  GC1.Justification = CATGRID_CENTER;
  pHamburgerLabel->SetGridConstraints(GC1);

  pFriesLabel = new CATDlgLabel(this, "FriesLabelId");
  GC1.Row = 0; GC1.Column = 2; GC1.H_Span = 1; GC1.V_Span = 1; 
  GC1.Justification = CATGRID_CENTER;
  pFriesLabel->SetGridConstraints(GC1);

  pDrinkLabel = new CATDlgLabel(this, "DrinkLabelId");
  GC1.Row = 0; GC1.Column = 4; GC1.H_Span = 1; GC1.V_Span = 1;
  GC1.Justification = CATGRID_CENTER;
  pDrinkLabel->SetGridConstraints(GC1);

  pHamburgerFrame = new CATDlgFrame(this, "HamburgerFrameId", CATDlgFraNoFrame | CATDlgGridLayout );
  CATDlgGridConstraints GCFH(1,0,1,1, CATGRID_4SIDES);
  pHamburgerFrame->SetGridConstraints(GCFH); 
  pFriesFrame      = new CATDlgFrame(this, "FriesFrameId", CATDlgFraNoFrame | CATDlgGridLayout);
  CATDlgGridConstraints GCFF(1,2,1,1, CATGRID_4SIDES);
  pFriesFrame->SetGridConstraints(GCFF);
  pDrinkFrame     = new CATDlgFrame(this, "DrinkFrameId", CATDlgFraNoFrame | CATDlgGridLayout);
  CATDlgGridConstraints GCFD(1,4,1,1, CATGRID_4SIDES);
  pDrinkFrame->SetGridConstraints(GCFD);
  pSeparator1     = new CATDlgSeparator(this, "Separator1Id", CATDlgCtrVertical);
  CATDlgGridConstraints GCsep1(1,1,1,1,CATGRID_TOP | CATGRID_BOTTOM);
  pSeparator1->SetGridConstraints(GCsep1);
  pSeparator2            = new CATDlgSeparator(this, "Separator2Id", CATDlgCtrVertical);
  CATDlgGridConstraints GCsep2(1,3,1,1,CATGRID_TOP | CATGRID_BOTTOM);
  pSeparator2->SetGridConstraints(GCsep2);

  pApply = new CATDlgPushButton(this, "ApplyId");
  pApply->SetGridConstraints(2,0,1,1,CATGRID_CENTER );

  pDismiss = new CATDlgPushButton(this, "DismissId");
  pDismiss->SetGridConstraints(2,2,1,1,CATGRID_CENTER );

  pReset = new CATDlgPushButton(this, "ResetId");
  pReset->SetGridConstraints(2,4,1,1,CATGRID_CENTER );

  //-------------------------------------------------------------
  // The Hamburger frame contains a set of CATDlgRadioButtons, a
  // set of CATDlgCheckButtons and a CATDlgSlider.
  //--------------------------------------------------------------
  
  // Set of CATDlgCheckButtons (default state is CATDlgUncheck) 
  _pRare       = new CATDlgRadioButton(pHamburgerFrame, "RareId");
  _pRare->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

  _pMedium     = new CATDlgRadioButton(pHamburgerFrame, "MediumId");
  _pMedium->SetGridConstraints(1,0,1,1,CATGRID_LEFT);

  _pWellDone   = new CATDlgRadioButton(pHamburgerFrame, "WellDoneId");
  _pWellDone->SetGridConstraints(2,0,1,1,CATGRID_LEFT);
 
  _pKetchup    = new CATDlgCheckButton(pHamburgerFrame, "KetchupId");
  _pKetchup->SetGridConstraints(0,1,1,1,CATGRID_LEFT);

  _pMustard    = new CATDlgCheckButton(pHamburgerFrame, "MustardId");
  _pMustard->SetGridConstraints(1,1,1,1,CATGRID_LEFT);

  _pPickle     = new CATDlgCheckButton(pHamburgerFrame, "PickleId");
  _pPickle->SetGridConstraints(2,1,1,1,CATGRID_LEFT);

  _pOnion      = new CATDlgCheckButton(pHamburgerFrame, "OnionId");
  _pOnion->SetGridConstraints(0,2,1,1,CATGRID_LEFT);

  _pMayonnaise = new CATDlgCheckButton(pHamburgerFrame, "MayonnaiseId");
  _pMayonnaise->SetGridConstraints(1,2,1,1,CATGRID_LEFT);

  // The slider to choose the count of hamburger
  _pHamburgerQuantity = new CATDlgSlider(pHamburgerFrame,
                                         "HamburgerQuantityId",
                                         CATDlgCtrHorizontal);

  _pHamburgerQuantity->SetGridConstraints(3,0,2,1,CATGRID_LEFT);
  
  // at most 10 hamburger
  _pHamburgerQuantity->SetRange(0.f,10.f,10);
  // allow to have integer values
  _pHamburgerQuantity->SetDecimalPoint(0);
  

  //---------------------------------------------------------------------
  // The fries frame contains a CATDlgLabel,CATDlgCombo and a CATDlgEditor.
  //---------------------------------------------------------------------

  // The label just before the combo
  // -------------------------------
  pSizeOfFriesLabel = new CATDlgLabel(pFriesFrame, "SizeOfFriesLabelId");
  pSizeOfFriesLabel    ->SetGridConstraints(0,0,1,1,CATGRID_LEFT);
  pQuantityOfFriesLabel = new CATDlgLabel(pFriesFrame, "QuantityOfFriesLabelId");
  pQuantityOfFriesLabel->SetGridConstraints(2,0,1,1,CATGRID_LEFT);

  // The fries size combo
  // ---------------------
  _pFriesSize = new CATDlgCombo(pFriesFrame, "FriesSizeId", CATDlgCmbOptionStyle);
  _pFriesSize->SetGridConstraints(0,1,1,1,CATGRID_LEFT);

  // Retrieves the NLS text of each combo's line
  char pcKey[30];
  CATString sKey;
  CATUnicodeString usText;
  CATUnicodeString usFriesSizeLines[5];

  for ( int i = 0; i < 5; i++)
  {
    // Transformation of an int in a char *
    sprintf(pcKey, "FriesSize%d", i);

    // Set this char * in a CATSTring
    sKey = pcKey;

    // retrieves the NLS text 
    if ( 0 != GetResourceValueFromKey(sKey, usText))
    {
       usFriesSizeLines[i]=usText;
    }
  }
  // fill the combo with the 5 lines
  _pFriesSize->SetLine(usFriesSizeLines, 5);

  // Initialize the second line ( indices start from 0 )
  _pFriesSize->SetSelect(1);

  // the Fries quantity editor
  // -------------------------
  _pFriesQuantity = new CATDlgEditor(pFriesFrame, "FriesQuantityId", CATDlgEdtInteger);
  _pFriesQuantity->SetGridConstraints(2,1,1,1,CATGRID_LEFT);
  
  // Initialize with 0 
  CATUnicodeString uszero;
  GetResourceValueFromKey("Zero", uszero);
  _pFriesQuantity->SetLine(uszero);
  

  // quantity : from 0 to 99 
  _pFriesQuantity->SetVisibleTextWidth(2);

  
  //-------------------------------------------------------------------
  // The Drink frame contains a CATDlgSelectorList,CATDlgLabel  and a CATDlgSpinner.
  //--------------------------------------------------------------------
  
  // The list of drink
  _pDrinkList = new CATDlgSelectorList(pDrinkFrame, "DrinkListId", CATDlgLstMultisel);
  _pDrinkList ->SetGridConstraints(0,0,2,1,CATGRID_4SIDES);

  _pDrinkList->SetVisibleTextWidth(16);
  _pDrinkList->SetVisibleTextHeight(4);

  CATUnicodeString usDrinkListLines[12];
  for ( int j= 0; j < 11; j++)
  {
    sprintf(pcKey, "Drink%d", j);
    sKey = pcKey;
    if ( 0 != GetResourceValueFromKey(sKey, usText))
    {
        usDrinkListLines[j]=usText;
    }
  }
  _pDrinkList->SetLine(usDrinkListLines, 11);

  // Drink Label just before the spinner
  pQuantityOfDrinksLabel = new CATDlgLabel(pDrinkFrame, "QuantityOfDrinksLabelId");
  pQuantityOfDrinksLabel->SetGridConstraints(1,0,1,1,CATGRID_LEFT);

  // Drink Quantity
  _pDrinkQuantity = new CATDlgSpinner(pDrinkFrame, "DrinkQuantityId");
  _pDrinkQuantity->SetGridConstraints(1,1,1,1,CATGRID_LEFT);

  // Between 0 and 10 drink
  _pDrinkQuantity->SetRange(0.f,10.f,10);

  // ----------------------------------------------
  // Manage the resizability of the Dialog object
  // ----------------------------------------------
  
  // Allow to resize the center row
  SetGridRowResizable(1,1);

  // Allows to resize the 3 frames (hamburger,fries,drink)
  SetGridColumnResizable(0,1);
  SetGridColumnResizable(2,1);
  SetGridColumnResizable(4,1);
  
  // To resize the Selector List
  pDrinkFrame->SetGridRowResizable(0,1);
  pDrinkFrame->SetGridColumnResizable(1,1);

  //-----------------------------------------------------------------
  // Associate callback functions to the various events which can be
  // triggered by the widgets of the dialog window.
  //-----------------------------------------------------------------
  
  AddAnalyseNotificationCB(_pWellDone, _pWellDone->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Cooking, NULL);
  AddAnalyseNotificationCB(_pRare, _pRare->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Cooking, NULL);
  AddAnalyseNotificationCB(_pMedium, _pMedium->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Cooking, NULL);

  AddAnalyseNotificationCB(_pKetchup, _pKetchup->GetChkBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Seasoning, NULL);
  AddAnalyseNotificationCB(_pMustard, _pMustard->GetChkBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Seasoning, NULL);
  AddAnalyseNotificationCB(_pPickle, _pPickle->GetChkBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Seasoning, NULL);
  AddAnalyseNotificationCB(_pOnion, _pOnion->GetChkBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Seasoning, NULL);
  AddAnalyseNotificationCB(_pMayonnaise, _pMayonnaise->GetChkBModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Seasoning, NULL);

  AddAnalyseNotificationCB(_pHamburgerQuantity,
                           _pHamburgerQuantity->GetSliderModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::HamburgerQuantity, NULL);
  AddAnalyseNotificationCB(_pFriesSize, _pFriesSize->GetComboSelectNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::FriesSize, NULL);
  AddAnalyseNotificationCB(_pFriesQuantity, _pFriesQuantity->GetEditModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::FriesQuantity, NULL);
  AddAnalyseNotificationCB(_pDrinkList, _pDrinkList->GetListSelectNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::DrinkList, NULL);
  AddAnalyseNotificationCB(_pDrinkQuantity, _pDrinkQuantity->GetSpinnerModifyNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::DrinkQuantity, NULL);
  AddAnalyseNotificationCB(pApply, pApply->GetPushBActivateNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Apply, NULL);
  AddAnalyseNotificationCB(pDismiss, pDismiss->GetPushBActivateNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Dismiss, NULL);
  AddAnalyseNotificationCB(pReset, pReset->GetPushBActivateNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Reset, NULL);
  AddAnalyseNotificationCB(this, GetWindCloseNotification(),
                           (CATCommandMethod)&CAADlgBurgerWindow::Dismiss, NULL);

  cout << "CAADlgBurgerWindow::Build End" << endl;
}
                 
//--------------------------------------------------------------------------------------

void CAADlgBurgerWindow::Cooking(CATCommand         * iSendingCommand, 
                                 CATNotification    * iSentNotification, 
                                 CATCommandClientData iUsefulData)
{

  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[2];

  // ----------------------------------
  // Title of the selected Radio Button
  // ---------------------------------- 
  usParam[0] = ((CATDlgRadioButton *)iSendingCommand)->GetTitle();

  // -------------------------------------
  // Gets the NLS word to say Check or not
  // --------------------------------------
  if (((CATDlgRadioButton *)iSendingCommand)->GetState()==CATDlgCheck) {
      GetResourceValueFromKey(CATString("CheckedState"), usParam[1]);
  } else {
      GetResourceValueFromKey(CATString("UncheckedState"), usParam[1]);
  }

  // --------------------------------------------
  // Constructs the NLS message with 2 parameters
  // --------------------------------------------
  CATUnicodeString usMessage ;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "RadioButtonNotification",usParam,2,
                                        "Radio button sends a CATDlgRadBModifyNotification");

  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::Seasoning(CATCommand         * iSendingCommand, 
                                   CATNotification    * iSentNotification, 
                                   CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[2];

  // ----------------------------------
  // Title of the selected Check Button
  // ---------------------------------- 
  usParam[0] = ((CATDlgCheckButton *)iSendingCommand)->GetTitle();

  // -------------------------------------
  // Gets the NLS word to say Check or not
  // --------------------------------------
  if (((CATDlgCheckButton *)iSendingCommand)->GetState()==CATDlgCheck) 
  {
      GetResourceValueFromKey("CheckedState", usParam[1]);
  } else 
  {
      GetResourceValueFromKey("UncheckedState", usParam[1]);
  }

  // --------------------------------------------
  // Constructs the NLS message with 2 parameters
  // --------------------------------------------
  CATUnicodeString usMessage ;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "CheckButtonNotification",usParam,2,
                                        "Check button sends a CATDlgChkBModifyNotification ");

  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::HamburgerQuantity(CATCommand         * iSendingCommand, 
                                           CATNotification    * iSentNotification, 
                                           CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[2];

  // -------------------
  // Title of the slider
  // ------------------- 
  usParam[0] = ((CATDlgSlider *)iSendingCommand)->GetTitle();

  // ------------------------------------
  // Transform an integer in a NLS string
  // ------------------------------------
  usParam[1].BuildFromNum(_pHamburgerQuantity->GetCurrentValue());

  // --------------------------------------------
  // Constructs the NLS message with 2 parameters
  // --------------------------------------------
  CATUnicodeString usMessage ;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                             "SliderNotification",usParam,2,
                             "HamburgerQuantity slider sends a CATDlgSliderModifyNotification");

  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::FriesSize(CATCommand         * iSendingCommand, 
                                   CATNotification    * iSentNotification, 
                                   CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[2];

  // ----------------------------------
  // Title of the Combo
  // ---------------------------------- 
  usParam[0] = ((CATDlgCombo *)iSendingCommand)->GetTitle();

  // ----------------------------------------------------
  // Retrieves the text of the selected line in the Combo
  // ----------------------------------------------------
  int LineSelected = _pFriesSize->GetSelect() ;
  _pFriesSize->GetLine(usParam[1],LineSelected);

  // --------------------------------------------
  // Constructs the NLS message with 2 parameters
  // --------------------------------------------
  CATUnicodeString usMessage ;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "ComboNotification",usParam,2,
                                        "FriesSize combo sends a CATDlgComboSelectNotification ");
  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::FriesQuantity(CATCommand         * iSendingCommand, 
                                       CATNotification    * iSentNotification, 
                                       CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[2];

  // ----------------------------------
  // Title of the editor ( of integer )
  // ---------------------------------- 
  usParam[0] = ((CATDlgEditor *)iSendingCommand)->GetTitle();

  // ----------------------------------------------------
  // Retrieves the given integer
  // ----------------------------------------------------
  _pFriesQuantity->GetLine(usParam[1]);

  // --------------------------------------------
  // Constructs the NLS message with 2 parameters
  // --------------------------------------------
  CATUnicodeString usMessage ;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "EditorNotification",usParam,2,
                                       "FriesQuantity editor sends a CATDlgEditModifyNotification");

  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::DrinkList(CATCommand         * iSendingCommand, 
                                   CATNotification    * iSentNotification,
                                   CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[3];

  // ----------------------------------
  // Title of the selector list 
  // ---------------------------------- 
  usParam[0] = ((CATDlgSelectorList *)iSendingCommand)->GetTitle();

  // ----------------------------------
  // Retrieves at most 2 drinks
  // ---------------------------------- 
  CATUnicodeString SelectedDrink[2];
  int NbLineSelected = 0;
  NbLineSelected = _pDrinkList->GetSelect(SelectedDrink,2); 

  // There is at least one line selected
  usParam[1] = SelectedDrink[0];
    
  CATUnicodeString usMessage ;
  if ( NbLineSelected >= 2 )
  {
    usParam[2] = SelectedDrink[1];

    // ---------------------------------------------
    // Constructs the NLS message with 3 parameters: 
    // Title/first selection/second selection
    // ---------------------------------------------
  
    usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "SelectorListNotificationWith3Params",usParam,3,
                                        "DrinkList selector sends a CATDlgListSelectNotification");
  }
  else
  {
    // ---------------------------------------------
    // Constructs the NLS message with 2 parameters:
    // Title and the unic selection
    // ---------------------------------------------

    usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                     "SelectorListNotificationWith2Params",usParam,2,
                                     "DrinkList selector sends a CATDlgListSelectNotification");
  }

  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::DrinkQuantity(CATCommand         * iSendingCommand, 
                                       CATNotification    * iSentNotification, 
                                       CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[2];

  // ----------------------------------
  // Title of the spinner
  // ---------------------------------- 
  usParam[0] = ((CATDlgSpinner *)iSendingCommand)->GetTitle();

  // -----------------------------------
  // Transform a float into a NLS string 
  // ----------------------------------- 
  usParam[1].BuildFromNum(_pDrinkQuantity->GetCurrentValue());

  // --------------------------------------------
  // Constructs the NLS message with 2 parameters
  // --------------------------------------------
  CATUnicodeString usMessage ;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                              "SpinnerNotification",usParam,2,
                              "DrinkQuantity spinner sends a CATDlgSpinnerModifyNotification");

  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::Apply(CATCommand         * iSendingCommand, 
                               CATNotification    * iSentNotification, 
                               CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[2];

  // ----------------------------------
  // Title of the Button Apply
  // ----------------------------------
  usParam[0] = ((CATDlgPushButton *)iSendingCommand)->GetTitle();

  // --------------------------------------------
  // Constructs the NLS message with 1 parameters
  // --------------------------------------------
  CATUnicodeString usMessage ;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "PushButtonNotification",usParam,1,
                                        "Apply button sends a CATDlgPushBActivateNotification");
  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;


  // ------------------------------------------------
  // Constructs the first sentence without parameters
  // ------------------------------------------------
  CATUnicodeString usMyOrder ;
  usMyOrder = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "Msg.Order",NULL,0,
                                        "I have ordered:\n");

  // --------------------------------------------
  // Constructs the NLS order message
  // --------------------------------------------
  if ( _pHamburgerQuantity->GetCurrentValue() > 0 )
  {
    if (_pRare->GetState()==CATDlgCheck)
      usParam[1] = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                               "Msg.Rare",NULL,0,"Rare");                                                                            
    else if (_pMedium->GetState()==CATDlgCheck)
      usParam[1] = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                               "Msg.Medium",NULL,0,"Medium");

    else if (_pWellDone->GetState()==CATDlgCheck)
      usParam[1] =  CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                "Msg.Welldone",NULL,0,"Welldone");
    else
      usParam[1] = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow","Msg.Null",NULL,0,"");


    usParam[0].BuildFromNum(_pHamburgerQuantity->GetCurrentValue());

 
    usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                        "Msg.Hamburger",usParam,2,
                                        "hamburger(s) with:\n") );
                    
    if (_pKetchup->GetState()==CATDlgCheck)
      usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                   "Msg.Ketchup",NULL,0,"Ketchup"));
    if (_pMustard->GetState()==CATDlgCheck)
      usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                       "Msg.Mustard",NULL,0,"Mustard"));
    if (_pPickle->GetState()==CATDlgCheck)
      usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                   "Msg.Pickle",NULL,0,"Pickle"));
    if (_pOnion->GetState()==CATDlgCheck)
      usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                   "Msg.Onion",NULL,0,"Onion"));
    if (_pMayonnaise->GetState()==CATDlgCheck)
      usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                   "Msg.Mayonnaise",NULL,0,"Mayonnaise"));
  }

  if ( _pFriesQuantity->GetIntegerValue() > 0 )
  {
    CATUnicodeString usParam[2];

    _pFriesQuantity->GetLine(usParam[0]);

    _pFriesSize->GetLine(usParam[1], _pFriesSize->GetSelect());

    usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                 "Msg.Fries",usParam,2,"fries\n"));
  }

  if ( _pDrinkQuantity->GetCurrentValue() > 0 )
  {
    CATUnicodeString usParam[2];

    usParam[0].BuildFromNum(_pDrinkQuantity->GetCurrentValue());

    // Retrieves only the first line
    _pDrinkList->GetSelect(&(usParam[1]),1);

    usMyOrder.Append(CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                                 "Msg.Drinks",usParam,2,"Drinks\n"));
  }

  // ----------------------------------------------------
  // Creation of the window which will contain the  order 
  // ----------------------------------------------------
  if (  NULL == _pOrderWindow ) 
  {
    // It's the first order

    // Window notify deleted when the window application will be deleted
    _pOrderWindow = new CATDlgNotify(this, "MyOrderId", CATDlgNfyOK);

    // Callbacks to hide the window after the end user click OK
    AddAnalyseNotificationCB(_pOrderWindow,
                             _pOrderWindow->GetNfyOKNotification(),
                 (CATCommandMethod)&CAADlgBurgerWindow::NotifyOK, NULL);
  }

  // ---------------------------------------------------
  // Display the order, usMyOrder, in a CATDlgNotify Window
  // ---------------------------------------------------
  _pOrderWindow->SetText(usMyOrder);
  _pOrderWindow->SetVisibility(CATDlgShow);
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::Dismiss(CATCommand         * iSendingCommand,
                                 CATNotification    * iSentNotification, 
                                 CATCommandClientData iUsefulData)
{
  cout << "CAADlgBurgerWindow::Dismiss Begin" << endl;

  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[1];

  // --------------------------------
  // The Title of the Dismiss Button
  // --------------------------------
  usParam[0] = ((CATDlgPushButton *)iSendingCommand)->GetTitle();

  // ----------------------------------------
  // Constructs the NLS message with 1 param
  // ----------------------------------------
  CATUnicodeString usMessage;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                       "PushButtonNotification",usParam,1,
                                       "Dismiss button sends CATDlgPushBActivateNotification\n");
  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;

  // -------------------------------------------
  // Application and Window will be soon deleted.
  // --------------------------------------------
  _pCAABurgerApplication->Destroy();

  cout << "CAADlgBurgerWindow::Dismiss End" << endl;
}

//--------------------------------------------------------------------------------------
void CAADlgBurgerWindow::Reset(CATCommand         * iSendingCommand,
                               CATNotification    * iSentNotification,
                               CATCommandClientData iUsefulData)
{
  if ( NULL == iSendingCommand ) return ;

  CATUnicodeString usParam[1];

  // --------------------------
  // Title of the Reset Button
  // -------------------------- 
  usParam[0] = ((CATDlgPushButton *)iSendingCommand)->GetTitle();

  // ----------------------------------------
  // Constructs the NLS message with 1 param
  // ----------------------------------------
  CATUnicodeString usMessage;
  usMessage = CATMsgCatalog::BuildMessage("CAADlgBurgerWindow",
                                          "PushButtonNotification",usParam,1,
                                          "Reset button sends CATDlgPushBActivateNotification \n");
  // -----------------------------------
  // Message sent in the standard output 
  // -----------------------------------
  cout << usMessage.ConvertToChar() << endl;


  // ----------------------------------------
  // Reset all the dialog object
  // ----------------------------------------

  // Hamburger Frame: each check button and the slider
  _pRare    ->SetState(CATDlgUncheck);
  _pMedium  ->SetState(CATDlgUncheck);
  _pWellDone->SetState(CATDlgUncheck);
  _pKetchup    ->SetState(CATDlgUncheck);
  _pMustard    ->SetState(CATDlgUncheck);
  _pPickle     ->SetState(CATDlgUncheck);
  _pOnion      ->SetState(CATDlgUncheck);
  _pMayonnaise->SetState(CATDlgUncheck);

  _pHamburgerQuantity->SetCurrentValue(0.f);

  // Fries Frame: the combo and the quantity editor 

  // The line selected is as the beginning
  _pFriesSize->SetSelect(1);

  // The quantity is as the beginning
  CATUnicodeString uszero;
  GetResourceValueFromKey("Zero", uszero);
  _pFriesQuantity->SetLine(uszero);

  // Drink Frame: the drink selector list and the quantity spinner
  int nbselection = _pDrinkList->GetSelectCount() ;
  cout << " You have had choosen " << nbselection  << " type of drink" << endl;
  _pDrinkList->ClearSelect();
  nbselection = _pDrinkList->GetSelectCount() ;

  if ( 0 == nbselection )
  {
     cout << " Now the selector list is empty" << endl;
  }else
  {
	  cout << " Pb in the infrastructure software " << endl; 
  }

  // The quantity is as the beginning
  _pDrinkQuantity->SetCurrentValue(0.f);

}

//--------------------------------------------------------------------------------------

void CAADlgBurgerWindow::NotifyOK(CATCommand         * iSendingCommand, 
                                  CATNotification    * iSentNotification, 
                                  CATCommandClientData iUsefulData)
{
  // --------------------------------------------------
  // Hide the panel just after the end user clicks OK
  // --------------------------------------------------
  _pOrderWindow->SetVisibility(CATDlgHide);
}
