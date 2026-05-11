// COPYRIGHT DASSAULT SYSTEMES 2002

// Local Framework
#include "CAAEPstINFVisuWire.h"

// Local Framework
#include "CAAIPstINFWire.h" 
#include "CAAIPstINFPoint.h" 

// Visualization Framework 
#include "CAT3DMarkerGP.h"
#include "CAT3DLineGP.h"
#include "CAT3DCustomRep.h"
#include "CATGraphicPrimitive.h"
#include "CATI3DGeoVisu.h"

// Mathematics Framework
#include "CATMathPoint.h"
#include "CATMathVector.h"

// ObjectModelerBase Framework
#include "CATISpecObject.h"
#include "CATListPtrCATISpecObject.h"

// Others
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Tie the implementation to its interface
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEPstINFVisuWire);

// To declare that the class is a data extension of CAAPstINFWire
//
CATImplementClass(CAAEPstINFVisuWire, DataExtension, CATBaseUnknown, CAAPstINFWire );

// 
// To declare that CAAEPstINFVisuWire implements CATI3DGeoVisu for the CAAPstINFWire
// component, insert the following line in the interface dictionary:
//
//    CAAPstINFWire CATI3DGeoVisu  libCAAPstINFModeler
//
//--------------------------------------------------------------------------------------------

CAAEPstINFVisuWire::CAAEPstINFVisuWire()
{
  cout << "*****CAAEPstINFVisuWire::CAAEPstINFVisuWire" << endl;
}

//-------------------------------------------------------------------------------------------

CAAEPstINFVisuWire::~CAAEPstINFVisuWire()
{
  cout << "*****CAAEPstINFVisuWire::~CAAEPstINFVisuWire" << endl;
}

//-------------------------------------------------------------------------------------------

CATRep * CAAEPstINFVisuWire::BuildRep()
{
  cout << "*****CAAEPstINFVisuWire::BuildRep" << endl;

  // The rep to return 
  CAT3DCustomRep *pWireRep = NULL ;


  CAAIPstINFWire *piPstINFWire = NULL;                
  HRESULT rc = QueryInterface(IID_CAAIPstINFWire,
	                          (void**)&piPstINFWire);
  
  if (SUCCEEDED(rc))
  {
     // Retrieve the points of the wire.
     CATLISTP(CATISpecObject) * pListOfPoint = NULL ;
     rc = piPstINFWire -> GetPoints(&pListOfPoint);
     if ( SUCCEEDED(rc) && NULL != pListOfPoint )
     {
        // Retrieve the coordinates (x,y,z) of the points
        int NbPoint = pListOfPoint->Size() ;
        CATMathPoint Extrem1, Extrem2 ;
        float * pCoordTable = new  float [NbPoint * 3 ] ;
        rc = RetrieveCoordinates(NbPoint,pListOfPoint,&pCoordTable,Extrem1,Extrem2);

        // No more need of the list of point
        for ( int i = 1 ; i <= NbPoint ; i++)
        {
	   CATISpecObject *pPoint = (*pListOfPoint)[i];
           if ( NULL != pPoint )
           {
               pPoint->Release();
               (*pListOfPoint)[i] = NULL ;
           }
        }

        delete pListOfPoint ;
        pListOfPoint = NULL ;

        if ( SUCCEEDED(rc) )
        {

           // Creation of the 3D graphic representation
           pWireRep  = new CAT3DCustomRep() ;

           // Creation of the graphic primitive dedicated to the points
           CAT3DMarkerGP * pPointGp = new CAT3DMarkerGP(pCoordTable,NbPoint,CROSS);

           CATGraphicAttributeSet PointGa ;
           pWireRep -> AddGP(pPointGp,PointGa);

           // Constructs the graphic primitive dedicated to the lines
           CAT3DLineGP * pLineGp = new CAT3DLineGP(pCoordTable,NbPoint,ALLOCATE, LINE_STRIP) ;
 
           CATGraphicAttributeSet LineGa ;
           pWireRep -> AddGP(pLineGp,LineGa);

           // Sets the bounding sphere
           CATMathPoint center =  Extrem1 + ((Extrem2-Extrem1) / 2.f)  ;
           float radius = (float) Extrem1.DistanceTo(center);
           CAT3DBoundingSphere be(center,radius);
           pWireRep->SetBoundingElement(be);
        }
     
        delete [] pCoordTable ;
        pCoordTable = NULL ;
     }
     piPstINFWire -> Release();
     piPstINFWire = NULL ;
  }
  
  return pWireRep;
}

//-------------------------------------------------------------------------------------------

HRESULT CAAEPstINFVisuWire::RetrieveCoordinates(int iNbPoint,
                                                CATLISTP(CATISpecObject) * ipListOfPoint,
                                                float ** opCoordTable,
                                                CATMathPoint & ioExtrem1,
                                                CATMathPoint & ioExtrem2)
{
    cout <<" CAAEPstINFVisuWire::RetrieveCoordinates" << iNbPoint << endl;

    HRESULT rc = S_OK ;

    double minx (100000.f),miny(100000.f),minz(100000.f) ;
    double maxx (-100000.f),maxy(-100000.f),maxz(-100000.f) ;
    double dCoord; 

    int i = 1 ;
    while ( (i <= iNbPoint) && ( S_OK == rc) )
    {        
        CATISpecObject * pObject = (*ipListOfPoint)[i] ;
        if ( pObject != NULL )
        {
           CAAIPstINFPoint *piPstINFPointOnSpecObject = NULL;                
           HRESULT rc = pObject -> QueryInterface(IID_CAAIPstINFPoint,
		                                         (void**)&piPstINFPointOnSpecObject);
           if ( SUCCEEDED(rc) )
           {
              piPstINFPointOnSpecObject -> GetX (&dCoord);
	          (*opCoordTable)[(i-1)*3] = dCoord;

              if ( dCoord > maxx ) maxx = dCoord;
              if ( dCoord < minx ) minx = dCoord;

	          piPstINFPointOnSpecObject -> GetY (&dCoord);
	          (*opCoordTable)[(i-1)*3 +1] = dCoord;
              
              if ( dCoord > maxy ) maxy = dCoord;
              if ( dCoord < miny ) miny = dCoord;

	          piPstINFPointOnSpecObject -> GetZ (&dCoord);
	          (*opCoordTable)[(i-1)*3 + 2] = dCoord;

              if ( dCoord > maxz ) maxz = dCoord;
              if ( dCoord < minz ) minz = dCoord;

              piPstINFPointOnSpecObject->Release();
              piPstINFPointOnSpecObject = NULL ;

           }else rc = E_FAIL ;

        }
        i++ ;
    }

    ioExtrem1.SetCoord(maxx,maxy,minz);
    ioExtrem2.SetCoord(minx,miny,maxz);

    return rc;
}

//-------------------------------------------------------------------------------------------

void CAAEPstINFVisuWire::SetPointGraphicAttribute(CATRep *iRep, 
                                                   CATVisPropertyType iPropertyType,
                                                   CATVisPropertiesValues & iPropertyValue)
{
   cout << "  CAAEPstINFVisuWire::SetPointGraphicAttribute " << endl;

   if ( NULL == iRep ) return;
  
   CAT3DCustomRep * pRepWire = (CAT3DCustomRep *) iRep ;

   // Retrieve the CAT3DMarkerGP
   int NbGP = pRepWire->GetGPSize();
   if ( NbGP != 2 ) return ;

   CATGraphicPrimitive * pGP = pRepWire->GetGP(0) ;
   if ( NULL == pGP || 0 == pGP->IsAKindOf("CAT3DMarkerGP") ) return;

   // Change the symbol
   if ( (iPropertyType == CATVPAllPropertyType ) || ( iPropertyType == CATVPSymbol))
   {
      // Retrieve the new symbol
	  unsigned int NewSymbol;
	  if (SUCCEEDED(iPropertyValue.GetSymbol(NewSymbol)))
	  {
         // Retrieve the current GP 
         CAT3DMarkerGP * pOldPointGP = (CAT3DMarkerGP *) pGP ;
         if ( NULL != pOldPointGP )
         {
            // retrieve the coordinate's points and the current symbol
            float * points = NULL;
            int nbPoints;
            SymbolType OldSymbol;
            
            pOldPointGP->Get(&points, &nbPoints, &OldSymbol);

            if ( NewSymbol != OldSymbol )
            {
               // Creation of a new marker with the new symbol
               CAT3DMarkerGP * pNewPointGP = new CAT3DMarkerGP(points,nbPoints,(SymbolType) NewSymbol);

               //Replace the marker with the same graphic attribute
               pRepWire->Modify(pOldPointGP,pNewPointGP,NULL);

               //The old GP must be deleted
               CATGraphicPrimitive::Destroy(pOldPointGP);
               pOldPointGP = NULL ;
            }
         }
	  } 
  }

  // Change the color
  if ( (iPropertyType == CATVPAllPropertyType ) || ( iPropertyType == CATVPColor))   
  {
    // The color of the marker is modified
    CATGraphicAttributeSet * pAg = &(pRepWire->GetAttribut(0));
    SetGraphicAttributeSet (pAg, CATVPColor, iPropertyValue);      
  }

}

//-------------------------------------------------------------------------------------------

void CAAEPstINFVisuWire::SetLineGraphicAttribute(CATRep *iRep, 
                                                   CATVisPropertyType iPropertyType,
                                                   CATVisPropertiesValues & iPropertyValue)
{
   cout << "  CAAEPstINFVisuWire::SetLineGraphicAttribute " << endl;

   if ( NULL == iRep ) return;
  
   CAT3DCustomRep * pRepWire = (CAT3DCustomRep *) iRep ;

   // Test that the second GP is the GP which contains the lines
   int NbGP = pRepWire->GetGPSize();
   if ( NbGP != 2 ) return ;

   CATGraphicPrimitive * pGP = pRepWire->GetGP(1) ;
   if ( NULL == pGP || 0 == pGP->IsAKindOf("CAT3DLineGP") ) return ;
 
   // Change the thickness
   if ( (iPropertyType == CATVPAllPropertyType ) || ( iPropertyType == CATVPWidth))
   {
      CATGraphicAttributeSet * pAg = &(pRepWire->GetAttribut(1));
      SetGraphicAttributeSet (pAg, CATVPWidth, iPropertyValue); 
   }
   
   // Change the type 
   if ( (iPropertyType == CATVPAllPropertyType ) || ( iPropertyType == CATVPLineType ))
   {
      CATGraphicAttributeSet * pAg = &(pRepWire->GetAttribut(1));
      SetGraphicAttributeSet (pAg, CATVPLineType, iPropertyValue); 
   }

   // Change the color 
   if ( (iPropertyType == CATVPAllPropertyType ) || ( iPropertyType == CATVPColor))   
   {
      CATGraphicAttributeSet * pAg = &(pRepWire->GetAttribut(1));
      SetGraphicAttributeSet (pAg, CATVPColor, iPropertyValue);      
   }
}
