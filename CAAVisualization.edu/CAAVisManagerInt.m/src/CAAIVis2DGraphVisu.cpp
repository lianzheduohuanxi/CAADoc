// COPYRIGHT DASSAULT SYSTEMES 1999


#include "CAAIVis2DGraphVisu.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
IID IID_CAAIVis2DGraphVisu =  { 
   0x2ccd5540,
   0xd884,
   0x11d3,
   {0x9e, 0xd6, 0x00, 0x50, 0x8b, 0x12, 0x96, 0xfa} 
};


// Declares that CAAIVis2DGraphVisu is an interface that OM-derives from CATBaseUnknown.
// Notice that this interface C++-derives from the CATIVisu interface (see CAAIVis2DGraphVisu.h)
// but doesn't OM-derive from the CATIVisu interface. This allows you to make a given component implement
// several visualization interfaces. If two interfaces deriving from CATIVisu were implemented
// by the same component, a QueryInterface call to CATIVisu would be underdetermined.
CATImplementInterface(CAAIVis2DGraphVisu, CATBaseUnknown);
