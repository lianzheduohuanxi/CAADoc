// COPYRIGHT DASSAULT SYSTEMES 2000

#include "CAAISysSurfaceProperties.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysSurfaceProperties = { /* ca8e731a-ef77-11d3-b7f5-0008c74fe8dd */
    0xca8e731a,
    0xef77,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAISysSurfaceProperties is an interface 
CATImplementInterface(CAAISysSurfaceProperties, CATBaseUnknown);

