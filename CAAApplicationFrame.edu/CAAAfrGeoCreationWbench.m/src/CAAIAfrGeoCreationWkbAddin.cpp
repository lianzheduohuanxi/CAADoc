// COPYRIGHT DASSAULT SYSTEMES 1999

#include <CAAIAfrGeoCreationWkbAddin.h>

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIAfrGeoCreationWkbAddin = { /* a4188b88-d4c1-11d3-b7f5-0008c74fe8dd */
    0xa4188b88,
    0xd4c1,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAIAfrGeoCreationWkbAddin is an interface that 
// OM-derives from CATIWorkbenchAddin
CATImplementInterface(CAAIAfrGeoCreationWkbAddin, CATIWorkbenchAddin);

