//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
//=============================================================================
// Local Framework
#include "CAAGemBrowserDocument.h"
#include "CAAGemRep.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    // For the current application to destroy
#include "CATDlgInclude.h"                // Dialog objects

// Visualization Framework
#include "CATNavigation3DViewer.h"        // the window
#include "CAT3DRep.h"                     // the visualisation rep
#include "CAT3DBagRep.h"                  // the visualisation rep
#include "CAT3DBoundingSphere.h"          // bounding sphere

// GeometricObjects Framework
#include "CATGeoFactory.h"                // geometry factory
#include "CATCGMContainerMngt.h"          // geometry factory management
#include "CATGeometry.h"                  // geometric object

// C++ Standard library
#include "iostream.h"
#include "fstream.h"
#include "CATErrorMacros.h"
#include "CATCommand.h"
//--------------------------------------------------------------------------------------
CAAGemBrowserDocument::CAAGemBrowserDocument(CATInteractiveApplication * iParentCommand)                              
                      : CATDlgDocument(iParentCommand, "CAAGemBrowserRepWindowId"),
	                    _pApplication(iParentCommand),_pTheModelToDisplay(NULL),_p3DViewer(NULL),
                        _piGeomFactory(NULL),_pFileSelector(NULL)
{
  cout << "CAAGemBrowserDocument::CAAGemBrowserDocument" << endl;

  // Do not construct any Dialog object child in the constructor 
  // Use the Build Method to do this.
}

//--------------------------------------------------------------------------------------

CAAGemBrowserDocument::~CAAGemBrowserDocument()
{ 
  cout << "CAAGemBrowserDocument::~CAAGemBrowserDocument" << endl; 

  if ( NULL != _pTheModelToDisplay )
  {
     // The bag and its children are deleted
     _pTheModelToDisplay->Destroy();
     _pTheModelToDisplay = NULL ;
  }
  
  // All Dialog Object that are children of this window are
  // automatically deleted ( The _p3DViewer included )
  _p3DViewer    = NULL ;
  _pApplication = NULL ;
   if (NULL!=_piGeomFactory) 
    {
      CATCloseCGMContainer(_piGeomFactory);
      _piGeomFactory=NULL;
    }
    if (NULL!=_pFileSelector) 
    {
      _pFileSelector->RequestDelayedDestruction();
      _pFileSelector=NULL;
    }
}

//--------------------------------------------------------------------------------------

void CAAGemBrowserDocument::Build()
{
  cout << "CAAGemBrowserDocument::Build" << endl;

  CreateMenuBar();

  CreateViewer();
  
}
//--------------------------------------------------------------------------------------

void CAAGemBrowserDocument::CreateMenuBar()
{
   CATDlgBarMenu* pMainMenu = NULL;
   pMainMenu = new CATDlgBarMenu(this,"MainMenu");

   CATDlgSubMenu* pFileMenu = NULL;
   pFileMenu = new CATDlgSubMenu(pMainMenu,"File");

   CATDlgPushItem* pOpenItem = NULL;
   pOpenItem = new CATDlgPushItem(pFileMenu,"Open");
   AddAnalyseNotificationCB(pOpenItem,
                            pOpenItem->GetMenuIActivateNotification(), 
                            (CATCommandMethod)&CAAGemBrowserDocument::Open, 
                            NULL); 
    
   CATDlgPushItem* pCloseItem=NULL;
   pCloseItem = new CATDlgPushItem(pFileMenu,"Close");
   AddAnalyseNotificationCB(pCloseItem,
                            pCloseItem->GetMenuIActivateNotification(), 
                            (CATCommandMethod)&CAAGemBrowserDocument::Close, 
                            NULL);

   CATDlgPushItem * pExitItem =NULL;  
   pExitItem = new CATDlgPushItem(pFileMenu,"Exit");
   AddAnalyseNotificationCB(pExitItem,
                            pExitItem->GetMenuIActivateNotification(), 
                            (CATCommandMethod)&CAAGemBrowserDocument::Exit, 
                            NULL);
   AddAnalyseNotificationCB(this,
                            GetWindCloseNotification(), 
                            (CATCommandMethod)&CAAGemBrowserDocument::Exit, 
                            NULL);
}

//--------------------------------------------------------------------------------------
void CAAGemBrowserDocument::CreateViewer()
{

  // The window contains a 3DViewer which allows the user to do 3D Manipulations 
  _p3DViewer = new CATNavigation3DViewer( this, "3DViewerId",CATDlgFraNoTitle, 800, 450);

  // Changes the color of the background
  _p3DViewer->SetBackgroundColor(0.2f,0.2f,0.6f);

  // The Viewer is attached to the 4 sides of the Window.
  Attach4Sides( _p3DViewer);

}
//--------------------------------------------------------------------------------------                 
void CAAGemBrowserDocument::CreateModelRepresentation()
{
  // The Top of the graphic representation tree
    _pTheModelToDisplay = new CAT3DBagRep();

  // Scans the geometry factory to retrieve the objects to visualize
  if (NULL != _piGeomFactory) 
  {
    float sag = 0.1f;
    CAAGemRep browser(_piGeomFactory,sag);
    CATGeometry* piCurrent = NULL ;
    while ( piCurrent = _piGeomFactory->Next ( piCurrent ) )
    {  
      CAT3DRep * pRep =NULL;
      browser.CreateRep(piCurrent, pRep);
      if ( NULL != pRep )
      {
        _pTheModelToDisplay->AddChild(*pRep);
      }
    }
  } 
}

//----------------------------------------------------------------------- 
// VisualizeModel
//-----------------------------------------------------------------------                
void CAAGemBrowserDocument::VisualizeModel()
{
   if ( (NULL != _p3DViewer) && ( NULL != _pTheModelToDisplay) )
   {    
      // Instruction to do once 
      _p3DViewer->AddRep((CAT3DRep*)_pTheModelToDisplay);

      // Reframe on the current bouding sphere
      const CAT3DBoundingSphere boundingSphere = _pTheModelToDisplay->GetBoundingElement(); 
      _p3DViewer->ReframeOn(boundingSphere);

      // Instruction to do at each  representation modification 
      _p3DViewer->Draw();
   }

}

//-----------------------------------------------------------------------
// Open
//-----------------------------------------------------------------------
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
//-----------------------------------------------------------------------
// OpenOK
// Retrieves the file name
// Closes the preceeding factory
// Opens the new one
// Visualizes
//-----------------------------------------------------------------------

void CAAGemBrowserDocument::OpenOK(CATCommand           * iSendingCommand, 
                                   CATNotification      * iSentNotification, 
                                   CATCommandClientData   iUsefulData)
{
  // Retrieves the file name	
  CATUnicodeString fileName;
  _pFileSelector->GetSelection(fileName);
  _pFileSelector->RequestDelayedDestruction();
  _pFileSelector=NULL;
  
  // Closes the precedeeding factory, if any
  Close(iSendingCommand,  iSentNotification,  iUsefulData);

  // Loads the geometry factory
#ifdef _WINDOWS_SOURCE
  ifstream filetoread(fileName.CastToCharPtr(), ios::binary ) ;
#else
  ifstream filetoread(fileName,ios::in,filebuf::openprot) ;
#endif
  CATTry
  {
    _piGeomFactory=::CATLoadCGMContainer(filetoread);
    filetoread.close();
  }
  CATCatch(CATError,error)
  {
    cout << (error->GetNLSMessage()).ConvertToChar() << endl; 
    Flush(error);
  }
  CATEndTry

  // Creates the graphic representation
  CreateModelRepresentation();

  // Draws
  VisualizeModel();  
} 

//-----------------------------------------------------------------------
// Cancel
//-----------------------------------------------------------------------
void CAAGemBrowserDocument::Cancel(CATCommand           * iSendingCommand, 
                                   CATNotification      * iSentNotification, 
                                   CATCommandClientData   iUsefulData)
{
	if (NULL!=_pFileSelector)
    {
     _pFileSelector->RequestDelayedDestruction();
	 _pFileSelector = NULL;
    }
}

//-----------------------------------------------------------------------
// Close
//-----------------------------------------------------------------------
void CAAGemBrowserDocument::Close(CATCommand           * iSendingCommand, 
                                  CATNotification      * iSentNotification, 
                                  CATCommandClientData   iUsefulData)
{
	
    if (NULL!=_piGeomFactory) 
    {
      CATCloseCGMContainer(_piGeomFactory);
      _piGeomFactory =NULL;
    }
    if (NULL != _pTheModelToDisplay)
    {
      _p3DViewer->RemoveRep(_pTheModelToDisplay); 
      _pTheModelToDisplay->Destroy();
     _pTheModelToDisplay = NULL;
    }
    _p3DViewer->Draw();
}

//-----------------------------------------------------------------------
// Exit
//-----------------------------------------------------------------------
void CAAGemBrowserDocument::Exit(CATCommand           * iSendingCommand, 
                                 CATNotification      * iSentNotification, 
                                 CATCommandClientData   iUsefulData)
{	
    if (NULL!=_piGeomFactory) 
    {
      CATCloseCGMContainer(_piGeomFactory);
      _piGeomFactory=NULL;
    }
    if (NULL!=_pFileSelector) 
    {
      _pFileSelector->RequestDelayedDestruction();
      _pFileSelector=NULL;
    }

    if (NULL!=_pApplication) 
    {
      _pApplication->Destroy();
      _pApplication = NULL ;
    }
}


