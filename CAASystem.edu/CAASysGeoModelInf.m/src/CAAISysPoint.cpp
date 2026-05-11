// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysPoint.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysPoint = { /* 757bc01e-d4ae-11d3-b7f5-0008c74fe8dd */
    0x757bc01e,
    0xd4ae,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAISysPoint is an interface
CATImplementInterface(CAAISysPoint, CATBaseUnknown);
