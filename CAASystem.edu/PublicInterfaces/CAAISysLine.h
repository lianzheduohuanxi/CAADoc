#ifndef CAAISysLine_H
#define CAAISysLine_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a line object.
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
//  SetStartPoint/GetStartPoint
//  SetEndPoint/GetEndPoint
//
//===========================================================================

//System Framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Mathematics Framework
class CATMathPoint;     // Needed by the methods

// Local Framework
#include "CAASysGeoModelInf.h"  // // Needed to export the IID 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysGeoModelInf IID IID_CAAISysLine;

class ExportedByCAASysGeoModelInf CAAISysLine : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

  virtual HRESULT  SetStartPoint(const CATMathPoint & iStartPoint) =0;
  virtual HRESULT  SetEndPoint  (const CATMathPoint & iEndPoint)   =0;

  virtual HRESULT  GetStartPoint(CATMathPoint & oStartPoint) const =0;
  virtual HRESULT  GetEndPoint  (CATMathPoint & oEndPoint  ) const =0;
 

};
#endif
