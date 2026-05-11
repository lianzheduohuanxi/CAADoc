// COPYRIGHT DASSAULT SYSTEMES 2003

// Local Framework
#include "CAAISysInterface.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//

IID IID_CAAISysInterface={ /* 0d143952-d4bf-11d3-b7f5-0108c74fe8dd */
    0x0d143952,
    0xd4bf,
    0x11d3,
    {0xb7, 0xf5, 0x01, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };



// Declares that CAAISysInterface is an interface 
CATImplementInterface(CAAISysInterface, CATBaseUnknown);
