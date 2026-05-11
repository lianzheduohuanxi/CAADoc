// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysPointProperties.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysPointProperties = { /* de5dbf42-ea89-11d3-b7f5-0008c74fe8dd */
    0xde5dbf42,
    0xea89,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAISysPointProperties is an interface 
CATImplementInterface(CAAISysPointProperties, CATBaseUnknown);

