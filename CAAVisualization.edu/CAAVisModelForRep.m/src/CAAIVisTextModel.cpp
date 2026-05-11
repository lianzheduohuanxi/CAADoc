// COPYRIGHT DASSAULT SYSTEMES 2003

// Local Framework
#include "CAAIVisTextModel.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIVisTextModel = { /* b776b3f8-b643-4834-912b-469dbd11b46d */
    0xb776b3f8,
    0xb643,
    0x4834,
    {0x91, 0x2b, 0x46, 0x9d, 0xbd, 0x11, 0xb4, 0x6d}
  };

// Declares that CAAIVisTextModel is an interface
CATImplementInterface(CAAIVisTextModel, CATBaseUnknown);

