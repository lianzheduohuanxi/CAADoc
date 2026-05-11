// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysGeomFactory.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysGeomFactory = { /* ba6349ac-d4bf-11d3-b7f5-0008c74fe8dd */
    0xba6349ac,
    0xd4bf,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAISysGeomFactory is an interface
CATImplementInterface(CAAISysGeomFactory, CATBaseUnknown);

