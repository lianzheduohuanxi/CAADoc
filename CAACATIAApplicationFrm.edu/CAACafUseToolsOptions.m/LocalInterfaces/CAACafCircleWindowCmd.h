#ifndef CAACafCircleWindowCmd_h
#define CAACafCircleWindowCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document (CAAGeometry) with its own workshop and 
//  commands.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Command which displays the discretization of a circle in taking account
//  of parameters defined in the Element Tools Options page. 
//
//  Illustrates:
//     - creating a simple command derived from CATDlgDialog
//     - using 2D Viewer
//     - Subscribing to callback events form setting controller
//
//===========================================================================
//  Inheritance:
//  ------------
//           CATDlgDialog (Dialog Framework)    
//              CATDialog   (Dialog Framework)
//                  CATCommand  (System Framework)
//                      CATBaseUnknown (System Framework)
//
//===========================================================================

// Dialog Framework
#include "CATDlgDialog.h"     // Needed to derive from CATDlgDialog

// System Framework
#include "CATEventSubscriber.h" // to receice callback

//Visualization Framework
class CAT2DViewer ;     // to visualize the circle
class CAT2DBagRep;      // to content the circle
class CAT2DCustomRep; 

//Visualization Framework
class CATFrmEditor;

class CAACafCircleWindowCmd : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAACafCircleWindowCmd.CATNls 
  //    
  DeclareResource(CAACafCircleWindowCmd, CATDlgDialog);
  
  public :
    
    // Constructor
    // -----------
    // Creates the dialog widgets
    //
    CAACafCircleWindowCmd();

    virtual ~CAACafCircleWindowCmd();  
	
  private : 
 
    //
    // ClickClose
    // ----------
    // The end user clicks Close.
    // 
    void ClickClose(CATCommand              *iPublishingCommand, 
                    CATNotification         *iNotification, 
                    CATCommandClientData     iUsefulData);

    // DisplayCircleCB
    // ---------------
    // It'a callback to react when a commit is done
    //
    void DisplayCircleCB  (CATCallbackEvent  iEvent,
                           void             *ipublisher,
                           CATNotification  *iNotification,
                           CATSubscriberData iUsefulData,
                           CATCallback       iCallBack );
    // DisplayCircle
    // ---------------------
    //
    HRESULT DisplayCircle();

    // EditorClose
    // -----------
    // Enable the destruction of the command when the editor is closed
    // and the command is always active.

    void EditorClose          (CATCallbackEvent  iEvent,
                           void             *iFrom,
                           CATNotification  *iNotification,
                           CATSubscriberData iData,
                           CATCallback       iCallBack );

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafCircleWindowCmd(const CAACafCircleWindowCmd &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAACafCircleWindowCmd & operator = (const CAACafCircleWindowCmd &iObjectToCopy);

  private : 

    CAT2DViewer * _p2DViewer ;

    CAT2DBagRep * _pTheModelToDisplay ;

    CAT2DCustomRep * _pCircleRep ;

    CATBaseUnknown * _pIBUController ;

    // To delete the command when the editor launching it is closed
    CATFrmEditor      * _pEditor ;
};
#endif
