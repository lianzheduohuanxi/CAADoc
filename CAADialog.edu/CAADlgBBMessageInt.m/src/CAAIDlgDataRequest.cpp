// COPYRIGHT DASSAULT DlgTEMES 1999

// Local Framework
#include "CAAIDlgDataRequest.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIDlgDataRequest= { /* 364c0254-4bfb-11d4-85b8-00108335648a */
    0x364c0254,
    0x4bfb,
    0x11d4,
    {0x85, 0xb8, 0x00, 0x10, 0x83, 0x35, 0x64, 0x8a}
  };

// Declares that CAAIDlgDataRequest is an interface 
CATImplementInterface(CAAIDlgDataRequest, CATBaseUnknown);

