// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//  Abstract of the sample:
//  ----------------------
//   
//  Interactive command
//
//    Command to select a 3D annotation and then retrieve and highlight the 
//    geometry on which annotation is applied. The topological composition 
//    (faces and edges count) of the geometry is displayed in a panel.
//    A cloud of point is displayed on the faces. An arrow that indicate the
//    outside material side is also displayed.
//
//  Illustrates:
//
//    Using TPS (Technological Product Specifications) and Mechanical Modeler
//    interfaces to retrieve the geometry of a 3D Annotation. 
//    The main APIs used here  are CATITPS, CATITTRS, CATIRGE and
//    CATIRGETopology.
//
//=============================================================================
//  Usage:
//  ------
//
//  Build the fw containing that command and create run time view.
//  Start CATIA V5
//  Menu Start + Mechanical Design + Functional Tolerancing & Annotation
//  Menu : View + Toolbar + CAA Samples to make the toolbar appear.
//  "Access Geometry" command can be launched from the toolbar.
//
//  Notice that the toolbar CAA Samples is also available in the following 
//  workbenches :
//   Mechanical Design + Product Fonctionnal Tolerancing & Annotations
//   DPM Powertrain + Process Tolerancing & Annotations
//
//=============================================================================

#ifndef CAATpiAccessGeometryCmd_H
#define CAATpiAccessGeometryCmd_H

#include "CATStateCommand.h"

class CATCommand;
class CATNotification;
class CATPathElementAgent;
class CATDialogAgent;
class CAATpiAccessGeometryWnd;
class CATITTRS;
class CATIRGE;
class CATHSO;
class CATPathElement;
class CATModelForRep3D;
class CATFace;
class CAT3DBagRep;
class CAT3DCustomRep;
class CATIRGETopology;
class CATMathPoint;
class CATMathDirection;
class CATMathTransformation;
class CAT4x4Matrix;

//-----------------------------------------------------------------------------
class CAATpiAccessGeometryCmd : public CATStateCommand
{
  CmdDeclareResource (CAATpiAccessGeometryCmd, CATStateCommand)

  public:

    CAATpiAccessGeometryCmd ();
    virtual ~CAATpiAccessGeometryCmd ();

    virtual void BuildGraph ();
    virtual CATStatusChangeRC Cancel (CATCommand * ipCmd,
                                      CATNotification * ipNotif);

    boolean OnAnnotationSelected (void * ipData);

  private:
    // must not be implemented for command
    CAATpiAccessGeometryCmd (CAATpiAccessGeometryCmd &);
    CAATpiAccessGeometryCmd& operator=(CAATpiAccessGeometryCmd&);

    HRESULT AnalyseTTRS (CATITTRS * ipiTTRS,
                         CATHSO * ipHSO,             // for highlighting 
                         CATPathElement * ipPathTPS,
                         int & oTTRSNodeCount,       // for composition dump
                         int & oTTRSSupportCount,
                         int & oRGECount,
                         int & oFaceCount,
                         int & oEdgeCount,
                         int & oVertexCount,
                         CAT3DBagRep * iopRep);

    HRESULT AnalyseRGE (CATIRGE * ipiRGE, 
                        CATHSO * ipHSO,             // for highlighting 
                        CATPathElement * ipPathTPS,
                        int & oRGECount,            // for composition dump
                        int & oFaceCount,
                        int & oEdgeCount,
                        int & oVertexCount,
                        CAT3DBagRep * iopRep);


    HRESULT SpecialTreatementForPathWithSeveralLeaf(CATPathElement * ipPathRGE,
                                                    CATHSO * ipHSO);

    HRESULT AddTTRSGeometryOnRepresentation (CATITTRS * ipiTTRS,
                                             CATPathElement * ipPathTPS,
                                             CAT3DBagRep * iopRep);
    HRESULT CreatePointAndNormalRepresentationOnFace (
                                                  CATFace * ipFace,
                                                  CATIRGETopology * ipiRGETopo,
                                                  CATPathElement * ipPathTPS,
                                                  CAT3DBagRep * iopRep);

    HRESULT CreateGraphicalPrimitives (CAT3DCustomRep * iopPointsAndNormalsRep,
                                       CATMathPoint & iPointOnSurface,
                                       CATMathDirection & iOusideMaterialDir);
    HRESULT  GetMatrixFromTransfo (CATMathTransformation & iTransfo,
                                   CAT4x4Matrix &oMatrix);

    CATPathElementAgent     * _pSelectionAgent;
    CATDialogAgent          * _pClosePanelAgent;
    CAATpiAccessGeometryWnd * _pPanel;

    CATModelForRep3D        * _pModelObjectForAdditionalRep;
    CATBoolean                _bDisplay3DGrid;
    CATBoolean                _bDisplayTTRSRep;

};
#endif
