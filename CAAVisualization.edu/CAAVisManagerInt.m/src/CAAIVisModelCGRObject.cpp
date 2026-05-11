// COPYRIGHT DASSAULT SYSTEMES 1999


#include "CAAIVisModelCGRObject.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
IID IID_CAAIVisModelCGRObject = { /* 1e35c384-21bd-11d4-85b3-00108335648a */
    0x1e35c384,
    0x21bd,
    0x11d4,
    {0x85, 0xb3, 0x00, 0x10, 0x83, 0x35, 0x64, 0x8a}
  };


// Declares that CAAIVisModelCGRObject is an interface that CNext-derive from CATBaseUnknown
CATImplementInterface(CAAIVisModelCGRObject,CATBaseUnknown);

