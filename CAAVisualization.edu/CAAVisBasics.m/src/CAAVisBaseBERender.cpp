// COPYRIGHT DASSAULT SYSTEMES 2000

//Local Framework
#include "CAAVisBaseBERender.h"

//Visualization Framework
#include "CATSupport.h"
#include "CATRep.h"
#include "CAT3DViewpoint.h"
#include "CAT3DFaceGP.h"
#include "CAT3DPlanarFaceGP.h"
#include "CATSurfacicRep.h"  //should not be there
#include "CATViewport.h"

#include <string.h>
#include <float.h>

//-------------------------------------------------------------------------------

CAAVisBaseBERender::CAAVisBaseBERender(const CATSupport &support)
:CATRender(support)
{
  _NBoxes = 0;
  _ppBoxes = (float **)malloc(sizeof(float *));

  //Initialization of our minima and maxima.
  _XMax = - FLT_MAX;
  _YMax = - FLT_MAX;
  _ZMax = - FLT_MAX;
  _XMin =  FLT_MAX;
  _YMin =  FLT_MAX;
  _ZMin =  FLT_MAX;
  
  _NbPush = 0;
}

//-------------------------------------------------------------------------------

CAAVisBaseBERender::~CAAVisBaseBERender()
{
  //deletion of the stored bounding boxes.
  if( NULL != _ppBoxes)
    {
      int i;
      for(i=0; i<_NBoxes; i++)
        {
          free (_ppBoxes[i]);
          _ppBoxes[i] = NULL;
        }
      free (_ppBoxes);
      _ppBoxes = NULL;
    }
}

//-------------------------------------------------------------------------------

void CAAVisBaseBERender::Draw(list<CATViewpoint> & vp, const int, const float)
{
  //This is the main method of a render.
  //It parses the rep trees lying under a list of viewpoints.
  int nVP = vp.length();
  int i;
  for(i=0; i<nVP; i++)
    {
      if ( NULL != vp[i] )
      {
         //We're only interested by the main 3D viewpoint.
         if(vp[i]->IsAKindOf("CAT3DViewpoint"))
          {
             CAT3DViewpoint * vp3d = (CAT3DViewpoint *)vp[i];
             if( ( NULL != vp3d) && vp3d->IsMain3DViewpoint())
               {
                 //Method called at the begining of a scene's drawing:
                 BeginDraw(*(vp3d));
   
                 //Gets the list of reps which are in this viwpoint:
                 list<CATRep> & reps = vp3d->GetRepList();
                 int nRep = reps.length();
                 int j;
                 for(j=0; j<nRep; j++)
                   {
                     //Check the bounding element state
                     if(reps[j]->IsInvalid())
                       reps[j]->ComputeBoundingElement();
   
                     //Each rep has its own Draw method.
                     reps[j]->Draw(*this, 1);
                   }
                 EndDraw(*vp3d);
               }
           }
        }
    }
}

//-------------------------------------------------------------------------------

void CAAVisBaseBERender::EndDraw(CATViewpoint & viewpoint)
{
  if((_XMax != - FLT_MAX)
     ||(_YMax != - FLT_MAX)
     ||(_ZMax != - FLT_MAX)
     ||(_XMin != FLT_MAX)
     ||(_YMin != FLT_MAX)
     ||(_ZMin != FLT_MAX))
    {
      
      _ppBoxes[_NBoxes] = (float *)malloc(6*sizeof(float));
      memset(_ppBoxes[_NBoxes], 0, 6*sizeof(float));
      
      _ppBoxes[_NBoxes][0] = _XMin;
      _ppBoxes[_NBoxes][1] = _YMin;
      _ppBoxes[_NBoxes][2] = _ZMin;
      _ppBoxes[_NBoxes][3] = _XMax;
      _ppBoxes[_NBoxes][4] = _YMax;
      _ppBoxes[_NBoxes][5] = _ZMax;
      
      _NBoxes++;
      _ppBoxes = (float **)realloc(_ppBoxes, (_NBoxes+1)*sizeof(float *));

    }
  
  _XMax = - FLT_MAX;
  _YMax = - FLT_MAX;
  _ZMax = - FLT_MAX;
  _XMin =  FLT_MAX;
  _YMin =  FLT_MAX;
  _ZMin =  FLT_MAX;
}

//-------------------------------------------------------------------------------

void CAAVisBaseBERender::DrawRepresentation(CATRep & rep)
{
  if(rep.IsAKindOf("CATSurfacicRep"))
    {
      CATSurfacicRep * sRep = (CATSurfacicRep *)&rep;
      if ( NULL != sRep )
        {
         sRep->SetEditMode(1);
        }
    }
  if((_XMax != - FLT_MAX)
     ||(_YMax != - FLT_MAX)
     ||(_ZMax != - FLT_MAX)
     ||(_XMin != FLT_MAX)
     ||(_YMin != FLT_MAX)
     ||(_ZMin != FLT_MAX))
    {
      
      _ppBoxes[_NBoxes] = (float *)malloc(6*sizeof(float));
      memset(_ppBoxes[_NBoxes], 0, 6*sizeof(float));
      
      _ppBoxes[_NBoxes][0] = _XMin;
      _ppBoxes[_NBoxes][1] = _YMin;
      _ppBoxes[_NBoxes][2] = _ZMin;
      _ppBoxes[_NBoxes][3] = _XMax;
      _ppBoxes[_NBoxes][4] = _YMax;
      _ppBoxes[_NBoxes][5] = _ZMax;
      
      _NBoxes++;
      _ppBoxes = (float **)realloc(_ppBoxes, (_NBoxes+1)*sizeof(float *));

    }

  _XMax = - FLT_MAX;
  _YMax = - FLT_MAX;
  _ZMax = - FLT_MAX;
  _XMin =  FLT_MAX;
  _YMin =  FLT_MAX;
  _ZMin =  FLT_MAX;

}

//-------------------------------------------------------------------------------

void CAAVisBaseBERender::Draw3DFace (CAT3DFaceGP & gp)
{
  int allocate = 0;
  float * vertices = NULL;
  int verticesArraySize = 0;
  float * normals = NULL;
  int normalsArraySize = 0;
  int * triangleIndice = NULL;
  int nbTriangle = 0;
  int * triangleStripIndice = NULL;
  int nbTriangleStrip = 0;
  int * nbVertexPerTriangleStrip = NULL;
  int * triangleFanIndice = NULL;
  int nbTriangleFan = 0;
  int * nbVertexPerTriangleFan = NULL;
  
  //Get these face's attributes..
  //---------------------------
  gp.Get(&allocate,
         &vertices, &verticesArraySize,           //vertices of the faceGP
         &normals, &normalsArraySize,      //normales of the faceGP (one per vertex)
         &triangleIndice, &nbTriangle,     //single triangles
         &triangleStripIndice, &nbTriangleStrip, &nbVertexPerTriangleStrip,   //triangles organized in strips
         &triangleFanIndice, &nbTriangleFan, &nbVertexPerTriangleFan); //triangles organized in fan
  
  int i;
  for(i=0; i<verticesArraySize; i+=3)
    {
      CATMathPointf * point3d = new CATMathPointf(vertices[i], vertices[i+1], vertices[i+2]);

      //We must take into account the matrix transformations
      //occured until the current step.
      //Indeed, to get the real coordinates of our face, we must
      //multiply its coordinates by the matrix obtained by the
      //multiplication of matrices traversed in the tree until now.
      if( _NbPush > 0 )
        *point3d = CATMathPointf(*(_PushedMatrix[_NbPush-1]) * *point3d);
      
      //Here, we're looking for the X, Y, Z maxima and minima,
      //for the whole rep.
      if(point3d->x > _XMax)
        _XMax = point3d->x;
      
      if(point3d->x < _XMin)
        _XMin = point3d->x;
      
      if(point3d->y > _YMax)
        _YMax = point3d->y;
      
      if(point3d->y < _YMin)
        _YMin = point3d->y;
      
      if(point3d->z > _ZMax)
        _ZMax = point3d->z;
      
      if(point3d->z < _ZMin)
      _ZMin = point3d->z;

      delete point3d;
    }
}

//-------------------------------------------------------------------------------

void CAAVisBaseBERender::Draw3DPlanarFace (CAT3DPlanarFaceGP & gp)
{
  Draw3DFace(gp);
}

//-------------------------------------------------------------------------------

CATRender * CAAVisBaseBERender::PushMatrix(CAT4x4Matrix &iMatrix)
{

  //viewpoint_ and viewport_ are the current viewport and viewpoint.

  //Adding of the current viewpoint and viewport into the list.
  _PushedViewpoints += viewpoint_->Clone();
  _PushedViewports  += viewport_->Clone();

  //Here, we are modifying the current viewpoint and viewport.
  *this *= iMatrix;

  //Here we're storing our current matrix
  if(_NbPush > 0 )
    {
      CAT4x4Matrix * pNewMatrix = new CAT4x4Matrix;
      pNewMatrix->multiply(iMatrix, *(_PushedMatrix[_NbPush-1]));
      
      _PushedMatrix += pNewMatrix;
    }
  else
    {
      _PushedMatrix += iMatrix;
    }

  //Counts the number of matrix transformations we're passing
  //through.
  _NbPush++;

  return (this);
}

//-------------------------------------------------------------------------------

void CAAVisBaseBERender::PopMatrix (CATRender *ioRender)
{
  _NbPush--;

  if(viewpoint_->IsMalloced())
    {
      viewpoint_->Release();
      viewpoint_ = NULL ;
    }

  if(viewport_->IsMalloced())
    {
      viewport_->Release();
      viewport_ = NULL ;
    }

  //Retrieving of the previous viewpoint, viewport and matrix states.
  viewpoint_ = _PushedViewpoints[_NbPush];
  viewport_  = _PushedViewports[_NbPush];

  viewpoint2D_ = (CAT2DViewpoint *) viewpoint_;
  viewpoint3D_ = (CAT3DViewpoint *) viewpoint_;
  viewport2D_  = (CAT2DViewport  *) viewport_;
  viewport3D_  = (CAT3DViewport  *) viewport_;

  CATViewpoint *pViewpointToRemove = _PushedViewpoints[_NbPush];
  CATViewport  *pViewportToRemove  = _PushedViewports[_NbPush];
  CAT4x4Matrix *pMatrixToRemove    = _PushedMatrix[_NbPush];

  _PushedViewpoints -= pViewpointToRemove;
  _PushedViewports  -= pViewportToRemove;
  _PushedMatrix     -= pMatrixToRemove;
  
}

//-------------------------------------------------------------------------------

int CAAVisBaseBERender::GetNumberOfBoxes()
{
  return _NBoxes;
}

//-------------------------------------------------------------------------------

void CAAVisBaseBERender::GetBox(int index, float * box)
{
  box[0] = _ppBoxes[index][0];
  box[1] = _ppBoxes[index][1];
  box[2] = _ppBoxes[index][2];
  box[3] = _ppBoxes[index][3];
  box[4] = _ppBoxes[index][4];
  box[5] = _ppBoxes[index][5];
}
//-------------------------------------------------------------------------------
