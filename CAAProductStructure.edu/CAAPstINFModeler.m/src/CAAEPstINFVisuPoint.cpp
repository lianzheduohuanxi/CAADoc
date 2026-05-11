// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFVisuPoint.h"

// Local Framework
#include "CAAIPstINFPoint.h" 

// Visualization Framework 
#include "CAT3DMarkerGP.h"
#include "CAT3DCustomRep.h"
#include "CATI3DGeoVisu.h"

// Others
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Tie the implementation to its interface
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEPstINFVisuPoint);

// To declare that the class is a data extension of CAAPstINFPoint
//
CATImplementClass(CAAEPstINFVisuPoint, DataExtension, CATBaseUnknown, CAAPstINFPoint );

// 
// To declare that CAAEPstINFVisuPoint implements CATI3DGeoVisu for the CAAPstINFPoint
// component, insert the following line in the interface dictionary:
//
//    CAAPstINFPoint CATI3DGeoVisu  libCAAPstINFModeler
//
//--------------------------------------------------------------------------------------------

CAAEPstINFVisuPoint::CAAEPstINFVisuPoint()
{
  cout << "*****CAAEPstINFVisuPoint::CAAEPstINFVisuPoint" << endl;
}

CAAEPstINFVisuPoint::~CAAEPstINFVisuPoint()
{
  cout << "*****CAAEPstINFVisuPoint::~CAAEPstINFVisuPoint" << endl;
}

CATRep * CAAEPstINFVisuPoint::BuildRep()
{
  cout << "*****CAAEPstINFVisuPoint::BuildRep" << endl;

  // The rep to return 
  CAT3DCustomRep *pPointRep = NULL ;

  CAAIPstINFPoint *piPstINFPoint = NULL;                
  HRESULT rc = QueryInterface(IID_CAAIPstINFPoint,
	                          (void**)&piPstINFPoint);
  
  if (SUCCEEDED(rc))
  {
     // Retrieves coordinates of the point
	 float coord[3];
	 double x;
	 rc = piPstINFPoint->GetX(&x);
	 if (FAILED(rc)) 
	 {
		 piPstINFPoint -> Release();
		 piPstINFPoint = NULL;
         return pPointRep;
	 }
	 coord[0] = x;
	 
	 double y;
	 rc = piPstINFPoint->GetY(&y);
	 if (FAILED(rc)) 
	 {
		 piPstINFPoint -> Release();
		 piPstINFPoint = NULL;
         return pPointRep;
	 }
	 coord[1] = y;
	 
	 double z;
	 rc = piPstINFPoint->GetZ(&z);
	 piPstINFPoint -> Release();
	 piPstINFPoint = NULL;
     if (FAILED(rc)) return pPointRep;
	 coord[2] = z;
	 
     // Creation of the 3D graphic representation
     pPointRep  = new CAT3DCustomRep() ;
	 cout << "Created CAT3DCustomRep OK" << endl;

     // Creation of the Graphic Primitive dedicated to the point
     CAT3DMarkerGP * pPointGp = new CAT3DMarkerGP(coord,1,CROSS);
	 cout << "Created CAT3DMarkerGP OK" << endl;

     // Default graphical attribute set 
     CATGraphicAttributeSet PointGa ;
     
     // Association of the Gp and the Ga to the Representation     
     pPointRep -> AddGP(pPointGp,PointGa);
	 cout << "Add GP OK" << endl;

     // Sets the bounding sphere
     CAT3DBoundingSphere be(coord,0.f,1.f) ;
     pPointRep->SetBoundingElement(be);

	 cout << "Bounding sphere set OK" << endl;
  }
  else cout << "QI on CAAIPstINFPoint KO" << endl;

  return pPointRep;
}


void CAAEPstINFVisuPoint::SetPointGraphicAttribute(CATRep *iRep, 
                                                   CATVisPropertyType iPropertyType,
                                                   CATVisPropertiesValues & iPropertyValue)
{
   cout << "  CAAEPstINFVisuPoint::SetPointGraphicAttribute " << endl;

   if ( NULL == iRep ) return;
  
   CAT3DCustomRep * pRepPoint = (CAT3DCustomRep *) iRep ;

   // The symbol property
   if ( (iPropertyType == CATVPAllPropertyType ) || ( iPropertyType == CATVPSymbol))
   {
      // retrieve the new symbol
	  unsigned int NewSymbol;
	  if (SUCCEEDED(iPropertyValue.GetSymbol(NewSymbol)))
	  {
         // Retrieve the current GP 
         CATGraphicPrimitive * pOldGP = pRepPoint->GetGP(0) ;
         if ( NULL != pOldGP )
         {
            CAT3DMarkerGP * pOldPointGP = (CAT3DMarkerGP *) pOldGP ;

            // retrieve the coordinate's point and the current symbol
            float * points = NULL;
            int nbPoints;
            SymbolType OldSymbol;
            
            pOldPointGP->Get(&points, &nbPoints, &OldSymbol);

            if ( NewSymbol != OldSymbol )
            {
               // Creation of a new marker with the new symbol
               CAT3DMarkerGP * pNewPointGP = new CAT3DMarkerGP(points,1,(SymbolType) NewSymbol);

               //Replace the marker with the same graphic attribute
               pRepPoint->Modify(pOldPointGP,pNewPointGP,NULL);

               //The old GP must be deleted
               CATGraphicPrimitive::Destroy(pOldPointGP);
               pOldPointGP = NULL ;
            }
         }
	  } 
  }

  // The color property
  if ( (iPropertyType == CATVPAllPropertyType ) || ( iPropertyType == CATVPColor))   
  {
    CATGraphicAttributeSet * pAg = &(pRepPoint->GetAttribut(0));
    SetGraphicAttributeSet (pAg, CATVPColor, iPropertyValue);      
  }

}
