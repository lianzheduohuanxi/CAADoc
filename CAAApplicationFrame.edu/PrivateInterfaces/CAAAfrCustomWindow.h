#ifndef CAAAfrCustomWindow_H
#define CAAAfrCustomWindow_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  Application using a new document type CAASample.
//     
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Abstract:
//  ---------
//  Window class which is a CATFrmWindow, so it enables display and 
//  manipulation of application data. 
//  It's the main window of the CAASample document.
//  It is not a standard window, It is customized to be composed of 3 Viewers. 
//
//  This window is intantiated in the CreateDefaultWindow of the 
//  CATIDocumentEdit Interface.
//
//  Illustrates
//     Creating a customized window
//
//===========================================================================
//  Inheritance:
//  ------------
//                CATFrmWindow (ApplicationFrame FrameWork)
//                   CATDlgDialog (Dialog Framework)
//                      CATDlgWindow (Dialog Framework)
//                         CATDialog    (Dialog Framework)
//                            CATCommand   (System Framework)
//                               CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  constructor : creates the viewer
//
//===========================================================================

// ApplicationFrame FrameWork
#include "CATFrmWindow.h"         // Needed to derive from CATFrmWindow

// ApplicationFrame FrameWork
class CATFrmEditor ;              // Needed by DuplicateWindow

// Visualization Framework 
class CATNavigation3DViewer ;     // 2 3DViewer in the window
class CATNavigation2DViewer ;     // 1 2DViewer in the window             
class CATPathElement ;            // For the path attached to each viewer

#include "CAAAfrGeoWindows.h"  // to export the class 

class ExportedByCAAAfrGeoWindows CAAAfrCustomWindow: public CATFrmWindow
{

  public:

    // Constructor
    // ------------
    // Creates a window to manage and display a document.
    //
    // @iName   :The identifier that defines the window's resources.
    // @iEditor :To controls the interactivity. 
    //
    // The document to visualize is referenced by the editor
    // 	
    CAAAfrCustomWindow(const CATString & iName, CATFrmEditor * iEditor=NULL);
    
    //  Build
    //  -----
    //  The window constructor is split in 2 parts :
    // 
    //    1- Dialog Part
    //       It's the most customizable part. You create the viewers and you 
    //       arrange them as Dialog Framework objects. Viewers must be retrieved 
    //       from the window, so they are data members of this instance. 
    //
    //    2- Interactivity Management Part	 
    //        In this part we are making in place the MVC model. 
    //        M : The document displayed in the editor 
    //        V : Viewers 
    //        C : The Visu Manager and the Editor 
    //        
    void Build();

    // Destructor
    // ----------
    // 
    virtual ~CAAAfrCustomWindow();


    // DuplicateWindow
    // ------------
    // Creates a clone window from this.
    //     
    virtual CATFrmWindow * DuplicateWindow();


    // DeleteWindow
    // ------------
    // 
    //  Detaches Viewers    from the ISO
    //  Detaches Viewpoints from the PSO and the HSO   
    //  Detaches Viewpoints from the controller 
    //    
    //  Calls the DeleteWindow method of the parent 
    // 
    virtual void DeleteWindow();

    // GetViewers
    // ----------
    // Retrieves the window's viewers.
    //
    void     GetViewers(CATNavigation3DViewer ** oV1,
                        CATNavigation3DViewer ** oV2, 
                        CATNavigation2DViewer ** oV3);
  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrCustomWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrCustomWindow(const CAAAfrCustomWindow &iObjectToCopy);
  	
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrCustomWindow & operator = (const CAAAfrCustomWindow &iObjectToCopy);

  private:

    // Viewers created are stored as data members 
    CATNavigation3DViewer * _pViewer1 ;
    CATNavigation3DViewer * _pViewer2 ;
    CATNavigation2DViewer * _pViewer3 ;

    // _pRootObjectPath
    // ----------------
    //
    // Path of objects which represents the part of a tree one wants to visualiaze. 
    // The last object of the path is the root object to visualize.
    //
    // This path is given to the Visu Manager for each viewer.  
    //
    // See CATVisManager::AttachTo  to have more details 
    //
    // Path is created in the constructor and deleted in the destructor
    //
    CATPathElement        * _pRootObjectPath ;

};
#endif
