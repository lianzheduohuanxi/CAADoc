//
// COPYRIGHT DASSAULT SYSTEMES 2000
//
#include "CAAICafColorPropertyPageEdtFactory.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAICafColorPropertyPageEdtFactory = { /* 95495a52-dee3-11d3-b7f5-0008c74fe8dd */
    0x95495a52,
    0xdee3,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAICafColorPropertyPageEdtFactory is an interface that 
// OM derives from CATIGenericFactory
CATImplementInterface(CAAICafColorPropertyPageEdtFactory, CATIGenericFactory);
