// COPYRIGHT DASSAULT SYSTEMES 1999

#include <CAAIAfrGeometryWksAddin.h>

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIAfrGeometryWksAddin = { /* f749fa4a-d4c0-11d3-b7f5-0008c74fe8dd */
    0xf749fa4a,
    0xd4c0,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAIAfrGeometryWksAddin is an interface that 
// OM-derives from CATIWorkbenchAddin
CATImplementInterface(CAAIAfrGeometryWksAddin, CATIWorkbenchAddin);


