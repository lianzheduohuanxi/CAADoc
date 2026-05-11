// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAAISysRevolAxis.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysRevolAxis = { /* f4d444d8-ef77-11d3-b7f5-0008c74fe8dd */
    0xf4d444d8,
    0xef77,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAISysRevolAxis is an interface 
CATImplementInterface(CAAISysRevolAxis, CATBaseUnknown);

