// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAECafVisuEllipse.h"

// CAASystem.edu Framework
#include "CAAISysEllipse.h"

// CAACafApplicationFrame.edu Framework
#include "GetCAACafGeometryEltSettingCtrl.h" // to read the setting file
#include "CAAICafGeometryEltSettingAtt.h"    

// Visualization Framework 
#include "CAT3DCustomRep.h"
#include "CAT3DArcEllipseGP.h"
#include "CAT3DMarkerGP.h"     // For the implicite center point

// System FW
#include "CATString.h"  

// Mathematic Framework 
#include "CATMathPoint.h"
#include "CATMathVector.h"

// Others
#include "iostream.h"

//--------------------------------------------------------------------------------------------
// Creates the TIE object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAECafVisuEllipse);

// To declare that the class derives is a data extension of CAASysEllipse
//
CATImplementClass(CAAECafVisuEllipse, DataExtension, CATBaseUnknown, CAASysEllipse);

// 
// To declare that CAAECafVisuEllipse implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysEllipse CATI3DGeoVisu  libCAACafUseToolsOptions
//
//--------------------------------------------------------------------------------------------

CAAECafVisuEllipse::CAAECafVisuEllipse()
{
  cout << "CAAECafVisuEllipse::CAAECafVisuEllipse" << endl;
}

CAAECafVisuEllipse::~CAAECafVisuEllipse()
{
  cout << "CAAECafVisuEllipse::~CAAECafVisuEllipse" << endl;
}

CATRep * CAAECafVisuEllipse::BuildRep()
{
  cout << "CAAECafVisuEllipse::BuildRep" << endl;
  
  // The rep to return
  CAT3DCustomRep         * pEllipseRep = NULL ;
  
  CAAISysEllipse *  piSysEllipse = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysEllipse, (void**)&piSysEllipse);
  if (SUCCEEDED(rc))
  {
     // Retrieves information about the ellipse
     CATMathPoint center;
     float XRadius, YRadius ;
     CATMathVector normal, axis ;

     piSysEllipse->GetCenter(center);
     piSysEllipse->GetRadius(XRadius, YRadius);
     piSysEllipse->GetPlanar(normal,axis);

     // Done with the ellipse
     piSysEllipse->Release();
     piSysEllipse = NULL ;

     // Creation of the 3D graphic representation
     pEllipseRep = new CAT3DCustomRep();

     // Constructs the graphic primitive dedicated to the ellipse
     CAT3DArcEllipseGP * pEllipseGp = NULL ;
     pEllipseGp = new CAT3DArcEllipseGP(center,normal,XRadius,YRadius, axis);

     // Default attribut graphique 
     CATGraphicAttributeSet  EllipseGa ;

     // Association of the Gp and the Ga to the Representation
     pEllipseRep->AddGP(pEllipseGp,EllipseGa);

     // Draws the center point if necessary
     // The information is set in the file CAACafGeometryEltSetting.CATSetting. 
	 // To read this file we use its controller. 
	 //
     CAAICafGeometryEltSettingAtt * piSettingAtt = NULL ;
     HRESULT rc = ::GetCAACafGeometryEltSettingCtrl(IID_CAAICafGeometryEltSettingAtt,(void**)& piSettingAtt);

     if (SUCCEEDED(rc) )
     {
        CATString visibility ;
        piSettingAtt->GetImplPointVisibility(visibility);


        CATString ImplPointShowSt = "ImplPointShow";
        if ( ImplPointShowSt == visibility )
        {
           // Creation of the Graphic Primitive dedicated to the center point
		   float coord[3] ;
		   coord[0] = center.GetX() ; 
		   coord[1] = center.GetY(); 
		   coord[2] = center.GetZ() ; 
           CAT3DMarkerGP * pPointGp = new CAT3DMarkerGP(coord,1,SMALLDOT); 
           
		   pEllipseRep->AddGP(pPointGp,EllipseGa);

        }
        piSettingAtt->Release();
        piSettingAtt = NULL ;
     }


     // Computes the bounding sphere
     float max = XRadius ;
     if ( XRadius < YRadius ) max = YRadius ;
     CAT3DBoundingSphere be(center,max);

     // Sets the bounding sphere
     pEllipseRep->SetBoundingElement(be) ;

  }

  return pEllipseRep;
} 







