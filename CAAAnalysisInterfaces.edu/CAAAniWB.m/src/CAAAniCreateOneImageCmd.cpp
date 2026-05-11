#include "CAAAniCreateOneImageCmd.h"

// CATAnalysisVisuInterfaces prereqs
#include "CATISamImage.h"
#include "CATISamImageColorMap.h"
#include "CATISamImageFactory.h"

// CATAnalysisInterfaces prereqs
#include "CATISamAccess.h"
#include "CATICharacCollector.h"
#include "CATISamExplicit.h"
#include "CATAnalysisExplicitModel.h"
#include "CATAnalysisExplicitRulesData.h"

// ApplicationFrame / Dialgog / DialogEngine  prereqs...
#include "CATApplicationFrame.h"  
#include "CATFrmEditor.h"  
#include "CATPathElementAgent.h"
#include "CATPathElement.h"

// Object Modeler 
#include "CATDocument.h"  
#include "CATIContainer.h"  

#include "CATCreateExternalObject.h"
CATCreateClass(CAAAniCreateOneImageCmd);

//=============================================================================
// Implementation
//=============================================================================
CATImplementClass( CAAAniCreateOneImageCmd ,
                   Implementation , 
                   CATStateCommand ,
                   CATNull );

//=============================================================================
// constructor
//=============================================================================
CAAAniCreateOneImageCmd::CAAAniCreateOneImageCmd ():
  CATStateCommand(CATString("CAAAniCreateOneImageCmd")),
  _SolutionFound ( NULL ),
  _Solution ( NULL )
{
}

//=============================================================================
// destructor
//=============================================================================
CAAAniCreateOneImageCmd::~CAAAniCreateOneImageCmd()
{
  // clean of Feature 
  if ( _Solution )  _Solution -> Release ();   _Solution = NULL;
  // clean of dialog agent
  if ( _SolutionFound )  _SolutionFound -> Release ();   _SolutionFound = NULL;
}

//=============================================================================
// BuildGraph :
//=============================================================================
void CAAAniCreateOneImageCmd::BuildGraph()
{
  // a single state
  CATDialogState * selState = GetInitialState ( "SelectState" );

  // one dialog agent
  _SolutionFound = new CATPathElementAgent ( "SelectSolutionAgent" );
  _SolutionFound -> SetBehavior ( CATDlgEngWithPrevaluation | CATDlgEngWithPSOHSO );

  // only objects that Implement CATICharacCollector
  _SolutionFound -> AddElementType ( IID_CATICharacCollector);

// Define the behavior of the selection filter:
//    only analysis feature Implementing CATICharacCollector Interface 
//    and that may return the physical type: "TRANSLATIONAL_VELOCITY"

  CATAcquisitionFilter * filter = Filter ((FilterMethod )
                                          &CAAAniCreateOneImageCmd::FindASolution,
                                          (void *) NULL );
  _SolutionFound -> SetFilter ( filter );
  AddCSOClient ( _SolutionFound );

  // add dialog agents to states
  selState -> AddDialogAgent ( _SolutionFound );

  // transition : etat initial -> Check
  AddTransition ( selState , NULL , IsOutputSetCondition(_SolutionFound) ,
         Action ( (ActionMethod) &CAAAniCreateOneImageCmd::CreateImage, NULL ) );
}

//=============================================================================
// FindASolution :
//=============================================================================
CATBoolean CAAAniCreateOneImageCmd::FindASolution ( CATDialogAgent * iAgent , void * iData )
{ 
  if (_Solution) _Solution -> Release(); _Solution = NULL;
  // we retrieve the selected object
  CATBaseUnknown * piReceiver = NULL;
  CATPathElement * path = _SolutionFound -> GetValue ();
  if (path) piReceiver = path -> CurrentElement ();
  if (NULL == piReceiver) return FALSE;

  // the set or the entity must implement the CATICharacCollector interface
  CATICharacCollector * piCollector = NULL;
  HRESULT hr = piReceiver -> QueryInterface ( IID_CATICharacCollector , (void **) &piCollector );
  if ( !SUCCEEDED(hr) ) return FALSE;

  // we have to search the "TRANSLATIONAL_VELOCITY" physical type ID
  CATSamPhysicalType goodPT = CATSamPhysicalTypeNone;  

  // first we retrive the explicit document
  CATISamExplicit * piExplicit = NULL;
  hr = piReceiver -> QueryInterface ( IID_CATISamExplicit ,  (void **) &piExplicit );
  if ( SUCCEEDED(hr) )
  {
    CATAnalysisExplicitModel * pModel = piExplicit -> GetExplicitModel ();
    piExplicit -> Release();
    piExplicit = NULL;
    if ( pModel )
    {
      // and the associated rules data
      const CATAnalysisExplicitRulesData * pRulesData = pModel -> GetRulesData ();
      if ( pRulesData ) pRulesData -> GetPhysicalTypeNumber ( "TRANSLATIONAL_VELOCITY" , goodPT );
    }
  }

  // we retrieve all the physical types provided by the object
  CATBoolean found = FALSE;
  int nbPT = 0;
  const CATSamPhysicalType * ptList = NULL;
  const CATString * unitList = NULL;  
  hr = piCollector -> GetAvailablePhysicalTypes ( nbPT , ptList , unitList );
  if ( SUCCEEDED(hr) )
  {
    // we check if the "TRANSLATIONAL_VELOCITY" physical type is provided
    for ( int ipt=0 ; ipt<nbPT && !found ; ipt++ )
      if ( ptList[ipt] == goodPT ) found = TRUE;
  }

  // we don't need CATICharacCollector interface pointer anymore
  piCollector -> Release (); piCollector = NULL; 

  // KO
  if ( !found ) return FALSE;
  // OK
  if (piReceiver)
    piReceiver -> QueryInterface(IID_CATBaseUnknown,(void **)& _Solution);

  return TRUE;
}

//=============================================================================
// CreateImage :
//=============================================================================
CATBoolean CAAAniCreateOneImageCmd::CreateImage ( void * iData )
{
  CATApplicationFrame::SetBusyCursor();

  // we retrieves the current document
	CATFrmEditor * editor = CATFrmEditor::GetCurrentEditor ();
	if (NULL == editor) return TRUE;

  CATDocument * document = editor -> GetDocument();
	if (NULL == document) return TRUE;

  // if it is an Analysis document, it implements CATISamAccess
  CATISamAccess * piAccess = NULL;
  HRESULT hr = document -> QueryInterface ( IID_CATISamAccess ,  (void **) &piAccess );
  if ( !SUCCEEDED(hr) ) return TRUE;

  // we retrieve the post-processor container
  CATIContainer * piContainer = NULL;
	hr = piAccess -> GetPostproContainer ( piContainer );
  piAccess -> Release();  piAccess = NULL;

  if (NULL == piContainer) return TRUE; /* quit the command in case of error */
  
  // the post-processor container implements CATISamImageFactory interface
  CATISamImageFactory * piFactory = NULL;
  hr = piContainer -> QueryInterface ( IID_CATISamImageFactory ,  (void **) &piFactory );
  piContainer -> Release(); piContainer = NULL;

  if (NULL == piFactory) return TRUE; /* quit the command in case of error */

  // image creation
  CATString imageName ( "CAA_Translational_velocity_Iso" );
  CATISamImage * piNewImage = NULL;
  hr = piFactory -> CreateImage ( imageName , _Solution , piNewImage );

  piFactory -> Release(); piFactory = NULL;

  if (NULL == piNewImage) return TRUE; /* quit the command in case of error */

  // we retrieve the color map
  CATISamImageColorMap * piColorMap = NULL;
  hr = piNewImage -> GetColorMap ( piColorMap );
  if (NULL != piColorMap)
  {
    // we impose the bounds
    piColorMap -> ImposeMinValue ( 1.f );
    piColorMap -> ImposeMaxValue ( 6.f );

    // and we update the color map...
    piColorMap -> UpdateDisplay ();

    piColorMap -> Release (); piColorMap = NULL;  
  }

  piNewImage -> Release ();  piNewImage = NULL;  

  return TRUE;
}

