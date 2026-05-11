#ifndef CAAVisManagerApplication_H
#define CAAVisManagerApplication_H


// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the sample:
//  ------------------------
//
//  Interactive application composed of three menus:
//
//  - The File Menu which enables the user to :
//   * Open a CGR file and visualize it.
//   * Insert a CGR model into the active document of the application
//   * Exit from the application
//
// - The View menu which enables the user to : ( not yet implemented )
//   * Reframe the viewpoint
//   * Activate/Desactivate the 2D Graph viewpoint
//
// - The Command menu which enables the user to : ( not yet implemented )
//
// This application illustrates:
//
//      -the creation of visualization interface
//      -the use of visualization interface in order to make objects
//        be visualized with this interface.
//      -the use of the VisManager to visualize a modeling tree within a viewer
//        and using a given visualization interface.
//      -the use of the Hso and Pso components for the (pre)highlight management.
//      -how to manage the visualization events and how to define the eventhandler tree.
//      -how to plug the selection behavior.
//      -how to decode what is under the mouse
//
//=============================================================================
//  Usage:
//  ------
//
//  Type:
//    CAAVisManagerApplication
//  
//  A frame composed of a menu bar and a default document is loaded. The document
//  is displayed into a 3D viewer.
//  
//=============================================================================
// Abstract of the class:
//  ----------------------
//  Application class.
//
//  This is the main object in the process. It avoids writing a main function.
//  Event loop is managed automatically by deriving from CATInteractiveApplication. 
//  CAAVisManagerApplication does the following jobs:
//
//   * creates the main window: the application frame.
//   * subscribes to the window closing to terminate the application.  
//   * creates a default document (and it is then displayed into a 3D viewer).
//
//=============================================================================
//  Inheritance:
//  ------------
//           - CATInteractiveApplication (Dialog Framework)
//              - CATApplication (System Framework)
//
//=============================================================================
//  Main Method:
//  ------------
//
//  * BeginApplication: Contains the whole application code.
//
//
//=============================================================================


// Dialog FrameWork
#include "CATInteractiveApplication.h" // To derive from 

//Visualization FrameWork
#include "list.h"

// Dialog FrameWork
class CATDlgFile;
class CATDlgDocument;

//Local FrameWork
class CAAVisManagerApplicationFrame;
class CAAVisManagerDocument;
#include "CAAVisManagerWindow.h"


class CAAVisManagerApplication : public CATInteractiveApplication 
{
  public:

     // Constructs the application given an identifier
     // Parameters:
     //    iIdentifier: 
     //        The identifier 
     CAAVisManagerApplication(const CATString &iIdentifier);
     virtual ~CAAVisManagerApplication();

     //Contains the application code  
     virtual void BeginApplication();

     //Returns the application return code.
     virtual int  EndApplication();     
     
     // AnalyseNotification
     // -------------------
     // To catch every manipulating events send by its children in order 
     // to process them. As for the other events the current document send 
     // them up to the chain of responsability.
     //
     CATNotifPropagationMode AnalyseNotification(CATCommand      * iFromClient, 
                                            CATNotification * iNotification); 

     // 
     static CATDlgDocument * GetFrame();

  private :

     // Default constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAVisManagerApplication ();

     // Copy constructor, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAVisManagerApplication(const CAAVisManagerApplication &iObjectToCopy);

     // Assignment operator, not implemented
     // Set as private to prevent from compiler automatic creation as public.
     CAAVisManagerApplication & operator = (const CAAVisManagerApplication &iObjectToCopy);

     // Defines the view and the look of the application.
     void CreateLayout();

     HRESULT OpenCGR          (const char * iFileName);
     HRESULT InsertCGR        (const char * iFileName);

     // methods for callbacks
     void ExitCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData);      
     void OpenCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData); 
     void InsertCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData); 
     void LoadOKCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData); 
     void LoadCANCELCB ( CATCommand *iCmd, CATNotification *iNotif, CATCommandClientData iData); 

     void CloseFileBox() ;

     void WindowActivated(CAAVisManagerWindow * iWindow);
     void WindowDeleted(CAAVisManagerWindow * iWindow);

private :

     // list of documents
     list<CAAVisManagerDocument> _DocumentList;

     // the current activated document.
     CAAVisManagerDocument * _ActiveDoc;

     // List of windows to visualize documents
     list<CAAVisManagerWindow> _WindowList;

     // CGR File Selector 
     CATDlgFile        *_pFileSelectorBox;

     // Useful data for callbacks methods ( CGR open or insert )
     int _TypeOfInput;
};    

#endif


