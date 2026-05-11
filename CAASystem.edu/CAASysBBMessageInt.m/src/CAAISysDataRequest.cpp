// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysDataRequest.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysDataRequest= { /* b53d0f88-3b8c-11d4-85b5-00108335648a */
    0xb53d0f88,
    0x3b8c,
    0x11d4,
    {0x85, 0xb5, 0x00, 0x10, 0x83, 0x35, 0x64, 0x8a}
  };


// Declares that CAAISysDataRequest is an interface 
CATImplementInterface(CAAISysDataRequest, CATBaseUnknown);

