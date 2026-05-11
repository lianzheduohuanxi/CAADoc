// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEVisVisuLine.h"

// CAASystem.edu Framework
#include "CAAISysLine.h"

// Visualization Framework 
#include "CAT3DCustomRep.h"
#include "CAT3DLineGP.h"
#include "CATMathPoint.h"

// Mathematics Framework
#include "CATMathVector.h"

// Others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuLine);

// To declare that the class is a data extension of CAASysLine
//
CATImplementClass(CAAEVisVisuLine, DataExtension, CATBaseUnknown, CAASysLine);
// 
// To declare that CAAEVisVisuLine implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysLine CATI3DGeoVisu  libCAAVisGeoModel
//

//-----------------------------------------------------------------------------

CAAEVisVisuLine::CAAEVisVisuLine()
{
  cout << "CAAEVisVisuLine::CAAEVisVisuLine" << endl;
}

CAAEVisVisuLine::~CAAEVisVisuLine()
{
  cout << "CAAEVisVisuLine::~CAAEVisVisuLine" << endl;
}

CATRep * CAAEVisVisuLine::BuildRep()
{
  cout << "CAAEVisVisuLine::BuildRep" << endl;

  // The rep to return
  CAT3DCustomRep         * pLineRep = NULL ;

  CAAISysLine * piSysLine = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysLine, (void**)&piSysLine);

  if (SUCCEEDED(rc))
  {

     // Retrieves information about the Line
     CATMathPoint start,end;
     piSysLine->GetStartPoint(start);
     piSysLine->GetEndPoint(end);

     // Done with the line
     piSysLine -> Release();
     piSysLine = NULL ;

     // Creation of the Graphic Primitive dedicated to the line
     float coord[6] ;
     coord[0] = (float) start.GetX() ;	  	  
     coord[1] = (float) start.GetY() ;
     coord[2] = (float) start.GetZ() ;
     coord[3] = (float) end.GetX() ;	  	  
     coord[4] = (float) end.GetY() ;
     coord[5] = (float) end.GetZ() ;

     // Creation of the 3D graphic representation 
     pLineRep = new CAT3DCustomRep();

     // Constructs the graphic primitive dedicated to the line
     CAT3DLineGP * pLineGp = new CAT3DLineGP(coord,2) ;

     // Default attribut graphique 
     CATGraphicAttributeSet   LineGa ;

     // Association of the Gp and the Ga to the Representation
     pLineRep->AddGP(pLineGp,LineGa);

     // Computes the Bounding sphere
     CATMathPoint center =  start + ((end-start) / 2.f)  ;
     float radius = (float) start.DistanceTo(center);
     CAT3DBoundingSphere be(center,radius);

     // Sets the bounding sphere
     pLineRep->SetBoundingElement(be) ;

  }

  return pLineRep;
} 

