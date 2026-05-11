// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVis3DGeoVisuForCuboid.h"
#include "CAAIVisModelCuboid.h"

// Visualization Framework
#include "CAT3DCustomRep.h"
#include "CAT3DFaceGP.h"

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVis3DGeoVisuForCuboid);

// To declare that the class is a data extension of CAAVisModelCuboid
//
CATImplementClass(CAAEVis3DGeoVisuForCuboid,DataExtension,CATBaseUnknown,CAAVisModelCuboid);


// 
// To declare that CAAEVis3DGeoVisuForCuboid implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelCuboid CATI3DGeoVisu  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------


CAAEVis3DGeoVisuForCuboid::CAAEVis3DGeoVisuForCuboid()
{
  cout << "CAAEVis3DGeoVisuForCuboid::CAAEVis3DGeoVisuForCuboid" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVis3DGeoVisuForCuboid::~CAAEVis3DGeoVisuForCuboid()
{
  cout << "CAAEVis3DGeoVisuForCuboid::~CAAEVis3DGeoVisuForCuboid" << endl;
}

//--------------------------------------------------------------------------------------------

CATRep * CAAEVis3DGeoVisuForCuboid::BuildRep()
{
   // The graphic representation to return 
   CAT3DCustomRep * pCuboidRep = NULL ;
   
   CAAIVisModelCuboid * pCAAIVisModelCuboid = NULL ;
   HRESULT rc = QueryInterface(IID_CAAIVisModelCuboid, (void**)&pCAAIVisModelCuboid);
   if (SUCCEEDED(rc))
   {
       // Retrieves Data
       float * vertices = NULL ;
       pCAAIVisModelCuboid->GetVertices(&vertices);

       // Done with the pointer 
       pCAAIVisModelCuboid->Release();
       pCAAIVisModelCuboid = NULL ;
       
       // Creates the Custom Representation 
       pCuboidRep = new CAT3DCustomRep();
   
       // 6 face  ==> 6x4 vertices.
       float verticestab[4*6*3];
       int face_num;
       int vertex_num;
       int fromvertex_num;
  
       // +++ face X0X1X5X6++++++++++++++++++++++++++++++++
       face_num = 0;
       vertex_num = 0;
       fromvertex_num=0;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 1;
       fromvertex_num=1;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 2;
       fromvertex_num=5;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 3;
       fromvertex_num=6;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
     
       // +++ face X1X2X6X7++++++++++++++++++++++++++++++++
       face_num = 1;
       vertex_num = 0;
       fromvertex_num=1;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 1;
       fromvertex_num=2;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 2;
       fromvertex_num=6;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 3;
       fromvertex_num=7;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
 
       // +++ face X2X3X7X4++++++++++++++++++++++++++++++++
       face_num = 2;
       vertex_num = 0;
       fromvertex_num=2;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 1;
       fromvertex_num=3;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 2;
       fromvertex_num=7;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 3;
       fromvertex_num=4;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
   
       // +++ face X3X0X4X5++++++++++++++++++++++++++++++++

       face_num = 3;
       vertex_num = 0;
       fromvertex_num=3;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 1;
       fromvertex_num=0;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 2;
       fromvertex_num=4;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 3;
       fromvertex_num=5;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
   
       // +++ face X5X6X4X7++++++++++++++++++++++++++++++++
   
       face_num = 4;
       vertex_num = 0;
       fromvertex_num=5;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 1;
       fromvertex_num=6;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 2;
       fromvertex_num=4;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 3;
       fromvertex_num=7;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];

       // +++ face X1X0X2X3++++++++++++++++++++++++++++++++
  
       face_num = 5;
       vertex_num = 0;
       fromvertex_num=1;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 1;
       fromvertex_num=0;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 2;
       fromvertex_num=2;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];
       vertex_num = 3;
       fromvertex_num=3;
       verticestab[4*3*face_num + 3*vertex_num + 0] = vertices[3*fromvertex_num];
       verticestab[4*3*face_num + 3*vertex_num + 1] = vertices[3*fromvertex_num+1];
       verticestab[4*3*face_num + 3*vertex_num + 2] = vertices[3*fromvertex_num+2];

       float  normals[6*4*3] ;
       int pt1 ;
       int pt2 ;
       int pt3 ;
       int ii;
       float norm;
       
       // +++ Normal to face X0X1X5X6++++++++++++++++++++++++++++++++
       face_num = 0;
       pt1 = 0;
       pt2 = 1;
       pt3 = 6;
       normals[4*3*face_num+0]  = (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+2]-vertices[3*pt2+2]) - (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+1]-vertices[3*pt2+1]) ;
       normals[4*3*face_num+1] =  -(vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+2]-vertices[3*pt2+2]) + (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       normals[4*3*face_num+2] =  (vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+1]-vertices[3*pt2+1]) - (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       norm = sqrt(normals[4*3*face_num+0]*normals[4*3*face_num+0]  +
                   normals[4*3*face_num+1]*normals[4*3*face_num+1] +
                   normals[4*3*face_num+2]*normals[4*3*face_num+2]);
       normals[4*3*face_num+0]  /= norm;
       normals[4*3*face_num+1]  /= norm;
       normals[4*3*face_num+2]  /= norm;
       for ( ii =1 ; ii<4;ii++)
       {
          normals[4*3*face_num+3*ii+0] = normals[4*3*face_num+0] ;
          normals[4*3*face_num+3*ii+1] = normals[4*3*face_num+1] ;
          normals[4*3*face_num+3*ii+2] = normals[4*3*face_num+2] ;
       }

       // +++ Normal to face X1X2X6X7++++++++++++++++++++++++++++++++
       face_num = 1;
       pt1 = 1;
       pt2 = 2;
       pt3 = 7;
       normals[4*3*face_num+0]  = (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+2]-vertices[3*pt2+2]) - (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+1]-vertices[3*pt2+1]) ;
       normals[4*3*face_num+1] =  -(vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+2]-vertices[3*pt2+2]) + (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       normals[4*3*face_num+2] =  (vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+1]-vertices[3*pt2+1]) - (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       norm = sqrt(normals[4*3*face_num+0]*normals[4*3*face_num+0]  +
                   normals[4*3*face_num+1]*normals[4*3*face_num+1] +
                   normals[4*3*face_num+2]*normals[4*3*face_num+2]);
       normals[4*3*face_num+0]  /= norm;
       normals[4*3*face_num+1]  /= norm;
       normals[4*3*face_num+2]  /= norm;
       for ( ii =1 ; ii<4;ii++)
       {
          normals[4*3*face_num+3*ii+0] = normals[4*3*face_num+0] ;
          normals[4*3*face_num+3*ii+1] = normals[4*3*face_num+1] ;
          normals[4*3*face_num+3*ii+2] = normals[4*3*face_num+2] ;
       }
   
       // +++ Normal to face X2X3X7X4++++++++++++++++++++++++++++++++
       face_num = 2;
       pt1 = 2;
       pt2 = 3;
       pt3 = 4;
       normals[4*3*face_num+0]  = (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+2]-vertices[3*pt2+2]) - (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+1]-vertices[3*pt2+1]) ;
       normals[4*3*face_num+1] =  -(vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+2]-vertices[3*pt2+2]) + (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       normals[4*3*face_num+2] =  (vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+1]-vertices[3*pt2+1]) - (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       norm = sqrt(normals[4*3*face_num+0]*normals[4*3*face_num+0] + 
                   normals[4*3*face_num+1]*normals[4*3*face_num+1] +
                   normals[4*3*face_num+2]*normals[4*3*face_num+2]);
       normals[4*3*face_num+0]  /= norm;
       normals[4*3*face_num+1]  /= norm;
       normals[4*3*face_num+2]  /= norm;
       for ( ii =1 ; ii<4;ii++)
       {
          normals[4*3*face_num+3*ii+0] = normals[4*3*face_num+0] ;
          normals[4*3*face_num+3*ii+1] = normals[4*3*face_num+1] ;
          normals[4*3*face_num+3*ii+2] = normals[4*3*face_num+2] ;
       }

       // +++ Normal to face X3X0X4X5++++++++++++++++++++++++++++++++
       face_num = 3;
       pt1 = 3;
       pt2 = 0;
       pt3 = 5;
       normals[4*3*face_num+0]  = (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+2]-vertices[3*pt2+2]) - (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+1]-vertices[3*pt2+1]) ;
       normals[4*3*face_num+1] =  -(vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+2]-vertices[3*pt2+2]) + (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       normals[4*3*face_num+2] =  (vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+1]-vertices[3*pt2+1]) - (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       norm = sqrt(normals[4*3*face_num+0]*normals[4*3*face_num+0] +
                   normals[4*3*face_num+1]*normals[4*3*face_num+1] +
                   normals[4*3*face_num+2]*normals[4*3*face_num+2]);
       normals[4*3*face_num+0]  /= norm;
       normals[4*3*face_num+1]  /= norm;
       normals[4*3*face_num+2]  /= norm;
       for ( ii =1 ; ii<4;ii++)
       {
          normals[4*3*face_num+3*ii+0] = normals[4*3*face_num+0] ;
          normals[4*3*face_num+3*ii+1] = normals[4*3*face_num+1] ;
          normals[4*3*face_num+3*ii+2] = normals[4*3*face_num+2] ;
       }
   
       // +++ Normal to face X5X6X4X7++++++++++++++++++++++++++++++++
       face_num = 4;
       pt1 = 5;
       pt2 = 6;
       pt3 = 7;
       normals[4*3*face_num+0]  = (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+2]-vertices[3*pt2+2]) - (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+1]-vertices[3*pt2+1]) ;
       normals[4*3*face_num+1] =  -(vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+2]-vertices[3*pt2+2]) + (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       normals[4*3*face_num+2] =  (vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+1]-vertices[3*pt2+1]) - (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       norm = sqrt(normals[4*3*face_num+0]*normals[4*3*face_num+0]  +
                   normals[4*3*face_num+1]*normals[4*3*face_num+1] +
                   normals[4*3*face_num+2]*normals[4*3*face_num+2]);
       normals[4*3*face_num+0]  /= norm;
       normals[4*3*face_num+1]  /= norm;
       normals[4*3*face_num+2]  /= norm;
       for ( ii =1 ; ii<4;ii++)
       {
          normals[4*3*face_num+3*ii+0] = normals[4*3*face_num+0] ;
          normals[4*3*face_num+3*ii+1] = normals[4*3*face_num+1] ;
          normals[4*3*face_num+3*ii+2] = normals[4*3*face_num+2] ;
       }
    
       // +++ Normal to face X1X0X2X3++++++++++++++++++++++++++++++++
       face_num = 5;
       pt1 = 1;
       pt2 = 0;
       pt3 = 3;
       normals[4*3*face_num+0]  = (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+2]-vertices[3*pt2+2]) - (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+1]-vertices[3*pt2+1]) ;
       normals[4*3*face_num+1] =  -(vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+2]-vertices[3*pt2+2]) + (vertices[3*pt2+2]-vertices[3*pt1+2])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       normals[4*3*face_num+2] =  (vertices[3*pt2+0]-vertices[3*pt1+0])*(vertices[3*pt3+1]-vertices[3*pt2+1]) - (vertices[3*pt2+1]-vertices[3*pt1+1])*(vertices[3*pt3+0]-vertices[3*pt2+0]);
       norm = sqrt(normals[4*3*face_num+0]*normals[4*3*face_num+0]  +
                   normals[4*3*face_num+1]*normals[4*3*face_num+1] +
                   normals[4*3*face_num+2]*normals[4*3*face_num+2]);
       normals[4*3*face_num+0]  /= norm;
       normals[4*3*face_num+1]  /= norm;
       normals[4*3*face_num+2]  /= norm;
       for ( ii =1 ; ii<4;ii++)
       {
          normals[4*3*face_num+3*ii+0] = normals[4*3*face_num+0] ;
          normals[4*3*face_num+3*ii+1] = normals[4*3*face_num+1] ;
          normals[4*3*face_num+3*ii+2] = normals[4*3*face_num+2] ;
       }

       // Constructs one triangle strip per polygon face and each face is made of 4 vertices.
      int TriangleStripIndices[6*4];
      int kk;
      for (kk=0;kk<24;kk++)
      TriangleStripIndices[kk] = 3*kk;
 
      int NbVerticesPerStrip[6]={4,4,4,4,4,4};
      // Constructs a 3D Face Graphical Primitive
      CAT3DFaceGP * gp = new CAT3DFaceGP(verticestab,3*4*6,normals,3*4*6,NULL,0,
                                          TriangleStripIndices,6,NbVerticesPerStrip,NULL,0,NULL);


      // we define the graphical attributes of the 3D face.
      CATGraphicAttributeSet att;
      att.SetColor(TRUECOLOR); // necessary for taken into account the RGBA components.
      att.SetColorRGBA(100,50,200); 
      att.SetType(3);  // it is a volumic object

      // we add the 3D face to the custom graphical representation.
      pCuboidRep->AddGP(gp,att);

      // we compute the Bounding Sphere of the custom graphical representation.
      float center[3]={0.5f*(vertices[0]+vertices[7*3]),0.5f*(vertices[1]+vertices[7*3+1]),0.5f*(vertices[2]+vertices[7*3+2])};
      float radius = 0.5f*(sqrt( (vertices[0]-vertices[7*3])*(vertices[0]-vertices[7*3])
                               + (vertices[1]-vertices[7*3+1])*(vertices[1]-vertices[7*3+1])
                               + (vertices[2]-vertices[7*3+2])*(vertices[2]-vertices[7*3+2]) ));
   
      CAT3DBoundingSphere be(center,radius);
      pCuboidRep->SetBoundingElement(be);
   
   }

   return  pCuboidRep;
}
