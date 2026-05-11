// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAISysCylinder.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAISysCylinder={ /* d50691a6-9e90-11d4-85bc-00108335648a */
    0xd50691a6,
    0x9e90,
    0x11d4,
    {0x85, 0xbc, 0x00, 0x10, 0x83, 0x35, 0x64, 0x8a}
  };

// Declares that CAAISysCylinder is an interface 
CATImplementInterface(CAAISysCylinder, CATBaseUnknown);
