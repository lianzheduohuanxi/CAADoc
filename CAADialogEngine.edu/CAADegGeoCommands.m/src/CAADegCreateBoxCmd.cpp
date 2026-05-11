// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAADegCreateBoxCmd.h" 
#include "CAADegBoxCreationChoiceNotification.h"

//DialogEngine Framework
#include "CATIndicationAgent.h"
#include "CATPathElementAgent.h"
#include "CATDialogTransition.h"

//Visualization Framework 
#include "CATPathElement.h"   
#include "CATCreate.h"   
#include "CATModify.h"      
#include "CATIModelEvents.h" 
#include "CATCSO.h"  

//CAASystem.edu Framework
#include "CAAISysAccess.h"       
#include "CAAISysPoint.h"  
#include "CAAISysLine.h"  
#include "CAAISysCuboid.h"       
#include "CAAISysGeomFactory.h"  
#include "CAAISysCollection.h"   

//ApplicationFrame Framework
#include "CATISO.h"
#include "CATFrmWindow.h"
#include "CATFrmLayout.h"
#include "CATFrm3DCamera.h"
#include "CATICamera.h"
#include "CATI3DCamera.h"
#include "CATFrmEditor.h"       
#include "CATAfrCheckHeaderAccessor.h"
#include "CATAfrCommandHeaderServices.h"

//ObjectModelerBase Framework
#include "CATIRedrawEvent.h"   //To visualize the new object in the spec tree 

// C++ Standard library
#include <iostream.h>

// Creates the CAADegCreateBoxPaletteHeader command header class
#include <CATCommandHeader.h>
MacDeclareHeader(CAADegCreateBoxPaletteHeader) ;

//----------------------------------------------------------------------------
// To declare that the class is a component main class which OM-derives 
// from CATStateCommand
//
CATImplementClass(CAADegCreateBoxCmd, Implementation,CATStateCommand, CATNull);

// To create the TIE Object
#include "TIE_CATIAfrCmdPaletteOptions.h"
TIE_CATIAfrCmdPaletteOptions(CAADegCreateBoxCmd);

// 
// To declare that CAADegCreateBoxCmd implements CATIAfrCmdPaletteOptions, insert 
// the following line in the interface dictionary:
//
//   CAADegCreateBoxCmd  CATIAfrCmdPaletteOptions libCAADegGeoCommands
//
//---------------------------------------------------------------------------

// Enables the instanciation of this command by its class name.  
// It will be used by the command header to launch the command. 
#include "CATCreateExternalObject.h"
CATCreateClass(CAADegCreateBoxCmd);

//----------------------LifeCycle's PART ----------------------------------
CAADegCreateBoxCmd::CAADegCreateBoxCmd():CATStateCommand("CreateBoxCmdId"),
                        _daPathElementCornerPoint(NULL),
						_daPathElementWidthPoint(NULL),
						_daIndicationDepthPoint(NULL),
						_daIndicationHeightPoint(NULL),
                        _pUIActiveObject(NULL), 
                        _pContainer(NULL),
						_pISO(NULL),
						_piCamera(NULL),
                        _CurrentBoxCreationTypeChoice (0),
                        _pTwoPointsCmdHdr(NULL),
                        _pThreePointsCmdHdr(NULL),
                        _pFourPointsCmdHdr(NULL),
                        _pOriginCheckHdr(NULL)
{
  cout << "CAADegCreateBoxCmd constructor" << endl ;

  //
  // 1- Keeps the root object 
  // 
  CATFrmEditor * pEditor   = GetEditor();
  if ( NULL != pEditor )
  {
	_pISO = pEditor->GetISO() ;
    CATPathElement path = pEditor->GetUIActiveObject();
    if ( path.GetSize() > 0  )
    {
      _pUIActiveObject = path[path.GetSize()-1];
      _pUIActiveObject->AddRef();
    }
  }

  //
  // 2- Retrieves the container which can create a box in the model 
  // 

  if ( NULL != _pUIActiveObject )
  {
    // Point will be created by this container and added inside
    CAAISysAccess * piSysAccess = NULL;                
    HRESULT rc = _pUIActiveObject->QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
    if (SUCCEEDED(rc))
    {
      piSysAccess->GetContainer(&_pContainer);
      piSysAccess->Release();
      piSysAccess=NULL;
    }
  }

  //
  // 3- Initiliazes temporaries elements 
  // 
  int i = 0;
  for ( ; i <3 ; i++ )
  {
     _apiTemporaryV[i]= NULL ;
  }

  
  for ( i=0 ; i <2 ; i++ )
  {
     _apiTemporaryP[i]= NULL ;
  }
  
  //
  // 4- Retrieves the viewpoint at the beginning of the command
  // 
  CATFrmLayout *pCurrentLayout = CATFrmLayout::GetCurrentLayout();
  if ( NULL != pCurrentLayout )
  {
    CATFrmWindow * pCurrentWindow = pCurrentLayout->GetCurrentWindow();
    if ( NULL != pCurrentWindow )
    {
      _piCamera = pCurrentWindow->GetCurrentCamera();
    }
  }
 
  //
  // 5- Creates or retrieves the check headers 
  //  
  
  // 5-1 Checks if the "CAADegTwoPointsBoxHdr" header exists ?
  CATCommandHeader * pCmd = NULL ;
  ::CATAfrGetCommandHeader("CAADegTwoPointsBoxHdr",pCmd);

  // 5-2 Creates the class to access the "CAADegTwoPointsBoxHdr" check header
  _pTwoPointsCmdHdr = new CATAfrCheckHeaderAccessor("CAADegTwoPointsBoxHdr");

  // 5-3 At the first CATAfrCheckHeaderAccessor call, the check header instance
  // will be created. Its parameters are set.
  if ( NULL == pCmd )
  {
      // The first check header is with the "check status" (TRUE)
      // by any notification is sent to modify the visualization (FALSE)
     _pTwoPointsCmdHdr->SetCheck(TRUE,FALSE);


     // The CAADegTwoPointsBoxHdr check header launches the CAADegTwoPointsBoxCheckHdr
     // command header when the state is checked. This last command header
     // launches the CAADegBoxPaletteChoiceCmd command defined in the CAADegGeoCommands.m 
     // module. 
     // 
     // The CAADegTwoPointsBoxCheckHdr is a command header without
     // graphic representation. No nls and rsc resources are necessary.
     // 
     new CAADegCreateBoxPaletteHeader
                          ("CAADegTwoPointsBoxCheckHdr",
                          "CAADegGeoCommands",
                          "CAADegBoxPaletteChoiceCmd", (void *) 1);

     // The CAADegTwoPointsBoxHdr check header launches the CAADegTwoPointsBoxUncheckHdr
     // command header when the state is unchecked. This last command header
     // launches the CAADegBoxPaletteChoiceCmd command defined in the CAADegGeoCommands.m 
     // module. 
     // 
     // The CAADegTwoPointsBoxUncheckHdr is a command header without
     // graphic representation. No nls and rsc resources are necessary.
     // 
     new CAADegCreateBoxPaletteHeader
                          ("CAADegTwoPointsBoxUncheckHdr",
                          "CAADegGeoCommands",
                          "CAADegBoxPaletteChoiceCmd", (void *) 1);
  
     _pTwoPointsCmdHdr->SetCheckCommand("CAADegTwoPointsBoxCheckHdr");
     _pTwoPointsCmdHdr->SetUncheckCommand("CAADegTwoPointsBoxUncheckHdr");

     // The nls resources (help, ...) and the rsc (icon) for the CAADegTwoPointsBoxHdr 
     // check header are defined in the CAADegCreateBoxPaletteHeader.CATNls
     // and CAADegCreateBoxPaletteHeader.CATRsc files. 
     //
     _pTwoPointsCmdHdr->SetResourceFile("CAADegCreateBoxPaletteHeader");

  }

  pCmd = NULL ;
  ::CATAfrGetCommandHeader("CAADegThreePointsBoxHdr",pCmd);

  _pThreePointsCmdHdr = new CATAfrCheckHeaderAccessor("CAADegThreePointsBoxHdr");
 
  if ( NULL == pCmd )
  {
     _pThreePointsCmdHdr->SetCheck(FALSE,FALSE);


     new CAADegCreateBoxPaletteHeader
                          ("CAADegThreePointsBoxCheckHdr",
                          "CAADegGeoCommands",
                          "CAADegBoxPaletteChoiceCmd", (void *) 2);

     new CAADegCreateBoxPaletteHeader
                          ("CAADegThreePointsBoxUncheckHdr",
                          "CAADegGeoCommands",
                          "CAADegBoxPaletteChoiceCmd", (void *) 2);

     _pThreePointsCmdHdr->SetCheckCommand("CAADegThreePointsBoxCheckHdr");
     _pThreePointsCmdHdr->SetUncheckCommand("CAADegThreePointsBoxUncheckHdr");

     _pThreePointsCmdHdr->SetResourceFile("CAADegCreateBoxPaletteHeader");

  }

  pCmd = NULL ;
  ::CATAfrGetCommandHeader("CAADegFourPointsBoxHdr",pCmd);
  
  _pFourPointsCmdHdr = new CATAfrCheckHeaderAccessor("CAADegFourPointsBoxHdr");

  if ( NULL == pCmd )
  {
     _pFourPointsCmdHdr->SetCheck(FALSE,FALSE);

  
     new CAADegCreateBoxPaletteHeader
                          ("CAADegFourPointsBoxCheckHdr",
                          "CAADegGeoCommands",
                          "CAADegBoxPaletteChoiceCmd", (void *) 3);

     new CAADegCreateBoxPaletteHeader
                          ("CAADegFourPointsBoxUncheckHdr",
                          "CAADegGeoCommands",
                          "CAADegBoxPaletteChoiceCmd", (void *) 3);

     _pFourPointsCmdHdr->SetCheckCommand("CAADegFourPointsBoxCheckHdr");
     _pFourPointsCmdHdr->SetUncheckCommand("CAADegFourPointsBoxUncheckHdr");

     _pFourPointsCmdHdr->SetResourceFile("CAADegCreateBoxPaletteHeader");
  }

  pCmd = NULL ;
  ::CATAfrGetCommandHeader("CAADegOriginBoxHdr",pCmd);

  _pOriginCheckHdr = new CATAfrCheckHeaderAccessor("CAADegOriginBoxHdr");

  if ( NULL == pCmd )
  {  
      // This check header is only a toggle, no command is necessary 
      // for the check/uncheck states.
      //
      _pOriginCheckHdr->SetResourceFile("CAADegCreateBoxCmd");
  }

  //
  // 6- Retrieves the current activated button 
  // 

  if ( (NULL != _pTwoPointsCmdHdr) && (_pTwoPointsCmdHdr->IsChecked() == 1) ) 
  {
      _CurrentBoxCreationTypeChoice = 1 ;
  }
  if ( (NULL != _pThreePointsCmdHdr) && (_pThreePointsCmdHdr->IsChecked() == 1) ) 
  {
      _CurrentBoxCreationTypeChoice = 2 ;
  }
  if ( (NULL != _pFourPointsCmdHdr) && (_pFourPointsCmdHdr->IsChecked() == 1) ) 
  {
      _CurrentBoxCreationTypeChoice = 3 ;
  }

}

//-----------------------------------------------------------------------

CAADegCreateBoxCmd::~CAADegCreateBoxCmd()
{
  cout << "CAADegCreateBoxCmd destructor" << endl ;

  if ( NULL != _daPathElementCornerPoint )
  {
	  _daPathElementCornerPoint->RequestDelayedDestruction();
	  _daPathElementCornerPoint= NULL ;
  }

  if ( NULL != _daPathElementWidthPoint )
  {
	  _daPathElementWidthPoint->RequestDelayedDestruction();
	  _daPathElementWidthPoint= NULL ;
  }

  if ( NULL != _daIndicationDepthPoint )
  {
	  _daIndicationDepthPoint->RequestDelayedDestruction();
	  _daIndicationDepthPoint= NULL ;
  }

  if ( NULL != _daIndicationHeightPoint )
  {
	  _daIndicationHeightPoint->RequestDelayedDestruction();
	  _daIndicationHeightPoint= NULL ;
  }

  if ( NULL != _pUIActiveObject )
  {
     _pUIActiveObject ->Release();
     _pUIActiveObject = NULL ;
  }

  if ( NULL != _pContainer ) 
  {
     _pContainer->Release(); 
     _pContainer = NULL ;
  }

   _pISO = NULL ;

  // Before this destructor, the Cancel method is called.
  //
  int i = 0;
  for ( ; i <3 ; i++ )
  {
     _apiTemporaryV[i]= NULL ;
  }

  
  for ( i=0 ; i <2 ; i++ )
  {
     _apiTemporaryP[i]= NULL ;
  }

  // The header commands are automatically deleted by the application
  // but not the access class instances.
  //
  if ( NULL != _pTwoPointsCmdHdr)
  {
     _pTwoPointsCmdHdr->Release();
     _pTwoPointsCmdHdr = NULL ;
  }
  if ( NULL != _pThreePointsCmdHdr)
  {
     _pThreePointsCmdHdr->Release();
     _pThreePointsCmdHdr = NULL ;
  }
  if ( NULL != _pFourPointsCmdHdr)
  {
     _pFourPointsCmdHdr->Release();
     _pFourPointsCmdHdr = NULL ;
  }
  if ( NULL != _pOriginCheckHdr)
  {
     _pOriginCheckHdr->Release();
     _pOriginCheckHdr = NULL ;
  }

  _piCamera = NULL ;

}

//----------------------BuildGraph PART -----------------------------------

void CAADegCreateBoxCmd::BuildGraph()
{
  cout << "CAADegCreateBoxCmd BuildGraph" << endl ;
  
  //...................
  //1- Agents Creation 
  //...................

  // -----------------------------------------------------
  // The first point to indicate the corner of the Box 
  // -----------------------------------------------------
  _daPathElementCornerPoint = new CATPathElementAgent("daCornerPointId");
  _daPathElementCornerPoint->AddElementType(IID_CAAISysPoint);

  // The selected point is hightlighted 
  _daPathElementCornerPoint->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);

  // -----------------------------------------------------
  // The second point to indicate the width of the Box 
  // -----------------------------------------------------
  _daPathElementWidthPoint = new CATPathElementAgent("daWidthPointId");
  _daPathElementWidthPoint->AddElementType(IID_CAAISysPoint);

  // The selected point is hightlighted 
  _daPathElementWidthPoint->SetBehavior(CATDlgEngWithPSOHSO | CATDlgEngWithPrevaluation);

  // -----------------------------------------------------
  // The third point to indicate the depth of the Box 
  // -----------------------------------------------------
  _daIndicationDepthPoint = new CATIndicationAgent("daDepthPointId");
  _daIndicationDepthPoint->SetBehavior(CATDlgEngAcceptOnPrevaluate |
	                                   CATDlgEngWithPrevaluation);
	         
  // The plane will be indicated after the selection of the first twice points. 

  // -----------------------------------------------------
  // The last point to indicate the height of the Box 
  // -----------------------------------------------------
  _daIndicationHeightPoint = new CATIndicationAgent("daHeightPointId");
  _daIndicationHeightPoint->SetBehavior(CATDlgEngAcceptOnPrevaluate |
	                                   CATDlgEngWithPrevaluation);
	         
  // The plane will be indicated after the selection of the first twice points. 
  
  //...................
  //2- States Creation
  //...................

   CATDialogState *stCornerPoint = GetInitialState("stCornerPointId");
   stCornerPoint->AddDialogAgent(_daPathElementCornerPoint);

   CATDialogState *stWidthPoint =  AddDialogState("stWidthPointId");
   stWidthPoint->AddDialogAgent(_daPathElementWidthPoint);

   CATDialogState *stDepthPoint =  AddDialogState("stDepthPointId");
   stDepthPoint->AddDialogAgent(_daIndicationDepthPoint);

   CATDialogState *stHeightPoint =  AddDialogState("stHeightPointId");
   stHeightPoint->AddDialogAgent(_daIndicationHeightPoint);

  // .......................
  //3- Transitions Creation
  // .......................

  // ----------------
  // From First State
  // ----------------
   
  CATDialogTransition *pState1Transition1= AddTransition
  (
     stCornerPoint,
     stWidthPoint,
     IsOutputSetCondition(_daPathElementCornerPoint),
     Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionCorner)
  ) ;

  // -----------------
  // From Second State 
  // -----------------

  CATDialogTransition *pState2Transition1= AddTransition
  (
     stWidthPoint,
     stDepthPoint,
     AndCondition(IsOutputSetCondition(_daPathElementWidthPoint),
	              Condition((ConditionMethod) & CAADegCreateBoxCmd::CheckChoice,(void*)4)),
     Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionWidth)
  ) ;

  CATDialogTransition *pState2Transition3 = AddTransition
  (
     stWidthPoint,
     NULL,
     AndCondition(IsOutputSetCondition(_daPathElementWidthPoint),
	              Condition((ConditionMethod) & CAADegCreateBoxCmd::CheckChoice,(void*)1)),
     Action((ActionMethod) & CAADegCreateBoxCmd::CreateBox)
  ) ;

  // -----------------
  // From Third state
  // -----------------

  CATDialogTransition *pState3Transition1= AddTransition
  (
     stDepthPoint,
     stHeightPoint,
     AndCondition(IsOutputSetCondition(_daIndicationDepthPoint),
	              Condition((ConditionMethod) & CAADegCreateBoxCmd::CheckChoice,(void*)3)),
     Action((ActionMethod) & CAADegCreateBoxCmd::AcquisitionDepth)
  ) ;

  CATDialogTransition *pState3Transition3 = AddTransition
  (
     stDepthPoint,
     NULL,
     AndCondition(IsOutputSetCondition(_daIndicationDepthPoint),
	              Condition((ConditionMethod) & CAADegCreateBoxCmd::CheckChoice,(void*)2)),
     Action((ActionMethod) & CAADegCreateBoxCmd::CreateBox)
  ) ;

  CATDialogTransition *pState3Transition4 = AddTransition
  (
     stDepthPoint,
     stDepthPoint,
     IsLastModifiedAgentCondition(_daIndicationDepthPoint),
     Action((ActionMethod) & CAADegCreateBoxCmd::DrawTemporaryDepth)
  ) ;

  // -----------------
  // From forth state
  // -----------------

  CATDialogTransition *pState4Transition1 = AddTransition
  (
     stHeightPoint,
     NULL,
     IsOutputSetCondition(_daIndicationHeightPoint),
     Action((ActionMethod) & CAADegCreateBoxCmd::CreateBox)
  ) ;

  CATDialogTransition *pState4Transition2 = AddTransition
  (
     stHeightPoint,
     stHeightPoint,
     IsLastModifiedAgentCondition(_daIndicationHeightPoint),
     Action((ActionMethod) & CAADegCreateBoxCmd::DrawTemporaryHeight)
  ) ;

  // When the end users clicks on one icon representing the way to create
  // the box element. This notification is sent by the 
  AddAnalyseNotificationCB(NULL, "CAADegBoxCreationChoiceNotification",
                (CATCommandMethod)&CAADegCreateBoxCmd::BoxCreationChoiceChange,
                            NULL);
  
}

//----------------------Condition methods's PART -----------------------------

CATBoolean CAADegCreateBoxCmd::CheckChoice(void *iChoice)
{
	CATBoolean Test = FALSE ;
	int Choice = CATPtrToINT32(iChoice) ;
	cout << "CAADegCreateBoxCmd::CheckChoice"<< Choice << endl;

    if ( ( 4 == Choice  ) && ( _CurrentBoxCreationTypeChoice > 1 ) )
	{
		   Test = TRUE;
	}else if ( _CurrentBoxCreationTypeChoice == Choice ) 
	{
		   Test = TRUE;
	}

	return Test ;
}

//----------------------Action methods's PART -----------------------------

CATBoolean CAADegCreateBoxCmd::CreateBox(void *iDummy)
{
  cout << "CAADegCreateBoxCmd::CreateBox" << endl ;

  // Retrieves the factory to create the new Box
  CAAISysGeomFactory * piSysGeomFactory = NULL;                
  HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);
  if (SUCCEEDED(rc))
  {
    // Creation of the Box by a factory 
    CAAISysCuboid * piSysBox = NULL ;
    rc = piSysGeomFactory -> Create(CAAISysGeomFactory::Cuboid, IID_CAAISysCuboid, 
                           (CATBaseUnknown**)&piSysBox);

    // Done with the factory
    piSysGeomFactory->Release();
    piSysGeomFactory=NULL;

    if (SUCCEEDED(rc))
    {      
      // Adds the box in the container's collection
      //
      CAAISysCollection * piSysCollection = NULL;                
      rc = _pContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
      if (SUCCEEDED(rc))
      {
         piSysCollection->AddObject(piSysBox); 
         piSysCollection-> Release();
         piSysCollection=NULL;
      }
      
	  // Find Caracteristic of the Box
      CATMathPoint CornerPoint ;
      CATMathPoint BoxOrigin ;

      FindBoxCornerPoint(CornerPoint);

      if ( NULL == _pOriginCheckHdr )
      {
          BoxOrigin = CornerPoint ;
      } else if (  FALSE == _pOriginCheckHdr->IsChecked() )
      {
         BoxOrigin = CornerPoint ;
      }

      piSysBox->SetOrigin(BoxOrigin);

	  CATMathVector WidthVector,DepthVector,HeightVector ;
	  FindBoxParameters(CornerPoint,WidthVector,DepthVector,HeightVector);
      piSysBox->SetVectors(WidthVector,DepthVector,HeightVector);

      // Updates Display 
      CATIModelEvents * piModelEvent = NULL;                
      rc = piSysBox->QueryInterface(IID_CATIModelEvents, (void**)&piModelEvent);
      if (SUCCEEDED(rc))
      {
		 CATCreate notif(piSysBox,_pUIActiveObject);
         piModelEvent->Dispatch(notif);

         piModelEvent->Release();
         piModelEvent=NULL;
      }
      
      // Updates the specification tree
      CATIRedrawEvent * piRedrawEvent= NULL;                
      rc =_pUIActiveObject->QueryInterface(IID_CATIRedrawEvent, (void**)&piRedrawEvent);
      if (SUCCEEDED(rc))
      {
        piRedrawEvent->Redraw();
        
        piRedrawEvent->Release();
        piRedrawEvent= NULL ;
      }

	  // Box in CSO
	  // Rule: Any object created is set in the CSO
	  // So this object can be used as an entry of the next command, 
	  // if this command used the AddCSOClient method. 
	  // See the CAADegCreateRectangleCmd::BuildGraph method.
	  // 
      CATFrmEditor * pEditor = GetEditor();
      if ( NULL != pEditor) 
      {
        
         CATCSO * pCso = pEditor->GetCSO()  ;
         if ( NULL != pCso)
         {
            // Creation of the path from the root to the Circle
            CATPathElement RootPath     = pEditor->GetUIActiveObject();
            CATPathElement *pPathBox= new CATPathElement(RootPath);
            pPathBox->AddChildElement(piSysBox);

            // Adds the path into the cso
            pCso->AddElement(pPathBox);

            //AddElement AddRef'ed
            pPathBox->Release();
            pPathBox=NULL;
         }
      }

      // Done with the point 
      piSysBox->Release();
      piSysBox=NULL;
    }

  }

  // Remove temporaries vectors set in the ISO 
  int i = 0;
  for ( ; i <3 ; i++ )
  {
	  if ( NULL != _apiTemporaryV[i] )
	  {
         _pISO->RemoveElement( _apiTemporaryV[i]);
         _apiTemporaryV[i]->Release();
         _apiTemporaryV[i]= NULL ;
	  }
  }

  // Remove temporaries points set in the ISO 
  for (  i=0 ; i <2 ; i++ )
  {
	  if ( NULL != _apiTemporaryP[i] )
	  {
         _pISO->RemoveElement( _apiTemporaryP[i]);
         _apiTemporaryP[i]->Release();
         _apiTemporaryP[i]= NULL ;
	  }
  }

  return TRUE ;
}

//-----------------------------------------------------------------------

CATBoolean CAADegCreateBoxCmd::AcquisitionCorner(void *iDummy)
{
	cout << "CAADegCreateBoxCmd::AcquisitionCorner"<< endl;
	return TRUE ;
}

//-----------------------------------------------------------------------

CATBoolean CAADegCreateBoxCmd::AcquisitionWidth(void *iDummy)
{ 
    cout << "CAADegCreateBoxCmd::AcquisitionWidth"<< endl;

    CATMathPoint OriginPoint ;
    FindBoxCornerPoint(OriginPoint);

    CATMathPoint WidthPoint;
    FindBoxWidthPoint(WidthPoint);

    CATMathVector Normal = OriginPoint - WidthPoint ;
    CATMathPlane  ProjectionPlane (OriginPoint,Normal) ;

    // The plane to select the second dimension (the depth) 
    _daIndicationDepthPoint->SetMathPlane(ProjectionPlane);

    // -----------------------------------------------------------------
    // Draw a temporaries elements to visualize the Box in wireframe
    // -----------------------------------------------------------------

    CAAISysGeomFactory * piSysGeomFactory = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);

    if (SUCCEEDED(rc) && ( NULL != _pISO))
    {
       // ------------------------------------------------------------
       // Draw a temporary line to show the first axis: 
       // -------------------------------------------------------------

        piSysGeomFactory->Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
                                    (CATBaseUnknown**)&_apiTemporaryV[0]);
 

        _apiTemporaryV[0]->SetStartPoint(OriginPoint);
        _apiTemporaryV[0]->SetEndPoint(WidthPoint);

        _pISO->AddElement(_apiTemporaryV[0]);


        // ------------------------------------------------------------
        // Draw a temporary line to show the second vector of the Box
        // -------------------------------------------------------------

        piSysGeomFactory->Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
                                    (CATBaseUnknown**)&_apiTemporaryV[1]);

        piSysGeomFactory->Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
                                    (CATBaseUnknown**)&_apiTemporaryP[0]);

        _apiTemporaryV[1]->SetStartPoint(OriginPoint);

        // The Depth point is on the U axis of the plane
        CATMathPoint DepthPoint ;
        ProjectionPlane.EvalPoint(1.f,0.f,DepthPoint);

        _apiTemporaryV[1]->SetEndPoint(DepthPoint);

        _apiTemporaryP[0]->SetCoord(DepthPoint.GetX(),
                                    DepthPoint.GetY(),
                                    DepthPoint.GetZ());

        _pISO->AddElement(_apiTemporaryV[1]);
        _pISO->AddElement(_apiTemporaryP[0]);
        
		
        piSysGeomFactory->Release();
        piSysGeomFactory= NULL ;

        // ------------------------
        // The Viewpoint is changed
        // ------------------------
        CATFrmLayout *pCurrentLayout = CATFrmLayout::GetCurrentLayout();
        if ( NULL != pCurrentLayout )
        {
            CATFrmWindow * pCurrentWindow = pCurrentLayout->GetCurrentWindow();
            if ( NULL != pCurrentWindow )
            {    	  
                 CATICamera * piICamera = NULL ;
                 piICamera = pCurrentWindow->GetCurrentCamera();
      
                 if (NULL != piICamera)
                 {
                     CATI3DCamera * pi3DCamera = NULL;
                     rc = piICamera->QueryInterface(IID_CATI3DCamera,(void **)& pi3DCamera);

                     if ( SUCCEEDED(rc) )
                     {
                         pi3DCamera->SetOrigin(OriginPoint);

                         // The V axis is for the Height point 
                         CATMathPoint HeightPoint ;
                         ProjectionPlane.EvalPoint(0.f,1.f,HeightPoint);

                         CATMathVector DirectionUp = HeightPoint - OriginPoint ;
                         pi3DCamera->SetZenith(DirectionUp);

                         CATMathVector DirectionSight = - (WidthPoint - OriginPoint) ;
	                     pi3DCamera->SetDirection(DirectionSight);

                         pCurrentWindow->SetCurrentCamera(pi3DCamera);

                         pi3DCamera->Release();
                         pi3DCamera = NULL ;
                     }

                     piICamera->Release();
                     piICamera = NULL ;
                 }
            }
        }
    }
	
    return TRUE ;
}

//-----------------------------------------------------------------------

CATBoolean CAADegCreateBoxCmd::AcquisitionDepth(void *iDummy)
{
    cout << "CAADegCreateBoxCmd::AcquisitionDepth"<< endl;
    
	CATMathPoint OriginPoint ;
    FindBoxCornerPoint(OriginPoint);

	CATMathPoint WidthPoint;
    FindBoxWidthPoint(WidthPoint);

	CATMathVector Normal = OriginPoint - WidthPoint ;
    CATMathPlane  ProjectionPlane (OriginPoint,Normal) ;
	
	// The plane to select the third dimension (the height) 
    _daIndicationHeightPoint->SetMathPlane(ProjectionPlane);
    
	// ------------------------------------------------------------
    // Draw a temporary line to show the last vector of the Box
	// -------------------------------------------------------------
	CAAISysGeomFactory * piSysGeomFactory = NULL;                
    HRESULT rc = _pContainer->QueryInterface(IID_CAAISysGeomFactory, 
                                          (void**)&piSysGeomFactory);

    if (SUCCEEDED(rc) && ( NULL != _pISO))
	{
        piSysGeomFactory->Create(CAAISysGeomFactory::Line, IID_CAAISysLine, 
                                    (CATBaseUnknown**)&_apiTemporaryV[2]);
 
	    piSysGeomFactory->Create(CAAISysGeomFactory::Point, IID_CAAISysPoint, 
                                    (CATBaseUnknown**)&_apiTemporaryP[1]);

		_apiTemporaryV[2]->SetStartPoint(OriginPoint);

		// The Height direction is along the V axis of the plane
		CATMathPoint HeightPoint ;
        ProjectionPlane.EvalPoint(0.f,1.f,HeightPoint);

        _apiTemporaryV[2]->SetEndPoint(HeightPoint);

        _apiTemporaryP[1]->SetCoord(HeightPoint.GetX(),
			                     HeightPoint.GetY(),
								 HeightPoint.GetZ());

        _pISO->AddElement(_apiTemporaryV[2]);
        _pISO->AddElement(_apiTemporaryP[1]);
        
		
		piSysGeomFactory->Release();
        piSysGeomFactory= NULL ;

	  }

	return TRUE ;
}

//-----------------------------------------------------------------------

CATBoolean CAADegCreateBoxCmd::DrawTemporaryDepth(void *iDummy)
{
    // Gets the current Point  
    CATMathPoint2D point2D = _daIndicationDepthPoint->GetValue();

	// Retrieves the plane associated to this indication agent
	CATMathPlane Plane = _daIndicationDepthPoint->GetMathPlane() ;
    
    // Projection of the 2D point in 3D space
    CATMathPoint Mouse ;
    Plane.EvalPoint(point2D.GetX(),0.f,Mouse);

    // Update the visualization
    _apiTemporaryP[0]->SetCoord(Mouse.GetX(),Mouse.GetY(),Mouse.GetZ());
    _apiTemporaryV[1]->SetEndPoint(Mouse);
    _pISO->UpdateElement(_apiTemporaryP[0]);
    _pISO->UpdateElement(_apiTemporaryV[1]);

    // Requiered to continue the rubber bending
    _daIndicationDepthPoint->InitializeAcquisition();

	return TRUE ;
}

//-----------------------------------------------------------------------

CATBoolean CAADegCreateBoxCmd::DrawTemporaryHeight(void *iDummy)
{
    // Gets the current Point  
    CATMathPoint2D point2D = _daIndicationHeightPoint->GetValue();

	// Retrieves the plane associated to this indication agent
	CATMathPlane Plane = _daIndicationHeightPoint->GetMathPlane() ;
    
    // Projection of the 2D point in 3D space
    CATMathPoint Mouse ;
    Plane.EvalPoint(0.f,point2D.GetY(),Mouse);

    // Update the visualization
    _apiTemporaryP[1]->SetCoord(Mouse.GetX(),Mouse.GetY(),Mouse.GetZ());
    _apiTemporaryV[2]->SetEndPoint(Mouse);
    _pISO->UpdateElement(_apiTemporaryP[1]);
    _pISO->UpdateElement(_apiTemporaryV[2]);

    // Requiered to continue the rubber bending
    _daIndicationHeightPoint->InitializeAcquisition();

	return TRUE ;
}

//----------------------Focus management PART ---------------------------------

CATStatusChangeRC CAADegCreateBoxCmd::Activate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateBoxCmd::Activate" << endl;

  // This command does't use the cso as entry. 
  // so here we empty it. If your command uses the AddCSOClient method in its 
  // BuildGraph Method, don't empty the CSO (see CAADegCreateCircleCmd)
  //
  CATFrmEditor * pEditor =GetEditor();
  
  if ( NULL != pEditor )
  {
     CATCSO * pCso = pEditor->GetCSO() ;
     if ( NULL != pCso ) 
     {
       pCso->Empty();
     }
  }
  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateBoxCmd::Desactivate( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateBoxCmd::Desactivate" << endl;

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------------------------------------------------------------

CATStatusChangeRC CAADegCreateBoxCmd::Cancel( CATCommand *iCmd,CATNotification *iNotif)
{
  cout << " CAADegCreateBoxCmd::Cancel" << endl;

  // Remove temporaries vectors set in the ISO 
  int i = 0;
  for ( ; i <3 ; i++ )
  {
	  if ( NULL != _apiTemporaryV[i] )
	  {
         _pISO->RemoveElement( _apiTemporaryV[i]);
         _apiTemporaryV[i]->Release();
         _apiTemporaryV[i]= NULL ;
	  }
  }

  // Remove temporaries points set in the ISO 
  for ( i=0 ; i <2 ; i++ )
  {
	  if ( NULL != _apiTemporaryP[i] )
	  {
         _pISO->RemoveElement( _apiTemporaryP[i]);
         _apiTemporaryP[i]->Release();
         _apiTemporaryP[i]= NULL ;
	  }
  }

  // Restore the Camera
  if ( NULL != _piCamera )
  {
     CATFrmLayout *pCurrentLayout = CATFrmLayout::GetCurrentLayout();
     if ( NULL != pCurrentLayout )
	 {
        CATFrmWindow * pCurrentWindow = pCurrentLayout->GetCurrentWindow();
        if ( NULL != pCurrentWindow )
		{
           pCurrentWindow->SetCurrentCamera(_piCamera);
		}
	 }

	 // No more need of this camera
	 _piCamera->Release();
	 _piCamera = NULL ;
  }

  return (CATStatusChangeRCCompleted) ;
}

//-------------------------Private methods -----------------------------

void CAADegCreateBoxCmd::FindBoxParameters( const CATMathPoint  & iOrigin,
												  CATMathVector & oWidth,
												  CATMathVector & oDepth ,
												  CATMathVector & oHeight ) const
{
	CATMathPoint WidthPoint ;
    FindBoxWidthPoint(WidthPoint) ;

	oWidth = WidthPoint - iOrigin ;

	CATMathPlane  Plane (iOrigin,-oWidth) ;

	// -------

    CATMathPoint DepthPoint ;
    double norm = 0 ;
	if ( 1 == _CurrentBoxCreationTypeChoice )
	{
         // Case ||V1|| = ||V2 ||= || V3||
		 norm = oWidth.Norm();
		 Plane.EvalPoint(-norm,0.f,DepthPoint);

	}else if ( _CurrentBoxCreationTypeChoice > 1 )
	{
		 // The Depth point has been given by indication
		if ( NULL != _apiTemporaryV[1] )
		{
            _apiTemporaryV[1]->GetEndPoint(DepthPoint);
		}
	}

    oDepth = DepthPoint - iOrigin ;

	// -------

	CATMathPoint HeightPoint ;
	if (  1 == _CurrentBoxCreationTypeChoice )
	{
         // Case ||VWidth|| = ||VDepth||= || VHeight||
		 norm = oWidth.Norm();
		 Plane.EvalPoint(0.f,norm,HeightPoint);

	}else if ( 2 == _CurrentBoxCreationTypeChoice )
	{
		 // Case ||VHeight|| = ||VDepth|| 
		 //
		 norm = oDepth.Norm();
   		 Plane.EvalPoint(0.f,norm,HeightPoint);

	}else if (  3 == _CurrentBoxCreationTypeChoice )
	{
		// Case where VWidth ,VDepth and  VHeight are differents
		// The Height point has been given by indication
		//
		if ( NULL != _apiTemporaryV[2] )
		{
            _apiTemporaryV[2]->GetEndPoint(HeightPoint);
		}
	}
  
    oHeight= HeightPoint - iOrigin ;


}

//---------------------------------------------------------------------

void CAADegCreateBoxCmd::FindBoxCornerPoint( CATMathPoint  & oOrigin) const
{
 
    CATPathElement * pPathModel = _daPathElementCornerPoint->GetValue();
    CAAISysPoint * piSysCornerPoint = NULL;  
    if ( (NULL != pPathModel) && (0 != pPathModel->GetSize()) )
	{
        // Retrieves the leaf of the path
        CATBaseUnknown * pObject = NULL ;
        pObject = (*pPathModel)[pPathModel->GetSize()-1];
	    if ( NULL != pObject )
		{
            HRESULT rc = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysCornerPoint);
            if ( SUCCEEDED(rc) )
			{
				float x,y,z ;
                piSysCornerPoint->GetCoord(x,y,z);
                oOrigin.SetX(x);
				oOrigin.SetY(y);
			    oOrigin.SetZ(z);

                piSysCornerPoint->Release();
				piSysCornerPoint= NULL ;
			}
		}
	}
}

//---------------------------------------------------------------------

void CAADegCreateBoxCmd::FindBoxWidthPoint( CATMathPoint  & oWidthPoint) const
{
 
    CATPathElement * pPathModel = _daPathElementWidthPoint->GetValue();
    CAAISysPoint * piSysWidthPoint = NULL;  
    if ( (NULL != pPathModel) && (0 != pPathModel->GetSize()) )
	{
        // Retrieves the leaf of the path
        CATBaseUnknown * pObject = NULL ;
        pObject = (*pPathModel)[pPathModel->GetSize()-1];
	    if ( NULL != pObject )
		{
            HRESULT rc = pObject->QueryInterface(IID_CAAISysPoint, (void**)&piSysWidthPoint);
            if ( SUCCEEDED(rc) )
			{
				float x,y,z ;
                piSysWidthPoint->GetCoord(x,y,z);
                oWidthPoint.SetX(x);
				oWidthPoint.SetY(y);
			    oWidthPoint.SetZ(z);

                piSysWidthPoint->Release();
				piSysWidthPoint= NULL ;
			}
		}
	}
}

//---------------------------------------------------------------------
CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteOptions() 
{
   cout <<" CAADegCreateBoxCmd:GetPaletteOptions() " << endl;

   // Fill up the palette with only one option
   CATLISTP(CATCommandHeader) PaletteOptions;

   CATCommandHeader * pCmd = NULL ;
   ::CATAfrGetCommandHeader("CAADegOriginBoxHdr",pCmd);

   if ( NULL != pCmd ) 
   {
       PaletteOptions.Append(pCmd);
       pCmd = NULL ;
   }
  
   return PaletteOptions ;
}

//---------------------------------------------------------------------

CATLISTP(CATCommandHeader) CAADegCreateBoxCmd::GetPaletteStateOptions() 
{
    
   cout <<" CAADegCreateBoxCmd:GetPaletteStateOptions() " << endl;

   CATLISTP(CATCommandHeader) PaletteStateOptions;

   CATDialogState * pCurrentState = GetCurrentState();
   if ( NULL != pCurrentState )
   {
      CATString StateName = pCurrentState->GetResourceID();
     
      if ( ! strcmp("stWidthPointId",StateName) )
      {
          CATCommandHeader * pCmd = NULL ;
          ::CATAfrGetCommandHeader("CAADegTwoPointsBoxHdr",pCmd);
          if ( NULL != pCmd ) 
          {
             PaletteStateOptions.Append(pCmd);
             pCmd = NULL ;
          }

          ::CATAfrGetCommandHeader("CAADegThreePointsBoxHdr",pCmd);
          if ( NULL != pCmd ) 
          {
             PaletteStateOptions.Append(pCmd);
             pCmd = NULL ;
          }

          ::CATAfrGetCommandHeader("CAADegFourPointsBoxHdr",pCmd);
          if ( NULL != pCmd ) 
          {
             PaletteStateOptions.Append(pCmd);
             pCmd = NULL ;
          }

      }else if (  ! strcmp("stDepthPointId" ,StateName) )
      {
          CATCommandHeader * pCmd = NULL ;
          ::CATAfrGetCommandHeader("CAADegThreePointsBoxHdr",pCmd);
          if ( NULL != pCmd ) 
          {
             PaletteStateOptions.Append(pCmd);
             pCmd = NULL ;
          }

          ::CATAfrGetCommandHeader("CAADegFourPointsBoxHdr",pCmd);
          if ( NULL != pCmd ) 
          {
             PaletteStateOptions.Append(pCmd);
             pCmd = NULL ;
          }
      }
   }
   
   return PaletteStateOptions ;
}
    
//---------------------------------------------------------------------

void CAADegCreateBoxCmd::BoxCreationChoiceChange (CATCommand  * iPublisher ,
                                    CATNotification      * iNotification,
                                    CATCommandClientData   iUsefulData)
{
   cout <<" CAADegCreateBoxCmd:GetPaletteStateOptions() " << endl;

   if ( NULL != iNotification )
   {
       if ( 1 == iNotification->IsAKindOf("CAADegBoxCreationChoiceNotification") )
       {
          CAADegBoxCreationChoiceNotification * pNotif = NULL ;
          pNotif = ( CAADegBoxCreationChoiceNotification *) iNotification ;
          
          int value = 0 ;
          HRESULT rc = pNotif->GetChoice(value);

          if ( SUCCEEDED(rc) &&
               (NULL != _pTwoPointsCmdHdr) && 
               (NULL != _pThreePointsCmdHdr) &&
               (NULL != _pFourPointsCmdHdr) )
          {
             if ( value == 1  )
             {
                 _pTwoPointsCmdHdr->SetCheck(TRUE,FALSE);
                 _pThreePointsCmdHdr->SetCheck(FALSE,FALSE);
                 _pFourPointsCmdHdr->SetCheck(FALSE,FALSE);
             }
             if ( value == 2 )
             {
                 _pTwoPointsCmdHdr->SetCheck(FALSE,FALSE);
                 _pThreePointsCmdHdr->SetCheck(TRUE,FALSE);
                 _pFourPointsCmdHdr->SetCheck(FALSE,FALSE);
             }
             if ( value == 3 )
             {
                 _pTwoPointsCmdHdr->SetCheck(FALSE,FALSE);
                 _pThreePointsCmdHdr->SetCheck(FALSE,FALSE);
                 _pFourPointsCmdHdr->SetCheck(TRUE,FALSE);
              
             }
             _CurrentBoxCreationTypeChoice = value ;
          }
       }
   }
}

