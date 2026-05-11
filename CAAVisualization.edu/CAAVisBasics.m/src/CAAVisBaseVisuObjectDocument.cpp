// COPYRIGHT DASSAULT SYSTEMES 2005

//Local Framework
#include "CAAVisBaseVisuObjectDocument.h"
#include "CAAVisBaseView.h"

//Visualization Framework
#include "CAT3DBagRep.h"
#include "CATSurfacicRep.h"
#include "CAT3DFaceGP.h"
#include "CAT3DLineGP.h"
#include "CAT3DPlanarFaceGP.h"
#include "CAT3DBoundingSphere.h"
#include "CATGraphicAttributeSet.h"
#include "CATVisMeasurableGP.h"
#include "CATGraphicPrimitive.h"

// Mathematics Framework
#include "CATMathConstant.h"
#include "CATMathDirectionf.h"
#include "CATMathPointf.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

//-------------------------------------------------------------------------------

CAAVisBaseVisuObjectDocument::CAAVisBaseVisuObjectDocument(CAAVisObjectType iObjectType,
                                                           CATDialog *iDialogParent,
                                                           const char *iDocumentName)
: CAAVisBaseDocument(iDialogParent, iDocumentName)
, _objectType(iObjectType)
{
  //Creation of the model:
  CreateModel();

  //Adding of the created model to the viewer:
  AddRepToViewer();
}

//-------------------------------------------------------------------------------

CAAVisBaseVisuObjectDocument::~CAAVisBaseVisuObjectDocument()
{
}

//-------------------------------------------------------------------------------

void CAAVisBaseVisuObjectDocument::CreateModel()
{
  _pRootContainer = new CAT3DBagRep;

  CATRep * model = NULL;
  switch(_objectType)
  {
  case CAAVisSurfacicRep :
     {
        model = CreateSurfacicRep();
     } break;
  }

  if(NULL != model)
    {
      _pRootContainer->AddChild(*model);
    }
}

#define CLEAR                    \
{                                \
   nbTriangles = 0;              \
   nbStrips    = 0;              \
   nbFans      = 0;              \
                                 \
   delete [] nbStripVertices;    \
   delete [] nbFanVertices;      \
   delete [] triangleIndices;    \
   delete [] stripIndices;       \
   delete [] fanIndices;         \
                                 \
   nbStripVertices = NULL;       \
   nbFanVertices   = NULL;       \
   triangleIndices = NULL;       \
   stripIndices    = NULL;       \
   fanIndices      = NULL;       \
   normal[0] = 0.0f;             \
   normal[1] = 0.0f;             \
   normal[2] = 0.0f;             \
}                                \
//-------------------------------------------------------------------------------

CATSurfacicRep * CAAVisBaseVisuObjectDocument::CreateSurfacicRep()
{
   CAAVisBaseView * view = GetView();
   if(view) view->SetTitle("CATSurfacicRep");

   // Variables used for face creation
   int nbTriangles = 0;
   int nbStrips    = 0;
   int nbFans      = 0;

   int * nbStripVertices = NULL;
   int * nbFanVertices   = NULL;

   int * triangleIndices = NULL;
   int * stripIndices    = NULL;
   int * fanIndices      = NULL;

   float normal[3] = { 0.0f, 0.0f, 0.0f };

   // Length of the cylinder
   double length = 50.0f;
   // Radius of the faces
   double radius = 10.0f;
   // Number of points wanted in order to tesselate the top and bottom faces
   unsigned int nbFaceVertices = 40;

   // Create the needed arrays for storing faces vertices
   float * topVertices    = new float[nbFaceVertices*3];
   float * bottomVertices = new float[nbFaceVertices*3];

   // The body face will need all the vertices from both the top and
   // bottom faces
   float * bodyVertices = new float[2*nbFaceVertices*3];
   float * bodyNormals  = new float[2*nbFaceVertices*3];

   float   bodyLineVertices[12];

   // Compute the vertices of the faces
   double angle = 0;
   double increment = CAT2PI/nbFaceVertices;
   unsigned int i;
   for(i=0;i<nbFaceVertices;++i)
   {
      // Compute position
      float x       = radius*(float)cos(angle);
      float y       = radius*(float)sin(angle);
      float zTop    = length/2.0f;
      float zBottom = -zTop;

      // Fill in top face vertices
      topVertices[3*i]   = x;
      topVertices[3*i+1] = y;
      topVertices[3*i+2] = zTop;

      // Fill in bottom face vertices
      bottomVertices[3*i]   = x;
      bottomVertices[3*i+1] = y;
      bottomVertices[3*i+2] = zBottom;

      // Fill in body face vertices.
      // Body vertices array interleaves the points of the top and bottom face
      bodyVertices[6*i]   = x;
      bodyVertices[6*i+1] = y;
      bodyVertices[6*i+2] = zTop;
      bodyVertices[6*i+3] = x;
      bodyVertices[6*i+4] = y;
      bodyVertices[6*i+5] = zBottom;

      // Fill in body line vertices
      if(i == 0)
      {
         bodyLineVertices[0] = x;
         bodyLineVertices[1] = y;
         bodyLineVertices[2] = zTop;
         bodyLineVertices[3] = x;
         bodyLineVertices[4] = y;
         bodyLineVertices[5] = zBottom;
      }
      else if(i == nbFaceVertices/2)
      {
         bodyLineVertices[6]  = x;
         bodyLineVertices[7]  = y;
         bodyLineVertices[8]  = zTop;
         bodyLineVertices[9]  = x;
         bodyLineVertices[10] = y;
         bodyLineVertices[11] = zBottom;
      }

      // Increase angle
      angle += increment;
   }

   //////////////////////////////////////////////////////////////////////////
   // We create the top and bottom faces
   // They both use the same set of vertices.
   // We only need to modify the z position and the strip indices ordering
   // in order to keep the strip triangles in a clockwise order
   // The faces will be composed of one fan triangle looping on a the face
   // vertices.
   //////////////////////////////////////////////////////////////////////////

   //////////////////////////////////////////////////////////////////////////
   // Top face
   //////////////////////////////////////////////////////////////////////////

   // Number of fans
   nbFans  = 1;

   // Array containing the number of vertices for each fan (here we only have one fan triangle)
   nbFanVertices    = new int[1];
   nbFanVertices[0] = nbFaceVertices;

   // Array containing all the indices pointing the vertices in the array
   // The resulting triangles must be indiced in order to keep the resulting
   // normal from the triangles in a clockwise order.
   fanIndices       = new int[nbFaceVertices];
   for(i=0;i<nbFaceVertices;++i)
      fanIndices[i] = 3*i;

   // We fill the normal value
   normal[0] = 0.0f;
   normal[1] = 0.0f;
   normal[2] = 1.0f;

   // We create the top face
   CAT3DPlanarFaceGP * topFace = new CAT3DPlanarFaceGP(  topVertices, nbFaceVertices*3,
                                                         normal,
                                                         triangleIndices,
                                                         nbTriangles,
                                                         stripIndices,
                                                         nbStrips,
                                                         nbStripVertices,
                                                         fanIndices,
                                                         nbFans,
                                                         nbFanVertices);

   // We create the line that bounds the face
   CAT3DLineGP * topLine = new CAT3DLineGP(topVertices, nbFaceVertices, ALLOCATE, LINE_LOOP);

   //////////////////////////////////////////////////////////////////////////
   // Bottom face
   //////////////////////////////////////////////////////////////////////////

   // Generate the fan indices
   // As above, but we invert the indices in order to keep the resulting
   // triangles in a clockwise order in respect to the normal
   for(i=0;i<nbFaceVertices;++i)
      fanIndices[i] = 3*(nbFaceVertices-i-1);

   // We fill the normal value
   normal[0] = 0.0f;
   normal[1] = 0.0f;
   normal[2] = -1.0f;

   // We create the bottom face
   CAT3DPlanarFaceGP * bottomFace = new CAT3DPlanarFaceGP(  bottomVertices, nbFaceVertices*3,
                                                            normal,
                                                            triangleIndices,
                                                            nbTriangles,
                                                            stripIndices,
                                                            nbStrips,
                                                            nbStripVertices,
                                                            fanIndices,
                                                            nbFans,
                                                            nbFanVertices);
   
   // We create the line that bounds the face
   CAT3DLineGP * bottomLine = new CAT3DLineGP(bottomVertices, nbFaceVertices, ALLOCATE, LINE_LOOP);

   // We can now clear the indices arrays
   CLEAR;

   //////////////////////////////////////////////////////////////////////////
   // Body face
   // The body is created using the vertices of the top and bottom faces
   // We generate one strip triangle that runs around the faces
   //////////////////////////////////////////////////////////////////////////

   nbStrips  = 1;
   nbStripVertices    = new int[1];
   stripIndices       = new int[2*nbFaceVertices+2];

   nbStripVertices[0] = 2*(nbFaceVertices+1);

   // Generate the strip indices
   for(i=0;i<2*nbFaceVertices;++i)
      stripIndices[i] = 3*i;

   // Close the strip
   stripIndices[2*nbFaceVertices]   = 0;
   stripIndices[2*nbFaceVertices+1] = 3;

   // Generate the normals for each vertices of the body
   for(i=0;i<2*nbFaceVertices;++i)
   {
      float * vertex = &bodyVertices[3*i];
      CATMathDirectionf normalDirection(CATMathPointf(0.0f, 0.0f, 0.0f), CATMathPointf(vertex[0], vertex[1], vertex[2]));
      normalDirection.Normalize();
      bodyNormals[3*i+0] = normalDirection.x;
      bodyNormals[3*i+1] = normalDirection.y;
      bodyNormals[3*i+2] = normalDirection.z;
   }

   // We create the body face
   CAT3DFaceGP * bodyFace = new CAT3DFaceGP( bodyVertices, 2*nbFaceVertices*3,
                                             bodyNormals,  2*nbFaceVertices*3,
                                             triangleIndices,
                                             nbTriangles,
                                             stripIndices,
                                             nbStrips,
                                             nbStripVertices,
                                             fanIndices,
                                             nbFans,
                                             nbFanVertices);

   // We create the lines that bounds the body
   CAT3DLineGP * bodyLine1 = new CAT3DLineGP(bodyLineVertices,     2, ALLOCATE, LINES);
   CAT3DLineGP * bodyLine2 = new CAT3DLineGP(&bodyLineVertices[6], 2, ALLOCATE, LINES);

   // We clear the indices arrays
   CLEAR;

   // Delete the vertices and normal arrays
   delete [] topVertices;
   delete [] bottomVertices;
   delete [] bodyVertices;
   delete [] bodyNormals;

   //////////////////////////////////////////////////////////////////////////
   // Topological informations
   // We can store topological informations on CATGraphicPrimitive objects
   // If the visualization data is saved as a CGR file, topological data will
   // be persistent in the CGR file
   //////////////////////////////////////////////////////////////////////////
   CATMathPoint center(0,0,0);
   CATMathVector axis(0,0,1);
   CATMathPoint startPoint,endPoint;

   // Top face
   CATGraphicPrimitive * gp = topFace;
   CATVisMeasurableGP cylinderTop(gp);
   cylinderTop.SetCylinder(center,axis,radius);

   // Bottom face
   gp = bottomFace;
   CATVisMeasurableGP cylinderBottom(gp);
   cylinderBottom.SetCylinder(center,axis,radius);

   // Top line
   gp = topLine;
   CATVisMeasurableGP circleTop(gp);
   circleTop.SetCircle(center,axis,radius);

   // Bottom line
   gp = bottomLine;
   CATVisMeasurableGP circleBottom(gp);
   circleBottom.SetCircle(center,axis,radius);

   // Body face
   gp = bodyFace;
   CATVisMeasurableGP cylinderBody(gp);
   cylinderBody.SetCylinder(center,axis,radius);

   // Body line 1
   gp = bodyLine1;
   startPoint.SetCoord(bodyLineVertices[0], bodyLineVertices[1], bodyLineVertices[2]);
   endPoint.SetCoord  (bodyLineVertices[3], bodyLineVertices[4], bodyLineVertices[5]);
   CATVisMeasurableGP cylinderBodyLine1(gp);
   cylinderBodyLine1.SetLine(startPoint,endPoint);

   // Body line 2
   gp = bodyLine2;
   startPoint.SetCoord(bodyLineVertices[6], bodyLineVertices[7],  bodyLineVertices[8]);
   endPoint.SetCoord  (bodyLineVertices[9], bodyLineVertices[10], bodyLineVertices[11]);
   CATVisMeasurableGP cylinderBodyLine2(gp);
   cylinderBodyLine2.SetLine(startPoint,endPoint);

   //////////////////////////////////////////////////////////////////////////
   // SurfacicRep
   // The CATSurfacicRep object will aggregate the faces and lines
   //////////////////////////////////////////////////////////////////////////

   // We create the surfacic rep
   CATSurfacicRep * sRep = new CATSurfacicRep();

   // We compute the bounding sphere of the resulting surfacic rep;
   CAT3DBoundingSphere globalSphere;
   globalSphere += CAT3DBoundingSphere(bottomFace->GetSphereCenter(), bottomFace->GetSphereRadius());
   globalSphere += CAT3DBoundingSphere(topFace->GetSphereCenter(),    topFace->GetSphereRadius());
   globalSphere += CAT3DBoundingSphere(bodyFace->GetSphereCenter(),   bodyFace->GetSphereRadius());
   sRep->SetBoundingElement(globalSphere);
   sRep->GetGraphicAttributeSet().SetType(3); // Specifies that this surfacic rep is a volume


   // We add the cylinder faces to the surfacic rep, giving them a custom color using
   // the CATGraphicAttributeSet.
   CATGraphicAttributeSet tmpAtt;
   tmpAtt.SetType(3); // Specifies that these faces are part of a volume
   tmpAtt.SetColor(BLUE);  // Give each face a specific color
   sRep->AddGeomFace(topFace, new CATGraphicAttributeSet(tmpAtt));
   tmpAtt.SetColor(GREEN);
   sRep->AddGeomFace(bottomFace, new CATGraphicAttributeSet(tmpAtt));
   tmpAtt.SetColor(RED);
   sRep->AddGeomFace(bodyFace, new CATGraphicAttributeSet(tmpAtt));

   // We add the lines to the surfacic rep, giving them a custom color and thickness using
   // the CATGraphicAttributeSet.
   tmpAtt.SetColor(BLACK);
   tmpAtt.SetThickness(2);
   sRep->AddGeomElt(CATBoundaryEdge, topLine, new CATGraphicAttributeSet(tmpAtt));
   sRep->AddGeomElt(CATBoundaryEdge, bottomLine, new CATGraphicAttributeSet(tmpAtt));
   sRep->AddGeomElt(CATInternalSmoothEdge, bodyLine1, new CATGraphicAttributeSet(tmpAtt));
   sRep->AddGeomElt(CATInternalSmoothEdge, bodyLine2, new CATGraphicAttributeSet(tmpAtt));

   return sRep;
}
