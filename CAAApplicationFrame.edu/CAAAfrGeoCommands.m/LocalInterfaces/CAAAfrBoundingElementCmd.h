#ifndef CAAAfrBoundingElementCmd_h
#define CAAAfrBoundingElementCmd_h

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
//  Command which displays temporary bounding sheres around model objects.
//  A dialog window enables the user to choose if the surrounding objects
//  will the points, the lines or objects of both types.
//  This command does not take the focus.
//  Three spheres are created, one for each plane: x=0, y=0, z=0.
//
//  Illustrates:
//     - creating a simple command derived from CATDlgDialog
//     - Arranging Dialog objects
//     - Subscribing to send/receive events
//     - Using a progress bar
//     - Using the Set of Interactive Objects (ISO) to display temporary objects
//     - Using cameras
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
//  Main Method:
//  ------------
//
//  constructor 
//     Creates the dialog widgets
//     Subscribes to the Apply and Close events
//     Retrieves the Set of Interactive Objects and the model container
//     Creates temporary circles to simulate bounding spheres
//
//  ClickApply  
//     Updates the temporary bounding sphere 
//     Uses a progress bar to simulate a long task.
//
//===========================================================================

// Dialog Framework
#include "CATDlgDialog.h"     // Needed to derive from CATDlgDialog

// System Framework
#include "CATBoolean.h"

// Dialog Framework
class CATDlgProgress;
class CATDlgCheckButton;
class CATDlgFrame;

// ApplicationFrame  Framework
class CATISO;                   // To see the bounding sphere
class CATFrmEditor ; 

//Visualization Framework
class CAT3DBoundingSphere ;
class CAT3DRep ;
class CATViewpoint ;

// CAASystem.edu framework
class CAAISysCircle;             // Bounding sphere 

class CAAAfrBoundingElementCmd : public CATDlgDialog
{
  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAAfrBoundingElementCmd.CATNls 
  //    
  DeclareResource(CAAAfrBoundingElementCmd, CATDlgDialog);
  
  public :
    
    // Constructor
    // -----------
    // Creates the dialog widgets
    // Subscribes to the Apply and Close events
    // Retrieves the Set of Interactive Objects and the model container
    // Creates temporary circles to simulate bounding spheres
    //
    CAAAfrBoundingElementCmd();

    virtual ~CAAAfrBoundingElementCmd();  
	
  private : 

    // ClickApply
    // ----------
    // The end user clicks Apply.
    // Updates the bounding sphere
    // and uses a progress bar to simulate a long task.
    void ClickApply(CATCommand              *iPublishingCommand, 
                    CATNotification         *iNotification, 
                    CATCommandClientData     iUsefulData);
 
    //
    // ClickClose
    // ----------
    // The end user clicks Close.
    // 
    void ClickClose(CATCommand              *iPublishingCommand, 
                    CATNotification         *iNotification, 
                    CATCommandClientData     iUsefulData);

    // ComputeBoundingSphere
    // ---------------------
    // Compute the bounding sphere of all objects contained in the model.
    // Point and line can be excluded of this total sphere, it depend on the
    // choise of the end user.
    // Return S_OK, if the bounding sphere is computed else E_FAILED
    //
    HRESULT ComputeBoundingSphere(CAT3DBoundingSphere &iBoundingSphere, 
                                  int                 &oNbElt     ,
                                  CATBoolean           iPointRead ,
                                  CATBoolean           iLineRead);

    // Get3DRep
    // ---------
    // Retrieves the Graphic Representation of the object iObject. 
    // If the iObject is NULL, we retrieve the graphic representation 
    // of the root object.
    // We use the visu manager and the method GenerateRepPathFromElement.
    // Return E_FAIL if there is a probleme to retrieve the Rep else S_OK
    // 
    HRESULT Get3DRep(CATBaseUnknown *iObject, CAT3DRep ** oRep) ;

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
    CAAAfrBoundingElementCmd(const CAAAfrBoundingElementCmd &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrBoundingElementCmd & operator = (const CAAAfrBoundingElementCmd &iObjectToCopy);

  private : 

    // Dialog objects
	CATDlgFrame       * _pPBarFrame   ;
    CATDlgProgress    * _pProgressBar ; 
    CATDlgCheckButton * _pPointCheck  ;
    CATDlgCheckButton * _pLineCheck ;

    // Data necessary to manipulate the model 

    // This object implements a factory interface to create Circle
    CATBaseUnknown    * _pContainer ;
    // It's the UI active object
    CATBaseUnknown    * _pUIActiveObject ;

    // Bounding sphere representation 
    // 3 circles to represent a sphere
    CAAISysCircle     * _piBoundingSphere[3];    
    int                 _IsBoundingSphereInISO ;
   
    // Set of Interactive Ojects to show the bounding spheres 
    CATISO            * _pISO ;

    // The Viewpoint of the current viewer. This data is useful to retrieve
    // the graphic representation 
    CATViewpoint      * _pViewpoint ;

    // To delete the command when the editor launching it is closed
    CATFrmEditor      * _pEditor ;
};
#endif
