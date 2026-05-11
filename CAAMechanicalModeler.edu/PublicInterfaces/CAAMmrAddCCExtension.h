#ifndef CAAMmrAddCCExtension_H
#define CAAMmrAddCCExtension_H

//COPYRIGHT DASSAULT SYSTEMES 2001

class CAAIMmrCCDataExtension ;
#include <CAAMmrCCDataExtension.h>
#include  <CATBaseUnknown.h>

HRESULT ExportedByCAAMmrCCDataExtension CAAMmrAddCCExtension(const CATBaseUnknown *iBaseFeature,CAAIMmrCCDataExtension **ioMmrCCDataExtension) ;
                                                       

#endif

