// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAEVisVisuPolyline.h"

// CAASystem.edu Framework
#include "CAAISysPolyline.h" 

// Visualization Framework 
#include "CAT3DLineGP.h"
#include "CAT3DCustomRep.h"

// Mathematics Framework 
#include "CATMathPoint.h"
#include "CATMath.h"

// other
#include <iostream.h>

//-------------------------------------------------------------------------------------------
// Creates the TIE Object
#include "TIE_CATI3DGeoVisu.h"
TIE_CATI3DGeoVisu(CAAEVisVisuPolyline);

// To declare that the class is a data extension of CAASysPolyline
//
CATImplementClass(CAAEVisVisuPolyline, DataExtension, CATBaseUnknown, CAASysPolyline );

// 
// To declare that CAAEVisVisuPolyline implements CATI3DGeoVisu, insert 
// the following line in the interface dictionary:
//
//    CAASysPolyline CATI3DGeoVisu  libCAAVisGeoModel
//
//--------------------------------------------------------------------------------------------

CAAEVisVisuPolyline::CAAEVisVisuPolyline()
{
  cout << "CAAEVisVisuPolyline::CAAEVisVisuPolyline" << endl;
}

CAAEVisVisuPolyline::~CAAEVisVisuPolyline()
{
  cout << "CAAEVisVisuPolyline::~CAAEVisVisuPolyline" << endl;
}

CATRep * CAAEVisVisuPolyline::BuildRep()
{
  cout << "CAAEVisVisuPolyline::BuildRep" << endl;

  // The rep to return 
  CAT3DCustomRep *pPolylineRep = NULL ;

  CAAISysPolyline * piSysPolyline = NULL;                
  HRESULT rc = QueryInterface(IID_CAAISysPolyline, (void**)&piSysPolyline);
  if (SUCCEEDED(rc))
  {
     // Data to compute the Bounding Box       
     float xmin,ymin,zmin,xmax,ymax,zmax;
     xmin = 10000 ; ymin = 10000 ; zmin = 10000;
     xmax = -10000 ; ymax = -10000 ; zmax = -10000;
     
     // Retrieves coordinates of each point which form the Polyline
     int nbpoint(0);
     CATMathPoint *pTabPoint = NULL ;
     piSysPolyline->GetListPoint(&nbpoint, &pTabPoint);

     if ( 0 != nbpoint )
     {
        // Array of coodinates 
        float * pTabFloat = new float [3* nbpoint];
	 
        int i;
        for ( i=0; i < nbpoint ; i++ )
        {
           // Fills the array 
           pTabFloat[i*3]   = (float) pTabPoint[i].GetX() ;
           pTabFloat[i*3+1] = (float) pTabPoint[i].GetY() ;
           pTabFloat[i*3+2] = (float) pTabPoint[i].GetZ() ;

           // Computes the min and max on each axis
           if ( pTabFloat[i*3]   > xmax ) xmax = pTabFloat[i*3] ;
           if ( pTabFloat[i*3]   < xmin ) xmin = pTabFloat[i*3] ; 
           if ( pTabFloat[i*3+1] > ymax ) ymax = pTabFloat[i*3+1] ;
           if ( pTabFloat[i*3+1] < ymin ) ymin = pTabFloat[i*3+1] ;
           if ( pTabFloat[i*3+2] > zmax ) zmax = pTabFloat[i*3+2] ;
           if ( pTabFloat[i*3+2] < zmin ) zmin = pTabFloat[i*3+2] ;
        }
        
        // Determines the line type
        int isclosed(0),typeline ;
        piSysPolyline->GetCloseStatus(&isclosed);
        if ( 1 == isclosed ) 
        {
           // Case of closed object: Rectangle, Triangle 
           // The last line is beetween the last and first point
           typeline = LINE_LOOP ;
        }
        else
        {
           // Case of open object: Polyline
           // No last line beetween the last and first point
           typeline = LINE_STRIP ; 
        }

        // Creation of the 3D graphic representation
        pPolylineRep  = new CAT3DCustomRep() ;

        // Constructs the graphic primitive dedicated to the Polyline
        // In mode ALLOCATE, all data are duplicated into the graphic primitive
        CAT3DLineGP * pPolylineGp = NULL ;
        pPolylineGp = new CAT3DLineGP(pTabFloat,nbpoint,ALLOCATE,typeline);
        delete [] pTabFloat ;
        pTabFloat  = NULL ;

        // Adds the Gp to the rep with a default graphic attribut 
        CATGraphicAttributeSet PolylineGa ; 

        // Association of the Gp and the Ga to the Representation         // 
        pPolylineRep->AddGP(pPolylineGp,PolylineGa);

        // Computes the bounding sphere from the bounding box
        CATMathPoint centre((xmin+xmax)/2.,(ymin+ymax)/2.,(zmin+zmax)/2.);
        double radius = CATSqrt( (xmax-xmin)*(xmax-xmin) +
                              (ymax-ymin)*(ymax-ymin) +
                              (zmax-zmin)*(zmax-zmin) ) /2. ;

        // Sets the bounding sphere 
        CAT3DBoundingSphere be(centre,(float)radius) ;
        pPolylineRep->SetBoundingElement(be);

     }
     // Done with the polyline
     piSysPolyline -> Release();
     piSysPolyline = NULL ;
  }

  return pPolylineRep;
}


