// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEVisVisuPoint.h"

// CAASystem.edu Framework
#include "CAAISysPoint.h" 

// Visualizatiuon Framework 
#include "CAT3DMarkerGP.h"
#include "CAT3DCustomRep.h"

// other
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuPoint);

// To declare that the class is a data extension of CAASysPoint
//
CATImplementClass(CAAEVisVisuPoint, DataExtension, CATBaseUnknown, CAASysPoint );

// 
// To declare that CAAEVisVisuPoint implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysPoint CATI3DGeoVisu  libCAAVisGeoModel
//

//--------------------------------------------------------------------------------------------

CAAEVisVisuPoint::CAAEVisVisuPoint()
{
  cout << "CAAEVisVisuPoint::CAAEVisVisuPoint" << endl;
}

CAAEVisVisuPoint::~CAAEVisVisuPoint()
{
  cout << "CAAEVisVisuPoint::~CAAEVisVisuPoint" << endl;
}

CATRep * CAAEVisVisuPoint::BuildRep()
{
  cout << "CAAEVisVisuPoint::BuildRep" << endl;

  // The rep to return 
  CAT3DCustomRep *pPointRep = NULL ;

  CAAISysPoint * piSysPoint = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysPoint, (void**)&piSysPoint);

  if (SUCCEEDED(rc))
  {
     // Retrieves coordinates of the point
     float coord[3] ;
     piSysPoint->GetCoord(coord[0],coord[1],coord[2]) ;

     // Done with the point
     piSysPoint -> Release();
     piSysPoint = NULL ;

     // Creation of the 3D graphic representation
     pPointRep  = new CAT3DCustomRep() ;

     // Creation of the Graphic Primitive dedicated to the point
     CAT3DMarkerGP * pPointGp = new CAT3DMarkerGP(coord,1,CROSS);

     // Default attribut graphique is set 
     CATGraphicAttributeSet PointGa ;
     
     // Association of the Gp and the Ga to the Representation     
     pPointRep->AddGP(pPointGp,PointGa);

     // Sets the bounding sphere
     CAT3DBoundingSphere be(coord,0.f,1.f) ;
     pPointRep->SetBoundingElement(be);

  }

  return pPointRep;
}


