#ifndef CAAIVisWireBox_h
#define CAAIVisWireBox_h

// COPYRIGHT DASSAULT SYSTEMES 1999
   
//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which characterizes a wire box. This interface and the wire box is
//  used in the CAADegClippingByBoxCmd class in the CAADialogEngine.edu 
//  framework. 
//
//===========================================================================
// System Framework
#include <CATBaseUnknown.h>        // Needed to derive from CATBaseUnknown


// Local Framework
#include "CAAVisWireBoxComp.h" // Needed to export the IID

// Mathematics framework
class CATMathPoint;     // Needed by SetCenterBox & GetCenterBox 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAAVisWireBoxComp IID IID_CAAIVisWireBox;

class ExportedByCAAVisWireBoxComp CAAIVisWireBox : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file
  CATDeclareInterface;

  public:

  virtual HRESULT SetDimBox ( const float iDimBox ) = 0;
  virtual HRESULT GetDimBox (float * oDimBox ) = 0;

  virtual  HRESULT  SetCenterBox(const CATMathPoint & iCenter)  =0 ;
  virtual  HRESULT  GetCenterBox(CATMathPoint & oCenter) const  =0 ;

};

#endif
