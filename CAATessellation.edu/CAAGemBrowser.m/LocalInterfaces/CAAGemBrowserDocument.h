#ifndef CAAGemBrowserDocument_h
#define CAAGemBrowserDocument_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  1 - Creates the Graphics Representation as a tree  
//  2 - Attaches the top of the tree in a viewer which allows the user to do 
//      3D manipulations
//  3 - Displays the tree of Representation
//=============================================================================

// Dialog Framework
#include "CATDlgDocument.h"      // To derive from

// Dialog Framework
class CATInteractiveApplication; // Application kept in data member
class CATDlgFile;

// Visualization Framework
class CAT3DBagRep ;               
class CATNavigation3DViewer;

// GeometricObjects              // The geometry factory to browse
class CATGeoFactory;

class CAAGemBrowserDocument : public CATDlgDocument
{
  // Declares the CAAGemBrowserDocument.CATNls file as the dialog message catalog
  DeclareResource(CAAGemBrowserDocument, CATDlgDocument)

  public:

	 // Constructor. No initialization is actually done in it.
	 // The real initialization is done in the Build method.
    CAAGemBrowserDocument(CATInteractiveApplication * iParentCommand);

    virtual ~CAAGemBrowserDocument();

	//
	// Build
    // -----
    // This method constructs:
    //  
    //   - The Menubar and all Dialog objects for the this interactive object
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

    // Callback on the open button item of the menubar
    void Open  (CATCommand           * iSendingCommand, 
                CATNotification      * iSentNotification, 
                CATCommandClientData   iUsefulData);

    // Callback on the OK button item of the file window
    void OpenOK  (CATCommand           * iSendingCommand, 
                  CATNotification      * iSentNotification, 
                  CATCommandClientData   iUsefulData);
    // Callback on the cancel button item of the file window
    void Cancel  (CATCommand           * iSendingCommand, 
                  CATNotification      * iSentNotification, 
                  CATCommandClientData   iUsefulData);

    // Callback on the close button item of the menubar
    void Close  (CATCommand           * iSendingCommand, 
                 CATNotification      * iSentNotification, 
                 CATCommandClientData   iUsefulData);

    // Creates the model representation, ie _pTheModelToDisplay. 
    void CreateModelRepresentation();

    // Creates the Menubar which is reduced to a File/Open-Close-Exit option
    void CreateMenuBar();


    // Creates the Dialog object to see the model 
    void CreateViewer();

 
    // Attaches the model representation in the 3D Viewer to see it and
    // draws the model.
    void VisualizeModel();

 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAGemBrowserDocument ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAGemBrowserDocument(const CAAGemBrowserDocument &iObjectToCopy);

  private:

	// The parent widget (a CATInteractiveApplication instance) 
    CATInteractiveApplication * _pApplication;

    // The Top of the representation tree
    CAT3DBagRep               * _pTheModelToDisplay ;

    // The Dialog object to display the model 
    CATNavigation3DViewer     * _p3DViewer ;
    
    // The  "file selection" window
	CATDlgFile                * _pFileSelector;
    
    //  The geometry factory that is visualized
    CATGeoFactory             * _piGeomFactory;
};
#endif

