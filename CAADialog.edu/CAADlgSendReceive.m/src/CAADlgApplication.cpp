// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAADlgApplication.h"
#include "CAADlgModel.h"
#include "CAADlgContainer.h"
#include "CAADlgViewScreen.h"
#include "CAADlgViewPlot.h"
#include "CAADlgElement.h"

#ifdef _WINDOWS_SOURCE
#include "CATDlgDocument.h"
#endif

// Constructor of an application
// -----------------------------

CAADlgApplication::CAADlgApplication(): CATInteractiveApplication(NULL, "") 
{
  printf("The CAADlgSendReceive application is created.\n\n");
  _pCommandWithFocus=NULL;
}

// Destructor of an application
// ----------------------------

CAADlgApplication::~CAADlgApplication() 
{
  printf("The CAADlgSendReceive application is deleted.\n");
  _pCommandWithFocus=NULL;
}

// Begin the application
// --------------------

void CAADlgApplication::BeginApplication() 
{

  // -------------------------------------
  // 1 - Beginning
  // -------------------------------------

  printf("1- The CAADlgSendReceive application is running.\n\n");

#ifdef _WINDOWS_SOURCE
  // The CATDlgDocument object will be automatically deleted at the end of the application
  CATDlgDocument *doc=new CATDlgDocument(this, "TheWindow");
  doc->SetVisibility(CATDlgShow);
#endif

  // Command to initialize the mechanism.
  // This command is never used.
  // 
  _pCommandWithFocus=new CATCommand(NULL);
  RequestStatusChange(CATCommandMsgRequestSharedMode, _pCommandWithFocus);

  // -------------------------------------
  // 2 - Objects creation for scenarios
  // -------------------------------------

  // Creation of two views: a screen and a plot
  printf("2- Object's creation:\n\n");

  CAADlgViewScreen Screen;
  CAADlgViewPlot   Plot;

  // Creation of a container
  CAADlgContainer *   pContainer = new CAADlgContainer("ModelContainer");

  // Creation of a model. It's a command whose parent is the container
  CAADlgModel   Model(pContainer, "Geometric");

  // Creation of some elements
  CAADlgElement * pLine     = new CAADlgElement("Line");
  CAADlgElement * pPoint    = new CAADlgElement("Point");
  CAADlgElement * pSurface  = new CAADlgElement("Surface");
  CAADlgElement * pCylinder = new CAADlgElement("Cylinder");

  printf("\n");

  // -------------------------------------
  // 3 - Scenarios
  // -------------------------------------

  // The screen takes the focus to become the active command. It will receive
  // all the notifications coming from the command tree structure that reach the
  // command selector.
  printf("3- The screen takes the focus:\n\n");
  Screen.WantedFocus();
  printf("\n");
  Model.Add(pLine);
  printf("\n");
  Model.Add(pPoint);
  printf("\n");
  Model.Remove(pLine);
  printf("\n");

  // The plot takes the focus to become the active command. It will receive
  // all the notifications coming from the command tree structure that reach the
  // command selector.
  // This automatically makes the screen release the focus.
  printf("4-The plot takes the focus:\n\n");
  Plot.WantedFocus();
  printf("\n");
  Model.Add(pSurface);
  printf("\n");
  Model.Remove(pPoint);
  printf("\n");

  // No point any longer exists, and thus point removal fails.
  // The model will send an error notification that will be caught by the 
  // the container. The plot will not receive it.
  // It's the Case B described in the header file.
  //
  Model.Remove(pPoint);
  printf("\n");

  // The screen takes the focus again, and receives all notifications coming
  // from the model
  printf("5-The screen takes the focus again:\n\n");
  Screen.WantedFocus();
  printf("\n");
  Model.Remove(pSurface);
  printf("\n");
  Model.Add(pCylinder);
  printf("\n");
  Model.Remove(pCylinder);
  printf("\n");

  // -----------------------
  // 4- Object's Destruction 
  // -----------------------
  printf("6- Object's destruction:\n\n");

  pLine->Release(); ;
  pLine = NULL ;
  pPoint->Release();;
  pPoint = NULL ;
  pSurface->Release(); ;
  pSurface = NULL ;
  pCylinder->Release(); ;
  pCylinder = NULL ;

  pContainer->RequestDelayedDestruction();
  pContainer= NULL ;
  
  // ------------------------------------
  // 5- The application should be deleted
  // ------------------------------------
  printf("\n");
  Destroy();
}

// End the application
// -------------------

int CAADlgApplication::EndApplication() 
{
  printf("\nThe CAADlgSendReceive application is going to finish.\n");

  _pCommandWithFocus->RequestDelayedDestruction();

  _pCommandWithFocus=NULL;
  
  return(0);
}

// Main
// ----

CAADlgApplication sx;
