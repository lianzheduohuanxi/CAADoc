// COPYRIGHT DASSAULT SYSTEMES 1999

//Local Framework
#include "CAAEVisVisuWireBox.h"

// CAASystem.edu Framework
#include "CAAIVisWireBox.h"

// Visualization Framework 
#include "CAT3DCustomRep.h"
#include "CAT3DLineGP.h" 

// mathematics Framework
#include "CATMathPoint.h" 
#include "CATMathVector.h" 
// Others
#include "iostream.h"

//---------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuWireBox);

// To declare that the class is a data extension of CAASysPlane
//
CATImplementClass(CAAEVisVisuWireBox, DataExtension, CATBaseUnknown, CAAVisWireBox);

// 
// To declare that CAAEVisVisuWireBox implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAAVisWireBox CATI3DGeoVisu  libCAAVisWireBoxComp
//

//---------------------------------------------------------------------------

CAAEVisVisuWireBox::CAAEVisVisuWireBox()
{
  cout << "CAAEVisVisuWireBox::CAAEVisVisuWireBox" << endl;
}

CAAEVisVisuWireBox::~CAAEVisVisuWireBox()
{
  cout << "CAAEVisVisuWireBox::~CAAEVisVisuWireBox" << endl;
}

CATRep * CAAEVisVisuWireBox::BuildRep()
{
  cout << "CAAEVisVisuWireBox::BuildRep" << endl;
  
   // The rep to return
   CAT3DCustomRep         * pWireBoxRep = NULL ;


 
   CAAIVisWireBox * piVisWireBox = NULL;                
   HRESULT rc = QueryInterface(IID_CAAIVisWireBox, (void**)&piVisWireBox);
   if (SUCCEEDED(rc))
   {
       float DimBox = .2f ;
       piVisWireBox->GetDimBox(&DimBox) ;
       

       CATMathPoint CenterBox ;
       piVisWireBox->GetCenterBox(CenterBox) ;

       piVisWireBox->Release();
       piVisWireBox = NULL ;

       pWireBoxRep = new CAT3DCustomRep();

   // Default Attribut graphique 
   CATGraphicAttributeSet   BoxGa ;

   float Cx = CenterBox.GetX() ;
   float Cy = CenterBox.GetY() ;
   float Cz = CenterBox.GetZ() ;

   float Tab1[12] ;
   Tab1[0] = Cx + DimBox; Tab1[1]  = Cy - DimBox; Tab1[2]  = Cz + DimBox ;
   Tab1[3] = Cx - DimBox; Tab1[4]  = Cy - DimBox; Tab1[5]  = Cz + DimBox ;
   Tab1[6] = Cx - DimBox; Tab1[7]  = Cy + DimBox; Tab1[8]  = Cz + DimBox ;
   Tab1[9] = Cx + DimBox; Tab1[10] = Cy + DimBox; Tab1[11] = Cz + DimBox ;
   CATMathPoint P1 (Tab1[0],Tab1[1],Tab1[2]) ;

   CAT3DLineGP * pPolyline1 = new CAT3DLineGP (Tab1, 4,ALLOCATE, LINE_LOOP);

   float Tab2[12] ;
   Tab2[0] = Cx + DimBox; Tab2[1]  = Cy - DimBox; Tab2[2]  = Cz - DimBox ;
   Tab2[3] = Cx - DimBox; Tab2[4]  = Cy - DimBox; Tab2[5]  = Cz - DimBox ;
   Tab2[6] = Cx - DimBox; Tab2[7]  = Cy + DimBox; Tab2[8]  = Cz - DimBox ;
   Tab2[9] = Cx + DimBox; Tab2[10] = Cy + DimBox; Tab2[11] = Cz - DimBox ;
   
   CATMathPoint P2 (Tab2[6],Tab2[7],Tab2[8]) ;

   CAT3DLineGP * pPolyline2 = new CAT3DLineGP (Tab2, 4,ALLOCATE, LINE_LOOP);

   float Tab3[8*3] ;
   Tab3[0] = Tab1[0] ; Tab3[1]  = Tab1[1] ;Tab3[2]  = Tab1[2] ;
   Tab3[3] = Tab2[0] ; Tab3[4]  = Tab2[1] ;Tab3[5]  = Tab2[2] ;

   Tab3[6] = Tab1[3] ; Tab3[7]  = Tab1[4] ;Tab3[8]  = Tab1[5] ;
   Tab3[9] = Tab2[3] ; Tab3[10] = Tab2[4] ;Tab3[11] = Tab2[5] ;

   Tab3[12] = Tab1[6] ; Tab3[13] = Tab1[7] ;Tab3[14] = Tab1[8] ;
   Tab3[15] = Tab2[6] ; Tab3[16] = Tab2[7] ;Tab3[17] = Tab2[8] ;

   Tab3[18] = Tab1[9] ; Tab3[19] = Tab1[10] ;Tab3[20] = Tab1[11] ;
   Tab3[21] = Tab2[9] ; Tab3[22] = Tab2[10] ;Tab3[23] = Tab2[11] ;

   CAT3DLineGP * pPolyline3 = new CAT3DLineGP (Tab3, 8,ALLOCATE, LINE);

   pWireBoxRep->AddGP(pPolyline1,BoxGa);
   pWireBoxRep->AddGP(pPolyline2,BoxGa);
   pWireBoxRep->AddGP(pPolyline3,BoxGa);

   // Computes the Bounding sphere
   CATMathVector Diagonal = P2-P1 ;
   double Radius = Diagonal.Norm() / 2;
     
   CAT3DBoundingSphere be(CenterBox,Radius) ;
   pWireBoxRep->SetBoundingElement(be);
   }

   return pWireBoxRep;
} 







