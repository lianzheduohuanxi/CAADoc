// COPYRIGHT DASSAULT SYSTEMES 1999

#include <CAAIAfrGeoAnalysisWkbAddin.h>

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
//
IID IID_CAAIAfrGeoAnalysisWkbAddin = { /* 66cbd58c-d4c1-11d3-b7f5-0008c74fe8dd */
    0x66cbd58c,
    0xd4c1,
    0x11d3,
    {0xb7, 0xf5, 0x00, 0x08, 0xc7, 0x4f, 0xe8, 0xdd}
  };


// Declares that CAAIAfrGeoAnalysisWkbAddin is an interface that 
// OM-derives from CATIWorkbenchAddin
CATImplementInterface(CAAIAfrGeoAnalysisWkbAddin, CATIWorkbenchAddin);

