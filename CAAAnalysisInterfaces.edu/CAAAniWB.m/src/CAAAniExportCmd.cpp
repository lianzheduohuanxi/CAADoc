#include "CAAAniExportCmd.h"

#include "CATISpecObject.h"
#include "CATIAAnalysisCase.h"
#include "CATISamAnalysisCase.h"
#include "CATIAAnalysisModel.h"
#include "CATIAAnalysisSets.h"
#include "CAAIAniExport.h"

// ApplicationFrame / Dialgog / DialogEngine  prereqs...
#include "CATApplicationFrame.h"  
#include "CATLib.h"  
#include "CATPathElementAgent.h"
#include "CATPathElement.h"

#include "CATIScriptManager.h"
#include "CATIScriptJournal.h"
#include "CATIScriptMethodCall.h"


#include "CATCreateExternalObject.h"
CATCreateClass(CAAAniExportCmd);

//=============================================================================
// Implementation
//=============================================================================
CATImplementClass(CAAAniExportCmd,Implementation,CATStateCommand,CATNull);

//=============================================================================
// constructor
//=============================================================================
CAAAniExportCmd::CAAAniExportCmd ():
  CATStateCommand(CATString("CAAAniExportCmd")),
  _CaseFound (NULL),
  _Case (NULL)
{
}

//=============================================================================
// destructor
//=============================================================================
CAAAniExportCmd::~CAAAniExportCmd()
{
  // clean of Feature 
  if (_Case)  _Case -> Release ();   _Case = NULL;
  // clean of dialog agent
  if (_CaseFound)  _CaseFound -> Release ();   _CaseFound = NULL;
}

//=============================================================================
// BuildGraph :
//=============================================================================
void CAAAniExportCmd::BuildGraph()
{
  // a single state
  CATDialogState * selState = GetInitialState ("SelectState");

  // one dialog agent
  _CaseFound = new CATPathElementAgent ("SelectCaseAgent");
  _CaseFound -> SetBehavior (CATDlgEngWithPrevaluation | CATDlgEngWithPSOHSO);
  _CaseFound -> AddElementType (IID_CATISamAnalysisCase);


  CATAcquisitionFilter * filter = Filter ((FilterMethod)&CAAAniExportCmd::FindACase,(void *) NULL);
  _CaseFound -> SetFilter (filter);
  AddCSOClient (_CaseFound);

  // add dialog agents to states
  selState -> AddDialogAgent (_CaseFound);

  // transition : etat initial -> Check
  AddTransition (selState,NULL,IsOutputSetCondition(_CaseFound),
         Action ((ActionMethod) &CAAAniExportCmd::Export,NULL));
}

//=============================================================================
// FindACase :
//=============================================================================
CATBoolean CAAAniExportCmd::FindACase (CATDialogAgent * iAgent,void * iData)
{ 
  if (_Case) _Case -> Release(); _Case = NULL;
  CATPathElement * path = _CaseFound -> GetValue ();

  if (path) {
    CATBaseUnknown * pCurr = path -> CurrentElement ();
    if (NULL == pCurr) return FALSE;

    pCurr -> QueryInterface (IID_CATISamAnalysisCase,(void **) &_Case);
  }

  if (_Case)  return TRUE;
  return FALSE;
}

//=============================================================================
// Export :
//=============================================================================
CATBoolean CAAAniExportCmd::Export (void * iData)
{
  CATApplicationFrame::SetBusyCursor();
  if (NULL == _Case) return FALSE;

  CATISpecObject* piModel = NULL;
  _Case -> GetWorkingModel(piModel);
  if (NULL == piModel) return FALSE;

  CATIAAnalysisModel_var spModelVB (piModel);
  piModel -> Release(); piModel = NULL;
  if (NULL_var == spModelVB) return FALSE;

  CATIAAnalysisSets * piListSets = NULL;
  spModelVB -> get_AnalysisSets(piListSets);
  if (piListSets){
    CATLONG nbSet = 0;
    piListSets -> get_Count (nbSet);
    piListSets -> Release();
  }

  CATIAAnalysisCase_var spCaseVB (_Case);
  CATUnicodeString String ("CAAAniExportVBExt");
  CATUnicodeString Path = CATGetTempDirectory();
  Path += CATUnicodeString("Fic.txt");
  CATBSTR Bstr, PathBstr;
  Path.ConvertToBSTR(&PathBstr);
  String.ConvertToBSTR(&Bstr);
  
  CATBaseDispatch * piDispa = NULL;
  spModelVB -> GetItem(Bstr,piDispa);
  CAAIAniExport_var spIdlObject(piDispa);

  if (piDispa) piDispa -> Release();

  if (!!spIdlObject ) spIdlObject -> Export(spCaseVB,PathBstr);

// Record the command.
  CATIScriptManager * piScriptManager = NULL;
  GetScriptManager(piScriptManager);
  if (piScriptManager)
  {
    CATBoolean IsRecording = FALSE;
    piScriptManager -> IsRecording(IsRecording);
    if (IsRecording)
    {
      CATIScriptJournal * piJournal = NULL;
      piScriptManager -> GetJournal(piJournal);
      if (piJournal) 
      {
        CATIScriptMethodCall * piMethodCall = NULL;
			 	piJournal -> CreateMethodCall(piMethodCall);
        if (piMethodCall)
        {
          piMethodCall -> SetTarget((CAAIAniExport*)spIdlObject);
          piMethodCall -> SetMethodName("Export");
          piMethodCall -> AddParameter((CATIAAnalysisCase*) spCaseVB,CATParamIn, FALSE);
          piMethodCall -> AddParameter(PathBstr,CATParamIn, FALSE);
        
          piJournal -> AddMethodCall(piMethodCall);
          piMethodCall -> Release();
        }
        piJournal -> Release();
      }
    }
    piScriptManager -> Release();
  }

  CATFreeString(Bstr);
  CATFreeString(PathBstr);

  return TRUE;
}
