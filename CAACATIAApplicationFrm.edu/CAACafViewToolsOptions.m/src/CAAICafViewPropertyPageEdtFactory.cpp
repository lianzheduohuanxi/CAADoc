#include "CAAICafViewPropertyPageEdtFactory.h"
//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAICafViewPropertyPageEdtFactory = { /* 42d5550c-d586-11d3-b7f5-0008c74fe8dd */
    0x42d5550c,
    0xd586,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAICafViewPropertyPageEdtFactory is an interface that 
// OM derives from CATIGenericFactory
CATImplementInterface(CAAICafViewPropertyPageEdtFactory, CATIGenericFactory);
