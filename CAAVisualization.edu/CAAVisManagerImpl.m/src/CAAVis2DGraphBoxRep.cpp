// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAVis2DGraphBoxRep.h"

// Visualization Framework
#include "CAT2DPolygonRep.h"
#include "CAT2DAnnotationTextRep.h"

// Mathematics Framework
#include "CATMathPoint2Df.h"

CAAVis2DGraphBoxRep::CAAVis2DGraphBoxRep(const char * title,float height, float width)
{

  // The Bag contains :
  //   - one 2D polygone representation
  //   - one 2D text     representation
  //

  // --------------------------------------------------------

  CAT2DPolygonRep        *auxPolyRep = NULL;
  
  float tab[2*4];
  tab[0] =  - 1.f*width;
  tab[1] =  - 1.f*height;
  tab[2] =  - 1.f*width;
  tab[3] =  + 1.f*height;
  tab[4] =  + 1.f*width;
  tab[5] =  + 1.f*height;
  tab[6] =  + 1.f*width;
  tab[7] =  - 1.f*height;

  auxPolyRep = new CAT2DPolygonRep(tab,4,FILL);
  auxPolyRep->SetColor(205);

  // --------------------------------------------------------

  CAT2DAnnotationTextRep *auxTextRep = NULL;
  
  float            TextOrigin[2]={0.f,0.f};
  CATUnicodeString TextTitle (title);
  CATAnchorPoint      TextPosition =  BASE_CENTER ;
  float            TextHeight   = 7.f ;
  
  auxTextRep = new CAT2DAnnotationTextRep(TextOrigin,TextTitle,TextPosition,TextHeight);
  auxTextRep->SetColor(20);
  
  
  // --------------------------------------------------------

  AddChild(*auxPolyRep);
  AddChild(*auxTextRep);

}


CAAVis2DGraphBoxRep::~CAAVis2DGraphBoxRep()
{

}

