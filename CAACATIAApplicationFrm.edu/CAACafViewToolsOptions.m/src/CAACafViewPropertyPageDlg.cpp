//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework
#include "CAACafViewPropertyPageDlg.h"
#include "CAAICafGeometryViewSettingAtt.h"
#include "GetCAACafGeometryViewSettingCtrl.h"

// Dialog Framework
#include "CATDlgInclude.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLock.h"

// System Framework 
#include "CATSettingInfo.h"

// CATIAApplicationFrame Framework 
#include "CATDlgToolsOptionsFrame.h"

// others
#include <iostream.h>

//-------------------------------------------------------------------------
CAACafViewPropertyPageDlg::CAACafViewPropertyPageDlg(CATDialog * parent) :
 CATDlgFrame(parent, "GeometryViewTO", CATDlgFraNoFrame|CATDlgGridLayout),
 _pIdAxis(NULL), _pIdPlane(NULL), _pIdWall(NULL)
{
  // Retrieves the Setting Controller with its CAAICafGeometryViewSettingAtt 
   // interface pointer.
   _pISettingAttForCtrl = NULL ;
   ::GetCAACafGeometryViewSettingCtrl(IID_CAAICafGeometryViewSettingAtt,
	                                              (void**)&_pISettingAttForCtrl);
}

//-------------------------------------------------------------------------
CAACafViewPropertyPageDlg::~CAACafViewPropertyPageDlg()
{
   cout << "CAACafViewPropertyPageDlg::~CAACafViewPropertyPageDlg" << endl;
   
   _pIdAxis = NULL ;
   _pIdPlane = NULL ;
   _pIdWall = NULL;
   
  if ( NULL != _pISettingAttForCtrl )
  {
     _pISettingAttForCtrl->Release();
     _pISettingAttForCtrl = NULL ;
  }
}

//-------------------------------------------------------------------------
void CAACafViewPropertyPageDlg::Build()
{
   cout << "CAACafViewPropertyPageDlg::Build" << endl;
  
  if ( NULL == _pISettingAttForCtrl )
  {
     return ;
  }

  CATDlgFrame * p3DRepresentationFrame = NULL ;

  // Any ToolsOptions page can contain several CATDlgToolsOptionsFrame with
  // the look :
  //    - A Title 
  //    - An Icon (optionnel)
  //    - An invisible Separator (not for the last frame)
  //
  // In this case, the page contains one CATDlgToolsOptionsFrame without
  // icon 
  //

  CATDlgToolsOptionsFrame * pToolsOptionsFrame = NULL ;

  CATString    TOFrameId      = "3DRepresentation" ;
  CATString    IconeName      = "" ;

  // CATDlgToolsOptionsBottomFrame -> While it's the last frame 
  // CATDlgToolsOptionsNoIcon      -> one frame without icon, so no aligment is necessary
  //
  CATDlgStyle  TOFrameStyle   = CATDlgToolsOptionsNoIcon | CATDlgToolsOptionsBottomFrame; 
  pToolsOptionsFrame = new CATDlgToolsOptionsFrame(this,TOFrameId,IconeName,TOFrameStyle);

  // Retrieves the frame which is the father of all widget created after.
  p3DRepresentationFrame = pToolsOptionsFrame->GetOptionsFrame();


     // Lock sets at the top 
     CATSettingInfo InfoForLock ;
     CATDlgLock * p3DRepresentationLock = NULL ;
     _pISettingAttForCtrl->GetInfo3DRepresentationMode(&InfoForLock);
     p3DRepresentationLock = new CATDlgLock(p3DRepresentationFrame,"3DRepresentationLock",InfoForLock); 
     
	 // the fourth argument is to declared that the lock is attached on
	 // 3 rows.
	 p3DRepresentationLock->SetGridConstraints(0,0,1,3,CATGRID_LEFT);

     // 3 radio buttons
     _pIdAxis   = new CATDlgRadioButton(p3DRepresentationFrame, "IdAxis");
     _pIdAxis->SetGridConstraints(0,1,1,1,CATGRID_LEFT);
     p3DRepresentationLock->AddAssociatedDialog(_pIdAxis);

     _pIdPlane  = new CATDlgRadioButton(p3DRepresentationFrame, "IdPlane");
     _pIdPlane->SetGridConstraints(1,1,1,1,CATGRID_LEFT);
     p3DRepresentationLock->AddAssociatedDialog(_pIdPlane);

     _pIdWall = new CATDlgRadioButton(p3DRepresentationFrame, "IdWall");
     _pIdWall->SetGridConstraints(2,1,1,1,CATGRID_LEFT);
     p3DRepresentationLock->AddAssociatedDialog(_pIdWall);

  // Callback, to modify the repository 
  //

  AddAnalyseNotificationCB(_pIdAxis,
                           _pIdAxis->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafViewPropertyPageDlg::OnRadModify,
                           (void*) 1);
  AddAnalyseNotificationCB(_pIdPlane,
                           _pIdPlane->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafViewPropertyPageDlg::OnRadModify,
                           (void*) 2);
  AddAnalyseNotificationCB(_pIdWall,
                           _pIdWall->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafViewPropertyPageDlg::OnRadModify,
                           (void*) 3);

}

//-------------------------------------------------------------------------
void CAACafViewPropertyPageDlg::ValueSettings()
{
 
  if ( NULL != _pISettingAttForCtrl )
  {
     CATString ident; 
     _pISettingAttForCtrl->Get3DRepresentationMode(ident);


     if      (ident == "IdAxis")   _pIdAxis->SetState(CATDlgCheck, 0);
     else if (ident == "IdPlane")  _pIdPlane->SetState(CATDlgCheck, 0);
     else if (ident == "IdWall")   _pIdWall->SetState(CATDlgCheck, 0);
  }

}


//-------------------------------------------------------------------------
void CAACafViewPropertyPageDlg::OnRadModify  (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData)
{

  if ( NULL != _pISettingAttForCtrl )
  {
     int radio = CATPtrToINT32(iUsefulData) ;

     switch ( radio )
     {
     case 1 : 
        if (_pIdAxis->GetState() == CATDlgCheck)
		{
           _pISettingAttForCtrl->Set3DRepresentationMode("IdAxis");
		}
        break ;
     case 3 : 
        if (_pIdPlane->GetState() == CATDlgCheck)
		{
           _pISettingAttForCtrl->Set3DRepresentationMode("IdPlane");
		}
        break ;
     case 2 : 
        if (_pIdWall->GetState() == CATDlgCheck)
		{
           _pISettingAttForCtrl->Set3DRepresentationMode("IdWall");
		}
        break ;
     }
  }

}

