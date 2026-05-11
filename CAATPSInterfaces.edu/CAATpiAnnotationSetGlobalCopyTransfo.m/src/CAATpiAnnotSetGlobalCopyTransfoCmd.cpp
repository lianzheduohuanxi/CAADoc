/**
* @quickReview OMM 13:08:23
* @quickReview ZGG 04:09:28
* @quickReview TPC 03:01:23
* @quickReview ILI 02:12:04
* @quickReview ZGG 02:04:26
* @quickReview ZGG 02:04:11
* @quickReview ZGG 02:03:05
*/
// COPYRIGHT DASSAULT SYSTEMES 2001
//=============================================================================
//
// CAATpiAnnotSetGlobalCopyTransfoCmd
//    Command to select a geometry and then create a 3D annotation text linked 
//    on selection.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Sep. 2001  Creation
//=============================================================================

//-------------------------------------------------- Include File of this class
#include "CAATpiAnnotSetGlobalCopyTransfoCmd.h"

//---------------------------------------------------------------------- System
#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"
#include "CATListOfCATString.h"
#include "CATUnicodeString.h"
#include "CATGetEnvValue.h"
#include "CATMathPlane.h"
#include "CATSO.h"
#include "CATFrmEditor.h"
#include "CATPathElementAgent.h"
#include "CATPathElement.h"
#include "CATDlgEngUtility.h"
#include "CATDialogState.h"
#include "CATTPSInstantiateComponent.h"
#include "CATITPSSet.h"
#include "CATITPS.h"
#include "CATITPSSetGlobalCopy.h"
#include "CATIPrtPart.h"
#include "CATIProduct.h"
#include "CATIDocRoots.h"
#include "CATILinkableObject.h"
#include "CATITPSDocument.h"
#include "CATITPSList.h"
#include "CATITPSComponent.h"
#include "CATInit.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATIPrtContainer.h"
#include "CATDocument.h"
#include "CATIGSMTool.h"
#include "CATIGeometricalElement.h"
#include "CATBody.h"
#include "CATIAlias.h"
#include "CATMathPoint.h"
#include "CATMathPlane.h"
#include "CATMathVector.h"
#include "CATApplicationFrame.h"
#include "CATDlgWindow.h"
#include "CATDlgNotify.h"
#include "CATIMovable.h"
#include "CATMath3x3Matrix.h"

#include "CATCreateExternalObject.h"
CATCreateClass (CAATpiAnnotSetGlobalCopyTransfoCmd);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiAnnotSetGlobalCopyTransfoCmd::CAATpiAnnotSetGlobalCopyTransfoCmd() : CATStateCommand ("CAATpiAnnotSetGlobalCopyTransfoCmd", CATCommandModeExclusive)
  , _pAgentAnnotationSet(NULL)
{
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiAnnotSetGlobalCopyTransfoCmd::~CAATpiAnnotSetGlobalCopyTransfoCmd()
{
  if(_pAgentAnnotationSet)
    _pAgentAnnotationSet->RequestDelayedDestruction();
  _pAgentAnnotationSet = NULL;
}


//-----------------------------------------------------------------------------
// BuildGraph
//-----------------------------------------------------------------------------
void CAATpiAnnotSetGlobalCopyTransfoCmd::BuildGraph()
{
  // Create selection agent
  _pAgentAnnotationSet = new CATPathElementAgent ("AgentProductRoot", NULL, CATDlgEngWithPrevaluation | CATDlgEngWithCSO);

  AddCSOClient(_pAgentAnnotationSet);

  // Create state
  CATDialogState *pSelectState = GetInitialState("SelectProduct");
  if(pSelectState)
  {
    // Plug selection agent
    pSelectState->AddDialogAgent(_pAgentAnnotationSet);
    // Define transitions
    AddTransition(pSelectState, NULL, IsOutputSetCondition(_pAgentAnnotationSet), Action((ActionMethod)&CAATpiAnnotSetGlobalCopyTransfoCmd::LaunchGlobalCopy));
  }
}


//-----------------------------------------------------------------------------
// CreateTextOnSelection
//-----------------------------------------------------------------------------
boolean CAATpiAnnotSetGlobalCopyTransfoCmd::LaunchGlobalCopy(void * ipData)
{
  if(!_pAgentAnnotationSet) return TRUE;

  if(!CATGetEnv("CAT_FTA_R193_GLOBAL_COPY"))
  {
    LaunchWarningPanel();
    return TRUE;
  }

  // ***********************************************************
  // Sample to use the CAA api: CATITPSSetGlobalCopy::GlobalCopySetTo
  // The annotation set of the first part is copied into the second part
  // A transformation matrix is applied on the first instance
  // The transfo matrix is defined with:
  //           Translation along X: -150 mm
  //           Rotation     along Y:   35deg
  //           Rotation     along Z:   40deg
  // Geometries (solid) of the destination document is the result of the ProductToPart of the first instance.
  // in second step, some annotations have been added on the second instance.
  // A merge is done to solve conflict between datums features A
  // A filter is done using the CaptureName = "KeepFTA"
  //    the annotation text "Right Face" is not manage by the capture "CaptureKeepFTA" => this text is not copied into target part document
  // ***********************************************************

  HRESULT rc = E_FAIL;

  CATITPSSet *piFTASet = NULL;
  CATIPrtPart *piDestinationPart = NULL;
  CATUnicodeString oMessage = "";
  // *********
  // @INPUT
  // CaptureName : used to filter annotations by Capture Name
  // *********
  CATUnicodeString CaptureName = "KeepFTA";
  CATMathTransformation *pTransfo = NULL;
  CATIPrtContainer_var spPrtContDestination;
  CATDocument *pDoc= NULL;

  // Retrieve the selected geometry
  CATSO *pSelection = _pAgentAnnotationSet->GetListOfValues();
  if(pSelection)
  {
    int SOSize = pSelection->GetSize();
    for(int Idx = 0; Idx < SOSize; ++Idx)
    {
      CATPathElement *piPath = NULL;
      piPath = (CATPathElement*) ((*pSelection) [Idx]);
      if(piPath)
      {
        piPath->InitToLeafElement();
        CATBaseUnknown *pBase = piPath->NextFatherElement();
        if(pBase)
        {
          pBase->AddRef();
          CATIProduct *piProdRoot = NULL;
          rc = pBase->QueryInterface(IID_CATIProduct, (void**)&piProdRoot);
          if(pBase) { pBase->Release(); pBase = 0; }
          if(!piProdRoot) return TRUE;
          CATILinkableObject *piProdRootLink = NULL;
          rc = piProdRoot->QueryInterface(IID_CATILinkableObject, (void**)&piProdRootLink);
          if(!piProdRootLink) return TRUE;
          pDoc = piProdRootLink->GetDocument();
          if(piProdRootLink) { piProdRootLink->Release(); piProdRootLink = 0; }
          if(piProdRoot) { piProdRoot->Release(); piProdRoot = 0; }
        }
      }
      piPath = NULL;
    }
  }
  else
  {
    CATFrmEditor *pEditor = CATFrmEditor::GetCurrentEditor();
    if(!pEditor) return TRUE;
    CATPathElement ActivePath = pEditor->GetUIActiveObject();
    ActivePath.InitToTopElement();
    CATBaseUnknown *pBaseEdit = ActivePath.NextChildElement();
    if(!pBaseEdit) return TRUE;
    CATILinkableObject *piProdRootLinkEdit = NULL;
    rc = pBaseEdit->QueryInterface(IID_CATILinkableObject, (void**)&piProdRootLinkEdit);
    if(!piProdRootLinkEdit) return TRUE;
    pDoc = piProdRootLinkEdit->GetDocument();
    if(piProdRootLinkEdit) { piProdRootLinkEdit->Release(); piProdRootLinkEdit = 0; }
  }


  if(!pDoc) return TRUE;
  CATIDocRoots *piDocRoots = NULL;
  rc = pDoc->QueryInterface(IID_CATIDocRoots, (void**)&piDocRoots);
  if(!piDocRoots) return TRUE;
  CATListValCATBaseUnknown_var* list_of_roots = piDocRoots->GiveDocRoots();
  if(piDocRoots) { piDocRoots->Release(); piDocRoots = 0; }
  CATIProduct_var spRootProduct;
  if(list_of_roots && (list_of_roots->Size() >= 1))
    spRootProduct = (*list_of_roots)[1];
  if(list_of_roots) { delete list_of_roots; list_of_roots = 0; }

  if(NULL_var == spRootProduct) return TRUE;

  int ChildCount = spRootProduct->GetChildrenCount();
  if(ChildCount != 2) return TRUE;
  CATListValCATBaseUnknown_var *pChildList = spRootProduct->GetChildren();
  if(!pChildList) return TRUE;
  int ChildCountCheck = pChildList->Size();
  if(ChildCountCheck != 2) return TRUE;

  // Get the position matrix applied on initial document. No position matrix applied on destination document.
  CATBaseUnknown_var spThirdInstance = (*pChildList)[1];
  CATMathTransformation MatrixComputedResultGeom;
  if(NULL_var != spThirdInstance)
  {
    CATIMovable* piMovable = NULL;
    HRESULT rc = spThirdInstance->QueryInterface(IID_CATIMovable, (void**)&piMovable);
    if( SUCCEEDED(rc) )
      piMovable->GetAbsPosition(MatrixComputedResultGeom);
    if(piMovable) { piMovable->Release(); piMovable = 0; }
  }

  CATBaseUnknown_var spBaseChild;
  for(int IdxChild = 1; IdxChild <= ChildCountCheck; ++IdxChild)
  {
    int TPSSetIncludedIntoDocChild = 0;

    spBaseChild = (*pChildList)[IdxChild];

    CATIProduct_var spProdChild = spBaseChild;
    if(NULL_var == spProdChild) return TRUE;
    CATIProduct_var spProdRef = spProdChild->GetReferenceProduct();
    if(NULL_var == spProdRef) return TRUE;

    CATILinkableObject *piLink = NULL;
    rc = spProdRef->QueryInterface (IID_CATILinkableObject, (void**)& piLink);
    if(SUCCEEDED(rc))
    {
      CATDocument *pDocChild = piLink->GetDocument();
      if(!pDocChild ) return TRUE;

      if(!piFTASet)
      {
        CATITPSDocument *piTPSDoc = NULL;
        pDocChild->QueryInterface(IID_CATITPSDocument, (void**)&piTPSDoc);
        if(!piTPSDoc) return TRUE;
        CATITPSList *piSetList = NULL;
        rc = piTPSDoc->GetSets(&piSetList, CATTPSSSMLocal);
        if(SUCCEEDED(rc))
        {
          unsigned int SetCount = 0;
          rc = piSetList->Count(&SetCount);
          if(SUCCEEDED(rc) && SetCount)
          {
            CATITPSComponent *piTPSComp = NULL;
            rc = piSetList->Item(0, &piTPSComp);
            if(SUCCEEDED(rc))
            {
              rc = piTPSComp->QueryInterface (IID_CATITPSSet, (void**)&piFTASet);
              TPSSetIncludedIntoDocChild = 1;
            }
            if(piTPSComp) { piTPSComp->Release(); piTPSComp = 0; }
          }
        }
        if(piSetList) { piSetList->Release(); piSetList = 0; }
        if(piTPSDoc) { piTPSDoc->Release(); piTPSDoc = 0; }
      }

      if(!TPSSetIncludedIntoDocChild)
      {
        CATInit *piDocAsInit = NULL;
        rc = pDocChild->QueryInterface(IID_CATInit, (void**)&piDocAsInit);
        if(!piDocAsInit ) return TRUE;
        CATBaseUnknown *piBase = piDocAsInit->GetRootContainer("CATIPrtContainer");
        if(piDocAsInit) { piDocAsInit->Release(); piDocAsInit = 0; }
        if(!piBase) return TRUE;

        CATIPrtContainer *piPrtCont = NULL;
        rc = piBase->QueryInterface(IID_CATIPrtContainer, (void**)&piPrtCont);
        if(piBase) { piBase->Release(); piBase = 0; }
        if(!piPrtCont) return TRUE;

        spPrtContDestination = piPrtCont;

        CATISpecObject_var spSpecPart = piPrtCont->GetPart();
        if(piPrtCont) { piPrtCont->Release(); piPrtCont = 0; }
        if(spSpecPart == NULL_var ) return TRUE;
        rc = spSpecPart->QueryInterface(IID_CATIPrtPart, (void**)&piDestinationPart);
      }
    }
    if(piLink) { piLink->Release(); piLink = 0; }
  }
  pDoc = NULL;

  if(!piDestinationPart) return TRUE;
  if(!piFTASet) return TRUE;

  CATIPrtPart_var spDestinationPart = piDestinationPart;
  if(NULL_var == spDestinationPart) return TRUE;
  if(NULL_var == spPrtContDestination) return TRUE;

  // *********
  // @INPUT
  // Transfo matrix: get the transfo matrix of the first child instance
  // *********
  pTransfo = new CATMathTransformation(MatrixComputedResultGeom);
  if(!pTransfo) return FALSE;

  CATITPSSetGlobalCopy *piGlobalCopySet = NULL;
  rc = piFTASet->QueryInterface(IID_CATITPSSetGlobalCopy, (void**)&piGlobalCopySet);
  if(piGlobalCopySet)
  {
    rc = piGlobalCopySet->GlobalCopySetTo(piDestinationPart, oMessage, &CaptureName, pTransfo);
    fprintf(stderr, "oMessage = %s\n", oMessage.CastToCharPtr());
  }
  if(piDestinationPart) { piDestinationPart->Release(); piDestinationPart = 0; }
  if(piGlobalCopySet) { piGlobalCopySet->Release(); piGlobalCopySet = 0; }
  if(piFTASet) { piFTASet->Release(); piFTASet = 0; }
  if(pTransfo) { delete pTransfo; pTransfo = 0; }

  return TRUE;
}

void CAATpiAnnotSetGlobalCopyTransfoCmd::LaunchWarningPanel()
{
  // Send warning panel
  CATApplicationFrame *pFrame = CATApplicationFrame::GetFrame();
  if(pFrame)
  {
    CATDlgWindow *pWindow = pFrame->GetMainWindow();
    if(pWindow)
    {
      CATDlgStyle WinStyle = CATDlgNfyWarning;
      CATDlgNotify *pWarnWind =  new CATDlgNotify (pWindow, "WarningImportAnnotationSetVariable", WinStyle);

      // Retrieve message from catalog
      CATString Catalog("CATTPSCommandImportAnnotationSet");
      CATUnicodeString TitKeyUni = "Title";
      CATUnicodeString MsgKeyUni = "Message";
      CATString TitKey = TitKeyUni.ConvertToChar();
      CATString MsgKey = MsgKeyUni.ConvertToChar();
      const CATUnicodeString WinTit = CATMsgCatalog::BuildMessage(Catalog, TitKey);
      const CATUnicodeString WinMsg = CATMsgCatalog::BuildMessage(Catalog, MsgKey);

      int ButtonPressed = pWarnWind->DisplayBlocked(WinMsg, WinTit);
      pWarnWind->RequestDelayedDestruction();
    }
  }
  return;
}
