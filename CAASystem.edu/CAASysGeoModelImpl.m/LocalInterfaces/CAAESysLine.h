#ifndef CAAESysLine_H
#define CAAESysLine_H

// COPYRIGHT DASSAULT SYSTEMES 1999
 
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Data extension ofd the CAASysLine component and implementing the 
//  CAAISysLine interface.
//
//===========================================================================
//  Main Method:
//  ------------
//
//  SetStartPoint/GetStartPoint
//  SetEndPoint/GetEndPoint
//
//===========================================================================

// System Framework
#include "CATBaseUnknown.h"  //Needed to derive from CATBaseUnknown

// Mathematics Framework
#include "CATMathPoint.h"    //Needed by the methods


class CAAESysLine : public CATBaseUnknown
{
  // Used in conjunction with CATImplementClass in the .cpp file
  CATDeclareClass;

  public:

    CAAESysLine();
    virtual ~CAAESysLine();

    // Start Point 
    virtual  HRESULT  SetStartPoint(const CATMathPoint  & iStartPoint) ;
    virtual  HRESULT  GetStartPoint(CATMathPoint  & oStartPoint) const ;

    // End Point 
    virtual  HRESULT  SetEndPoint  (const CATMathPoint  & iEndPoint)   ;
    virtual  HRESULT  GetEndPoint  (CATMathPoint  & oEndPoint)   const ;

  private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysLine(const CAAESysLine &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAESysLine & operator = (const CAAESysLine &iObjectToCopy);


  private:

    CATMathPoint    _StartPoint ;
    CATMathPoint    _EndPoint ;

};
#endif
