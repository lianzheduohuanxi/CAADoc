// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAVisRepWindow.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy
#include "CATDlgPushItem.h"               // Dialog's object 
#include "CATDlgBarMenu.h"
#include "CATDlgSubMenu.h"

// Visualization Framework
#include "CATNavigation3DViewer.h"
#include "CAT3DBagRep.h"
#include "CAT3DCustomRep.h"
#include "CAT3DLineGP.h"
#include "CAT3DMarkerGP.h"
#include "CAT3DPlanarFaceGP.h"

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAAVisRepWindow::CAAVisRepWindow(CATInteractiveApplication * iParentCommand)                              
       : CATDlgDocument(iParentCommand, "CAAVisRepWindowId"),
         _pApplication(iParentCommand),_pTheModelToDisplay(NULL),_p3DViewer(NULL)

{
  cout << "CAAVisRepWindow::CAAVisRepWindow" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAAVisRepWindow::~CAAVisRepWindow()
{ 
  cout << "CAAVisRepWindow::~CAAVisRepWindow" << endl; 

  if ( NULL != _pTheModelToDisplay )
  {
     // The bag and its children are deleted
     _pTheModelToDisplay->Destroy();
     _pTheModelToDisplay = NULL ;
  }
  
  // All Dialog's Object children of this Window are
  // automatically deleted ( The _p3DViewer included )
  _pApplication = NULL ;
  _p3DViewer    = NULL ;
}

//--------------------------------------------------------------------------------------

void CAAVisRepWindow::Build()
{
  cout << "CAAVisRepWindow::Build" << endl;

  CreateMenuBar();

  CreateViewer();
  
  CreateModelRepresentation();

  VisualizeModel();

}
//--------------------------------------------------------------------------------------

void CAAVisRepWindow::CreateMenuBar()
{
   CATDlgBarMenu * pMenuBar = NULL ;
   pMenuBar  = new CATDlgBarMenu(this, "MenuBar");
   
   CATDlgSubMenu * pFileMenu = NULL ;
   pFileMenu = new CATDlgSubMenu(pMenuBar, "File");

   CATDlgPushItem * pPushItem = NULL ;
   pPushItem = new CATDlgPushItem(pFileMenu, "Exit"); 

   AddAnalyseNotificationCB(pPushItem,
                            pPushItem->GetMenuIActivateNotification(),
                           (CATCommandMethod)&CAAVisRepWindow::Exit, NULL);

   AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAAVisRepWindow::Exit, NULL);
}

//--------------------------------------------------------------------------------------
void CAAVisRepWindow::CreateViewer()
{

  _p3DViewer = new CATNavigation3DViewer( this, "Navigation3DId",
                                          CATDlgFraNoTitle, 800, 450);


  // Changes the color of the background
  _p3DViewer->SetBackgroundColor(0.2f,0.2f,0.6f);

  Attach4Sides( _p3DViewer);

}
//--------------------------------------------------------------------------------------                 
void CAAVisRepWindow::CreateModelRepresentation()
{
   _pTheModelToDisplay = new CAT3DBagRep() ;

   // ------------------------------------------
   // Creation of the line defined on the X axis
   // ------------------------------------------ 
   CAT3DCustomRep * pLineOnXAxis = NULL ;
   
   CATMathPoint PositionXPoint1(20.f,0.f,0.f ) ;
   CATMathPoint PositionXPoint2(200.f,0.f,0.f ) ;

   int NONE = 0 ;
   pLineOnXAxis = CreateLineEndedByTwoPoints(PositionXPoint1,PositionXPoint2,NONE);

   if ( NULL != pLineOnXAxis )
   {
      _pTheModelToDisplay->AddChild(*pLineOnXAxis);
   }

   // ------------------------------------------
   // Creation of the line defined on the Y axis 
   // ------------------------------------------
   CAT3DCustomRep * pLineOnYAxis = NULL ;
   
   CATMathPoint PositionYPoint1(0.f,20.f,0.f );
   CATMathPoint PositionYPoint2(0.f,200.f,0.f ) ;

   int EDGE = 1 ;
   pLineOnYAxis = CreateLineEndedByTwoPoints(PositionYPoint1,PositionYPoint2,EDGE);

   if ( NULL != pLineOnYAxis )
   {
       // The rep defined the thickness and the color of the line GP
       // but notice that the line type is allways those defined on the line GP
       //
       pLineOnYAxis->SetInheritanceMode(LINEWIDTH_INHERITANCE | COLOR_INHERITANCE );
       pLineOnYAxis->SetThickness(1);
       pLineOnYAxis->SetColor(MAGENTA);

       // The rep is added in the bag
      _pTheModelToDisplay->AddChild(*pLineOnYAxis);
   }

   // ----------------------------------------------
   // Creation of the first cube 
   //   - Color    : Red
   //   - Position : (50,50,0)
   //   - Face     : Volum  (one-side lighting) 
   // ------------------------------------------
   CAT3DCustomRep * pRedCube = NULL ;

   CATMathPoint RedCubePosition(50.f,50.f,0.f );
 
   int VOLUM = 3 ;
   pRedCube = CreateOpenCube(RedCubePosition,VOLUM);

   if ( NULL != pRedCube )
   {
       // The rep redefined the color of each face GP
       pRedCube->SetInheritanceMode(COLOR_INHERITANCE);
       pRedCube->SetColor(RED);

       // The cube is added in the bag
      _pTheModelToDisplay->AddChild(*pRedCube);
   }

   // ----------------------------------------------
   // Creation of the second cube 
   //   - Color    : White
   //   - Position : (50,150,0)
   //   - Face     : Skin ( two-sided lighting )
   // ------------------------------------------
   CATMathPoint WhiteCubePosition(50.f,150.f,0.f );
   CAT3DCustomRep * pWhiteCube = NULL ;

   int SKIN = 2 ;
   pWhiteCube = CreateOpenCube(WhiteCubePosition,SKIN);
   
   if ( NULL != pWhiteCube )
   {
       // The cube is added in the bag
      _pTheModelToDisplay->AddChild(*pWhiteCube);
   }

}
//--------------------------------------------------------------------------------------
CAT3DCustomRep * CAAVisRepWindow::CreateLineEndedByTwoPoints( const CATMathPoint &iStartPoint,
                                                              const CATMathPoint &iEndPoint,
                                                              int                 iEdgeType )
{
    CAT3DCustomRep * pTheRepToReturn = NULL ;
 
    pTheRepToReturn = new CAT3DCustomRep();

    // ---------------------------------------------
    // 1- Create a Line ( green ) with 2 points yellow 
    // ---------------------------------------------

    float coord[6] ;
    coord[0] = (float) iStartPoint.GetX() ;	  	  
    coord[1] = (float) iStartPoint.GetY() ;
    coord[2] = (float) iStartPoint.GetZ() ;
    coord[3] = (float) iEndPoint.GetX() ;	  	  
    coord[4] = (float) iEndPoint.GetY() ;
    coord[5] = (float) iEndPoint.GetZ() ;

    // --------------------------------
    // 1- Creates the Green dotted Line 
    // -------------------------------- 

    CAT3DLineGP * pLineGP = new CAT3DLineGP(coord,2) ;

    CATGraphicAttributeSet LineAG ;
    LineAG.SetColor(GREEN);

    // The thickness index is between 1 to 16
    LineAG.SetThickness(4);

    // See documentation to have another argument
    LineAG.SetLineType(2);

    // None : the line is allways seen 
    // EDGE : the line is hidden by object in front of it.
    LineAG.SetType(iEdgeType) ;

    pTheRepToReturn->AddGP(pLineGP,LineAG);

    // -----------------------------
    // 2- Creates the Yellow Points   
    // -----------------------------

    CAT3DMarkerGP * pPointGP = new CAT3DMarkerGP(coord,2,CROSS);

    CATGraphicAttributeSet PointAG ;
    PointAG.SetColor(YELLOW);

    pTheRepToReturn->AddGP(pPointGP,PointAG);

    // ------------------------------
    // 3- Computes the BoundingSphere 
    // ------------------------------

    CATMathPoint Center =  iStartPoint + ((iEndPoint-iStartPoint) / 2.f)  ;
    float Radius = (float) iStartPoint.DistanceTo(Center);
    CAT3DBoundingSphere BoundingSphere(Center,Radius);

     // Sets the bounding sphere
    pTheRepToReturn->SetBoundingElement(BoundingSphere) ;


    return (pTheRepToReturn);
}

//--------------------------------------------------------------------------------------

CAT3DCustomRep * CAAVisRepWindow::CreateOpenCube( const CATMathPoint &iStartPoint,
                                                  int iTypeFace )
{
    CAT3DCustomRep * pTheRepToReturn = NULL ;
 
    // ------------------------------------------------------------------
    // 1- The cube is defined with 8 points computed from the iStartPoint
    // ------------------------------------------------------------------
   
    CATMathVector VectorX(50.f,0.f,0.f);
    CATMathVector VectorY(0.f,50.f,0.f);
    CATMathVector VectorZ(0.f,0.f,50.f);

    // 4 points in a plane: P
    CATMathPoint Point1 = iStartPoint ;
    CATMathPoint Point2 = iStartPoint + VectorY ;
    CATMathPoint Point3 = iStartPoint + VectorY + VectorX ;
    CATMathPoint Point4 = iStartPoint + VectorX ;

    // 4 points in a plane: P + VectorZ
    CATMathPoint Point5 = Point1  + VectorZ;
    CATMathPoint Point6 = Point2  + VectorZ;
    CATMathPoint Point7 = Point3  + VectorZ;
    CATMathPoint Point8 = Point4  + VectorZ ;


    // --------------------------------------------------
    // 2- Create a cube with 6 faces whose one is noshow
    // ---------------------------------------------------
    
    CATGraphicAttributeSet FaceNoShowAG ;
    FaceNoShowAG.SetShowMode(1);

    // --------------------------------------------------
    // 3- Each Face GP as the type VOLUM or SKIN: 
    //    VOLUM = only one side-face is paint  
    //    SKIN  = the two side face are  paint
    // ---------------------------------------------------

    CATGraphicAttributeSet FaceShowAG ;
    FaceShowAG.SetType(iTypeFace);
   
    // --------------------------------------------------------------
    // 4- The graphic representation of the cube is a CAT3DCustomRep
    //    composed of 6 CAT3DPlanarFaceGP.
    // --------------------------------------------------------------
    pTheRepToReturn = new CAT3DCustomRep();

    CAT3DPlanarFaceGP * pPlanGP = NULL ; 
    
    // Bottom face 
    // -----------
    pPlanGP = CreateFaceGP(Point4,Point3,Point1,Point2);                                     
    pTheRepToReturn->AddGP(pPlanGP,FaceShowAG);

    // Top face (no-show) 
    // ------------------
    pPlanGP = CreateFaceGP(Point5,Point6,Point8,Point7);
    pTheRepToReturn->AddGP(pPlanGP,FaceNoShowAG);

    // Left face  
    // ----------
    pPlanGP = CreateFaceGP(Point5,Point8,Point1,Point4);
    pTheRepToReturn->AddGP(pPlanGP,FaceShowAG);

    // Right face 
    // -----------  
    pPlanGP = CreateFaceGP(Point7,Point6,Point3,Point2);
    pTheRepToReturn->AddGP(pPlanGP,FaceShowAG);

    // Front face
    // ----------   
    pPlanGP = CreateFaceGP(Point8,Point7,Point4,Point3);
    pTheRepToReturn->AddGP(pPlanGP,FaceShowAG);

    // Back face 
    // ---------
    pPlanGP = CreateFaceGP(Point6,Point5,Point2,Point1);
    pTheRepToReturn->AddGP(pPlanGP,FaceShowAG);

    // ------------------------------------------
    // 5- Computes the BoundingSphere of the Cube
    // ------------------------------------------

    CATMathPoint Center = iStartPoint + (VectorY + VectorX + VectorZ)/2;

    float Radius = (float) iStartPoint.DistanceTo(Center);
    CAT3DBoundingSphere BoundingSphere(Center,Radius);

    // Sets the bounding sphere
    pTheRepToReturn->SetBoundingElement(BoundingSphere) ;

    return pTheRepToReturn;

}

//-------------------------------------------------------------------------------------- 
CAT3DPlanarFaceGP * CAAVisRepWindow::CreateFaceGP(const CATMathPoint & iPointTopLeft    ,
                                                  const CATMathPoint & iPointTopRight   ,
                                                  const CATMathPoint & iPointBottomLeft ,
                                                  const CATMathPoint & iPointBottomRight)
                                   
{
    CAT3DPlanarFaceGP * pTheGPToReturn = NULL ;

    //---------------------------------------------------------
    // 1- Data useful for the Graphic Primitive to create
    // --------------------------------------------------------
    
    float point[12];
    float normal[3];

    // 0 Triangle
    int nbTriangle       = 0 ;
    int * triangleIndice = NULL ;

    // 1 Triangle strip 
    int nbVertexPerTriangleStrip[1] = { 4 };
    int triangleStripIndice[4]      = { 0, 3, 6, 9 };
    int         nbTriangleStrip     = 1 ;

    // 0 triangle fan
    int *      triangleFanIndice = NULL ;
    int            nbTriangleFan = 0 ;
    int * nbVertexPerTriangleFan = NULL;

    //---------------------------------------------------------
    // 2- Definition of the Triangle Strip
    // --------------------------------------------------------
 
    /* 
     
      Given your 4 points so that your face is just in front of your eyes. and the normal
      sight goes from the face to you. 

              1             3 

      Top     X-------------X
              |           / |                 1 = iPointTopLeft
              |       T /   |                 2 = iPointBottomLeft
           U  |       /     |                 3 = iPointTopRight
              V     /       V                 4 = iPointBottomRight
              |   /         |
              | /           |
      Bottom  X-------------X             

             Left          Right

              2             4 
             
      The Strip is defined with 4 points given in this ordre: [1,2,3,4]. The first
      triangle [1,2,3] allways defined the normal. 
      
      Normal = U ^ T = Vector [2-1] ^ Vector [3-2].    

      
    */

    // --------------------------------------------------------
    // 3- Fills Data 
    // ---------------------------------------------------------

    point[0]= iPointTopLeft.GetX(); 
    point[1]= iPointTopLeft.GetY();
    point[2]= iPointTopLeft.GetZ();

    point[3]= iPointBottomLeft.GetX(); 
    point[4]= iPointBottomLeft.GetY(); 
    point[5]= iPointBottomLeft.GetZ();

    point[6]= iPointTopRight.GetX() ;
    point[7]= iPointTopRight.GetY(); 
    point[8]= iPointTopRight.GetZ();

    point[9]  = iPointBottomRight.GetX();
    point[10] = iPointBottomRight.GetY(); 
    point[11] = iPointBottomRight.GetZ();

    CATMathVector U = iPointBottomLeft - iPointTopLeft ;
    CATMathVector T = iPointTopRight   - iPointBottomLeft ; 
    CATMathVector N = U ^ T;
    
    // The Normal must be normalized.
    N.Normalize() ;

    normal[0] = N.GetX();
    normal[1] = N.GetY(); 
    normal[2] = N.GetZ();

    // ---------------------------------------------------------
    // 4- The Face is defined with 1 triangle strip of 2 triangles.
    // ---------------------------------------------------------
    pTheGPToReturn = new CAT3DPlanarFaceGP(point,12,normal,triangleIndice,nbTriangle,
                                  triangleStripIndice,nbTriangleStrip,
                                  nbVertexPerTriangleStrip,
                                  triangleFanIndice,
                                  nbTriangleFan,
                                  nbVertexPerTriangleFan);
     
    return pTheGPToReturn ;
}
//--------------------------------------------------------------------------------------                 
void CAAVisRepWindow::VisualizeModel()
{

   if ( (NULL != _p3DViewer) && ( NULL != _pTheModelToDisplay) )
   {    
      // Instruction to do once
      _p3DViewer->AddRep((CAT3DRep*)_pTheModelToDisplay);

      // Instruction to do at each  representation modification 
      _p3DViewer->Draw();
   }

}
//--------------------------------------------------------------------------------------

void CAAVisRepWindow::Exit(CATCommand         * iSendingCommand, 
                           CATNotification    * iSentNotification, 
                           CATCommandClientData iUsefulData)
{
   _pApplication->Destroy();
   _pApplication = NULL ;
}


