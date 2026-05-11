#ifndef CAAVisManagerWindow_H
#define CAAVisManagerWindow_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  MDI Window .  
//
//
//  Events send by it:
//    
//	       WINDOW_ACTIVATED    (from uncurrent window to current window)
//	       WINDOW_DEACTIVATED  (from current window to uncurrent window)
//	       WINDOW_CREATED
//	       WINDOW_DELETED
//         VIEWER_SELECTED    (MouseButton1 Down on a Viewer) (sender is viewer)
//         VIEWER_ACTIVATED   (The CurrentViewer has been changed) (sender is viewer)
//         VIEWPOINT_CHANGED  (The main viewpoint of the currentViewer has been changed) 
//                             (sender is window)
//------------------------------------------------------------------------------
//       
// Dialog Framework
#include "CATDlgDialog.h"   // To derive from

// Local framework
class CAAVisManagerEditor ;

// Visualization FrameWork
class CATIndicator;
class CAT3DIndicator;
class CATViewer ;
class CATPathElement ;

#include <CATString.h>

enum  CAAVisManagerWindowState {CAAVisModelMinimizeWindow, 
                                CAAVisModelRestoredWindow,
                                CAAVisModelMaximizeWindow};

class CAAVisManagerWindow: public CATDlgDialog
{

   // Used in conjunction with CATImplementClass in the .cpp file 
   CATDeclareClass ;
   
 public:

   // Events define
   CATDeclareCBEvent(WINDOW_ACTIVATED);
   CATDeclareCBEvent(WINDOW_DEACTIVATED);
   CATDeclareCBEvent(WINDOW_CREATED);
   CATDeclareCBEvent(WINDOW_DELETED);
   CATDeclareCBEvent(VIEWER_SELECTED);
   CATDeclareCBEvent(VIEWER_ACTIVATED);
   CATDeclareCBEvent(VIEWPOINT_CHANGED);
   CATDeclareCBEvent(VIEWER_SHOW);
   CATDeclareCBEvent(VIEWER_NO_SHOW);
   
   CAAVisManagerWindow(CAAVisManagerEditor * iEditor, const CATString & iWindowId);

   virtual ~CAAVisManagerWindow();

   // Duplicator, Not Yet implemented
   virtual CAAVisManagerWindow * DuplicateWindow();

   CATViewer * GetViewer(void);
  
   virtual CAAVisManagerEditor * GetEditor() ;

   virtual void Build() ;

   // Methods called by the application 
   virtual void DeleteWindow();


 private:
       
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerWindow(const CAAVisManagerWindow &iObjectToCopy);
   
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisManagerWindow & operator = (const CAAVisManagerWindow &iObjectToCopy);
   
    // CB on MDI events
    void AddCB(void);
   
    // Callback methods 
    void MDICB   (CATCommand*, CATNotification *, CATCommandClientData);

    void WindowToDelete() ;
    void WindowToActivate();

    void Attach() ;
    void Detach() ;
    void ChangeBackgroundIndicator();
    void ResetBackgroundIndicator();

 private:
   
    // The Navigation 3DViewer 
    CATViewer      * _pViewer;

    // The Path of the model to visualize
    CATPathElement * _pRootObjectPath ;

    // the saved background indicator.
    CATIndicator   * _pSavedBackgrdIndicator;

    // the indicator of the current document.
    CAT3DIndicator * _pDocBackgrdIndicator;

    // The object which manages the interactivity
    CAAVisManagerEditor * _pEditor ;
}; 
#endif



