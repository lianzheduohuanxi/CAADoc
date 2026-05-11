#ifndef CAAISysMyInterface_H
#define CAAISysMyInterface_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Interface which prints the content of a CAASysComponent object.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================

// System framework
#include "CATBaseUnknown.h"   // Needed to derive from CATBaseUnknown

// Local framework
#include "CAASysComponentInt.h"  // Needed to export the IID 

// Global Unique IDentifier defined in .cpp 
extern ExportedByCAASysComponentInt IID IID_CAAISysMyInterface;

class ExportedByCAASysComponentInt CAAISysMyInterface : public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

    virtual  HRESULT  Print()  const  =0 ;   

};
#endif
