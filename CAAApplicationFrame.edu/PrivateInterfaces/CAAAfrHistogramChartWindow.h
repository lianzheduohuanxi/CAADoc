#ifndef CAAAfrHistogramChartWindow_H
#define CAAAfrHistogramChartWindow_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the sample:
//  ----------------------
//
//  
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
//  It is not a standard window, It is HistogramChartized to be composed of 3 Viewers. 
//
//  This window is intantiated in the CreateDefaultWindow of the 
//  CATIDocumentEdit Interface.
//
//  Illustrates
//     Creating a HistogramChartized window
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
class CATNavigation2DViewer ;     // 2DViewer in the window             
class CATPathElement ;            // For the path attached to each viewer

#include "CAAAfrGeoWindows.h"  // to export the class 

class ExportedByCAAAfrGeoWindows CAAAfrHistogramChartWindow: public CATFrmWindow
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
    CAAAfrHistogramChartWindow(const CATString & iName, CATFrmEditor * iEditor=NULL);
    
    //  Build
    //  -----
    //  The window constructor is split in 2 parts :
    // 
    //    1- Dialog Part
    //       It's the most HistogramChartizable part. You create the viewers and you 
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
    virtual ~CAAAfrHistogramChartWindow();


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
 
  private:

    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrHistogramChartWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrHistogramChartWindow(const CAAAfrHistogramChartWindow &iObjectToCopy);
  	
    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAAfrHistogramChartWindow & operator = (const CAAAfrHistogramChartWindow &iObjectToCopy);
  	
  private:

    // Viewer created 
    CATNavigation2DViewer * _pViewer ;

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
