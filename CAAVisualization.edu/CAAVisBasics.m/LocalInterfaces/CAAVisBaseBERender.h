#ifndef CAAVisBaseBERender_h
#define CAAVisBaseBERender_h

// COPYRIGHT DASSAULT SYSTEMES 2000

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Bounding boxes render class.
//  This object illustrates the way to do a render.
//  It goes through the scene tree and calculates the bounding
//  boxes for each rep. These bounding boxes are stored, and can be
//  accessed thanks to a public method.
//  The calculation of bounding boxes is the simpliest: while
//  rendering a rep, we are looking for its maximum and minimum coordinates,
//  which are the bounding box coordinates.
//
//===========================================================================
//  Inheritance:
//  ------------
//           CAAVisBERender
//             CATRender(Visualization Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  Draw: parses the scene through the render.
//
//  GetNumberOfBoxes: gets the number of boxes
//                    calculated into the scene.
//
//  GetBoundingBox: Gets the bounding box of a rep, from its index.
//
//===========================================================================

//Visualzation Framework
#include "CATRender.h"
#include "list.h"

//Visualzation Framework
class CATSupport;
class CATViewpoint;

class CAAVisBaseBERender : public CATRender
{
public:

  // Constructs a Bounding Boxes render from  a CATSupport.
  // The CATSupport of the scene can be retreived easily from the viewer.
  CAAVisBaseBERender(const CATSupport &iSupport);
  
  virtual ~CAAVisBaseBERender();

  //Overridden methods:
  //
  //Draws the scene through the render.
  virtual void Draw(list<CATViewpoint> &iViewpoints, const int, const float);

  //Called each time we are begining a new rep.
  virtual void DrawRepresentation(CATRep &iRep);

  virtual void EndDraw(CATViewpoint &iViewpoint);

  //Draws a 3D face through the render. Here we're going to look for
  //maima and minima, and to compare them with the ones found for other faces
  //of the rep.
  virtual void Draw3DFace (CAT3DFaceGP &iGP);

  virtual void Draw3DPlanarFace (CAT3DPlanarFaceGP &iGP);

  // Modifys the render so that it takes into account the
  // fact that our local repair has changed. Called
  // at the drawing of a CAT3DBagRep.
  // Pushes the matrices in the order they come.
  virtual CATRender * PushMatrix(CAT4x4Matrix &iMatrix);

  //Pops back the matrices stack so that we get back to the previous
  //state.
  virtual void PopMatrix (CATRender *ioRender);

  //Own methods:
  
  int GetNumberOfBoxes();
  
  void GetBox(int iIndex, float *oBox);

private:

  //Default constructor
  CAAVisBaseBERender();

  //Copy constructor
  CAAVisBaseBERender(const CAAVisBaseBERender &iBrother);

  //Assignment operator
  CAAVisBaseBERender & operator = (const CAAVisBaseBERender &iBrother);

private:

  int _NBoxes;
  float **_ppBoxes;

  //data members used to store the minima and maxima
  //while rendering a rep.
  float _XMax, _YMax, _ZMax, _XMin, _YMin, _ZMin;

  //persistence of states through matrix transformations
  int _NbPush;
  list<CATViewpoint> _PushedViewpoints;
  list<CATViewport>  _PushedViewports;
  list<CAT4x4Matrix> _PushedMatrix;
};

#endif
