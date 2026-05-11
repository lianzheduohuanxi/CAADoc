//
// COPYRIGHT DASSAULT SYSTEMES 2000
//

#include "CAAICafElementPropertyPageEdtFactory.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAICafElementPropertyPageEdtFactory = { /* 4ee83c16-d55d-11d3-b7f5-0008c74fe8dd */
    0x4ee83c16,
    0xd55d,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAICafElementPropertyPageEdtFactory is an interface that 
// OM derives from CATIGenericFactory
CATImplementInterface(CAAICafElementPropertyPageEdtFactory, CATIGenericFactory);
