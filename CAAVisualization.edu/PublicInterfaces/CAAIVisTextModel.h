#ifndef CAAIVisTextModel_h
#define CAAIVisTextModel_h

// COPYRIGHT DASSAULT SYSTEMES 2003

//
//===========================================================================
// Interface implemented by the CAAVisTextModel component
// 
//===========================================================================
//
// System Framework
#include <CATBaseUnknown.h>       //Needed to derive from 

// Local Framework
#include "CAAVisModelForRep.h"  //Needed to export the IID

// VisualizationBase Framework
class CATRep ;

// Global Unique IDentifier defined in .cpp 
// exported by CAAAfrCustomizedCommandHeader
extern IID ExportedByCAAVisModelForRep IID_CAAIVisTextModel;

class ExportedByCAAVisModelForRep CAAIVisTextModel: public CATBaseUnknown
{
  // Used in conjunction with CATImplementInterface in the .cpp file 
  CATDeclareInterface;

  public:

      virtual HRESULT SetGraphicRepresentation(CATRep * iRep) = 0;
  
};


#endif
