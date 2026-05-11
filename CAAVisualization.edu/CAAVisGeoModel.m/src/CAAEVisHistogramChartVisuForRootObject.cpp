// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEVisHistogramChartVisuForRootObject.h"

// CAASystem.edu Framework
#include "CAAISysCollection.h"
#include "CAAISysAccess.h"
#include "CAAISysPoint.h"
#include "CAAISysLine.h"
#include "CAAISysPlane.h"
#include "CAAISysEllipse.h"
#include "CAAISysCircle.h"    

// Visualization Framework 
#include "CAT2DCustomRep.h"
#include "CAT2DLineGP.h"
#include "CAT2DAnnotationTextGP.h"
#include "CAT2DPolygonGP.h"   

// System Framework 
#include "CATUnicodeString.h" 
 
// C++ standard Library
#include <iostream.h>

//-----------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CAAIVisHistogramChartVisu.h"
TIE_CAAIVisHistogramChartVisu(CAAEVisHistogramChartVisuForRootObject);

// To declare that the class is a data extension of the CAASysGeomRootObj component
//
CATImplementClass(CAAEVisHistogramChartVisuForRootObject,DataExtension,CATBaseUnknown,CAASysGeomRootObj);
// 
// To declare that CAAEVisHistogramChartVisuForRootObject implements CAAIVisHistogramChartVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysGeomRootObj  CAAIVisHistogramChartVisu  libCAAVisGeoModel
//
//-----------------------------------------------------------------------------

CAAEVisHistogramChartVisuForRootObject::CAAEVisHistogramChartVisuForRootObject()
{
  cout << "CAAEVisHistogramChartVisuForRootObject::CAAEVisHistogramChartVisuForRootObject" << endl;
}

CAAEVisHistogramChartVisuForRootObject::~CAAEVisHistogramChartVisuForRootObject()
{
  cout << "CAAEVisHistogramChartVisuForRootObject::~CAAEVisHistogramChartVisuForRootObject" << endl;
}

CATRep * CAAEVisHistogramChartVisuForRootObject::BuildRep()
{
  cout << "CAAEVisHistogramChartVisuForRootObject::BuildRep" << endl;

  CAT2DCustomRep    * pRepToReturn = NULL ;

  pRepToReturn = new CAT2DCustomRep();


  // ---------------------------
  // Constructs Texts
  // ---------------------------
  CATGraphicAttributeSet TextGa ;
  CATUnicodeString TextTitle ;
  float distance = 10.f;
  float pas      = 10.f + 50.f ;
  float            TextOrigin[2] ;
  TextOrigin[1] = -10.f ;
  
  CATAnchorPoint      TextPosition =  BOTTOM_LEFT ;
  float            TextHeight   = 9.f ;

  TextTitle = "Point";
  TextOrigin[0] = distance ;
  CAT2DAnnotationTextGP * pPointTextGp = new CAT2DAnnotationTextGP(TextOrigin,TextTitle,TextPosition,TextHeight);
  distance += pas ;

  TextOrigin[0] = distance ;
  TextTitle = "Line" ;
  CAT2DAnnotationTextGP * pLineTextGp = new CAT2DAnnotationTextGP(TextOrigin,TextTitle,TextPosition,TextHeight);
  distance += pas ;

  TextOrigin[0] = distance ;
  TextTitle = "Plane";
  CAT2DAnnotationTextGP * pPlaneTextGp = new CAT2DAnnotationTextGP(TextOrigin,TextTitle,TextPosition,TextHeight);
  distance += pas ;

  TextOrigin[0] = distance ;
  TextTitle = "Circle";
  CAT2DAnnotationTextGP * pCircleTextGp = new CAT2DAnnotationTextGP(TextOrigin,TextTitle,TextPosition,TextHeight);
  distance += pas ;

  TextOrigin[0] = distance ;
  TextTitle = "Ellipse";
  CAT2DAnnotationTextGP * pEllipseTextGp = new CAT2DAnnotationTextGP(TextOrigin,TextTitle,TextPosition,TextHeight);
  distance += pas ;

  pRepToReturn->AddGP(pPointTextGp,TextGa);
  pRepToReturn->AddGP(pLineTextGp,TextGa) ;
  pRepToReturn->AddGP(pPlaneTextGp,TextGa);
  pRepToReturn->AddGP(pCircleTextGp,TextGa);
  pRepToReturn->AddGP(pEllipseTextGp,TextGa);
  

  // --------------------------------------
  // Retrieves the count of each component
  // --------------------------------------
  // With the CAAISysAccess interface we retrieve the container which contains
  // the UIActivable root object and all component of the model
  //

  int Histogram[5] ;
  int i;
  for (i=0; i < 5 ; i++ )
  {
     Histogram[i] = 0 ;
  }

  CAAISysAccess * piSysAccess = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysAccess, (void**)&piSysAccess);
  if (SUCCEEDED(rc))
  {
     // Retrieves the container 
     CATBaseUnknown * piBuknContainer = NULL ;
     rc = piSysAccess->GetContainer(&piBuknContainer);
     if (SUCCEEDED(rc))
     {
        // Retrieves the collection
        CAAISysCollection * piSysCollection = NULL;                
        rc = piBuknContainer->QueryInterface(IID_CAAISysCollection, 
                                          (void**)&piSysCollection);
        if (SUCCEEDED(rc))
        {
           // Retrieves the count of object in the container
           int Count(0);
           piSysCollection->GetNumberOfObjects(&Count);
           
           // The first object of the list is itself (the root object) 
           int i;
           for (i=2; i<=Count; i++)
           {
              // Retrieves the ieme object
              CATBaseUnknown * pBuknObject = NULL ;
              rc = piSysCollection->GetObject(i, &pBuknObject);

			  if ( SUCCEEDED(rc) )
			  {
			     CAAISysPoint *pISysPoint = NULL;
		         rc = pBuknObject->QueryInterface(IID_CAAISysPoint,(void**)&pISysPoint);
				                   
                 if ( SUCCEEDED(rc) )
				 {
                       pISysPoint->Release();
                       pISysPoint= NULL ;
                       Histogram[0] += 1;
				 }

				 CAAISysLine *pISysLine = NULL;
                 rc = pBuknObject->QueryInterface(IID_CAAISysLine, (void**)&pISysLine);				                  
                 if ( SUCCEEDED(rc) )
				 { 
                        pISysLine->Release();
	                    pISysLine= NULL ;
                        Histogram[1] += 1;
				 }

                 CAAISysPlane *pISysPlane = NULL;
                 rc = pBuknObject->QueryInterface(IID_CAAISysPlane, (void**)&pISysPlane);
				                                       
                 if ( SUCCEEDED(rc) )
				 {
	                    pISysPlane->Release();
	                    pISysPlane= NULL ;
                        Histogram[2] += 1;
				 }

                 CAAISysCircle *pISysCircle = NULL;
                 rc = pBuknObject->QueryInterface(IID_CAAISysCircle,(void**)&pISysCircle);
				                               
                 if ( SUCCEEDED(rc) )
				 {
                         pISysCircle->Release();
	                     pISysCircle= NULL ;
                         Histogram[3] += 1;
				 }
			  
                 CAAISysEllipse *pISysEllipse = NULL;
                 rc = pBuknObject->QueryInterface(IID_CAAISysEllipse,(void**)&pISysEllipse);
				                                      
                 if ( SUCCEEDED(rc) )
				 {
                        pISysEllipse->Release();
	                    pISysEllipse= NULL ;
                        Histogram[4] += 1;
				 }
               
                 // Done with the pointer
                 pBuknObject->Release();
                 pBuknObject = NULL ;
			  }

           } 
           // Done with the collection pointer
           piSysCollection -> Release();
		   piSysCollection = NULL;
        } 
        // Done with the container pointer
        piBuknContainer -> Release();
        piBuknContainer = NULL ;
     }
     // Done with the access pointer
     piSysAccess -> Release();
     piSysAccess = NULL ;
  }

  // -----------------
  // Constructs Boxes
  // ------------------
  int HistogramColor[5];
  HistogramColor[0] = GREEN ; 
  HistogramColor[1] = RED   ; 
  HistogramColor[2] = WHITE ; 
  HistogramColor[3] = BLUE  ; 
  HistogramColor[4] = YELLOW ; 

  float Xposition = 10 ;
  CATGraphicAttributeSet BoxeGa ;
  float aPointBoxe[8];
  int maxPoint = -100 ;
  int j;
  for (j=0; j < 5 ; j++)
  {
	  // Change the color of the box for each type of component
	  BoxeGa.SetColor(HistogramColor[j]);
	  
	  if ( 0 != Histogram[j] )
	  {
		 if ( Histogram[j] > maxPoint ) 
		 {
             maxPoint = Histogram[j] ;
		 }

		 aPointBoxe[0] = Xposition ; aPointBoxe[1] = 10.f ;
		 aPointBoxe[2] = Xposition ; aPointBoxe[3] = 10.f + Histogram[j]*20;
		 aPointBoxe[4] = Xposition + 50.f ; aPointBoxe[5] = 10.f + Histogram[j]*20;
		 aPointBoxe[6] = Xposition + 50.f ; aPointBoxe[7] = 10.f ;

         CAT2DPolygonGP * pBoxeGp = new CAT2DPolygonGP(aPointBoxe,4,FILL);
         pRepToReturn->AddGP(pBoxeGp,BoxeGa); 

		 TextOrigin[0] = Xposition + 25.f ; TextOrigin[1] = aPointBoxe[3] - 15.f ;
		 TextPosition = BASE_CENTER ;
		 TextHeight = 15.f ;
		 TextTitle.BuildFromNum(Histogram[j]);
         CAT2DAnnotationTextGP * pValueGp = new CAT2DAnnotationTextGP(TextOrigin,TextTitle,TextPosition,TextHeight);
         pRepToReturn->AddGP(pValueGp,TextGa); 
	  }

      Xposition += 60 ;
  }

  // --------------
  // Constructs axis 
  // --------------

  float aPoint[4];
  CATGraphicAttributeSet LineGa ;
  LineGa.SetThickness(2);

  // The X Line has always the same size
  aPoint[0] = 0.0 ; aPoint[1] = 0.0 ; 
  aPoint[2] = 300.0 ; aPoint[3] = 0.0 ;
  CAT2DLineGP * pLineHoriGp = new CAT2DLineGP(aPoint,2);

   // The Y Line 's size depend on the max of component
  float Height (0.f);
  if ( -100 == maxPoint )
  {
	  Height = 50.f ;
  }else
  {
      Height =  10.f + maxPoint*20 + 50.f ;
  }
  aPoint[0] = 0.0 ; aPoint[1] = 0.0 ; 
  aPoint[2] = 0.0 ; aPoint[3] = Height;
  CAT2DLineGP * pLineVertGp = new CAT2DLineGP(aPoint,2);

  pRepToReturn->AddGP(pLineHoriGp,LineGa);
  pRepToReturn->AddGP(pLineVertGp,LineGa);

  // -------------------------
  // Sets the bounding sphere
  // --------------------------
  CAT2DBoundingBox be(0.f,300.f,-20.f,Height) ;
  pRepToReturn->SetBoundingElement(be);

  return pRepToReturn ;
}

