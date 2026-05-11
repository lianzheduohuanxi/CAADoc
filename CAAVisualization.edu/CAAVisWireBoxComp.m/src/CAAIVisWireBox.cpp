// COPYRIGHT DASSAULT SYSTEMES 1999

// Local Framework
#include "CAAIVisWireBox.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIVisWireBox={ /* d2ba5568-d869-4bf3-a45b-6e0ef9ae3d2d */
    0xd2ba5568,
    0xd869,
    0x4bf3,
    {0xa4, 0x5b, 0x6e, 0x0e, 0xf9, 0xae, 0x3d, 0x2d}
  };

// Declares that CAAIVisWireBox is an interface 
CATImplementInterface(CAAIVisWireBox, CATBaseUnknown);

