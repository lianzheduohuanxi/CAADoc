// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysPlane.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysPlane={ /* 0adf6be0-d4c0-11d3-b7f5-0008c74fe8dd */
    0x0adf6be0,
    0xd4c0,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAISysPlane is an interface
CATImplementInterface(CAAISysPlane, CATBaseUnknown);


