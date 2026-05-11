// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEVisVisuCylinder.h"

// CAASystem.edu Framework
#include "CAAISysCylinder.h"

// Visualization Framework 
#include "CAT3DCustomRep.h"
#include "CAT3DCylinderGP.h"

// Mathematic Framework
#include <CATMathVector.h>

// Others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuCylinder);

// To declare that the class is a data extension of CAASysCylinder
//
CATImplementClass(CAAEVisVisuCylinder, DataExtension, CATBaseUnknown, CAASysCylinder);

// 
// To declare that CAAEVisVisuCylinder implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysCylinder CATI3DGeoVisu  libCAAVisGeoModel
//

//--------------------------------------------------------------------------------------------

CAAEVisVisuCylinder::CAAEVisVisuCylinder()
{
  cout << "CAAEVisVisuCylinder::CAAEVisVisuCylinder" << endl;
}

CAAEVisVisuCylinder::~CAAEVisVisuCylinder()
{
  cout << "CAAEVisVisuCylinder::~CAAEVisVisuCylinder" << endl;
}

CATRep * CAAEVisVisuCylinder::BuildRep()
{
  cout << "CAAEVisVisuCylinder::BuildRep" << endl;

  // The rep to return
  CAT3DCustomRep         * pCylinderRep = NULL ;
  
  CAAISysCylinder * piSysCylinder = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysCylinder, (void**)&piSysCylinder);

  if (SUCCEEDED(rc))
  {

     // Retrieves information about the Cylinder
     CATMathPoint Base, Top ;
     float radius ;

     piSysCylinder->GetBasePoint(Base);
     piSysCylinder->GetRadius(radius);
     piSysCylinder->GetTopPoint(Top);

     // Done with the interface pointer
     piSysCylinder -> Release();
     piSysCylinder = NULL ;

     // Creation of the 3D graphic representation 
     pCylinderRep = new CAT3DCustomRep();

     // Creation of the Graphic Primitive dedicated to the Cylinder
	 float aBase[3] ;
	 float aExtrusion[3]  ;
	 aBase[0] = Base.GetX() ;
	 aBase[1] = Base.GetY() ;
	 aBase[2] = Base.GetZ() ;

     CATMathVector Extrusion = Top - Base ;
     
     aExtrusion[0] = Extrusion.GetX() ;
	 aExtrusion[1] = Extrusion.GetY() ;
	 aExtrusion[2] = Extrusion.GetZ() ;
	 
	 float sag = .002f ;

	 CAT3DCylinderGP * pCylinderGp = new CAT3DCylinderGP(aBase,aExtrusion,radius,sag);

     // Default attribut graphique 
     CATGraphicAttributeSet  CylinderGa ;

	 // It's a Volumic GP 
     CylinderGa.SetType(3) ;

     // Association of the Gp and the Ga to the Representation 
     pCylinderRep->AddGP(pCylinderGp,CylinderGa);

     // Sets a Bounding Sphere 
	 CATMathVector V = (Top - Base)/2 ;

	 CATMathPoint Center =  Base + V ;
	 double norm = V.Norm() ;

	 // Radius = max between the radius of the cylinder and the half of the
	 // line
	 //
	 double RadiusBE = norm ;
	 if ( RadiusBE < radius )
	 {
        RadiusBE = radius ;
	 }

	 CAT3DBoundingSphere be(Center,RadiusBE);

     pCylinderRep->SetBoundingElement(be) ;

  }

  // The rep is kept in the adapter
  return pCylinderRep;
} 







