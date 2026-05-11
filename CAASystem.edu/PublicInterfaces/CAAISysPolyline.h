#ifndef CAAISysPolyline_h
#define CAAISysPolyline_h

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a Polyline object.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GetListPoint/SetListPoint
//  GetCloseStatus/SetCloseStatus
//
//===========================================================================
// System Framework
#include <CATBaseUnknown.h>        // Needed to derive from CATBaseUnknown

// Mathematics Framework
class CATMathPoint ;

// Local Framework
#include "CAASysGeoModelInf.h" // Needed to export the IID

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysPolyline;

class ExportedByCAASysGeoModelInf CAAISysPolyline : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file
  CATDeclareInterface;

  public:

  // iList contains at least 3 points else error. This list is duplicated
  // in the polyline data. 
  virtual HRESULT SetListPoint ( const int iPointCount, CATMathPoint *  iList ) = 0;
  virtual HRESULT GetListPoint ( int * oPointCount    , CATMathPoint ** oList ) = 0;

  // 1 - Closed : It's a polygone 
  // 0 - Open   : It's a polyline
  virtual HRESULT SetCloseStatus ( const int iIsClosed ) = 0;
  virtual HRESULT GetCloseStatus (int * oIsClosed ) = 0;
};

#endif
