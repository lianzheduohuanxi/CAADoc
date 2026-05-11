/**
 * @quickReview SOB 05:06:08
 * @quickReview ZGG 04:09:28
 * @quickReview ZGG 02:03:05
 */
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiRetrieveAnnotationCmd
//    Command to select a geometry and then retrieve and highlight all
//    3D annotations which are applied on selected geometry.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Fev. 2002  Creation
//=============================================================================

//---------------------------------------------- Include File of this extension
#include "CAATpiRetrieveAnnotationCmd.h"

//---------------------------------------------------------------------- System
#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

//--------------------------------------------------------------- Visualization
#include "CATPathElement.h"
#include "CATHSO.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATFrmEditor.h"

//------------------------------------------------------- InteractiveInterfaces
#include "CATIBuildPath.h"

//---------------------------------------------------------------- DialogEngine
#include "CATStateCommand.h"
#include "CATPathElementAgent.h"
#include "CATDialogAgent.h"
#include "CATDlgEngUtility.h"
#include "CATDialogState.h"

//----------------------------------------------------------- ObjectModelerBase
#include "CATIAlias.h"

//------------------------------------------------------------ CATTPSInterfaces
#include "CATTPSInstantiateComponent.h"
#include "CATITPSRetrieveServices.h"
#include "CATITPSList.h"
#include "CATITPSComponent.h"

//------------------------------------------------------------ CAATPSInterfaces
#include "CAATpiRetrieveAnnotationWnd.h"

#include "CATCreateExternalObject.h"
CATCreateClass (CAATpiRetrieveAnnotationCmd);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiRetrieveAnnotationCmd::CAATpiRetrieveAnnotationCmd ()
: CATStateCommand ("CAATpiRetrieveAnnotationCmd", CATCommandModeExclusive)
, _pSelectionAgent (NULL)
, _pClosePanelAgent (NULL)
, _pPanel (NULL)
{}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiRetrieveAnnotationCmd::~CAATpiRetrieveAnnotationCmd ()
{
  if ( _pSelectionAgent )
  {
    _pSelectionAgent -> RequestDelayedDestruction();
    _pSelectionAgent = NULL;
  }
  if ( _pClosePanelAgent )
  {
    _pClosePanelAgent -> RequestDelayedDestruction();
    _pClosePanelAgent = NULL;
  }
  if ( _pPanel )
  {
    _pPanel -> RequestDelayedDestruction();
    _pPanel = NULL;
  }
}


//-----------------------------------------------------------------------------
// BuildGraph
//-----------------------------------------------------------------------------
void CAATpiRetrieveAnnotationCmd::BuildGraph ()
{
  // Create selection agent
  _pSelectionAgent = new CATPathElementAgent ("SelectionAgent",
                                              NULL,  // all objects accepted
                                              CATDlgEngWithPrevaluation|
                                              CATDlgEngWithPSOHSO|
                                              CATDlgEngRepeat);
  AddCSOClient (_pSelectionAgent);

  // Create panel
  _pPanel = new CAATpiRetrieveAnnotationWnd ();
  _pPanel -> SetFather (this);
  _pPanel -> SetVisibility (CATDlgShow);

  // Create agent on Panel
  _pClosePanelAgent = new CATDialogAgent("ClosePanelAgent");

  _pClosePanelAgent -> AcceptOnNotify (_pPanel,
                                       _pPanel -> GetWindCloseNotification());
  _pClosePanelAgent -> AcceptOnNotify (_pPanel,
                                       _pPanel -> GetDiaCLOSENotification());

  // Retrieve initial state
  CATDialogState * pSelectState = GetInitialState("SelectState");
  if ( pSelectState )
  {
    // Plug selection agent
    pSelectState -> AddDialogAgent(_pSelectionAgent);
    pSelectState -> AddDialogAgent(_pClosePanelAgent);
  
    // Define transitions
    AddTransition (pSelectState,
                   pSelectState,
                   IsOutputSetCondition(_pSelectionAgent),
                   Action((ActionMethod)& 
                   CAATpiRetrieveAnnotationCmd::SomethingSelected));

    AddTransition (pSelectState,
                   NULL,
                   IsOutputSetCondition(_pClosePanelAgent),
                   NULL);
  }
}


//-----------------------------------------------------------------------------
// SomethingSelected
//-----------------------------------------------------------------------------
boolean CAATpiRetrieveAnnotationCmd::SomethingSelected (void * ipData)
{
  if ( !_pSelectionAgent || !_pPanel ) return (TRUE);

  HRESULT rc = E_FAIL;

  // List of Alias of the retrieved 3D annotations that will be displayed
  // in the panel
  CATListValCATUnicodeString AliasList;

  // Retrieve the selection
  CATPathElement * pPathSelected = _pSelectionAgent -> GetValue ();
  if ( pPathSelected )
  {
    // Retrieve HSO from editor and Empty it
    CATFrmEditor * pEdt = GetEditor();
    if ( pEdt ) 
    {
      CATHSO * pHSO = pEdt -> GetHSO();
      if ( pHSO ) 
      {
        pHSO -> Empty();
        // Add selected PathElement in the HSO, it will be highlighted
        pHSO -> AddElements (pPathSelected);
        
        // Retrieve CATITPSRetrieveServices interfaces
        CATITPSRetrieveServices * piRetServ = NULL;
        rc = CATTPSInstantiateComponent (DfTPS_ItfRetrieveServices,
                                         (void**) & piRetServ);
        if ( SUCCEEDED(rc) )
        {
          // Retrieve the list of TPS (3D Annotations) linked on selected Path
          CATITPSList * piTPSList = NULL;
          rc = piRetServ -> RetrieveTPSsFromPath (pPathSelected, NULL, &piTPSList);
          if ( SUCCEEDED(rc) )
          {
            unsigned int Count = 0;
            piTPSList -> Count(&Count);
            if ( Count )
            {
              CATITPSComponent * piItem = NULL;

              CATIAlias * piAlias = NULL;
              CATUnicodeString Alias;

              CATIBuildPath * piBuildPath = NULL;
              CATPathElement * pPath = NULL;

              // Iterate on the list of 3D annotations 
              for ( unsigned int Idx = 0 ; Idx < Count ; Idx ++)
              {
                rc = piTPSList -> Item (Idx, &piItem);
                if ( SUCCEEDED(rc) )
                {
                  // Append it's alias to the list of Alias
                  rc = piItem -> QueryInterface (IID_CATIAlias, 
                                                 (void**)&piAlias); 
                  if ( SUCCEEDED(rc) )
                  {
                    Alias = piAlias -> GetAlias();
                    AliasList.Append(Alias);

                    piAlias -> Release();
                    piAlias = NULL;
                  }

                  // Highlight the retrieved TPS by placing its PathElement
                  // in the HSO.
                  rc = piItem -> QueryInterface (IID_CATIBuildPath, 
                                                 (void**)&piBuildPath);  
                  if ( SUCCEEDED(rc) )
                  {
                    rc = piBuildPath->ExtractPathElement(pPathSelected, &pPath);
                    if ( SUCCEEDED(rc) )
                    {
                      pHSO -> AddElements (pPath);

                      pPath -> Release();
                      pPath = NULL;
                    }
                    piBuildPath -> Release();
                    piBuildPath = NULL;
                  }
                  piItem -> Release();
                  piItem = NULL;
                }
              }
            }
            piTPSList -> Release();
            piTPSList = NULL;
          }
          piRetServ -> Release();
          piRetServ = NULL;
        }
        // No more elements to Add in the HSO, notification is send
        // and HSO content can be highlighted.
        pHSO -> EndAddElements ();
        pHSO = NULL;
      }
      pEdt = NULL;
    }
    pPathSelected = NULL;
  }

  // Send AliasList to the panel for Display
  _pPanel -> SetAliasList (AliasList);

  // Reset agent for next selection
  _pSelectionAgent -> InitializeAcquisition();

  return (TRUE);
}
