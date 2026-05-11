#ifndef CAAVisBasicWindow_h
#define CAAVisBasicWindow_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  1 - Creates the Graphics Representation as a tree  
//  2 - Attaches the top of the tree in a viewer which allows 3D manipulations
//  3 - Display the tree of Representation
// 
//=============================================================================
//  Inheritance:
//  ------------
//           CATDlgDocument (Dialog Framework)
//             CATDlgWindow (Dialog Framework)
//               CATDialog (Dialog Framework)
//                 CATCommand (System Framework)
//                   CATEventSubscriber (System Framework)
//                     CATBaseUnknown (System Framework)
//
//=============================================================================

// Dialog FrameWork
#include "CATDlgDocument.h"   // To derive from

// Dialog Framework
class CATInteractiveApplication;  // Application kept in data member

// Visualization Framework
class CAT3DBagRep ;               
class CATNavigation3DViewer;

class CAAVisBasicWindow : public CATDlgDocument
{
  // Declares the CAAVisBasicWindow.CATNls file as the dialog message catalog
  DeclareResource(CAAVisBasicWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAAVisBasicWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAAVisBasicWindow();

   //
   // Build
    // -----
    // This method constructs:
    //  
    //   - The Menubar and all Dialog's object for the this interactive object
    //      --> see CreateMenuBar()
    //   - The Graphical Representation of the model 
    //      --> see CreateModelRepresentation()
    //
    void     Build();

  private:

    // Callback on the exit button item of the menubar
    void Exit  (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    // CreateModelRepresentation
    // --------------------------
    // This method creates the model representation, ie _pTheModelToDisplay. 
    void CreateModelRepresentation();

    // CreateMenuBar
    // -------------
    // Creates the Menubar which is reduced to a File/Exit option
    //
    void CreateMenuBar();

    // CreateViewer
    // -------------
    // Creates the Dialog object to see the model 
    //
    void CreateViewer();

    // VisualizeModel
    // --------------
    // Attachs the model representation in the 3D Viewer to see it and
    // asks a draw model.
    //
    void VisualizeModel();

    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisBasicWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisBasicWindow(const CAAVisBasicWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisBasicWindow & operator = (const CAAVisBasicWindow &iObjectToCopy);

  private:

   //The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pApplication;

    // The Top of the representation tree
    CAT3DBagRep               * _pTheModelToDisplay ;

    // The Dialog object to display the model 
    CATNavigation3DViewer     * _p3DViewer ;
};
#endif
