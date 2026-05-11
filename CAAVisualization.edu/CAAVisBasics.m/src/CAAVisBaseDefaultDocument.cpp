// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAVisBaseDefaultDocument.h"

//Visualization Framework
#include "CAT3DBagRep.h"
#include "CAT3DFaceGP.h"
#include "CAT3DCustomRep.h"
#include "CAT3DLodRep.h"

//Mathematics Framework
#include "CATMath.h"
#include "CATMathConstant.h"

#define TORUS_RADIUS 50  //The torus global radius
#define CIRCLE_RADIUS 20 //he radius of a torus circle.
#define MAX_SAG 10
#define NLOD 4           //The wanted number of LODs.

//-------------------------------------------------------------------------------

CAAVisBaseDefaultDocument::CAAVisBaseDefaultDocument(CATDialog *iDialogParent,
                                                     const char *iDocumentName)
: CAAVisBaseDocument(iDialogParent, iDocumentName)
{
  //Creation of a graphical representation
  CreateModel();
  
  //Adding the graphical representation into the viewer.
  AddRepToViewer();
}

//-------------------------------------------------------------------------------

CAAVisBaseDefaultDocument::~CAAVisBaseDefaultDocument()
{
  _pTorus = NULL;
}

//-------------------------------------------------------------------------------

void CAAVisBaseDefaultDocument::CreateModel()
{
  // Our graphical representation will be a torus.

  // We first have to create its tessellation
  
  // We want our graphical representation to have
  // NLOD levels of details, with the constraint that
  // the max sag is equal to MAX_SAG.

  // The class provided to manage levels of details is the
  // CAT3DLodRep class.

  _pRootContainer  = new CAT3DBagRep;
  _pTorus = new CAT3DLodRep;

  int color[3] = {255, 255, 255}; //White color

  int colors[] = {200, 200, 255, //bright blue
                  200, 0,   0,   //red
                  0,   0,   255, //blue
                  0,   200, 0};  //green
  
  int i;
  for(i=NLOD; i>0; i--)
    {
      //Let's set a different color for each LOD, in order
      //to better view the switching:
      //
      color[0] = colors[3*(i%NLOD)];
      color[1] = colors[3*(i%NLOD)+1];
      color[2] = colors[3*(i%NLOD)+2];
      
      //We're adding a new Level Of Details to our
      //CAT3DLodRep.
      //
      //The given sag corresponds to the sag for the
      //whole model, expressed in millimeters.
      //Here, for example, we want four LODs, and a
      //maximum sag inferior to 10 millimeters. The taken values are
      //1.25, 1.66, 2.5 and 5.0 millimeters.
      //The distances eye-model for which we have a
      //LOD swtching depends on the "Level Of Details" setting
      //chosen in CATIA(Tools > Options > Performance, Level Of Details, static).
      //To see well the four LODs, one must choose an approximate
      //static LOD value of 3.1 millimeters.
      //
      AddLOD(float(MAX_SAG)/(float)(2*i), color);
    }
  //Adding of the CAT3DLodRep to the CAT3DBagRep
  _pRootContainer->AddChild(*_pTorus);
}

//-------------------------------------------------------------------------------

void CAAVisBaseDefaultDocument::AddLOD(float sag, int *iColor)
{
  // A torus can be defined thanks to a circle extruded
  // along a circular path.
  //
  // Let's assume that the extruded circle radius is the "circle radius"
  // and that the circular path radius is the "torus radius".
  
  //radius of the torus
  int R = TORUS_RADIUS;

  //radius of a torus circle
  int r = CIRCLE_RADIUS;

  //From the global torus sag, we determine the "circle" sag
  //and the "torus" sag which  respectively determine the number of
  //vertices used to describe a circle on the torus, and the number
  //of circles used to describe the torus.

  float teta = CATSqrt(sag/r);
  float phi  = CATSqrt(sag/R);

  int nVertexPerCircle = floor(2*CATPI/teta)+1;
  int nCircles         = floor(2*CATPI/phi)+1;

  teta = 2*CATPI/nVertexPerCircle;
  phi  = 2*CATPI/nCircles;
  
  //array containing the vertices coordinates:
  int verticesArraySize = 3*nCircles*nVertexPerCircle;
  float * vertices = new float[verticesArraySize];
  
  
  //array containing the normals to each vertex:
  int normalsArraySize = 3*nCircles*nVertexPerCircle;
  float * normals = new float[normalsArraySize];
  
  
  int i;
  for(i=0; i<nCircles; i++)
    {
      int j;
      for(j=0; j<nVertexPerCircle; j++)
        {
          //vertex XYZ coordinates:
          vertices[3*(nVertexPerCircle*i+j)]   = (R+r*CATCos(j*teta))*CATSin(i*phi);
          vertices[3*(nVertexPerCircle*i+j)+1] = r*CATSin(j*teta);
          vertices[3*(nVertexPerCircle*i+j)+2] = (R+r*CATCos(j*teta))*CATCos(i*phi);

          //normal vector XYZ coordinates:
          normals[3*(nVertexPerCircle*i+j)]   = CATCos(j*teta)*CATSin(i*phi);
          normals[3*(nVertexPerCircle*i+j)+1] = CATSin(j*teta); 
          normals[3*(nVertexPerCircle*i+j)+2] = CATCos(j*teta)*CATCos(i*phi);
        }
    }

  // Creation of the torus graphical representation thanks to the CAT3DFaceGP.
  // We can build a CAT3DFaceGP made of nCircles triangles strips, each one
  // made of 2*nVertexPerCircle vertices. Indeed, by joining, with strips, the torus circles
  // two by two, we can describe the entire torus.

  // We have to build an array containing the vertices indices, sorted in
  // order to be parsed as strips vertices.

  //Array containing vertices indices:
  int * triangleStripIndices = new int[nCircles*2*(nVertexPerCircle+1)];
  //number of strips used to describe the torus:
  int nbTriangleStrip = nCircles;
  //Array containing the number of vertices used for each strip:
  int * nbVertexPerTriangleStrip = new int[nCircles];

  // the parsing order looks like this:
  // 
  //           first strip:
  //           -----------
  //   Circle0.Vertex0  -> Circle1.Vertex0
  //   Circle1.Vertex0  -> Circle0.Vertex1
  //   Circle0.Vertex2  -> Circle1.Vertex2
  //               ...
  //   Circle1.Vertex11 -> Circle0.Vertex0
  //   Circle0.Vertex0  -> Circle1.Vertex0
  //
  //           second strip:
  //           ------------
  //   Circle1.Vertex0  -> Circle2.Vertex0
  //   Circle2.Vertex0  -> Circle1.Vertex1
  //               ...

  for(i=0; i<nCircles; i++)
    {
      int j;
      for(j=0; j<=nVertexPerCircle; j++)
        {
          if(j<nVertexPerCircle)
            {
              triangleStripIndices[2*(nVertexPerCircle+1)*i+2*j]   = 3*(i*nVertexPerCircle+j);
              triangleStripIndices[2*(nVertexPerCircle+1)*i+2*j+1] = 3*((((i+1)%nCircles)*nVertexPerCircle)+j);
            }
          else
            {
              triangleStripIndices[2*(nVertexPerCircle+1)*i+2*j]   = 3*((i)*nVertexPerCircle);
              triangleStripIndices[2*(nVertexPerCircle+1)*i+2*j+1] = 3*(((i+1)%nCircles)*nVertexPerCircle);
            }
        }
      nbVertexPerTriangleStrip[i] = 2*(nVertexPerCircle+1);
    }

  // Creation of the CAT3DFaceGP:

  int   * triangleIndices        = NULL;
  int     nbTriangle             = 0;
  int   * triangleFanIndices     = NULL;
  int     nbTriangleFan          = 0;
  int   * nbVertexPerTriangleFan = NULL;
  float * TextureCoord           = NULL;
  int     TextureFormat          = 3 ;
  
  CAT3DFaceGP * face = new CAT3DFaceGP(vertices,
                                       verticesArraySize,
                                       normals,
                                       normalsArraySize,
                                       triangleIndices,
                                       nbTriangle,
                                       triangleStripIndices,
                                       nbTriangleStrip,
                                       nbVertexPerTriangleStrip,
                                       triangleFanIndices,
                                       nbTriangleFan,
                                       nbVertexPerTriangleFan,
                                       TextureCoord,
                                       TextureFormat,
                                       ALLOCATE_VERTICES | ALLOCATE_NORMALS
                                       );

  // The CAT3DFaceGP is added to a CAT3DCustomRep
  CAT3DCustomRep * torus = new CAT3DCustomRep;
  CATGraphicAttributeSet attributs;

  //We specify within the graphic attributs that our surface is a SOLID.
  attributs.SetType(3);

  //In order to be able to see each LOD, we specify a different color
  //for each LOD:

  attributs.SetColor(TRUECOLOR);
  attributs.SetColorRGBA(iColor[0], iColor[1], iColor[2]);

  //Adding of the CAT3DFaceGP to the CAT3DCustomRep
  torus->AddGP(face, attributs);
  
  //We MUST create the associated bounding box:
  //centered at the origin, and with a radius equal to
  //R+r.
  float center[3] = {0.0, 0.0, 0.0};
  float radius = R+r;
  CAT3DBoundingSphere bs(center, radius);
  torus->SetBoundingElement(bs);
  
  //As each CAt3DFaceGP has its own attribute, we don't need to give
  //an attribute to the rep, but it's better to do it.
  torus->SetGraphicAttributeSet(attributs);
  
  //Adding of the CAT3DCustomRep as a new level of detail
  //for the torus representation.
  _pTorus->AddLod(torus, sag);

  delete [] vertices;
  delete [] normals;
  delete [] triangleStripIndices;
  delete [] nbVertexPerTriangleStrip;
}

//-------------------------------------------------------------------------------

