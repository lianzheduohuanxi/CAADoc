// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEVisVisuCuboid.h"

// CAASystem.edu Framework
#include "CAAISysCuboid.h" 

// Visualizatiuon Framework 
#include "CAT3DCuboidRep.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

// other
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuCuboid);

// To declare that the class is a data extension of CAASysCuboid
//
CATImplementClass(CAAEVisVisuCuboid, DataExtension, CATBaseUnknown, CAASysCuboid );

// 
// To declare that CAAEVisVisuCuboid implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysCuboid CATI3DGeoVisu  libCAAVisGeoModel
//

//--------------------------------------------------------------------------------------------

CAAEVisVisuCuboid::CAAEVisVisuCuboid()
{
  cout << "CAAEVisVisuCuboid::CAAEVisVisuCuboid" << endl;
}

CAAEVisVisuCuboid::~CAAEVisVisuCuboid()
{
  cout << "CAAEVisVisuCuboid::~CAAEVisVisuCuboid" << endl;
}

CATRep * CAAEVisVisuCuboid::BuildRep()
{
  cout << "CAAEVisVisuCuboid::BuildRep" << endl;

  // The rep to return 
  CAT3DCuboidRep *pCuboidRep = NULL ;

  CAAISysCuboid * piSysCuboid = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysCuboid, (void**)&piSysCuboid);

  if (SUCCEEDED(rc))
  {
     // Retrieves the corner origin of the cuboid
     CATMathPoint Corner ;
     piSysCuboid->GetOrigin(Corner);

     // Retrieves 3 vectors 
     CATMathVector Width,Height,Depth ;
     piSysCuboid->GetVectors(Width,Depth,Height);

     // Done with the Cuboid
     piSysCuboid -> Release();
     piSysCuboid = NULL ;

     // Creation of the 3D graphic representation
     pCuboidRep  = new CAT3DCuboidRep(Corner,Width,Depth,Height,WHITE) ;

     // Sets the bounding sphere
     CATMathVector Sum = (Width + Depth + Height)/2 ;
     CATMathPoint Center = Corner + Sum ;
     double Radius = Sum.Norm();
     
     CAT3DBoundingSphere be(Center,Radius) ;
     pCuboidRep->SetBoundingElement(be);

  }

  return pCuboidRep;
}


