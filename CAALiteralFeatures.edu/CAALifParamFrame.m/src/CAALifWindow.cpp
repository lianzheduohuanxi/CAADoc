// COPYRIGHT DASSAULT SYSTEMES 1999 - 2000

// Local Framework
#include "CAALifServices.h"
#include "CATISpecObject.h" // Added by FRG on 07/30/2002
#include "CAALifReturnCodes.h"
#include "CAALifWindow.h"

// LiteralFeatures Framework
#include "CATICkeParmFactory.h"
#include "CATIParmPublisher.h"
#include "CATIParmManipulator.h"
#include "CATICkeParamFrame.h"
#include "CATICkeRelation.h"
#include "CATIParmEvents.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeFunctionFactory.h"
#include "CATIKweActivable.h"

// ObjectModeler Framework
#include "CATIContainer.h"

// ObjectSpecsModeler Framework
#include "CATISpecObject.h"

// Dialog Framework
#include "CATInteractiveApplication.h"    
#include "CATDlgPushItem.h"               
#include "CATDlgBarMenu.h"
#include "CATDlgSubMenu.h"
#include "CATDlgNotify.h"
#include "CATDlgLabel.h"

#include "CAALifApplication.h"

#include "CATIPrtContainer.h"
#include "CATIPrtPart.h"


// C++ Standard Library
#include "iostream.h"

//  Dialog window constructor
//
CAALifWindow::CAALifWindow(CATInteractiveApplication * iParentCommand)                              
: CATDlgDocument(iParentCommand, "CAALifWindowDocument"),
_pApplication(iParentCommand)
{
    
    // Don't construct any object in the constructor 
    // Use the Build method to do this.
    cout << "CAALifWindow::CAALifWindow" << endl;
    _services = NULL;
    
}

// Dialog window destructor
//
CAALifWindow::~CAALifWindow()
{ 
    
    // All dialog's object children of this window are
    // automatically deleted 
    cout << "CAALifWindow::~CAALifWindow" << endl;
    _services->CAALifCloseSession ();
    _pApplication = NULL ;
    _services = NULL;	
    
}

// Build the objects below:
//              * the menu bar
//              * two length type parameters
//              * a parameter manipulator
// Specify the way the "Length1" parameter is to be displayed
// with a spinner - with a label - with the formula pushbutton
// (if any formula constrains "Length1")


void CAALifWindow::Build()
{
    int returnCode = CAALifOk;	
    
    // Create a menu bar 
    CreateMenuBar();
    ((CAALifApplication*)_pApplication)->GetServices( &_services );
    
    // Create a session
    returnCode = _services->CAALifInitSession ();
    if( returnCode != CAALifOk )
    {
        cout << " Init failed ! " << endl;
        return;
    }	
    // Retrieve the parameter factory 
    CATIContainer* piContainer = NULL;
    returnCode = CAALifOk;		
    HRESULT hr = _services->CAALifCreateInstanceContainer( &piContainer );
    if( FAILED(hr) )
    {
        cout << " Build failed ! No Container." ;
        return;
    } 
    // The parameter factory is required to build the
    // objects used below:
    //          the parameters,
    //          the formula,
    //          the manipulator
    CATICkeParmFactory* piFact=NULL;
    HRESULT rc = piContainer->QueryInterface(IID_CATICkeParmFactory,
        (void**) &piFact);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on container for CATICkeParmFactory" << endl << flush;
        piContainer->Release();
        piContainer = NULL;
        return;
    }	
    
    CATIPrtContainer* piPrtContainer = NULL;
    rc = piContainer->QueryInterface(IID_CATIPrtContainer,
        (void**) &piPrtContainer);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on container for CATIPrtContainer" << endl << flush;
        piContainer->Release();
        piContainer = NULL;
        piFact->Release();
        piFact = NULL;
        return;
    }
    piContainer->Release();	
    piContainer = NULL;
    
    CATIPrtPart_var myPart = NULL_var;
    myPart = piPrtContainer->GetPart();
    piPrtContainer->Release();
    piPrtContainer = NULL;			
    if( myPart == NULL_var )
    {
        cout << "Mechanical Part not retreived." << endl;
        return; 
    }
    CATIParmPublisher* piPublish = NULL;
    rc = myPart->QueryInterface(IID_CATIParmPublisher,
        (void**) &piPublish);
    if (FAILED(rc)) 
    {
        cout << "ERROR in QueryInterface on Container for CATIParmPublisher" << endl << flush;
        piFact->Release();
        piFact = NULL;			
        return;
    }
    
    
    if (NULL != piPublish)
        cout << "Adhesion to CATIParmPublisher" << endl;
    
    // Create a length type parameter 
    // Its name is "Length1" - Its initial value is 0
    // _spParam1 is declared as a private data in CAALifWindow.h
    //
    _spParam1 = piFact->CreateLength("Length1",0);
 
	// It is important (but not necessary) to aggregate those parameters especially in part context
	CATISpecObject_var spParameterSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Parameter, piPublish
		,CATCke::True);
	CATIParmPublisher_var spParmPublisher = NULL_var;
	if (!!spParameterSet)
		spParmPublisher = spParameterSet;
    
	if (!!spParmPublisher)
		spParmPublisher->Append(_spParam1);

    // Create another length type parameter
    // Name: "Length2" - Initial value: 2.5 mm
    //
    CATICkeParm_var spParam2 = NULL_var;
    spParam2 = piFact->CreateLength("Length2", 2.5/1000);

	// It is important (but not necessary) to aggregate those parameters especially in part context
	if (!!spParmPublisher)
		spParmPublisher->Append(spParam2);

    
    // Define the list of parameters to be passed
    // as the argument 5 of the CreateFormula method
    //
    CATCkeListOf(Parm) pParamList;
    pParamList.Append (_spParam1);
    pParamList.Append (spParam2);
    
    // Create the formula "Length1 = Length2 * 2"
    // Initial value DISPLAYED in the editor : 5.0 mmm 
    //
    CATICkeRelation_var
        spFormula = piFact->CreateFormula ("Formula1",
        "",
        "", 
        _spParam1,
        &pParamList,
        "a2*2",
        NULL_var,
        CATCke::False); 

	// It is important (but not necessary) to aggregate those relations especially in part context
	CATISpecObject_var spRelationSet = CATCkeGlobalFunctions::GetFunctionFactory()->GetCurrentSet(CATICkeFunctionFactory::Relation, piPublish,CATCke::True);
	if (!!spRelationSet)
	{
		CATIParmPublisher_var spParmPublisher = spRelationSet;
		if (!!spParmPublisher)
		{
			spParmPublisher->Append(spFormula);
		}
	}

    // Deactivate the formula
    // To display the f(x) pushbutton opposite
    // the value field of the parameter editor, you can comment the
    // statement below so that "Formula1" keeps on being activated.
    // but:
    // WARNING: as there is no formula editor plugged, you will crash 
    // 
	CATIKweActivable_var hKweActivable = spFormula;
   	hKweActivable->SetActivationStatus(0);
    
    // Create a manipulator
    //
    CATIParmManipulator_var spParmManip = NULL_var;
    spParmManip = piFact->CreateParmManipulator();
    
    // Associate the manipulator with "Length1"
    //
    _spParam1->SetManipulator (spParmManip);

    /*
    * argument 1: minimum value in model units:0.5
    * argument 2: 1 (minimum can be reached)
    * argument 3: maximum value in model units:5.0
    * argument 4: 1 (maximum can be reached)
    */
    spParmManip->SetAccurateRange (0.5,1,5,1);
    
    // Set the manipulator increment value
    //
    spParmManip->SetStep (0.5);
    
    
    // Create an editor for "Length1"
    /*
    *   CATCkeLabel: label associated with the parameter editor (value fetched in CAALifWindow.CATNls)
    *   CATCkeWithSpinner : a spinner added to the parameter editor
    */
    CATICkeParamFrame_var spParamFrame1 = _spParam1;
    
    CATDlgFrame *pFrame1  =  NULL;
    //pFrame1 = spParamFrame1->GetInPanelEdition(spPublish,this,
    pFrame1 = spParamFrame1->GetInPanelEdition(NULL_var,this,
        CATCkeLabel|CATCkeWithSpinner, "MySpinner");
    
    // Subscribe to a "ChangeValue" notification
    // Launch the Update function for any change value notification 
    //
    CATIParmEvents_var spEvt = _spParam1;
    AddCallback(spEvt->GetCallbackManager(),
        spEvt->GetChangeValueNotification(),
        (CATSubscriberMethod)&CAALifWindow::OnDisplayMessage, NULL);
    
    piPublish->Release();
    piPublish = NULL;
    piFact->Release();
    piFact = NULL;
  }
  
  // Create a menu bar with the File & File->Exit commands
  // Specify that the CAALifWindow::Exit is launched when the window is closed 
  // or when the Exit command is selected
  
  void CAALifWindow::CreateMenuBar()
  {
      CATDlgBarMenu * pMenuBar = NULL ;
      pMenuBar  = new CATDlgBarMenu(this, "MenuBar");
      
      CATDlgSubMenu * pFileMenu = NULL ;
      pFileMenu = new CATDlgSubMenu(pMenuBar, "File");
      
      CATDlgPushItem * pPushItem = NULL ;
      pPushItem = new CATDlgPushItem(pFileMenu, "Exit"); 
      
      
      AddAnalyseNotificationCB(pPushItem,
          pPushItem->GetMenuIActivateNotification(),
          (CATCommandMethod)&CAALifWindow::OnExit, NULL);
      
      AddAnalyseNotificationCB(this,
          GetWindCloseNotification(),
          (CATCommandMethod)&CAALifWindow::OnExit, NULL);
      
  }
  
  // Make the event subscriber resign its subscription to all the callbacks 
  // added for all the events published by _spParam1 
  // Terminate the application
  //
  void CAALifWindow::OnExit(CATCommand* iMyCommand, 
      CATNotification* paramNotification,
      CATCommandClientData myData)
  {
      CATIParmEvents_var spEvt = _spParam1;
      RemoveSubscriberCallbacks(spEvt->GetCallbackManager()); 
      _pApplication->Destroy();
      _pApplication = NULL ;
  }
  
  // Display an information box with the new parameter value
  //
  void CAALifWindow::OnDisplayMessage(CATCallbackEvent parmEvent, 
      void* publisherObject,
      CATNotification* paramNotification,
      CATSubscriberData myData,
      CATCallback callBackId)
  {
      CATDlgNotify* 
          pNotif = new CATDlgNotify(this, "", CATDlgNfyInformation|CATDlgWndModal);
      
      pNotif->DisplayBlocked (_spParam1->Show().ConvertToChar(),"New value for parameter");
  }
