// COPYRIGHT DASSAULT SYSTEMES 1999


#include "CAAIVisModelObject.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
IID IID_CAAIVisModelObject = {
  0x295be138,
    0xd580,
    0x11d3,
    {0x9e, 0xd2, 0x00, 0x50, 0x8b, 0x12, 0x96, 0xfa}
  };


// Declares that CAAIVisModelObject is an interface that CNext-derive from CATBaseUnknown
CATImplementInterface(CAAIVisModelObject,CATBaseUnknown);

