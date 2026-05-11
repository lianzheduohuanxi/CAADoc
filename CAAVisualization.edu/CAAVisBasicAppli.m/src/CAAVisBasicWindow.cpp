// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAVisBasicWindow.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy
#include "CATDlgPushItem.h"               // Dialog's object 
#include "CATDlgBarMenu.h"
#include "CATDlgSubMenu.h"

// Visualization Framework
#include "CATNavigation3DViewer.h"
#include "CAT3DBagRep.h"
#include "CAT3DCuboidRep.h"
#include "CAT3DSimpleSphereRep.h"

// Mathematics Framework
#include "CATMathPointf.h"
#include "CATMathVectorf.h"

// C++ Standard library
#include "iostream.h"

//--------------------------------------------------------------------------------------
CAAVisBasicWindow::CAAVisBasicWindow(CATInteractiveApplication * iParentCommand)                              
                      : CATDlgDocument(iParentCommand, "CAAVisRepWindowId"),
	                    _pApplication(iParentCommand),_pTheModelToDisplay(NULL),_p3DViewer(NULL)

{
  cout << "CAAVisBasicWindow::CAAVisBasicWindow" << endl;

  // Don't construct any Dialog's Object child in the constructor 
  // Use the Build Method to do this.

}

//--------------------------------------------------------------------------------------

CAAVisBasicWindow::~CAAVisBasicWindow()
{ 
  cout << "CAAVisBasicWindow::~CAAVisBasicWindow" << endl; 

  if ( NULL != _pTheModelToDisplay )
  {
     // The bag and its children are deleted
     _pTheModelToDisplay->Destroy();
     _pTheModelToDisplay = NULL ;
  }
  
  // All Dialog's Object children of this Window are
  // automatically deleted ( The _p3DViewer included )
  _p3DViewer    = NULL ;
  _pApplication = NULL ;
}

//--------------------------------------------------------------------------------------

void CAAVisBasicWindow::Build()
{
  cout << "CAAVisBasicWindow::Build" << endl;

  CreateMenuBar();

  CreateViewer();
  
  CreateModelRepresentation();

  VisualizeModel();
}
//--------------------------------------------------------------------------------------

void CAAVisBasicWindow::CreateMenuBar()
{
   CATDlgBarMenu * pMenuBar = NULL ;
   pMenuBar  = new CATDlgBarMenu(this, "MenuBar");
   
   CATDlgSubMenu * pFileMenu = NULL ;
   pFileMenu = new CATDlgSubMenu(pMenuBar, "File");

   CATDlgPushItem * pPushItem = NULL ;
   pPushItem = new CATDlgPushItem(pFileMenu, "Exit"); 

   AddAnalyseNotificationCB(pPushItem,
                            pPushItem->GetMenuIActivateNotification(),
                           (CATCommandMethod)&CAAVisBasicWindow::Exit, NULL);

   AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(),
                           (CATCommandMethod)&CAAVisBasicWindow::Exit, NULL);
}

//--------------------------------------------------------------------------------------
void CAAVisBasicWindow::CreateViewer()
{

  // The window contains a 3DViewer which allows 3D Manipulations 
  _p3DViewer = new CATNavigation3DViewer( this, "3DViewerId",CATDlgFraNoTitle, 800, 450);

  // Changes the color of the background
  _p3DViewer->SetBackgroundColor(0.2f,0.2f,0.6f);

  // The Viewer is attached to the 4 sides of the Window.
  Attach4Sides( _p3DViewer);

}
//--------------------------------------------------------------------------------------                 
void CAAVisBasicWindow::CreateModelRepresentation()
{
  // ------------------------------------------
  // The Top of the graphic representation tree
  // ------------------------------------------

  _pTheModelToDisplay = new CAT3DBagRep();

  // ------------------------------------------
  // Create a cuboid
  // ------------------------------------------
   
  CATMathPointf  Corner (-20.f, -20.f,  0.f);
  CATMathVectorf FirstVector ( 20.f,   0.f,  0.f);
  CATMathVectorf SecondVector (  0.f,  20.f,  0.f);
  CATMathVectorf ThirdVector (  0.f,   0.f, 20.f);


  CAT3DCuboidRep * pCuboid = new CAT3DCuboidRep(Corner,
                                                FirstVector,
                                                SecondVector,
                                                ThirdVector);
  if ( NULL != pCuboid )
  {
      pCuboid->SetColor(YELLOW);
      _pTheModelToDisplay->AddChild(*pCuboid);
  }

  // ------------------------------------------
  // Create a sphere
  // ------------------------------------------
  CATMathPointf  Center (0.f, 0.f, 20.f);
  float          Radius        = 10.f;


  CAT3DSimpleSphereRep * pSphere = new CAT3DSimpleSphereRep(Center, Radius);
                                                             
  if ( NULL != pSphere )
  {

     pSphere->SetColor(GREEN);
     pSphere->SetTransparentMode(1);

    _pTheModelToDisplay->AddChild(*pSphere);
  }
  
}

//--------------------------------------------------------------------------------------                 
void CAAVisBasicWindow::VisualizeModel()
{

   if ( (NULL != _p3DViewer) && ( NULL != _pTheModelToDisplay) )
   {    
      // Instruction to do once .
      _p3DViewer->AddRep((CAT3DRep*)_pTheModelToDisplay);

      // Instruction to do at each  representation modification 
      _p3DViewer->Draw();
   }

}
//--------------------------------------------------------------------------------------

void CAAVisBasicWindow::Exit(CATCommand         * iSendingCommand, 
                                  CATNotification    * iSentNotification, 
                                  CATCommandClientData iUsefulData)
{
   _pApplication->Destroy();
   _pApplication = NULL ;
}


