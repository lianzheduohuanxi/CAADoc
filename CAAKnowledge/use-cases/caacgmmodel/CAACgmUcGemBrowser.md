---
title: "Browsing the Geometric Container"
category: "use case"
module: "CAACgmModel"
tags: ["CAAGemBrowserRepWindowId", "CATICGMContainer", "CATICGMCellTessellator", "CAADoc", "CAAGMOperatorsTesBody", "CAAGemBrowserDocument_h", "CAAGMModelNurbs", "CATInteractiveApplication", "CAAGMModelGemBrowser", "CAAGMModelCreation", "CAAVisBase", "CAAGMModelIntersect", "CAATopJournal", "CAAGMOperatorsOverview", "CAAGemBrowserApplication", "CAAGemBrowserDocument", "CATIA", "CAAGemRep", "CATICGMSurfaceTessellator", "CATICGMObject"]
source_file: "Doc/online/CAACgmModel/CAACgmUcGemBrowser.md"
converted: "2026-05-11T17:33:48.225077"
---
# Browsing the Geometric Container  
  
---  
Use Case  
## Abstract

In all the CATIA Geometric Modeler use cases, a CATGeoFactory container, creating and containing the geometric objects, is created and can be stored in a .NCGM file. The purpose of the CAAGMModelGemBrowser use case is to create an application and a document allowing you to visualize the created objects of a CATGeoFactory container.
    * What You Will Learn With This Use Case
    * The CAAGMModelGemBrowser Use Case
      * What Does CAAGMModelGemBrowser Do
      * How to Launch CAAGMModelGemBrowser
      * Where to Find the CAAGMModelGemBrowser Code
    * Step-by-Step
    * In Short
    * References  
---  
## What You Will Learn With This Use Case

This use case explains a means to visualize geometric objects:

    * The bodies.
    * The points, curves, and surfaces which are not pointed to by any other geometric object.

First an application and a document are defined, following the same way as in the `CAAVisBase` use case. Then, the visualization of the objects are computed. Hence, you will learn:

    * How to load and use the geometry factory.
    * How to read data on the geometric objects.
    * How to use the tessellation operators: `CATCellOperator` to tessellate a cell, `CATCurveTessellator` to tessellate a curve and `CATSurfaceTessellator` to tessellate a surface.
    * How to create representations.
## The CAAGMModelGemBrowser Use Case

CAAGMModelGemBrowser is a use case of the CAAGMModelInterfaces.edu framework. This use case illustrates the geometric modeler tessellation capabilities.
### What Does CAAGMModelGemBrowser Do

This use case:

    * First derives a new class of application CAAGemBrowserApplication and a new class of document CAAGemBrowserDocument, and provides the corresponding overridden methods.
    * Then defines the class CAAGemRep that computes the representation.

![GEM Browser](images/CAACgmGemBrowser1.gif)

This use case is a proposal of geometry visualization. Its intent is not to be a full graphic application. In particular, the color or the selection are not managed here.

In the picture above, the CAAGMModelGemBrowser use case displays the result of the CAAGMOperatorsJournal use case. This result was saved in the folder:

`InstallRootFolder\intel_a\CNext\resources\graphic\CAATopJournal.NCGM`

to allow you to visualize an example without processing any other use case. To visualize the model, simply select the menu File and the item Open. Then select the file.
### How to Launch CAAGMModelGemBrowser

To launch CAAGMModelGemBrowser, you will need to set up the build time environment, then compile CAAGMModelGemBrowser.m along with its prerequisites, set up the run time environment, and then execute the use case [1].

This use case is an interactive application. To visualize a .NCGM document (for example, the model saved at the last step of the CAAGMOperatorsJournal, CAAGMOperatorsOverview, CAAGMModelCreation, CAAGMModelNurbs, CAAGMOperatorsTesBody, or CAAGMModelIntersect use cases ), click the File+Open menu and select the file you want to display.
### Where to Find the CAAGMModelGemBrowser Code

The CAAGMModelGemBrowser use case is made of three classes 

    * CAAGemBrowserApplication, defining the application.
    * CAAGemBrowserDocument, defining the window.
    * CAAGemRep, creating the representations.

The sources (CAAGemBrowserApplication.cpp, CAAGemBrowserDocument.cpp, CAAGemRep.cpp) are located in the CAAGMModelGemBrowser.m module of the CAAGMModelInterfaces.edu framework.

The corresponding headers (CAAGemBrowserApplication.h, CAAGemBrowserDocument.h, CAAGemRep.h) are located in the `LocalInterfaces` directory of the CAAGMModelGemBrowser.m module.

`InstallRootFolder\CAADoc\CAAGMModelInterfaces.edu\CAAGMModelGemBrowser.m\`

where `InstallRootFolder` [1] is the folder where the API CD-ROM is installed.
## Step-by-Step

CAAGMModelGemBrowser is divided into the following steps:

    * Creating an Interactive Application to Display the Document
    * Creating Dialog Objects and Setting their Behaviors and Styles
      * Constructor and Build methods
      * Creating the Menu Bar
      * Creating the Viewer
      * Managing the Open Callback
      * Loading the Geometry Factory
    * Creating the Representations
      * Representation of a Point
      * Representation of a Line
      * Representation of a Curve
      * Representation of a Plane
      * Representation of a Surface
      * Representation of a Body
      * Representation of a Edge
### Creating an Interactive Application to Display the Document

Thanks to an interactive application, the CAAGemBrowserDocument can be displayed and run as a standalone application. This interactive application is made of the class CAAGemBrowserApplication that derives from CATInteractiveApplication. Its header file is as follows.
    #include "CATInteractiveApplication.h"  // To derive from
    
    class CAAGemBrowserApplication : public CATInteractiveApplication
    {
      public:
    	
        CAAGemBrowserApplication(const CATString & iApplicationId);
        virtual     ~CAAGemBrowserApplication();
        virtual void BeginApplication();
        virtual int  EndApplication();
    
    private:
        CAAGemBrowserApplication();
        CAAGemBrowserApplication(const CAAGemBrowserApplication &iObjectToCopy);   
    };

In addition to the constructor and destructor, this interactive application class redefines two methods of CATInteractiveApplication:

    * `BeginApplication`, called by the system just after the application constructor. This method is dedicated to create the different objects managed by the application, namely here the document window.
    * `EndApplication`, called by the system when the application destruction is requested. This method is dedicated to deallocate objects or close files.

The document window is created in the `BeginApplication` method, and in this use case, the `EndApplication` has nothing to deallocate since it is automatically deleted when the application is deleted.
    
    ...
    void CAAGemBrowserApplication::BeginApplication()
    {
      cout << "CAAGemBrowserApplication::BeginApplication" << endl;
    
      // This window is deleted when the application is deleted.
      // The application is deleted by the Destroy Method called in the 
      // CAAGemBrowserDocument::Exit method.
      //
      CAAGemBrowserDocument * pMainWindow =NULL;
      pMainWindow = new **CAAGemBrowserDocument**(**this**);
    
      // Constructs all Dialog objects of the window
      pMainWindow->**Build**();
    
      pMainWindow->**SetVisibility**(CATDlgShow);
    }
    
    int CAAGemBrowserApplication::EndApplication()
    {              
      return 0;
    }

Note that the document window is first instantiated, then initialized using its `Build` method, and finally set as visible. The constructor parameter is the dialog box parent in the command tree structure, set as the application itself.

The application is simply instantiated as follows.
    
    ...
    CAAGemBrowserApplication ApplicationInstance("CAAGemBrowserApplicationInstance");

The main program is created from this instance.
### Creating Dialog Objects and Setting their Behaviors and Styles

The file CAAGemBrowserDocument.h contains the following:
    #ifndef CAAGemBrowserDocument_h
    #define CAAGemBrowserDocument_h
    #include "CATDlgDocument.h"      // To derive from
    
    class CATInteractiveApplication; // Application kept in data member
    class CATDlgFile;
    class CAT3DBagRep ;              // Data member class forward declaration            
    class CATNavigation3DViewer;
    class CATGeoFactory;
    
    class CAAGemBrowserDocument : public CATDlgDocument
    {
      **DeclareResource**(CAAGemBrowserDocument, CATDlgDocument)
    
      public:
        CAAGemBrowserDocument(CATInteractiveApplication * iParentCommand);
        virtual ~CAAGemBrowserDocument();
        void     Build();
    
      private:
     ...
        // Creates the model representation, ie _pTheModelToDisplay
        void CreateModelRepresentation();
    
        // Creates the Menubar which is reduced to a File/Open-Close-Exit option
        void CreateMenuBar();
    
        // Creates the Dialog object to see the model 
        void CreateViewer();
    
        // Attaches the model representation in the 3D Viewer to see it and
        // asks a draw model
        void VisualizeModel();
    
        // Default constructor, not implemented
        // Set as private to prevent from compiler automatic creation as public.
        CAAGemBrowserDocument ();
    
        // Copy constructor, not implemented
        // Set as private to prevent from compiler automatic creation as public.
        CAAGemBrowserDocument(const CAAGemBrowserDocument &iObjectToCopy);
    
      private:
        //The parent widget (a CATInteractiveApplication instance)
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

The `DeclareResource` macro enables the class and all its dialog objects to use the automatic resource assignment. The first parameter is the class name, and the resource files must use this class name as file name, such as CAAGemBrowserDocument.CATNls for the file containing the texts and messages.

The class has a constructor, a destructor, and a `Build` method. Additional private methods create the menu bar, the dialog object to see the model, the object containing all the representations and visualize the model. Pointers to the different dialog objects are then declared as data members.

The remaining part of this file deals with the callback method declaration.
    
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
#### Constructor and Build Methods

Let's have a look at the beginning of CAAGemBrowserDocument.cpp:
    
    CAAGemBrowserDocument::CAAGemBrowserDocument(CATInteractiveApplication * iParentCommand) 
                          : CATDlgDocument(iParentCommand, "CAAGemBrowserRepWindowId"),
    	                _pApplication(iParentCommand),_pTheModelToDisplay(NULL),
                            _p3DViewer(NULL),
                            _piGeomFactory(NULL),_pFileSelector(NULL)
    {
      cout << "CAAGemBrowserDocument::CAAGemBrowserDocument" << endl;
    
      // Do not construct any Dialog object child in the constructor 
      // Use the Build Method to do this.
    }
    
    void CAAGemBrowserDocument::**Build**()
    {
      cout << "CAAGemBrowserDocument::Build" << endl;
    
      CreateMenuBar();
      CreateViewer(); 
    }

The constructor is empty, but calls the base class `CATDlgDocument` constructor, and sets the parent command of the window as the interactive application itself. The `Build` method calls for the creation of the menu bar and for the creation of the viewer that allows the user to do 3D manipulations.
#### Creating the Menu Bar
    
    void CAAGemBrowserDocument::**CreateMenuBar**()
    {
       CATDlgBarMenu* pMainMenu = NULL;
       pMainMenu = new CATDlgBarMenu(this,"MainMenu");
    
       CATDlgSubMenu* pFileMenu = NULL;
       pFileMenu = new CATDlgSubMenu(pMainMenu,"File");
    
       CATDlgPushItem* pOpenItem = NULL;
       pOpenItem = new CATDlgPushItem(pFileMenu,"Open");
    
       **AddAnalyseNotificationCB**(pOpenItem,
                                pOpenItem->GetMenuIActivateNotification(), 
                                (CATCommandMethod)&CAAGemBrowserDocument::Open, 
                                NULL); 
        
       CATDlgPushItem* pCloseItem=NULL;
       pCloseItem = new CATDlgPushItem(pFileMenu,"Close");
       **AddAnalyseNotificationCB**(pCloseItem,
                                pCloseItem->GetMenuIActivateNotification(), 
                                (CATCommandMethod)&CAAGemBrowserDocument::Close, 
                                NULL);
    
       CATDlgPushItem * pExitItem =NULL;  
       pExitItem = new CATDlgPushItem(pFileMenu,"Exit");
       **AddAnalyseNotificationCB**(pExitItem,
                                pExitItem->GetMenuIActivateNotification(), 
                                (CATCommandMethod)&CAAGemBrowserDocument::Exit, 
                                NULL);
       **AddAnalyseNotificationCB**(this,
                                GetWindCloseNotification(), 
                                (CATCommandMethod)&CAAGemBrowserDocument::Exit, 
                                NULL);
    }

The `CreateMenuBar` method creates the menu and menu items. Since the declaration of an external resource file has been made in the header, the items will be displayed according to the chosen language.

Moreover, this method sets the callbacks to trigger the appropriate method when a specific control is activated.

    * If the File/Open menu is selected, a file selector window is activated.
    * If the File/Close menu is selected, the model visualization disappears.
    * If the File/Exit menu is selected, this ends the application.
#### Creating the Viewer

The 3D navigation viewer is an instance of the CATNavigation3DViewer class. It is created in the `CreateViewer` method of the CAAGemBrowserDocument class that is called when the application is launched.
    
    void CAAGemBrowserDocument::CreateViewer()
    {
      // The window contains a 3DViewer which allows the user to do 3D Manipulations 
      _p3DViewer = new CATNavigation3DViewer( this, "3DViewerId",CATDlgFraNoTitle, 800, 450);
    
      // Changes the color of the background
      _p3DViewer->SetBackgroundColor(0.2f,0.2f,0.6f);
    
      // The Viewer is attached to the 4 sides of the Window
    Attach4Sides( _p3DViewer);
    }

The `_pViewer` pointer to the 3D navigation viewer is kept as a data member of the CAAGemBrowserDocument class. The `Attach4Sides` method attaches the four sides of the viewer to those of the window. This makes the viewer occupy the whole window space.
#### Managing the Open Callback

Once the user clicks on the File/Open item, the following callback is triggered:
    
    void CAAGemBrowserDocument::Open  (CATCommand           * iSendingCommand, 
                                       CATNotification      * iSentNotification, 
                                       CATCommandClientData   iUsefulData)
    {
      // Creates a File box
      _pFileSelector = new CATDlgFile(this,"FileBox",NULL);
      _pFileSelector->SetVisibility(CATDlgShow);
      
      // Sets the authorized types
      CATUnicodeString nameExtension = CATUnicodeString("NCGM files");
      CATString filterExtension = CATString("*.NCGM");
      _pFileSelector->SetFilterStrings(&nameExtension, &filterExtension, 1);
    
      // callbacks on the FileBox interactions
      AddAnalyseNotificationCB(_pFileSelector, 
                               _pFileSelector->GetDiaCANCELNotification(), 
                               (CATCommandMethod)&CAAGemBrowserDocument::Cancel, 
                               NULL);  
      int iTypeOfInput = 0;
      AddAnalyseNotificationCB(_pFileSelector, 
                               _pFileSelector->GetDiaOKNotification(), 
                               (CATCommandMethod)&CAAGemBrowserDocument::OpenOK, 
                               &iTypeOfInput);   
    }

This method creates a File Box to select the file to display. The authorized type of file extension is `*NCGM`. Once again, callbacks are set to trigger methods when a specific control is activated. In particular, the `OpenOK` method opens the file and visualizes the created objects of the CATGeoFactory container.
#### Loading the Geometry Factory

The `OpenOK` callback:

    * Retrieves the file to open: `GetSelection`.
    * Loads the `CATGeoFactory`: `CATLoadCGMContainer`.
    * Creates the representations: `CreateModelRepresentation`.
    * Draws the representations: `VisualizeModel`.
    
    void CAAGemBrowserDocument::OpenOK(CATCommand           * iSendingCommand, 
                                       CATNotification      * iSentNotification, 
                                       CATCommandClientData   iUsefulData)
    {
      // Retrieves the file name
      CATUnicodeString fileName;
      _pFileSelector->**GetSelection**(fileName);
      delete _pFileSelector; 
      _pFileSelector=NULL;
      
      // Closes the precedeeding factory, if any
      Close(iSendingCommand,  iSentNotification,  iUsefulData);
    
      // Loads the geometry factory
    #ifdef _WINDOWS_SOURCE
      ifstream filetoread(fileName, ios::binary ) ;
    #else
      ifstream filetoread(fileName,ios::in,filebuf::openprot) ;
    #endif
    
      _piGeomFactory=**::CATLoadCGMContainer**(filetoread);
      filetoread.close();
    
      // Creates the  representation
      **CreateModelRepresentation**();
    
      // Draws
      **VisualizeModel**();  
    } 			

The `CreateModelRepresentation` method begins by creating the representation bag to attach to the viewer.
    
    void CAAGemBrowserDocument::**CreateModelRepresentation**()
    {
      // The Top of the  representation tree
        _pTheModelToDisplay = new **CAT3DBagRep**();
    
      // Scans the geometry factory to retrieve the objects to visualize
      if (NULL != _piGeomFactory) 
      {
        float sag = 0.1f;
        **CAAGemRep** browser(_piGeomFactory,**sag**);
        CATGeometry* piCurrent = NULL ;
        while ( piCurrent = _piGeomFactory->**Next** ( piCurrent ) )
        {  
          CAT3DRep * pRep =NULL;
          browser.**CreateRep**(piCurrent, pRep);
          if ( NULL != pRep )
          {
            _pTheModelToDisplay->**AddChild**(*pRep);
          }
        }
      } 
    }

Then, it defines the `CAAGemRep` object to compute the representations of the geometric objects. The `CATGeoFactory` is scanned by the ` Next` method in order to retrieve the objects to visualize. The representation of an object is created by the `CreateRep` method of `CATGemRep`, and added (`AddChild`) to the representation bag.

The visualization is done by the `VisualizeModel` method.
    
    void CAAGemBrowserDocument::VisualizeModel()
    {
       if ( (NULL != _p3DViewer) && ( NULL != _pTheModelToDisplay) )
       {    
          // Attaches the bag to the viewer
          _p3DViewer->**AddRep**((CAT3DRep*)_pTheModelToDisplay);
    
          // Reframes on the current bounding sphere
          const CAT3DBoundingSphere boundingSphere = _pTheModelToDisplay->GetBoundingElement(); 
          _p3DViewer->**ReframeOn**(boundingSphere);
    
          // Instruction to do at each  representation modification
          _p3DViewer->**Draw**();
       }
    }

    * The bag representation is attached to the viewer.
    * The visualization is reframed on the bounding box of the model.
    * The viewer is drawn.
### Creating the Representations

CAAGemRep is the class dedicated to the creation of the representations.
    
    ... // GeometricObjects forward declarations
    
    ... // Tessellation forward declarations
    class CAT3DRep;
    #include "CATBoolean.h"
     
    class CAAGemRep 
    {
      public:
        CAAGemRep(CATGeoFactory * ipiGeomFactory, float iSag);
        ~CAAGemRep();
    
        //  Creates the  representation of a geometric object
        void **CreateRep**(CATGeometry * ipiToView, CAT3DRep *& iopRep);
    
        //  Creates the  representation of a body
        void **CreateBodyRep**(CATBody * ipiBody, CAT3DRep *& iopRep);  
    
        //  Creates the  representation of a face
        //  The arguments are the output of the tessellation cell or body operators
        void **CreateSurfaceRep**(CATBoolean          iPlane,
                              CATSide             iSide, 
                              CATTessPointIter  * iPoints,
                              CATTessStripeIter * iStrips,
                              CATTessFanIter    * iFans,
                              CATTessPolyIter   * iPolygons,
                              CATTessTrianIter  * iTriangles,
                              CAT3DRep *& iopRep);
    
        //  Creates the  representation of a plane
        void **CreatePlaneRep**(CATPlane *piPlane, CAT3DRep *& iopRep);
    
        //  Creates the  representation of an edge
        //  The arguments are the output of the tessellation cell or body operator
        void **CreateEdgeRep**  (CATEdge * ipiEdge, 
                             long & ioNumOfPoints,
                             float * oaPoints, 
                             CAT3DRep *& iopRep);
    
        //  Creates the  representation of a curve
        //  The arguments are the output of CATCurveTessellator
        void **CreateCurveRep** (long & ioNumOfPoints,
                             float * oaPoints, 
                             CAT3DRep *& iopRep);
    
        //  Creates the  representation of a line
        void **CreateLineRep**(CATLine *piLine, CAT3DRep *& iopRep);
    
        //  Creates the  representation of a point
        void **CreatePointRep**  (CATMathPoint & point,CAT3DRep *& iopRep);
    
      private:
        CAAGemRep ();
        CAAGemRep(const CAAGemRep &iObjectToCopy);
      
        CATGeoFactory * _piGeomFactory; // The geometry factory that is visualized
        float          _sag;           // The tessellation sag
    };

    1. `CreateRep` directs the creation of different kinds of representations, according to the different types of objects.
    2. `CreateBodyRep` tessellates a body and creates the corresponding representation.
    3. `CreateSurfaceRep` creates the representation of a surface from the results of a tessellation operator.
    4. `CreateEdgeRep` creates the representation of a curve from the results of a tessellation operator.
    5. `CreateCurveRep` creates the representation of a curve (that is not a line) from the results of a tessellation operator.
    6. `CreateLineRep` directly creates the representation of a line.
    7. `CreatePlaneRep` directly creates the representation of a plane.
    8. `CreatePointRep` directly creates the representation of a point.

The private data are the pointer to the `CATGeoFactory` container that is visualized, and the sag used to define the tessellation [2].

The structure of the **CreateRep** method is as follows:
    
    void CAAGemRep::**CreateRep**(CATGeometry * ipiToView, CAT3DRep *& iopRep)
    {
     
      if (NULL!= ipiToView)
      {
        // ------ Body visualization
        if (0!=ipiToView->**IsATypeOf**(**CATBodyType**)) 
        { 
           CATBody * piBody=(CATBody * )ipiToView;
           CreateBodyRep(piBody,iopRep);
        }
        // ------ Curve visualization
        else if (0!=ipiToView->IsATypeOf(**CATCurveType**))
        {
           if (0== ipiToView->**GetUseCount**())      // to only visualize alone curves
           {       
             // ------ Line
             if (0!=ipiToView->IsATypeOf(**CATLineType**))
             {
                CATLine * piLine=(CATLine*)ipiToView;
                CreateLineRep(piLine,iopRep);               
             }
             else
             // ------ other curves         
             {   
                ... --> use a CATCurveTessellator 
             }
           }
        }
        // ------ Surface
        else if (0!=ipiToView->IsATypeOf(**CATSurfaceType**))
        {
           CATSurface * piSurface = (CATSurface * )ipiToView;
           
            if (0== ipiToView->**GetUseCount**()) // only visualizes surfaces that are not pointed to
            {     
             // ----- Plane
             if(ipiToView->IsATypeOf(**CATPlaneType**))
             {
                CATPlane * piPlane=(CATPlane*)ipiToView;
                CreatePlaneRep(piPlane,iopRep);
             }
             else
             // Other surfaces
             {
               ... --> use CATSurfaceTessellator
             } 
           }
        }
        // Point
        else if (0!=ipiToView->IsATypeOf(**CATPointType**))
        {
           if (0== ipiToView->GetUseCount())
           {
              CATPoint * piPoint = (CATPoint*)ipiToView;
              CATMathPoint point;
              piPoint->GetMathPoint(point);
              CreatePointRep(point,iopRep);
           }
        }
      }  
    }

The creation of the representations is managed according to the type of the geometric object, retrieved with the `CATICGMContainer::IsATypeOf` method. In case of surfaces, curves, or points, the choice of the use case is to visualize only objects that are not pointed to by any other object. Hence the `CATICGMObject::GetUseCount` returns if an object is pointed to or not.

We now examine in detail all the type of geometry: point, line, curve, plane, surface and body.
#### Representation of a Point

The coordinates of the point are directly passed to the constructor of the representation.
    
    void CAAGemRep::CreatePointRep  (CATMathPoint & point,CAT3DRep *& iopRep)
    {
       // Gets the coordinates of the point
       double ioFirstCoord,ioSecondCoord,ioThirdCoord;
       point.**GetCoord**(ioFirstCoord,ioSecondCoord,ioThirdCoord);
       float aCoord[3];
       aCoord[0]= (float)ioFirstCoord;
       aCoord[1]= (float)ioSecondCoord;
       aCoord[2]= (float)ioThirdCoord;
        
       // Creates the rep
       CAT3DPointRep *rep = new **CAT3DPointRep**(aCoord,FULLCIRCLE);
    
       // Returns the rep
       iopRep = rep;
    }
#### Representation of a Line

The lines have a specific treatment: they do not need to be discretized. Two cases are considered: finite (or trimmed) and infinite lines. To know if a line is infinite, the model size of the `CATGeoFactory` container is retrieved (`GetModelSize`). The model size defines the maximum bounding box of the model [3] and one tests whether this maximum bounding box includes the extremities of the curve.
    
    void CAAGemRep::CreateLineRep(CATLine *piLine, CAT3DRep *& iopRep)
    {
      CAT3DRep *pRep = NULL;
    
      CATCrvParam startParam, endParam  ;
      piLine->GetStartLimit(startParam);
      piLine->GetEndLimit(endParam);
    
      // The start and end points of the line
      CATMathPoint startPoint =piLine->EvalPoint(startParam);
      CATMathPoint endPoint =piLine->EvalPoint(endParam);
      CATMathPointf start, end;
      start.x = (float) startPoint.GetX();
      start.y = (float) startPoint.GetY();
      start.z = (float) startPoint.GetZ();
      end.x   = (float) endPoint.GetX();
      end.y   = (float) endPoint.GetY();
      end.z   = (float) endPoint.GetZ();
    
      // Is the line infinite?
      double infinity=piLine->GetContainer()->**GetModelSize**();
      CATMathBox boxInfinite(-infinity,infinity,-infinity,infinity,-infinity,infinity) ;
      int isFinite = (boxInfinite.IsContaining(startPoint) 
                        && boxInfinite.IsContaining(endPoint) ) ? 1 : 0;
      
      if ( isFinite )
      {
        // Creates the rep of the finite line 
        CAT3DLineRep* pRepresentation = new **CAT3DLineRep**();
        pRepresentation->**Modify**(start,end);
        pRep = pRepresentation;
      }
      else
      {
        // Creates a special rep: an arrow 
        CATMathLine line(startPoint,endPoint);
        CATMathPoint origin, projpt;
        line.Project(origin,projpt);
        CATMathVector vect;
        line.GetDirection(vect);
         
        CATMathPointf  ptf((float)projpt.GetX(), (float)projpt.GetY(), (float)projpt.GetZ());
        CATMathVectorf tf(vect);
         
        CAT3DCustomRep  * pBagGP = new CAT3DCustomRep();     
        CAT3DFixedArrowGP* pArrow = new **CAT3DFixedArrowGP**(ptf,tf, 40, 2);
        CATGraphicAttributeSet attribute;  
        pBagGP->AddGP(pArrow,attribute);  
        pRep = pBagGP;
      }
      // Returns the rep
      iopRep = pRep;
    }

In case of a finite line, a CAT3DLineRep instance is modified to be trimmed by the start and end limits of the line, thus defining the representation of the line.

In case of an infinite line, an arrow is visualized: a CAT3DFixedArrowGP is created at the origin of the line, along its direction. The total arrow length is 40 millimeters, and the head height is 2 millimeters.
#### Representation of a Curve

We are here in the `CreateRep` method of CAAGemRep. We describe now the code under the _other curves_ comment.

In case of a curve, the program first checks that the curve is not degenerated. The bounding box of the current limits is first retrieved with the `CATCurve::GetBox` method, the length of its diagonal is then computed. If this length is:

    * Less than the factory resolution (`CATGeoFactory::GetResolution`), the representation of a point is created. The point is evaluated with ` CATCurve::Eval`.
    * Greater than the factory resolution. The `CATICGMCurveTessellator` operator computes the data used to create the representation of a curve. The representation itself is created in the `CreateCurveRep` method that is later detailed.
    
    // piCurve is the pointer to the interface of a curve to visualize
    // Is the curve a curve or a point? Gets the bounding box of its limits.
    CATMathBox boundingBox;
    CATMathPoint low,high;
    CATCrvLimits limits;
    piCurve->GetLimits(limits);
    piCurve->**GetBox**(limits,boundingBox);
    boundingBox.GetLow(low);
    boundingBox.GetHigh(high);
    CATMathVector diagonal=high-low;
    double diagonalLength= diagonal.Norm();
    
    // really a curve to visualize
    if ( diagonalLength > _piGeomFactory->**GetResolution**() )
    {     
      CATICGMCurveTessellator * pCurveTess = **CATCGMCreateCurveTessellator**(_sag);
      if (NULL!=pCurveTess)
      {
    
        pCurveTess -> **AddCurve**(piCurve, limits);
        pCurveTess -> **Run**();
                  
        // Retrieves the tessellation results
        long  numOfPoints;
        float * aPoints= NULL;
        pCurveTess-> **GetCurve** (piCurve, numOfPoints, &aPoints);
    
        // Creates the rep
        **CreateCurveRep** (numOfPoints,aPoints,iopRep);
    
        pCurveTess->Release();
        pCurveTess=NULL;
      } 
    }
    // The curve is a point
    else
    {
      CATCrvParam crvParam;
      piCurve->GetStartLimit(crvParam);
      CATMathPoint pt;
      piCurve->**Eval**(crvParam, CATCrvEvalCommand::EvalPoint, &pt);
      **CreatePointRep**(pt,iopRep);
    }

To use the `CATICGMCurveTessellator` operator:

    * Create it.
    * Add the curve(s) to tessellate, and precise their limits.
    * Run it.
    * Get the tessellation results.
    * Release it.

The tessellation results are used by the method `CreateCurveRep` of `CAAGemRep` to create the representation as follows.
    
    void CAAGemRep::CreateCurveRep  (long & ioNumOfPoints, 
                                     float * oaPoints, 
                                     CAT3DRep *& iopRep)
    {
      CAT3DCurveRep*   pCurveRep = NULL;
      
      // Creates the rep
      CAT3DPolylineGP* polylineGP = new **CAT3DPolylineGP**(oaPoints, ioNumOfPoints, 1);
      pCurveRep  = new CAT3DCurveRep();
      pCurveRep->**AddWireframeLOD**(0,polylineGP, _sag);
    
      // Defines the bounding box 
      float xmin=1.e+10,ymin=1.e+10,zmin=1.e+10,xmax=-1.e+10,ymax=-1.e+10,zmax=-1.e+10;
      for (int j=0, curj=0; j<ioNumOfPoints; j++, curj+=3)
      {
        if(oaPoints[curj+0] < xmin) xmin=oaPoints[curj+0];
        if(oaPoints[curj+1] < ymin) ymin=oaPoints[curj+1];
        if(oaPoints[curj+2] < zmin) zmin=oaPoints[curj+2];
        if(oaPoints[curj+0] > xmax) xmax=oaPoints[curj+0];
        if(oaPoints[curj+1] > ymax) ymax=oaPoints[curj+1];
        if(oaPoints[curj+2] > zmax) zmax=oaPoints[curj+2];
      }
      CATMathPointf center((float) (xmin+xmax)/2.f, 
                           (float) (ymin+ymax)/2.f, 
                           (float) (zmin+zmax)/2.f);
      double radius= sqrt((xmax-xmin)*(xmax-xmin)+
                          (ymax-ymin)*(ymax-ymin)+
                          (zmax-zmin)*(zmax-zmin))/2.f;
      pCurveRep->**SetBoundingElement**(CAT3DBoundingSphere(center, (float)radius));
     
      // Returns the rep
      iopRep = pCurveRep;
    }

The representation of a curve is a collection of graphic polylines `CAT3DPolylineGP`, each one representing a level of detail (LOD). Here, one LOD is added to the curve representation (`AddWireframeLOD`), with a level a detail having `_sag` as the corresponding sag value. Finally, the bounding box is computed from the tessellation results and set to the curve representation.
#### Representation of a Plane

The origin and the axes of the plane are directly passed to the constructor of the representation. As the plane is infinite, a given size is fixed. The associated bounding sphere is also set to the representation.
    
    void CAAGemRep::CreatePlaneRep(CATPlane *piPlane, CAT3DRep *& iopRep)
    {
      CATMathPlane plane;
    
      // Gets the mathematical definition
      piPlane->GetAxis(plane);
      CATMathPoint      center = plane.GetOrigin();
      CATMathDirection  vAxis  = plane.GetSecondDirection();
      CATMathDirection  uAxis  = plane.GetFirstDirection();
      CATMathPointf     origin((float) center.GetX(), 
                               (float) center.GetY(), 
                               (float) center.GetZ());
      CATMathDirectionf u((float) uAxis.GetX(), 
                          (float) uAxis.GetY(), 
                          (float) uAxis.GetZ());
      CATMathDirectionf v((float) vAxis.GetX(), 
                          (float) vAxis.GetY(), 
                          (float) vAxis.GetZ());
      
      float size = 20.f;
      float radius  = 15.f;
    
      // Creates the rep
      CAT3DPlanRep *pRep = new **CAT3DPlanRep**(origin,u,v,size);
      
      CAT3DBoundingSphere *pBe = new CAT3DBoundingSphere(origin,0.f,radius);
      pRep->SetBoundingElement(*pBe);
      delete pBe;
      pBe=NULL;
    
      // Returns the rep
      iopRep = pRep;
    }
#### Representation of a Surface

We are here in the `CreateRep` method of CAAGemRep. We describe now the code under the _other surfaces_ comment.

The surface is first tessellated with `CATSurfaceTessellator`.
    
    // piSurface is the pointer to the surface to visualize
    CATSurLimits limits;
    piSurface->GetLimits(limits);
    CATICGMSurfaceTessellator * pSurfTess = **CATCGMCreateSurfaceTessellator**(_sag);
    if (NULL!=pSurfTess)
    {
      pSurfTess -> **AddSurface**(piSurface, limits);
      pSurfTess -> **Run**();
                  
      CATBoolean isPlanar;
      CATTessPointIter *    pPoints    = NULL;
      CATTessStripeIter *   pStrips    = NULL;
      CATTessFanIter *      pFans      = NULL;
      CATTessPolyIter *     pPolygons  = NULL;
      CATTessTrianIter *    pTriangles = NULL;
         
      pSurfTess -> **GetSurface**(piSurface,isPlanar,
                              &pPoints,&pStrips,&pFans,&pPolygons,&pTriangles);
      CATSide side=CATSideUnknown;
      **CreateSurfaceRep**(isPlanar,side, pPoints, pStrips,pFans, pPolygons, pTriangles,iopRep);
                  
      pSurfTess->Release();
      pSurfTess=NULL;
    }

To use the `CATICGMSurfaceTessellator` operator:

    * Create it.
    * Add the surface(s) to tessellate, and precise their limits.
    * Run it.
    * Get the tessellation results.
    * Release it.

The tessellation results are used by the method `CreateSurfaceRep` of `CAAGemRep` to create the representation as follows:

    * Computing the normals and the bounding box: the iterator on the points is used.
    * Retrieving the isolated triangles with `CATTessTrianIter`.
    * Retrieving the triangle strips with `CATTessStripeIter`.
    * Creating the graphic primitives.

We now detail the use of the point iterator to retrieve the normals in case of a non-planar surface.
    
    // allocation of the arrays
      long numberOfPoints = ipPoints->**GetNbPoint**();
      if (numberOfPoints == 0) return ;
      
      long verticesArraySize = numberOfPoints*3 ;
      float * vertices = new float [verticesArraySize];
      long normalsArraySize = verticesArraySize ;
      float * normals = new float [normalsArraySize];
    
    // iterator on the points 
    // ipPoints is the CATTessPointIterator retrieved from the tessellator
      i = 0 ;
      double const  * ptd;   
      while ( ipPoints->**IsExhausted**()==0 ) 
      {
        ptd = ipPoints->**GetPointXyz**();
        vertices[i  ] = (float) ptd[0] ;
        vertices[i+1] = (float) ptd[1] ;
        vertices[i+2] = (float) ptd[2] ;
        
        if (xmin > vertices[i  ]) xmin=vertices[i  ];
        if (ymin > vertices[i+1]) ymin=vertices[i+1];
        if (zmin > vertices[i+2]) zmin=vertices[i+2];
        if (xmax < vertices[i  ]) xmax=vertices[i  ];
        if (ymax < vertices[i+1]) ymax=vertices[i+1];
        if (zmax < vertices[i+2]) zmax=vertices[i+2];
        
        if (!iPlane) { // the surface is not a plane
          CATBoolean b = ipPoints->**GetPointNor**(vector);
          if ( b ) 
          {
            if (ori<0) 
            {// the normal must be inverted
              normals[i+0] = (float) -vector->GetX() ;
              normals[i+1] = (float) -vector->GetY() ;
              normals[i+2] = (float) -vector->GetZ() ;
            } else {
              normals[i+0] = (float) vector->GetX() ;
              normals[i+1] = (float) vector->GetY() ;
              normals[i+2] = (float) vector->GetZ() ;
            }
          } else {
            // default normal: it is not computed by the tessellation
            normals[i+0] = 1.0 ;
            normals[i+1] = 0.0 ;
            normals[i+2] = 0.0 ;
          }
        }
        i +=3  ;
        ipPoints->**GoToNext**();
      }

`CATTessPointIterator::GetNbPoints` outputs the number of points computed by the tessellation. Now, the iterator is used as follows:

    * The `IsExhauted` method declares whether the end is reached. If there is no points anymore, it returns `0`.
    * The `GetPointXyz` returns the current point. The coordinates of this point are then put in the array that will be passed to the graphic primitive creation.
    * The `GetPointNor` returns the normal to the surface at the current point. The coordinates of this normal are also put in an array to be later used.
    * The `GoToNext` method skips to the next point of the iterator.

Now, the isolated triangles are read with the `CATTessTrianIter` iterator created by the tessellator. Its use is similar to the use of a `CATTessPointIter`.
    
    long  numberOfTriangles = ipTriangles->**GetNbTrian**();
      if ( NULL!= numberOfTriangles ) 
      {
        triangleIndice = new int [3 * numberOfTriangles] ;
        i = 0 ;
        while ( ipTriangles->**IsExhausted**()==0 ) {
          ipTriangles->**GetTrianNuPts**(NuPts);
          
          if (ori <0) {
            // triangles must be inverted
            triangleIndice[i]   =  NuPts[2]*3 ;
            triangleIndice[i+1] =  NuPts[1]*3 ;
            triangleIndice[i+2] =  NuPts[0]*3 ;
          } else {
            triangleIndice[i]   = NuPts[0]*3 ;
            triangleIndice[i+1] = NuPts[1]*3 ;
            triangleIndice[i+2] = NuPts[2]*3 ;
          }
          i += 3 ;
          ipTriangles->**GoToNext**();
        }
      }

As this method is also used to create the representation of a face, the relative orientation of the face and the surface is taken into account here by the ` ori` value, initialized with the corresponding output of the tessellator. In the same way, the strips of triangles are retrieved.
    
    long TotalPointNb=0;
      long numberOfStrips = ipStrips->**GetNbStri**(TotalPointNb) ; 
      if ( numberOfStrips ) {
        nbVertexPerTriangleStrip = new int [numberOfStrips] ;
        triangleStripIndice = new int [TotalPointNb] ;
        i = 0 ;
        j = 0 ;
        while ( ipStrips->**IsExhausted**()==0 ) {
          nbVertexPerTriangleStrip[i] = ipStrips->GetStriNbPts(); 
          ipStrips ->**GetStriNuPts**( &(triangleStripIndice[j]) ) ;
          for ( k=0 ; k < nbVertexPerTriangleStrip[i] ; k++ ) {
            triangleStripIndice[j+k] *= 3 ;
          }
          if (ori <0) {
            // Inverts to strip: Swap 2 by 2
            int m=0 ;
            for ( int l=0; l<(nbVertexPerTriangleStrip[i])/2 ;l++) {
              int i1 = triangleStripIndice[j+m];
              triangleStripIndice[j+m] = triangleStripIndice[j+m+1];
              triangleStripIndice[j+m+1] = i1 ;
              m +=2 ;
            }
          }
          j += nbVertexPerTriangleStrip[i] ;
          i += 1;
          ipStrips->**GoToNext**();
        }
      } 

Now, the representation can be created.
    
    CAT3DFaceGP * faceGP = NULL;
      if ( iPlane )
        faceGP = new **CAT3DPlanarFaceGP**(vertices,verticesArraySize,
                                       normals,
                                       triangleIndice,numberOfTriangles,
                                       triangleStripIndice, numberOfStrips, nbVertexPerTriangleStrip,
                                       triangleFanIndice,  numberOfFans,  nbVertexPerTriangleFan);
      
      else
        
        faceGP = new **CAT3DFaceGP**(vertices,verticesArraySize,
                                 normals,normalsArraySize,
                                 triangleIndice,numberOfTriangles, 
                                 triangleStripIndice, numberOfStrips, nbVertexPerTriangleStrip,
                                 triangleFanIndice,numberOfFans,nbVertexPerTriangleFan);
      
      if (NULL!=vertices)                 delete [] vertices;
      if (NULL!=normals)                  delete [] normals;
      if (NULL!=triangleIndice)           delete [] triangleIndice ;
      if (NULL!=triangleStripIndice)      delete [] triangleStripIndice ;
      if (NULL!=nbVertexPerTriangleStrip) delete [] nbVertexPerTriangleStrip ;
      if (NULL!=triangleFanIndice )       delete [] triangleFanIndice ;
      if (NULL!=nbVertexPerTriangleFan )  delete [] nbVertexPerTriangleFan ;
    
      CAT3DCustomRep * pSurfacicRep = new **CAT3DCustomRep**();
      CATGraphicAttributeSet ag ;
      ag.SetType(2);
      pSurfacicRep->**AddGP**(faceGP,ag);
    
      // Gets the bounding box
      CATMathPointf Center(float((xmin+xmax)/2.),
                           float((ymin+ymax)/2.),
                           float((zmin+zmax)/2.));
      double BoundingSphereRadius= sqrt((xmax-xmin)*(xmax-xmin)+
                                        (ymax-ymin)*(ymax-ymin)+
                                        (zmax-zmin)*(zmax-zmin))/2.;
      CAT3DBoundingSphere BoundingSphere( Center, float(BoundingSphereRadius));
      pSurfacicRep->**SetBoundingElement**(BoundingSphere); 

The graphic primitive is first created: it is a CAT3DPlanarFaceGP for a planar surface or a CAT3DFaceGP for a non-planar surface. This primitive is added to a new CAT3DCustomRep. The computed bounding box is set with the `SetBoundingElement` method, thus ending the construction of the surface representation.
#### Representation of a Body

All the previous methods are used to create the representation of a body. `CATICGMCellTessellator` is used to create data needed by the `CreateSurfaceRep` and `CreateCurveRep` methods. The faces, edges of wire domains, and vertices in volume are tessellated. In particular, neither the edges of the face, nor the vertices of the edges are represented.
    
    void CAAGemRep::CreateBodyRep(CATBody * ipiBody, CAT3DRep *& iopRep)  
    {
     ...
     iopRep=NULL;
     CAT3DBagRep* pBagRep = NULL;
     pBagRep = new CAT3DBagRep();
    
     CATICGMCellTessellator * pTessellator = **CATCGMCreateCellTessellator**(_sag);
    
     //-------------------------------------------------- 
     // Tessellates the faces
     //-------------------------------------------------- 
     if (NULL!=pTessellator)
     {
       // Retrieves all the faces
       CATLISTP(CATCell) cells;
       ipiBody->GetAllCells( cells,2);   // 2 for retrieving the faces
       int numberOfCells = cells.Size();
      
       for (int ifa=1 ; ifa<=numberOfCells ; ifa++)
       {
         pTessellator->**AddFace**((CATFace *)(cells[ifa]));
       }
       pTessellator -> **Run**();
     
       // for each face, retrieve the tessellation results
      
       for (ifa=1 ; ifa<=numberOfCells ; ifa++)
       {   
         CATFace * piFace = (CATFace*) cells[ifa]; 
        
         // a special visualization for infinite face
         if (TRUE== piFace->**GetInfinite**())
         {
           CATOrientation ori;
           CATGeometry*    piGeom= piFace->GetGeometry(&ori);
           if (NULL!= piGeom && piGeom->IsATypeOf(CATPlaneType) )
           {
              CATPlane * piPlane = (CATPlane *)piGeom;      
              CAT3DRep* pRep=NULL;
              **CreatePlaneRep**(piPlane,pRep);
              if (NULL!=pRep)
             {
              if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
              pBagRep->AddChild(*pRep);
             }
           }
         }
         else
         {
           CATBoolean isPlanar;
           CATTessPointIter *    pPoints  = NULL;
           CATTessStripeIter *   pStrips    = NULL;
           CATTessFanIter *      pFans      = NULL;
           CATTessPolyIter *     pPolygons  = NULL;
           CATTessTrianIter *    pTriangles = NULL;
           short side;
         
           pTessellator -> **GetFace**(piFace,isPlanar,&pPoints,&pStrips,&pFans,&pPolygons,&pTriangles,&side);
           CAT3DRep * pRep=NULL;
           **CreateSurfaceRep**(isPlanar, side, pPoints, pStrips,pFans, pPolygons, pTriangles,pRep);
           if (NULL!=pRep)
           {
              if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
              pBagRep->AddChild(*pRep);
           }
         }
       }
       pTessellator->Release();
       pTessellator = NULL;
     }
    
     //-------------------------------------------------- 
     // Now tessellate the wire domains (not the edges of faces)
     //-------------------------------------------------- 
     // ......
      
     // Returns the rep
     iopRep=pBagRep;
    }

All the faces of the body are retrieved in one shot with the `GetAllCells` method of the CATTopology interface from which the body derives. The 2 value is the dimension for the faces. All these faces are `Add`ed to `CATICGMCellTessellator`, that is then `Run`. Now, for each face, the results are retrieved:

    * If the face is infinite, the representation of a plane is created, if the associated geometry is a plane.
    * Otherwise, the `GetFace` method of the `CATICGMCellTessellator` returns all the data that is needed to create the representation of a surface.

The tessellator is released after use.

The way to create the representation of the vertices in volume and the edges of the wires is very similar.
    
    // the number of domains
     long nbDomains= ipiBody->**GetNbDomains**();
     CATLISTP(CATCell)  cells;
     int numberOfCells =0;
    
     for (int dom = 1;dom<=nbDomains;dom++)
     {
       CATDomain * piDomain = ipiBody->**GetDomain**( dom );
        
       // ------ Wire
       if (NULL!=piDomain && 1==(piDomain->IsATypeOf(**CATWireType**)) )
       {
         // Creates a cell tessellator
         pTessellator = CATCGMCreateCellTessellator(_sag); 
         if (pTessellator!=NULL)
         {
           // Retrieves the number of edges of the wire
           cells.RemoveAll();
           piDomain->**GetAllCells**(cells,1);
           numberOfCells = cells.Size();
           
           // Adds the edges to tessellate
           for  (int i=1 ; i<=numberOfCells ; i++)
           { 
             CATEdge * piEdge = (CATEdge*) cells[i];
             pTessellator -> **AddEdge**(piEdge);
           }
    
           // Runs it
           pTessellator->**Run**();
        
           // for each each edge 
           for  ( i=1 ; i<=numberOfCells ; i++)
           { 
             CATEdge * piEdge = (CATEdge*) cells[i];
             long  numOfPoints;
             float   * aPoints= NULL;
             
             // Retrieves the tessellation results
             pTessellator -> **GetEdge**(piEdge,numOfPoints,&aPoints);
    
             CAT3DRep * pRep=NULL;
    
             // Creates the rep
             **CreateEdgeRep** (piEdge, numOfPoints,aPoints,pRep);
             if (NULL!=pRep)
             {
              if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
              pBagRep->AddChild(*pRep);
             }
           }
           pTessellator->Release();
           pTessellator = NULL;
         }
       }
    
       //  ----- and the points
       else if(NULL!=piDomain && 1==(piDomain->IsATypeOf(**CATVertexInVolumeType**)))
       {
         
         CATCell * piCell = piDomain->**GetCell**(1);
         if (NULL!=piCell) 
         {
           CATVertex * piVertex=(CATVertex * )piCell;
    
           // Gets the geometry of the vertex
           CATPoint * piPoint = piVertex->GetPoint();
    
           // Creates the rep
           CAT3DRep * pRep=NULL;
           CATMathPoint point;
           piPoint->GetMathPoint(point);
           **CreatePointRep**  (point,pRep);
           if (NULL!=pRep)
           {
              if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
              pBagRep->AddChild(*pRep);
           }
    
         }	
       }
     }

We first loop on all the domains of the body. `GetDomain` returns the pointer to the i-th domain.

    * If the domain is a wire: 
      * All the edges of this wire are retrieved: `GetAllCells` is called with 1.
      * They are `Add`ed to the created `CATICGMCellTessellator`.
      * The tessellator is `Run`.
      * For each edge, the tessellation results are retrieved: `GetEdge`.
      * These results are passed to `CreateEdgeRep` that created the representation.
      * The tessellator is released after use.
    * If the domain is a vertex in volume: 
      * The unique cell of this domain is retrieved.
      * The representation of the corresponding point is created.
#### Representation of an Edge

The representation is created in a very similar way as in the curve case. They only differ by the process of the degenerated elements
    
    void CAAGemRep::CreateEdgeRep  (CATEdge * ipiEdge, 
                                    long & ioNumOfPoints, 
                                    float * oaPoints, 
                                    CAT3DRep *& iopRep)
    {
      CAT3DRep *pRep = NULL;
      	   
      CATMathBox boundingBox;
      CATMathPoint low,high;
      
      ipiEdge->GetBoundingBox(boundingBox);
      boundingBox.GetLow(low);
      boundingBox.GetHigh(high);
      CATMathVector diagonal=high-low;
      double diagonalLength= diagonal.Norm();
      
      if ( diagonalLength > _piGeomFactory->**GetResolution**() )
      {		     		
         **CreateCurveRep** (ioNumOfPoints,oaPoints,pRep);
      }
      // The edge is a point
      else
      {
        //Gets the coordinates of a point
        CATPointOnEdgeCurve *piStartPoec=NULL;
        ipiEdge->**GetVerticesPointsOnEdgeCurve**(&piStartPoec,NULL );
        CATMathPoint pt;
        piStartPoec->GetMathPoint(pt);
        **CreatePointRep**(pt,pRep);
      }
    
      // Returns the rep
      iopRep = pRep;
    }

If the edge has a length greater than the factory resolution, the representation of a curve is created.

Otherwise, one point of the edge is recovered, and a representation of this point is created. Notice that to get the points extremities of an edge, the `CATEdge::GetVerticesPointsOnEdgeCurve` method can be used.
## In Short

This use case offers the programmer a way to visualize the geometry and topology created by the CATGeoFactory. Meanwhile, it illustrates how to tessellate geometric objects.
## References

[1] |  [ Building and Launching a Use Case](../CAADocUseCases/CAADocRunSample.md)  
---|---  
[2] | [Using a Tessellation Operator](CAACgmUcTesBody.md)  
## History

Version: **1.1** [Nov 2000] | Use of CAT3DCustomRep for the graphic representation of a surface representation.  
---|---  
Version: **1** [Jun 2000] | Document created
