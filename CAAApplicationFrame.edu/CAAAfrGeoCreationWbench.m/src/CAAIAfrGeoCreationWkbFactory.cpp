// COPYRIGHT DASSAULT SYSTEMES 1999

#include <CAAIAfrGeoCreationWkbFactory.h>

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIAfrGeoCreationWkbFactory = { /* b32eed10-d4c1-11d3-b7f5-0008c74fe8dd */
    0xb32eed10,
    0xd4c1,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAIAfrGeoCreationWkbFactory is an interface that 
// OM-derives from CATIGenericFactory
CATImplementInterface(CAAIAfrGeoCreationWkbFactory, CATIGenericFactory);
