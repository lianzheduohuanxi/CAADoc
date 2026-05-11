// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysCuboid.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysCuboid = { /* 1d1246c2-986d-11d4-85bc-00108335648a */
    0x1d1246c2,
    0x986d,
    0x11d4,
    {0x85, 0xbc, 0x00, 0x10, 0x83, 0x35, 0x64, 0x8a}
  };

// Declares that CAAISysCuboid is an interface
CATImplementInterface(CAAISysCuboid, CATBaseUnknown);
