// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysCollection.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysCollection = { /* 8d143952-d4bf-11d3-b7f5-0008c74fe8dd */
    0x8d143952,
    0xd4bf,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAISysCollection is an interface
CATImplementInterface(CAAISysCollection, CATBaseUnknown);

