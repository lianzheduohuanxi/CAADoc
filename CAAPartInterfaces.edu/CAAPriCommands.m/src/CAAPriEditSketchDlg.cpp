// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAPriEditSketchDlg.h"
#include "CAAPriEditSketchNotification.h"

// ObjectModelerBase Framework
#include "CATIAlias.h"

// ObjectSpecModeler
#include "CATISpecObject.h"

// Dialog Framework
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgPushButton.h"
#include "CATDlgFrame.h"


// C++ Standard Library
#include "iostream.h"

//------------------------------------------------------------------------------------------

CAAPriEditSketchDlg::CAAPriEditSketchDlg(CATDialog * iParent): 
      CATDlgDialog (iParent,"CAAPriEditSketchDlg",
                    CATDlgWndBtnOKCancel | CATDlgGridLayout),_pLabelOfTheProfile(NULL)
{
   cout << "CAAPriEditSketchDlg::CAAPriEditSketchDlg" << endl; 
}

//--------------------------------------------------------------------------------------

CAAPriEditSketchDlg::~CAAPriEditSketchDlg()
{
  cout << "CAAPriEditSketchDlg::~CAAPriEditSketchDlg" << endl;
  _pLabelOfTheProfile = NULL ;
}

//--------------------------------------------------------------------------------------

void CAAPriEditSketchDlg::Build()
{
   // Frame Text Explanation

   CATDlgFrame * pFrameTextExpl = new CATDlgFrame(this,"FrameTextExplId", CATDlgGridLayout);
   pFrameTextExpl -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

   CATDlgLabel * pLabelTextExpl = new CATDlgLabel(pFrameTextExpl, "LabelTextExplId");
   pLabelTextExpl -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);

   // Frame Sketch Edition
   CATDlgFrame * pFrameProfile = new CATDlgFrame(this,"FrameProfileId", CATDlgGridLayout);
   pFrameProfile -> SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES);

   _pLabelOfTheProfile = new CATDlgLabel(pFrameProfile, "LabelOfTheProfileId");
   _pLabelOfTheProfile -> SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES);
 
   CATDlgPushButton * pEditSketchPB = new CATDlgPushButton(pFrameProfile,"EditSketchPBId");
   pEditSketchPB -> SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES);


   // Callbacks to edit the sketch
   AddAnalyseNotificationCB (pEditSketchPB, 
                              pEditSketchPB->GetPushBActivateNotification(),
                              (CATCommandMethod)&CAAPriEditSketchDlg::EditSketch,
                              NULL);
                              
}

//--------------------------------------------------------------------------------------

void CAAPriEditSketchDlg::SetElement(CATISpecObject * pISpecObjectOnProfile )
{
   if ( (NULL != pISpecObjectOnProfile) && (NULL!=_pLabelOfTheProfile) )
   {
      CATIAlias * pIAlias = NULL ;
      HRESULT rc = pISpecObjectOnProfile->QueryInterface(IID_CATIAlias, 
                                                 (void **) & pIAlias);
      if ( SUCCEEDED(rc) )
      {
          CATUnicodeString Name = pIAlias->GetAlias();

          _pLabelOfTheProfile->SetTitle(Name);

          pIAlias->Release();
          pIAlias = NULL ;
      }
   }
}

//--------------------------------------------------------------------------------------

void CAAPriEditSketchDlg::EditSketch(CATCommand* cmd, 
                                  CATNotification* evt, 
                                  CATCommandClientData data)
{
   cout <<" CAAPriEditSketchDlg::EditSketch" << endl;

   // No need to delete the notification
   CAAPriEditSketchNotification * pNotif = new CAAPriEditSketchNotification();
   SendNotification(GetFather(),pNotif);
   pNotif = NULL ;
}

