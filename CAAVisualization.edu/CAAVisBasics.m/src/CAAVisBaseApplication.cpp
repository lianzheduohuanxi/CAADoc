// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAVisBaseApplication.h"
#include "CAAVisBaseDocument.h"
#include "CAAVisBaseDefaultDocument.h"
#include "CAAVisBaseCGRDocument.h"
#include "CAAVisBaseVisuObjectDocument.h"
#include "CAAVisBaseBERender.h"
#include "CAAVisBaseView.h"
#include "CAAVisBaseApplicationFrame.h"
#include "CAAVisBaseInsertNotification.h"
#include "CAAVisBaseOpenNotification.h"
#include "CAAVisBaseRenderBENotification.h"
#include "CAAVisBaseViewpointDlg.h"
#include "CAAVisBaseNewViewpointNotification.h"
#include "CAAVisBaseManipulatorNotification.h"
#include "CAAVisBaseCreateObjectNotification.h"

//Visualization Framework
#include "CATViewer.h"
#include "CAT3DViewpoint.h"
#include "CAT3DBagRep.h"
#include "CAT3DLineRep.h"
#include "CAT3DManipulator.h"

//Mathematics Framework
#include "CATMathPointf.h"
#include "CATMathDirectionf.h" //For the manipulator part
#include "CATMathDirection.h"  //For the manipulator part
#include "CATMathAxis.h"       //For the manipulator part


//-------------------------------------------------------------------------------
  
CAAVisBaseApplication::CAAVisBaseApplication()
: CATInteractiveApplication(NULL, "VisBaseApplication")
{
  _pApplicationFrame = NULL;
  _pActiveDoc = NULL;
  _ActiveDocIndex = 0;
}

//-------------------------------------------------------------------------------

CAAVisBaseApplication::~CAAVisBaseApplication()
{
  _pApplicationFrame = NULL;
  _pActiveDoc = NULL;
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::BeginApplication()
{
  // Here is created the application frame, with
  // menu bars, and so on.
  CreateLayout();

  // Here is created a default document. This document
  // contains the representation of a torus.
  //The created document will be deleted if its corresponding
  //view is closed by the user (OnDeleteWindow method) or at the
  //exit.
  _pActiveDoc = new CAAVisBaseDefaultDocument(_pApplicationFrame, "Torus");
  _Documents.fastadd(_pActiveDoc);

  //updates the active document index
  _ActiveDocIndex = _Documents.length() - 1;

  //increases the list of potential bounding boxes
  _BoxesBags.fastadd(NULL);

  //increases the list of potential manipulators
  _Manipulators.fastadd(NULL);
  
  //Adds callbacks on the created document's window, in order to be
  //warned when it is activated, deleted..
  AddMDICallbacks(_pActiveDoc);
  
}

//-------------------------------------------------------------------------------

int CAAVisBaseApplication::EndApplication()
{
  return 0;
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::DestroyApplicationObjects()
{
  //Remove callbacks added on opened windows:
  int i;
  for(i=0; i<_Documents.length(); i++)
    {
      RemoveMDICallbacks(_Documents[i]);
    }

  //Destroy every bounding boxes corresponding to opened
  //documents
  for(i=_BoxesBags.length()-1; i>=0; i--)
    {
      CAT3DBagRep *pBagToDelete = _BoxesBags[i];
      if(NULL != pBagToDelete)
        {
          _BoxesBags -= pBagToDelete;
          // An object inherited from CATRep must never be
          // deallocated by "delete". One must called the
          // "Destroy" method on it.
          pBagToDelete->Destroy();
          pBagToDelete = NULL;
        }
    }

  //Destroy every _Manipulators corresponding to opened
  //documents
  for(i=_Manipulators.length()-1; i>=0; i--)
    {
      CAT3DManipulator *pManipulatorToDelete =  _Manipulators[i];
      if(NULL != pManipulatorToDelete)
        {
          // A manipulator msutn't be
          // deleted. One must called the
          // "Destroy" method on it.
          pManipulatorToDelete->Destroy();
          pManipulatorToDelete = NULL;
        }
    }

  
  //destroy every documents
  for(i=_Documents.length()-1; i>=0; i--)
    {
      CAAVisBaseDocument *pDocToDelete = _Documents[i];
      if(NULL != pDocToDelete)
        {
          _Documents -= pDocToDelete;
          pDocToDelete->Release();;
          pDocToDelete = NULL;
        }
    }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::CreateLayout()
{
  //Every dialog objects created here, are not explicitly
  //deleted in this class. Indeed, dialog objects deletion is
  //managed by an application global mechanism, and must never be
  //deleted by the class which allocated them.
  
  // The application frame is represented thanks to a
  // CAAVisBaseApplicationFrame.
  _pApplicationFrame = new CAAVisBaseApplicationFrame(this, "VisBaseSample",CATDlgWndFrameMDI);

  //The real frame construction is made by invoking its build method:
  _pApplicationFrame->Build();

  //Add callbacks on the layout's events:
  //
  //Insert event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseInsertNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::InsertCB,
                           NULL);

  //Open event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseOpenNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::OpenCB,
                           NULL);

  //Render Bounding elements event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseRenderBENotification",
                           (CATCommandMethod)& CAAVisBaseApplication::RenderBECB,
                           NULL);

  //Reframe event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseReframeNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::ReframeCB,
                           NULL);

  //Modify Viewpoint event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseModifyViewpointNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::ModifyViewpointCB,
                           NULL);

  //Exit event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseExitNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::ExitCB,
                           NULL);

  //Manipulator event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseManipulatorNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::ManipulatorCB,
                           NULL);
  
  //VisuObject creation event:
  AddAnalyseNotificationCB(_pApplicationFrame,
                           "CAAVisBaseCreateObjectNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::CreateObjectCB,
                           NULL);

  _pApplicationFrame->SetRectDimensions(0, 0, 800, 1000);
  _pApplicationFrame->SetVisibility(CATDlgShow);

 
  // Forces the display update.
  //UpdateDisplay();
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::AddMDICallbacks(CAAVisBaseDocument *iDocument)
{
  //Adds a callback on the iDocument's view, in order to
  //be warned when it is activated or deleted..
  if ( NULL != iDocument )
  {
     AddCallback(iDocument->GetView(),
                 CAAVisBaseView::WINDOW_ACTIVATED(),
                 (CATSubscriberMethod)& CAAVisBaseApplication::WindowMDICB,
                 (CATSubscriberData)CATINT32ToPtr(0));
   
     AddCallback(iDocument->GetView(),
                 CAAVisBaseView::WINDOW_DELETED(),
                 (CATSubscriberMethod)& CAAVisBaseApplication::WindowMDICB,
                 (CATSubscriberData)CATINT32ToPtr(1));
     
  }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::RemoveMDICallbacks(CAAVisBaseDocument *iDocument)
{
  //removes every subscription to iDocument.
  if(NULL != iDocument)
    RemoveSubscriberCallbacks(iDocument->GetView());
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::WindowMDICB(CATCallbackEvent   iEvent,
                                     void              *iPublisher,
                                     CATNotification   *iNotification,
                                     CATSubscriberData  iData,
                                     CATCallback        iCallbackId)
{
  //Here are treated every events linked with the Multi
  //Documents configuration
  
  int cmd = CATPtrToINT32(iData);
  
  CAAVisBaseView *pView = (CAAVisBaseView *)iPublisher;

  switch(cmd)
    {
    case 0: //event: window activated.
      if(NULL != iPublisher)
        OnWindowActivated((CAAVisBaseDocument *)pView->GetDocument());
      break;
    case 1: //event: window deleted.
      if(NULL != iPublisher)
        OnDeleteWindow((CAAVisBaseDocument *)pView->GetDocument());
      break;
    }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::OnWindowActivated(CAAVisBaseDocument *iDocument)
{
  //The activated window corresponds to the document
  //which has to become the active document.
  //So, we have to update our pointer to the active document and
  //the active document index.
  _ActiveDocIndex = _Documents.index(iDocument);
  _pActiveDoc = _Documents[_ActiveDocIndex];

  //We also must warn the frame so it can do the
  //necessary updates on its side:
  //The active document index is passed as an argument.
  _pApplicationFrame->OnWindowActivated(_ActiveDocIndex);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::OnDeleteWindow(CAAVisBaseDocument *iDocument)
{
  if ( NULL != iDocument )
{
  //A window is deleted. That means that a document is closed.
  //We have to update our documents list, our pointer
  //to the active document. 
  //We also must delete the document, the associated bounding boxes if needed.

  //Let's get the index of the document which is going to be deleted:
  int index = _Documents.index(iDocument);

  //Remove subscription from the document soon deleted:
  RemoveMDICallbacks(iDocument);
  
  //deletes the associated bounding boxes:
  CAT3DBagRep * pBoxesToDelete = _BoxesBags[index];
  _BoxesBags -= pBoxesToDelete;

  if(NULL != pBoxesToDelete)
    {
      // An object inherited from CATRep must never be
      // deallocated by "delete". One must called the
      // "Destroy" method on it.
      pBoxesToDelete->Destroy();
      pBoxesToDelete = NULL;
    }

  //Destroy the associated manipulator
  CAT3DManipulator *pManipulatorToDelete = _Manipulators[index];
  _Manipulators -= pManipulatorToDelete;

  if(NULL != pManipulatorToDelete)
    {
      // A manipulator msutn't be
      // deleted. One must called the
      // "Destroy" method on it.
      pManipulatorToDelete->Destroy();
      pManipulatorToDelete = NULL;
    }
  
  //Removes the document from the list.
  _Documents -= iDocument;


  //If no more doucment is opened:
  if(0 == _Documents.length())
    {
      _pActiveDoc = NULL;
    }
  else
    {
      _pActiveDoc = _Documents[0];
    }
  _ActiveDocIndex = 0;

  //deletion of the document
  iDocument->Release();
  iDocument = NULL;

  //Warn the application frame so it can do its own updatings:
  //The index of the deleted document is passed as an argument.
  _pApplicationFrame->OnDeleteWindow(index);
}
}


//-------------------------------------------------------------------------------

void CAAVisBaseApplication::OpenCGR(const char *iFileName)
{
  if(NULL == iFileName)
    return;

  //Here is instanciated a new document containing
  //the graphical representation of the CGR file indicated.
  //The created document will be deleted if its corresponding
  //view is closed by the user (OnDeleteWindow method) or at the
  //exit.
  _pActiveDoc = new CAAVisBaseCGRDocument(iFileName, _pApplicationFrame, iFileName);
  
  //Adding of the new document to the list
  //of opened documents.
  _Documents.fastadd(_pActiveDoc);

  //updates the active document index
  _ActiveDocIndex = _Documents.length() - 1;

  //increases the list of bounding boxes
  _BoxesBags.fastadd(NULL);

  //increases the list of manipulators
  _Manipulators.fastadd(NULL);
  
  //Adds callbacks on the created document's window, in order to be
  //warned when it is activated, deleted..
  AddMDICallbacks(_pActiveDoc);
}

void CAAVisBaseApplication::InsertModel(const char *iFileName)
{
  //If no document is opened, we can't insert any model.
  if(0 == _Documents.length())
    return;
  
  if( NULL != _pActiveDoc)
    _pActiveDoc->InsertModel(iFileName);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::RenderBE(int iItemChecked)
{
  //If no document is opened, we can't render bounding boxes.
  if(0 == _Documents.length())
    return;
  
  CAT3DBagRep * pBoxesBag = NULL;

  CAAVisBaseView *pDocView = _pActiveDoc->GetView();
  if(NULL == pDocView)
    return;
  
  CATViewer *pViewer = pDocView->GetViewer();
  if(NULL == pViewer)
    return;

      
  //If the "BE Render" check item has been checked on, we have to
  //render the bounding boxes.
  if(1 == iItemChecked)
    {
      //If boxes are already rendered, return.
      if(NULL != _BoxesBags[_ActiveDocIndex])
        return;

      //Creation of a new Bounding Boxes render:
      //The render will be deleted at the end of the scope

      //Instanciation of our render:
      const CATSupport &pSupport = pViewer->GetSupport();
      CAAVisBaseBERender pBERender(pSupport);

      //We want our rendering to be done on the main 3D viewpoint:
      list<CATViewpoint> viewpoints;
      viewpoints.fastadd( pViewer->GetMain3DViewpoint());

      //The real rendering is done through the call to Draw:
      pBERender.Draw(viewpoints, 1, 0);

      //Let's get the number of calculated bounding boxes:
      int nBoxes = pBERender.GetNumberOfBoxes();

      //If no box was claculated, we must
      //delete the render and exit the method:
      if(0 == nBoxes)
        return;
   

      //Let's get the root bag of our main 3D viewpoint
      CAT3DBagRep * root = (CAT3DBagRep *)(pViewer->GetMain3DViewpoint().GetBag());
      if ( NULL == root) 
      { 
        return;
      }

      //Creation of a bag to store our boxes representations:
      //This bag will be destroyed at the deletion of the
      //corresponding window, i.e in the OnDeleteWindow method
      //or on exit, as child of the window main bag.
      pBoxesBag = new CAT3DBagRep;

      //This bag is added to the main 3D viewpoint bag. So, we'll see
      //our boxes in the scene.
      root->AddChild(*pBoxesBag);

      //We're using CAT3DLineRep to display our bounding boxes.
      //the double pointer, lines will be deleted at the end
      //of the scope.
      CAT3DLineRep ** lines = new CAT3DLineRep*[12];

      //Retrieving of the bounding boxes from the render:
      int i;
      for(i=0; i<nBoxes; i++)
        {
          float currentBox[6];
          //Here is done the retrieving of the i-th bounding box:
          pBERender.GetBox(i, currentBox);

          //Our render gives the box as its extreme points.
          //From these two points coordinates, we can retrieve
          //every box vertices coordinates.
          //
          //Each line is a 6 floats array: XYZ coordinates
          //for the two extreme vertices.
          float currentLine[6];

          //Each box is a set of 12 lines:
          //

          
          currentLine[0] = currentBox[0];
          currentLine[1] = currentBox[1];
          currentLine[2] = currentBox[2];
          currentLine[3] = currentBox[0];
          currentLine[4] = currentBox[4];
          currentLine[5] = currentBox[2];
          //First line
          lines[0] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[0];
          currentLine[1] = currentBox[1];
          currentLine[2] = currentBox[2];
          currentLine[3] = currentBox[3];
          currentLine[4] = currentBox[1];
          currentLine[5] = currentBox[2];
          //Second line
          lines[1] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[0];
          currentLine[1] = currentBox[1];
          currentLine[2] = currentBox[2];
          currentLine[3] = currentBox[0];
          currentLine[4] = currentBox[1];
          currentLine[5] = currentBox[5];
          //Third line
          lines[2] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[0];
          currentLine[1] = currentBox[1];
          currentLine[2] = currentBox[5];
          currentLine[3] = currentBox[0];
          currentLine[4] = currentBox[4];
          currentLine[5] = currentBox[5];
          //Fourth line
          lines[3] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[0];
          currentLine[1] = currentBox[1];
          currentLine[2] = currentBox[5];
          currentLine[3] = currentBox[3];
          currentLine[4] = currentBox[1];
          currentLine[5] = currentBox[5];
          //Fifth line
          lines[4] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[3];
          currentLine[1] = currentBox[1];
          currentLine[2] = currentBox[5];
          currentLine[3] = currentBox[3];
          currentLine[4] = currentBox[4];
          currentLine[5] = currentBox[5];
          //Sixth line
          lines[5] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[3];
          currentLine[1] = currentBox[4];
          currentLine[2] = currentBox[5];
          currentLine[3] = currentBox[0];
          currentLine[4] = currentBox[4];
          currentLine[5] = currentBox[5];
          //Seventh line
          lines[6] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[3];
          currentLine[1] = currentBox[4];
          currentLine[2] = currentBox[5];
          currentLine[3] = currentBox[3];
          currentLine[4] = currentBox[4];
          currentLine[5] = currentBox[2];
          //Heighth line
          lines[7] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[3];
          currentLine[1] = currentBox[4];
          currentLine[2] = currentBox[2];
          currentLine[3] = currentBox[3];
          currentLine[4] = currentBox[1];
          currentLine[5] = currentBox[2];
          //Ninth line
          lines[8] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[3];
          currentLine[1] = currentBox[4];
          currentLine[2] = currentBox[2];
          currentLine[3] = currentBox[0];
          currentLine[4] = currentBox[4];
          currentLine[5] = currentBox[2];
          //Tenth line
          lines[9] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[3];
          currentLine[1] = currentBox[1];
          currentLine[2] = currentBox[5];
          currentLine[3] = currentBox[3];
          currentLine[4] = currentBox[1];
          currentLine[5] = currentBox[2];
          //Eleventh line
          lines[10] = new CAT3DLineRep(currentLine);

          currentLine[0] = currentBox[0];
          currentLine[1] = currentBox[4];
          currentLine[2] = currentBox[5];
          currentLine[3] = currentBox[0];
          currentLine[4] = currentBox[4];
          currentLine[5] = currentBox[2];
          //Twelfth line
          lines[11] = new CAT3DLineRep(currentLine);

          int j;
          for(j=0; j<12; j++)
            {
              //We want our lines not to use the Z-buffer.
              lines[j]->GetGraphicAttributeSet().SetType(1);
              //Adding of the lines to the lines bag.
              //The lines will be destroyed in the
              //same time as children of pBoxesBag.
              pBoxesBag->AddChild(*(lines[j]));
            }
        }

      //We can now delete the lines double pointer
      delete [] lines;
      lines = NULL ;

      //We maintain a list of bounding boxes bags, associated to
      //the opened documents list.
      //Each opened document has an associated bounding boxes bag in
      //which boxes can eventually be stored.
      _BoxesBags += pBoxesBag;
      _BoxesBags.swap(_ActiveDocIndex, _BoxesBags.length()-1);
      _BoxesBags -= _BoxesBags[_BoxesBags.length()-1];
  }
  //The "BE Render" check item has been unchecked:
  else
  {
      if(NULL == _BoxesBags[_ActiveDocIndex])
      {
        return;
      }
      //If we have a bounding boxes graphical representation, we delete it:
      //
      //We retrive the main 3D viewpoint main bag:
      CAT3DBagRep * root = (CAT3DBagRep *)(pViewer->GetMain3DViewpoint().GetBag());
      if ( NULL == root) 
         return ;

      //We kept track of our bounding boxes bags, so we can remove
      //the bounding boxes representation from the retrived bag:
      //(here, the representation is removed from the viewpoint but
      //NOT deleted)
      root->RemoveChild(*(_BoxesBags[_ActiveDocIndex]));

      //Update of our bounding boxes list
      CAT3DBagRep * bagToDelete = _BoxesBags[_ActiveDocIndex];
      _BoxesBags.fastadd(NULL);
      _BoxesBags.swap(_ActiveDocIndex, _BoxesBags.length()-1);
      _BoxesBags -= _BoxesBags[_BoxesBags.length()-1];

      //Bounding boxes deletion:
      //
      // An object inherited from CATRep must never be
      // deallocated by "delete". One must called the
      // "Destroy" method on it.
      if ( NULL != bagToDelete )
      {
         bagToDelete->Destroy();
         bagToDelete = NULL;
      }
  }
  //Forces the redrawing of the scene.
  pViewer->Draw();
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::Reframe()
{
  if(0 == _Documents.length())
    return;

  CAAVisBaseView *pDocView = _pActiveDoc->GetView();
  if(NULL == pDocView)
    return;
  
  CATViewer *pViewer = pDocView->GetViewer();
  if(NULL == pViewer)
    return;
  
  
  //Retrieving of the main 3D viewpoint:
  CAT3DViewpoint &vp3d =pViewer->GetMain3DViewpoint();

  //Retrieving of the window dimensions:
  float windowWidth(0), windowHeight(0);
  pViewer->GetGraphicSize(&windowWidth, &windowHeight);

  //If the window is not square, we can distinguish two different
  //angles in our view pyramid.
  //Usually we work with the teta angle, but, if our window height is greater
  //than our window width, that means that we must take care of the smallest
  //dimension (i.e the window width), and so, work with the other angle.
  
  float ratio;
  if(windowHeight > windowWidth) //that means that we must take care
                                 //of the other angle of the frustum
                                 //which can be approximated by teta*(windowWidth/windowHeight)
    {
      ratio = windowHeight/windowWidth;
    }
  else
    {
      ratio = 1.0f;
    }

  //To reframe the view, we also need the representation bounding volume.
  CAT3DBagRep * rootBag = (CAT3DBagRep *)(vp3d.GetBag());

  if ( NULL != rootBag )
  {

     //If the bounding element is invalid, let's force its calculation:
     if(rootBag->IsInvalid())
       rootBag->ComputeBoundingElement(1);

     //Retrieving of the bounding element:
     const CAT3DBoundingSphere &bs3d = rootBag->GetBoundingElement();

     //Retrieving of the bounding element radius:
     float radius = bs3d.GetRadius();

     if(radius == 0.f)
       radius = bs3d.GetRadiusMM(); //Returns the radius for fixed objects
                                 //on which zoom has no effect.

     //We also need to know the opening angle of our frustum to calculate
     //the distance to the object the eye must be to view it completely.
     //This angle is the "teta" we dealt with just above:
     float angle = vp3d.GetAngle();
  
     //Some tools are available for conversions:
     angle = (float)CATDegreeToRadian*angle;

     //The focus is the eye-target distance.
     float focus = 1.05f * (radius/tan(angle)) * ratio;

     //Calculation of the new eye position:
     CATMathPointf eyePosition = bs3d.GetCenter() - vp3d.GetSightDirection()*focus;

     //Setting of the viewpoint's changed parameters:
     // - Focus
     // - Eye position
     vp3d.SetFocus(focus);
     vp3d.SetOrigin(eyePosition);
  }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::ModifyViewpoint()
{
  if(0 == _Documents.length())
    return;

  //Every dialog objects created here, are not explicitly
  //deleted in this class. Indeed, dialog objects deletion is
  //managed by an application global mechanism, and must never be
  //deleted by the class which allocated them.
  CAAVisBaseViewpointDlg * pViewpointDlg = new CAAVisBaseViewpointDlg(_pApplicationFrame,
                                                                      "ViewpointParameters");

  //Building of every dialog objects of the dialog box.
  pViewpointDlg->Build();

  //Initializations
  //---------------
  CAAVisBaseView *pDocView = _pActiveDoc->GetView();
  if(NULL == pDocView)
    return;
  
  CATViewer *pViewer = pDocView->GetViewer();
  if(NULL == pViewer)
    return;
  
  
  //Retrieving of the main 3D viewpoint:
  CAT3DViewpoint &vp3d =pViewer->GetMain3DViewpoint();

  const CATMathPointf &origin = vp3d.GetOrigin();
  const CATMathDirectionf &sightDirection = vp3d.GetSightDirection();

  //Here are initialized the dialog box fields:
  pViewpointDlg->Init(origin,
                      sightDirection,
                      vp3d.GetProjectionType(),
                      vp3d.GetFocusDistance(),
                      vp3d.GetAngle());
  
  //Adding callback:
  //Each time, a field is modifyed, we're called back
  //in the NewViewpointCB method.
  //This is this method which is in charge of transmitting
  //the new parameters to the viewpoint.
  AddAnalyseNotificationCB(pViewpointDlg,
                           "CAAVisBaseNewViewpointNotification",
                           (CATCommandMethod)& CAAVisBaseApplication::NewViewpointCB,
                           NULL);

  //Makes the dialog box visible:
  pViewpointDlg->SetVisibility(CATDlgShow);
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::AddManipulator(int iItemChecked)
{
  //If no document is opened, we can't Add nor Remove a manipulator.
  if(0 == _Documents.length())
    return;

  CAAVisBaseView *pDocView = _pActiveDoc->GetView();
  if(NULL == pDocView)
    return;
  
  CATViewer *pViewer = pDocView->GetViewer();
  if(NULL == pViewer)
    return;
  

  if(1 == iItemChecked) //We must add a manipulator
    {
      //Retrieving of the model thanks to the document:
      //This is the bag on which we're going to add a manipulator:
      CAT3DBagRep *pRoot = _pActiveDoc->GetModel();
      
      //Now, we're going to instanciate a 3D manipulator attached to this bag:
      //We want our rep to be moved along a direction
      CAT3DManipulator *pManipulator = new CAT3DManipulator(this,
                                                            "Manipulator",
                                                            pRoot,
                                                            CAT3DManipulator::DirectionTranslation);
      
      //We must give an initial position to our manipulator.
      //This position is not necessary the same than the bag position.
      //Indeed, the data retrieved when our manipulator is moved is an offset
      //in respect to this initial position.
      //
      //Here, the initial position is set to origin.
      CATMathAxis initialPosition;
      pManipulator->SetPosition(initialPosition);
      
      //Set the transformation characteristics:
      //Here, we have a direction translation, so we're going to use
      //the SetTranslationDirection method:
      //
      //We want our object to be translated along the
      //y direction.
      CATMathDirection yDirection(0, 1, 0);
      
      pManipulator->SetTranslationDirection(yDirection); 
      
      //Add a callback to be informed about the manipulation:
      AddAnalyseNotificationCB(pManipulator, CATManipulator::GetCATManipulate(),
                               (CATCommandMethod)& CAAVisBaseApplication::OnManipulateCB, NULL);

      //We maintain a list of manipulators, associated to
      //the opened documents list.
      //Each opened document has an associated pointer on a manipulator
      //which can be fill in if needed.
      _Manipulators += pManipulator;
      _Manipulators.swap(_ActiveDocIndex, _Manipulators.length()-1);
      _Manipulators -= _Manipulators[_Manipulators.length()-1];
    }
  else  //We must remove the manipulator
    {
      //We kept track of the added manipulators
      
      //Update of our bounding boxes list
      CAT3DManipulator *pManipulatorToDelete = _Manipulators[_ActiveDocIndex];
      
      _Manipulators.fastadd(NULL);
      _Manipulators.swap(_ActiveDocIndex, _Manipulators.length()-1);
      _Manipulators -= _Manipulators[_Manipulators.length()-1];

      //Destroy the manipulator
      if ( NULL != pManipulatorToDelete ) pManipulatorToDelete->Destroy();
      pManipulatorToDelete = NULL ;
    }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::InsertCB(CATCommand *iPublisher,
                                     CATNotification *iNotification,
                                     CATCommandClientData  iData)
{
  CAAVisBaseInsertNotification *pNotification = (CAAVisBaseInsertNotification *)iNotification;

  if(NULL != pNotification)
  {
     char *pTmpString = (char *)pNotification->GetFileName();
     char *pFileName = (char *)malloc((strlen(pTmpString)+1) * sizeof(char));
     memset(pFileName, 0, strlen(pTmpString)+1);
     strcpy(pFileName, pTmpString);

     //Insertion of the CGR in the current document:
     InsertModel(pFileName);

     free(pFileName);
     pFileName = NULL ;
  }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::OpenCB(CATCommand *iPublisher,
                                   CATNotification *iNotification,
                                   CATCommandClientData  iData)
{
  CAAVisBaseOpenNotification *pNotification = (CAAVisBaseOpenNotification *)iNotification;

  if(NULL != pNotification)
  {
     char *pTmpString = (char *)pNotification->GetFileName();
     char *pFileName = (char *)malloc((strlen(pTmpString)+1) * sizeof(char));
     memset(pFileName, 0, strlen(pTmpString)+1);
     strcpy(pFileName, pTmpString);

     //opening of a new CGR document
     OpenCGR(pFileName);
  
     free(pFileName);
     pFileName = NULL ;
  }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::RenderBECB(CATCommand *iPublisher,
                                     CATNotification *iNotification,
                                     CATCommandClientData  iData)
{
  CAAVisBaseRenderBENotification *pNotification = NULL ;
  pNotification = (CAAVisBaseRenderBENotification *)iNotification;

  if(NULL != pNotification)
  {
     //Rendering of the bounding boxes:
     RenderBE(pNotification->GetState());
  }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::ReframeCB(CATCommand *iPublisher,
                                      CATNotification *iNotification,
                                      CATCommandClientData  iData)
{
  Reframe();
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::ModifyViewpointCB(CATCommand *iPublisher,
                                              CATNotification *iNotification,
                                              CATCommandClientData  iData)
{
  ModifyViewpoint();
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::ExitCB(CATCommand *iPublisher,
                                   CATNotification *iNotification,
                                   CATCommandClientData  iData)
{
  // Cleaning the application
  DestroyApplicationObjects();

  //Ending the application:
  Destroy();
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::NewViewpointCB(CATCommand *iPublisher,
                                           CATNotification *iNotification,
                                           CATCommandClientData  iData)
{
  CAAVisBaseNewViewpointNotification * pNotif = NULL ;
  pNotif = (CAAVisBaseNewViewpointNotification *)iNotification;

  if ( NULL != pNotif )
  {
     CAAVisBaseView *pDocView = _pActiveDoc->GetView();
     if( NULL != pDocView)
     {
       
        CATViewer *pViewer = pDocView->GetViewer();
     
        if(NULL != pViewer)
        {
       
           //Retrieving of the main 3D viewpoint:
           CAT3DViewpoint &vp3d =pViewer->GetMain3DViewpoint();
   
           //Setting of the new parameters:
           //
           //Origin
           vp3d.SetOrigin(*(pNotif->GetOrigin()));
   
           //Sight
           vp3d.SetSightDirection(*(pNotif->GetSightDirection()));
   
           //Projection type
           vp3d.SetProjectionType(pNotif->GetProjectionType());
   
           //Focus distance
           vp3d.SetFocus(pNotif->GetFocusDistance());
   
           //Angle
           vp3d.SetAngle(pNotif->GetAngle());
        }
     }
  }

}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::ManipulatorCB(CATCommand *iPublisher,
                                          CATNotification *iNotification,
                                          CATCommandClientData  iData)
{
  CAAVisBaseManipulatorNotification *pNotification = NULL ;
  pNotification = (CAAVisBaseManipulatorNotification *)iNotification;

  if(NULL != pNotification)
  {
     AddManipulator(pNotification->GetState());
  }
}

//-------------------------------------------------------------------------------

void CAAVisBaseApplication::OnManipulateCB(CATCommand *iPublisher,
                                           CATNotification *iNotification,
                                           CATCommandClientData  iData)
{
  //We want our representation to follow the Manipulator
  //positions, constrained to the defined axis.

  CAAVisBaseView *pDocView = _pActiveDoc->GetView();

  if((NULL != pDocView) && ( NULL != iPublisher) )
  {
      
     CATViewer *pViewer = pDocView->GetViewer();

     if(NULL != pViewer)
     {
   
        //We're retrieving the notification containing the transformation:
        CATTransformationNotification *pTransfoNotif = 
             ((CATTransformationNotification *) iPublisher->SendCommandSpecificObject(
                         CATTransformationNotification::ClassName(), iNotification));

        if ( NULL != pTransfoNotif)
        {

           //We're retrieving the transformation from this notification:
           const CATMathTransformation &pTransformation = pTransfoNotif->GetTransformation();

           pTransfoNotif->Release();
           pTransfoNotif = NULL ;

           //We want to move our representation thanks to the retrieved transformation.
           //To move our Bag Rep, we can multiply its transformation matrix by the
           //transformation matrix corresponding to the retrieved transformation.
           //
           //The transformation we authorized for our manipulator is a tranlation. We first
           //have to retrieve the tranlation vector:
           CATMathVector translationVector;
           pTransformation.GetVector(translationVector);

           //We're building a 4x4 matrix (visualization matrix) from this
           //translation vector.
           CAT4x4Matrix visuMatrix(translationVector);

           //We can now multiply this matrix by the Bag Rep matrix:
           //Retrieving of the model thanks to the document:
           CAT3DBagRep *pRoot = _pActiveDoc->GetModel();

           if(NULL != pRoot)
           {
              //Gets the initial matrix:
              CAT4x4Matrix *pInitialMatrix = NULL ;
              if(NULL == pRoot->GetMatrix())
              {
                 pInitialMatrix = new CAT4x4Matrix;
              }
              else
              {
                 pInitialMatrix = new CAT4x4Matrix(*(pRoot->GetMatrix()));
              }
  
              //Multiply the two matrices:
              *pInitialMatrix *= visuMatrix;
              //Sets the new matrix
               pRoot->SetMatrix(*pInitialMatrix);

               pInitialMatrix->Release() ;
               pInitialMatrix = NULL ;

               //Re-initialize the Manipulator position
               CAT3DManipulator *pManipulator = (CAT3DManipulator *)iPublisher;
               CATMathAxis origin;
               pManipulator->SetPosition(origin);
   
               //Forces the redrawing of the scene.
               pViewer->Draw();
            }
         }
      }
   }
}

void CAAVisBaseApplication::CreateObjectCB(CATCommand *iPublisher, CATNotification *iNotification, CATCommandClientData  iData)
{
   CAAVisBaseCreateObjectNotification * createNotif = (CAAVisBaseCreateObjectNotification *)iNotification;
   if(!createNotif) return;

  //Here is instanciated a new document containing
  //the graphical representation of the CGR file indicated.
  //The created document will be deleted if its corresponding
  //view is closed by the user (OnDeleteWindow method) or at the
  //exit.
  _pActiveDoc = new CAAVisBaseVisuObjectDocument(createNotif->GetObjectType(), _pApplicationFrame, "VisuObject");
  
  //Adding of the new document to the list
  //of opened documents.
  _Documents.fastadd(_pActiveDoc);

  //updates the active document index
  _ActiveDocIndex = _Documents.length() - 1;

  //increases the list of bounding boxes
  _BoxesBags.fastadd(NULL);

  //increases the list of manipulators
  _Manipulators.fastadd(NULL);
  
  //Adds callbacks on the created document's window, in order to be
  //warned when it is activated, deleted..
  AddMDICallbacks(_pActiveDoc);
}

//-------------------------------------------------------------------------------
// Ignition

//application class instance creation
CAAVisBaseApplication appli;
