// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEVisVisuPlane.h"

// CAASystem.edu Framework
#include "CAAISysPlane.h"

// Visualization Framework 
#include "CAT3DCustomRep.h"
#include "CAT3DFixedPlanGP.h"
#include "CATMathDirection.h"

// Others
#include "iostream.h"

//---------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuPlane);

// To declare that the class is a data extension of CAASysPlane
//
CATImplementClass(CAAEVisVisuPlane, DataExtension, CATBaseUnknown, CAASysPlane);

// 
// To declare that CAAEVisVisuPlane implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysPlane CATI3DGeoVisu  libCAAVisGeoModel
//

//---------------------------------------------------------------------------

CAAEVisVisuPlane::CAAEVisVisuPlane()
{
  cout << "CAAEVisVisuPlane::CAAEVisVisuPlane" << endl;
}

CAAEVisVisuPlane::~CAAEVisVisuPlane()
{
  cout << "CAAEVisVisuPlane::~CAAEVisVisuPlane" << endl;
}

CATRep * CAAEVisVisuPlane::BuildRep()
{
  cout << "CAAEVisVisuPlane::BuildRep" << endl;
  
  // The rep to return
  CAT3DCustomRep         * pPlaneRep = NULL ;
  
  CAAISysPlane * piSysPlane = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysPlane, (void**)&piSysPlane);
  if (SUCCEEDED(rc))
  {
    // Retrieves information about the Plane
    CATMathPoint origin ;
    piSysPlane->GetOrigin(origin);
    CATMathVector u,v ;
    piSysPlane->GetPlane(u,v);

    // Done with the plane
    piSysPlane -> Release();
    piSysPlane= NULL ;

    // Creation of the 3D graphic representation 
    pPlaneRep = new CAT3DCustomRep();

    // Creation of the Graphic Primitive dedicated to the Plane
	CATMathDirection Udir(u), Vdir(v);
    CAT3DFixedPlanGP * pPlaneGp = new CAT3DFixedPlanGP(origin,Udir,Vdir,20.f);

     // Default attribut graphique 
     CATGraphicAttributeSet   PlaneGa ;

     // Association of the Gp and the Ga to the Representation
    pPlaneRep->AddGP(pPlaneGp,PlaneGa);

    // Sets the bounding sphere
    CAT3DBoundingSphere be(origin,0.f,15.f);
    pPlaneRep->SetBoundingElement(be) ;

  }

  return pPlaneRep;
} 







