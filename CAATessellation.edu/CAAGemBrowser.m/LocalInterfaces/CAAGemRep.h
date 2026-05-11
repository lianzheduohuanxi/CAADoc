#ifndef CAAGemRep_h
#define CAAGemRep_h
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
//=============================================================================
//
//  Class to creates the graphical representation of the geometric objects
//
//=============================================================================

// Mathematics
class CATMathPoint ;             //  mathematical point
// GeometricObjects Framework
class CATGeometry;               // geometric object
class CATGeoFactory;             // geometry factory
class CATPlane;                  // geometric plane
class CATLine;                   // geometric line
class CATCurve;                  // geometric curve

// Topology
#include "CATTopDefine.h"        // for CATSide
class CATBody;                   // Body
class CATEdge ;                  // Edge

// Tessellation to recover the results of a tessellation operator
class CATTessPointIter;         
class CATTessStripeIter;
class CATTessFanIter;
class CATTessPolyIter;
class CATTessTrianIter;  

// GeometryVisualization
class CAT3DRep;

// System
#include "CATDataType.h"
#include "CATBoolean.h"
 
class CAAGemRep 
{

  public:
    CAAGemRep(CATGeoFactory * ipiGeomFactory, double iSag);
    ~CAAGemRep();

    //  Creates the graphical representation of a geometric object
    void CreateRep(CATGeometry * ipiToView, CAT3DRep *& iopRep);

    //  Creates the graphical representation of a body
    void CreateBodyRep(CATBody * ipiBody, CAT3DRep *& iopRep);  


    //  Creates the graphical representation of a face
    //  The arguments are the output of the tessellation cell or body operators
    void CreateSurfaceRep(CATBoolean          iPlane,
                          CATSide             iSide, 
                          CATTessPointIter  * iPoints,
                          CATTessStripeIter * iStrips,
                          CATTessFanIter    * iFans,
                          CATTessPolyIter   * iPolygons,
                          CATTessTrianIter  * iTriangles,
                          CAT3DRep *& iopRep);


    //  Creates the graphical representation of a plane
    void CreatePlaneRep(CATPlane *piPlane, CAT3DRep *& iopRep);


    //  Creates the graphical representation of an edge
    //  The arguments are the output of the tessellation cell or body operator
    void CreateEdgeRep  (CATEdge * ipiEdge, CATLONG32 & ioNumOfPoints, float * oaPoints, CAT3DRep *& iopRep);

    //  Creates the graphical representation of a curve that is not a line
    //  The arguments are the output of the tessellation cell or body operator
    void CreateCurveRep  (CATLONG32 & ioNumOfPoints, float * oaPoints, CAT3DRep *& iopRep);

    //  Creates the graphical representation of a line
    void CreateLineRep(CATLine *piLine, CAT3DRep *& iopRep);

    //  Creates the graphical representation of a point
    void CreatePointRep  (CATMathPoint & iPoint,CAT3DRep *& iopRep);

  private:

    // 
    // Default constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAGemRep ();

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAGemRep(const CAAGemRep &iObjectToCopy);

    // The geometry factory from which the objects are visualized
    CATGeoFactory * _piGeomFactory;

    // The tessellation sag
    float          _sag;
};
#endif
