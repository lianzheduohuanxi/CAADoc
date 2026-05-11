#ifndef CAAAfrProgressTaskSampleCmd_h
#define CAAAfrProgressTaskSampleCmd_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//  This sample shows how to use CATIProgressTaskUI, CATTaskController and
//  CATIProgressTask to simulate an interruptible task. 
//  
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  This class is a command ( a dialog comand ) which contains two objects:
//    - a check button to indicate if the task is interruptible or not
//    - a button to launch the task 
//   
//  During the task, a dialog box (modal) is displayed. This dialog box 
//  contains a progress bar and some informations about the task and the
//  progression. If the task is interruptible, a Cancel button enables the
//  end user to interrupt the task. If the task is interrupted the 
//  dialog box with the progress bar is closed 
//
//  The command implements the CATIProgressTask
//
//===========================================================================
//  
//  How to launch the sample:
//  ------------------------
//   - Launch CATIA 
//   - Start Menu, Infrastructure / CAA V5 Geometrical Analysis
//   - In the "Mathematic Analysis" toolbar or in the Analysis menu 
//      launch the "Progress Task" command
//   - Click or nor the Interruptible Task check button
//   - Push the Compute button 
//   - To finish the command, click Close 
//
//===========================================================================

// Dialog Framework
#include "CATDlgDialog.h"     // Needed to derive from CATDlgDialog

// Dialog Framework
class CATDlgCheckButton;  // for a dialog component

// ApplicationFrame Framework
class CATIProgressTaskUI ; // for the CATIProgressTask methods
class CATFrmEditor;         // to keep the editor when the command is launched

class CAAAfrProgressTaskSampleCmd : public CATDlgDialog
{
  // Used in conjunction with CATImplementClass in the .cpp file  
  CATDeclareClass;

  //
  // In the Cnext/resources/msgcatalog you have :
  //     CAAAfrProgressTaskSampleCmd.CATNls 
  //    
  DeclareResource(CAAAfrProgressTaskSampleCmd, CATDlgDialog);
  
  public :
    
    // Constructor
    // -----------
    // Creates the dialog widgets
    // Subscribes to the Compute and Close events
    //
    CAAAfrProgressTaskSampleCmd();

    virtual ~CAAAfrProgressTaskSampleCmd();  

    // CATIProgressTask interface
    // --------------------------

    // The task is included in this method. The dialog box which contains the
    // progress bar is controlled by the CATIProgressTaskUI interface. So in this 
    // method you give the order to the dialog box to:
    //  - Give the range of the progress bar ( once )
    //  - At each step you set the index of the process  
    // If the task is interruptible, the method return E_FAIL and the dialog box will 
    // be closed. 
    //
    virtual HRESULT PerformTask    (CATIProgressTaskUI  * iUI, void * iUserData);
    
    // Returns the name of the NLS file, same as the current command,
    // which contains:
    //  - The title of the  dialog box which contains the progress bar
    //       keyword: ProgressTaskUI.Title 
    //  - The object concerned by the task
    //       keyword: ProgressTaskUI.ObjectName
    //  - The comment 
    //       keyword: ProgressTaskUI.Comment   
    //
    // Note: in this use case, the comment is not the default comment, those
    // set in the ProgressTaskUI.Comment. We have choosen to change the comment
    // at each step: Step i .... The comment is built from the keyword
    // ProgresstaskUI.CommentRuntime set in the same NLS file as the current
    // command. 
    //
    virtual HRESULT GetCatalogName (CATString           * oCatalogName);

    // Returns the name of the icon displayed in the dialog box
    // which contains the progress bar
    virtual HRESULT GetIcon        (CATString           * oIcon) ;

  private : 

    // ClickCompute
    // ----------
    // The end user clicks on the Compute button
    // A simulate task is launched. 
    //
    void ClickCompute(CATCommand            *iPublishingCommand, 
                    CATNotification         *iNotification, 
                    CATCommandClientData     iUsefulData);
 
    //
    // ClickClose
    // ----------
    // The end user clicks Close.
    // The current command is deleted
    //
    void ClickClose(CATCommand              *iPublishingCommand, 
                    CATNotification         *iNotification, 
                    CATCommandClientData     iUsefulData);

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
    CAAAfrProgressTaskSampleCmd(const CAAAfrProgressTaskSampleCmd &iObjectToCopy);

    // Assigment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrProgressTaskSampleCmd & operator = (const CAAAfrProgressTaskSampleCmd &iObjectToCopy);

  private : 

    // Enable to launch an interruptible task or not
    CATDlgCheckButton * _pInterruptTask  ;

    // To delete the command with the good editor
    CATFrmEditor      * _pEditor ;


};
#endif
