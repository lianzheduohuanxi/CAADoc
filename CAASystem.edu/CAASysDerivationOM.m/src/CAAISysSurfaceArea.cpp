// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAAISysSurfaceArea.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysSurfaceArea = { /* d41578c0-ef77-11d3-b7f5-0008c74fe8dd */
    0xd41578c0,
    0xef77,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAISysSurfaceArea is an interface 
CATImplementInterface(CAAISysSurfaceArea, CATBaseUnknown);

