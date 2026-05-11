// COPYRIGHT DASSAULT SYSTEMES 2007

#define FULL_TEST
#define FILL_LIST1
#define FILL_LIST2

#include "CATTestListViewDocument.h"
#include "CATTestListViewAppli.h"

#include "CATDlgDialog.h"
#include "CATDlgGridConstraints.h"

#include "CATDlgBarMenu.h"
#include "CATDlgCheckItem.h"
#include "CATDlgEditor.h"
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgPushButton.h"
#include "CATDlgPushItem.h"
#include "CATDlgRadioItem.h"
#include "CATDlgSplitter.h"
#include "CATDlgSubMenu.h"

// SCA : CATDlgTable on the left-hand side
#include <SampleColViewModel.h>
#include <SampleViewModel.h>

// SCA : CATDlgTable on the right-hand side
#include <SampleColVariantModel.h>
#include <SampleVariantModel.h>

#include <SampleViewController.h>
#include <SampleListEditor.h>

#include "CATIDlgTableViewColumnModel.h"
#include "CATIDlgTableViewModel.h"

#include "iostream.h"

#define Sample_WIDTH1 100
#define Sample_WIDTH2 100
#define Sample_HEIGHT 300
#ifdef FULL_TEST
#define Sample_NB_ROWS 1000
#define Sample_NB_VARS 500
#else
#define Sample_NB_ROWS 10
#define Sample_NB_VARS 10
#endif

static SampleListEditor *GDEMultiList01 = NULL;
static SampleListEditor *GDEMultiList02 = NULL;
static SampleViewController* GDEControl01 = NULL;
static SampleViewController* GDEControl02 = NULL;

CATDlgFrame *SampleFrameButtons = NULL;

// Constructor
//---------------
CATTestListViewDocument::CATTestListViewDocument (CATTestListViewAppli *father, const CATString &name, CATDlgStyle style, const int savevrml)
  :CATDlgDocument(father, name, style), _Appli(father)
{
  // Menu bar creation
  //---------------------
  CATDlgBarMenu *menuBar = new CATDlgBarMenu(this, "menubar");
 
  AddAnalyseNotificationCB(this,
    GetWindCloseNotification(),
    (CATCommandMethod)& CATTestListViewDocument::exit, NULL);
  
  // Start menu creation in the menu bar
  //---------------------------------------
  CATDlgSubMenu *Start = new CATDlgSubMenu(menuBar, "Start");
  
  // Creation of the Proto Push Item in the Start Menu
  //-----------------------------------------------------
  CATDlgPushItem *SPanel = new CATDlgPushItem(Start, "Proto");
    AddAnalyseNotificationCB(SPanel, SPanel->GetMenuIActivateNotification(),
                             (CATCommandMethod) &CATTestListViewDocument::CreateSampleProto, NULL);
  
  // Creation of the Exit Push Item in the Start Menu
  //----------------------------------------------------
  SPanel = new CATDlgPushItem(Start, "Exit");
    AddAnalyseNotificationCB(SPanel, SPanel->GetMenuIActivateNotification(),
                             (CATCommandMethod) &CATTestListViewDocument::exit, NULL);
  
  // Tables creation
  //-------------------
  CreateSampleProto(NULL, NULL, NULL);
}

// Destructor
//--------------
CATTestListViewDocument::~CATTestListViewDocument()
{
  _Appli = NULL;
}

// On exit the application is destroyed
//----------------------------------------
void CATTestListViewDocument::exit ( CATCommand *, CATNotification *, CATCommandClientData)
{
  if ( NULL != _Appli )
    _Appli->Destroy();
}

//-------------------------------------------------------------------------------
void CATTestListViewDocument::CreateSampleProto(CATCommand *, CATNotification *, CATCommandClientData)
{
cout << this << "->CreateSampleProto()" << endl;

  CATDialog* pFather = this;
  
  // Creation of a dialog window ( pop up ) 
  //------------------------------------------
  CATDlgDialog* pDlgDialog = new CATDlgDialog(pFather, "SearchForCommands",
                                              CATDlgGridLayout|CATDlgWndBtnOKCancel);
  {
    // Dialog Box Management
    //------------------------- 
    pDlgDialog->SetDefaultButton(NULL);
    pDlgDialog->SetTitle("Proto Sample");
    pDlgDialog->SetGridRowResizable(0, 0);
    pDlgDialog->SetGridRowResizable(1, 1);
    pDlgDialog->SetGridColumnResizable(0, 1);
    pDlgDialog->SetGridColumnResizable(0, 1);
    pDlgDialog->SetGridRowResizable(0, 0);
    pDlgDialog->SetGridRowResizable(1, 1);

    // Dialog box position definition
    //----------------------------------
    DPOS pos;
    pos.x = 10;
    pos.y = 50;
    pDlgDialog->SetRectPosition(pos);
    
    // Dialog box button frame creation
    //------------------------------------
    SampleFrameButtons = new CATDlgFrame(pDlgDialog, "FrameButtons", CATDlgFraNoFrame|CATDlgGridLayout);
    {
      CATDlgLabel *icon01 = new CATDlgLabel (SampleFrameButtons, "icon01");
      icon01->SetIconName("CATIALogoNTP2");
      icon01->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

      CATDlgLabel *lab01 = new CATDlgLabel (SampleFrameButtons, "lab01");
      lab01->SetTitle("Vehicle : ");
      lab01->SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

      CATDlgEditor *edit01 = new CATDlgEditor(SampleFrameButtons, "edit01");
      edit01->SetVisibleTextWidth(10);
      edit01->SetText("XXUPG253-E");
      edit01->SetGridConstraints (1, 1, 1, 1, CATGRID_4SIDES);

      CATDlgLabel *foo1 = new CATDlgLabel (SampleFrameButtons, "foo1");
      foo1->SetTitle("         ");
      foo1->SetGridConstraints(1, 2, 1, 1, CATGRID_4SIDES);

      CATDlgLabel *lab02 = new CATDlgLabel (SampleFrameButtons, "lab02");
      lab02->SetTitle("UPG : ");
      lab02->SetGridConstraints(1, 3, 1, 1, CATGRID_4SIDES);

      CATDlgEditor *edit02 = new CATDlgEditor(SampleFrameButtons, "edit02");
      edit02->SetVisibleTextWidth(10);
      edit02->SetText("XXUPG253-E");
      edit02->SetGridConstraints (1, 4, 1, 1, CATGRID_4SIDES);

      CATDlgLabel *foo2 = new CATDlgLabel (SampleFrameButtons, "foo2");
      foo2->SetTitle("                                         ");
      foo2->SetGridConstraints(1, 5, 1, 1, CATGRID_4SIDES);

      CATDlgPushButton *PushButtonEdit = new CATDlgPushButton (SampleFrameButtons, "PushButtonEdit");
      PushButtonEdit->SetTitle("Force Cells Values");
      PushButtonEdit->SetGridConstraints(1, 6, 1, 1, CATGRID_4SIDES);

      CATDlgEditor *edit03 = new CATDlgEditor(SampleFrameButtons, "edit03");
      edit03->SetVisibleTextWidth(10);
      edit03->SetText("VC-xxx");
      edit03->SetGridConstraints (1, 7, 1, 1, CATGRID_4SIDES);

      AddAnalyseNotificationCB(PushButtonEdit,
                               PushButtonEdit->GetPushBActivateNotification(),
                               (CATCommandMethod)& CATTestListViewDocument::OnForceEditCB,
                               (CATCommandClientData) edit03);

      CATDlgPushButton *PushButtonMaxi = new CATDlgPushButton (SampleFrameButtons, "PushButtonMaxi");
      PushButtonMaxi->SetTitle("Maximize/Restore");
      PushButtonMaxi->SetGridConstraints(1, 8, 1, 1, CATGRID_4SIDES);

      AddAnalyseNotificationCB(PushButtonMaxi,
                               PushButtonMaxi->GetPushBActivateNotification(),
                               (CATCommandMethod)& CATTestListViewDocument::OnForceMaxiCB,
                               (CATCommandClientData) pDlgDialog);
    }
    
    // Split the frame in two parts, one for each table
    //----------------------------------------------------
    CATDlgSplitter *SplitFrame = new CATDlgSplitter(pDlgDialog, "Split", CATDlgCtrHorizontal);
    SplitFrame->SetVisibility(CATDlgShow);
    
    // Sets the splitter's sash position in the middle of the frame
    //---------------------------------------------------------
    double iPos = 0.5;
    SplitFrame->SetSashPosition(iPos);
    
    // Creates a new frame for the first table
    //-------------------------------------------
    CATDlgFrame *FrameMultiList1 = new CATDlgFrame(SplitFrame, "FrameMultiList1",
                                                   CATDlgGridLayout|CATDlgFraNoFrame|CATDlgFraNoTitle);
    FrameMultiList1->SetGridRowResizable(0, 1);
    FrameMultiList1->SetGridColumnResizable(0, 1);
    FrameMultiList1->SetRectDimensions(0, 0, Sample_HEIGHT, Sample_WIDTH1);
    {
      // SCA : Inspiration. Editor creation
      //--------------------------------------
      GDEMultiList01 = new SampleListEditor( FrameMultiList1, "Result", CATRightScroll|CATListSortable|CATListHeaderFullWidth|CATListHeaderAlwaysVisible );

      // SCA Row headers activation
      //------------------------------
      GDEMultiList01->SetRowHeadersEnabled(1);

      // SCA : Creation of a controller in order to have a GetLabel and a GetIcon
      //----------------------------------------------------------------------------
      GDEControl01 = new SampleViewController(GDEMultiList01);
      GDEMultiList01->SetController(GDEControl01);

      // SCA : CATListView argument in order to test the model recovery 
      //------------------------------------------------------------------
      SampleColViewModel *columns = new SampleColViewModel();
      columns->DefineTheColumns(10);

      // SCA : SetController was added for column highlight
      //------------------------------------------------------
      columns->SetController(GDEControl01);

      //CATIColumnModel_var colmodel(columns);
      CATIDlgTableViewColumnModel_var colmodel(columns);
      GDEMultiList01->SetColumnModel(colmodel);
      GDEMultiList01->Invalidate();

      columns->Release();
      columns = NULL;

      // SCA : Model creation for the first table
      //--------------------------------------------
      SampleViewModel *model= new SampleViewModel();
#ifdef FILL_LIST1
      // Fill the columns with default values
      //----------------------------------------
      model->FillTheColumns(Sample_NB_ROWS);
#endif
      CATIDlgTableViewModel_var rm(model);
      model->Release();
      model = NULL;
      GDEMultiList01->SetModel(rm);
      GDEControl01->SetModel(rm);

      AddAnalyseNotificationCB(GDEMultiList01,  
                               GDEMultiList01->GetSelectionNotification(),  
                               (CATCommandMethod)&CATTestListViewDocument::OnSelectionCB01,  
                                NULL  );
    }
    
    // Creates a new frame for the second table
    //--------------------------------------------
    CATDlgFrame *FrameMultiList2 = new CATDlgFrame(SplitFrame, "FrameMultiList2",
                                                   CATDlgGridLayout|CATDlgFraNoFrame|CATDlgFraNoTitle);
    FrameMultiList2->SetGridRowResizable(0, 1);
    FrameMultiList2->SetGridColumnResizable(0, 1);
    FrameMultiList2->SetRectDimensions(0, 0, Sample_HEIGHT, Sample_WIDTH2);
    {
      // SCA : Inspiration
      //---------------------
      GDEMultiList02 = new SampleListEditor( FrameMultiList2, "Result", CATRightScroll|CATListSortable|CATListHeaderFullWidth|CATListHeaderAlwaysVisible );

      // SCA Displays the rows headers
      //---------------------------------
      GDEMultiList02->SetRowHeadersEnabled(1);

      // SCA : A controller is created, otherwise GetLabel and GetIcon are not called
      //--------------------------------------------------------------------------------
      GDEControl02 = new SampleViewController(GDEMultiList02);
      GDEMultiList02->SetController(GDEControl02);

      // SCA : CATListView argument in order to test the model recovery
      //------------------------------------------------------------------
      SampleColVariantModel *columns = new SampleColVariantModel();
      columns->DefineTheColumns(Sample_NB_VARS);

      // SCA : SetController was added for column highlight
      //------------------------------------------------------
      columns->SetController(GDEControl02);

      //CATIColumnModel_var colmodel(columns);
      CATIDlgTableViewColumnModel_var colmodel(columns);
      GDEMultiList02->SetColumnModel(colmodel);
      GDEMultiList02->Invalidate();

      columns->Release();
      columns = NULL;

      // SCA : Create model
      //----------------------
      SampleVariantModel *model= new SampleVariantModel();
#ifdef FILL_LIST2
      model->FillTheColumns(Sample_NB_ROWS, Sample_NB_VARS);
#endif
      CATIDlgTableViewModel_var rm(model);
      model->Release();
      model = NULL;
      GDEMultiList02->SetModel(rm);
      GDEControl02->SetModel(rm);

      // Can be directly call from the controller (to be replaced)
      AddAnalyseNotificationCB(GDEMultiList02,  
                               GDEMultiList02->GetSelectionNotification(),  
                               (CATCommandMethod)&CATTestListViewDocument::OnSelectionCB02,  
                                NULL  );

    }

    // SCA: It is the controller 2, list of right-hand side, which controls the controller 1, 
    // the list of left-hand side. (the right controls the left), because Hide is FALSE, 
    // therefore the elevator of GDEControl02 is not mask.
    //------------------------------------------------------------------------------------------
    GDEControl02->Synchronize(GDEMultiList01, GDEControl01);

    //SCA : Idem but different syntax, Hide is TRUE, therefore the elevator of GDEControl01 is mask.
    //GDEControl01->Synchronize(GDEMultiList02, GDEControl02, TRUE);
    //SCA : The opposite, the left-hand side controls the right-hand side
    //GDEControl01->Synchronize(GDEMultiList02, GDEControl02);
    //-------------------------------------------------------------------------------------------------

    // Attachments of the 3 frames
    //-------------------------------
    SampleFrameButtons->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
    SplitFrame->SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);
  }

  AddAnalyseNotificationCB(pDlgDialog, pDlgDialog->GetDiaOKNotification(),
                           (CATCommandMethod)& CATTestListViewDocument::OnCloseListCB, NULL);
  AddAnalyseNotificationCB(pDlgDialog, pDlgDialog->GetDiaCANCELNotification(),
                           (CATCommandMethod)& CATTestListViewDocument::OnCloseListCB, NULL);
  AddAnalyseNotificationCB(pDlgDialog, pDlgDialog->GetWindCloseNotification(),
                           (CATCommandMethod)& CATTestListViewDocument::OnCloseListCB, NULL);

  pDlgDialog->SetVisibility(CATDlgShow);
}

//--------------------------------------------------------------------------------------
void CATTestListViewDocument::OnCloseListCB(CATCommand * from, CATNotification *, CATCommandClientData  )
{
  CATDlgDialog* pDialog = (CATDlgDialog*)from;
  pDialog->RequestDelayedDestruction();
  pDialog = NULL;
}

//--------------------------------------------------------------------------------------
void CATTestListViewDocument::OnSelectionCB01(CATCommand * from, CATNotification *, CATCommandClientData  )
{
  cout << "CATTestListViewDocument::OnSelectionCB01" << endl << flush;

  //As example: a selection in the view model, clears selection in the variant model
  //-----------------------------------------------------------------------------------
  GDEControl02->ClearSelection(0);
}

//--------------------------------------------------------------------------------------
void CATTestListViewDocument::OnSelectionCB02(CATCommand * from, CATNotification *, CATCommandClientData  )
{
  cout << "CATTestListViewDocument::OnSelectionCB02" << endl << flush;

  //As example: a selection in the variant model, clears selection in the view model
  //-----------------------------------------------------------------------------------
  GDEControl01->ClearSelection(0);

  //As example: sets a new label
  //------------------------------
  CATListOfSampleCell pSelectedCells(GDEControl02->GetSelectedCells());
  CATIDlgTableViewModel_var vModel( GDEControl02->GetModel() );
  if (!!vModel)
    for (int i=1; i<=pSelectedCells.Size(); i++)
      vModel->SetLabel((pSelectedCells[i]).GetRow(), (pSelectedCells[i]).GetColumn(), "Selected");
  GDEMultiList02->Invalidate();
}

//--------------------------------------------------------------------------------------
void CATTestListViewDocument::OnForceEditCB(CATCommand * from, CATNotification *, CATCommandClientData  idata)
{
  cout << "CATTestListViewDocument::OnForceEditCB" << endl << flush;
  CATDlgEditor *edit = (CATDlgEditor *) idata;
  CATUnicodeString foo("Selected for PushButton");
  if( edit && edit->IsAKindOf(CATDlgEditor::ClassName()))
    foo = edit->GetText();

  CATListOfSampleCell pSelectedCells(GDEControl02->GetSelectedCells());
  CATIDlgTableViewModel_var vModel( GDEControl02->GetModel() );
  if (!!vModel)
    for (int i=1; i<=pSelectedCells.Size(); i++)
      vModel->SetLabel((pSelectedCells[i]).GetRow(), (pSelectedCells[i]).GetColumn(), foo);
  GDEMultiList02->Invalidate();
}
//--------------------------------------------------------------------------------------

static int DialogRectDx = -1;
static int DialogRectDy = -1;
static int DialogRectMx = 0;

//--------------------------------------------------------------------------------------
void CATTestListViewDocument::OnForceMaxiCB(CATCommand * from, CATNotification *, CATCommandClientData  idata)
{
  cout << "CATTestListViewDocument::OnForceMaxiCB" << endl << flush;
  CATDlgDialog *dlg = (CATDlgDialog *) idata;
  if (dlg)
  {
    DRECT DialogRect;
    dlg->GetRectDimensions(&DialogRect);
    cout << "  DialogBox : " << DialogRect.dx << "x" << DialogRect.dy
         << " en (" << DialogRect.x << ", " << DialogRect.y << ")" << endl;
    if (DialogRectDx == -1 || DialogRectDy == -1)
    {
      DialogRectDx = DialogRect.dx;
      DialogRectDy = DialogRect.dy;
    }
    if (DialogRectMx == 0)
    {
      int oHeigth = 0;
      int oWidth = 0;
      dlg->GetMaximumSize(&oHeigth, &oWidth);
      DialogRectMx  = 1;
      DialogRect.x  = 50;
      DialogRect.y  = 100;
      DialogRect.dx = oWidth-100;
      DialogRect.dy = oHeigth-200;
      dlg->SetRectDimensions(DialogRect);
    }
    else
    {
      DialogRectMx  = 0;
      DialogRect.x  = 50;
      DialogRect.y  = 100;
      DialogRect.dx = DialogRectDx;
      DialogRect.dy = DialogRectDy;
      dlg->SetRectDimensions(DialogRect);
    }
  }
}
