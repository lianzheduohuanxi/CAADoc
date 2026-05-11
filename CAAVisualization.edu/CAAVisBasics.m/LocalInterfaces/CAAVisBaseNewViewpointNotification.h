#ifndef CAAVisBaseNewViewpointNotification_h
#define CAAVisBaseNewViewpointNotification_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class is the notification sent by the dialog object, used
//  to change the viewpoint parameters, to the application to warn him
//  of the new viewpoint parameters. These parameters are stored in this notification,
//  and can be retrieve by the application.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseNewViewpointNotification
//             CATNotification (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
// 
//
//===========================================================================

//System Framework
#include "CATNotification.h"

//Visualization Framework
#include "CATProjectionType.h"

//Mathematics Framework
class CATMathPointf;
class CATMathDirectionf;

class CAAVisBaseNewViewpointNotification : public CATNotification
{
  CATDeclareClass;

public:

  // Constructs a notification from the different
  // viewpoint parameters controled by the dialog
  // object.
  // Parameters
  //   iOrigin
  //     The viewpoint origin
  //   iSight
  //     The viewpoint sight direction
  //   iProjection
  //     The viewpoint projection type. CONIC or CYLINDRICAL.
  //   iFocus
  //     The viewpoint focus distance
  //   iAngle
  //     The viewpoint angle
  CAAVisBaseNewViewpointNotification(CATMathPointf      *iOrigin,
                                     CATMathDirectionf  *iSight,
                                     CATProjectionType     iProjection,
                                     float              iFocus,
                                     float              iAngle);

  //Destructor
  virtual ~CAAVisBaseNewViewpointNotification();

  //Gets the viewpoint origin
  CATMathPointf * GetOrigin();

  //Gets the Sight direction
  CATMathDirectionf * GetSightDirection();

  //Gets the projection type
  CATProjectionType GetProjectionType();

  //Gets the focus distance
  float GetFocusDistance();

  //Gets the angle value
  float GetAngle();

private:

  //Default constructor
  CAAVisBaseNewViewpointNotification();

  //Copy constructor
  CAAVisBaseNewViewpointNotification(const CAAVisBaseNewViewpointNotification &iBrother);

  //Assignment operator
  CAAVisBaseNewViewpointNotification & operator = (const CAAVisBaseNewViewpointNotification &iBrother);

private:

  //values:
  CATMathPointf      *_pOrigin;
  CATMathDirectionf  *_pSight;
  CATProjectionType     _ProjectionType;
  float              _Focus;
  float              _Angle;
};

#endif
