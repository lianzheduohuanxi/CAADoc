// COPYRIGHT DASSAULT SYSTEMES 2000

// Local Framework
#include "CAAEVis3DGeoVisuForSphere.h"
#include "CAAIVisModelSphere.h"

// Mathematic FW
#include "CATMathPointf.h"

// Visualization framework
#include "CAT3DSimpleSphereRep.h"

// Standard Library
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVis3DGeoVisuForSphere);

// To declare that the class is a data extension of CAAVisModelSphere
//
CATImplementClass(CAAEVis3DGeoVisuForSphere,DataExtension,CATBaseUnknown,CAAVisModelSphere);

// 
// To declare that CAAEVis3DGeoVisuForSphere implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAAVisModelSphere CATI3DGeoVisu  libCAAVisManagerImpl
//
//--------------------------------------------------------------------------------------------

CAAEVis3DGeoVisuForSphere::CAAEVis3DGeoVisuForSphere()
{
  cout << "CAAEVis3DGeoVisuForSphere::CAAEVis3DGeoVisuForSphere" << endl;
}

//--------------------------------------------------------------------------------------------

CAAEVis3DGeoVisuForSphere::~CAAEVis3DGeoVisuForSphere()
{
  cout << "CAAEVis3DGeoVisuForSphere::~CAAEVis3DGeoVisuForSphere" << endl;
}

//--------------------------------------------------------------------------------------------

CATRep * CAAEVis3DGeoVisuForSphere::BuildRep()
{
   CAT3DSimpleSphereRep * pSphereRep = NULL ;

   CAAIVisModelSphere *piCAAIVisModelSphere = NULL ;
   HRESULT rc = QueryInterface(IID_CAAIVisModelSphere, (void**)&piCAAIVisModelSphere);
   if (SUCCEEDED(rc))
   {
      // Retrieves Data
      float Radius ;
      piCAAIVisModelSphere->GetRadius(Radius);
      CATMathPointf Center ;
      piCAAIVisModelSphere->GetCenter(Center);
   
      piCAAIVisModelSphere->Release();
      piCAAIVisModelSphere = NULL ;

      // Creates the graphic representation
      pSphereRep = new CAT3DSimpleSphereRep(Center,Radius);
   }
   
   return pSphereRep ; 
}
