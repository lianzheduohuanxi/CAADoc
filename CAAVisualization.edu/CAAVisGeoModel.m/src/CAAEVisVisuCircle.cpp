// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEVisVisuCircle.h"

// CAASystem.edu Framework
#include "CAAISysCircle.h"

// Visualization Framework 
#include "CAT3DCustomRep.h"
#include "CATMathVector.h"
#include "CATMathPoint.h"
#include "CAT3DArcCircleGP.h"

// Others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuCircle);

// To declare that the class is a data extension of CAASysCircle
//
CATImplementClass(CAAEVisVisuCircle, DataExtension, CATBaseUnknown, CAASysCircle);

// 
// To declare that CAAEVisVisuCircle implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysCircle CATI3DGeoVisu  libCAAVisGeoModel
//

//--------------------------------------------------------------------------------------------

CAAEVisVisuCircle::CAAEVisVisuCircle()
{
  cout << "CAAEVisVisuCircle::CAAEVisVisuCircle" << endl;
}

CAAEVisVisuCircle::~CAAEVisVisuCircle()
{
  cout << "CAAEVisVisuCircle::~CAAEVisVisuCircle" << endl;
}

CATRep * CAAEVisVisuCircle::BuildRep()
{
  cout << "CAAEVisVisuCircle::BuildRep" << endl;

  // The rep to return
  CAT3DCustomRep         * pCircleRep = NULL ;
  
  CAAISysCircle * piSysCircle = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysCircle, (void**)&piSysCircle);

  if (SUCCEEDED(rc))
  {

     // Retrieves information about the Circle
     CATMathPoint center ;
     float radius ;
     CATMathVector normal, axis ;

     piSysCircle->GetCenter(center);
     piSysCircle->GetRadius(radius);
     piSysCircle->GetPlanar(normal,axis);

     // Done with the interface pointer
     piSysCircle -> Release();
     piSysCircle = NULL ;

     // Creation of the 3D graphic representation 
     pCircleRep = new CAT3DCustomRep();

     // Creation of the Graphic Primitive dedicated to the Circle
     CAT3DArcCircleGP * pCircleGp = new CAT3DArcCircleGP(center,normal,radius,axis);

     // Default attribut graphique 
     CATGraphicAttributeSet  CircleGa ;

     // Association of the Gp and the Ga to the Representation 
     pCircleRep->AddGP(pCircleGp,CircleGa);

     // Sets a Bounding sphere 
     CAT3DBoundingSphere be(center,radius);
     pCircleRep->SetBoundingElement(be) ;

  }

  // The rep is kept in the adapter
  return pCircleRep;
} 







