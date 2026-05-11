#ifndef CAAIVisModelSetOfObject_H
#define CAAIVisModelSetOfObject_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//==========================================================================
//
// Abstract of the class: 
// -----------------------
// Interface which characterizes a CAAVisModelSetOfObject object.
//  
//=============================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

// Local framework
#include "CAAVisManagerInt.h"  // Needed to export the IID and the class

// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAAVisManagerInt IID IID_CAAIVisModelSetOfObject;

class ExportedByCAAVisManagerInt CAAIVisModelSetOfObject : public CATBaseUnknown
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :


};

#endif 
