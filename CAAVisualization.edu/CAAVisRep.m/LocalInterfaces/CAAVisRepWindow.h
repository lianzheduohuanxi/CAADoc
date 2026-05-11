#ifndef CAAVisRepWindow_h
#define CAAVisRepWindow_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
//  Abstract of the class:
//  ----------------------
//
//  This window contains a model of 4 objects which are :
//
//    - A) a first line ended by 2 points
//    - B) a second line ended by 2 points
//    - C) a red   cube without the top face 
//    - D) a white cube without the top face
//
//  Each object is graphically represented by a CAT3DCustomRep, and to be seen
//  they are attached to a CAT3DBagREp. 
// 
//  The CAT3DCustomRep of A and B objects are defined so :
// 
//     - a CAT3DLineGP : green , dotted and with a large thickness 
//     - a CAT3DMarkerGP with 2 points which are cross and yellow
//     
//     ==> See the CreateLineEndedByTwoPoints method
//  
//  The CAT3DCustomRep of C and D objects are defined so : 
//
//     - 6 CAT3DPlanarFaceGP whose one is no show. That allows to see inside the 
//       cube. 
// 
//     ==> See the CreateOpenCube method
//     
//  The Object A is visually so:
//  
//     - The Line is green, dotted with a big thickness 
//     - Points are yellow cross 
//     
//     Each graphic attributes are defined on the Graphic Primitive. The 
//     default Attribute Graphic of the Graphic Representation is not used. 
//     
//  The Object B is visually so:
//  
//     - The Line is magenta, dotted with a small thickness
//     - The Line is hidden by cube : use EDGE type  
//     - Points are magenta cross . 
//     
//     The Magenta Color and the small thickness provide from the 
//     Attribute Graphic of the Graphic Representation. We have set 
//     Color and LineWith inheritance. 
//     
//  The Object C is visually so:
//     
//     - Red and you dont see side face inside the cube. Each face is defined
//       as VOLUM. 
//       
//     The Red Color  provide from the Attribute Graphic of the Graphic
//     Representation. We have set Color inheritance. 
//
//  The Object D is visually so:
//     
//     - White and you see side face inside the cube. Each face is defined
//       as SKIN. 
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
class CAT3DCustomRep ;
class CATNavigation3DViewer;
class CATMathPoint;
class CAT3DPlanarFaceGP ;

class CAAVisRepWindow : public CATDlgDocument
{
  // Declares the CAAVisRepWindow.CATNls file as the dialog message catalog
  DeclareResource(CAAVisRepWindow, CATDlgDocument)

  public:
   /*
    * Constructor. No initialization is actually done in it.
    * The real initialization is done in the Build method.
    */
    CAAVisRepWindow(CATInteractiveApplication * iParentCommand);

    virtual ~CAAVisRepWindow();

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
    // This model contains the A, B, C and D objects.
    // 
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


    // CreateLineEndedByTwoPoints
    // ---------------------------
    // The Line is defined by the iStartPoint and iEndPoint points.
    // Points are "sticked" at each side of the line.
    // iEdgeType allows to hidde (EDGE) or not (NONE) the line with 
    // objects in front of it.
    //  
    CAT3DCustomRep * CreateLineEndedByTwoPoints(const CATMathPoint &iStartPoint,
                                                const CATMathPoint & iEndPoint,
                                                int                  iEdgeType);

    // CreateOpenCube
    // ---------------
    // iStartPoint defines a corner of the cube. The top face is not seen which
    // allows to see inside it.
    // iTypeFace is VOLUM, one side of face are lghting, else SKIN and two faces
    // are painted.
    //
    CAT3DCustomRep * CreateOpenCube( const CATMathPoint &iStartPoint,
                                                    int iTypeFace ) ;
    // CreateFaceGP
    // ---------------
    // 
    CAT3DPlanarFaceGP * CreateFaceGP(const CATMathPoint & iPointTopLeft,
                                   const CATMathPoint & iPointTopRight   ,
                                   const CATMathPoint & iPointBottomLeft ,
                                   const CATMathPoint & iPointBottomRight) ;
    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisRepWindow ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisRepWindow(const CAAVisRepWindow &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAVisRepWindow & operator =  (const CAAVisRepWindow &iObjectToCopy);

  private:


    /* The parent widget (a CATInteractiveApplication instance) */
    CATInteractiveApplication * _pApplication;

    CAT3DBagRep               * _pTheModelToDisplay ;

    CATNavigation3DViewer     * _p3DViewer ;
};
#endif
