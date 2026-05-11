#ifndef CAAVisBaseViewpointDlg_h
#define CAAVisBaseViewpointDlg_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//  Viewpoint Dialog box class.
//  The "Modify viewpoint" push item allows the
//  user to control the Viewpoint parameters through
//  this dialog box.
//  The parameters controled by this dialog box are :
//    - Viewpoint origin
//    - Viewpoint sight direction
//    - Viewpoint projection type
//    - Viewpoint focus distance
//    - Viewpoint Angle
//  
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBaseViewpointDlg
//             CATDlgDialog (Dialog Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Build : to build the dialog objects: editors, radio buttons...
//
//  Init  : to init the different dialog box fields to correct values.
//  
//===========================================================================

//Dialog Framework
#include "CATDlgDialog.h"

//Visualization Framework
#include "CATProjectionType.h"

//Mathematic Framework"
class CATMathPointf;
class CATMathDirectionf;

//Dialog Framework
class CATDlgEditor;
class CATDlgRadioButton;

class CAAVisBaseViewpointDlg : public CATDlgDialog
{
  // Declares the CAAVisBaseViewpointDlg.CATNls file as the dialog message catalog
  DeclareResource(CAAVisBaseViewpointDlg, CATDlgDialog)
      
public:

  // Constructs a Dialog box.
  // Parameters
  //   iParent
  //     The parent dialog object. Here, the
  //     application frame.
  //   iObjectName
  //     The name of our dialog object.
  //   iStyle
  //     The style wanted for our dialog box.
  CAAVisBaseViewpointDlg(CATDialog *iParent,
                         const CATString& iObjectName,
                         CATDlgStyle iStyle = NULL);

  //Destructor
  virtual ~CAAVisBaseViewpointDlg();

  // Builds the dialog box
  void Build();

  // Initilializes the dialog box fields from viewpoints
  // parameters intial values.
  // Parameters
  //   iOrigin
  //     The viewpoint initial origin
  //   iSightDirection
  //     The viewpoint initial sight direction
  //   iProjectionType
  //     The viewpoint initial projection type. CONIC or CYLINDRIC.
  //   iFocusDistance
  //     The viewpoint initial focus distance
  //   iAngle
  //     The viewpoint initial angle
  void Init(const CATMathPointf     &iOrigin,
            const CATMathDirectionf &iSightDirection,
            CATProjectionType    iProjectionType,
            float             iFocusDistance,
            float             iAngle);

private:

  //Default constructor
  CAAVisBaseViewpointDlg();

  //Copy constructor
  CAAVisBaseViewpointDlg(const CAAVisBaseViewpointDlg &iBrother);
  
  //Assignment operator
  CAAVisBaseViewpointDlg & operator = (const CAAVisBaseViewpointDlg &iBrother);
  
  //Callbacks
  void OriginCB        (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void SightCB         (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void ProjectionTypeCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void FocusCB         (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void AngleCB         (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void OKCB            (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void APPLYCB         (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);
  void CANCELCB        (CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData);

  // Builds a CAAVisBaseNewViewpointNotification with the current viewpoint
  // parameters, and sends it to the application.
  void SendNotif();
  
private:

  //Initial values:
  //Stored in order to be able to restore
  //the initial state if "CANCEL"
  CATMathPointf      *_pInitialOrigin;
  CATMathDirectionf  *_pInitialSight;
  CATProjectionType     _InitialProjectionType;
  float              _InitialFocus;
  float              _InitialAngle;

  //Current values:
  CATMathPointf      *_pCurrentOrigin;
  CATMathDirectionf  *_pCurrentSight;
  CATProjectionType     _CurrentProjectionType;
  float              _CurrentFocus;
  float              _CurrentAngle;

  //Dialog objects we need to store:
  CATDlgEditor          *_pOriginXEditor;
  CATDlgEditor          *_pOriginYEditor;
  CATDlgEditor          *_pOriginZEditor;

  CATDlgEditor          *_pSightXEditor;
  CATDlgEditor          *_pSightYEditor;
  CATDlgEditor          *_pSightZEditor;

  CATDlgRadioButton     *_pConicRadioButton;
  CATDlgRadioButton     *_pCylindricRadioButton;

  CATDlgEditor          *_pFocusEditor;
  CATDlgEditor          *_pAngleEditor;
};

#endif
