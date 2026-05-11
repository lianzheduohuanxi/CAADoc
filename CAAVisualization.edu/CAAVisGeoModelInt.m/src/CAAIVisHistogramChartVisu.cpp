// COPYRIGHT DASSAULT SYSTEMES 1999


#include "CAAIVisHistogramChartVisu.h"

// Use uuid_gen -C on UNIX or uuidgen -s on NT  to generate the IID 
IID IID_CAAIVisHistogramChartVisu =  { /* fb7bec2e-66b3-11d4-85ba-00108335648a */
    0xfb7bec2e,
    0x66b3,
    0x11d4,
    {0x85, 0xba, 0x00, 0x10, 0x83, 0x35, 0x64, 0x8a}
  };


// Declares that CAAIVisHistogramChartVisu is an interface that OM-derives from CATBaseUnknown.
// Notice that this interface C++-derives from the CATIVisu interface (see CAAIVisHistogramChartVisu.h)
// but doesn't OM-derive from the CATIVisu interface. This allows you to make a given component implement
// several visualization interfaces. If two interfaces deriving from CATIVisu were implemented
// by the same component, a QueryInterface call to CATIVisu would be underdetermined.
CATImplementInterface(CAAIVisHistogramChartVisu, CATBaseUnknown);
