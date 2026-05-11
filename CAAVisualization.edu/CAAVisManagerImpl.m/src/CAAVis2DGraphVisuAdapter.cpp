// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAVis2DGraphVisuAdapter.h"

// Mathematics FrameWork
#include "CATMathVector2Df.h"

//-----------------------------------------------------------------------------

CAAVis2DGraphVisuAdapter::CAAVis2DGraphVisuAdapter()
{
}

//-----------------------------------------------------------------------------

CAAVis2DGraphVisuAdapter::~CAAVis2DGraphVisuAdapter()
{
}

//-----------------------------------------------------------------------------

CAT3x3Matrix & CAAVis2DGraphVisuAdapter::GetPositioningMatrix()
{
    return _PositioningMat;
}

//-----------------------------------------------------------------------------

void CAAVis2DGraphVisuAdapter::IncrementPositioningMatrix()
{
   // we add a translation vector to the vertical translation vector.
   CATMathVector2Df Vtranslation_v (0.f,20.f);
   CATMathVector2Df translatation_v =  _PositioningMat.GetTranslation ();
   translatation_v = translatation_v + Vtranslation_v;

   // we record the 2D postionning matrix of the current object.
   _PositioningMat.SetTranslation(translatation_v);
}

//-----------------------------------------------------------------------------
