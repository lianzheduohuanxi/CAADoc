#ifndef CAAIVisModelCGRObject_H
#define CAAIVisModelCGRObject_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//==========================================================================
//
// Abstract of the class: 
// -----------------------
// Interface which characterizes a CAAVisModelCGRObject object. 
//
//
//=============================================================================

// System Framework
#include "CATBaseUnknown.h"     // Needed to derive from CATBaseUnknown

///Visualization FrameWork
class CATRep ;

// Local framework
#include "CAAVisManagerInt.h"  // Needed to export the IID and the class

// Global Unique IDentifier defined in .cpp 
extern  ExportedByCAAVisManagerInt IID IID_CAAIVisModelCGRObject;

class ExportedByCAAVisManagerInt CAAIVisModelCGRObject : public CATBaseUnknown
{
   // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public :

  virtual HRESULT GetCGRRep(CATRep ** oCGRRep) = 0;
  virtual HRESULT ReadCGRFile(const char * iCGRFileName) = 0;

};

#endif 
