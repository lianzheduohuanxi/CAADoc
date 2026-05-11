// COPYRIGHT DASSAULT SYSTEMES 1999


#include "CAAIVisModelSetOfObject.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
IID IID_CAAIVisModelSetOfObject = { /* 178481b6-2d65-11d4-85b4-00108335648a */
    0x178481b6,
    0x2d65,
    0x11d4,
    {0x85, 0xb4, 0x00, 0x10, 0x83, 0x35, 0x64, 0x8a}
  };


// Declares that CAAIVisModelSetOfObject is an interface that CNext-derive from CATBaseUnknown
CATImplementInterface(CAAIVisModelSetOfObject,CATBaseUnknown);

