#ifndef CAAIVisModelSphere_H
#define CAAIVisModelSphere_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//==========================================================================
//
// Abstract of the class: 
// -----------------------
// Interface which characterizes a CAAVisModelSphere object.
//  
//=============================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

//Mathematics FrameWork
class CATMathPointf;

// Local framework
#include "CAAVisManagerInt.h"  // Needed to export the IID and the class

// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAAVisManagerInt IID IID_CAAIVisModelSphere;

class ExportedByCAAVisManagerInt CAAIVisModelSphere : public CATBaseUnknown
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

    // The circle is defined by: 
    // ------------------------

    //  A point center 
    // -------------------
    virtual  HRESULT     SetCenter(const CATMathPointf & iCenter)  =0 ;
    virtual  HRESULT     GetCenter(CATMathPointf & oCenter) const  =0 ;

    //  A radius
    // -------------------
    virtual  HRESULT     SetRadius(const float iRadius)           =0 ;
    virtual  HRESULT     GetRadius(float & oRadius)        const  =0 ;

};

#endif 
