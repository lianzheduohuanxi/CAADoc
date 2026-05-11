// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAVisBaseViewpointDlg.h"
#include "CAAVisBaseNewViewpointNotification.h"

//Dialog Framework
#include "CATDlgFrame.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgRadioButton.h"

//Mathematics Framework
#include "CATProjectionType.h"
#include "CATMathPointf.h"
#include "CATMathDirectionf.h"

//-------------------------------------------------------------------------------

CAAVisBaseViewpointDlg::CAAVisBaseViewpointDlg(CATDialog *iParent,
                                               const CATString& iObjectName,
                                               CATDlgStyle iStyle)
:CATDlgDialog(iParent, iObjectName,
              iStyle | CATDlgWndOK | CATDlgWndAPPLY | CATDlgWndCANCEL
              | CATDlgWndAutoResize | CATDlgWndNoResize | CATDlgWndModal)
{
  _pInitialOrigin        = NULL;
  _pInitialSight         = NULL;
  _InitialProjectionType = CONIC;
  _InitialFocus          = 0.0;
  _InitialAngle          = 0.0;

  _pCurrentOrigin        = NULL;
  _pCurrentSight         = NULL;
  _CurrentProjectionType = CONIC;
  _CurrentFocus          = 0.0;
  _CurrentAngle          = 0.0;

  //Stored Dialog objects:
  _pOriginXEditor        = NULL;
  _pOriginYEditor        = NULL;
  _pOriginZEditor        = NULL;
  _pSightXEditor         = NULL;
  _pSightYEditor         = NULL;
  _pSightZEditor         = NULL;
  _pConicRadioButton     = NULL;
  _pCylindricRadioButton = NULL;
  _pFocusEditor          = NULL;
  _pAngleEditor          = NULL;
  
}

//-------------------------------------------------------------------------------

CAAVisBaseViewpointDlg::~CAAVisBaseViewpointDlg()
{
  // All the dialog's children are automatically released by the dialog.
  // That's why the menu widgets are not deallocated here.
  // The subscriptions by AddAnalyseNotificationCB are also cancelled 
  // automatically.

  //Deletion of initial values
  if(NULL != _pInitialOrigin )
    {
      delete _pInitialOrigin;
      _pInitialOrigin = NULL;
    }

  if( NULL != _pInitialSight)
    {
      delete _pInitialSight;
      _pInitialSight = NULL;
    }

  //Deletion of current values:
  if(NULL != _pCurrentOrigin)
    {
      delete _pCurrentOrigin;
      _pCurrentOrigin = NULL;
    }

  if(NULL != _pCurrentSight)
    {
      delete _pCurrentSight;
      _pCurrentSight = NULL;
    }

  //Stored Dialog objects:
  _pOriginXEditor        = NULL;
  _pOriginYEditor        = NULL;
  _pOriginZEditor        = NULL;
  _pSightXEditor         = NULL;
  _pSightYEditor         = NULL;
  _pSightZEditor         = NULL;
  _pConicRadioButton     = NULL;
  _pCylindricRadioButton = NULL;
  _pFocusEditor          = NULL;
  _pAngleEditor          = NULL;
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::Build()
{
  //Every dialog objects created here, are not explicitly
  //deleted in this class. Indeed, dialog objects deletion is
  //managed by an application global mechanism, and must never be
  //deleted by the class which allocated them.
  
  //Global frame
  //------------
  CATDlgFrame *pGlobalFrame = new CATDlgFrame(this, "GlobalContainer", CATDlgFraNoFrame | CATDlgFraNoTitle | CATDlgGridLayout);

  //
  //  Vectors frame
  //  -------------
  CATDlgFrame *pVectorsFrame = new CATDlgFrame(pGlobalFrame, "VectorsFrame", CATDlgFraNoTitle | CATDlgGridLayout);

  //    -Origin frame-
  CATDlgFrame *pOriginFrame = new CATDlgFrame(pVectorsFrame, "OriginFrame", CATDlgGridLayout);

  //      X label
  CATDlgLabel *pOriginXLabel = new CATDlgLabel(pOriginFrame, "X");
  //      X Editor
  _pOriginXEditor = new CATDlgEditor(pOriginFrame, "XEditor", CATDlgEdtDouble);

  //      Y label
  CATDlgLabel *pOriginYLabel = new CATDlgLabel(pOriginFrame, "Y");
  //      Y Editor
  _pOriginYEditor = new CATDlgEditor(pOriginFrame, "YEditor", CATDlgEdtDouble);

  //      Z label
  CATDlgLabel *pOriginZLabel = new CATDlgLabel(pOriginFrame, "Z");
  //      Z Editor
  _pOriginZEditor = new CATDlgEditor(pOriginFrame, "ZEditor", CATDlgEdtDouble);


  //    -Sight direction frame-
  CATDlgFrame *pSightFrame = new CATDlgFrame(pVectorsFrame, "SightFrame", CATDlgGridLayout);

  //      X label
  CATDlgLabel *pSightXLabel = new CATDlgLabel(pSightFrame, "X");
  //      X Editor
  _pSightXEditor = new CATDlgEditor(pSightFrame, "XEditor", CATDlgEdtDouble);

  //      Y label
  CATDlgLabel *pSightYLabel = new CATDlgLabel(pSightFrame, "Y");
  //      Y Editor
  _pSightYEditor = new CATDlgEditor(pSightFrame, "YEditor", CATDlgEdtDouble);

  //      Z label
  CATDlgLabel *pSightZLabel = new CATDlgLabel(pSightFrame, "Z");
  //      Z Editor
  _pSightZEditor = new CATDlgEditor(pSightFrame, "ZEditor", CATDlgEdtDouble);
  

  //
  //  Values Frame
  //  ------------
  CATDlgFrame *pValuesFrame = new CATDlgFrame(pGlobalFrame, "ValuesFrame", CATDlgFraNoTitle | CATDlgGridLayout);

  //    -Projection radio buttons-

  //      Conical projection
  _pConicRadioButton = new CATDlgRadioButton(pValuesFrame, "Conical");

  //      Cylindrical projection
  _pCylindricRadioButton = new CATDlgRadioButton(pValuesFrame, "Cylindrical");

  //    -Other values-

  //      Focus distance
  //        label
  CATDlgLabel *pFocusLabel = new CATDlgLabel(pValuesFrame, "FocusLabel");
  //        editor
  _pFocusEditor = new CATDlgEditor(pValuesFrame, "FocusEditor", CATDlgEdtDouble);

  //      Angle
  //        label
  CATDlgLabel *pAngleLabel = new CATDlgLabel(pValuesFrame, "AngleLabel");
  //        editor
  _pAngleEditor = new CATDlgEditor(pValuesFrame, "AngleEditor", CATDlgEdtDouble);

  
  //---------------------
  //Layout's organization
  //---------------------
  //pGlobalFrame->SetDefaultOrientation(Vertical);
  
  //pGlobalFrame->Attach4Sides(pVectorsFrame);
  //pGlobalFrame->Attach4Sides(pValuesFrame);
  
  //pVectorsFrame->Attach4Sides(pOriginFrame);
  //pVectorsFrame->Attach4Sides(pSightFrame);

  pVectorsFrame->SetGridConstraints(0,                                    //lign 0 
                                    0,                                    //column 0
                                    1,                                    //length 
                                    1,                                    //height
                                    CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_LEFT);
                                    //CATGRID_LEFT);

  pValuesFrame->SetGridConstraints(1,                                    //lign 0 
                                   0,                                    //column 0
                                   1,                                    //length 
                                   1,                                    //height
                                   CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_LEFT);
                                   //CATGRID_LEFT);
  
  //Set the grid constraints for the Vectors frames :
  pOriginFrame->SetGridConstraints(0,                                    //lign 0 
                                   0,                                    //column 0
                                   1,                                    //length 
                                   1,                                    //height
                                   //CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_LEFT);
                                   CATGRID_LEFT);

  pSightFrame->SetGridConstraints(0,                                    //lign 0
                                  1,                                    //column 1
                                  1,                                    //length 
                                  1,                                    //height
                                  //CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_RIGHT);
                                  CATGRID_RIGHT); 


  //Set the grid constraints for the Origin frame's elements
  //X
  pOriginXLabel->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);
  _pOriginXEditor->SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);

  //Y
  pOriginYLabel->SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);
  _pOriginYEditor->SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);

  //Z
  pOriginZLabel->SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);
  _pOriginZEditor->SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);


  //Set the grid constraints for the Sight frame's elements
  //X
  pSightXLabel->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);
  _pSightXEditor->SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);

  //Y
  pSightYLabel->SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);
  _pSightYEditor->SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);

  //Z
  pSightZLabel->SetGridConstraints(2, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);
  _pSightZEditor->SetGridConstraints(2, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_CENTER);


  //Set the grid constraints for Projection radio buttons:
  _pConicRadioButton->SetGridConstraints(0, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_LEFT);
  _pCylindricRadioButton->SetGridConstraints(1, 0, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_LEFT);

  //Set the grid constraints for Focus, Angle and Zoom :
  //Focus
  pFocusLabel->SetGridConstraints(0, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_RIGHT);
  _pFocusEditor->SetGridConstraints(0, 2, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_RIGHT);

  //Angle
  pAngleLabel->SetGridConstraints(1, 1, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_RIGHT);
  _pAngleEditor->SetGridConstraints(1, 2, 1, 1, CATGRID_4SIDES | CATGRID_CST_HEIGHT | CATGRID_RIGHT);


  //Callbacks:
  //Origin
  //
  //  _pOriginXEditor
  AddAnalyseNotificationCB(_pOriginXEditor, _pOriginXEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::OriginCB,
                           (CATCommandClientData)CATINT32ToPtr(0));
  //  _pOriginYEditor
  AddAnalyseNotificationCB(_pOriginYEditor, _pOriginYEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::OriginCB,
                           (CATCommandClientData)CATINT32ToPtr(1));

  //  _pOriginZEditor
  AddAnalyseNotificationCB(_pOriginZEditor, _pOriginZEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::OriginCB,
                           (CATCommandClientData)CATINT32ToPtr(2));

  //Sight
  //
  //  _pSightXEditor
  AddAnalyseNotificationCB(_pSightXEditor, _pSightXEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::SightCB,
                           (CATCommandClientData)CATINT32ToPtr(0));
  //  _pSightYEditor
  AddAnalyseNotificationCB(_pSightYEditor, _pSightYEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::SightCB,
                           (CATCommandClientData)CATINT32ToPtr(1));

  //  _pSightZEditor
  AddAnalyseNotificationCB(_pSightZEditor, _pSightZEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::SightCB,
                           (CATCommandClientData)CATINT32ToPtr(2));

  //Projection Type
  AddAnalyseNotificationCB(_pConicRadioButton, _pConicRadioButton->GetRadBModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::ProjectionTypeCB,
                           (CATCommandClientData)CATINT32ToPtr(0));
  AddAnalyseNotificationCB(_pCylindricRadioButton, _pCylindricRadioButton->GetRadBModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::ProjectionTypeCB,
                           (CATCommandClientData)CATINT32ToPtr(1));

  //Focus distance
  AddAnalyseNotificationCB(_pFocusEditor, _pFocusEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::FocusCB, NULL);

  //Angle
  AddAnalyseNotificationCB(_pAngleEditor, _pAngleEditor->GetEditModifyNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::AngleCB, NULL);

 
  //Add notifications on OK, Apply, CANCEL buttons:
  //OK
  AddAnalyseNotificationCB(this, GetDiaOKNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::OKCB, NULL);

  //Apply
  AddAnalyseNotificationCB(this, GetDiaAPPLYNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::APPLYCB, NULL);

  //cancel
  AddAnalyseNotificationCB(this, GetDiaCANCELNotification(),
                           (CATCommandMethod)& CAAVisBaseViewpointDlg::CANCELCB, NULL);  
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::Init(const CATMathPointf     &iOrigin,
                                  const CATMathDirectionf &iSightDirection,
                                  CATProjectionType    iProjectionType,
                                  float             iFocusDitance,
                                  float             iAngle)
{
  //Initializations of data members:
  _pInitialOrigin         = new CATMathPointf(iOrigin);
  _pInitialSight          = new CATMathDirectionf(iSightDirection);
  _InitialProjectionType  = iProjectionType;
  _InitialFocus           = iFocusDitance;
  _InitialAngle           = iAngle;

  _pCurrentOrigin         = new CATMathPointf(iOrigin);
  _pCurrentSight          = new CATMathDirectionf(iSightDirection);
  _CurrentProjectionType  = iProjectionType;
  _CurrentFocus           = iFocusDitance;
  _CurrentAngle           = iAngle;

  //Initialization of dialog fields
  _pOriginXEditor->SetValue(iOrigin.x, 0);  //0 not to generate an event from this initialization.
  _pOriginYEditor->SetValue(iOrigin.y, 0);  //0 not to generate an event from this initialization.
  _pOriginZEditor->SetValue(iOrigin.z, 0);  //0 not to generate an event from this initialization.

  _pSightXEditor->SetValue(iSightDirection.x, 0);  //0 not to generate an event from this initialization.
  _pSightYEditor->SetValue(iSightDirection.y, 0);  //0 not to generate an event from this initialization.
  _pSightZEditor->SetValue(iSightDirection.z, 0);  //0 not to generate an event from this initialization.

  if(CONIC == iProjectionType)
    {
      _pConicRadioButton->SetState(CATDlgCheck, 0);  //0 not to generate an event from this initialization.
      _pCylindricRadioButton->SetState(CATDlgUncheck, 0);  //0 not to generate an event from this initialization.
    }
  else
    {
      _pConicRadioButton->SetState(CATDlgUncheck, 0);  //0 not to generate an event from this initialization.
      _pCylindricRadioButton->SetState(CATDlgCheck, 0);  //0 not to generate an event from this initialization.
    }

  _pFocusEditor->SetValue(iFocusDitance, 0);  //0 not to generate an event from this initialization.
  _pAngleEditor->SetValue(iAngle, 0);  //0 not to generate an event from this initialization.

}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::OriginCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  //Data indicates whether X, Y or Z has been modified.
  int data = CATPtrToINT32(iData);

  
  switch(data)
    {
    case 0:
      _pCurrentOrigin->x = _pOriginXEditor->GetValue();
      break;
    case 1:
      _pCurrentOrigin->y = _pOriginYEditor->GetValue();
      break;
    case 2:
      _pCurrentOrigin->z = _pOriginZEditor->GetValue();
      break;
    }

  //Warns the application of the new parameters:
  SendNotif();
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::SightCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
    //Data indicates whether X, Y or Z has been modified.
  int data = CATPtrToINT32(iData);
  
  
  switch(data)
    {
    case 0:
      _pCurrentSight->x = _pSightXEditor->GetValue();
      break;
    case 1:
      _pCurrentSight->y = _pSightYEditor->GetValue();
      break;
    case 2:
      _pCurrentSight->z = _pSightZEditor->GetValue();
      break;
    }

  //Normalizes the sight vector. This must be called as we changed
  //data.
  //_pCurrentSight->Normalize();
  
  //Warns the application of the new parameters:
  SendNotif();
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::ProjectionTypeCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  //Data indicates whether the CONIC or CYLINDRIC radio button was checked.
  int data = CATPtrToINT32(iData);
  
  
  switch(data)
    {
    case 0:  //CONIC
      _CurrentProjectionType = CONIC;
      break;
    case 1:  //CYLINDRIC
      _CurrentProjectionType = CYLINDRIC;
      break;
    }

  //Warns the application of the new parameters:
  SendNotif();
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::FocusCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  _CurrentFocus = _pFocusEditor->GetValue();

  //Warns the application of the new parameters:
  SendNotif();
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::AngleCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  _CurrentAngle = _pAngleEditor->GetValue();

  //Warns the application of the new parameters:
  SendNotif();
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::OKCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  // Deallocates the dialog. A window deallocation must be postponed until all
  // the notifications already sent are treated. That's why the  
  // RequestDelayedDestruction method must be used instead of Release.
  RequestDelayedDestruction();
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::APPLYCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  //The initial state is reseted.
  delete _pInitialOrigin;
  delete _pInitialSight;
  
  _pInitialOrigin         = new CATMathPointf(*_pCurrentOrigin);
  _pInitialSight          = new CATMathDirectionf(*_pCurrentSight);
  _InitialProjectionType  = _CurrentProjectionType;
  _InitialFocus           = _CurrentFocus;
  _InitialAngle           = _CurrentAngle;
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::CANCELCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
  CAAVisBaseNewViewpointNotification * pCancelNotif = new CAAVisBaseNewViewpointNotification(_pInitialOrigin,
                                                                                             _pInitialSight,
                                                                                             _InitialProjectionType,
                                                                                             _InitialFocus,
                                                                                             _InitialAngle);
  //Sending of this notification to be received by the application:
  //The notification is sent to the father (Application frame). As
  //the application frame doesn't treate it, it is transfered to its
  //father, the application, which treats it.
  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  SendNotification(GetFather(), pCancelNotif);

  // Deallocates the dialog. A window deallocation must be postponed until all
  // the notifications already sent are treated. That's why the  
  // RequestDelayedDestruction method must be used instead of Release.
  RequestDelayedDestruction();
}

//-------------------------------------------------------------------------------

void CAAVisBaseViewpointDlg::SendNotif()
{
  //Building of a new notification
  CAAVisBaseNewViewpointNotification * pNotif = new CAAVisBaseNewViewpointNotification(_pCurrentOrigin,
                                                                                       _pCurrentSight,
                                                                                       _CurrentProjectionType,
                                                                                       _CurrentFocus,
                                                                                       _CurrentAngle);

  //Sending of this notification to be received by the application:
  //The notification is sent to the father (Application frame). As
  //the application frame doesn't treate it, it is transfered to its
  //father, the application, which treats it.

  //
  // Notice: No need to destroy notification because 
  // it will be destroyed automatically .
  //
  SendNotification(GetFather(), pNotif);
}

