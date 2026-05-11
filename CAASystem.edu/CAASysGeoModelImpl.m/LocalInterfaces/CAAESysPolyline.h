#ifndef CAAESysPolyline_H
#define CAAESysPolyline_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysPolyline component and implementing the 
//  CAAISysPolyline interface.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GetListPoint/SetListPoint
//  SetCloseStatus/SetCloseStatus
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"

// Mathematics Framework
class CATMathPoint;

class CAAESysPolyline : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public :

    CAAESysPolyline();
    virtual ~CAAESysPolyline();


    // A polyline is a list of 3D points 
    // ---------------------------------
    virtual HRESULT SetListPoint( const int iPointCount, CATMathPoint  * iList  );  

    // Returns E_FAIL if oPointCount or oList is NULL else S_OK 
    virtual HRESULT GetListPoint( int * oPointCount    , CATMathPoint ** oList );
 
    
    // this polyline can be closed, so it's a polygone 
    // ------------------------------------------------
    // Set 0 the object is a polyline else it's a polygone 
    //
    virtual HRESULT SetCloseStatus( const int iIsClosed ); 

    // Returns E_FAIL if oIsClosed is NULL else S_OK
    //
    virtual HRESULT GetCloseStatus( int * oIsClosed );  

  private:

   // Copy constructor, not implemented
   // Set as private to prevent from compiler automatic creation as public.
    CAAESysPolyline(const CAAESysPolyline &iObjectToCopy);
 
   // Assignment operator, not implemented
   // Set as private to prevent from compiler automatic creation as public.
    CAAESysPolyline & operator = (const CAAESysPolyline &iObjectToCopy);
 
  private :

    // this list contains at least 3 points
    CATMathPoint            * _pListe;
    int                       _PointCount;
    int                       _IsClosed ;
};

#endif
