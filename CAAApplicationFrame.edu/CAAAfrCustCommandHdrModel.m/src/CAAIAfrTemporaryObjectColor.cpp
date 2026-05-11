// COPYRIGHT DASSAULT SYSTEMES 2003

// Local Framework
#include "CAAIAfrTemporaryObjectColor.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIAfrTemporaryObjectColor = { /* efc100b7-173b-4c1e-96c5-ed748e52da12 */
    0xefc100b7,
    0x173b,
    0x4c1e,
    {0x96, 0xc5, 0xed, 0x74, 0x8e, 0x52, 0xda, 0x12}
  };

// Declares that CAAIAfrGetTemporaryObjectColor is an interface
CATImplementInterface(CAAIAfrTemporaryObjectColor, CATBaseUnknown);

