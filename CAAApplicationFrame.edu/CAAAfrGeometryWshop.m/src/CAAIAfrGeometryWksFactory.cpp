// COPYRIGHT DASSAULT SYSTEMES 1999

#include <CAAIAfrGeometryWksFactory.h>

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIAfrGeometryWksFactory = { /* 0f55f206-d4c1-11d3-b7f5-0008c74fe8dd */
    0x0f55f206,
    0xd4c1,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAIAfrGeometryWksFactory is an interface that 
// OM-derives from CATIGenericFactory
CATImplementInterface(CAAIAfrGeometryWksFactory, CATIGenericFactory);
