// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseNewViewpointNotification.h"


CATImplementClass(CAAVisBaseNewViewpointNotification, Implementation, CATNotification, CATNull);

//-------------------------------------------------------------------------------

CAAVisBaseNewViewpointNotification::CAAVisBaseNewViewpointNotification(CATMathPointf      *iOrigin,
                                                                       CATMathDirectionf  *iSight,
                                                                       CATProjectionType     iProjection,
                                                                       float              iFocus,
                                                                       float              iAngle)
:CATNotification(CATNotificationDeleteOn)
{
   // We use the CATNotificationDeleteOn parameter to say that we want this 
   // notification to be automatically
   // delete at the end of the next transaction (as defines by the System FrameWork).
   //
  _pOrigin        = iOrigin;
  _pSight         = iSight;
  _ProjectionType = iProjection;
  _Focus          = iFocus;
  _Angle           = iAngle;
}

//-------------------------------------------------------------------------------

CAAVisBaseNewViewpointNotification::~CAAVisBaseNewViewpointNotification()
{
  //The data members are not owned by the notification. It must not
  //delete them.
  _pOrigin        = NULL;
  _pSight         = NULL;
  
}

//-------------------------------------------------------------------------------

CATMathPointf * CAAVisBaseNewViewpointNotification::GetOrigin()
{
  return _pOrigin;
}

//-------------------------------------------------------------------------------

CATMathDirectionf * CAAVisBaseNewViewpointNotification::GetSightDirection()
{
  return _pSight;
}

//-------------------------------------------------------------------------------

CATProjectionType CAAVisBaseNewViewpointNotification::GetProjectionType()
{
  return _ProjectionType;
}

//-------------------------------------------------------------------------------

float CAAVisBaseNewViewpointNotification::GetFocusDistance()
{
  return _Focus;
}

//-------------------------------------------------------------------------------

float CAAVisBaseNewViewpointNotification::GetAngle()
{
  return _Angle;
}

//-------------------------------------------------------------------------------
