// COPYRIGHT DASSAULT SYSTEMES 2002

//Local Framework
#include "CAAEPstINFVisuLine.h"

// Local Framework
#include "CAAIPstINFLine.h"
#include "CAAIPstINFPoint.h"

// Visualization Framework 
#include "CAT3DCustomRep.h"
#include "CAT3DLineGP.h"
#include "CATMathPoint.h"
#include "CATI3DGeoVisu.h"

// Mathematics Framework
#include "CATMathVector.h"

// Others
#include "iostream.h"

//-----------------------------------------------------------------------------
// Tie the implementation to its interface
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEPstINFVisuLine);

// To declare that the class is a data extension of CAASysLine
//
CATImplementClass(CAAEPstINFVisuLine,
				  DataExtension,
				  CATBaseUnknown,
				  CAAPstINFLine);
// 
// To declare that CAAEPstINFVisuLine implements CATI3DGeoVisu for the CAAPstINFLine
// component, insert the following line in the interface dictionary:
//
//    CAAPstINFLine CATI3DGeoVisu  libCAAIntegrateNewFeaturesImpl
//

//-----------------------------------------------------------------------------

CAAEPstINFVisuLine::CAAEPstINFVisuLine()
{
  cout << "*****CAAEPstINFVisuLine::CAAEPstINFVisuLine" << endl;
}

CAAEPstINFVisuLine::~CAAEPstINFVisuLine()
{
  cout << "*****CAAEPstINFVisuLine::~CAAEPstINFVisuLine" << endl;
}

CATRep * CAAEPstINFVisuLine::BuildRep()
{
  cout << "*****CAAEPstINFVisuLine::BuildRep" << endl;

  // The rep to return
  CAT3DCustomRep *pLineRep = NULL ;

  CAAIPstINFLine *piPstINFLine = NULL;                
  HRESULT rc = QueryInterface(IID_CAAIPstINFLine,
	                          (void**)&piPstINFLine);

  if (SUCCEEDED(rc))
  {

     // Retrieves information about the Line
     CATISpecObject *piStartPoint = NULL;
	 CATISpecObject *piEndPoint = NULL;
     rc = piPstINFLine -> GetPoint(1, &piStartPoint);
	 if (FAILED(rc) || (NULL == piStartPoint))
	 {
		 piPstINFLine -> Release();
		 piPstINFLine = NULL;
		 return pLineRep;
	 }
	 rc = piPstINFLine -> GetPoint(2, &piEndPoint);
     piPstINFLine -> Release();
     piPstINFLine = NULL ;
	 if (FAILED(rc) || (NULL == piEndPoint)) 
	 {
		 piStartPoint -> Release();
		 piStartPoint = NULL;
		 return pLineRep;
	 }

	 // Creation of the Graphic Primitive dedicated to the line
     float coord[6] ;
	 double dCoord;

     CAAIPstINFPoint *piPstINFPointOnSpecObject = NULL;                
     HRESULT rc = piStartPoint -> QueryInterface(IID_CAAIPstINFPoint,
		                                         (void**)&piPstINFPointOnSpecObject);
	 piStartPoint -> Release();
	 piStartPoint = NULL;
     if (FAILED(rc)) 
	 {
		 piEndPoint -> Release();
		 piEndPoint = NULL;
		 return pLineRep;
	 }

	 rc = piPstINFPointOnSpecObject -> GetX (&dCoord);
	 if (FAILED(rc))
	 {
         piEndPoint -> Release();
		 piEndPoint = NULL; 
		 piPstINFPointOnSpecObject -> Release();
	     piPstINFPointOnSpecObject = NULL;
		 return pLineRep;
	 }
	 coord[0] = dCoord;
	 rc = piPstINFPointOnSpecObject -> GetY (&dCoord);
     if (FAILED(rc))
	 {
		 piEndPoint -> Release();
		 piEndPoint = NULL;
		 piPstINFPointOnSpecObject -> Release();
	     piPstINFPointOnSpecObject = NULL;
		 return pLineRep;
	 }
	 coord[1] = dCoord;
	 rc = piPstINFPointOnSpecObject -> GetZ (&dCoord);
	 piPstINFPointOnSpecObject -> Release();
	 piPstINFPointOnSpecObject = NULL;
     if (FAILED(rc))
	 {
		 piEndPoint -> Release();
		 piEndPoint = NULL;
		 return pLineRep;
	 }
	 coord[2] = dCoord;

	 CATMathPoint start(coord[0],
		                coord[1],
						coord[2]);
      
     rc = piEndPoint -> QueryInterface(IID_CAAIPstINFPoint,
	                                   (void**)&piPstINFPointOnSpecObject);
	 piEndPoint -> Release();
	 piEndPoint = NULL;
     if (FAILED(rc)) return pLineRep;

	 rc = piPstINFPointOnSpecObject -> GetX (&dCoord);
     if (FAILED(rc))
	 {
		 piPstINFPointOnSpecObject -> Release();
	     piPstINFPointOnSpecObject = NULL;
		 return pLineRep;
	 }
     coord[3] = dCoord;
	 rc = piPstINFPointOnSpecObject -> GetY (&dCoord);
	 if (FAILED(rc))
	 {
		 piPstINFPointOnSpecObject -> Release();
	     piPstINFPointOnSpecObject = NULL;
		 return pLineRep;
	 }
	 coord[4] = dCoord;
	 rc = piPstINFPointOnSpecObject -> GetZ (&dCoord);
	 piPstINFPointOnSpecObject -> Release();
	 piPstINFPointOnSpecObject = NULL;
	 if (FAILED(rc)) return pLineRep;
     coord[5] = dCoord;

	 CATMathPoint end(coord[3],
		              coord[4],
					  coord[5]);

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
  cout << "QI on CAAIPstINFLine KO." << endl;

  return pLineRep;
} 

