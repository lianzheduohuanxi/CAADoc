/**
 * @quickReview SOB 05:06:08
 * @quickReview ZGG 04:09:28
 * @quickReview CGK 04:01:13
 * @quickReview ZGG 03:07:04
 * @quickReview ZGG 03:04:17
 * @quickReview ZGG 02:06:05
 * @quickReview ZGG 02:04:26
 * @quickReview SVN 02:04:17
 * @quickReview ZGG 02:04:11
 * @quickReview ZGG 02:03:26
 * @quickReview ZGG 02:03:05
 */
// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CAATpiAccessGeometryCmd
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
#include "CAATpiAccessGeometryCmd.h"

//---------------------------------------------------------------------- System
#include "CATBaseUnknown.h"
#include "CATBooleanDef.h"
#include "CATListOfCATUnicodeString.h"
#include "CATUnicodeString.h"

//---------------------------------------------------------------- DialogEngine
#include "CATDialogState.h"

//----------------------------------------------------------------- Mathematics
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATMathTransformation.h"
#include "CATMathVector.h"
#include "CATMath3x3Matrix.h"
#include "CATSoftwareConfiguration.h"
#include "CATMathDirectionf.h"
#include "CATMathPointf.h"

//----------------------------------------------------------- VisualizationBase
#include "CATPathElement.h"
#include "CATHSO.h"
#include "CATISO.h"
#include "CATModelForRep3D.h"
#include "CAT3DBagRep.h"
#include "CAT3DCustomRep.h"
#include "CAT3DMarkerGP.h"
#include "CAT3DArrowGP.h"
#include "CATGraphicAttributeSet.h"
#include "CAT3DBoundingSphere.h"
#include "CAT4x4Matrix.h"
#include "CAT3DRep.h"

//------------------------------------------------------------ ApplicationFrame
#include "CATFrmEditor.h"

//------------------------------------------------------- InteractiveInterfaces
#include "CATIBuildPath.h"

//----------------------------------------------------------- GeometricsObjects
#include "CATGeoFactory.h"
#include "CATSurface.h"
#include "CATSurParam.h"
#include "CATSurLimits.h"

//------------------------------------------------------- NewTopologicalObjects
#include "CATCell.h"
#include "CATFace.h"
#include "CATPositionPtFaceOperator.h"

//------------------------------------------------------------ ProductStructure
#include "CATIMovable.h"

//---------------------------------------------------------------- DialogEngine
#include "CATStateCommand.h"
#include "CATPathElementAgent.h"
#include "CATDialogAgent.h"
#include "CATDlgEngUtility.h"

//----------------------------------------------------------- MechanicalModeler
#include "CATITTRSList.h"
#include "CATITTRS.h"
#include "CATIRGE.h"
#include "CATIRGETopology.h"

//------------------------------------------------------------ CATTPSInterfaces
#include "CATITPS.h"
#include "CATITPS3DGeoVisu.h"

//------------------------------------------------------------ CAATPSInterfaces
#include "CAATpiAccessGeometryWnd.h"

#include "CATCreateExternalObject.h"
CATCreateClass (CAATpiAccessGeometryCmd);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CAATpiAccessGeometryCmd::CAATpiAccessGeometryCmd ()
: CATStateCommand ("CAATpiAccessGeometryCmd", CATCommandModeExclusive)
, _pSelectionAgent (NULL)
, _pClosePanelAgent (NULL)
, _pPanel (NULL)
, _pModelObjectForAdditionalRep (NULL)
, _bDisplay3DGrid (FALSE)
, _bDisplayTTRSRep (FALSE)
{
  _pModelObjectForAdditionalRep = new CATModelForRep3D();
}


//-----------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------
CAATpiAccessGeometryCmd::~CAATpiAccessGeometryCmd ()
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
  if ( _pModelObjectForAdditionalRep )
  {
    _pModelObjectForAdditionalRep -> Release();
    _pModelObjectForAdditionalRep = NULL;
  }
}


//-----------------------------------------------------------------------------
// BuildGraph
//-----------------------------------------------------------------------------
void CAATpiAccessGeometryCmd::BuildGraph ()
{
  // Create selection agent
  _pSelectionAgent = new CATPathElementAgent ("SelectionAgent",
                                              "CATITPS",  // 3D Annotations
                                              CATDlgEngWithPrevaluation|
                                              CATDlgEngWithPSOHSO/*|
                                              CATDlgEngRepeat*/);
  AddCSOClient (_pSelectionAgent);

  // Create panel
  _pPanel = new CAATpiAccessGeometryWnd ();
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
                   CAATpiAccessGeometryCmd::OnAnnotationSelected));

    AddTransition (pSelectState,
                   NULL,
                   IsOutputSetCondition(_pClosePanelAgent),
                   NULL);
  }
}


//-----------------------------------------------------------------------------
// Cancel
//-----------------------------------------------------------------------------
CATStatusChangeRC CAATpiAccessGeometryCmd::Cancel (CATCommand * ipCmd,
                                                   CATNotification * ipNotif)
{
  // Empty ISO at the end of the command
  if ( _pModelObjectForAdditionalRep )
  {
    CATFrmEditor * pEdt = GetEditor();
    if ( pEdt ) 
    {
      CATISO * pISO = pEdt -> GetISO();
      if ( pISO ) 
      {
        pISO -> RemoveElement (_pModelObjectForAdditionalRep);
      }
    }
    _pModelObjectForAdditionalRep -> Release();
    _pModelObjectForAdditionalRep = NULL;
  }

  return (CATStatusChangeRCCompleted);
}


//-----------------------------------------------------------------------------
// OnAnnotationSelected
//-----------------------------------------------------------------------------
boolean CAATpiAccessGeometryCmd::OnAnnotationSelected (void * ipData)
{
  if ( !_pSelectionAgent
    || !_pPanel
    || !_pModelObjectForAdditionalRep)
  {
    return (TRUE);
  }

  HRESULT rc = E_FAIL;

  int TTRSNodeCount = 0;
  int TTRSSupportCount = 0;
  int RGECount = 0;
  int FaceCount = 0;
  int EdgeCount = 0;
  int VertexCount = 0;

  // Read display parameters from panel
  _pPanel -> GetRequiredDisplay (&_bDisplay3DGrid, &_bDisplayTTRSRep);

  // Retrieve the path of the selected annotation
  CATPathElement * pPathTPS = _pSelectionAgent -> GetValue ();
  if ( pPathTPS )
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
        pHSO -> AddElements (pPathTPS);

        CATISO * pISO = pEdt -> GetISO();
        if ( pISO ) 
        {
          // Clean existing element in ISO
          pISO -> RemoveElement (_pModelObjectForAdditionalRep);

          // Retrieve CATITPS interface on selected 3D annotation
          CATITPS * piTPS = NULL;
          rc = pPathTPS -> Search (IID_CATITPS, (void**) &piTPS);
          if ( SUCCEEDED(rc) )
          {
            // Retrieve the list of TTRSs which are directly referenced by
            // the annotation, most often that list contains only 1 element,
            // exeptions are Semantics Targets V5 and Default Annotation
            CATITTRSList * piTTRSList = NULL;
            rc = piTPS -> GetTTRS (&piTTRSList);
            if ( SUCCEEDED(rc) )
            {
              unsigned int TTRSCount = 0;
              piTTRSList -> Count (&TTRSCount);

              CATITTRS * piTTRS = NULL;

              // Allocate representation to display surfaces of TTRSs
              // Points and normals on the TTRSs faces will be
              // added in that Rep by AnalyseTTRS method.
              CAT3DBagRep * pRep = new CAT3DBagRep();

              // Iterate on the list TTRS
              for ( unsigned int Idx = 0 ; Idx < TTRSCount ; Idx ++)
              {
                rc = piTTRSList -> Item (Idx, &piTTRS);
                if ( SUCCEEDED(rc) )
                {
                  // Analyse TTRS Composition
                  AnalyseTTRS (piTTRS, pHSO, pPathTPS,
                               TTRSNodeCount, TTRSSupportCount, RGECount,
                               FaceCount, EdgeCount, VertexCount, pRep);

                  // Construct a Rep to visualize TTRS and add it to ISO
                  AddTTRSGeometryOnRepresentation (piTTRS, pPathTPS, pRep);

                  piTTRS -> Release();
                  piTTRS = NULL;
                }
              }
              // Add new Rep in ISO
              _pModelObjectForAdditionalRep -> SetRep (pRep);

              pISO -> AddElement (_pModelObjectForAdditionalRep);
              pRep = NULL;

              piTTRSList -> Release();
              piTTRSList = NULL;
            }
            piTPS -> Release();
            piTPS = NULL;
          }
          pISO = NULL;
        }
        // No more elements to Add in the HSO, notification is send
        // and HSO content can be highlighted.
        pHSO -> EndAddElements ();
        pHSO = NULL;
      }
      pEdt = NULL;
    }
    pPathTPS = NULL;
  }

  // Prepare the composition list  that will be displayed in the panel
  CATListValCATUnicodeString CompositionList;
  CATUnicodeString Line;

  if ( TTRSNodeCount )
  {
    Line.BuildFromNum (TTRSNodeCount, "%4d");
    Line.Append (" TTRS Node (Group of Surface)");
    CompositionList.Append(Line);
  }
  if ( TTRSSupportCount )
  {
    Line.BuildFromNum (TTRSSupportCount,"%4d");
    Line.Append (" TTRS Support (User Surface)");
    CompositionList.Append(Line);
  }
  if ( RGECount )
  {
    Line.BuildFromNum (RGECount, "%4d");
    Line.Append (" RGE (Geometrical Element)");
    CompositionList.Append(Line);
  }
  if ( FaceCount )
  {
    Line.BuildFromNum (FaceCount, "%4d");
    Line.Append (" Face(s)");
    CompositionList.Append(Line);
  }
  if ( EdgeCount )
  {
    Line.BuildFromNum (EdgeCount, "%4d");
    Line.Append (" Edge(s)");
    CompositionList.Append(Line);
  }
  if ( VertexCount )
  {
    Line.BuildFromNum (VertexCount, "%4d");
    Line.Append (" Vertex");
    CompositionList.Append(Line);
  }

  // Send CompositionList to the panel for Display
  _pPanel -> SetCompositionList (CompositionList);

  // Reset agent for next selection
  _pSelectionAgent -> InitializeAcquisition();

  return (TRUE);
}


//-----------------------------------------------------------------------------
// AnalyseTTRS
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryCmd::AnalyseTTRS (CATITTRS * ipiTTRS,
                                              CATHSO * ipHSO, 
                                              CATPathElement * ipPathTPS,
                                              int & oTTRSNodeCount,
                                              int & oTTRSSupportCount,
                                              int & oRGECount,
                                              int & oFaceCount,
                                              int & oEdgeCount,
                                              int & oVertexCount,
                                              CAT3DBagRep * iopRep)
{
  if ( ! ipiTTRS || !ipHSO || !ipPathTPS ) return (E_FAIL);

  HRESULT oRc = E_FAIL;

  // Retrieve TTRS nature: support or node.
  CATMmrTTRSType TTRSType = ipiTTRS -> GetNature ();

  // Retrieve the components of the TTRS
  CATLISTV(CATBaseUnknown_var) CompList;
  HRESULT rc = ipiTTRS -> GetComponents (CompList);
  if ( SUCCEEDED(rc) )
  {
    int ComponentCount = CompList.Size();
    int AnalyseSuccessCount = 0;

    CATBaseUnknown_var spBaseComp;

    // If TTRS is a node, components are TTRS
    if ( TTRSType == CATMmrNodeTTRS )
    {
      oTTRSNodeCount ++; // Increment node count

      // Iterate on TTRS components and analyse them
      CATITTRS * piTTRSComp = NULL;
      for ( int i = 1 ; i <= ComponentCount ; i++ )
      {
        spBaseComp = CompList[i];
        if ( NULL_var != spBaseComp )
        {
          rc = spBaseComp -> QueryInterface(IID_CATITTRS, (void**)&piTTRSComp);
          if ( SUCCEEDED(rc) )
          {
            rc = AnalyseTTRS (piTTRSComp, ipHSO, ipPathTPS,
                              oTTRSNodeCount, oTTRSSupportCount, oRGECount,
                              oFaceCount, oEdgeCount, oVertexCount, iopRep);
            if ( SUCCEEDED(rc) )
            {
              AnalyseSuccessCount++;
            }
            piTTRSComp -> Release();
            piTTRSComp = NULL;
          }
          spBaseComp = NULL_var;
        }
      }
    }
    else // If TTRS is a support, components are RGE
    {
      oTTRSSupportCount ++; // Increment support count

      // Iterate on RGE and analyse them
      CATIRGE * piRGE = NULL;
      for ( int i = 1 ; i <= ComponentCount ; i++ )
      {
        spBaseComp = CompList[i];
        if ( NULL_var != spBaseComp )
        {
          rc = spBaseComp -> QueryInterface (IID_CATIRGE, (void**)& piRGE);
          if ( SUCCEEDED(rc) )
          {
            rc = AnalyseRGE (piRGE, ipHSO, ipPathTPS,
                             oRGECount, 
                             oFaceCount, oEdgeCount, oVertexCount, iopRep);
            if ( SUCCEEDED(rc) )
            {
              AnalyseSuccessCount++;
            }
            piRGE -> Release();
            piRGE = NULL;
          }
          spBaseComp = NULL_var;
        }
      }
    }
    // method return S_OK only if each component is analysed successfuly
    if ( ComponentCount == AnalyseSuccessCount )
    {
      oRc = S_OK;
    }
  }
  return (oRc);
}


//-----------------------------------------------------------------------------
// AnalyseRGE
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryCmd::AnalyseRGE (CATIRGE * ipiRGE,
                                             CATHSO * ipHSO, 
                                             CATPathElement * ipPathTPS,
                                             int & oRGECount,
                                             int & oFaceCount,
                                             int & oEdgeCount,
                                             int & oVertexCount,
                                             CAT3DBagRep * iopRep)
{
  if ( ! ipiRGE || !ipHSO || !ipPathTPS || !iopRep) return (E_FAIL);

  HRESULT oRc = E_FAIL;

  oRGECount ++; // Increment RGE Count
  
  CATIRGETopology * piRGETopo = NULL;
  HRESULT rc = ipiRGE -> QueryInterface (IID_CATIRGETopology, 
                                         (void**)& piRGETopo);
  if ( SUCCEEDED(rc) )
  {
    CATLISTP (CATCell) * pCellList = NULL;
    rc = piRGETopo -> GetCells (&pCellList);
    if ( SUCCEEDED(rc) )
    {
      int CellCount = pCellList -> Size();
      for (int CellIdx = 1; CellIdx <= CellCount; CellIdx++)
      {
        CATCell * pCell = (*pCellList)[CellIdx];
        if ( pCell ) 
        {
          int CellDim = pCell -> GetDimension();
          switch ( CellDim )
          {
          case 0 : oVertexCount ++ ; break;
          case 1 : oEdgeCount ++ ; break;
          case 2 : // Cell is a Face
            {
              oFaceCount ++;
              CATFace * pFace = (CATFace*) pCell;
              CreatePointAndNormalRepresentationOnFace (pFace, piRGETopo,
                                                        ipPathTPS, iopRep);
              pFace = NULL;
            }
            break;
          }
          pCell -> Release();
          pCell = NULL;
        }
      }
      pCellList -> RemoveAll();
      delete pCellList;
      pCellList = NULL;
    }
    piRGETopo -> Release();
    piRGETopo = NULL;
  }

  // Highlight the geometry referenced by the RGE by placing its PathElement
  // in the HSO.
  CATIBuildPath * piBuildPath = NULL;
  rc = ipiRGE -> QueryInterface (IID_CATIBuildPath, (void**)&piBuildPath);  
  if ( SUCCEEDED(rc) )
  {
    CATPathElement * pPath = NULL;
    rc = piBuildPath -> ExtractPathElement (ipPathTPS, &pPath);
    if ( SUCCEEDED(rc) )
    {
      ipHSO -> AddElements (pPath);

      SpecialTreatementForPathWithSeveralLeaf (pPath, ipHSO);

      pPath -> Release();
      pPath = NULL;
    }
    piBuildPath -> Release();
    piBuildPath = NULL;
  }
  oRc = S_OK;
  return (oRc);
}


//-----------------------------------------------------------------------------
// SpecialTreatementForPathWithSeveralLeaf
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryCmd::SpecialTreatementForPathWithSeveralLeaf (
                                                    CATPathElement * ipPathRGE,
                                                    CATHSO * ipHSO)
{
  if ( !ipPathRGE || !ipHSO ) return (E_FAIL);

  // In Some Case for V4 Annotations the returned PathElement can
  // contains several leaf elements. In such case duplicate 
  // PathElements for each leaf in order to create separate PathElements
  ipPathRGE -> InitToLeafElement();
  ipPathRGE -> NextFatherElement();
  CATBaseUnknown * pElement = ipPathRGE -> NextRightElement();
  if ( pElement )  // More than one leaf in the PathElement
  {
    // Create a PathElement that does not contain the leafs of pPath
    CATPathElement * pPathWithoutLeafs = new CATPathElement;
    ipPathRGE -> InitToTopElement();
    CATBaseUnknown * pTop = ipPathRGE -> NextChildElement();
    CATBaseUnknown * pTopNext = ipPathRGE -> NextChildElement();
    while ( pTop && pTopNext )
    {
      pPathWithoutLeafs -> AddChildElement (pTop);

      pTop = pTopNext;
      pTopNext = ipPathRGE -> NextChildElement();
    }

    CATPathElement * pAdditionalPath = NULL;
    ipPathRGE -> InitToLeafElement ();
    ipPathRGE -> NextFatherElement ();
    pElement = ipPathRGE -> NextRightElement();
    while ( pElement )
    {
      pAdditionalPath = pPathWithoutLeafs -> Clone();
      if ( pAdditionalPath )
      {
        pAdditionalPath -> InitToLeafElement ();
        pAdditionalPath -> AddChildElement (pElement);
        ipHSO -> AddElements (pAdditionalPath);
        pAdditionalPath -> Release ();
        pAdditionalPath = NULL;
      }

      // Manage Next Leaf of pPath
      pElement = ipPathRGE -> NextRightElement ();
    }
    pPathWithoutLeafs -> Release();
    pPathWithoutLeafs = NULL;
  }
  return (S_OK);
}


//-----------------------------------------------------------------------------
// AddTTRSGeometryOnRepresentation
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryCmd::AddTTRSGeometryOnRepresentation (
                                                    CATITTRS * ipiTTRS,
                                                    CATPathElement * ipPathTPS,
                                                    CAT3DBagRep * iopRep)
{
  if ( !ipiTTRS || !ipPathTPS || !iopRep ) return (E_FAIL);

  // If display of TTRS is not required 
  if ( !_bDisplayTTRSRep ) return (S_OK);

  HRESULT oRc = E_FAIL;

  // Build TTRS Visualization
  CATITPS3DGeoVisu * piVisuTTRS = NULL;
  HRESULT rc = ipiTTRS -> QueryInterface (IID_CATITPS3DGeoVisu, 
                                          (void**)& piVisuTTRS);
  if ( SUCCEEDED(rc) )
  {
    CAT3DRep * pRepTTRS = (CAT3DRep*) piVisuTTRS -> BuildRep();
    if ( pRepTTRS ) 
    {
      // Retrieve transformation from product structure.
      CATIMovable * piMove = NULL;
      rc = ipPathTPS -> Search (IID_CATIMovable, (void**)& piMove);
      if ( SUCCEEDED(rc) )
      {
        CATMathTransformation AbsolutePos;
        rc = piMove -> GetAbsPosition(AbsolutePos);
        if ( SUCCEEDED(rc) )
        {
          CAT4x4Matrix PosMatrix;
          rc = GetMatrixFromTransfo (AbsolutePos, PosMatrix);
          if ( SUCCEEDED(rc) )
          {
            // Construct the following tree of rep
            // iopRep
            //   \
            //    pBagForTransfo => used to apply global position matrix
            //      \
            //       pRepTTRS 
            
            CAT3DBagRep * pBagForTransfo = new CAT3DBagRep();
            
            pBagForTransfo -> AddChild (*pRepTTRS);

            iopRep -> AddChild ((CAT3DRep&)*pBagForTransfo);

            pBagForTransfo -> SetMatrix(PosMatrix);

            // Force color of TTRS representation to purple
            pBagForTransfo -> SetColorRGBA ( 128, 0, 128);
            pBagForTransfo -> SetInheritanceMode (COLOR_INHERITANCE);

            oRc = S_OK;
          }
        }
        piMove -> Release();
        piMove = NULL;
      }
      pRepTTRS = NULL;
    }
    piVisuTTRS -> Release();
    piVisuTTRS = NULL;
  }
  return (oRc);
}


//-----------------------------------------------------------------------------
// CreatePointAndNormalRepresentationOnFace
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryCmd::CreatePointAndNormalRepresentationOnFace (
                                                  CATFace * ipFace,
                                                  CATIRGETopology * ipiRGETopo,
                                                  CATPathElement * ipPathTPS,
                                                  CAT3DBagRep * iopRep)
{
  if ( !ipFace || !ipiRGETopo || !ipPathTPS || !iopRep ) return (E_FAIL);
  
  // If display of grid is not required
  if ( !_bDisplay3DGrid ) return (S_OK);

  HRESULT oRc = E_FAIL;
  
  // Retrieve coefficient to direction along outside material side
  int Coefficient = 0;
  ipiRGETopo -> GetOutsideMaterialCoefficientOnNormal(&Coefficient);
  
  // Compute Transformation to take into account product position

  // First retrieve local transformation to apply on cells
  CATMathTransformation LocalPos;
  CATMathTransformation * pLocalPos = NULL;
  HRESULT rc = ipiRGETopo -> GetTransformation (&pLocalPos);
  if ( SUCCEEDED(rc) )
  {
    LocalPos = (*pLocalPos);

    delete pLocalPos;
    pLocalPos = NULL;
  }

  // Second retrieve transformation from product structure.
  CATMathTransformation AbsolutePos;
  CATIMovable * piMove = NULL;
  rc = ipPathTPS -> Search (IID_CATIMovable, (void**)& piMove);
  if ( SUCCEEDED(rc) )
  {
    piMove -> GetAbsPosition(AbsolutePos);

    piMove -> Release();
    piMove = NULL;
  }

  // Cumulate the two positions
  CATMathTransformation Position =  AbsolutePos * LocalPos;

  // Allocate a new rep for points and normals of that face
  CAT3DCustomRep * pPointsAndNormalsRep = new CAT3DCustomRep();

  CATSurface * pSurface = ipFace -> GetSurface();
  if ( pSurface )
  {
    const CATSurLimits * pSurLimits = ipFace -> Get2DBoundingBox();
    if ( pSurLimits && ! pSurLimits ->IsEmpty() )
    {
      double Umin = 0.0;
      double Umax = 0.0;
      double Vmin = 0.0;
      double Vmax = 0.0;
      pSurLimits -> GetExtremities(Umin, Vmin, Umax, Vmax);

      double Ucurrent = 0.0;
      double Vcurrent = 0.0;

      int GridResolution = 10;

      double FractionU = (Umax - Umin) / GridResolution;
      double FractionV = (Vmax - Vmin) / GridResolution;

      CATMathPoint PointOnSurface;
      CATMathDirection NormalAtPointOnSurface;
      CATSurParam InitialParam;
      CATMathPoint PointOnSurfacePos;
      CATMathDirection NormalAtPointOnSurfacePos;

      CATGeoFactory * pGeoFact = ipFace -> GetContainer();
      if ( pGeoFact )
      {
        // Create topological operator for checkinh that points are inside face
        CATSoftwareConfiguration * pSoftConfig =
                                          new CATSoftwareConfiguration(NULL,0);
        if ( pSoftConfig )
        {
          CATPositionPtFaceOperator * pPosPtFaceOpe
             = CATCreatePositionPtFaceOperator (pGeoFact,
                                                pSoftConfig,
                                                InitialParam,
                                                ipFace);
          if ( pPosPtFaceOpe )
          {
            for ( int IdxU = 0 ; IdxU <= GridResolution ; IdxU ++)
            {
              Ucurrent = Umin + FractionU * IdxU; // Increment U parameter

              for ( int IdxV = 0 ; IdxV <= GridResolution ; IdxV ++)
              {
                Vcurrent = Vmin + FractionV * IdxV; // Increment V parameter

                // Evaluate point and normal on surface              
                CATSurParam Param;
                pSurface -> CreateParam (Ucurrent, Vcurrent, Param);

                pSurface -> EvalPoint (Param, PointOnSurface);
                pSurface -> EvalNormal (Param, NormalAtPointOnSurface);

                // Check that point is inside Face Limits
                pPosPtFaceOpe -> SetSurParam (Param);
                pPosPtFaceOpe -> Run ();
              
                // If point is inside face limits, keep it for further treatement
                if ( CATLocationOuter != pPosPtFaceOpe-> GetOneResult() )
                {
                  // Orient direction along outside material side
                  if ( Coefficient != 0 )
                  {
                    NormalAtPointOnSurface *= Coefficient;
                  }
                
                  // Apply Transformation to take into account product position
                  PointOnSurfacePos = Position * PointOnSurface;
                  NormalAtPointOnSurfacePos = Position * NormalAtPointOnSurface;

                  // Create Representation of Point and normal and add it
                  // to the representation
                  CreateGraphicalPrimitives (pPointsAndNormalsRep, PointOnSurfacePos,
                                             NormalAtPointOnSurfacePos);
                }
              }
            }
            delete pPosPtFaceOpe;
            pPosPtFaceOpe = NULL;
          }
          pSoftConfig -> Release();
          pSoftConfig = NULL;
        }
        pGeoFact = NULL;
      }
      pSurLimits = NULL;
    }
    pSurface = NULL;
  }
  iopRep -> AddChild((*pPointsAndNormalsRep));

  return (oRc);
}


//-----------------------------------------------------------------------------
// CreateGraphicalPrimitives
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryCmd::CreateGraphicalPrimitives (
                                       CAT3DCustomRep * iopPointsAndNormalsRep, 
                                       CATMathPoint & iPointOnFace,
                                       CATMathDirection & iOusideMaterialDir)
{
  if ( !iopPointsAndNormalsRep ) return (E_FAIL);

  HRESULT oRc = S_OK;

  CATMathPointf Pointf = iPointOnFace;
  CATMathDirectionf Directionf = iOusideMaterialDir;

  float PointCoord [3];
  PointCoord [0] = Pointf.x;
  PointCoord [1] = Pointf.y;
  PointCoord [2] = Pointf.z;

  CATGraphicAttributeSet AttributePoint;
  AttributePoint.SetColor(YELLOW);

  CAT3DMarkerGP * pPointGP = new CAT3DMarkerGP (PointCoord);
  iopPointsAndNormalsRep -> AddGP(pPointGP, AttributePoint);

  iopPointsAndNormalsRep -> AddBoundingElement(
                                         CAT3DBoundingSphere(Pointf,0.f));

  CATGraphicAttributeSet AttributeArrow;
  AttributeArrow.SetColor(YELLOW);

  CAT3DArrowGP * pArrowGP = new CAT3DArrowGP (Pointf, Directionf, 
                                              10 /*Length in mm*/);

  iopPointsAndNormalsRep -> AddGP(pArrowGP, AttributeArrow);

  return (oRc);
}


//-----------------------------------------------------------------------------
// GetMatrixFromTransfo
//-----------------------------------------------------------------------------
HRESULT CAATpiAccessGeometryCmd::GetMatrixFromTransfo (
                                              CATMathTransformation & iTransfo,
                                              CAT4x4Matrix &oMatrix)
{
  HRESULT oRc = E_FAIL;

  CATMath3x3Matrix Matrix3x3;
  CATMathVector Vector;

  iTransfo.GetMatrix (Matrix3x3);
  iTransfo.GetVector (Vector);

  double Coeff[3][3];
  Matrix3x3.GetCoef (Coeff[0][0], Coeff[0][1], Coeff[0][2],
                     Coeff[1][0], Coeff[1][1], Coeff[1][2],
                     Coeff[2][0], Coeff[2][1], Coeff[2][2]);

  float ** ppRot = NULL;
  typedef float * pPointerFloat;
  ppRot = new pPointerFloat[3];
  int iRow = 0;
  for (; iRow < 3; iRow ++) 
  { 
    ppRot[iRow] = new float[3];
    for (int iCol = 0; iCol < 3; iCol ++)
    {
      ppRot[iRow][iCol] = (float)Coeff[iCol][iRow];
    }
  }

  oMatrix = CAT4x4Matrix ((const float**)ppRot, Vector);
  oRc = S_OK;

  for (iRow = 0; iRow < 3; iRow ++)
  {
    delete [] ppRot[iRow];
    ppRot[iRow] = NULL;
  }
  delete [] ppRot;
  ppRot = NULL;

  return (oRc);
}



