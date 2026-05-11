//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
// Local Framework
#include "CAACafElementPropertyPageDlg.h"
#include "CAAICafGeometryEltSettingAtt.h"

#include "GetCAACafGeometryEltSettingCtrl.h"

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

//---------------------------------------------------------------------------------
CAACafElementPropertyPageDlg::CAACafElementPropertyPageDlg(CATDialog * parent) :
 CATDlgFrame(parent, "GeometryElementTO", CATDlgFraNoFrame|CATDlgGridLayout),
 _pIdHide(NULL), _pIdShow(NULL), _pIdPreSelectShow(NULL),
 _pImplPointShow(NULL),_pImplPointHide(NULL),
 _pMaxPoint(NULL)
{
   cout << "CAACafElementPropertyPageDlg::CAACafElementPropertyPageDlg" << endl;

   // Retrieves the Setting Controller with its CAAICafGeometryEltSettingAtt 
   // interface pointer.
   _pISettingAttForCtrl = NULL ;
   ::GetCAACafGeometryEltSettingCtrl(IID_CAAICafGeometryEltSettingAtt,
	                                              (void**)&_pISettingAttForCtrl);

}
//---------------------------------------------------------------------------------
CAACafElementPropertyPageDlg::~CAACafElementPropertyPageDlg()
{
   cout << "CAACafElementPropertyPageDlg::~CAACafElementPropertyPageDlg" << endl;
   
   // Dialog's object automaticaly deleted
   _pIdHide = NULL ; 
   _pIdShow =NULL ; 
   _pIdPreSelectShow = NULL ;

   _pImplPointShow = NULL ; 
   _pImplPointHide =NULL ;
   _pMaxPoint = NULL ; 

  if ( NULL != _pISettingAttForCtrl )
  {
     _pISettingAttForCtrl->Release();
     _pISettingAttForCtrl = NULL ;
  }
}
//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::Build()
{
  cout << "CAACafElementPropertyPageDlg::Build Begin" << endl;

  if ( NULL == _pISettingAttForCtrl )
  {
     return ;
  }

  
  // Any ToolsOptions page can contain several CATDlgToolsOptionsFrame with
  // include :
  //    - A Title 
  //    - An Icon (optional)
  //    - An invisible Separator (except for the last frame)
  //
  // In this case, the page contains 3 CATDlgToolsOptionsFrame:
  //
  //   1- Frame = Identifier Type Frame   ( Without Icon )
  //   2- Frame = Max Point to discretize Curves  ( With  Icon )
  //   3- Frame = Implicit Point ( With Icon )

  // 1- First Frame
   CATDlgFrame * pIdentifierFrame = NULL ;

  CATDlgToolsOptionsFrame * pToolsOptionsFrame1 = NULL ;

  CATString    TOFrameId1      = "Identifier" ;
  CATString    IconName1      = "" ;
  // The frame contains no Icon but an invisible separator
  CATDlgStyle  TOFrameStyle1   = CATDlgToolsOptionsInvisibleIcon ; 
  pToolsOptionsFrame1 = new CATDlgToolsOptionsFrame(this,TOFrameId1,IconName1,TOFrameStyle1);

  // Retrieves the frame which is the father of all widget created after.
  pIdentifierFrame = pToolsOptionsFrame1->GetOptionsFrame();

  pToolsOptionsFrame1->SetGridConstraints(0,0,1,1,CATGRID_TOP);


     // Lock sets at the top 
     CATSettingInfo InfoForLockForId ;
     _pISettingAttForCtrl->GetInfoIdentifierVisibility(&InfoForLockForId);

     CATDlgLock * pIdentifierLock = NULL ;
     pIdentifierLock = new CATDlgLock(pIdentifierFrame,"IdentifierLock",InfoForLockForId);
     

     // the fourth argument is to declared that the lock is attached on
     // 3 rows.
     pIdentifierLock->SetGridConstraints(0,0,1,3,CATGRID_LEFT);

     // 3 Radio buttons 
     _pIdHide   = new CATDlgRadioButton(pIdentifierFrame, "IdHide");
     _pIdHide->SetGridConstraints(0,1,1,1,CATGRID_LEFT);
     pIdentifierLock->AddAssociatedDialog(_pIdHide);

     _pIdShow  = new CATDlgRadioButton(pIdentifierFrame, "IdShow");
     _pIdShow->SetGridConstraints(1,1,1,1,CATGRID_LEFT);
     pIdentifierLock->AddAssociatedDialog(_pIdShow);

     _pIdPreSelectShow = new CATDlgRadioButton(pIdentifierFrame, "IdPreSelectShow");
     _pIdPreSelectShow->SetGridConstraints(2,1,1,1,CATGRID_LEFT);
     pIdentifierLock->AddAssociatedDialog(_pIdPreSelectShow);

  // 2- Second Frame
  CATDlgFrame * pMaxPointCurveFrame = NULL ;

  CATDlgToolsOptionsFrame * pToolsOptionsFrame2 = NULL ;

  CATString    TOFrameId2      = "MaxPointCurve" ;

  // No .CATRsc file : Here you give the name of the icon 
  CATString    IconName2      = "I_CAAToolsOptionsEltMaxPointCurve" ;

  // The frame contains a visible icon and an invisible separator.
  CATDlgStyle  TOFrameStyle2   = NULL ; 
  pToolsOptionsFrame2 = new CATDlgToolsOptionsFrame(this,TOFrameId2,IconName2,TOFrameStyle2);
  pToolsOptionsFrame2->SetGridConstraints(1,0,1,1,CATGRID_TOP);
  
  // Retrieves the frame which is the father of all widget created after.
  pMaxPointCurveFrame = pToolsOptionsFrame2->GetOptionsFrame();

      // Lock sets before the slider
     CATSettingInfo * pInfoList = NULL ;
     int nbInfo = 0;
     _pISettingAttForCtrl->GetInfoMaxPointCurve(&pInfoList,&nbInfo);

     CATDlgLock * pMaxPointLock = NULL ;
     pMaxPointLock = new CATDlgLock(pMaxPointCurveFrame,"MaxPointLock",pInfoList,nbInfo);
     delete [] pInfoList ;
     pInfoList = NULL ;

     pMaxPointLock->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

      // Slider in the pMaxPointCurveFrame frame
     _pMaxPoint = new CATDlgSlider(pMaxPointCurveFrame, "MaxPoint");
     _pMaxPoint->SetRange(2, 100, 100);
     _pMaxPoint->SetGridConstraints(0,1,1,1,CATGRID_CENTER);
 
     // The lock is associated to one dialog object, the slider
	 pMaxPointLock->AddAssociatedDialog(_pMaxPoint);


  // 3- Third Frame
  CATDlgFrame * pImplicitPointFrame = NULL ;

  CATDlgToolsOptionsFrame * pToolsOptionsFrame3 = NULL ;

  CATString    TOFrameId3      = "ImplicitePoint" ;

  // No .CATRsc file : Here you give the name of the icon 
  CATString    IconName3      = "I_CAAToolsOptionsEltImplicitePoint" ;

  // The Frame contains a visible icon and no separator.
  // For the last frame of a page this options is mandatory
  //
  CATDlgStyle  TOFrameStyle3   = CATDlgToolsOptionsBottomFrame ; 
  pToolsOptionsFrame3 = new CATDlgToolsOptionsFrame(this,TOFrameId3,IconName3,TOFrameStyle3);

  // Retrieves the frame which is the father of all widget created after.
  pImplicitPointFrame = pToolsOptionsFrame3->GetOptionsFrame();

  pToolsOptionsFrame3->SetGridConstraints(2,0,1,1,CATGRID_TOP);

     // Lock sets before the 2 buttons
     CATSettingInfo InfoForLockForImplPoint ;
     _pISettingAttForCtrl->GetInfoImplPointVisibility(&InfoForLockForImplPoint);

     CATDlgLock * pImplicitPointLock = NULL ;
     pImplicitPointLock = new CATDlgLock(pImplicitPointFrame,"ImplicitPointLock",
                                                    InfoForLockForImplPoint);
     
     // the fourth argument is to declared that the lock is attached on
     // 1 row.
     pImplicitPointLock->SetGridConstraints(0,0,1,1,CATGRID_LEFT);

     // 2 radio buttons
     _pImplPointShow = new CATDlgRadioButton(pImplicitPointFrame, "ImplPointShow");
     _pImplPointShow->SetGridConstraints(0,1,1,1,CATGRID_RIGHT);
	 pImplicitPointLock->AddAssociatedDialog(_pImplPointShow);

     _pImplPointHide = new CATDlgRadioButton(pImplicitPointFrame, "ImplPointHide");
     _pImplPointHide->SetGridConstraints(0,2,1,1,CATGRID_RIGHT);
	 pImplicitPointLock->AddAssociatedDialog(_pImplPointHide);

  // Callback, to modify the repository 
  //

  AddAnalyseNotificationCB(_pIdHide,
                           _pIdHide->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafElementPropertyPageDlg::IdHideCB,
                           NULL);

  AddAnalyseNotificationCB(_pIdShow,
                           _pIdShow->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafElementPropertyPageDlg::IdShowCB,
                           NULL);

  AddAnalyseNotificationCB(_pIdPreSelectShow,
                           _pIdPreSelectShow->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafElementPropertyPageDlg::IdPreSelectShowCB,
                           NULL);

  AddAnalyseNotificationCB(_pMaxPoint,
                           _pMaxPoint->GetSliderModifyNotification(),
                           (CATCommandMethod)&CAACafElementPropertyPageDlg::MaxPointCB,
                           NULL);

  AddAnalyseNotificationCB(_pImplPointShow,
                           _pImplPointShow->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafElementPropertyPageDlg::ImplPointShowCB,
                           NULL);

  AddAnalyseNotificationCB(_pImplPointHide,
                           _pImplPointHide->GetRadBModifyNotification(),
                           (CATCommandMethod)&CAACafElementPropertyPageDlg::ImplPointHideCB,
                           NULL);
}

//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::ValueSettings()
{

  CATString ident; 
  _pISettingAttForCtrl->GetIdentifierVisibility(ident);

  if      (ident == "IdHide")           _pIdHide->SetState(CATDlgCheck, 0);
  else if (ident == "IdShow")           _pIdShow->SetState(CATDlgCheck, 0);
  else if (ident == "IdPreSelectShow")  _pIdPreSelectShow->SetState(CATDlgCheck, 0);
     
  int maxpoint;
  _pISettingAttForCtrl->GetMaxPointCurve(maxpoint);

  float maxpointf = maxpoint ;
  _pMaxPoint->SetCurrentValue(maxpointf, 0);

  CATString implpoint; 
  _pISettingAttForCtrl->GetImplPointVisibility(implpoint);

  if      (implpoint == "ImplPointHide")  _pImplPointHide->SetState(CATDlgCheck, 0);
  else if (implpoint == "ImplPointShow")  _pImplPointShow->SetState(CATDlgCheck, 0);

}

//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::IdHideCB  (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData)
{
 
  if (_pIdHide->GetState() == CATDlgCheck)
  {
     _pISettingAttForCtrl->SetIdentifierVisibility("IdHide");
  }

}

//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::IdShowCB (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData)
{

  if (_pIdShow->GetState() == CATDlgCheck)
  {
     _pISettingAttForCtrl->SetIdentifierVisibility("IdShow");
  }
}

//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::IdPreSelectShowCB (CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData)
{
 
  if (_pIdPreSelectShow->GetState() == CATDlgCheck)
  {
     _pISettingAttForCtrl->SetIdentifierVisibility("IdPreSelectShow");
  }

}

//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::MaxPointCB(CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData)
{

  float max = _pMaxPoint->GetCurrentValue();

  int maxpoint = max ;
  _pISettingAttForCtrl->SetMaxPointCurve(maxpoint);


}

//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::ImplPointShowCB(CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData)
{

  if (_pImplPointShow->GetState() == CATDlgCheck)
  {
	 _pISettingAttForCtrl->SetImplPointVisibility("ImplPointShow");
  }
}

//---------------------------------------------------------------------------------
void CAACafElementPropertyPageDlg::ImplPointHideCB(CATCommand         * iPublishingCommand,
                              CATNotification    * iNotification,
                              CATCommandClientData iUsefulData)
{

  if (_pImplPointHide->GetState() == CATDlgCheck)
  {
	 _pISettingAttForCtrl->SetImplPointVisibility("ImplPointHide");
  }
}

