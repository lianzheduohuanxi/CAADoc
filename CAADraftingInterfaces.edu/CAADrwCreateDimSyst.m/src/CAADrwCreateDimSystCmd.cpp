// COPYRIGHT DASSAULT SYSTEMES 2000
#include "CAADrwCreateDimSystCmd.h"

// System
#include <iostream.h>
#include "CATBaseUnknown.h"
#include "CATCreateExternalObject.h"   // Define the CATDeclareClass macro
#include "CATIUnknownListImpl.h"
#include "CATIUnknownList.h"
#include "IUnknown.h" 

// ObjectSpecsModeler
#include "CATISpecObject.h"

// DialogEngine
#include "CATDialogState.h"

// Visualization
#include "CATPathElementAgent.h"
#include "CATPathElement.h"
#include "CATSO.h"

// DraftingInterface
#include "IDMPoint2D.h"
#include "CATIDrwAnnotationFactory.h"
#include "CATIDrwDimDimension.h"
#include "CATDimDefinition.h"
#include "CATIDrwDimSystem.h"
#include "CATDimSystemDefinition.h"
#include "CATIDrwStackedDimSystem.h"
#include "CATDrwDimEnum.h"
#include "CATDrwDimSystemType.h"

// Mathematics
#include "CATMathPoint2D.h"

// The command name
CATCreateClass (CAADrwCreateDimSystCmd);

// ----------------------------------------------------------------------------
CAADrwCreateDimSystCmd::CAADrwCreateDimSystCmd():CATStateCommand(CATString("CreateDimSystem"))
, _pObjectAgent(NULL)
{
}

// ----------------------------------------------------------------------------
CAADrwCreateDimSystCmd::~CAADrwCreateDimSystCmd()
{
   if (NULL != _pObjectAgent) {_pObjectAgent->RequestDelayedDestruction(); _pObjectAgent = NULL;}
}

// ----------------------------------------------------------------------------
void CAADrwCreateDimSystCmd::BuildGraph()
{  
   // Creation of the acquisition agent
   _pObjectAgent = new CATPathElementAgent("_pObjectAgent A");
   _pObjectAgent ->SetBehavior( CATDlgEngWithPrevaluation | 
                               CATDlgEngMultiAcquisition | 
                               CATDlgEngWithCSO); 

   // We only want to get points
   _pObjectAgent ->AddElementType("IDMPoint2D");
   AddCSOClient(_pObjectAgent);
   
   //  States definition
   CATDialogState* pState1 = GetInitialState("Sel points");
   pState1->AddDialogAgent(_pObjectAgent);
   
   // Transition definition
   AddTransition(pState1, NULL, IsOutputSetCondition(_pObjectAgent),
                 Action((ActionMethod)&CAADrwCreateDimSystCmd::CreateDimSyst, NULL, NULL));
}

// ----------------------------------------------------------------------------
boolean CAADrwCreateDimSystCmd::CreateDimSyst(void *iData)
{ 
   CATSO* pObjSO = _pObjectAgent->GetListOfValues(); 
   CATPathElement *pElemPath = NULL;

   // Dimension System creation:
   // ==========================
   if (NULL != pObjSO)  
   {
      // We will scan the CSO from the begining
      pObjSO->InitElementList();
      CATIDrwAnnotationFactory *piDrwFact = NULL;
      IDMPoint2D *piFirstElem = NULL;
      IDMPoint2D *piSecondElem = NULL;
      IDMPoint2D *piNextElem = NULL;
      CATIDrwDimSystem *piDimSyst = NULL;
      CATIDrwDimDimension *piDim = NULL;
      CATDimSystemDefinition sysDef;
      sysDef.SystemType = StackedDimSystem;
      sysDef.SetOffsetMode(ConstantOffsetSystem);
      sysDef.SetValueAlignmentMode(OnRefLineSide);
      sysDef.SetValueOffset(100.0);
      while (NULL != (pElemPath = (CATPathElement*)pObjSO->NextElement())  )
      {
         if (NULL == piFirstElem)
         {
           piFirstElem = (IDMPoint2D *)pElemPath->FindElement(IID_IDMPoint2D);
           piDrwFact = (CATIDrwAnnotationFactory *)pElemPath->FindElement(IID_CATIDrwAnnotationFactory);
         }
         else if (NULL == piSecondElem)
         {
          piSecondElem = (IDMPoint2D *)pElemPath->FindElement(IID_IDMPoint2D);
          // Dimension creation
          if (piSecondElem && piFirstElem)
          {

            CATDrwDimType dimType = DrwDimDistance;
            CATDimDefinition dimDef;
            dimDef.OrientationReference = ParallelDim;
            dimDef.Orientation = DrwDimAuto;
            CATIUnknownList * piSelectionsList =NULL;
            CATIUnknownListImpl * piListsel = new CATIUnknownListImpl();
            piListsel->QueryInterface(IID_CATIUnknownList, (void **) &piSelectionsList);
            piListsel->Release(); piListsel=NULL;

            IUnknown * piLine1 = NULL;
            IUnknown * piLine2 = NULL;
            piFirstElem->QueryInterface(IID_IUnknown, (void **)&piLine1);
            piSecondElem->QueryInterface(IID_IUnknown, (void **)&piLine2);
            if (piSelectionsList)
            {
              piSelectionsList->Add(0, piLine1);
              piSelectionsList->Add(1, piLine2);
            }
            double pt1[2],pt2[2];
            piFirstElem->GetPointData(pt1);
            piSecondElem->GetPointData(pt2);
            double  * pts[2] = { NULL, NULL };
            pts[0] = pt1;
            pts[1] = pt2;

            dimDef.Orientation = DrwDimAuto;
            if (piDrwFact)
            {
              piDrwFact->CreateDimension(piSelectionsList,pts,dimType,&dimDef,&piDim);
              piDrwFact->CreateDimSystem(piDim,&sysDef,&piDimSyst);
            }
            if (piLine1) piLine1->Release(),piLine1 = NULL;
            if (piLine2) piLine2->Release(),piLine2 = NULL;
            if (piSelectionsList) piSelectionsList->Release(),piSelectionsList=NULL;
          }
         }
         else if (NULL == piNextElem)
         {
             piNextElem = (IDMPoint2D *)pElemPath->FindElement(IID_IDMPoint2D);
             // Dimension system creation
             if (piNextElem && piDimSyst && piDim)
             {
               double pt1[2];
               piNextElem->GetPointData(pt1);
               CATMathPoint2D ptSel(pt1[0],pt1[1]);
               CATIDrwDimDimension *myDimToAdd = NULL;
               piDimSyst->AddDimension((CATBaseUnknown *)piNextElem,myDimToAdd,&ptSel);
             }
             if (piNextElem) piNextElem->Release(),piNextElem=NULL;
         }
         else
           cout << "invalid input" << endl;
      }
      if (piDim) piDim->Release(),piDim=NULL;

      // Dimension System modifications:
      // ===============================
      if (piDimSyst)
      {
        // Get the master dimension for dimension system moving
        CATIDrwDimDimension *piMasterDim=NULL;
        CATMathPoint2D ptPos(150.0,230);
        piDimSyst->GetMasterDimension(&piMasterDim);
        if (piMasterDim)
        {
          piMasterDim->MoveDimensionLine (ptPos);
          CATISpecObject_var spDimSpec = piMasterDim;
          if (!!spDimSpec)
            spDimSpec->Update();
          piMasterDim->Release();piMasterDim=NULL;
        }
      // Dimension system properties modification
        CATIDrwStackedDimSystem *piDrwStkSyst=NULL;
        if (SUCCEEDED(piDimSyst->QueryInterface(IID_CATIDrwStackedDimSystem,(void **)&piDrwStkSyst)))
        {
          double valueoffset = 12.0;
          piDrwStkSyst->SetValueAlignmentMode(AlignedOnCenter); 
          piDrwStkSyst->SetOffset(valueoffset);
          piDrwStkSyst->Release();piDrwStkSyst=NULL;
        }
        piDimSyst->LineUp(2);
      }
      if (piDrwFact) piDrwFact->Release(); piDrwFact=NULL;
      if (piDimSyst) piDimSyst->Release(),piDimSyst=NULL;
      if (piFirstElem) piFirstElem->Release(),piFirstElem=NULL;
      if (piSecondElem) piSecondElem->Release(),piSecondElem=NULL;
      
      _pObjectAgent -> InitializeAcquisition();
      return TRUE;
   }
   return FALSE;
}

