// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysCircle.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysCircle={ /* f281aba4-d4b4-11d3-b7f5-0008c74fe8dd */
    0xf281aba4,
    0xd4b4,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAISysCircle is an interface 
CATImplementInterface(CAAISysCircle, CATBaseUnknown);
