// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CAAISysColorProperties.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysColorProperties = { /* d75dc502-dec7-11d3-b7f5-0008c74fe8dd */
    0xd75dc502,
    0xdec7,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };

// Declares that CAAISysColorProperties is an interface 
CATImplementInterface(CAAISysColorProperties, CATBaseUnknown);

