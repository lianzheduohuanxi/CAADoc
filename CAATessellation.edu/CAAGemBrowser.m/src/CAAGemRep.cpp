/**
* @quickReview CRE 04:04:22
*/
//=============================================================================
//
// COPYRIGHT DASSAULT SYSTEMES  2000
//
//=============================================================================

// Local Framework
#include "CAAGemRep.h"

// Mathematics Framework
#include "CATMathPlane.h"              // mathematical plane
#include "CATMathLine.h"               // mathematical line
#include "CATMathPoint.h"              // mathematical point
#include "CATMathPointf.h"             // floating point for the visualization
#include "CATMathVectorf.h"            // floating vector for the visualization

// GeometricObjects Framework
#include "CATGeoFactory.h"             // geometry factory
#include "CATGeometry.h"               // geometric object
#include "CATSurface.h"                // surface
#include "CATPlane.h"                  // geometric plane
#include "CATCurve.h"                  // geometric curve
#include "CATLine.h"                   // geometric line
#include "CATPoint.h"                  // geometric point
#include "CATPointOnEdgeCurve.h"       // Point on edge curve (poec)
#include "CATCrvParam.h"               // parameters on a curve
#include "CATCrvLimits.h"              // limits of a curve
#include "CATSurLimits.h"              // limits of a curve

// Topology
#include "CATBody.h"                   // Body
#include "CATFace.h"                   // Face
#include "CATEdge.h"                   // Edge
#include "CATVertex.h"                 // Vertex
#include "CATDomain.h"                 // Domain

// Tessellation
#include "CATCurveTessellator.h"       // Curve tessellator
#include "CATSurfaceTessellator.h"     // Surface tessellator
#include "CATCellTessellator.h"        // Cell tessellator
#include "CATTessPointIter.h"          // Result of the tessellation: the points
#include "CATTessStripeIter.h"         // Result of the tessellation: the stripe
#include "CATTessPolyIter.h"           // Result of the tessellation: the polygons
#include "CATTessTrianIter.h"          // Result of the tessellation: the triangles 
#include "CATTessFanIter.h"         
#include "CATSurfacicRep.h"         

// GeometryVisualization
#include "CAT3DBagRep.h"                
#include "CAT3DPlanarFaceGP.h"          
#include "CAT3DFaceGP.h"
#include "CAT3DPolylineGP.h"
#include "CAT3DPointRep.h"
#include "CAT3DCurveRep.h"
#include "CAT3DLineRep.h"
#include "CAT3DFixedArrowGP.h"
#include "CAT3DPlanRep.h"
#include "CAT3DCustomRep.h"
#include "CATGraphicAttributeSet.h"
#include "CAT3DBoundingSphere.h"
 
// System
#include "CATErrorMacros.h"

// out
#include <iostream.h>

//------------------------------------------------------------------------------
// ***********************************  CONSTRUCTOR
//------------------------------------------------------------------------------
CAAGemRep::CAAGemRep(CATGeoFactory * ipiGeomFactory, double iSag)
{
   _piGeomFactory = ipiGeomFactory;
   _sag=iSag;
}
CAAGemRep::~CAAGemRep()
{
	_piGeomFactory = NULL;
}

//------------------------------------------------------------------------------
// ***********************************  Geometry
//------------------------------------------------------------------------------
void CAAGemRep::CreateRep(CATGeometry * ipiToView, CAT3DRep *& iopRep)
{

  if (NULL!= ipiToView)
  {
    //
    // ------ Body visualization
    if (0!=ipiToView->IsATypeOf(CATBodyType)) 
    { 
       CATBody * piBody=(CATBody * )ipiToView;
       CreateBodyRep(piBody,iopRep);
    }

    //
    // ------ Curve visualization
    else if (0!=ipiToView->IsATypeOf(CATCurveType))
    {
       if (0== ipiToView->GetUseCount())      // to only visualize alone curves
       {
         
         // ------ Line
         if (0!=ipiToView->IsATypeOf(CATLineType))
         {
            CATLine * piLine=(CATLine*)ipiToView;
            CreateLineRep(piLine,iopRep);    
              
         }
         else

         // ------ other curves   --> use a curve tessellator to create a body
         {   
            CATCurve * piCurve = (CATCurve * )ipiToView;
			if (NULL == piCurve) return ;

            // Is the curve a curve or a point? 
            // Gets the bounding box of its current limits.
            CATMathBox boundingBox;
            CATCrvLimits limits;
            piCurve->GetLimits(limits);
            piCurve->GetBox(limits,boundingBox);
            CATMathPoint low,high;
            boundingBox.GetLowLimit(low);
            boundingBox.GetHighLimit(high);
            CATMathVector diagonal=high-low;
            double diagonalLength= diagonal.Norm();

            // really a curve to visualize
			if (NULL == _piGeomFactory) return ;
            if ( diagonalLength > _piGeomFactory->GetResolution() )
            {     
              CATCurveTessellator * pCurveTess = new CATCurveTessellator(_sag);
              if (NULL!=pCurveTess)
              {
                
                pCurveTess -> AddCurve(piCurve, limits);
                pCurveTess -> Run();
              
                // Retrieves the tessellation results
                CATLONG32  numOfPoints;
                float * aPoints= NULL;
                pCurveTess-> GetCurve (piCurve, numOfPoints, &aPoints);

                // Creates the rep
                CreateCurveRep (numOfPoints,aPoints,iopRep);

                delete pCurveTess;
                pCurveTess=NULL;
              } 
            }
            // The curve is a point
            else
            {
              CATCrvParam crvParam;
              piCurve->GetStartLimit(crvParam);
              CATMathPoint pt;
              piCurve->Eval(crvParam, CATCrvEvalCommand::EvalPoint, &pt);
              CreatePointRep(pt,iopRep);
            }
         }
       }
    }

    //
    // ------ Surface
    else if (0!=ipiToView->IsATypeOf(CATSurfaceType))
    {
       CATSurface * piSurface = (CATSurface * )ipiToView;
	   if (NULL==piSurface) return;
       // only visualizes surfaces that are not pointed to
        if (0== ipiToView->GetUseCount())
        {     
         // Plane
         if(ipiToView->IsATypeOf(CATPlaneType))
         {
            CATPlane * piPlane=(CATPlane*)ipiToView;
            CreatePlaneRep(piPlane,iopRep);
         }
         else

         // Other surfaces --> use a surface tessellator to create a body
         {
           // Creates the operator 
           CATSurLimits limits;
           piSurface->GetLimits(limits);
           CATSurfaceTessellator * pSurfTess = new CATSurfaceTessellator(_sag);
           if (NULL!=pSurfTess)
           {
             pSurfTess -> AddSurface(piSurface, limits);
             pSurfTess -> Run();
              
             CATBoolean isPlanar;
             CATTessPointIter *    pPoints    = NULL;
             CATTessStripeIter *   pStrips    = NULL;
             CATTessFanIter *      pFans      = NULL;
             CATTessPolyIter *     pPolygons  = NULL;
             CATTessTrianIter *    pTriangles = NULL;
     
             pSurfTess -> GetSurface(piSurface,isPlanar,&pPoints,&pStrips,&pFans,&pPolygons,&pTriangles);
             CATSide side=CATSideUnknown;
             CreateSurfaceRep(isPlanar,side, pPoints, pStrips,pFans, pPolygons, pTriangles,iopRep);
              
             delete pSurfTess;
             pSurfTess=NULL;
           }
         } 
       }
    }
    //
    // Point
    else if (0!=ipiToView->IsATypeOf(CATPointType))
    {
       if (0== ipiToView->GetUseCount())
       {
          CATPoint * piPoint = (CATPoint*)ipiToView;
		  if (piPoint == NULL) return;
          CATMathPoint point;
          piPoint->GetMathPoint(point);
          CreatePointRep(point,iopRep);
       }
    }
  }  
}


//------------------------------------------------------------------------------
// ***********************************  BODY
//------------------------------------------------------------------------------
void CAAGemRep::CreateBodyRep(CATBody * ipiBody, CAT3DRep *& iopRep)  
{
 //
 // ------ Tessellates
 // 
	if (ipiBody == NULL) return;
 iopRep=NULL;
 CAT3DBagRep* pBagRep = NULL;

 CATCellTessellator * pTessellator = new CATCellTessellator(_sag);
 

 if (NULL!=pTessellator)
 {
 
   CATLISTP(CATCell) cells;
   ipiBody->GetAllCells( cells,2); 
   int numberOfCells = cells.Size();
  
   int ifa = 1;
for (; ifa<=numberOfCells ; ifa++)
   {
     pTessellator->AddFace((CATFace *)(cells[ifa]));
   }
   pTessellator -> Run();
 
   //-------------------------------------------------- 
   // for each face, retrieve the tessellation results.
   //-------------------------------------------------- 
  
   for (ifa=1 ; ifa<=numberOfCells ; ifa++)
   { 
   
     CATFace * piFace = (CATFace*) cells[ifa]; 
	 if (NULL == piFace) return;
     
     // a special visualization for infinite face
     if (TRUE== piFace->GetInfinite())
     {
       CATOrientation ori;
       CATGeometry*    piGeom= piFace->GetGeometry(&ori);
       if (NULL!= piGeom && piGeom->IsATypeOf(CATPlaneType) )
       {
          CATPlane * piPlane = (CATPlane *)piGeom;      
          CAT3DRep* pRep=NULL;
          CreatePlaneRep(piPlane,pRep);
          if (NULL!=pRep)
          {
            if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
            pBagRep->AddChild(*pRep);
          }
       }
     }
     else
     {
       CATBoolean isPlanar;
       CATTessPointIter *    pPoints  = NULL;
       CATTessStripeIter *   pStrips    = NULL;
       CATTessFanIter *      pFans      = NULL;
       CATTessPolyIter *     pPolygons  = NULL;
       CATTessTrianIter *    pTriangles = NULL;
       short side;
     
       pTessellator -> GetFace(piFace,isPlanar,&pPoints,&pStrips,&pFans,&pPolygons,&pTriangles,&side);
       CAT3DRep * pRep=NULL;
       CreateSurfaceRep(isPlanar,side, pPoints, pStrips,pFans, pPolygons, pTriangles,pRep); 
       
       if (NULL!=pRep)
       {
          if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
          pBagRep->AddChild(*pRep);
       }
     }

   }
   delete pTessellator;
   pTessellator = NULL;
 }

 //-------------------------------------------------- 
 // Only tessellate the wire domains (not the edges of faces)
 //-------------------------------------------------- 
 // the number of domains
 CATLONG32 nbDomains= ipiBody->GetNbDomains();
 CATLISTP(CATCell)  cells;
 int numberOfCells =0;

 for (int dom = 1;dom<=nbDomains;dom++)
 {
   CATDomain * piDomain = ipiBody->GetDomain( dom );
    
   // ------ Wire
   if (NULL!=piDomain && 1==(piDomain->IsATypeOf(CATWireType)) )
   {
     // Creates a cell tessellator
     pTessellator = new CATCellTessellator(_sag); 
     if (pTessellator!=NULL)
     {
       // Retrieves the number of edges of the wire
       cells.RemoveAll();
       piDomain->GetAllCells(cells,1);
       numberOfCells = cells.Size();
       
       // Adds the edges to tessellate
       int i = 1;
for  (; i<=numberOfCells ; i++)
       { 
         CATEdge * piEdge = (CATEdge*) cells[i];
         pTessellator -> AddEdge(piEdge);
       }

       // Runs it
       pTessellator->Run();

       
       // for each each edge 
       for  ( i=1 ; i<=numberOfCells ; i++)
       { 
         CATEdge * piEdge = (CATEdge*) cells[i];
         CATLONG32  numOfPoints;
         float   * aPoints= NULL;
         
         // Retrieves the tessellation results
         pTessellator -> GetEdge(piEdge,numOfPoints,&aPoints);

         CAT3DRep * pRep=NULL;

         // Creates the rep 
         CreateEdgeRep (piEdge, numOfPoints,aPoints,pRep);
         if (NULL!=pRep)
         {
           if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
           pBagRep->AddChild(*pRep);
         }

       }
       delete pTessellator;
       pTessellator = NULL;
     }
   }

   //  ----- and the points
   else if(NULL!=piDomain && 1==(piDomain->IsATypeOf(CATVertexInVolumeType)))
   {
     
     CATCell * piCell = piDomain->GetCell(1);
     if (NULL!=piCell) 
     {
       CATVertex * piVertex=(CATVertex * )piCell;
	   if (NULL == piVertex) return;

       // Gets the geometry of the vertex
       CATPoint * piPoint = piVertex->GetPoint();
	 
       // Creates the rep
       CAT3DRep * pRep=NULL;
       CATMathPoint point;
       piPoint->GetMathPoint(point);
       CreatePointRep  (point,pRep);
       if (NULL!=pRep)
       {
          if (NULL== pBagRep) pBagRep = new CAT3DBagRep();
          pBagRep->AddChild(*pRep);
       }

     }	
   }
 }
  
 // Returns the rep
 iopRep=pBagRep;
 }


//------------------------------------------------------------------------------
// ***********************************  Surface
//------------------------------------------------------------------------------
void CAAGemRep::CreateSurfaceRep(CATBoolean          iPlane,
                                 CATSide             iSide, 
                                 CATTessPointIter  * iPoints,
                                 CATTessStripeIter * iStrips,
                                 CATTessFanIter    * iFans,
                                 CATTessPolyIter   * iPolygons,
                                 CATTessTrianIter  * iTriangles,
                                 CAT3DRep *& iopRep)
{
  if ( iPoints==NULL || iStrips==NULL || iFans==NULL || iPolygons==NULL || iTriangles==NULL ) return;

  float
    *vertices=NULL,
    *normals =NULL;
  int 
    *triangleIndice     =NULL,
    *triangleStripIndice=NULL,
    *triangleFanIndice  =NULL ;
  int
    *nbVertexPerTriangleStrip=NULL,
    *nbVertexPerTriangleFan=NULL ;
  int verticesArraySize=0,normalsArraySize=0;
  int j,k,NuPts[3],ori=0 ;
  CATBoolean boolean ;
  // 
  // Recherche des normales - 
  // dans le cas ou le fond est plan on ne recherche qu'une normale unique pour
  // utiliser ulterieurement la primitive graphique adhoc
  //
  CATLONG32 NumberOfPoints = iPoints ? iPoints->GetNbPoint() : 0 ;
  if (NumberOfPoints == 0)
    return;

  verticesArraySize = NumberOfPoints*3 ;
  vertices = new float [verticesArraySize];
  float xmin=1.e+10,ymin=1.e+10,zmin=1.e+10,xmax=-1.e+10,ymax=-1.e+10,zmax=-1.e+10;

  if ( (iSide != CATSideLeft) && ( iSide != CATSideRight) ) {
    ori = 1 ; // to avoid zero normal 
  } else {
    ori = - iSide ;
  }

  const CATMathVector * vector=NULL ;
  if (iPlane ) {
    normalsArraySize = 3 ;
    normals = new float [normalsArraySize];
    // on recupere n'importe quelle normale 
    boolean = iPoints->GetPointNor(vector); 
    if ( boolean && vector) {
      // on est sur que vector n'est pas nul
      normals[0] = (float) vector->GetX()*ori ;
      normals[1] = (float) vector->GetY()*ori ;
      normals[2] = (float) vector->GetZ()*ori ;
    } else { 
      // normale non calculee par le maillage 
      normals[0] = 1.0 ;
      normals[1] = 0.0 ;
      normals[2] = 0.0 ;
    }
  } else {
    normalsArraySize = verticesArraySize ;
    normals = new float [normalsArraySize];
  }

  double const  * ptd;   
  while ( iPoints->IsExhausted()==0 ) {
    ptd    = iPoints->GetPointXyz();
    CATLONG32 i = 3 * iPoints->GetPointNu();
    vertices[i  ] = (float) ptd[0] ;
    vertices[i+1] = (float) ptd[1] ;
    vertices[i+2] = (float) ptd[2] ;

    if (xmin > vertices[i  ]) xmin=vertices[i  ];
    if (ymin > vertices[i+1]) ymin=vertices[i+1];
    if (zmin > vertices[i+2]) zmin=vertices[i+2];
    if (xmax < vertices[i  ]) xmax=vertices[i  ];
    if (ymax < vertices[i+1]) ymax=vertices[i+1];
    if (zmax < vertices[i+2]) zmax=vertices[i+2];

    if (!iPlane) { 
      boolean = iPoints->GetPointNor(vector);
      if ( boolean &&  vector)
      {
        // on est sur que vector n'est pas nul
        if (ori<0) {
          normals[i+0] = (float) -vector->GetX() ;
          normals[i+1] = (float) -vector->GetY() ;
          normals[i+2] = (float) -vector->GetZ() ;
        } else {
          normals[i+0] = (float) vector->GetX() ;
          normals[i+1] = (float) vector->GetY() ;
          normals[i+2] = (float) vector->GetZ() ;
        }
      } else {
        // normale non calculee par le maillage 
        normals[i+0] = 1.0 ;
        normals[i+1] = 0.0 ;
        normals[i+2] = 0.0 ;
      }
    }

    iPoints->GoToNext();
  }

  //
  // ALlocation des tableaux
  //
  CATLONG32 NumberOfTriangles = iTriangles->GetNbTrian();
  CATLONG32 NbTotalPointStrip=0;
  CATLONG32 NumberOfStrips    = iStrips->GetNbStri(NbTotalPointStrip) ; 
  CATLONG32 NbTotalPointFan=0;
  CATLONG32 NumberOfFans      = iFans->GetNbFan(NbTotalPointFan) ; 


  if ( NumberOfTriangles || ((NumberOfStrips)&&(ori <0))  )
  {
    if ((NumberOfStrips)&&(ori <0))
      triangleIndice = new int [3 * (NumberOfTriangles+NumberOfStrips) ] ;
    else
      triangleIndice = new int [3 * NumberOfTriangles] ;
  }

  if ( NumberOfStrips ) 
  {
    nbVertexPerTriangleStrip = new int [NumberOfStrips] ;
    triangleStripIndice = new int [NbTotalPointStrip] ;
  }

  if ( NumberOfFans )
  {
    nbVertexPerTriangleFan = new int [NumberOfFans] ;
    triangleFanIndice = new int [NbTotalPointFan] ;
  }

  //
  // Recherche des triangles
  //
  if ( NumberOfTriangles ) {
    CATLONG32 i = 0 ;
    while ( iTriangles->IsExhausted()==0 ) {
      iTriangles->GetTrianNuPts(NuPts);

      if (ori <0) {
        // cout << "inversion triangle" << endl;
        triangleIndice[i]   =  NuPts[2]*3 ;
        triangleIndice[i+1] =  NuPts[1]*3 ;
        triangleIndice[i+2] =  NuPts[0]*3 ;
      } else {
        triangleIndice[i]   = NuPts[0]*3 ;
        triangleIndice[i+1] = NuPts[1]*3 ;
        triangleIndice[i+2] = NuPts[2]*3 ;
      }

      i += 3 ;
      iTriangles->GoToNext();
    }
  }


  //
  // Recuperation des trianglestrips
  //
  if ( NumberOfStrips ) {
    CATLONG32 i = 0 ;
    j = 0 ;
    while ( iStrips->IsExhausted()==0 ) {

      int NbPts = nbVertexPerTriangleStrip[i] = iStrips->GetStriNbPts(); 
      iStrips ->GetStriNuPts( &(triangleStripIndice[j]) ) ;


      for ( k=0 ; k < NbPts ; k++ ) {
        triangleStripIndice[j+k] *= 3 ;
      }

      if (ori <0) 
      {
        // strip pair : on enleve le dernier triangle en le mettant dans le paquet des simples
        //              pour se ramener au scenario des strips impairs
        if ( 0 == (NbPts%2) )
        {
          CATLONG32 ii = NumberOfTriangles*3 ;

          triangleIndice[ii]   =  triangleStripIndice[j+NbPts-1] ;
          triangleIndice[ii+1] =  triangleStripIndice[j+NbPts-3] ;
          triangleIndice[ii+2] =  triangleStripIndice[j+NbPts-2] ;

          NumberOfTriangles++;

          NbPts = nbVertexPerTriangleStrip[i] = NbPts-1;
        }

        // strip impair : permutation inverse   
        for (int l=0; l<(NbPts>>1); l++)
        {
          int tmp = triangleStripIndice[j+l];
          triangleStripIndice[j+l  ] = triangleStripIndice[j+NbPts-1-l];
          triangleStripIndice[j+NbPts-1-l] = tmp;
        }

      }
      j += NbPts ;
      i += 1;
      iStrips->GoToNext();
    }
  }  


  //
  // Recuperation trianglefans
  //  
  if ( NumberOfFans ) {
    CATLONG32 i = 0 ;
    j = 0 ;
    while ( iFans->IsExhausted()==0 ) {
      nbVertexPerTriangleFan[i] = iFans->GetFanNbPts(); 
      iFans ->GetFanNuPts( &(triangleFanIndice[j]) ) ;
      for ( k=0 ; k < nbVertexPerTriangleFan[i] ; k++ ) {
        triangleFanIndice[j+k] *= 3 ;
      }

      if (ori <0) {
        // cout << "inversion Fan" << endl;
        int NbPts = nbVertexPerTriangleFan[i];
        for ( int l=1; l<=(NbPts-1)/2; l++) {
          int i1 = triangleFanIndice[j+l];
          triangleFanIndice[j+l] = triangleFanIndice[j+NbPts-l];
          triangleFanIndice[j+NbPts-l] = i1 ;
        }
      }
      j += nbVertexPerTriangleFan[i] ;
      i += 1;
      iFans->GoToNext();
    }
  }  

  //
  // Creation des primitives graphiques et rattachement a la representation surfacique de la face
  //
  CAT3DFaceGP * faceGP = NULL;
  if ( iPlane )
    faceGP = new CAT3DPlanarFaceGP(vertices,verticesArraySize,normals,
    triangleIndice,NumberOfTriangles,
    triangleStripIndice,NumberOfStrips,nbVertexPerTriangleStrip,
    triangleFanIndice,NumberOfFans,nbVertexPerTriangleFan);

  else
    faceGP = new CAT3DFaceGP(vertices,verticesArraySize,
    normals,normalsArraySize,
    triangleIndice,NumberOfTriangles, 
    triangleStripIndice, NumberOfStrips, nbVertexPerTriangleStrip,
    triangleFanIndice,NumberOfFans,nbVertexPerTriangleFan);

  delete [] vertices;
  delete [] normals;
  if (triangleIndice)           delete [] triangleIndice ;
  if (triangleStripIndice)      delete [] triangleStripIndice ;
  if (nbVertexPerTriangleStrip) delete [] nbVertexPerTriangleStrip ;
  if (triangleFanIndice )       delete [] triangleFanIndice ;
  if (nbVertexPerTriangleFan )  delete [] nbVertexPerTriangleFan ;

  CATSurfacicRep * SurfacicRep = new CATSurfacicRep();
  CATGraphicAttributeSet * ag  = new CATGraphicAttributeSet();
  ag->SetType(2);
  SurfacicRep->AddGeomFace(faceGP,ag);

  // Recuperation du volume d'encombrement
  CATMathPointf Center(float((xmin+xmax)/2.),
    float((ymin+ymax)/2.),
    float((zmin+zmax)/2.));
  double BoundingSphereRadius= sqrt((xmax-xmin)*(xmax-xmin)+
    (ymax-ymin)*(ymax-ymin)+
    (zmax-zmin)*(zmax-zmin))/2.;

  CAT3DBoundingSphere BoundingSphere( Center, float(BoundingSphereRadius));
  SurfacicRep->SetBoundingElement(BoundingSphere);

  iopRep = SurfacicRep;
  if (SurfacicRep)
  {
  SurfacicRep->Destroy();
  SurfacicRep = NULL;
  }
}
//------------------------------------------------------------------------------
// ***********************************  Plane
//------------------------------------------------------------------------------
 void CAAGemRep::CreatePlaneRep(CATPlane *piPlane, CAT3DRep *& iopRep)
{
  CATMathPlane plane;
  if (NULL == piPlane) return;

  // Gets the mathematical definition
  piPlane->GetAxis(plane);

  //CATMathPoint      center = plane.GetOrigin();
  //CATMathDirection  vAxis  = plane.GetSecondDirection();
  //CATMathDirection  uAxis  = plane.GetFirstDirection();
  CATMathPoint center;
  plane.GetOrigin(center);
  CATMathDirection vAxis, uAxis;
  plane.GetSecondDirection(vAxis);
  plane.GetFirstDirection(uAxis);
  CATMathPointf     origin((float) center.GetX(), (float) center.GetY(), (float) center.GetZ());
  CATMathDirectionf u((float) uAxis.GetX(), (float) uAxis.GetY(), (float) uAxis.GetZ());
  CATMathDirectionf v((float) vAxis.GetX(), (float) vAxis.GetY(), (float) vAxis.GetZ());
  
  // Creates the rep 
  float size = 40.f;
  CAT3DPlanRep *pRep = new CAT3DPlanRep(origin,u,v,size);

  float radius  = 35.f;
  CAT3DBoundingSphere pBe(origin,0.f,radius);
  pRep->SetBoundingElement(pBe);
  
  // Returns the rep
  iopRep = pRep;
}

//------------------------------------------------------------------------------
// ***********************************  Edge
//------------------------------------------------------------------------------
void CAAGemRep::CreateEdgeRep  (CATEdge * ipiEdge, CATLONG32 & ioNumOfPoints, float * oaPoints, CAT3DRep *& iopRep)
{
  CAT3DRep *pRep = NULL;
  if (NULL == ipiEdge) return;
  	   
  CATMathBox boundingBox;
  CATMathPoint low,high;
  
  ipiEdge->GetBoundingBox(boundingBox);
  boundingBox.GetLowLimit(low);
  boundingBox.GetHighLimit(high);
  CATMathVector diagonal=high-low;
  double diagonalLength= diagonal.Norm();
  if (NULL == _piGeomFactory) return;
  if ( diagonalLength > _piGeomFactory->GetResolution() )
  {		     		
     CreateCurveRep (ioNumOfPoints,oaPoints,pRep);
  }
  // The edge is a point
  else
  {
    //Gets the coordinates of a point
    CATPointOnEdgeCurve *piStartPoec=NULL;
    ipiEdge->GetVerticesPointsOnEdgeCurve(&piStartPoec,NULL );
    CATMathPoint pt;
    if (NULL!=piStartPoec) 
    {
        piStartPoec->GetMathPoint(pt);
        CreatePointRep(pt,pRep);
    }
  }

  // Returns the rep
  iopRep = pRep;
}

//------------------------------------------------------------------------------
// ***********************************  Curve
//------------------------------------------------------------------------------
void CAAGemRep::CreateCurveRep  (CATLONG32 & ioNumOfPoints, float * oaPoints, CAT3DRep *& iopRep)
{
  CAT3DCurveRep*   pCurveRep = NULL;
  	   
  

  // Creates the rep
  CAT3DPolylineGP* polylineGP = new CAT3DPolylineGP(oaPoints, ioNumOfPoints, 1);
  pCurveRep  = new CAT3DCurveRep();
  pCurveRep->AddWireframeLOD(0,polylineGP, _sag);

  // Defines the bounding box
  float xmin=1.e+10,ymin=1.e+10,zmin=1.e+10,xmax=-1.e+10,ymax=-1.e+10,zmax=-1.e+10;
  for (int j=0, curj=0; j<ioNumOfPoints; j++, curj+=3)
  {
       if(oaPoints[curj+0] < xmin) xmin=oaPoints[curj+0];
       if(oaPoints[curj+1] < ymin) ymin=oaPoints[curj+1];
       if(oaPoints[curj+2] < zmin) zmin=oaPoints[curj+2];
       if(oaPoints[curj+0] > xmax) xmax=oaPoints[curj+0];
       if(oaPoints[curj+1] > ymax) ymax=oaPoints[curj+1];
       if(oaPoints[curj+2] > zmax) zmax=oaPoints[curj+2];
  }
  CATMathPointf center((float) (xmin+xmax)/2.f, (float) (ymin+ymax)/2.f, (float) (zmin+zmax)/2.f);
  double radius= sqrt((xmax-xmin)*(xmax-xmin)+(ymax-ymin)*(ymax-ymin)+(zmax-zmin)*(zmax-zmin))/2.f;
  pCurveRep->SetBoundingElement(CAT3DBoundingSphere(center, (float)radius));
 
  // Returns the rep
  iopRep = pCurveRep;
}
//------------------------------------------------------------------------------
// ***********************************  Line
//------------------------------------------------------------------------------
void CAAGemRep::CreateLineRep(CATLine *piLine, CAT3DRep *& iopRep)
{
  CAT3DRep *pRep = NULL;
  if (NULL == piLine) return;

  CATCrvParam startParam, endParam  ;
  piLine->GetStartLimit(startParam);
  piLine->GetEndLimit(endParam);

  // The start and end points of the line
  //CATMathPoint startPoint =piLine->EvalPoint(startParam);
  //CATMathPoint endPoint =piLine->EvalPoint(endParam);
  CATMathPoint startPoint, endPoint;
  piLine->Eval(startParam,CATCrvEvalCommand::EvalPoint,&startPoint);
  piLine->Eval(endParam,CATCrvEvalCommand::EvalPoint,&endPoint);
  CATMathPointf start, end;
  start.x = (float) startPoint.GetX();
  start.y = (float) startPoint.GetY();
  start.z = (float) startPoint.GetZ();
  end.x   = (float) endPoint.GetX();
  end.y   = (float) endPoint.GetY();
  end.z   = (float) endPoint.GetZ();

  // Is the line infinite?
  double infinity=piLine->GetContainer()->GetModelSize();
  CATMathBox boxInfinite(-infinity,infinity,-infinity,infinity,-infinity,infinity) ;
  int isFinite = (boxInfinite.IsContaining(startPoint) && boxInfinite.IsContaining(endPoint) ) ? 1 : 0;
  
  if ( isFinite )
  {
    // Creates the rep of the finite line 
    CAT3DLineRep* pRepresentation = new CAT3DLineRep();
    pRepresentation->Modify(start,end);
    pRep = pRepresentation;
  }
  else
  {
    // Creates a special rep: an arrow 
    CATMathLine line(startPoint,endPoint);
    CATMathPoint origin, projpt;
    line.Project(origin,projpt);
    CATMathVector vect;
    line.GetDirection(vect);
     
    CATMathPointf  ptf((float)projpt.GetX(), (float)projpt.GetY(), (float)projpt.GetZ());
    CATMathVectorf tf(vect);
     
    CAT3DCustomRep  * pBagGP = new CAT3DCustomRep();     
    CAT3DFixedArrowGP* pArrow = new CAT3DFixedArrowGP(ptf,tf, 40, 2);
    CATGraphicAttributeSet attribute;  
    pBagGP->AddGP(pArrow,attribute);  
    pRep = pBagGP;
  }
  // Returns the rep
  iopRep = pRep;
}


//------------------------------------------------------------------------------
// ***********************************  Point
//------------------------------------------------------------------------------
void CAAGemRep::CreatePointRep  (CATMathPoint & point,CAT3DRep *& iopRep)
{
   // Gets the coordinates of the point
   double ioFirstCoord,ioSecondCoord,ioThirdCoord;
   point.GetCoord(ioFirstCoord,ioSecondCoord,ioThirdCoord);
   float aCoord[3];
   aCoord[0]= (float)ioFirstCoord;
   aCoord[1]= (float)ioSecondCoord;
   aCoord[2]= (float)ioThirdCoord;
    
   // Creates the rep
   CAT3DPointRep *rep = new CAT3DPointRep(aCoord,FULLCIRCLE);

   // Returns the rep
   iopRep = rep;
 }

